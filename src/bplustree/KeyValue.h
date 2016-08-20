#ifndef __KEYVALUE__H__
#define __KEYVALUE__H__

// TODO : neet to change to long long.
#define KEYTYPE_INTEGER 1
#define KEYTYPE_STRING 2
#define KEYTYPE_DOUBLE 3
// etcetc...

class KeyValue
{
public:
    // this < b returns -1;  this == b returns 0; this > b returns 1.
    virtual int compare(const KeyValue *b) const = 0;
    virtual int compWithMagicKey(const KeyValue *b) const;
    void setMagicKey();
    virtual void toCharArray(unsigned char* s) const = 0;
    static KeyValue* fromCharArray(const unsigned char *s, int type);

	int magicKey;
};

#endif
