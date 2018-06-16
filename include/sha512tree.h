#ifndef __SHA512_TREE_H__
#define __SHA512_TREE_H__

int sha512tree_contains(char *hexdigest);
int sha512tree_add(char *hexdigest);
int sha512tree_del(char *hexdigest);

#endif
