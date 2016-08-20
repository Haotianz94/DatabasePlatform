#include "RecordBuilder.h"
#include <iostream>
#include <regex>

using namespace std;
using namespace hsql;

RecordBuilder::RecordBuilder():
	_ignore(false),
	_connect(false),
	_init(false),
	_length(0),
	_cols(0),
	_cols_int(0),
	_cols_double(0),
	_cols_string(0),
	_null_offset(0),
	_primary_key(-1) {}
RecordBuilder::RecordBuilder(char* format):
	_ignore(false),
	_connect(false),
	_init(false),
	_length(0),
	_cols(0),
	_cols_int(0),
	_cols_double(0),
	_cols_string(0),
	_null_offset(0),
	_primary_key(-1)
	{ initFormat(format); }
RecordBuilder::~RecordBuilder()
{
}

char* RecordBuilder::createFormat(const char* tablename, vector<ColumnDefinition*>* columns,
	 const char* primary_key, int& format_length, int& record_length, int& key_index_len,
	  int& key_index_type, int& key_index_col)
{
	int format_l = 4 + strlen(tablename) + 36 * int(columns->size()) + 4;
	char* format = new char[format_l];
	char* format_begin = format;
	//cout<<format_l<<endl;
	int record_l = 0;
	format_l = 0;

	//table name
	int l = strlen(tablename);
	*((int*)format) = l;
	format += 4;
	format_l += 4;
	for(int i=0; i<l; i++)
		*format++ = tablename[i];
	format_l += l;
	
	*((int*)format) = int(columns->size());
	format += 4;
	format_l += 4;
	//cols
	int checks = 0;//count check constrants
	for(unsigned int i=0; i<columns->size(); i++)
	{
		//col name
		l = strlen((*columns)[i]->name);
		*((int*)format) = l;
		format += 4;
		for(int j=0; j<l; j++)
			*format++ = (*columns)[i]->name[j];
		format_l += l;
		//type
		*((int*)format) = (*columns)[i]->type;
		format += 4;
		*((int*)format) = (*columns)[i]->size;
		format += 4;
		*((int*)format) = (*columns)[i]->not_null? 1:0;
		format += 4;
		format_l += 16;
		if((*columns)[i]->type == ColumnDefinition::STRING)
			record_l += int((*columns)[i]->size + 1);
		else
			record_l += 8;
		if(columns->at(i)->check_expr != NULL)
			checks++;
	}
	//primary key
	*((int*)format) = -1;
	int find_key = -1;
	if(primary_key != NULL)
		for(unsigned int i=0; i<columns->size(); i++)
		{
			if(strcmp((*columns)[i]->name, primary_key) == 0)
			{
				*((int*)format) = int(i);
				find_key = int(i);
				break;
			}
		}
	if(find_key != -1)
	{
		if(columns->at(find_key)->type == ColumnDefinition::STRING)
		{
			key_index_len = columns->at(find_key)->size + 1;
			key_index_type = KEYTYPE_STRING;
		}
		else if(columns->at(find_key)->type == ColumnDefinition::INT)
		{
			key_index_len = 8;
			key_index_type = KEYTYPE_INTEGER;
		}
		else
		{
			key_index_len = 8;
			key_index_type = KEYTYPE_DOUBLE;
		}
		key_index_col = find_key;
	}
	else
	{
		if(columns->at(0)->type == ColumnDefinition::STRING)
		{
			key_index_len = columns->at(0)->size + 1;
			key_index_type = KEYTYPE_STRING;
		}
		else if(columns->at(0)->type == ColumnDefinition::INT)
		{
			key_index_len = 8;
			key_index_type = KEYTYPE_INTEGER;
		}
		else
		{
			key_index_len = 8;
			key_index_type = KEYTYPE_DOUBLE;
		}
		key_index_col = 0;
	}

	format += 4;
	format_l += 4;
	// is null
	record_l += int(columns->size());
	// check 
	/**((int*)format) = checks;
	format += 4;
	format_l += 4;
	if(checks != 0)
	{
		for(unsigned int i=0; i<columns->size(); i++)
		{
			if(columns->at(i)->check_expr)
			{
				*((int*)format) = int(i);
				format += 4;
				format_l += 4;
				vector<Expr*>* list = check_expr->literal_list;
				int l = int(list->size());
				*((int*)format) = l;
				format += 4;
				format_l += 4;

			}
		}
	}*/

	format = '\0';
	format_length = format_l;
	record_length = record_l;
	return format_begin;
}

char* RecordBuilder::formatRecord(vector<Expr*>* values, Error& errorCode, int& errorKey)
{
	//must check num outside;
	char* record = new char[_length+1];
	record[_length] = '\0';
	char* record_begin = record;
	char* null_begin = record + _null_offset;

	//init
	for(int i=0; i<_cols; i++)
	{
		null_begin[i] = 0;
	}

	//match key
	for(unsigned int i=0; i<values->size(); i++)
	{
		record = record_begin;
		if((*values)[i]->type == kExprLiteralNull)
		{
			if(_not_null[i] == 1)
			{
				errorCode = ISNULL;
				errorKey = i;
				delete record_begin;
				return NULL;
			}
			else
				null_begin[i] = 1;
		}
		else if(_key_type[i] == ColumnDefinition::INT)
		{
			if((*values)[i]->type != kExprLiteralInt)
			{
				errorCode = NOTINT;
				errorKey = i;
				delete record_begin;
				return NULL;
			}
			record += _offset[i];
			*((int64_t*)record) = (*values)[i]->ival;
		}
		else if(_key_type[i] == ColumnDefinition::DOUBLE)
		{
			if((*values)[i]->type == kExprLiteralInt)
			{
				record += _offset[i];
				*((double*)record) = (*values)[i]->ival;
			}
			else if((*values)[i]->type == kExprLiteralFloat)
			{
				record += _offset[i];
				*((double*)record) = (*values)[i]->fval;
			}
			else
			{
				errorCode = NOTDOUBLE;
				errorKey = i;
				delete record_begin;
				return NULL;
			}
		}
		else if(_key_type[i] == ColumnDefinition::STRING)
		{
			if((*values)[i]->type != kExprLiteralString)
			{
				errorCode = NOTSTRING;
				errorKey = i;
				delete record_begin;
				return NULL;
			}
			record += _offset[i];
			int l = strlen((*values)[i]->name);
			if(l > _value_length[i])
			{
				errorCode = OVERLENGTH;
				errorKey = i;
				delete record_begin;
				return NULL;
			}
			for(int j=0; j<l; j++)
			{
				record[j] = (*values)[i]->name[j];
			}
			record[l] = '\0';
		}
	}
	errorCode = OK;
	errorKey = -1;
	return record_begin;
}


char* RecordBuilder::formatRecord(vector<char*>* keys, vector<Expr*>* values, Error& errorCode, int& errorKey)
{
	//must check num outside;
	char* record = new char[_length+1];
	record[_length] = '\0';
	char* record_begin = record;
	char* null_begin = record + _null_offset;

	//init
	for(int i=0; i<_cols; i++)
	{
		null_begin[i] = 1;
	}

	//match key
	for(unsigned int i=0; i<keys->size(); i++)
	{
		record = record_begin;

		int k = _key_table[string((*keys)[i])] - 1;
		//cout<<"kkk"<<k<<endl;
		if(k == -1)
		{
			errorCode = BADKEY;
			errorKey = i;
			delete record_begin;
			return NULL;
		}
		if(null_begin[k] == 0)
		{
			errorCode = REDUNDENT;
			errorKey = i;
			delete record_begin;
			return NULL;
		}
		if((*values)[i]->type == kExprLiteralNull)
			continue;
		else
			null_begin[k] = 0;
		if(_key_type[k] == ColumnDefinition::INT)
		{
			if((*values)[i]->type != kExprLiteralInt)
			{
				errorCode = NOTINT;
				errorKey = i;
				delete record_begin;
				return NULL;
			}
			record += _offset[k];
			*((int64_t*)record) = (*values)[i]->ival;
		}
		else if(_key_type[k] == ColumnDefinition::DOUBLE)
		{
			if((*values)[i]->type == kExprLiteralInt)
			{
				record += _offset[k];
				*((double*)record) = (*values)[i]->ival;
			}
			else if((*values)[i]->type == kExprLiteralFloat)
			{
				record += _offset[k];
				*((double*)record) = (*values)[i]->fval;
			}
			else
			{
				errorCode = NOTDOUBLE;
				errorKey = i;
				delete record_begin;
				return NULL;
			}
		}
		else if(_key_type[k] == ColumnDefinition::STRING)
		{
			if((*values)[i]->type != kExprLiteralString)
			{
				errorCode = NOTSTRING;
				errorKey = i;
				delete record_begin;
				return NULL;
			}
			record += _offset[k];
			int l = strlen((*values)[i]->name);
			if(l > _value_length[k])
			{
				errorCode = OVERLENGTH;
				errorKey = i;
				delete record_begin;
				return NULL;
			}
			for(int j=0; j<l; j++)
			{
				record[j] = (*values)[i]->name[j];
			}
			record[l] = '\0';
		}
	}
	//can be null
	for(int i=0; i<_cols; i++)
		if(null_begin[i] == 1 && _not_null[i] == 1)
		{
			errorCode = ISNULL;
			errorKey = i;
			delete record_begin;
			return NULL;
		}

	//cout<<strlen(record_begin)<<endl;
	errorCode = OK;
	errorKey = -1;
	return record_begin;
}

void RecordBuilder::initFormat(char* format)
{
	_init = true;
	_connect = false;
	//table name
	int l = *((int*)format);
	format += 4;
	//cout<<"tablename length:"<<l<<endl;
	_table_name = string(format,l);
	//cout<<"tablename "<<_table_name<<endl;
	format += l;
	//cols
	_cols = *((int*)format);
	//cout<<"cols "<<_cols<<endl;
	format += 4;
	_key_name.resize(_cols);
	_key_type.resize(_cols);
	_value_length.resize(_cols);
	_offset.resize(_cols);
	_not_null.resize(_cols);
	//each col
	for(int i=0; i<_cols; i++)
	{
		//key name
		l = *((int*)format);
		format += 4;
		_key_name[i] = string(format, l);
		_key_table.insert(pair<string, int>(_key_name[i], i+1));
		format += l;
		//offset
		_offset[i] = _length;
		//key type and length
		_key_type[i] = *((ColumnDefinition::DataType*)format);
		format += 4;
		l = _value_length[i] = *((int*)format);
		format += 4;
		switch (_key_type[i])
		{
			case ColumnDefinition::INT:			_cols_int ++;
														_length += 8;
														break;
			case ColumnDefinition::DOUBLE:		_cols_double ++;
														_length += 8;
														break;
			case ColumnDefinition::STRING:		_cols_string ++;
														_length += (l+1);
														break;
			default:									break;
		}
		//can be null		
		_not_null[i] = *((int*)format);
		format += 4;
	}
	_primary_key = *((int*)format);
	_null_offset = _length;
	_length += _cols;

	_key_index.push_back(_primary_key);

	//cout<<_table_name<<' '<<_cols<<endl;
}

void RecordBuilder::addFormat(char* format)
{
	_init = true;
	_connect = true;
	//table name
	int l = *((int*)format);
	format += 4;
	//cout<<"tablename length:"<<l<<endl;
	string newtbname = string(format,l);
	_table_name += newtbname;
	newtbname += string(".");
	//cout<<"tablename "<<_table_name<<endl;
	format += l;
	//cols
	int newcols = *((int*)format);
	int oldcols = _cols;
	_cols += newcols;
	//cout<<"cols "<<_cols<<endl;
	format += 4;
	_key_name.resize(_cols);
	_key_type.resize(_cols);
	_value_length.resize(_cols);
	_offset.resize(_cols);
	_not_null.resize(_cols);
	//each col
	_length = _length - oldcols;
	for(int i=oldcols; i<_cols; i++)
	{
		//key name
		l = *((int*)format);
		format += 4;
		_key_name[i] = newtbname + string(format, l);
		_key_table.insert(pair<string, int>(_key_name[i], i+1));
		format += l;
		//offset
		_offset[i] = _length;
		//key type and length
		_key_type[i] = *((ColumnDefinition::DataType*)format);
		format += 4;
		l = _value_length[i] = *((int*)format);
		format += 4;
		switch (_key_type[i])
		{
			case ColumnDefinition::INT:			_cols_int ++;
														_length += 8;
														break;
			case ColumnDefinition::DOUBLE:		_cols_double ++;
														_length += 8;
														break;
			case ColumnDefinition::STRING:		_cols_string ++;
														_length += (l+1);
														break;
			default:									break;
		}
		//can be null		
		_not_null[i] = *((int*)format);
		format += 4;
	}
	if(_primary_key == -1)
	{
		int key = *((int*)format);
		if(key != -1)
			_primary_key = oldcols + key;
	}

	_null_offset = _length;
	_length += _cols;
	//record_length = _length;
	//cout<<"reocord length"<<' '<<_length<<endl;
	/*if(_primary_key != -1)
	{
		if(_key_type[_primary_key] == ColumnDefinition::STRING)
		{
			key_index_len = _value_length[_primary_key] + 1;
			key_index_type = KEYTYPE_STRING;
		}
		else if(_key_type[_primary_key] == ColumnDefinition::INT)
		{
			key_index_len = 8;
			key_index_type = KEYTYPE_INTEGER;
		}
		else
		{
			key_index_len = 8;
			key_index_type = KEYTYPE_DOUBLE;
		}
		key_index_col = _primary_key;
	}
	else
	{
		if(_key_type[0] == ColumnDefinition::STRING)
		{
			key_index_len = _value_length[0] + 1;
			key_index_type = KEYTYPE_STRING;
		}
		else if(_key_type[0] == ColumnDefinition::INT)
		{
			key_index_len = 8;
			key_index_type = KEYTYPE_INTEGER;
		}
		else
		{
			key_index_len = 8;
			key_index_type = KEYTYPE_DOUBLE;
		}
		key_index_col = 0;
	}*/
}

int RecordBuilder::findKey(char* key)
{
	for(int i=0; i<_cols; i++)
	{
		if(strcmp(key, _key_name[i].c_str()) == 0)
			return i;
	}
	return -1;
}

string RecordBuilder::getTableMode()
{
	string tableMode;
	//cout<<"cols"<<' '<<_cols<<endl;
	for(int i=0; i<_cols; i++)
	{
		tableMode += _key_name[i];
		tableMode += string(" ");
		switch (_key_type[i])
		{
			case ColumnDefinition::INT: 	tableMode += string("INT ");break;
			case ColumnDefinition::DOUBLE:	tableMode += string("DOUBLE ");break;
			case ColumnDefinition::STRING:	tableMode += string("TEXT ");break;
		}
		char s[20];
		if(_not_null[i] == 1)
			sprintf(s, "(%d) NOT NULL\n", _value_length[i]);
		else
			sprintf(s, "(%d) \n", _value_length[i]);
		tableMode += string(s); 
	}
	if(_primary_key != -1)
	{
		tableMode += string("primary key: ");
		tableMode += _key_name[_primary_key];
		tableMode += string("\n");
	}
	return tableMode;
}

bool RecordBuilder::match(char* record, Expr* expr)
{
	if(expr->type != kExprBoolean || expr == NULL || expr->expr == NULL)
		return false;

	switch (expr->op_type)
	{
		case Expr::NOT:
			return !match(record, expr->expr);
		case Expr::ISNULL:
		{
			Expr* column = calculate(record, expr->expr);
			if(column)
			{
				if(column->type == kExprLiteralNull || column->type == kExprIgnore)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		case Expr::AND:
			return match(record, expr->expr) && match(record, expr->expr2);
		case Expr::OR:
			return match(record, expr->expr) || match(record, expr->expr2);
		case Expr::EQUAL:
		{
			//cout<<"match equal"<<endl;
			Expr* left = calculate(record, expr->expr);
			Expr* right = calculate(record, expr->expr2);
			if(!left || !right)
				return false;
			if(left->type == kExprIgnore || right->type == kExprIgnore)
				return true;
			//cout<<"left "<<left->ival<<" right "<<right->ival<<endl;
			if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
				return left->ival == right->ival;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
				return left->fval == right->fval;
			else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
				return left->ival == right->fval;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
				return left->fval == right->ival;
			else if(left->type == kExprLiteralString && right->type == kExprLiteralString)
				return string(left->name) == string(right->name);
			else
				return false;
		}
		case Expr::NOT_EQUAL:
		{
			//cout<<"match not equal"<<endl;
			Expr* left = calculate(record, expr->expr);
			Expr* right = calculate(record, expr->expr2);
			if(!left || !right)
				return false;
			if(left->type == kExprIgnore || right->type == kExprIgnore)
				return true;
			//cout<<"left "<<left->ival<<" right "<<right->ival<<endl;
			if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
				return left->ival != right->ival;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
				return left->fval != right->fval;
			else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
				return left->ival != right->fval;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
				return left->fval != right->ival;
			else if(left->type == kExprLiteralString && right->type == kExprLiteralString)
				return !(string(left->name) == string(right->name));
			else
				return false;
		}
		case Expr::LESS:
		{
			Expr* left = calculate(record, expr->expr);
			Expr* right = calculate(record, expr->expr2);
			if(!left || !right)
				return false;
			if(left->type == kExprIgnore || right->type == kExprIgnore)
				return true;
			if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
				return left->ival < right->ival;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
				return left->fval < right->fval;
			else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
				return left->ival < right->fval;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
				return left->fval < right->ival;
			else
				return false;
		}
		case Expr::GREATER:
		{
			//cout<<"match equal"<<endl;
			Expr* left = calculate(record, expr->expr);
			Expr* right = calculate(record, expr->expr2);
			if(!left || !right)
				return false;
			if(left->type == kExprIgnore || right->type == kExprIgnore)
				return true;
			//cout<<"left "<<left->ival<<" right "<<right->ival<<endl;
			if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
				return left->ival > right->ival;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
				return left->fval > right->fval;
			else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
				return left->ival > right->fval;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
				return left->fval > right->ival;
			else
				return false;
		}
		case Expr::LESS_EQ:
		{
			Expr* left = calculate(record, expr->expr);
			Expr* right = calculate(record, expr->expr2);
			if(!left || !right)
				return false;
			if(left->type == kExprIgnore || right->type == kExprIgnore)
				return true;
			if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
				return left->ival <= right->ival;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
				return left->fval <= right->fval;
			else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
				return left->ival <= right->fval;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
				return left->fval <= right->ival;
			else
				return false;
		}
		case Expr::GREATER_EQ:
		{
			Expr* left = calculate(record, expr->expr);
			Expr* right = calculate(record, expr->expr2);
			if(!left || !right)
				return false;
			if(left->type == kExprIgnore || right->type == kExprIgnore)
				return true;
			if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
				return left->ival >= right->ival;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
				return left->fval >= right->fval;
			else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
				return left->ival >= right->fval;
			else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
				return left->fval >= right->ival;
			else
				return false;
		}
		case Expr::LIKE:
		{
			Expr* left = calculate(record, expr->expr);
			Expr* right = calculate(record, expr->expr2);
			if(!left || !right)
				return false;
			if(left->type == kExprIgnore || right->type == kExprIgnore)
				return true;
			if(left->type == kExprLiteralString && right->type == kExprLiteralString)
			{
				char* str = right->name;
 				int l = strlen(str);
 				char* p = new char[l*2];
 				char* ps = p;
 				for(int i=0; i<l; i++)
				{
					if(str[i] == '%' || str[i] == '*')
					{	
						*p++ = '.';
						*p++ = '*';
					}
					else if(str[i] == '_' || str[i] == '?')
						*p++ = '.';
					else
						*p++ = str[i];
				}
				*p = '\0';		
				const regex pattern(ps);
				delete[] ps;
   				return regex_match(left->name, pattern);
			}
			else
				return false;
		}
		case Expr::NOT_LIKE:
		{
			Expr* left = calculate(record, expr->expr);
			Expr* right = calculate(record, expr->expr2);
			if(!left || !right)
				return false;
			if(left->type == kExprIgnore || right->type == kExprIgnore)
				return true;
			if(left->type == kExprLiteralString && right->type == kExprLiteralString)
			{
				char* str = right->name;
 				int l = strlen(str);
 				char* p = new char[l*2];
 				char* ps = p;
 				for(int i=0; i<l; i++)
				{
					if(str[i] == '%' || str[i] == '*')
					{	
						*p++ = '.';
						*p++ = '*';
					}
					else if(str[i] == '_' || str[i] == '?')
						*p++ = '.';
					else
						*p++ = str[i];
				}
				*p = '\0';		
				const regex pattern(ps);
				delete[] ps;
   				return !regex_match(left->name, pattern);
			}
			else
				return false;
		}
		case Expr::IN:
		{
			Expr* left = calculate(record, expr->expr);
			vector<Expr*>* list = expr->literal_list;
			if(left == NULL)
				return false;
			if(left->type == kExprIgnore)
				return true;
			if(!left->isLiteral())
				return false;
			ExprType type = left->type;		
			bool res = false;
			for(unsigned int i=0; i<list->size(); i++)
			{
				switch (type)
				{
					case kExprLiteralInt:
					{
						if(list->at(i)->type == kExprLiteralInt)
							res = res || (list->at(i)->ival == left->ival);
						else if(list->at(i)->type == kExprLiteralFloat)
							res = res || (list->at(i)->fval == left->ival);
						else
							return false;
						break;
					}
					case kExprLiteralFloat:
					{
						if(list->at(i)->type == kExprLiteralInt)
							res = res || (list->at(i)->ival == left->fval);
						else if(list->at(i)->type == kExprLiteralFloat)
							res = res || (list->at(i)->fval == left->fval);
						else
							return false;
						break;
					}
					case kExprLiteralString:
					{
						if(list->at(i)->type == kExprLiteralString)
							res = res || (string(list->at(i)->name) == string(left->name));
						else
							return false;
						break;	
					}
				}
			}
			return res;
		}
		default:
			break;
	}
	return false;
}

Expr* RecordBuilder::calculate(char* record, Expr* expr)//char +++++ 1
{
	if(expr->type == kExprLiteralNull || expr->type == kExprBoolean)
		return NULL;
	if(expr->isLiteral())
		return expr;
	if(expr->type == kExprColumnRef)
	{
		int key;
		if(!_connect)
		{
			if(expr->table != NULL && string(expr->table) != _table_name )
			{
				if(_ignore)
				{
					Expr* e = new Expr(kExprIgnore);
					return e;
				}
				else
					return NULL;
			}
			key = _key_table[string(expr->name)]-1;
		}
		else
		{
			char columnref[100];
			sprintf(columnref, "%s.%s", expr->table, expr->name);
			key = _key_table[string(columnref)]-1;
			if(key == -1)
			{
				Expr* e = new Expr(kExprIgnore);
				return e;
			}
		}
		if(key == -1) 
			return NULL;

		char * record_begin = record;
		record += _null_offset;
		record += key;
		if(*record == 1)
			return Expr::makeLiteral();
		else
			record = record_begin;

		record += _offset[key];
		if(_key_type[key] == ColumnDefinition::INT)
			return Expr::makeLiteral(*((int64_t*)record));
		else if(_key_type[key] == ColumnDefinition::DOUBLE)
			return Expr::makeLiteral(*((double*)record));
		else
			return Expr::makeLiteral(record);
	}
	else if(expr->type == kExprOperator)
	{
		switch (expr->op_type)
		{
			case Expr::UMINUS:
			{
				Expr* column = calculate(record, expr->expr);
				if(!column)
					return NULL;
				if(column->type == kExprIgnore)
					return column;
				if(column->type == kExprLiteralInt)
					return Expr::makeLiteral(-column->ival);
				else if(column->type == kExprLiteralFloat)
					return Expr::makeLiteral(-column->fval);
				else
					return NULL;
			}
			case Expr::ADD:
			{
				Expr* left = calculate(record, expr->expr);
				Expr* right = calculate(record, expr->expr2);
				if(!left || !right)
					return NULL;
				if(left->type == kExprIgnore)
					return left;
				if(right->type == kExprIgnore)
					return right;
				if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
					return Expr::makeLiteral(left->ival + right->ival);
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
					return Expr::makeLiteral(left->fval + right->fval);
				else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
					return Expr::makeLiteral(left->ival + right->fval);
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
					return Expr::makeLiteral(left->fval + right->ival);
				else
					return NULL;
			}
			case Expr::MINUS:
			{
				Expr* left = calculate(record, expr->expr);
				Expr* right = calculate(record, expr->expr2);
				if(!left || !right)
					return NULL;
				if(left->type == kExprIgnore)
					return left;
				if(right->type == kExprIgnore)
					return right;
				if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
					return Expr::makeLiteral(left->ival - right->ival);
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
					return Expr::makeLiteral(left->fval - right->fval);
				else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
					return Expr::makeLiteral(left->ival - right->fval);
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
					return Expr::makeLiteral(left->fval - right->ival);
				else
					return NULL;
			}
			case Expr::MULTIPLE:
			{
				Expr* left = calculate(record, expr->expr);
				Expr* right = calculate(record, expr->expr2);
				if(!left || !right)
					return NULL;
				if(left->type == kExprIgnore)
					return left;
				if(right->type == kExprIgnore)
					return right;
				if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
					return Expr::makeLiteral(left->ival * right->ival);
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
					return Expr::makeLiteral(left->fval * right->fval);
				else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
					return Expr::makeLiteral(left->ival * right->fval);
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
					return Expr::makeLiteral(left->fval * right->ival);
				else
					return NULL;
			}
			case Expr::DIVIDE:
			{
				Expr* left = calculate(record, expr->expr);
				Expr* right = calculate(record, expr->expr2);
				if(!left || !right)
					return NULL;
				if(left->type == kExprIgnore)
					return left;
				if(right->type == kExprIgnore)
					return right;
				if(left->type == kExprLiteralInt && right->type == kExprLiteralInt && right->ival != 0)
					return Expr::makeLiteral(int64_t(left->ival / right->ival));
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat && right->fval != 0)
					return Expr::makeLiteral(left->fval / right->fval);
				else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat && right->fval != 0)
					return Expr::makeLiteral(left->ival / right->fval);
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt && right->ival != 0)
					return Expr::makeLiteral(left->fval / right->ival);
				else
					return NULL;
			}
			case Expr::MOD:
			{
				Expr* left = calculate(record, expr->expr);
				Expr* right = calculate(record, expr->expr2);
				if(!left || !right)
					return NULL;
				if(left->type == kExprIgnore)
					return left;
				if(right->type == kExprIgnore)
					return right;
				if(left->type == kExprLiteralInt && right->type == kExprLiteralInt && right->ival != 0)
					return Expr::makeLiteral(left->ival % right->ival);
				else
					return NULL;
			}
			case Expr::MI:
			{
				Expr* left = calculate(record, expr->expr);
				Expr* right = calculate(record, expr->expr2);
				if(!left || !right)
					return NULL;
				if(left->type == kExprIgnore)
					return left;
				if(right->type == kExprIgnore)
					return right;
				if(left->type == kExprLiteralInt && right->type == kExprLiteralInt)
					return Expr::makeLiteral(pow(left->ival, right->ival));
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralFloat)
					return Expr::makeLiteral(pow(left->fval, right->fval));
				else if(left->type == kExprLiteralInt && right->type == kExprLiteralFloat)
					return Expr::makeLiteral(pow(left->ival, right->fval));
				else if(left->type == kExprLiteralFloat && right->type == kExprLiteralInt)
					return Expr::makeLiteral(pow(left->fval, right->ival));
				else
					return NULL;
			}
			default:
				break;
		}
	}
	return NULL;
}
bool RecordBuilder::checkUpdate(vector<UpdateClause*>* updates)
{
	bool* used = new bool[_cols];
	for(int i=0; i<_cols; i++)
		used[i] = false;
	for(unsigned int i=0; i<updates->size(); i++)
	{
		int key = _key_table[string(updates->at(i)->column)] - 1;
		if(key == -1 || used[key] )
		{
			delete[] used;
			return false;
		}
		else
			used[key] = true;
	}
	delete[] used;
	return true;
}

bool RecordBuilder::updateRecord(char* record, vector<UpdateClause*>* updates)
{
	//showRecord(record);
	char* record_copy = new char[_length+1];
	for(int i=0; i<_length; i++)
		record_copy[i] = record[i];
	//showRecord(record_copy);
	char* record_begin = record_copy; 
	for(unsigned int i=0; i<updates->size(); i++)
	{
		record_copy = record_begin;
		int key = _key_table[string(updates->at(i)->column)] - 1;
		//cout<<updates->at(i)<<' '<<key<<endl;
		Expr* value = calculate(record_copy, updates->at(i)->value);
		//cout<<"value "<<value->ival<<endl;
		if(value == NULL)
		{
			delete[] record_begin;
			return false;
		}
		else if(value->type == kExprLiteralNull)
		{
			if(_not_null[key] == 1)
			{
				delete[] record_begin;
				return false;
			}
			else
			{
				record_copy += _null_offset;
				record_copy[key] = 1;
			}
		}
		else if(value->type == kExprLiteralInt)
		{
			if(_key_type[key] == ColumnDefinition::INT)
			{
				//cout<<"offset "<<_offset[key]<<endl;
				record_copy += _offset[key];
				*((int64_t*)record_copy) = value->ival;
			}
			else
			{
				delete[] record_begin;
				return false;	
			}
		}
		else if(value->type == kExprLiteralFloat)
		{
			if(_key_type[key] == ColumnDefinition::INT)
			{
				record_copy += _offset[key];
				*((double*)record_copy) = value->ival;
			}
			if(_key_type[key] == ColumnDefinition::DOUBLE)
			{
				record_copy += _offset[key];
				*((double*)record_copy) = value->fval;
			}
			else 
			{
				delete[] record_begin;
				return false;	
			}
		}
		else if(value->type == kExprLiteralString)
		{
			if(_key_type[key] != ColumnDefinition::STRING)
			{
				delete[] record_begin;
				return false;	
			}
			record_copy += _offset[key];
			int l = strlen(value->name);
			if(l > _value_length[key])
			{
				delete record_begin;
				return false;
			}
			for(int j=0; j<l; j++)
			{
				record_copy[j] = value->name[j];
			}
			record_copy[l] = '\0';
		}
	}
	//showRecord(record_copy);
	for(int i=0; i<_length; i++)
		record[i] = record_begin[i];
	delete[] record_begin;
	showRecord(record);
	return true;
}
string RecordBuilder::showRecord(char* record)
{
	string divide = string("--------------------------------\n");
	string res;
	//res += divide;
	char* record_begin = record;
	for(int i=0; i<_cols; i++)
	{
		record = record_begin;
		res += _key_name[i];
		res += string(" : ");
		record += _null_offset;
		record += i;
		if(*record == 1)
			res += string("NULL\n");
 		else
		{
			record = record_begin + _offset[i];
			switch (_key_type[i])
			{
				case ColumnDefinition::INT:
				{
					//cout<<*((int64_t*)record)<<endl;
					char s[50];
					sprintf(s, "%ld\n", *((int64_t*)record));
					res += string(s);
					break;
				}
				case ColumnDefinition::DOUBLE:
				{
					//cout<<*((double*)record)<<endl;
					char s[50];
					sprintf(s, "%lf\n", *((double*)record));
					res += string(s);
					break;
				}
				case ColumnDefinition::STRING:
				{
					//cout<<record<<endl;
					res += string(record);
					res += string("\n");
					break;
				}
			}
		}
	}
	res += divide;
	return res;
}
string RecordBuilder::showRecord(char* record, vector<Expr*>* select_list)
{
	if(select_list->empty())
		return string("");
	if(select_list->at(0)->type == kExprStar)
	{
		return showRecord(record);
	}

	string divide = string("--------------------------------\n");
	string res;
	//res += divide;
	char* record_begin = record;
	for(unsigned int i=0; i<select_list->size(); i++)
	{
		int key;
		if(!_connect)
			key = _key_table[string(select_list->at(i)->name)]-1;
		else
		{
			Expr* column = select_list->at(i);
			char columnref[100];
			sprintf(columnref, "%s.%s", column->table, column->name);
			key = _key_table[string(columnref)] - 1;
		}
		
		record = record_begin;
		res += _key_name[key];
		res += string(" : ");
		record += _null_offset;
		record += key;
		if(*record == 1)
			res += string("NULL\n");
		else
		{
			record = record_begin + _offset[key];
			switch (_key_type[key])
			{
				case ColumnDefinition::INT:
				{
					//cout<<*((int64_t*)record)<<endl;
					char s[50];
					sprintf(s, "%ld\n", *((int64_t*)record));
					res += string(s);
					break;
				}
				case ColumnDefinition::DOUBLE:
				{
					//cout<<*((double*)record)<<endl;
					char s[50];
					sprintf(s, "%lf\n", *((double*)record));
					res += string(s);
					break;
				}
				case ColumnDefinition::STRING:
				{
					//cout<<record<<endl;
					res += string(record);
					res += string("\n");
					break;
				}
			}
		}
	}
	res += divide;
	return res;
}
bool RecordBuilder::checkSelect(vector<Expr*>* select_list)
{

	if(select_list->at(0)->type == kExprStar)
		return true;

	bool* used = new bool[_cols];
	for(int i=0; i<_cols; i++)
		used[i] = false;
	for(unsigned int i=0; i<select_list->size(); i++)
	{
		if(select_list->at(i)->type == kExprCalculate)
			continue;
		if(select_list->at(i)->type != kExprColumnRef)
		{
			delete[] used;
			return false;
		}
		if(!_connect)
		{
			Expr* column = select_list->at(i);
			if(column->table != NULL && string(column->table) != _table_name)
				return false;
			int key = _key_table[string(column->name)] - 1;
			if(key == -1 || used[key] )
			{
				delete[] used;
				return false;
			}
			else
				used[key] = true;
		}
		else
		{
			Expr* column = select_list->at(i);
			char columnref[100];
			sprintf(columnref, "%s.%s", column->table, column->name);
			int key = _key_table[string(columnref)] - 1;
			if(key == -1 || used[key] )
			{
				delete[] used;
				return false;
			}
			else
				used[key] = true;
		}
	}
	delete[] used;
	return true;
}
KeyValue* RecordBuilder::getIndexVal(char* record, int colId)
{
	record += _offset[colId];
	switch(_key_type[colId])
	{
		case ColumnDefinition::INT:
		{	
			int64_t val = *((int64_t*)record);
			IntegerKeyValue *key = new IntegerKeyValue(val);
			return key;
		}
		case ColumnDefinition::DOUBLE:
		{
			double val = *((double*)record);
			DoubleKeyValue *key = new DoubleKeyValue(val);
			return key;
		}
		case ColumnDefinition::STRING:
		{
			StringKeyValue *key = new StringKeyValue(record);
			return key;
		}
	}
}
bool RecordBuilder::addIndex(int colId)
{
	if(_primary_key == -1)
	{
		vector<int>::iterator it = find(_key_index.begin(), _key_index.end(), colId);
		if(it == _key_index.end() && colId != 0)
		{
			_key_index.push_back(colId);
			return true;
		}
	}
	else
	{
		vector<int>::iterator it = find(_key_index.begin(), _key_index.end(), colId);
		if(it == _key_index.end())
		{
			_key_index.push_back(colId);
			return true;
		}
	}
	return false;
}
bool RecordBuilder::addIndex(const char* column)
{
	int colId = _key_table[string(column)]-1;
	if( colId != -1)
	{
		return addIndex(colId);
	}
	else
		return false;
}
bool RecordBuilder::dropIndex(const char* column)
{
	int colId = _key_table[string(column)]-1;
	if( colId == -1)
		return false;
	if(_primary_key == -1)
	{
		vector<int>::iterator it = find(_key_index.begin(), _key_index.end(), colId);
		if(it != _key_index.end() && colId != 0)
		{
			_key_index.erase(it);
			return true;
		}
	}
	else
	{
		vector<int>::iterator it = find(_key_index.begin(), _key_index.end(), colId);
		if(it != _key_index.end() && colId != _primary_key)
		{
			_key_index.erase(it);
			return true;
		}
	}
	return false;
}
vector<SelectOpt>*  RecordBuilder::getSelectOpt(vector<Expr*>* select_list)
{
	vector<SelectOpt>* select_opt = new vector<SelectOpt>();
	for(vector<Expr*>::iterator it = select_list->begin(); it != select_list->end();)
	{
		if((*it)->type == kExprCalculate)
		{
			if(!_connect)
			{
				Expr* cal = *it;
				Expr* column = (*it)->expr;
				//cout<<"aaa: "<<column->name<<endl;
				if(column->table != NULL && string(column->table) != _table_name)
					return NULL;
				int key = _key_table[string(column->name)] - 1;
				if(key == -1)
					return NULL;
				if(_key_type[key] == ColumnDefinition::STRING)
					return NULL;
				double val;
				SelectOpt::Option opt;
				if(cal->op_type == Expr::SUM)
				{
					val = 0;
					opt = SelectOpt::SUM;
				}
				else if(cal->op_type == Expr::AVG)
				{
					val = 0;
					opt = SelectOpt::AVG;
				}
				else if(cal->op_type == Expr::MAX)
				{
					val = -999999999;
					opt = SelectOpt::MAX;
				}
				else if(cal->op_type == Expr::MIN)
				{
					val = 9999999999;
					opt = SelectOpt::MIN;
				}
				select_opt->push_back(SelectOpt(key, opt, val, _key_name[key], _key_type[key]));
			}
			it = select_list->erase(it);
		}
		else
			++it;
	}
	return select_opt;
}
double RecordBuilder::getSelectVal(char* record, int colId)
{
	record += _offset[colId];
	if(_key_type[colId] == ColumnDefinition::INT)
		return double(*((int64_t*)record));
	else
		return *((double*)record); 
}
