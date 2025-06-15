#ifndef AVL_TREE_H
#define AVL_TREE_H


struct AvlNode 
{
    int data_;
    AvlNode* left_;
    AvlNode* right_;
    int height_;

    AvlNode(int value)
        : data_(value), left_(nullptr), right_(nullptr), height_(0) {}
};


class AvlTree {
private:
    AvlNode* root_;

    void insert(AvlNode* node, int val);
    AvlNode* remove(AvlNode* node, int val);
    void printInOrder(AvlNode* node);
    void destroyTree(AvlNode* node);

    // AVL helpers
    int height(AvlNode* node);
    void LL_rotation(AvlNode*& A);
    void RR_rotation(AvlNode*& A);
    void LR_rotation(AvlNode*& A);
    void RL_rotation(AvlNode*& A);

public:
    AvlTree();
    ~AvlTree();

    void insert(int val);
    void remove(int val);
    void printInOrder();
};

#endif
