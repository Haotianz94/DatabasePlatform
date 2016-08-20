%{
/**
 * bison_parser.y
 * defines bison_parser.h
 * outputs bison_parser.c
 * 
 * Grammar File Spec: http://dinosaur.compilertools.net/bison/bison_6.html
 *
 */
/*********************************
 ** Section 1: C Declarations
 *********************************/

#include "sqllib.h"
#include "bison_parser.h"
#include "flex_lexer.h"

#include <stdio.h>

using namespace hsql;

int yyerror(YYLTYPE* llocp, SQLStatementList** result, yyscan_t scanner, const char *msg) {

	SQLStatementList* list = new SQLStatementList();
	list->isValid = false;
	list->parser_msg = strdup(msg);
	list->error_line = llocp->first_line;
	list->error_col = llocp->first_column;

	*result = list;
	return 0;
}



%}
/*********************************
 ** Section 2: Bison Parser Declarations
 *********************************/


// Specify code that is included in the generated .h and .c files
%code requires {
// %code requires block	
#include "parser_typedef.h"

// Auto update column and line number
#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
    	yylloc->total_column++; \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }
}

// Define the names of the created files
%output  "bison_parser.cpp"
%defines "bison_parser.h"

// Tell bison to create a reentrant parser
%define api.pure full

// Prefix the parser
%define api.prefix {hsql_}
%define api.token.prefix {SQL_}

%define parse.error verbose
%locations

%initial-action {
	// Initialize
	@$.first_column = 0;
	@$.last_column = 0;
	@$.first_line = 0;
	@$.last_line = 0;
	@$.total_column = 0;
	@$.placeholder_id = 0;
};


// Define additional parameters for yylex (http://www.gnu.org/software/bison/manual/html_node/Pure-Calling.html)
%lex-param   { yyscan_t scanner }

// Define additional parameters for yyparse
%parse-param { hsql::SQLStatementList** result }
%parse-param { yyscan_t scanner }


/*********************************
 ** Define all data-types (http://www.gnu.org/software/bison/manual/html_node/Union-Decl.html)
 *********************************/
%union {
	double fval;
	int64_t ival;
	char* sval;
	uint uval;
	bool bval;

	hsql::SQLStatement* statement;
	hsql::CreateDBStatement* createDB_stmt;
	hsql::DropDBStatement*  dropDB_stmt;
	hsql::UseDBStatement* useDB_stmt;
	hsql::ShowTableStatement* showTable_stmt;
	hsql::CreateStatement* 	create_stmt;
	hsql::DropStatement*   	drop_stmt;
	hsql::DescStatement* desc_stmt;
	hsql::InsertStatement* 	insert_stmt;
	hsql::DeleteStatement* 	delete_stmt;
	hsql::UpdateStatement* 	update_stmt;
	hsql::SelectStatement* 	select_stmt;
	hsql::CreateIndexStatement* createIndex_stmt;
	hsql::DropIndexStatement* dropIndex_stmt;

	hsql::Expr* expr;
	hsql::OrderDescription* order;
	hsql::OrderType order_type;
	hsql::ColumnDefinition* column_t;
	hsql::GroupByDescription* group_t;
	hsql::UpdateClause* update_t;
	hsql::SQLStatementList* stmt_list;

	std::vector<char*>* str_vec;
	std::vector<hsql::ColumnDefinition*>* column_vec;
	std::vector<hsql::UpdateClause*>* update_vec;
	std::vector<hsql::Expr*>* expr_vec;
	std::vector<std::vector<hsql::Expr*>*>* expr_vec_vec;
}



/*********************************
 ** Token Definition
 *********************************/
%token <sval> IDENTIFIER STRING
%token <fval> FLOATVAL
%token <ival> INTVAL
%token <uval> NOTEQUALS LESSEQ GREATEREQ

/* SQL Keywords */
%token DEALLOCATE PARAMETERS INTERSECT TEMPORARY TIMESTAMP
%token DISTINCT NVARCHAR RESTRICT TRUNCATE ANALYZE BETWEEN
%token CASCADE COLUMNS CONTROL DEFAULT EXECUTE EXPLAIN
%token HISTORY INTEGER NATURAL PREPARE PRIMARY SCHEMAS
%token SPATIAL VIRTUAL BEFORE COLUMN CREATE DELETE DIRECT
%token DOUBLE ESCAPE EXCEPT EXISTS GLOBAL HAVING IMPORT
%token INSERT ISNULL OFFSET RENAME SCHEMA SELECT SORTED
%token TABLES UNIQUE UNLOAD UPDATE VALUES AFTER ALTER CROSS
%token DELTA GROUP INDEX INNER LIMIT LOCAL MERGE MINUS ORDER
%token OUTER RIGHT TABLE UNION USING WHERE CALL DATE DESC
%token DROP FILE FROM FULL HASH HINT INTO JOIN LEFT LIKE
%token LOAD NULL PART PLAN SHOW TEXT TIME VIEW WITH ADD ALL
%token AND ASC CSV FOR INT KEY NOT OFF SET TBL TOP AS BY IF
%token IN IS OF ON OR TO DATABASE USE CHECK SUM AVG MIN MAX


/*********************************
 ** Non-Terminal types (http://www.gnu.org/software/bison/manual/html_node/Type-Decl.html)
 *********************************/
%type <stmt_list>	statement_list
%type <statement> 	statement 
%type <createDB_stmt> createDB_statement
%type <dropDB_stmt> dropDB_statement
%type <useDB_stmt>  useDB_statement
%type <showTable_stmt> showTable_statement
%type <create_stmt> create_statement
%type <drop_stmt>	drop_statement
%type <desc_stmt>   desc_statement
%type <insert_stmt> insert_statement
%type <delete_stmt> delete_statement
%type <update_stmt> update_statement
%type <select_stmt> select_statement
%type <createIndex_stmt> createIndex_statement
%type <dropIndex_stmt> dropIndex_statement

%type <sval> 		table_name DBname opt_primary_key
%type <bval> 		opt_distinct opt_not_null
%type <ival>        opt_size
%type <uval>		column_type 
%type <expr> 		expr star_expr
%type <expr> 		column_name select_opt literal int_literal num_literal string_literal
%type <expr> 		operator_expr comp_expr opt_where opt_having opt_check 
%type <order>		opt_order
%type <order_type>	opt_order_type
%type <column_t>	column_def
%type <update_t>	update_clause
%type <group_t>		opt_group
%type <str_vec>		ident_commalist 
%type <expr_vec> 	expr_list select_list literal_list
%type <update_vec>	update_clause_commalist
%type <column_vec>	column_def_commalist
%type <expr_vec_vec> value_list

/******************************
 ** Token Precedence and Associativity
 ** Precedence: lowest to highest
 ******************************/
%left		OR
%left		AND
%right		NOT
%right		'=' EQUALS NOTEQUALS LIKE
%nonassoc	'<' '>' LESS GREATER LESSEQ GREATEREQ

%nonassoc	NOTNULL
%nonassoc	ISNULL
%nonassoc	IS				/* sets precedence for IS NULL, etc */
%left		'+' '-'
%left		'*' '/' '%'
%left		'^'

/* Unary Operators */
%right 		UMINUS
%left		'[' ']'
%left		'(' ')'
%left		'.'

%%
/*********************************
 ** Section 3: Grammar Definition
 *********************************/

// Defines our general input.
input:
		statement_list opt_semicolon {
			*result = $1;
		}
	;


statement_list:
		statement { $$ = new SQLStatementList($1); }
	|	statement_list ';' statement { $1->addStatement($3); $$ = $1; }
	;

statement:
		createDB_statement { $$ = $1; }
	|	dropDB_statement { $$ = $1; }
	|	useDB_statement { $$ = $1; }
	|	showTable_statement { $$ = $1; }
	|	create_statement { $$ = $1; }
	|	drop_statement { $$ = $1; }
	|	desc_statement { $$ = $1; }
	|	insert_statement { $$ = $1; }
	|	delete_statement { $$ = $1; }
	|	update_statement { $$ = $1; }
	|	select_statement { $$ = $1; }
	|	createIndex_statement { $$ = $1; }
	|	dropIndex_statement { $$ = $1; }
	;

/******************************
 * CreateDB Statement
 * CREATE DATABASE orderDB
 ******************************/
createDB_statement:
		CREATE DATABASE DBname {
			$$ = new CreateDBStatement();
			$$->DBname = $3;
		}
	;
DBname:
		IDENTIFIER
	;	

/******************************
 * DropDB Statement
 * DROP DATABASE orderDB
 ******************************/
dropDB_statement:
		DROP DATABASE DBname {
			$$ = new DropDBStatement();
			$$->DBname = $3;
		}
	;

/******************************
 * UseDB Statement
 * USE orderDB
 ******************************/
useDB_statement:
		USE DBname {
			$$ = new UseDBStatement();
			$$->DBname = $2;
		}
	;

/******************************
 * ShowTable Statement
 * SHOW TABLES
 ******************************/
showTable_statement:
		SHOW TABLES {
			$$ = new ShowTableStatement();
		}
	;


/******************************
 * Create Statement
 * CREATE TABLE customer (id int(10) NOT NULL, name varchar(25) NOT NULL, gender varchar(1) NOT NULL, PRIMARY KEY(id))
 ******************************/
create_statement:
		CREATE TABLE table_name '(' column_def_commalist opt_primary_key ')' {
			$$ = new CreateStatement();
			$$->table_name = $3;
			$$->columns = $5;
			$$->primary_key = $6;
		}
	;

opt_primary_key:
		',' PRIMARY KEY '(' IDENTIFIER ')'{ $$ = $5; }
	|	PRIMARY KEY '(' IDENTIFIER ')'{ $$ = $4; }
	|	/* empty */ { $$ = NULL; }
	;

column_def_commalist:
		column_def { $$ = new std::vector<ColumnDefinition*>(); $$->push_back($1); }
	|	column_def_commalist ',' column_def { $1->push_back($3); $$ = $1; }
	;

column_def:
		IDENTIFIER column_type opt_size opt_not_null opt_check{
			$$ = new ColumnDefinition($1, (ColumnDefinition::DataType) $2, $3, $4, $5);
		}
	;

opt_size:
		'(' INTVAL ')' { $$ = $2; }
	|	/* empty */ { $$ = 20;}

opt_not_null:
		NOT NULL { $$ = true; }
	| 	/* empty */ { $$ = false;}

opt_check:
		CHECK comp_expr  { $$ = $2; }
	|	/* empty */ { $$ = NULL; }


column_type:
		INT { $$ = ColumnDefinition::INT; }
	|	INTEGER { $$ = ColumnDefinition::INT; }
	|	DOUBLE { $$ = ColumnDefinition::DOUBLE; }
	|	TEXT { $$ = ColumnDefinition::STRING; }
	;

/******************************
 * Drop Statement
 * DROP TABLE customer;
 ******************************/

drop_statement:
		DROP TABLE table_name {
			$$ = new DropStatement();
			$$->table_name = $3;
		}
	;

/******************************
 * Desc Statement
 * DESC customer;
 ******************************/

desc_statement:
		DESC table_name {
			$$ = new DescStatement();
			$$->table_name = $2;
		}
	;

/******************************
 * Insert Statement
 * INSERT INTO customer VALUES (300001, 'CHAD CABELLO' 'F');
 * INSERT INTO orders VALUES (315000,200001,’eight’);
 * INSERT INTO orders (id, num) VALUES (123, 456)
 ******************************/
insert_statement:
		INSERT INTO table_name VALUES value_list {
			$$ = new InsertStatement();
			$$->table_name = $3;
			$$->value_list = $5;
		}
	|	INSERT INTO table_name '(' ident_commalist ')' VALUES value_list {
			$$ = new InsertStatement();
			$$->table_name = $3;
			$$->keys = $5;
			$$->value_list = $8; 			
		}
	;

value_list:
		'(' literal_list ')' 				{ $$ = new std::vector<std::vector<hsql::Expr*>*>(); $$->push_back($2); }
	|	value_list ',' '(' literal_list ')'	{ $1->push_back($4); $$ = $1; }
	;

/******************************
 * Delete Statement 
 * DELETE FROM publisher WHERE state=’CA’;
 ******************************/
delete_statement:
		DELETE FROM table_name opt_where {
			$$ = new DeleteStatement();
			$$->table_name = $3;
			$$->expr = $4;
		}
	;


/******************************
 * Update Statement
 * UPDATE book SET title=’Nine Times Nine’ WHERE authors=’Anthony Boucher’;
 ******************************/

update_statement:
	UPDATE table_name SET update_clause_commalist opt_where {
		$$ = new UpdateStatement();
		$$->table_name = $2;
		$$->updates = $4;
		$$->where = $5;
	}
	;

update_clause_commalist:
		update_clause { $$ = new std::vector<UpdateClause*>(); $$->push_back($1); }
	|	update_clause_commalist ',' update_clause { $1->push_back($3); $$ = $1; }
	;

update_clause:
		IDENTIFIER '=' operator_expr {
			$$ = new UpdateClause();
			$$->column = $1;
			$$->value = $3;
		}
	;

/******************************
 * Select Statement
 * SELECT * FROM publisher WHERE nation=’CA’;
 * SELECT title FROM book WHERE authors is null;
 * SELECT book.title,orders.quantity FROM book,orders WHERE book.id=orders.book_id AND orders.quantity>8;
 // expanded
 * SELECT title,authors FROM book WHERE authors like ’%David%’;
 * SELECT customer.name,book.title,orders.quantity FROM customer,book,orders WHERE orders.customer_id=customer.id AND orders.book_id=book.id AND orders.quantity > 9;
 * SELECT SUM(quantity) FROM orders;
 * SELECT AVG(quantity) FROM orders;
 * SELECT MAX(quantity) FROM orders;
 * SELECT MIN(quantity) FROM orders;
 * SELECT customer_id,SUM(quantity) FROM orders GROUP BY customer_id; 
 ******************************/

select_statement:

		SELECT opt_distinct select_list FROM ident_commalist opt_where opt_group opt_order{
			$$ = new SelectStatement();
			$$->select_distinct = $2;
			$$->select_list = $3;
			//$$->from_table = $4;
			$$->table_list = $5;
			$$->where_expr = $6;
			$$->group_by = $7;
			$$->order = $8;
		}
	;

opt_distinct:
		DISTINCT { $$ = true; }
	|	/* empty */ { $$ = false; }
	;

select_list:
		select_opt { $$ = new std::vector<Expr*>(); $$->push_back($1); }
	|	select_list ',' select_opt { $1->push_back($3); $$ = $1; }
	|	star_expr { $$ = new std::vector<Expr*>(); $$->push_back($1); }
	;

select_opt:
		column_name					{ $$ = $1; }
	|	SUM '(' column_name ')'		{ $$ = Expr::makeCalculate($3, Expr::SUM); }
	|	AVG '(' column_name ')'		{ $$ = Expr::makeCalculate($3, Expr::AVG); }
	|	MAX '(' column_name ')'		{ $$ = Expr::makeCalculate($3, Expr::MAX); }
	|	MIN '(' column_name ')'		{ $$ = Expr::makeCalculate($3, Expr::MIN); }
	;

opt_where:
		WHERE comp_expr { $$ = $2; }
	|	/* empty */ { $$ = NULL; }
	;

opt_group:
		GROUP BY expr_list opt_having {
			$$ = new GroupByDescription();
			$$->columns = $3;
			$$->having = $4;
		}
	|	/* empty */ { $$ = NULL; }
	;

opt_having:
		HAVING expr { $$ = $2; }
	|	/* empty */ { $$ = NULL; }

opt_order:
		ORDER BY expr opt_order_type { $$ = new OrderDescription($4, $3); }
	|	/* empty */ { $$ = NULL; }
	;

opt_order_type:
		ASC { $$ = kOrderAsc; }
	|	DESC { $$ = kOrderDesc; }
	|	/* empty */ { $$ = kOrderAsc; }
	;

/******************************
 * CreateIndex Statement
 * CREATE INDEX customer(name)
 ******************************/
createIndex_statement:
		CREATE INDEX table_name '(' IDENTIFIER ')' {
			$$ = new CreateIndexStatement();
			$$->table = $3;
			$$->column = $5;
		}
	;

/******************************
 * DropIndex Statement
 * DROP INDEX customer(name)
 ******************************/
dropIndex_statement:
		DROP INDEX table_name '(' IDENTIFIER ')' {
			$$ = new DropIndexStatement();
			$$->table = $3;
			$$->column = $5;
		}
	;

/******************************
 * Expressions 
 ******************************/
expr_list:
		expr { $$ = new std::vector<Expr*>(); $$->push_back($1); }
	|	expr_list ',' expr { $1->push_back($3); $$ = $1; }
	;

literal_list:
		literal { $$ = new std::vector<Expr*>(); $$->push_back($1); }
	|	literal_list ',' literal { $1->push_back($3); $$ = $1; }
	;

expr:
		'(' expr ')' { $$ = $2; }
	|	operator_expr
	|	comp_expr
	;

operator_expr:
		'(' operator_expr ')'					{ $$ = $2; }
	|	'-' operator_expr 						{ $$ = Expr::makeOpUnary(Expr::UMINUS, $2); }
	|	operator_expr '-' operator_expr			{ $$ = Expr::makeOpBinary($1, Expr::MINUS, $3); }
	|	operator_expr '+' operator_expr			{ $$ = Expr::makeOpBinary($1, Expr::ADD, $3); }
	|	operator_expr '/' operator_expr			{ $$ = Expr::makeOpBinary($1, Expr::DIVIDE, $3); }
	|	operator_expr '*' operator_expr			{ $$ = Expr::makeOpBinary($1, Expr::MULTIPLE, $3); }
	|	operator_expr '%' operator_expr			{ $$ = Expr::makeOpBinary($1, Expr::MOD, $3); }
	|	operator_expr '^' operator_expr			{ $$ = Expr::makeOpBinary($1, Expr::MI, $3); }
	|	column_name
	|	literal
	;


comp_expr:
		'(' comp_expr ')'   					{ $$ = $2; }
	|	NOT comp_expr 							{ $$ = Expr::makeBoolUnary(Expr::NOT, $2); }
	|	column_name IS NULL 					{ $$ = Expr::makeBoolUnary(Expr::ISNULL, $1); }
	|	operator_expr '=' operator_expr			{ $$ = Expr::makeBoolBinary($1, Expr::EQUAL, $3); }
	|	operator_expr NOTEQUALS operator_expr	{ $$ = Expr::makeBoolBinary($1, Expr::NOT_EQUAL, $3); }
	|	operator_expr '<' operator_expr			{ $$ = Expr::makeBoolBinary($1, Expr::LESS, $3); }
	|	operator_expr '>' operator_expr			{ $$ = Expr::makeBoolBinary($1, Expr::GREATER, $3); }
	|	operator_expr LESSEQ operator_expr		{ $$ = Expr::makeBoolBinary($1, Expr::LESS_EQ, $3); }
	|	operator_expr GREATEREQ operator_expr	{ $$ = Expr::makeBoolBinary($1, Expr::GREATER_EQ, $3); }
	|	comp_expr AND comp_expr					{ $$ = Expr::makeBoolBinary($1, Expr::AND, $3); }
	|	comp_expr OR comp_expr					{ $$ = Expr::makeBoolBinary($1, Expr::OR, $3); }
	|	operator_expr LIKE operator_expr		{ $$ = Expr::makeBoolBinary($1, Expr::LIKE, $3); }
	|	operator_expr NOT LIKE operator_expr	{ $$ = Expr::makeBoolBinary($1, Expr::NOT_LIKE, $4); }
	|	operator_expr IN '(' literal_list ')'			{ $$ = Expr::makeBoolBinary($1, Expr::IN, $4); }
	;

column_name:
		IDENTIFIER { $$ = Expr::makeColumnRef($1); }
	|	IDENTIFIER '.' IDENTIFIER { $$ = Expr::makeColumnRef($1, $3); }
	;

literal:
		string_literal
	|	num_literal
	|	NULL { $$ = Expr::makeLiteral(); }	
	;

string_literal:
		STRING { $$ = Expr::makeLiteral($1); }
	;


num_literal:
		FLOATVAL { $$ = Expr::makeLiteral($1); }
	|	int_literal
	;

int_literal:
		INTVAL { $$ = Expr::makeLiteral($1); }
	;

star_expr:
		'*' { $$ = new Expr(kExprStar); }
	;


/******************************
 * Table 
 ******************************/
table_name:
		IDENTIFIER
	|	IDENTIFIER '.' IDENTIFIER
	;


/******************************
 * Misc
 ******************************/

opt_semicolon:
		';'
	|	/* empty */
	;


ident_commalist:
		IDENTIFIER { $$ = new std::vector<char*>(); $$->push_back($1); }
	|	ident_commalist ',' IDENTIFIER { $1->push_back($3); $$ = $1; }
	;

%%
/*********************************
 ** Section 4: Additional C code
 *********************************/

/* empty */

