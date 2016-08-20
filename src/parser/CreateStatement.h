#ifndef __CREATE_STATEMENT_H__
#define __CREATE_STATEMENT_H__

#include "SQLStatement.h"
#include "Expr.h"
namespace hsql {

/**
 * @struct ColumnDefinition
 * @brief Represents definition of a table column
 */
struct ColumnDefinition {
	enum DataType {
		STRING,
		INT,
		DOUBLE
	};

	ColumnDefinition(char* name, DataType type, int64_t size, bool null, Expr* check_expr) :
		name(name),
		type(type),
		size(size),
		not_null(null),
		check_expr(check_expr) {}

	virtual ~ColumnDefinition() {
		delete name;
	}

	char* name;
	DataType type;
	int64_t size;
	bool not_null;
	Expr* check_expr;
};


/**
 * @struct CreateStatement
 * @brief Represents "CREATE TABLE students (name TEXT, student_number INTEGER, city TEXT, grade DOUBLE)"
 */
struct CreateStatement : SQLStatement {

	CreateStatement() :
		SQLStatement(kStmtCreate),
		columns(NULL),
		table_name(NULL),
		primary_key(NULL) {};

	virtual ~CreateStatement() {
		delete columns;
		delete table_name;
	}

	std::vector<ColumnDefinition*>* columns;
	const char* table_name;
	const char* primary_key;	
};



} // namespace hsql
#endif