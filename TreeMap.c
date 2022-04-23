#include <assert.h>
#include "TreeMap.h"

static void free_nodes(Node *curr);
void TM_free(TreeMap *op) {
    free_nodes(op->head);
    free(op);
}

static void free_nodes(Node *curr) {
    if (curr == NULL)
        return;

    free_nodes(curr->left);
    free_nodes(curr->right);
    free(curr);
}

static Node **TM_find(Node **curr, long key, TreeMap *tr);
static TreeMapVal TM_del(Node **curr, long key, Node **to_delete);

TreeMapVal TM_delete(TreeMap *op, long key) {
    Node **to_delete;
    to_delete = malloc (sizeof(Node**));
    //*to_delete = malloc (sizeof(Node*));

    TreeMapVal ret = TM_del(&op->head, key, to_delete);
    
    //free(*to_delete);
    free(to_delete);
    return ret;
}

Node *find_leftmost(Node *curr) {
    if (curr == NULL)
        return curr;
    else if (curr->left == NULL)
        return curr;
    else
        return find_leftmost(curr->left);
}

static TreeMapVal handle_del(Node **to_delete, Node *parent) {
    assert(*to_delete != parent);
    assert((*to_delete)->right != *to_delete);
    assert(*to_delete == parent->left || *to_delete == parent->right);

    TreeMapVal ret = {NoErr,(*to_delete)->value};
    Node *replacement = find_leftmost(*to_delete);

    if (replacement == *to_delete) { // has no leftnodes
        replacement = (*to_delete)->right;
    }
    else {
        replacement->right = (*to_delete)->right;
    }

    if (parent->left == *to_delete) {
        parent->left = replacement;
    }
    else {
        parent->right = replacement;
    }


    assert((*to_delete)->right != *to_delete);
    assert(*to_delete != parent);
    free(*to_delete);

    return ret;
}

static TreeMapVal TM_del(Node **curr, long key, Node **to_delete) {
    TreeMapVal ret = {DelErr, 0};
    if (*curr == NULL)
        return ret;

    long k = (*curr)->key;
    if (k == key) {
        assert((*curr)->right != *curr);
        *to_delete = *curr;
        assert((*curr)->right != *curr);
        return ret;
    }
    else if (key > k) {
        ret = TM_del(&((*curr)->right), key, to_delete);
    }
    else if (key < k) {
        ret = TM_del(&((*curr)->left), key, to_delete);
    }

    if (*to_delete != NULL && ret.err != NoErr) {
        ret = handle_del(to_delete, *curr);
        *to_delete = NULL;
    }

    return ret;
}

Node *TM_set(TreeMap *op, long key, long val) {
    Node **to_insert = TM_find(&(op->head), key, op);

    if (*to_insert != NULL) {
        (*to_insert)->value = val;
        return *to_insert;
    }

    (*to_insert) = malloc(sizeof(Node));
    (*to_insert)->value = val;
    (*to_insert)->key = key;
    (*to_insert)->left = NULL;
    (*to_insert)->right = NULL;
    return *to_insert;
}

TreeMapVal TM_get(TreeMap *op, long key) {
    Node **found = (TM_find(&(op->head), key, op));
    TreeMapVal ret = {0};
    if (*found == NULL)
        ret.err = KeyDoesNotExist;
    else
        ret.val = (*found)->value;
    return ret;
}

Node TM_create(TreeMap *op) {
    
}

static Node **TM_find(Node **curr, long key, TreeMap *tr) {
    if (curr == NULL || *curr == NULL)
        return curr;
    long d = (*curr)->key;
    if (d == key)
        return curr;
    else if (key > d)
        return TM_find(&((*curr)->right), key, tr);
    else if (key < d)
        return TM_find(&((*curr)->left), key, tr);
    return NULL;
}

