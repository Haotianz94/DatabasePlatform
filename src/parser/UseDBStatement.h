#ifndef __USEDB_STATEMENT_H__
#define __USEDB_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct DropDBStatement
 * @brief Represents "DROP DATABASE Dbname"
 */
struct UseDBStatement : SQLStatement {

	UseDBStatement() :
		SQLStatement(kStmtUseDB),
		DBname(NULL) {};

	virtual ~UseDBStatement() {
		delete DBname;
	}
	
	const char* DBname;
};


} // namespace hsql
#endif