#include "FileStructureUtil.h"

void int2tribytes(int x, unsigned char* s)
{
    for (int i = 0; i < 3; ++i, x >>= 8)
        s[2 - i] = x & 255;
}
