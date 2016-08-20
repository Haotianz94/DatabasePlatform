#ifndef __DOUBLEKEYVALUE__H__
#define __DOUBLEKEYVALUE__H__

#include <string.h>
#include "KeyValue.h"

class DoubleKeyValue : public KeyValue
{
public:
	DoubleKeyValue(double x) : val(x)
	{}
	DoubleKeyValue(const unsigned char *s)
	{
		val = *((double*)(s + 4));
		magicKey = *((int*)s);
	}
	virtual int compare(const KeyValue *b) const
	{
		if (val < ((DoubleKeyValue*)b)->val)
			return -1;
		if (val == ((DoubleKeyValue*)b)->val)
			return 0;
		return 1;
	}
	virtual void toCharArray(unsigned char* s) const
	{
		memcpy((char*)s, &magicKey, 4);
		memcpy(s + 4, &val, sizeof(double));
	}
	
	double val;
};

#endif
