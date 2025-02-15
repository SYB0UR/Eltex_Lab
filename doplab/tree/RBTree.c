#define _GNU_SOURCE
#include <string.h>
#include <stdio.h> 
#include "RBTree.h"

static RBNode* rb_create_node(RBTree* tree, const char* name, int is_dir) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    if (node == NULL) {
        perror("Failed to allocate memory for node");
        return NULL;
    }
    node->name = strdup(name);
    if (node->name == NULL) {
        perror("Failed to allocate memory for node name");
        free(node);
        return NULL;
    }
    node->is_dir = is_dir;
    node->left = node->right = node->parent = tree->nil;
    node->color = RED;
    return node;
}

static void rb_destroy_node(RBTree* tree, RBNode* node) {
    if (node != tree->nil) {
        free(node->name);
        free(node);
    }
}

RBTree* rb_create() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    if (tree == NULL) {
        perror("Failed to allocate memory for tree");
        return NULL;
    }
    tree->nil = (RBNode*)malloc(sizeof(RBNode));
    if (tree->nil == NULL) {
        perror("Failed to allocate memory for nil node");
        free(tree);
        return NULL;
    }
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    return tree;
}

void rb_destroy(RBTree* tree) {
    rb_clear(tree);
    free(tree->nil);
    free(tree);
}

void rb_insert(RBTree* tree, const char* name, int is_dir) {
    if (name == NULL) return;
    RBNode* z = rb_create_node(tree, name, is_dir);
    if (z == NULL) return; 

    RBNode* y = tree->nil;
    RBNode* x = tree->root;
    while (x != tree->nil) {
        y = x;
        if (strcmp(z->name, x->name) < 0) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == tree->nil) {
        tree->root = z;
    }
    else if (strcmp(z->name, y->name) < 0) y->left = z;
    else y->right = z;
    z->left = z->right = tree->nil;

    z->color = BLACK;
}

static void rb_inorder(RBNode* node, RBNode** array, int* index, RBNode* nil) {
    if (node != nil) {
        rb_inorder(node->left, array, index, nil);
        if (array != NULL) array[(*index)++] = node;
        else (*index)++;
        rb_inorder(node->right, array, index, nil);
    }
}

RBNode* rb_get_index(RBTree* tree, int index) {
    int size = rb_size(tree);
    if (index < 0 || index >= size) return tree->nil;
    RBNode** array = (RBNode**)malloc(size * sizeof(RBNode*));
    int current_index = 0;
    rb_inorder(tree->root, array, &current_index, tree->nil);
    RBNode* node = array[index];
    free(array);
    return node;
}

int rb_size(RBTree* tree) {
    int size = 0;
    rb_inorder(tree->root, NULL, &size, tree->nil);
    return size;
}

void rb_clear_node(RBTree* tree, RBNode* node) {
    if (node != tree->nil) {
        rb_clear_node(tree, node->left);
        rb_clear_node(tree, node->right);
        rb_destroy_node(tree, node);
    }
}

void rb_clear(RBTree* tree) {
    rb_clear_node(tree, tree->root);
    tree->root = tree->nil;
}