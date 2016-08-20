#include "IntegerKeyValue.h"
#include "DoubleKeyValue.h"
#include "StringKeyValue.h"
#include "KeyValue.h"
#include <stdlib.h>

KeyValue* KeyValue :: fromCharArray(const unsigned char *s, int type)
{
    switch(type)
    {
    	case KEYTYPE_INTEGER:
    		return new IntegerKeyValue(s);
    	case KEYTYPE_STRING:
    		return new StringKeyValue(s);
    	case KEYTYPE_DOUBLE:
    		return new DoubleKeyValue(s);
    }
}

void KeyValue :: setMagicKey()
{
	magicKey = rand();
}

int KeyValue :: compWithMagicKey(const KeyValue *b) const
{
   	int ret = compare(b);
    if (ret)	return ret;
    if (magicKey < b->magicKey)
    	return -1;
    if (magicKey == b->magicKey)
    	return 0;
    return 1;
}
