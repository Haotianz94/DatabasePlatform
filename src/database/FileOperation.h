#ifndef __FILEOPERATION__H__
#define __FILEOPERATION__H__

#include "../bufmanager/BufPageManager.h"
#include "../fileio/FileManager.h"
#include "../utils/pagedef.h"
#include "../bplustree/BPlusTree.h"
#include "../bplustree/KeyValue.h"
#include "../bplustree/IntegerKeyValue.h"

#include <vector>
#include <map>

class FileOperation
{
public:
    FileOperation(FileManager *fManager, BufPageManager *bufManager, char *path);
    
    bool openTable();
    bool createTable(unsigned char *tableStructure, int tableStructureLength, int recordLength);
    void close();
    
    ~FileOperation();

    unsigned char* getTableStructure();
    // Get the b+-tree pointer by its ID. 
    BPlusTree *getTreeByColId(int id);
    // Create an index; returns the b+-tree ID.
    BPlusTree *createIndex(bool isMainIndex, int indexLen, int keyType, int colId);
    // Current page <- page 0.
    void changeRootpageById(int treeId, int rootPage);

    // Only for B+ tree access.
    void markRead();
    // Current page <- created page.
    int createPage(int kind, int spcBytes, int recordLength, unsigned char *spc = NULL, int initRecordsAmount = 0);
    void toPage(int pageIndex);
    int getKind();
    int getRecordsAmount();
    void setRecordsAmount(int amount);
    unsigned char* getIthRecord(int i);
    unsigned char* getSpcField();
    int getMaxRecordNum();
    // Moving records after pos to insert a record in pos.
    void insert(int pos, unsigned char* record);
    // Remove the pos-th record.
    void remove(int pos);

private:
    const static int DATAPAGE_OFFSET, RECORD_POINTER_LEN;

    FileManager *fileManager;
    BufPageManager *bufPageManager;

    char *fileName;
    bool isOpened;
    int fileId;
    int indexAmount, recordLength, pageAmount;

    static unsigned char buf[PAGE_SIZE + 10];
    int curIndex, curPageId;
    unsigned char *curPageData;
    std::vector <BPlusTree*> trees;
    std::map <int, int> col2tid;

    inline int twobytes(unsigned char a, unsigned char b);
    // Current page <- page 0
    void changePageAmount(int newPageAmount);
};

#endif
