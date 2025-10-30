#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * An AVL tree is a balanced binary tree where:
 *  > the height of the left subtree may differ from 
 *    the height of the right subtree by AT MOST 1
 */ 

typedef struct treenode {
    int32_t data;
    struct treenode* left;
    struct treenode* right;
} node;

/* helper functions */
void check_tree(node* root);
void free_tree(node* root);
void update_height(node* root);
void preorder(node* root);
void postorder(node* root);

node* new_node(int32_t val);
node* insert_tree_node(node* root, int32_t val);
node* max_left(node* root);
node* rebalance(node* root);

int32_t max(int32_t a, int32_t b);
bool is_leaf_node(node* root);
bool has_two_children(node* root);

/* delete functions */
node* delete_value(node* root, int32_t value);
node* find_delete_ptr(node* root, int32_t value);
node* delete(node* root, node* delete_ptr);

/* tests */
void small_insert();
void many_insert_bad_case();
void small_delete();
void many_inserts_and_delete_bad_case();


int main()
{
    node* tree = insert_tree_node(tree, 10);
    int32_t val = 5;
    return 0;
}

int32_t max(int32_t a, int32_t b)
{
    return (a > b)? a : b;
}


node* new_node(int32_t val)
{
    node* result = malloc(sizeof(node));
    result->data = 0;
    if (val) result->data = val;
    result->left = NULL;
    result->right = NULL;
    return result;
}

node* insert_tree_node(node* root, int32_t val)
{
    if (root == NULL) return new_node(val);
    if (val < root->data) 
        root->left = insert_tree_node(root->left, val); 
    else 
        root->right = insert_tree_node(root->right, val); 
    root = rebalance(root);
    update_height(root);
    return root;
}

node* rebalance(node* root)
{

}
