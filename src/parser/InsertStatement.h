#ifndef __INSERT_STATEMENT_H__
#define __INSERT_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {


/**
 * @struct InsertStatement
 * @brief Represents "INSERT INTO students VALUES ('Max', 1112233, 'Musterhausen', 2.3)"
 */
struct InsertStatement : SQLStatement {

	InsertStatement() :
		SQLStatement(kStmtInsert),
		table_name(NULL),
		value_list(NULL),
		keys(NULL) {}
	
	virtual ~InsertStatement() {
		delete table_name;
		delete value_list;
		delete keys;
	}

	const char* table_name;
	std::vector<std::vector<Expr*>*>* value_list;
	std::vector<char*>* keys;
};




} // namsepace hsql
#endif