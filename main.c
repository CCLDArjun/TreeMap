#include <assert.h>
#include <printf.h>
#include "TreeMap.h"

void test();

int main(int argc, const char *argv[]) {
    test();
}

void test() {
    TreeMap *map = malloc(sizeof(TreeMap));

    Node *n = TM_set(map, 6, 7);
    Node *e = TM_set(map, 10, 9);

    assert(n == map->head);
    assert(e == map->head->right);
    assert(TM_get(map, 10).val == 9);

    TM_set(map, 10, 5);
    assert(TM_get(map, 10).val == 5);

    TreeMapVal retd = TM_get(map, 110);
    assert(retd.err == KeyDoesNotExist);
    assert(map->head->right != map->head->right->right);

    TreeMapVal ret = TM_delete(map, 10);
    assert(ret.val == 5);
    assert(map->head->right == NULL);

    printf("tests passed!!\n");
    TM_free(map);
}

