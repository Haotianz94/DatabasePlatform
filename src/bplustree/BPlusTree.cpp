#include <cstdlib>
#include <cstring>
#include "../database/FileOperation.h"
#include "../utils/FileStructureUtil.h"
#include "FileAccesser.h"
#include "KeyValue.h"

#include "BPlusTree.h"

using namespace std;

BPlusTree :: BPlusTree(FileOperation *fileOperation, 
    int indexLength, int dataLength, int treeId, int rootPageId, int keyType) :
    indexLen(indexLength), 
    dataLen(dataLength),
    rootPage(rootPageId),
    fileOpt(fileOperation)
{
    this->keyType = keyType;
    fileAcc = new FileAccesser(fileOperation, indexLength, dataLength, treeId, keyType, rootPage);
    if (rootPage < 0)
        this->rootPage = fileAcc->createTree();
    else
        fileAcc->loadTree();
}

BPlusTree :: ~BPlusTree()
{
    delete fileAcc;
}

int BPlusTree :: findInNode(const KeyValue* index, FindMode mode)
{
    int step = 1, childNum = fileAcc->getChildNum(), pos;
    for (; step <= childNum; step <<= 1);
    step >>= 1;
    switch (mode)
    {
        case less:
            for (pos = -1; step; step >>= 1)
                if (pos + step < childNum)
                {
                    KeyValue *curIndex = fileAcc->getIndex(pos + step);
                    pos += curIndex->compare(index) < 0 ? step : 0;
                    delete curIndex;
                }
            break;
        case lessequal:
        case equal:
            for (pos = -1; step; step >>= 1)
                if (pos + step < childNum)
                {
                    KeyValue *curIndex = fileAcc->getIndex(pos + step);
                    pos += curIndex->compare(index) <= 0 ? step : 0;
                    delete curIndex;
                }
            break;
    }
    return pos;
}

int BPlusTree :: findInNode(const KeyValue* index)
{
    int step = 1, childNum = fileAcc->getChildNum(), pos;
    for (; step <= childNum; step <<= 1);
    step >>= 1;
    for (pos = -1; step; step >>= 1)
        if (pos + step < childNum)
        {
            KeyValue *curIndex = fileAcc->getIndex(pos + step);
            pos += curIndex->compWithMagicKey(index) <= 0 ? step : 0;
            delete curIndex;
        }
    return pos;
}

BPlusTree :: Iterator BPlusTree :: insert(KeyValue* index, unsigned char* data)
{
    BPlusTree :: Iterator ret(fileAcc);
    fileAcc->toPage(rootPage);
    if (fileAcc->getChildNum() == 0)
    {
        fileAcc->insertFirstNode(index, data, ret);
        return ret;
    }

    int splitedPointer;
    KeyValue* splitedIndex;
    for(index->setMagicKey(); !_insert(rootPage, index, data, ret, splitedPointer, splitedIndex); index->setMagicKey());
    if (splitedIndex != NULL)
    {
        // Create new root.
        fileAcc->toPage(rootPage);
        int oldRoot = rootPage;
        KeyValue* oldIndex = fileAcc->getIndex(0);
        rootPage = fileAcc->createNewRoot();
        fileAcc->insert(0, oldIndex, oldRoot);
        fileAcc->insert(1, splitedIndex, splitedPointer);
        delete splitedIndex;
        delete oldIndex;
    }
    return ret;
}

bool BPlusTree :: _insert(int pageId, const KeyValue* index, unsigned char* data, 
    BPlusTree :: Iterator &ret, int& splitedPointer, KeyValue*& splitedIndex)
{
    fileAcc->toPage(pageId);
    if (fileAcc->getIsLeaf())
    {
        int insertPos = findInNode(index) + 1;
        if (insertPos > 0)
        {
            KeyValue *curIndex = fileAcc->getIndex(insertPos - 1);
            if (curIndex->magicKey == index->magicKey)
            {
                delete curIndex;
                return false;
            }
            delete curIndex;
        }
        if (fileAcc->getChildNum() == fileAcc->getMaxChildNum())
        {
            // Split.
            int mid = fileAcc->getChildNum() / 2 - 1;
            if (mid >= 0)
            {
                splitedPointer = fileAcc->split(mid, pageId);
                splitedIndex = fileAcc->getIndex(0);
                if (insertPos <= mid + 1)
                {
                    fileAcc->toPage(pageId);
                    fileAcc->insert(insertPos, index, data);
                    ret.pid = pageId;
                    ret.pos = insertPos;
                }
                else
                {
                    fileAcc->insert(insertPos - mid - 1, index, data);
                    ret.pid = splitedPointer;
                    ret.pos = insertPos - mid - 1;
                }
            }
            else
            {
                if (insertPos == 0)
                {
                    splitedPointer = fileAcc->split(-1, pageId);
                    splitedIndex = fileAcc->getIndex(0);
                    fileAcc->toPage(pageId);
                    fileAcc->insert(0, index, data);
                    ret.pid = pageId;
                    ret.pos = 0;
                }
                else
                {
                    splitedPointer = fileAcc->split(0, pageId);
                    unsigned char *s = new unsigned char[indexLen + 5];
                    index->toCharArray(s);
                    splitedIndex = KeyValue::fromCharArray(s, keyType);
                    delete s;
                    fileAcc->insert(0, index, data);
                    ret.pid = splitedPointer;
                    ret.pos = 0;
                }
            }
        }
        else
        {
            fileAcc->insert(insertPos, index, data);
            ret.pid = pageId;
            ret.pos = insertPos;
            splitedPointer = -1;
            splitedIndex = NULL;
        }
        return true;
    }
    
    int pos = findInNode(index);
    if (!_insert(fileAcc->getPointer(pos==-1 ? 0 : pos), index, data, ret, splitedPointer, splitedIndex))
        return false;
    fileAcc->toPage(pageId);
    if (pos == -1)
        fileAcc->changeIndex(0, index);
    if (splitedIndex != NULL)
    {
        // Need Insert.
        int insertPos = (pos==-1?0:pos) + 1;
        if (fileAcc->getChildNum() == fileAcc->getMaxChildNum())
        {
            // Split.
            int mid = fileAcc->getChildNum() / 2 - 1;
            int newSplitedPointer = fileAcc->split(mid, pageId);
            KeyValue* newSplitedIndex = fileAcc->getIndex(0);
            if (insertPos <= mid + 1)
            {
                fileAcc->toPage(pageId);
                fileAcc->insert(insertPos, splitedIndex, splitedPointer);
            }
            else
                fileAcc->insert(insertPos - mid - 1, splitedIndex, splitedPointer);
            delete splitedIndex;
            splitedIndex = newSplitedIndex;
            splitedPointer = newSplitedPointer;
        }
        else
        {
            // No split.
            fileAcc->insert(insertPos, splitedIndex, splitedPointer);
            delete splitedIndex;
            splitedPointer = -1;
            splitedIndex = NULL;
        }
    }
    return true;
}

void BPlusTree :: erase(const BPlusTree :: Iterator &iterator)
{
    if (iterator == this->end())
        return;
    fileAcc->toPage(iterator.pid);
    KeyValue *index = fileAcc->getIndex(iterator.pos);
    if (_erase(rootPage, index))
    {
        rootPage = fileAcc->createTree();
    }
    delete index;
}

bool BPlusTree :: _erase(int pageId, const KeyValue* index)
{
    fileAcc->toPage(pageId);
    int pos = findInNode(index);
    if (fileAcc->getIsLeaf())
    {
        fileAcc->erase(pos);
        if (fileAcc->getChildNum() == 0)
        {
            int prev = fileAcc->getPrevLeaf(), next = fileAcc->getNextLeaf();
            fileAcc->recyclePage();
            if (prev != 0)
            {
                fileAcc->toPage(prev);
                fileAcc->setNextLeaf(next);
            }
            if (next != 0)
            {
                fileAcc->toPage(next);
                fileAcc->setPrevLeaf(prev);
            }
            return true;
        }
        return false;
    }
    if (_erase(fileAcc->getPointer(pos), index))
    {
        fileAcc->toPage(pageId);
        fileAcc->erase(pos);
        if (fileAcc->getChildNum() == 0)
        {
            fileAcc->recyclePage();
            return true;
        }
        return false;
    }
}

BPlusTree :: Iterator BPlusTree :: find(const KeyValue* index, FindMode mode)
{
    fileAcc->toPage(rootPage);
    if (fileAcc->getChildNum() == 0 || index->compare(fileAcc->getIndex(0)) < 0)
        return this->end();
    Iterator found = _find(rootPage, index, mode);
    if (mode == equal && found.getKey()->compare(index) != 0)
        return this->end();
    return found;
}

BPlusTree :: Iterator BPlusTree :: _find(int pageId, const KeyValue* index, FindMode mode)
{
    fileAcc->toPage(pageId);
    if (fileAcc->getIsLeaf())
    {
        int pos = findInNode(index, mode);
        if (pos >= 0)
            return BPlusTree::Iterator(fileAcc, pageId, findInNode(index, mode));
        else
            return end();
    }
    int pos = findInNode(index, mode), last;
    if (pos < 0)
        return end();
    if (pos > 0)
        last = fileAcc->getPointer(pos - 1);
    Iterator ret = _find(fileAcc->getPointer(pos), index, mode);
    if (ret != end())
        return ret;
    if (ret == end() && pos > 0)
        return _find(last, index, mode);
    return end();
}

BPlusTree :: Iterator BPlusTree :: begin()
{
    int pageId = rootPage;
    for (fileAcc->toPage(rootPage); !fileAcc->getIsLeaf();)
    {
        pageId = fileAcc->getPointer(0);
        if (pageId == 0)
            return end();
        fileAcc->toPage(pageId);
    }
    while(fileAcc && fileAcc->getChildNum() == 0)
    {
        pageId = fileAcc->getNextLeaf();
        if (pageId == 0)
            return end();
        fileAcc->toPage(pageId);
    }
    return BPlusTree::Iterator(fileAcc, pageId, 0);
}

BPlusTree :: Iterator BPlusTree :: end()
{
    return BPlusTree :: Iterator(fileAcc);
}

// ----------------------------------- Iterator realization -----------------------------------------------

BPlusTree :: Iterator :: Iterator(FileAccesser *acc) :
    f(acc), pid(-1), pos(0)
{}

BPlusTree :: Iterator :: Iterator(FileAccesser *acc, int pageId, int position) :
    f(acc), pid(pageId), pos(position)
{}

BPlusTree :: Iterator :: ~Iterator()
{}

unsigned char* BPlusTree :: Iterator :: operator *()
{
    if (pid < 0)
        return NULL;
    f->toPage(pid);
    return f->getData(pos);
}

bool BPlusTree :: Iterator :: operator == (const Iterator &b) const
{
    return f == b.f && pid == b.pid && pos == b.pos;
}

bool BPlusTree :: Iterator :: operator != (const Iterator &b) const
{
    return f != b.f || pid != b.pid || pos != b.pos;
}

BPlusTree::Iterator& BPlusTree :: Iterator :: operator ++()
{
    f->toPage(pid);
    if (pos < f->getChildNum() - 1)
        pos++;
    else
    {
        pos = 0;
        do
        {
            pid = f->getNextLeaf();
            f->toPage(pid);
        }
        while (pid && !f->getChildNum());
        if (pid == 0)
            pid = -1;
    }
}

void BPlusTree :: Iterator :: markRead()
{
    f->markRead();
}

void BPlusTree :: Iterator :: toCharArray(unsigned char* s)
{
    int2tribytes(pid, s);
    int2tribytes(pos, s + 4);
}

BPlusTree::Iterator BPlusTree :: Iterator :: fromCharArray(BPlusTree* tree, unsigned char* p)
{
    int pageId = (((p[0] << 8) | p[1]) << 8) | p[2],
        position = (((p[3] << 8) | p[4]) << 8) | p[5];
    return Iterator(tree->fileAcc, pageId, position);
}

KeyValue* BPlusTree :: Iterator :: getKey()
{
    return f->getIndex(pos);
}