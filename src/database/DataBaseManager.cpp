#include "DataBaseManager.h"

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <algorithm>

using namespace std;

DataBaseManager::DataBaseManager()
{
	int res = chdir(DBROOT);
	char root[100];
	getcwd(root, 100);
	_DBRootPath = string(root);

	ifstream fin(DBNAMEFILE);
	char DBname[100];
	//start as empty file, can run ok
	int num=0;
	fin>>num;
	for(int i=0; i<num; i++)
	{
		fin >> DBname;
		_DBlist.push_back(string(DBname));
	}
	fin.close();
	_currentDB.clear();

	_fileManager = new FileManager();
	_bufPageManager = new BufPageManager(_fileManager);
}
DataBaseManager::~DataBaseManager()
{
	closeCurrentDB();

	ofstream fout(DBNAMEFILE);
	fout << _DBlist.size() << endl;
	for(unsigned int i=0; i<_DBlist.size(); i++)
	{
		fout << _DBlist[i] << endl;
	}
	fout.close();
	_DBlist.clear();
	//cout<<"~DataBaseManager"<<endl;
}
string DataBaseManager::createDB(string DBname)
{
	vector<string>::iterator it = find(_DBlist.begin(), _DBlist.end(), DBname);
	if(it != _DBlist.end())
		return string("Error: The DataBase has already exist.\n");

	_DBlist.push_back(DBname);
	string dir = _DBRootPath + string("/") + DBname; 
	int status = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if(status == -1)
		return string("Error: Create DataBase " + DBname + " failed.\n");
	string tableListFile = dir + string("/") + string(TABLELISTFILE);
	ofstream fout(tableListFile.c_str());
	fout<<0<<endl;
	fout.close();
	return string("Create DataBase: " + DBname + " succeed.\n");
}
string DataBaseManager::dropDB(string DBname)
{
	// does dir exist
	if(_currentDB == DBname)
		closeCurrentDB();

	string dir = _DBRootPath + string("/") + DBname;
	////cout<<dir<<endl;
	DIR* Dir = opendir(dir.c_str());
	if(Dir == NULL)
		return string("Error: The DataBase does not exist.\n");
	//remove file	
	struct dirent *dirEntry = NULL;
    while((dirEntry = readdir(Dir)) != NULL)
    {
    	if(dirEntry->d_name[0] == '.')
    		continue;
    	string fileDir = dir + string("/") + string(dirEntry->d_name);
    	int res = remove(fileDir.c_str());
    	if(res == -1)
    		return string("Error: drop DataBase : " + DBname + " failed.\n");
    }    
    closedir(Dir);
    //remove dirctory
	int res = rmdir(dir.c_str());
	if(res == -1)
		return string("Error: drop DataBase: " + DBname + " failed.\n");	
	//remove from DBlist
	vector<string>::iterator it = find(_DBlist.begin(), _DBlist.end(), DBname);
	_DBlist.erase(it);
	return string("Drop DataBase: " + DBname + " succeed.\n");
}
string DataBaseManager::useDB(std::string DBname)
{
	// does dir exist
	vector<string>::iterator it = find(_DBlist.begin(), _DBlist.end(), DBname);
	if(it == _DBlist.end())
		return string("Error: The DataBase does not exist.\n");
	if(DBname == _currentDB)
		return string("Error: The DataBase is in use.\n");

	closeCurrentDB();
	
	//char currentpath[100];
	//getcwd(currentpath, 100);
	//cout<<currentpath<<endl;

	int res = chdir(DBname.c_str());
	//cout<<"chdir res:"<<' '<<res<<endl;
	
	//getcwd(currentpath, 100);
	//cout<<currentpath<<endl;

	_currentDB = DBname;
	ifstream fin(TABLELISTFILE);
	int num=0;
	char tableName[100];
	fin >> num;
	for(int i=0; i<num; i++)
	{
		fin >> tableName;
		string tname(tableName);
		_currentTableList.push_back(tname);

		char path[100];
		sprintf(path, "%s.table", tableName);
		//cout<<"tablepath"<<path<<endl;
		FileOperation* fileOp = new FileOperation(_fileManager, _bufPageManager, path);
		fileOp->openTable();
		RecordBuilder* builder = new RecordBuilder((char*)fileOp->getTableStructure());
		//init index 
		int cols = builder->getCols();
		for(int i=0; i<cols; i++)
		{
			BPlusTree* tree = fileOp->getTreeByColId(i);
			if(tree)
				builder->addIndex(i);
		}

		_map_file.insert(pair<string, FileOperation*>(tname, fileOp) );
		_map_record.insert(pair<string, RecordBuilder*>(tname, builder));
	}
	fin.close();

	return string("Use DataBase: " + DBname + " succeed.\n");
}
string DataBaseManager::getAllTable()
{
	// does dir exist
	//string dir = string(DBPATH) + DBname;
	if(_currentDB.empty())
		return string("Error: current DataBase is null.\n");

	if(_currentTableList.empty())
		return string("There are not any tables in current DataBase.\n");
	string tableList = "Tables in current DataBase:\n";
	for(unsigned int i=0; i<_currentTableList.size(); i++)
	{
		tableList += _currentTableList[i];
		tableList += string("\n");
	}
	return tableList;
}
string DataBaseManager::createTable(const char* tableName, vector<hsql::ColumnDefinition*>* columns, const char* primary_key)
{
	//cout<<"create table"<<columns->size()<<' '<<primary_key<<endl;
	if(_currentDB.empty())
		return string("Error: current DataBase is null.\n");
	
	vector<string>::iterator it = find(_currentTableList.begin(), _currentTableList.end(), string(tableName));
	if(it != _currentTableList.end())
		return string("Error: The table has already exist.\n");

	//check create valid
	bool find_key = false;
	for(unsigned int i=0; i<columns->size(); i++)
	{
		if(primary_key != NULL && strcmp((*columns)[i]->name, primary_key) == 0 )
			find_key = true;
		for(unsigned int j=0; j<i; j++)
		{
			if(strcmp((*columns)[j]->name, (*columns)[i]->name) == 0)
				return string("Error: create table failed -- two columns have same name.\n");///redundant name					
		}
	}
	if(primary_key != NULL && !find_key)
		return string("Error: create table failed -- cannot find primary key.\n");///not find key
	//cout<<"create vaild"<<endl;

	int format_length;
	int record_length;
	RecordBuilder* builder = new RecordBuilder();
	int key_index_len, key_index_type, key_index_col;
	char* format = builder->createFormat(tableName, columns, primary_key, format_length,
		 record_length, key_index_len, key_index_type, key_index_col);
	//cout<<format_length<<' '<<record_length<<endl;
	//cout<<"format end"<<endl;
	if(format == NULL)
	{
		////cout<<"format end1"<<endl;
		delete builder;
		return string("Error: create Table ") + string(tableName) + string(" failed.\n"); 
	}
	else
	{
		builder->initFormat(format);
		//cout<<builder->getTableMode()<<endl;

		string tname(tableName);
		char path[100];
		sprintf(path, "%s.table", tableName);
		FileOperation* fileOp = new FileOperation(_fileManager, _bufPageManager, path);
		fileOp->createTable((unsigned char*)format, format_length, record_length);
		//cout<<"create table"<<endl;
		//cout<<key_index_len<<' '<<key_index_type<<' '<<key_index_col<<endl;
		fileOp->createIndex(true, key_index_len, key_index_type, key_index_col);
		//cout<<"create index"<<endl;
		fileOp->openTable();
		//cout<<"openTable"<<endl;
		delete[] format;
		
		_currentTableList.push_back(tname);
		_map_file.insert(pair<string, FileOperation*>(tname, fileOp) );
		_map_record.insert(pair<string, RecordBuilder*>(tname, builder));
		return string("Create Table ") + tname + string(" succeed.\n"); 
	}
}

string DataBaseManager::dropTable(string tableName)
{
	if(_currentDB.empty())
		return string("Error: current DataBase is null.\n");

	vector<string>::iterator it = find(_currentTableList.begin(), _currentTableList.end(), tableName);
	if(it != _currentTableList.end())
	{
		_currentTableList.erase(it);
		FileOperation* fileOp = _map_file[tableName];
		fileOp->close();
		//cout<<"close"<<endl;
		delete fileOp;
		//cout<<"delete 1"<<endl;
		RecordBuilder* builder = _map_record[tableName];
		delete builder;
		//cout<<"delete 2"<<endl;
		_map_file.erase(tableName);
		_map_record.erase(tableName);
		//cout<<"erase"<<endl;

		string filePath = tableName + string(".table");
		if(remove(filePath.c_str()) != -1)
			return string("Drop table: ") + tableName + string(" succeed.\n");
	}
	else
		return string("Error: table " ) + tableName + string(" does not exist.\n");
}

string DataBaseManager::getTableMode(string tableName)
{
	if(_currentDB.empty())
		return string("Error: current DataBase is null.\n");
	
	vector<string>::iterator it = find(_currentTableList.begin(), _currentTableList.end(), tableName);
	if(it != _currentTableList.end())
	{
		RecordBuilder* builder = _map_record[tableName];
		string tableMode = "Table " + tableName + " info:\n";
		tableMode += builder->getTableMode();
		return tableMode;
	}
	else
		return string("Error: table " + tableName + " does not exist.\n");
}

FileOperation* DataBaseManager::getFileOperation(string tableName)
{
	return _map_file[tableName];
}

RecordBuilder* DataBaseManager::getRecordBuilder(string tableName)
{
	return _map_record[tableName];
}

void DataBaseManager::closeCurrentDB()
{
	if(!_currentDB.empty())
	{
		ofstream fout(TABLELISTFILE);
		fout<<_currentTableList.size()<<endl;
		for(unsigned int i=0; i<_currentTableList.size(); i++)
			fout<<_currentTableList[i].c_str()<<endl;
		fout.close();
		_currentTableList.clear();

		map<string, FileOperation*>::iterator it_file;
		map<string, RecordBuilder*>::iterator it_record; 
		for(it_file = _map_file.begin(); it_file != _map_file.end(); ++it_file)
		{
			it_file->second->close();
			delete it_file->second;
		}
		for(it_record = _map_record.begin(); it_record != _map_record.end(); ++it_record)
			delete it_record->second;
		_map_file.clear();
		_map_record.clear();
		_currentDB.clear();
		int res = chdir("..");
	}
}

bool DataBaseManager::checkSelect(vector<char*>* table_list)
{
	bool* used = new bool[_currentTableList.size()];
	for(unsigned int i=0; i<_currentTableList.size(); i++)
		used[i] = false;

	for(unsigned int i=0; i<table_list->size(); i++)
	{	
		bool find = false;
		for(unsigned int j=0; j<_currentTableList.size(); j++)
			if(string(table_list->at(i)) == _currentTableList[j])
			{
				if(used[j] == true)
					return false;
				else
					used[j] = true;
				find = true;
				break;
			}
		if(!find)
			return false;
	}
	delete[] used;
	return true;
}