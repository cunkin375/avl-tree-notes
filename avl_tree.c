#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define NULLPTR -1

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

int32_t maximum(int32_t a, int32_t b)
{
    return (a > b)? a : b;
}


node* new_node(int32_t val)
{
    node* result = (node*)malloc(sizeof(node));
    result->data = 0;
    if (val) result->data = val;
    result->height = 0;
    result->left = NULL;
    result->right = NULL;
    return result;
}

node* insert_tree_node(node* root, int32_t val)
{
    if (root == NULL) return new_node(val);
    if (val < root->data) 
        root->left = insert_tree_node(root->left, val); 
    else // val >= root->data
        root->right = insert_tree_node(root->right, val); 
    root = rebalance(root);
    update_height(root);
    return root;
}

node* rebalance(node* root)
{
    // base case
    if (!root) return NULL;

    int32_t left_height = (root->left)? root->left->height : NULLPTR;
    int32_t right_height = (root->right)? root->right->height : NULLPTR;

    // check if already balanced
    if (abs(left_height - right_height) <= 1) return root;

    // nodes used for rebalancing
    node* tempA = NULL;
    node* tempB = NULL;
    node* tempC = NULL;
    node* subT0 = NULL;
    node* subT1 = NULL;
    node* subT2 = NULL;
    node* subT3 = NULL;

    // left is too tall
    if (left_height > right_height)
    {

        int32_t left_left_height = (root->left->left)? root->left->left->height : NULLPTR;
        int32_t left_right_height = (root->left->right)? root->left->right->height : NULLPTR;

        // left-left case
        if (left_left_height >= left_right_height)
        {
            tempC = root;
            tempB = root->left;
            tempA = root->left->left;
            subT1 = tempA->right;
            subT2 = tempB->right;
        } 
        // left-right case
        else 
        {
            tempA = root->left;
            tempB = root->left->right;
            tempC = root;
            subT1 = tempB->left;
            subT2 = tempB->right;
        }

    }

    // right is too tall
    else 
    {

        int32_t right_right_height = (root->right->right)? root->right->right->height : NULLPTR;
        int32_t right_left_height = (root->right->left)? root->right->left->height : NULLPTR;

        // right left case
        if (right_left_height > right_right_height)
        {
            tempA = root;
            tempB = root->right->left;
            tempC = root->right;
            subT1 = tempB->left;
            subT2 = tempB->right;
        }

        // right right case
        else 
        {
            tempA = root;
            tempB = root->right;
            tempC = root->right->right;
            subT1 = tempB->left;
            subT2 = tempC->left;
        }

    }
    
    subT0 = tempA->left;
    subT3 = tempC->right;

    // form b tree at top
    tempB->left = tempA;
    tempB->right = tempC;

    // attach subtrees
    tempA->left = subT0;
    tempA->right = subT1;
    tempC->left = subT2;
    tempC->right = subT3;

    // update heights in order
    update_height(tempA);
    update_height(tempC); 
    update_height(tempB); 

    // return new root
    return tempB;

} // end rebalance

void update_height(node* root)
{
    if (root == NULL) return;
    int32_t left_height = (root->left)? root->left->height : NULLPTR;
    int32_t right_height = (root->right)? root->right->height : NULLPTR;
    root->height = 1 + maximum(left_height, right_height);
}






