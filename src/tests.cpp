#include "database/SQLParser.h"
#include "database/DataBaseSystem.h"
#include "utils/MyBitMap.h"
#include <iostream>

using namespace hsql;
using namespace std;

int main(int argc, char* argv[])
{
	MyBitMap :: initConst();

	DataBaseSystem myDB;

	if(argv[1][0] == '0')
	{
		while(true)
		{
			char sql[1000];
			cin.getline(sql, 1000);
			string sqlStmt(sql);
			if(sqlStmt == string("quit"))
				break;
			else
				cout<<myDB.readSQLstmt(sqlStmt);
			cout<<endl;
		}
	}
	else if(argv[1][0] == '1')
	{
		cout<<myDB.readSQLfile("../dataset/create.sql");
		cout<<myDB.readSQLfile("../../dataset/publisher.sql"); 
		cout<<myDB.readSQLfile("../../dataset/customer.sql"); 
		cout<<myDB.readSQLfile("../../dataset/book.sql"); 
		cout<<myDB.readSQLfile("../../dataset/orders.sql"); 
		
		while(true)
		{
			char sql[1000];
			cin.getline(sql, 1000);
			string sqlStmt(sql);
			if(sqlStmt == string("quit"))
				break;
			else
				cout<<myDB.readSQLstmt(sqlStmt);
			cout<<endl;
		}     
	}

	return 0;
}