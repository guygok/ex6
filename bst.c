#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

/*
 * Generic BST implementation.
 * - data is void* (generic pointer)
 * - ordering is decided by cmp(a,b)
 * - printing decided by print(data)
 * - freeing decided by freeData(data)
 *
 * Important: bstInsert DOES NOT free duplicates. Caller decides what to do.
 */

BST* createBST(int (*cmp)(void*, void*), void (*print)(void*), void (*freeData)(void*)) {
    BST* t = (BST*)malloc(sizeof(BST));
    if (!t) return NULL;
    t->root = NULL;
    t->compare = cmp;
    t->print = print;
    t->freeData = freeData;
    return t;
}

static BSTNode* createNode(void* data) {
    BSTNode* n = (BSTNode*)malloc(sizeof(BSTNode));
    if (!n) return NULL;
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

BSTNode* bstInsert(BSTNode* root, void* data, int (*cmp)(void*, void*)) {
    if (!root) return createNode(data);

    int c = cmp(data, root->data);
    if (c < 0) root->left = bstInsert(root->left, data, cmp);
    else if (c > 0) root->right = bstInsert(root->right, data, cmp);
    /* c == 0 => duplicate: do nothing, keep existing */
    return root;
}

void* bstFind(BSTNode* root, void* data, int (*cmp)(void*, void*)) {
    if (!root) return NULL;

    int c = cmp(data, root->data);
    if (c == 0) return root->data;
    if (c < 0) return bstFind(root->left, data, cmp);
    return bstFind(root->right, data, cmp);
}

/* We print with indentation by depth (matches examples showing tabs). */
static void inorderRec(BSTNode* root, void (*print)(void*), int depth) {
    if (!root) return;
    inorderRec(root->left, print, depth + 1);
    for (int i = 0; i < depth; i++) printf("\t");
    print(root->data);
    inorderRec(root->right, print, depth + 1);
}

static void preorderRec(BSTNode* root, void (*print)(void*), int depth) {
    if (!root) return;
    for (int i = 0; i < depth; i++) printf("\t");
    print(root->data);
    preorderRec(root->left, print, depth + 1);
    preorderRec(root->right, print, depth + 1);
}

static void postorderRec(BSTNode* root, void (*print)(void*), int depth) {
    if (!root) return;
    postorderRec(root->left, print, depth + 1);
    postorderRec(root->right, print, depth + 1);
    for (int i = 0; i < depth; i++) printf("\t");
    print(root->data);
}

void bstInorder(BSTNode* root, void (*print)(void*)) {
    inorderRec(root, print, 0);
}

void bstPreorder(BSTNode* root, void (*print)(void*)) {
    preorderRec(root, print, 0);
}

void bstPostorder(BSTNode* root, void (*print)(void*)) {
    postorderRec(root, print, 0);
}

void bstFree(BSTNode* root, void (*freeData)(void*)) {
    if (!root) return;
    bstFree(root->left, freeData);
    bstFree(root->right, freeData);
    if (freeData) freeData(root->data);
    free(root);
}

void freeBST(BST* tree) {
    if (!tree) return;
    bstFree(tree->root, tree->freeData);
    free(tree);
}
