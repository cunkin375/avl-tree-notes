#include <memory>


template<typename T>
class AVLTree 
{
private:
    typedef struct m_Node
    {
        std::unique_ptr<T> data;
        int32_t height;
        m_Node* left;
        m_Node* right;

        m_Node(T& incoming_data) 
            : data(incoming_data)
            , height(0)
            , left(nullptr), right(nullptr)
        {}

    } m_Node;

public:
    // TODO: Fix constructor
    AVLTree(T value);
    ~AVLTree();

    void remove_value(std::unique_ptr<T> value);

    void check_tree() const;
    void insert();

private:
    // rebalance takes in a unique_ptr reference because it shuffles pointers within the AVL Tree
    // source: Herb Sutter "Back to the Basics! Essentials of Modern C++ Style"
    std::unique_ptr<m_Node> rebalance(std::unique_ptr<m_Node>& root);

    m_Node* find_delete_ptr(m_Node* root);
    m_Node* find_max_left(m_Node* root);
    m_Node* find_min_right(m_Node* root);

    void delete_node();
    void update_height();
    void relabance();

    bool is_leaf_node(m_Node* root) const;
    bool has_two_children(m_Node* root) const;
};
