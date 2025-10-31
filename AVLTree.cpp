#include <memory>

struct Node 
{
    int32_t key_;
    int32_t height_;
    Node* left_;
    Node* right_;

    Node(int32_t  incoming_key) : 
        key_(incoming_key), 
        height_(1),
        left_(nullptr), right_(nullptr)
    {
    }
};

class AVLTree 
{


};
