#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

typedef struct Node Node;
struct Node {
    Node *left;
    Node *right;
    long key;
    long value;
};

typedef struct TreeMapVal TreeMapVal;
typedef enum {
    NoErr, KeyDoesNotExist, DelErr
} Err;

struct TreeMapVal {
    Err err; 
    long val;
};

typedef struct {
    Node *head;
    unsigned int key_type;
    unsigned int value_type;
} TreeMap;


Node *TM_set(TreeMap *op, long key, long val);
TreeMapVal TM_get(TreeMap *op, long key);
TreeMapVal TM_delete(TreeMap *op, long key);
void TM_free(TreeMap *op);





// static Node **TM_find_before(Node **curr, void *key, TreeMap *tr




