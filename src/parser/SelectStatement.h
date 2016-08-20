#ifndef __SELECT_STATEMENT_H__
#define __SELECT_STATEMENT_H__

#include "SQLStatement.h"
#include "Expr.h"
#include "CreateStatement.h"

namespace hsql {



/**
 * @struct OrderDescription
 * @brief Description of the order by clause within a select statement
 * 
 * TODO: hold multiple expressions to be sorted by
 */
typedef enum {
	kOrderAsc,
	kOrderDesc
} OrderType;

struct OrderDescription {
	OrderDescription(OrderType type, Expr* expr) :
		type(type),
		expr(expr) {}
		
	virtual ~OrderDescription() {
		delete expr;
	}

	OrderType type;
	Expr* expr;	
};


/**
 * @struct GroupByDescription
 */
struct GroupByDescription {
	GroupByDescription() : 
		columns(NULL),
		having(NULL) {}

	~GroupByDescription() {
		delete columns;
		delete having;
	}

	std::vector<Expr*>* columns;
	Expr* having;
};

struct SelectOpt
{
	typedef enum {
		MAX,
		MIN,
		SUM,
		AVG
	}Option;

	int colId;	
	Option opt;
	double val;
	std::string colName;
	ColumnDefinition::DataType type; 
	SelectOpt(int colId, Option opt, double val, std::string colName, ColumnDefinition::DataType type):
		colId(colId),
		opt(opt),
		val(val),
		colName(colName),
		type(type) {}
};

/**
 * @struct SelectStatement
 * @brief Representation of a full select statement.
 * 
 * TODO: add union_order and union_limit
 */
struct SelectStatement : SQLStatement {
	SelectStatement() : 
		SQLStatement(kStmtSelect),
		//from_table(NULL),
		table_list(NULL),
		select_list(NULL),
		where_expr(NULL),
		group_by(NULL),
		order(NULL) {};

	virtual ~SelectStatement() {
		//delete from_table;
		delete table_list;
		delete select_list;
		delete where_expr;
		delete group_by;
		delete order;
	}

	//TableRef* from_table;
	std::vector<char*>* table_list;
	bool select_distinct;
	std::vector<Expr*>* select_list;
	Expr* where_expr;	
	GroupByDescription* group_by;
	OrderDescription* order;
};


} // namespace hsql

#endif