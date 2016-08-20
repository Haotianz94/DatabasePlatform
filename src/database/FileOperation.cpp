#include <cstring>
#include <cstdlib>
#include <vector>
#include "../bufmanager/BufPageManager.h"
#include "../fileio/FileManager.h"
#include "../utils/pagedef.h"
#include "../utils/FileStructureUtil.h"
#include "../bplustree/BPlusTree.h"
#include "FileOperation.h"

using namespace std;

// page 0
//  0 - 1    bytes: length per record
//  2 - 2    byte : amount of indexes
//  4 - 6    bytes: amount of all pages
//  8 - 1023 bytes: index information
//  3 bytes for root page index
//  1 byte for column id
//  2 bytes for key size
//  1 byte = 0: not main index
//         = 1: main index
//  1 byte = key type
// 1024 - 4095 bytes: record structure

// page 1 ~ 
// byte 0: kind of this page.
// byte 1 ~ 2: amount of records.
// byte 3: special contents bytes.
// byte 4 ~ 5: length per record.
// byte 6 ~ 7: empty.
// byte 8 ~ : special contents (e.g. pointer to the minimum leaf for B+-tree.)
// following: Records. Sorted by index (not the work of this file.). 
//            No spaces between two records.

unsigned char FileOperation :: buf[PAGE_SIZE + 10];
const int FileOperation :: DATAPAGE_OFFSET = 8;
const int FileOperation :: RECORD_POINTER_LEN = 8;
// 4 bytes page index (3 bytes used) + 4 bytes offset (2 bytes used).

FileOperation :: FileOperation(FileManager *fManager, BufPageManager *bufManager, char *path)
    : fileManager(fManager),
      bufPageManager(bufManager),
      fileName(path),
      isOpened(false),
      indexAmount(0),
      recordLength(0), 
      pageAmount(0)
{}

bool FileOperation :: openTable()
{
    if (isOpened)
        return false;
    isOpened = fileManager->openFile(fileName, fileId);
    if (!isOpened)
        return false;
    
    toPage(0);
    unsigned char *b = curPageData;
    recordLength = twobytes(b[0], b[1]);
    indexAmount = b[2];
    pageAmount = (((b[4] << 8) | b[5]) << 8) | b[6];
    
    b = b + 8;
    for (int i = 0; i < indexAmount; ++i, b += 8)
    {
        int rootPage = (((b[0] << 8) | b[1]) << 8) | b[2];
        int indexLen = (b[4] << 8) | b[5], isMainIndex = b[6];
        if (isMainIndex)
            trees.push_back(new BPlusTree(this, indexLen, recordLength, i, rootPage, b[7]));
        else
            trees.push_back(new BPlusTree(this, indexLen, RECORD_POINTER_LEN, i, rootPage, b[7]));
        col2tid[b[3]] = i;
    }
    return true;
}

FileOperation :: ~FileOperation()
{
    bufPageManager->close();
    fileManager->closeFile(fileId);
}

bool FileOperation :: createTable(unsigned char *tableStructure, int tableStructureLength, int recordLength)
{
    if (tableStructureLength > 3000)
    {
        printf("An Error occurred when creating a table: record length too long ( > 3000 bytes).");
        exit(0);
    }
    if (isOpened)
        return false;
    if (!fileManager->createFile(fileName))
        return false;
    isOpened = fileManager->openFile(fileName, fileId);
    if (!isOpened)
        return false;

    this->recordLength = recordLength;
    this->pageAmount = 1;

    toPage(0);
    unsigned char *b = curPageData;
    b[0] = recordLength >> 8;
    b[1] = recordLength & 255;
    memset(b + 2, 0, 6);
    b[6] = 1;
    memcpy(b + 1024, tableStructure, tableStructureLength);
    markRead();
    return true;
}

void FileOperation :: close()
{
    bufPageManager->close();
    fileManager->closeFile(fileId);
}

unsigned char* FileOperation :: getTableStructure()
{
    toPage(0);
    return curPageData + 1024;
}

BPlusTree* FileOperation :: getTreeByColId(int id)
{
    if (col2tid.count(id) > 0)
        return trees[col2tid[id]];
    return NULL;
}

BPlusTree* FileOperation :: createIndex(bool isMainIndex, int indexLen, int keyType, int colId)
{
    toPage(0);
    curPageData[2] = ++indexAmount;
    unsigned char *b = curPageData + 8 + (indexAmount - 1) * 8;
    b[3] = colId;
    b[4] = indexLen >> 8;
    b[5] = indexLen & 255;
    b[7] = keyType;
    if (isMainIndex)
    {
        b[6] = 1;
        trees.push_back(new BPlusTree(this, indexLen, recordLength, indexAmount - 1, -1, keyType));
    }
    else
    {
        b[6] = 0;
        trees.push_back(new BPlusTree(this, indexLen, RECORD_POINTER_LEN, indexAmount - 1, -1, keyType));
    }
    col2tid[colId] = indexAmount - 1;
    markRead();
    return trees[indexAmount - 1];
}

void FileOperation :: changeRootpageById(int treeId, int rootPage)
{
    toPage(0);
    unsigned char *b = curPageData + 8 + treeId * 8;
    int2tribytes(rootPage, b);
    markRead();
}

void FileOperation :: markRead()
{
    bufPageManager->markDirty(curIndex);
}

void FileOperation :: changePageAmount(int newPageAmount)
{
    toPage(0);
    pageAmount = newPageAmount;
    int2tribytes(pageAmount, curPageData + 4);
    markRead();
}

int FileOperation :: createPage(int kind, int spcBytes, int recordLength, unsigned char *spc, int initRecordsAmount)
{
    changePageAmount(pageAmount + 1);
    curPageData = (unsigned char*)bufPageManager->getPage(fileId, pageAmount - 1, curIndex);
    curPageData[0] = (unsigned char)kind;
    curPageData[1] = initRecordsAmount >> 8;
    curPageData[2] = initRecordsAmount & 255;
    curPageData[3] = (unsigned char)spcBytes;
    curPageData[4] = recordLength >> 8;
    curPageData[5] = recordLength & 255;
    if (spc != NULL)
        memcpy(curPageData + DATAPAGE_OFFSET, spc, spcBytes);
    else
        memset(curPageData + DATAPAGE_OFFSET, 0, spcBytes);
    bufPageManager->access(curIndex);
    bufPageManager->markDirty(curIndex);
    return pageAmount - 1;
}

void FileOperation :: toPage(int pageIndex)
{
    curPageData = (unsigned char*)bufPageManager->getPage(fileId, pageIndex, curIndex);
    bufPageManager->access(curIndex);
}

int FileOperation :: getKind()
{
    return curPageData[0];
}

int FileOperation :: getRecordsAmount()
{
    return twobytes(curPageData[1], curPageData[2]);
}

void FileOperation :: setRecordsAmount(int amount)
{
    curPageData[1] = amount >> 8;
    curPageData[2] = amount & 255;
    markRead();
}

unsigned char* FileOperation :: getIthRecord(int i)
{
    return curPageData + DATAPAGE_OFFSET + curPageData[3] +
        i * twobytes(curPageData[4], curPageData[5]);
}

unsigned char* FileOperation :: getSpcField()
{
    return curPageData + DATAPAGE_OFFSET;
}

int FileOperation :: twobytes(unsigned char a, unsigned char b)
{
    return (a << 8) + b;
}

int FileOperation :: getMaxRecordNum()
{
    return (PAGE_SIZE - DATAPAGE_OFFSET - curPageData[3]) / twobytes(curPageData[4], curPageData[5]);
}

void FileOperation :: insert(int pos, unsigned char* record)
{
    bufPageManager->access(curIndex);
    int recordLength = twobytes(curPageData[4], curPageData[5]);
    int offset = DATAPAGE_OFFSET + curPageData[3] + pos * recordLength;
    int copyLength = (getRecordsAmount() - pos) * recordLength;

    memcpy(buf, curPageData + offset, copyLength);
    memcpy(curPageData + offset, record, recordLength);
    memcpy(curPageData + offset + recordLength, buf, copyLength);

    if (curPageData[2] == 255)
    {
        ++curPageData[1];
        curPageData[2] = 0;
    }
    else
        curPageData[2]++;

    bufPageManager->markDirty(curIndex);
}

void FileOperation :: remove(int pos)
{
    bufPageManager->access(curIndex);
    int recordLength = twobytes(curPageData[4], curPageData[5]);
    int offset = DATAPAGE_OFFSET + curPageData[3] + pos * recordLength;
    int copyLength = (getRecordsAmount() - pos - 1) * recordLength;

    memcpy(buf, curPageData + offset + recordLength, copyLength);
    memcpy(curPageData + offset, buf, copyLength);

    if (curPageData[2] == 0)
    {
        --curPageData[1];
        curPageData[2] = 255;
    }
    else
        curPageData[2]--;
    
    bufPageManager->markDirty(curIndex);
}
