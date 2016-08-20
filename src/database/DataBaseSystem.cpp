#include "DataBaseSystem.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace hsql;

DataBaseSystem::DataBaseSystem()
{
	dbManager = new DataBaseManager();
	cout<<"Welcome to our Database Platform!"<<endl;	
}

DataBaseSystem::~DataBaseSystem()
{
	delete dbManager;
}
string DataBaseSystem::readSQLfile(const char* filename)
{
	ifstream fin(filename);
	int sum = 0;
	string text;
	while(!fin.eof())
	{
		char stmt[500];
		fin.getline(stmt, 500);
		text += string(stmt);	
	}
	//cout<<text;
	SQLStatementList* stmt_list = SQLParser::parseSQLString(text);
	if(!stmt_list->isValid)
		return string("Error: invaild SQL file.\n");
	else
	{
		string res;
		int num = stmt_list->numStatements();
		cout<<num<<endl;
		for(int i=0; i<num; i++)
			res += processSQLstmt(stmt_list->getStatement(i));
		return res;
	}
}
string DataBaseSystem::readSQLstmt(string sqlStmt)
{
	SQLStatementList* stmt_list = SQLParser::parseSQLString(sqlStmt);
	if(!stmt_list->isValid)
		return string("Error: invaild SQL statement.\n");
	else
	{
		string res;
		int num = stmt_list->numStatements();
		//cout<<num<<endl;
		for(int i=0; i<num; i++)
			res += processSQLstmt(stmt_list->getStatement(i));
		return res;
	}
}
string DataBaseSystem::processSQLstmt(SQLStatement* statement)
{
	if(statement->type() == kStmtCreateDB)
	{
		CreateDBStatement* stmt = (CreateDBStatement*) statement;
		////cout<<stmt->DBname<<endl;
		return dbManager->createDB(string(stmt->DBname));
	}
	else if(statement->type() == kStmtDropDB)
	{
		DropDBStatement* stmt = (DropDBStatement*) statement;
		////cout<<stmt->DBname<<endl;
		return dbManager->dropDB(string(stmt->DBname));
	}
	else if(statement->type() == kStmtUseDB)
	{
		UseDBStatement* stmt = (UseDBStatement*) statement;
		////cout<<stmt->DBname<<endl;
		return dbManager->useDB(string(stmt->DBname));
	}
	else if(statement->type() == kStmtShowTable)
	{
		return dbManager->getAllTable();
	}
	else if(statement->type() == kStmtCreate)
	{
		CreateStatement* stmt = (CreateStatement*) statement;
		return dbManager->createTable(stmt->table_name, stmt->columns, stmt->primary_key);
	}
	else if(statement->type() == kStmtDrop)
	{
		DropStatement* stmt = (DropStatement*) statement;
		return dbManager->dropTable(string(stmt->table_name));
	}
	else if(statement->type() == kStmtDesc)
	{
		DescStatement* stmt = (DescStatement*) statement;
		
		/*//cout<<"All records:"<<endl;
		FileOperation* fileOp = dbManager->getFileOperation(string(stmt->table_name));
		RecordBuilder* builder = dbManager->getRecordBuilder(string(stmt->table_name));

		int pkid = builder->getPKId();
		BPlusTree* tree;
		if(pkid != -1)
			tree = fileOp->getTreeByColId(pkid);
		else
			tree = fileOp->getTreeByColId(0);
		int sum = 0;
		for(BPlusTree::Iterator it = tree->begin(); it != tree->end(); ++it)
		{
			//cout<<"Record "<<++sum<<" :"<<endl;
			builder->showRecord((char*)*it);
		}
		//cout<<"All records end"<<endl;*/

		return dbManager->getTableMode(string(stmt->table_name));
	}
	else if(statement->type() == kStmtInsert)
	{
		InsertStatement* stmt = (InsertStatement*) statement;
		FileOperation* fileOp = dbManager->getFileOperation(string(stmt->table_name));
		RecordBuilder* builder = dbManager->getRecordBuilder(string(stmt->table_name));
		
		string res;
		for(unsigned int i=0; i<stmt->value_list->size(); i++)
		{
			vector<Expr*>* values = stmt->value_list->at(i);

			char* record;
			RecordBuilder::Error errorCode;
			int errorKey;
			if(stmt->keys == NULL)
			{
				//cout<<"insert 1"<<endl;
				int cols = builder->getCols();
				if(values->size() != cols)
					res += string("Error: insert failed.\n");///more detail
				record = builder->formatRecord(values, errorCode, errorKey);
			}
			else
			{
				//cout<<"insert 2"<<endl;
				int cols = builder->getCols();
				if(stmt->keys->size() != values->size())
					res += string("Error: insert failed.\n");///more deatil
				if(stmt->keys->size() > cols)
					res += string("Error: insert failed.\n");///more detail
				record = builder->formatRecord(stmt->keys, values, errorCode, errorKey);
			}

			KeyValue* key;
			BPlusTree* tree;
			if(record != NULL)
			{
				int pkid = builder->getPKId();
				if(pkid == -1)
				{
					key = builder->getIndexVal(record, 0);
					tree = fileOp->getTreeByColId(0);
					tree->insert(key, (unsigned char*)record);
					res += string("insert into ") + string(stmt->table_name) + " succeed.\n";
				}
				else
				{
					key = builder->getIndexVal(record, pkid);
					tree = fileOp->getTreeByColId(pkid);
					BPlusTree::Iterator found = tree->find(key, BPlusTree::equal);
					if(found != tree->end())
						res += string("Error: the primary key has already exist.\n");
					else
					{
						tree->insert(key, (unsigned char*)record);
						res += string("insert into ") + string(stmt->table_name) + " succeed.\n";
					}
				}
				delete[] record;
			}
			else
			{
				switch (errorCode)
				{
					case RecordBuilder::NOTINT:
						res += string("Error: the element inserted is not INT type.\n");
						break;
					case RecordBuilder::NOTDOUBLE:
						res += string("Error: the element inserted is not DOUBLE type.\n");
						break;
					case RecordBuilder::NOTSTRING:
						res += string("Error: the element inserted is not STRING type.\n");
						break;
					case RecordBuilder::OVERLENGTH:
						res += string("Error: the string inserted is too long.\n");
						break;
					case RecordBuilder::ISNULL:
						res += string("Error: the element inserted can not be null.\n");
						break;
					case RecordBuilder::BADKEY:
						res += string("Error: can not find the key name.\n");
						break;
					case RecordBuilder::REDUNDENT:
						res += string("Error: the key name are the same.\n");
						break;
					default:
						res += string("Error: insert failed.\n");
				}
			}
		}
		return res;
	}
	else if(statement->type() == kStmtUpdate)
	{
		UpdateStatement* stmt = (UpdateStatement*) statement;
		FileOperation* fileOp = dbManager->getFileOperation(string(stmt->table_name));
		RecordBuilder* builder = dbManager->getRecordBuilder(string(stmt->table_name));

		if(!builder->checkUpdate(stmt->updates))
			return string("Error: invaild update clauses.\n");

		int pkid = builder->getPKId();
		BPlusTree* tree;
		if(pkid != -1)
			tree = fileOp->getTreeByColId(pkid);
		else
			tree = fileOp->getTreeByColId(0);
		if(pkid == -1)
		{
			BPlusTree::Iterator prev = NULL;
			BPlusTree::Iterator cur = tree->begin();
			vector<char*> updated;
			int length = builder->getRecordLength();
			while(cur != tree->end())
			{
				if(builder->match((char*)*cur, stmt->where))
				{
					char* record = new char[length+1];
					for(int i=0; i<length; i++)
						record[i] = ((char*)*cur)[i];
					if(builder->updateRecord(record, stmt->updates))
					{
						updated.push_back(record);
						tree->erase(cur);
						if(prev == NULL)
							cur = tree->begin();
						else
						{
							cur = prev;
							++cur;
						}
					}
					else
						delete[] record;
				}
				else
				{
					prev = cur;
					++cur;
				}
			}
			for(unsigned int i=0; i<updated.size(); i++)
			{
				tree->insert(builder->getIndexVal(updated[i], 0), (unsigned char*)updated[i]);
				delete[] updated[i];
			}

			char str[100];
			sprintf(str, "Update %d from table %s\n", updated.size(), stmt->table_name);
			return string(str);
		}
		else
		{
			string res = "Error: can not find a record matches where clause.\n";
			vector<char*> updating;
			vector<char*> updated;
			int pkid = builder->getPKId();
			vector<KeyValue*> updated_pkval;
			int length = builder->getRecordLength();

			BPlusTree::Iterator prev = NULL;
			BPlusTree::Iterator cur = tree->begin();
			while(cur != tree->end())
			{
				if(builder->match((char*)*cur, stmt->where))
				{
					char* record1 = new char[length+1];
					char* record2 = new char[length+1];
					char* iter = (char*)*cur;
					for(int i=0; i<length; i++)
						record1[i] =  record2[i] = iter[i];
					updating.push_back(record1);
					updated.push_back(record2);
					tree->erase(cur);
					if(prev == NULL)
						cur = tree->begin();
					else
					{
						cur = prev;
						++cur;
					}
				}
				else
				{
					prev = cur;
					++cur;
				}
			}
			if(updating.empty())
				return res;
			bool update_succ = true;
			for(unsigned int i=0; i<updated.size(); i++)
			{
				if(!builder->updateRecord(updated.at(i), stmt->updates))
				{
					update_succ = false;
					res = string("Error: invalid update clauses.\n");
					break;
				}
			}
			if(update_succ)
			{
				for(unsigned int i=0; i<updated.size(); i++)
				{
					KeyValue* pkval =  builder->getIndexVal(updated.at(i), pkid);
					for(int j=0; j<i; j++)
						if(pkval->compare(updated_pkval.at(j)) == 0)
						{
							update_succ = false;
							res = string("Error: the primary key has already exist.\n");
							break;
						}
					updated_pkval.push_back(pkval);
				}
			}
			if(update_succ)
			{
				for(unsigned int i=0; i<updated_pkval.size(); i++)
				{
					BPlusTree::Iterator found = tree->find(updated_pkval.at(i), BPlusTree::equal);
					if(found != tree->end())
					{
						update_succ = false;
						res = string("Error: the primary key has already exist.\n");
						break;
					}
				}
			}
			if(update_succ)
			{
				for(unsigned int i=0; i<updated.size(); i++)
					tree->insert(updated_pkval.at(i), (unsigned char*)updated.at(i));
			}
			else
			{
				for(unsigned int i=0; i<updating.size(); i++)
					tree->insert(builder->getIndexVal(updating.at(i), pkid), (unsigned char*)updating.at(i));
			}
			for(unsigned int i=0; i<updating.size(); i++)
			{
				delete[] updating.at(i);
				delete[] updated.at(i);
			}
			if(update_succ)
			{
				char str[100];
				sprintf(str, "Update %d from table %s\n", updated.size(), stmt->table_name);
				return string(str);
			}
			else
				//return string("Error: update table ") + string(stmt->table_name) + string(" failed.\n");
				return res;
		}
	}
	else if(statement->type() == kStmtDelete)
	{
		DeleteStatement* stmt = (DeleteStatement*) statement;
		FileOperation* fileOp = dbManager->getFileOperation(string(stmt->table_name));
		RecordBuilder* builder = dbManager->getRecordBuilder(string(stmt->table_name));

		int pkid = builder->getPKId();
		BPlusTree* tree;
		if(pkid != -1)
			tree = fileOp->getTreeByColId(pkid);
		else
			tree = fileOp->getTreeByColId(0);
		int sum = 0;
		BPlusTree::Iterator prev = NULL;
		BPlusTree::Iterator cur = tree->begin();
		while(cur != tree->end())
		{
			if(builder->match((char*)*cur, stmt->expr))
			{
				sum++;
				tree->erase(cur);
				if(prev == NULL)
					cur = tree->begin();
				else
				{
					cur = prev;
					++cur;
				}
			}
			else
			{
				prev = cur;
				++cur;
			}
		}

		char str[100];
		sprintf(str, "Delete %d from table %s\n", sum, stmt->table_name);
		return string(str);
	}
	else if(statement->type() == kStmtSelect)
	{
		SelectStatement* stmt = (SelectStatement*) statement;

		if(!dbManager->checkSelect(stmt->table_list))
			return string("Error: invaild select from clause.\n");

		string divide = string("--------------------------------\n");
		if(stmt->table_list->size() == 1)
		{
			FileOperation* fileOp = dbManager->getFileOperation(string(stmt->table_list->at(0)));
			RecordBuilder* builder = dbManager->getRecordBuilder(string(stmt->table_list->at(0)));
			if(!builder->checkSelect(stmt->select_list))
				return string("Error: invaild select clauses.\n");

			vector<SelectOpt>* select_opt = builder->getSelectOpt(stmt->select_list);
			if(select_opt == NULL)
				return string("Error: invaild select clauses.\n");
			//SelectOpt selopt = select_opt->at(0);				
			//cout<<selopt.colId<<' '<<selopt.val<<' '<<selopt.opt<<endl;
			BPlusTree* tree;
			int pkid = builder->getPKId();
			if(pkid == -1)
				tree = fileOp->getTreeByColId(0);
			else
				tree = fileOp->getTreeByColId(pkid);
			string res = "Select results:\n";
			res += divide;
			int num = 0;
			for(BPlusTree::Iterator it = tree->begin(); it != tree->end(); ++it)
			{
				if(builder->match((char*)*it, stmt->where_expr))
				{
					res += builder->showRecord((char*)*it, stmt->select_list);
					//res += divide;
					num ++;
					//cout<<"bbb"<<endl;
					for(unsigned int i=0; i<select_opt->size(); i++)
					{
						SelectOpt& selopt = select_opt->at(i);
						//cout<<selopt.colId<<' '<<selopt.val<<' '<<selopt.opt<<endl;
						double val = builder->getSelectVal((char*)*it, selopt.colId);
						//cout<<val<<endl;
						//cout<<"aaa"<<endl;
						if(selopt.opt == SelectOpt::SUM || selopt.opt == SelectOpt::AVG)
						{
							selopt.val += val;
						}
						else if(selopt.opt == SelectOpt::MAX)
						{
							if(selopt.val < val)
								selopt.val = val;
						}
						else if(selopt.opt == SelectOpt::MIN)
						{
							if(selopt.val > val)
								selopt.val = val;
						}
					} 
				}
			}
			//cout<<"bbb"<<endl;
			if(!select_opt->empty())
			{
				for(unsigned int i=0; i<select_opt->size(); i++)
				{
					SelectOpt& selopt = select_opt->at(i);
					//cout<<selopt.val<<endl;
					char r[100];
					if(selopt.type == ColumnDefinition::INT)
					{
						if(selopt.opt == SelectOpt::SUM)
							sprintf(r, "SUM(%s) : %ld\n", selopt.colName.c_str(), (int64_t)selopt.val);
						else if(selopt.opt == SelectOpt::AVG)
							sprintf(r, "AVG(%s) : %f\n", selopt.colName.c_str(), selopt.val/num);
						else if(selopt.opt == SelectOpt::MAX)
							sprintf(r, "MAX(%s) : %ld\n", selopt.colName.c_str(), (int64_t)selopt.val);
						else 
							sprintf(r, "MIN(%s) : %ld\n", selopt.colName.c_str(), (int64_t)selopt.val);
					}
					else
					{	
						if(selopt.opt == SelectOpt::SUM)
							sprintf(r, "SUM(%s) : %f\n", selopt.colName.c_str(), selopt.val);
						else if(selopt.opt == SelectOpt::AVG)
							sprintf(r, "AVG(%s) : %f\n", selopt.colName.c_str(), selopt.val/num);
						else if(selopt.opt == SelectOpt::MAX)
							sprintf(r, "MAX(%s) : %f\n", selopt.colName.c_str(), selopt.val);
						else 
							sprintf(r, "MIN(%s) : %f\n", selopt.colName.c_str(), selopt.val);
					}
					res += string(r);
				}
				res += divide;
			}
			char r[200];
			sprintf(r, "Totally Select %d results.\n", num);
			res += string(r);
			return res;		
		}
		else
		{
			RecordBuilder* tmpBuilder = new RecordBuilder();
			//FileOperation* tmpFileOp;
			//int record_length, key_index_len, key_index_type, key_index_col;
			for(unsigned int i=0; i<stmt->table_list->size(); i++)
			{
				char* format = (char*)dbManager->getFileOperation(string(stmt->table_list->at(i)))->getTableStructure();
				tmpBuilder->addFormat(format);
			}
			if(!tmpBuilder->checkSelect(stmt->select_list))
				return string("Error: invaild select clauses.\n");

			delete tmpBuilder;

			/*char path[] = "tmp.table";
			char format[] = "This is a tmp file";
			tmpFileOp = new FileOperation(dbManager->getFileManager(), dbManager->getBufPageManager(), path);
			tmpFileOp->createTable((unsigned char*)format, strlen(format), record_length);
			tmpFileOp->createIndex(true, key_index_len, key_index_type, key_index_col);
			tmpFileOp->openTable();*/

			vector<char*> connectA;
			vector<char*> connectB;
			int lengthA, lengthB, colsA, colsB;
			
			RecordBuilder * builder = dbManager->getRecordBuilder(string(stmt->table_list->at(0)));
			lengthA = builder->getRecordLength();
			colsA = builder->getCols();
			selectRecord(connectA, stmt->table_list->at(0), stmt->where_expr);
			tmpBuilder = new RecordBuilder();
			char* format = (char*)dbManager->getFileOperation(string(stmt->table_list->at(0)))->getTableStructure();
			tmpBuilder->addFormat(format);
			for(unsigned int i=1; i<stmt->table_list->size(); i++)
			{
				char* format = (char*)dbManager->getFileOperation(string(stmt->table_list->at(i)))->getTableStructure();
				tmpBuilder->addFormat(format);
				selectRecord(connectB, stmt->table_list->at(i), stmt->where_expr);
				builder = dbManager->getRecordBuilder(string(stmt->table_list->at(i)));
				lengthB = builder->getRecordLength();
				colsB = builder->getCols();
				connnectRecord(connectA, connectB, lengthA, colsA, lengthB, colsB, stmt->where_expr, tmpBuilder);
			}
			//int pkid = tmpBuilder->getPKId();
			//cout<<"pkid "<<pkid<<endl;
			//if(pkid == -1)
			//	pkid = 0;
			//BPlusTree* tree = tmpFileOp->getTreeByColId(pkid);
			//if(tree == NULL)
			//	return string("Select Failed\n");
			/*for(unsigned int i=0; i<connectA.size(); i++)
			{
				char* record = connectA[i];
				KeyValue* key = tmpBuilder->getIndexVal(record, pkid);
				tree->insert(key, (unsigned char*)record);
				delete[] record;
			}*/
			//cout<<"insert end"<<endl;
			string res = "Select results:\n";
			res += divide;
			for(unsigned int i=0; i<connectA.size(); i++)
			{
				//if(tmpBuilder->match((char*)*it, stmt->where_expr))
				//{
					res += tmpBuilder->showRecord(connectA[i], stmt->select_list);
					delete[] connectA[i];
					//res += divide;
				//}
			}
			//remove("tmp.table");
			char r[200];
			sprintf(r, "Totally Select %d results.\n", connectA.size());
			res += string(r);
			return res;	
		}
	}
	else if(statement->type() == kStmtCreateIndex)
	{
		CreateIndexStatement* stmt = (CreateIndexStatement*) statement;
		FileOperation* fileOp = dbManager->getFileOperation(string(stmt->table));
		RecordBuilder* builder = dbManager->getRecordBuilder(string(stmt->table));
		if(builder->addIndex(stmt->column))
		{
			char res[100];
			sprintf(res, "Create Index: %s for %s succeed.\n", stmt->column, stmt->table);
			return string(res);
		}
		else
		{
			char res[100];
			sprintf(res, "Error: create Index: %s for %s failed.\n", stmt->column, stmt->table);
			return string(res);
		}
	}
	else if(statement->type() == kStmtDropIndex)
	{
		DropIndexStatement* stmt = (DropIndexStatement*) statement;
		FileOperation* fileOp = dbManager->getFileOperation(string(stmt->table));
		RecordBuilder* builder = dbManager->getRecordBuilder(string(stmt->table));
		if(builder->dropIndex(stmt->column))
		{
			char res[100];
			sprintf(res, "Drop Index: %s for %s succeed.\n", stmt->column, stmt->table);
			return string(res);
		}
		else
		{
			char res[100];
			sprintf(res, "Error: drop Index: %s for %s failed.\n", stmt->column, stmt->table);
			return string(res);	
		}
	}
	return string("Error: undefined SQL statment.\n");
}
void DataBaseSystem::selectRecord(vector<char*>& connect, const char* table_name, Expr* where_expr)
{
	//cout<<"selectRecord "<<endl;
	if(!connect.empty())
	{
		for(unsigned int i=0; i<connect.size(); i++)
			delete[] connect[i];
		connect.clear();
	}

	FileOperation* fileOp = dbManager->getFileOperation(string(table_name));
	RecordBuilder* builder = dbManager->getRecordBuilder(string(table_name));
	int pkid = builder->getPKId();
	if(pkid == -1)
		pkid = 0;
	BPlusTree* tree = fileOp->getTreeByColId(pkid);
	int length = builder->getRecordLength();

	builder->setIgnore(true);
	int sum=0, num=0;
	for(BPlusTree::Iterator it=tree->begin(); it != tree->end(); ++it)
	{
		if(builder->match((char*)*it, where_expr))
		{
			char* record = new char[length+1];
			char* iter = (char*)*it;
			for(int j=0; j<length; j++)
				record[j] = iter[j];
			connect.push_back(record);
			num++;
		}
		sum++;
	}
	//cout<<"sum"<<sum<<' '<<"num"<<num<<endl;
	builder->setIgnore(false);
	//cout<<"selectRecord "<<length<<endl;
}
void DataBaseSystem::connnectRecord(vector<char*>& connectA, vector<char*>& connectB, int& lengthA,
	 int& colsA, int lengthB, int colsB, Expr* where_expr, RecordBuilder* tmpBuilder)
{
	//cout<<"connnectRecord "<<lengthA<<' '<<colsA<<' '<<lengthB<<' '<<colsB<<endl;
	int dataA = lengthA - colsA;
	int dataB = lengthB - colsB;
	vector<char*> connected;
	for(unsigned int i=0; i<connectA.size(); i++)
	{
		//cout<<i<<endl;
		for(unsigned int j=0; j<connectB.size(); j++)
		{
			int cur = 0;
			char* record = new char[lengthA+lengthB+1];
			for(int k=0; k<dataA; k++)
				record[k] = connectA[i][k];
			cur += dataA;
			for(int k=0; k<dataB; k++)
				record[cur+k] = connectB[j][k];
			cur += dataB;
			for(int k=0; k<colsA; k++)
				record[cur+k] = connectA[i][dataA+k];
			cur += colsA;
			for(int k=0; k<colsB; k++)
				record[cur+k] = connectB[j][dataB+k];

			if(tmpBuilder->match(record, where_expr))
				connected.push_back(record);
			else
				delete[] record;
		}
		delete[] connectA[i];
	}

	for(unsigned int i=0; i<connectB.size(); i++)
		delete[] connectB[i];
	connectA.clear();
	connectB.clear();
	connectA = connected;
	lengthA += lengthB;
	colsA += colsB;
	//cout<<"connnectRecord end"<<lengthA<<' '<<colsA<<endl;
}