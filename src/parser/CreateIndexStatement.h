#ifndef __CREATEINDEX_STATEMENT_H__
#define __CREATEINDEX_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct CreateDBStatement
 * @brief Represents "CREATE DATABASE Dbname"
 */
struct CreateIndexStatement : SQLStatement {

	CreateIndexStatement() :
		SQLStatement(kStmtCreateIndex),
		table(NULL),
		column(NULL) {};

	virtual ~CreateIndexStatement() {
		delete table;
		delete column;
	}
	
	const char* table;
	const char* column;
};


} // namespace hsql
#endif