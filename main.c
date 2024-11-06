#include "rbtree.h"
#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    struct trie *trie_root = trie_create();

    trie_insert(trie_root, "habanga", 5);

    trie_delete(trie_root, "habanga");
    trie_root->rbt = find_root(trie_root->rbt);
    printf("Height: %d\n", rbtree_height(trie_root->rbt->value->rbt));

    printf("Deleted\n");
    // trie_delete_all(trie_root);
    rbtree_free(trie_root->rbt);
    free(trie_root);
    /*
    if (shit->rbt != &NIL)
    {
        struct rbtree *root = find_root(shit->rbt);
        rbtree_free(root);
    }
    free(shit);
    if (trie_root->rbt != &NIL)
    {
        struct rbtree *root = find_root(trie_root->rbt);
        rbtree_free(root);
    }
    free(trie_root);


    */

    return 0;
}
