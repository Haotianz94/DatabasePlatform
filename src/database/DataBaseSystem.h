#ifndef __DATABASESYSTEM__H__
#define __DATABASESYSTEM__H__

#include "SQLParser.h"
#include "DataBaseManager.h"

class DataBaseSystem
{
private:
	DataBaseManager* dbManager;
	//hsql::SQLStatementList* stmt_list;

public:
	DataBaseSystem();
	~DataBaseSystem();
	//void readsqlFile(const char* filename);
	std::string processSQLstmt(hsql::SQLStatement* statement);
	std::string readSQLfile(const char* filename);
	std::string readSQLstmt(std::string sqlStmt);
	void selectRecord(std::vector<char*>& connect, const char* table_name, hsql::Expr* where_expr);
	void connnectRecord(std::vector<char*>& connectA, vector<char*>& connectB, int& lengthA, int& colsA,
		 int lengthB, int colsB, hsql::Expr* where_expr, RecordBuilder* tmpBuilder);
	//void execute();
	//void clear();
};

#endif