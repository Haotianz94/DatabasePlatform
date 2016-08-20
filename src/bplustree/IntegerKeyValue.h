#ifndef __INTEGERKEYVALUE__H__
#define __INTEGERKEYVALUE__H__

#include <string.h>
#include "KeyValue.h"

class IntegerKeyValue : public KeyValue
{
public:
	IntegerKeyValue(long long x) : val(x)
	{}
	IntegerKeyValue(const unsigned char *s)
	{
		val = *((long long*)(s + 4));
		magicKey = *((int*)s);
	}
	virtual int compare(const KeyValue *b) const
	{
		if (val < ((IntegerKeyValue*)b)->val)
			return -1;
		if (val == ((IntegerKeyValue*)b)->val)
			return 0;
		return 1;
	}
	virtual void toCharArray(unsigned char* s) const
	{
		memcpy((char*)s, &magicKey, 4);
		memcpy(s + 4, &val, sizeof(long long));
	}
	
	long long val;
};

#endif