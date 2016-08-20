#ifndef __DROPINDEX_STATEMENT_H__
#define __DROPINDEX_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct DropDBStatement
 * @brief Represents "Drop DATABASE Dbname"
 */
struct DropIndexStatement : SQLStatement {

	DropIndexStatement() :
		SQLStatement(kStmtDropIndex),
		table(NULL),
		column(NULL) {};

	virtual ~DropIndexStatement() {
		delete table;
		delete column;
	}
	
	const char* table;
	const char* column;
};


} // namespace hsql
#endif