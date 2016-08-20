#include <cstring>
#include <cstdlib>

#include "../database/FileOperation.h"
#include "BPlusTree.h"
#include "../utils/FileStructureUtil.h"

#include "FileAccesser.h"

// For no-leaf node:
// Addtion bytes: 
//   3 bytes for the node number of this sub-tree.
// Records format:
//   n bytes for index + 4 bytes for pointer (only 3 bytes used).
// For leaf node:
// Addtion bytes:
//   3 bytes for pointer to the next leaf.
//   3 bytes for pointer to the prev leaf.
// Records format:
//   n bytes for index + m bytes for data.

unsigned char FileAccesser :: buf[9001];
const int FileAccesser :: NOLEAF_ADD_BYTES = 4;
const int FileAccesser :: LEAF_ADD_BYTES = 8;

FileAccesser :: FileAccesser(FileOperation *fileOperation, int indexLength, int dataLength, int treeId, int keyType, int rootPageId) :
    fOperation(fileOperation), tid(treeId), indexLen(indexLength + 4), dataLen(dataLength), rootPage(rootPageId),
    noLeafMaxChNum(-1), leafMaxChNum(-1)
{
    this->keyType = keyType;
    alignedIndexLen = ((indexLen + 3) >> 2) << 2;
    alignedDataLen = ((dataLen + 3) >> 2) << 2;
}

FileAccesser :: ~FileAccesser()
{}

int FileAccesser :: createTree()
{
    rootPage = fOperation->createPage(PAGETYPE_BTREE_NODE, NOLEAF_ADD_BYTES, 4 + alignedIndexLen);
    fOperation->changeRootpageById(tid, rootPage);
    return rootPage;
}

void FileAccesser :: loadTree()
{}

int FileAccesser :: createNewRoot()
{
    int ret = createTree();
    toPage(ret);
    return ret;
}

int FileAccesser :: getMaxChildNum()
{
    if (fOperation->getKind() == PAGETYPE_BTREE_NODE)
    {
        if (noLeafMaxChNum == -1)
            noLeafMaxChNum = fOperation->getMaxRecordNum();
        return noLeafMaxChNum;
    }
    else
    {
        if (leafMaxChNum == -1)
            leafMaxChNum = fOperation->getMaxRecordNum();
        return leafMaxChNum;
    }
}

int FileAccesser :: getChildNum()
{
    return fOperation->getRecordsAmount();
}

bool FileAccesser :: getIsLeaf()
{
    return fOperation->getKind() == PAGETYPE_BTREE_LEAF;
}

void FileAccesser :: toPage(int pageId)
{
    fOperation->toPage(pageId);
}

void FileAccesser :: markRead()
{
    fOperation->markRead();
}

KeyValue* FileAccesser :: getIndex(int pos)
{
    return KeyValue::fromCharArray(fOperation->getIthRecord(pos), keyType);
}

void FileAccesser :: changeIndex(int pos, const KeyValue* index)
{
    index->toCharArray(fOperation->getIthRecord(pos));
    fOperation->markRead();
}

int FileAccesser :: getPointer(int pos)
{
    unsigned char *s = fOperation->getIthRecord(pos) + alignedIndexLen;
    return (((s[0] << 8) | s[1]) << 8) | s[2];
}

unsigned char* FileAccesser :: getData(int pos)
{
    return fOperation->getIthRecord(pos) + alignedIndexLen;
}

void FileAccesser :: erase(int pos)
{
    fOperation->remove(pos);
}

void FileAccesser :: insertFirstNode(const KeyValue* index, const unsigned char* data, BPlusTree :: Iterator &ret)
{
    int leafPage = 
        fOperation->createPage(PAGETYPE_BTREE_LEAF, LEAF_ADD_BYTES, alignedIndexLen + alignedDataLen);
    index->toCharArray(buf);
    memcpy(buf + alignedIndexLen, data, dataLen);
    fOperation->insert(0, buf);
    ret.pid = leafPage;
    ret.pos = 0;
    
    fOperation->toPage(rootPage);
    int2tribytes(leafPage, buf + alignedIndexLen);
    fOperation->insert(0, buf);
}

void FileAccesser :: insert(int pos, const KeyValue* index, const unsigned char* data)
{
    index->toCharArray(buf);
    memcpy(buf + alignedIndexLen, data, dataLen);
    fOperation->insert(pos, buf);
}

void FileAccesser :: insert(int pos, const KeyValue* index, int pointer)
{
    index->toCharArray(buf);
    int2tribytes(pointer, buf + alignedIndexLen);
    fOperation->insert(pos, buf);
}

int FileAccesser :: split(int pos, int curPage)
{
    if (getIsLeaf())
    {
        int recordLen = alignedIndexLen + alignedDataLen;
        int rightHalfLen = getChildNum() - pos - 1;
        memcpy(buf, fOperation->getIthRecord(pos + 1), recordLen * rightHalfLen);
        
        int oldNext = getNextLeaf();
        unsigned char buf2[10];
        int2tribytes(oldNext, buf2);
        int2tribytes(curPage, buf2 + 4);
        int newPage = fOperation->createPage(PAGETYPE_BTREE_LEAF, LEAF_ADD_BYTES, recordLen, buf2, rightHalfLen);
        memcpy(fOperation->getIthRecord(0), buf, recordLen * rightHalfLen);
        fOperation->markRead();

        fOperation->toPage(curPage);
        fOperation->setRecordsAmount(pos + 1);
        setNextLeaf(newPage);

        if (oldNext != 0)
        {
            fOperation->toPage(oldNext);
            setPrevLeaf(newPage);
        }

        fOperation->toPage(newPage);
        return newPage;
    }
    else
    {
        int recordLen = alignedIndexLen + 4;
        int rightHalfLen = getChildNum() - pos - 1;
        memcpy(buf, fOperation->getIthRecord(pos + 1), recordLen * rightHalfLen);
        fOperation->setRecordsAmount(pos + 1);
        int newPage = fOperation->createPage(PAGETYPE_BTREE_NODE, NOLEAF_ADD_BYTES, recordLen, NULL, rightHalfLen);
        memcpy(fOperation->getIthRecord(0), buf, recordLen * rightHalfLen);
        fOperation->markRead();
        return newPage;
    }
}

int FileAccesser :: getNextLeaf()
{
    unsigned char *b = fOperation->getSpcField();
    return (((b[0] << 8) | b[1]) << 8) | b[2];
}

int FileAccesser :: getPrevLeaf()
{
    unsigned char *b = fOperation->getSpcField();
    return (((b[4] << 8) | b[5]) << 8) | b[6];
}

void FileAccesser :: setNextLeaf(int id)
{
    unsigned char *b = fOperation->getSpcField();
    int2tribytes(id, b);
    markRead();
}

void FileAccesser :: setPrevLeaf(int id)
{
    unsigned char *b = fOperation->getSpcField();
    int2tribytes(id, b + 4);
    markRead();
}

void FileAccesser :: recyclePage()
{}
