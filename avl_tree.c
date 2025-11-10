#include <stdio.h>
#include "avl_tree.h"

#define __DEBUG__

int main()
{
    int32_t init_value = 400;
    node* tree_top = new_node(init_value);

    for (size_t i = 0; i < 50; i++)
    {
        int32_t val = rand() % 800;
        tree_top = insert_tree_node(tree_top, val);
#ifdef __DEBUG__
        printf("Inserted %d\n", val);
#endif
    }

    // printf("Preorder traversal: ");
    // preorder(tree_top);
    // printf("\n");

    printf("Inorder traversal: ");
    inorder(tree_top);
    printf("\n");

    // printf("Postorder traversal: ");
    // postorder(tree_top);
    // printf("\n");

    printf("Deleted node right of: %d\n", delete_value(tree_top, init_value)->data);

    printf("Inorder traversal: ");
    inorder(tree_top);
    printf("\n");

    return 0;
}

int32_t maximum(int32_t a, int32_t b)
{
    return (a > b)? a : b;
}

bool is_leaf_node(node* root)
{
    return root->left == NULL && root->right == NULL;
}

bool has_two_children(node* root)
{
    return root->left != NULL && root->right != NULL;
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

node* max_left(node* root)
{
    node* temp = root->left;
    while (temp->right != NULL)
        temp = temp->right;
    return temp;
}

node* rebalance(node* root)
{
    // base case
    if (!root) return NULL;

    int32_t left_height = (root->left)? root->left->height : -1;
    int32_t right_height = (root->right)? root->right->height : -1;

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

        int32_t left_left_height = (root->left->left)? root->left->left->height : -1;
        int32_t left_right_height = (root->left->right)? root->left->right->height : -1;

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

        int32_t right_right_height = (root->right->right)? root->right->right->height : -1;
        int32_t right_left_height = (root->right->left)? root->right->left->height : -1;

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
    int32_t left_height = (root->left)? root->left->height : -1;
    int32_t right_height = (root->right)? root->right->height : -1;
    root->height = 1 + maximum(left_height, right_height);
}

// ====== Deletion Functions =============================================================

node* delete_value(node* root, int32_t value)
{
    node* remove_ptr = find_delete_ptr(root, value);
    if (remove_ptr == NULL) return root; // value not found
    return delete_node(root, remove_ptr);
}

node* find_delete_ptr(node* root, int32_t value)
{
    if (root == NULL) return NULL;
    if (value < root->data) return find_delete_ptr(root->left, value);
    else if (value > root->data) return find_delete_ptr(root->right, value);
    else return root; // value found
}

node* delete_node(node* root, node* delete_ptr)
{
    // extra measure
    if (root == NULL) return NULL;

    int32_t delete_value = delete_ptr->data;

    if (root == delete_ptr)
    {
        if (is_leaf_node(root))
        {
            free(delete_ptr);
            return NULL;
        }
        else if (has_two_children(root))
        {
            node* temp = max_left(root);

            int32_t save_value = temp->data;

            delete_ptr->left = delete_node(delete_ptr->left, temp);

            delete_ptr->data = save_value;

            // rebalance and update
            delete_ptr = rebalance(root);
            update_height(root);

            return delete_ptr;
        }
        else // one child case
        {
            node* return_value = (root->left != NULL) ? root->left : root->right;
            free(root);
            return return_value;
        }
    }

    // go left
    if (delete_value < root->data)
        root->left = delete_node(root->left, delete_ptr);
    else // go right
        root->right = delete_node(root->right, delete_ptr);

    update_height(root);

    return root;
} // end delete_node

// ====== Traversal Functions ============================================================

void postorder(node* root)
{
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void inorder(node* root)
{
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(node* root)
{
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

