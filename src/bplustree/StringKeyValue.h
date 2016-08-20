#ifndef __STRINGKEYVALUE__H__
#define __STRINGKEYVALUE__H__

#include "KeyValue.h"
#include <string>
#include <string.h>

class StringKeyValue : public KeyValue
{
public:
	StringKeyValue(std::string x) : val(x)
	{}
	StringKeyValue(const unsigned char *s)
	{
		val = (char*)(s + 4);
		magicKey = *((int*)s);
	}
	virtual int compare(const KeyValue *b) const
	{
		return val.compare(((StringKeyValue*)b)->val);
	}
	virtual void toCharArray(unsigned char* s) const
	{
		memcpy((char*)s, &magicKey, 4);
		strcpy((char*)s + 4, val.c_str());
	}
	
	std :: string val;
};

#endif
