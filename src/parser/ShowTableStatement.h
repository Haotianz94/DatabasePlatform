#ifndef __SHOWTABLE_STATEMENT_H__
#define __SHOWTABLE_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct DropDBStatement
 * @brief Represents "DROP DATABASE Dbname"
 */
struct ShowTableStatement : SQLStatement {

	ShowTableStatement() :
		SQLStatement(kStmtShowTable){};

	virtual ~ShowTableStatement() {
	}
};


} // namespace hsql
#endif