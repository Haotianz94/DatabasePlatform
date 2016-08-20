#ifndef __DROPDB_STATEMENT_H__
#define __DROPDB_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct DropDBStatement
 * @brief Represents "DROP DATABASE Dbname"
 */
struct DropDBStatement : SQLStatement {

	DropDBStatement() :
		SQLStatement(kStmtDropDB),
		DBname(NULL) {};

	virtual ~DropDBStatement() {
		delete DBname;
	}
	
	const char* DBname;
};


} // namespace hsql
#endif