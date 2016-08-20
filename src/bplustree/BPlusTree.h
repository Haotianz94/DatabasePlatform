#ifndef __BPLUSTREE__BPLUSTREE__H__
#define __BPLUSTREE__BPLUSTREE__H__

#include "KeyValue.h"

class FileOperation;
class FileAccesser;

class BPlusTree
{
public:
    // NO Overflow check.
    class Iterator
    {
    public:
        Iterator(FileAccesser *acc);
        Iterator(FileAccesser *acc, int pageId, int position);
        ~Iterator();

        unsigned char* operator *();
        bool operator == (const Iterator &b) const;
        bool operator != (const Iterator &b) const;
        Iterator& operator ++();

        // One MUST call markRead() function after changing any data of the record.
        void markRead();
        KeyValue* getKey();
        void toCharArray(unsigned char* res);
        static Iterator fromCharArray(BPlusTree* tree, unsigned char* p);

        friend class FileAccesser;
        friend class BPlusTree;

    private:
        FileAccesser *f;
        // pid = -1, pos = 0 : end
        int pid, pos;
    };

    BPlusTree(FileOperation *fileOperation, int indexLength, int dataLength, int treeId, int rootPageId, int keyType);
    ~BPlusTree();
    
    Iterator insert(KeyValue* index, unsigned char* data);
    void erase(const Iterator &iterator);
    
    enum FindMode
    {
        less, lessequal, equal, 
    };
    Iterator find(const KeyValue* index, FindMode mode);
    Iterator begin();
    Iterator end();
    
private:
    int indexLen, dataLen, rootPage, keyType;
    FileOperation *fileOpt;
    FileAccesser *fileAcc;
    
    // return range : -1 to size - 1.
    int findInNode(const KeyValue* index, FindMode mode);
    int findInNode(const KeyValue* index);
    
    bool _insert(int pageId, const KeyValue* index, unsigned char* data, Iterator &ret, int& splitedPointer, KeyValue*& splitedIndex);
    bool _erase(int pageId, const KeyValue* index);
    Iterator _find(int pageId, const KeyValue* index, FindMode mode);

};

#endif
