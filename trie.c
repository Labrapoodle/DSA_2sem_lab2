#include "trie.h"
#include "rbtree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct trie *trie_create()
{
    struct trie *te = (struct trie *)malloc(sizeof(struct trie));
    te->finished_flag = 0;
    te->value = '\0';
    te->rbt = &NIL;

    return te;
}

struct trie *trie_insert(struct trie *root, char *key, char value)
{
    struct trie *child;
    struct trie *node = root;
    while (*key != '\0')
    {

        child = trie_get_child(node, *key);

        if (child == NULL)
        {

            child = trie_create();
            trie_set_child(node, *key, child);
        }
        node = child;
        key++;
    }
    node->value = value;
    return node;
}

struct trie *trie_lookup(struct trie *root, char *key)
{

    struct trie *child;
    struct trie *node = root;
    while (*key != '\0')
    {

        child = trie_get_child(node, *key);
        if (child == NULL)
        {

            printf("Child is null %c\n", *key);
            return NULL;
        }
        node = child;
        key++;
    }
    if (node->value == '\0')
    {
        return NULL;
    }
    return node;
}

struct trie *lookup_for_parent(struct trie *root, char *key)
{
    struct trie *child;
    struct trie *node = root;
    while (*key != '\0')
    {

        child = trie_get_child(node, *key);
        if (child == NULL)
        {

            printf("Child is null %c\n", *key);
            return NULL;
        }
        node = child;
        key++;
    }
    return node;
}

void trie_delete(struct trie *root, char *key)
{
    struct trie *node = trie_lookup(root, key);

    struct trie *parent = NULL;
    int len = strlen(key);
    char copy_key[len + 1];
    strncpy(copy_key, key, len + 1);

    for (int i = 0; i < len - 1; i++)
    {
        printf("Input string: %s\n", copy_key);
        copy_key[len - i] = '\0';
        printf("Working string: %s\n", copy_key);
        parent = trie_get_parent(root, copy_key);

        struct rbtree *p_root = find_root(parent->rbt);

        if (rbtree_height(p_root) > 1)
        {
            printf("I is: %d\n", i);
            i = len + 1;
        }
        char last_of_key = *(copy_key + strlen(copy_key) - 1);

        rbtree_delete(p_root, last_of_key);

        free(node);

        node = parent;
    }
}

struct trie *trie_get_parent(struct trie *root, char *child_key)
{

    int substr_len = strlen(child_key) - 1;
    if (substr_len <= 0)
    {
        printf("Error with key length\n");
        return NULL;
    }

    char parent_key[substr_len + 1];
    strncpy(parent_key, child_key, substr_len);
    parent_key[substr_len] = '\0';

    struct trie *parent = lookup_for_parent(root, parent_key);
    if (parent == NULL)
    {
        printf("Error in get_parent. Parent is null\n");
    }
    // strncpy(child_key, parent_key, strlen(child_key));
    return parent;
}

void trie_set_child(struct trie *node, char key_part, struct trie *child)
{
    if (node->rbt == &NIL)
    {
        node->rbt = (struct rbtree *)malloc(sizeof(struct rbtree));
        node->rbt = rbtree_create_node(key_part, child);
    }
    else
    {
        struct rbtree *local_root = find_root(node->rbt);
        rbtree_add(local_root, key_part, child);
    }
}

struct trie *trie_get_child(struct trie *node, char key_part)
{
    if (node->rbt == &NIL)
    {
        return NULL;
    }
    struct rbtree *local_root = find_root(node->rbt);
    struct rbtree *rbtree_node = rbtree_lookup(local_root, key_part);
    if (rbtree_node == &NIL)
    {
        return NULL;
    }
    return rbtree_node->value;
}

void tree_traverse_in_order(struct rbtree *root)
{
    if (root != &NIL)
    {
        tree_traverse_in_order(root->left);
        trie_delete_all(root->value);
        struct rbtree *root_root = find_root(root->value->rbt); // I gave up on naming, sorry
        rbtree_free(root_root);
        free(root->value);
        tree_traverse_in_order(root->right);
    }
}

void trie_delete_all(struct trie *root)
{
    if (root->rbt != &NIL)
    {
        struct rbtree *rb_root = find_root(root->rbt);
        tree_traverse_in_order(rb_root);
    }
}
