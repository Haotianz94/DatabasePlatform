#ifndef __DATABASEMANAGER__H__
#define __DATABASEMANAGER__H__

#include "RecordBuilder.h"
#include "FileOperation.h"
#include <vector>
#include <map>

#define DBROOT "DataBaseRoot"
#define DBNAMEFILE "DBNameList.txt"
#define TABLELISTFILE "tableList.txt"

class DataBaseManager
{
private:
	std::vector<std::string> _DBlist;
	std::string _currentDB;
	std::string _DBRootPath;

	std::vector<string> _currentTableList;
	std::map<string, FileOperation*> _map_file;
	std::map<string, RecordBuilder*> _map_record;  
	
	FileManager* _fileManager;
	BufPageManager* _bufPageManager;

	void closeCurrentDB();

public:
	DataBaseManager();
	~DataBaseManager();
	std::string createDB(std::string DBname);
	std::string dropDB(std::string DBname);
	std::string useDB(std::string DBname);
	std::string getAllTable();
	std::string createTable(const char* tableName, std::vector<hsql::ColumnDefinition*>* columns, const char* primary_key);
	std::string dropTable(std::string tableName);
	std::string getTableMode(std::string tableName);
	FileOperation* getFileOperation(std::string tableName);
	RecordBuilder* getRecordBuilder(std::string tableName);
	FileManager* getFileManager() { return _fileManager; }
	BufPageManager* getBufPageManager() { return _bufPageManager; }
	bool checkSelect(std::vector<char*>* table_list);
};

#endif