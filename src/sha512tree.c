#include <openssl/sha.h>
#include <stdlib.h>

#include "config.h"
#include "sha512tree.h"

sha512tree *new_leaf()
{
        sha512tree *leaf = (sha512tree*) malloc(sizeof(sha512tree));
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->num = 1;

        return leaf;
}

void set_leaf(sha512tree *tree, int bit) {
        if (bit == LEAF_RIGHT) {
                tree->right = new_leaf();
        } else {
                tree->left = new_leaf();
        }
}

int check_leaf(sha512tree *tree, int bit)
{
        return bit ?
                tree->right != NULL:
                tree->left != NULL;
}

sha512tree *check_uchar(sha512tree *tree, unsigned char ch, int set)
{
        int i,bit;

        for (i=0; i < 8; i++) {
                bit = CHECK_BIT(ch, i);

                /* check if the leaf is set and update if needed */
                if (!check_leaf(tree, bit)) {
                        if(!set) {
                                return NULL;
                        } else {
                                set_leaf(tree, bit);
                        }
                } else {
                        tree->num++;
                }

                /* move to next leaf */
                if (bit == LEAF_RIGHT) {
                        tree = tree->right;
                } else {
                        tree = tree->left;
                }
        }

        return tree;
}

int sha512tree_contains(sha512tree *tree, unsigned char *hexdigest)
{
        debug_print("sha512tree_contains start%c", '\n');

        int i;
        unsigned char hash[SHA512_DIGEST_LENGTH];
        sha512tree *tmp;


        SHA512(hexdigest, sizeof(hexdigest) - 1, hash);

        for (i=0; i < SHA512_DIGEST_LENGTH-1; i++) {
                tmp = check_uchar(tree, hash[i], 0);

                if (tmp == NULL) {
                        return 0;
                } else {
                        tree = tmp;
                }
        }

        debug_print("sha512tree_contains done%c", '\n');
        return 1;
}

int sha512tree_add(sha512tree *tree, unsigned char *hexdigest)
{
        int i;
        unsigned char hash[SHA512_DIGEST_LENGTH];

        SHA512(hexdigest, sizeof(hexdigest) - 1, hash);

        for (i=0; i < SHA512_DIGEST_LENGTH-1; i++) {
                tree = check_uchar(tree, hash[i], 0);
        }

        return 0;
}

int sha512tree_del(sha512tree *tree, unsigned char *hexdigest)
{
        return 1;
}
