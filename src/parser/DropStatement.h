#ifndef __DROP_STATEMENT_H__
#define __DROP_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {


/**
 * @struct DropStatement
 * @brief Represents "DROP TABLE"
 */
struct DropStatement : SQLStatement {

	DropStatement() :
		SQLStatement(kStmtDrop),
		table_name(NULL) {}

	virtual ~DropStatement() {
		delete table_name;
	}

	const char* table_name;
};


} // namespace hsql
#endif