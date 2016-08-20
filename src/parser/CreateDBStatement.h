#ifndef __CREATEDB_STATEMENT_H__
#define __CREATEDB_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct CreateDBStatement
 * @brief Represents "CREATE DATABASE Dbname"
 */
struct CreateDBStatement : SQLStatement {

	CreateDBStatement() :
		SQLStatement(kStmtCreateDB),
		DBname(NULL) {};

	virtual ~CreateDBStatement() {
		delete DBname;
	}
	
	const char* DBname;
};


} // namespace hsql
#endif