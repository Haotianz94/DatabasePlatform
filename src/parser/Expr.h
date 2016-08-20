#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include <stdlib.h>
#include <memory>
#include <vector>

namespace hsql {

// Helper function
char* substr(const char* source, int from, int to);



typedef enum {
	kExprLiteralFloat,
	kExprLiteralString,
	kExprLiteralInt,
	kExprStar,
	kExprPlaceholder,
	kExprColumnRef,
	kExprFunctionRef,
	kExprOperator,
	kExprBoolean,
	kExprLiteralNull,
	kExprCalculate,
	kExprIgnore
} ExprType;


typedef struct Expr Expr;

/** 
 * @class Expr
 * @brief Represents SQL expressions (i.e. literals, operators, column_refs)
 *
 * TODO: When destructing a placeholder expression, we might need to alter the placeholder_list
 */
struct Expr {
	/**
	 * Operator types. These are important for expressions of type kExprOperator
	 * Trivial types are those that can be described by a single character e.g:
	 * + - * / < > = %
	 * Non-trivial are:
	 * <> <= >= LIKE ISNULL NOT
	 */
	typedef enum {
		// Bool
		NOT,
		ISNULL,
		EQUAL,
		NOT_EQUAL,
		LESS,
		LESS_EQ,
		GREATER,
		GREATER_EQ,
		LIKE,
		NOT_LIKE,
		AND,
		OR,
		IN,
		// Operator
		UMINUS,
		ADD,
		MINUS,
		DIVIDE,
		MULTIPLE,
		MOD,
		MI,
		//calculate
		SUM,
		AVG,
		MAX,
		MIN
	} OperatorType;



	Expr(ExprType type) :
		type(type),
		expr(NULL),
		expr2(NULL),
		name(NULL),
		literal_list(NULL),
		table(NULL),
		alias(NULL) {};

	// Interesting side-effect:
	// Making the destructor virtual used to cause segmentation faults
	~Expr();
	
	ExprType type;

	Expr* expr;
	Expr* expr2;
	char* name;
	char* table;
	char* alias;
	float fval;
	int64_t ival;
	int64_t ival2;
	std::vector<Expr*>* literal_list;

	OperatorType op_type;
	bool distinct;


	/**
	 * Convenience accessor methods
	 */
	inline bool isType(ExprType e_type) { return e_type == type; }
	inline bool isLiteral() { return isType(kExprLiteralInt) || isType(kExprLiteralFloat) || isType(kExprLiteralString) || isType(kExprPlaceholder); }
	inline bool hasAlias() { return alias != NULL; }
	inline bool hasTable() { return table != NULL; }
	inline char* getName() {
		if (alias != NULL) return alias;
		else return name;
	}

	/**
	 * Static expression constructors
	 */
	static Expr* makeOpUnary(OperatorType op, Expr* expr);
	static Expr* makeOpBinary(Expr* expr1, OperatorType op, Expr* expr2);
	static Expr* makeBoolUnary(OperatorType op, Expr* expr);
	static Expr* makeBoolBinary(Expr* expr1, OperatorType op, Expr* expr2);
	static Expr* makeBoolBinary(Expr* expr1, OperatorType op, std::vector<Expr*>* list);

	static Expr* makeCalculate(Expr* expr, OperatorType op);

	static Expr* makeLiteral(int64_t val);
	static Expr* makeLiteral(double val);
	static Expr* makeLiteral(char* val);
	static Expr* makeLiteral();

	static Expr* makeColumnRef(char* name);
	static Expr* makeColumnRef(char* table, char* name);
	static Expr* makeFunctionRef(char* func_name, Expr* expr, bool distinct);

	static Expr* makePlaceholder(int id);
};

// Zero initializes an Expr object and assigns it to a space in the heap
// For Hyrise we still had to put in the explicit NULL constructor
// http://www.ex-parrot.com/~chris/random/initialise.html
// Unused
#define ALLOC_EXPR(var, type) 		\
	Expr* var;						\
	do {							\
		Expr zero = {type};			\
		var = (Expr*)malloc(sizeof *var);	\
		*var = zero;				\
	} while(0);
#undef ALLOC_EXPR


} // namespace hsql

#endif
