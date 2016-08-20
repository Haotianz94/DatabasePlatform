#ifndef __BPLUSTREE__FILEACCESSER__H__
#define __BPLUSTREE__FILEACCESSER__H__

#include <cstring>
#include <cstdlib>

#include "BPlusTree.h"
#include "KeyValue.h"

class FileOperation;

class FileAccesser
{
public:
    FileAccesser(FileOperation *fileOperation, int indexLength, int dataLength, int treeId, int keyType, int rootPageId);
    ~FileAccesser();

    int createNewRoot();
    int getMaxChildNum();
    int getChildNum();
    bool getIsLeaf();

    void toPage(int pageId);

    void markRead();

    KeyValue* getIndex(int pos);
    void changeIndex(int pos, const KeyValue* index);
    int getPointer(int pos);
    unsigned char* getData(int pos);

    void erase(int pos);
    void insertFirstNode(const KeyValue* index, const unsigned char* data, BPlusTree :: Iterator &ret);
    // For leaf.
    void insert(int pos, const KeyValue* index, const unsigned char* data);
    // For no leaf.
    void insert(int pos, const KeyValue* index, int pointer);
    // Split into 0 ~ pos; pos+1 ~ length-1. returns new page id.
    // After split, current page = new page.
    int split(int pos, int curPage);
    int getNextLeaf();
    void setNextLeaf(int id);
    int getPrevLeaf();
    void setPrevLeaf(int id);
    int createTree();
    void loadTree();
    void recyclePage();
    
private:
    FileOperation *fOperation;
    static unsigned char buf[9001];
    static const int NOLEAF_ADD_BYTES, LEAF_ADD_BYTES;
    int tid, indexLen, dataLen, rootPage, keyType;
    int alignedIndexLen, alignedDataLen;
    int noLeafMaxChNum, leafMaxChNum;
};

#endif
