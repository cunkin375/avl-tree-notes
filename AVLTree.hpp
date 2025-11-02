#include <memory>


template<typename T>
class AVLTree 
{
private:
    struct Node_
    {
        std::unique_ptr<T> data_;
        uint32_t height_;
        Node_* left_;
        Node_* right_;

        Node_(T incoming_data) : 
            data_(incoming_data), 
            height_(0),
            left_(nullptr), right_(nullptr)
        {
        }
    };

public:
    // TODO: Fix constructor
    AVLTree(T value) : root_(insert()) 
    {
    }
    ~AVLTree();

    T remove_value(std::unique_ptr<T> value);

    void check_tree() const;
    void insert();

private:
    // rebalance takes in a unique_ptr reference because it shuffles pointers within the AVL Tree
    // source: Herb Sutter "Back to the Basics! Essentials of Modern C++ Style"
    std::unique_ptr<Node_> rebalance(std::unique_ptr<Node_>& root);

    Node_* find_delete_ptr(Node_& root);
    Node_* max_left(Node_& root);

    void delete_node();
    void update_height();

    bool is_leaf_node(Node_& root) const;
    bool has_two_children(Node_& root) const;

private:
    std::unique_ptr<Node_> root_;
};
