#ifndef RBTREE_H
#define RBTREE_H

#include <stdlib.h>
#include <string.h>

typedef enum { RED, BLACK } NodeColor;

typedef struct RBNode {
    char* name;
    int is_dir;
    struct RBNode* left, * right, * parent;
    NodeColor color;
} RBNode;

typedef struct {
    RBNode* root;
    RBNode* nil;
} RBTree;

RBTree* rb_create();
void rb_destroy(RBTree* tree);
void rb_insert(RBTree* tree, const char* name, int is_dir);
RBNode* rb_get_index(RBTree* tree, int index);
int rb_size(RBTree* tree);
void rb_clear(RBTree* tree);

#endif