#ifndef __FILESTRUCTUREUTIL__H__
#define __FILESTRUCTUREUTIL__H__

#define PAGETYPE_FIRSTPAGE 0
#define PAGETYPE_BTREE_NODE 1
#define PAGETYPE_BTREE_LEAF 2

void int2tribytes(int x, unsigned char* s);

#endif
