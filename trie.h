#pragma once
#include "rbtree.h"

struct trie
{
    struct rbtree *rbt;
    char value;
    int finished_flag;
};

struct trie *trie_create();
struct trie *trie_insert(struct trie *root, char *key, char value);
struct trie *trie_lookup(struct trie *root, char *key);
struct trie *lookup_for_parent(struct trie *root, char *key);
void trie_delete(struct trie *root, char *key);
struct trie *trie_get_parent(struct trie *root, char *child_key);
void tree_traverse_in_order(struct rbtree *root);
void trie_set_child(struct trie *node, char key_part, struct trie *child);
struct trie *trie_get_child(struct trie *node, char key_part);
void trie_delete_all(struct trie *root);
// void trie_print(struct trie *root, int level);
