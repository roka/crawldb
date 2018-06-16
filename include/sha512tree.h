#ifndef __SHA512_TREE_H__
#define __SHA512_TREE_H__

#include <stdint.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define LEAF_LEFT 0
#define LEAF_RIGHT 1

struct sha512tree {
        uint64_t num;
        struct sha512tree *left;
        struct sha512tree *right;
};

typedef struct sha512tree sha512tree;

sha512tree *new_leaf();
int sha512tree_contains(sha512tree *tree, unsigned char *hexdigest);
int sha512tree_add(sha512tree *tree, unsigned char *hexdigest);
int sha512tree_del(sha512tree *tree, unsigned char *hexdigest);

#endif
