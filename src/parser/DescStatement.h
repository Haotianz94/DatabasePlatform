#ifndef __DESC_STATEMENT_H__
#define __DESC_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct DropDBStatement
 * @brief Represents "DROP DATABASE Dbname"
 */
struct DescStatement : SQLStatement {

	DescStatement() :
		SQLStatement(kStmtDesc),
		table_name(NULL) {};

	virtual ~DescStatement() {
		delete table_name;
	}
	
	const char* table_name;
};


} // namespace hsql
#endif