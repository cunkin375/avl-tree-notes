#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/*
 * An AVL tree is a balanced binary tree where:
 *  > the height of the left subtree may differ from 
 *    the height of the right subtree by AT MOST 1
 */ 

typedef struct treenode {
    int32_t data;
    int32_t height;
    struct treenode* left;
    struct treenode* right;
} node;

/* helper functions */
void check_tree(node* root);
void free_tree(node* root);
void update_height(node* root);
void preorder(node* root);
void postorder(node* root);
void inorder(node* root);

node* new_node(int32_t val);
node* insert_tree_node(node* root, int32_t val);
node* max_left(node* root);
node* rebalance(node* root);

int32_t maximum(int32_t a, int32_t b);
bool is_leaf_node(node* root);
bool has_two_children(node* root);

/* delete functions */
node* delete_value(node* root, int32_t value);
node* find_delete_ptr(node* root, int32_t value);
node* delete_node(node* root, node* remove_ptr);

/* tests */
void small_insert();
void many_insert_bad_case();
void small_delete();
void many_inserts_and_delete_bad_case();

