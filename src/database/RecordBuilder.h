#ifndef __RECORDBUILDER__H__
#define __RECORDBUILDER__H__

#include <cstring>
#include <string>
#include <cstdlib>
#include <map>
#include "../parser/sqllib.h"
#include "stdint.h"
#include "../bplustree/KeyValues.h"

class RecordBuilder
{
	private:
		bool _ignore;
		bool _connect;
		bool _init;
		int _length;
		int _cols;
		int _cols_int;
		int _cols_double;
		int _cols_string;
		int _null_offset; // isNULL 1/ notNULL 0
		int _primary_key;

		std::string _table_name;

		std::vector<std::string> _key_name;
		std::vector<hsql::ColumnDefinition::DataType> _key_type;
		std::vector<int> _value_length;
		std::vector<int> _not_null;
		std::vector<int> _offset;

		std::map<std::string, int> _key_table;
		std::vector<int> _key_index;

		int findKey(char* key);

	public:

		enum Error
		{
			OK,
			NOTINT,
			NOTDOUBLE,
			NOTSTRING,
			OVERLENGTH,
			ISNULL,
			BADKEY,
			REDUNDENT,
			BADTYPE
		};

		RecordBuilder();
		RecordBuilder(char* format);
		~RecordBuilder();
		char* createFormat(const char* tablename, std::vector<hsql::ColumnDefinition*>* columns, 
			const char* primary_key, int& format_length, int& record_length, int& key_index_len,
			 int& key_index_type, int& key_index_col);
		void initFormat(char* format);
		void addFormat(char* format);
		char* formatRecord(std::vector<hsql::Expr*>* values, Error& errorCode, int& errorKey);
		char* formatRecord(std::vector<char*>* keys, std::vector<hsql::Expr*>* values, Error& errorCode, int& errorKey);
		std::string getTableMode();
		int getCols() { return _cols; }
		int getRecordLength() { return _length; }
		std::string showRecord(char* record);
		std::string showRecord(char* record, std::vector<hsql::Expr*>* select_list);
		bool match(char* record, hsql::Expr* where);
		hsql::Expr* calculate(char* record, hsql::Expr* expr);
		bool checkUpdate(std::vector<hsql::UpdateClause*>* updates);
		bool updateRecord(char* record, std::vector<hsql::UpdateClause*>* updates);
		bool checkSelect(std::vector<hsql::Expr*>* select_list);
		
		KeyValue* getIndexVal(char* record, int colId);
		std::vector<int>* getIndexCol() { return &_key_index; }
		int getPKId() { return _primary_key; }
		bool addIndex(int colId);
		bool addIndex(const char* column);
		bool dropIndex(const char* column);
		void setIgnore(bool ignore) { _ignore = ignore; }
		std::vector<hsql::SelectOpt>* getSelectOpt(std::vector<hsql::Expr*>* select_list);
		double getSelectVal(char* record, int colId);
};

#endif