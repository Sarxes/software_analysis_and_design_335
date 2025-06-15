#include "binary_search_tree.h"

AvlTree::AvlTree() : root_(nullptr) {}

AvlTree::~AvlTree() {
    destroyTree(root_);
}

void AvlTree::destroyTree(AvlNode* node) {
    if (node) {
        destroyTree(node->left_);
        destroyTree(node->right_);
        delete node;
    }
}

void AvlTree::insert(int val) {
    root_ = insert(root_, val);
}

void AvlTree::remove(int val) {
    root_ = remove(root_, val);
}

void AvlTree::printInOrder() {
    printInOrder(root_);
    std::cout << std::endl;
}

void AvlTree::printInOrder(AvlNode* node) {
    if (node) {
        printInOrder(node->left_);
        std::cout << node->data_ << " ";
        printInOrder(node->right_);
    }
}

int AvlTree::height(AvlNode* node) {
    return node == nullptr ? -1 : node->height_;
}

AvlTree::void insert(const Comparable& x, AvlNode*& t) const 
{
    if (t == nullptr) 
        t = new AvlNode(x, nullptr, nullptr);
    
    else if (x < t->element) 
    {
        insert(x, t->left);
        
        //this part finds the A(first unbalanced node from the way up) from image
        // if x < t->element, that means the first turn was an l 
        if (height(t->left) - height(t->right) == 2) 
        {
            //this part finds the second turn, 
            if (x < t->left->element)
                LL_rotation(t);
            else
                LR_rotation(t);
        }
    }

    //symetric reasoning to above
    else if (t->element < x) 
    {
        insert(x, t->right);

        if (height(t->right) - height(t->left) == 2) 
        {
            if (t->right->element < x)
                RR_rotation(t);
            else
                RL_rotation(t);
        }
    }

    else 
    {
        // Duplicate; do nothing
    }

    //update height of A
    t->height = std::max(height(t->left), height(t->right)) + 1;
}


remove ( const Comparable & x , AvlNode < Comparable > * & t )
{
if ( t == NULL )
// can 't delete from an empty tree
return ;
if ( x < t - > element ) {
// delete from the left subtree
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. 12
CSci 335 Software Design and Analysis 3
Chapter 4 Trees, Part 2
Prof. Stewart Weiss
remove ( x , t - > left ) ;
// check if the heights of the subtrees are now too different
if ( height ( t - > right ) - height ( t - > left ) == 2 ) // unbalanced
// right subtree too tall relative to left
// Which rotation to use depends on whether the left subtree
of the
// right subtree is larger , or the right of the right is
larger .
// If the right is larger we MUST use RR
if ( height (( t - > right ) -> right ) >= height (( t - > right ) -> left ) )
RR_rotation ( t ) ;
else
RL_rotation ( t ) ;
}
else if ( t - > element < x ) {
// delete from the right subtree
remove ( x , t - > right ) ;
if ( height ( t - > left ) - height ( t - > right ) == 2 ) // unbalanced
// left subtree too tall
if ( height (( t - > left ) -> left ) >= height (( t - > left ) -> right ) )
LL_rotation ( t ) ;
else
LR_rotation ( t ) ;
}
else { // delete this node
if (( t - > left != NULL ) && (t - > right != NULL ) ) { // two non - empty
subtrees
t - > element = findMin (t - > right ) -> element ;
remove (t - > element , t - > right ) ;
if ( height ( t - > left ) - height ( t - > right ) == 2 ) //
unbalanced
// left subtree too tall
if ( height (( t - > left ) -> left ) >= height (( t - > left ) -> right ) )
LL_rotation ( t ) ;
else
LR_rotation ( t ) ;
}
else {
AVLNode < Comparable >* OldNode = t ;
t = (t - > left != NULL ) ? t - > left : t - > right ;
delete OldNode ;
}
}
if ( NULL != t )
t - > height = max ( height ( t - > left ) , height ( t - > right ) ) + 1;

}

void AvlTree::LL_rotation(AvlNode*& A) {
    AvlNode* B = A->left_;
    A->left_ = B->right_;
    B->right_ = A;

    A->height_ = std::max(height(A->left_), height(A->right_)) + 1;
    B->height_ = std::max(height(B->left_), height(B->right_)) + 1;

    A = B;
}

void AvlTree::RR_rotation(AvlNode*& A) {
    AvlNode* B = A->right_;
    A->right_ = B->left_;
    B->left_ = A;

    A->height_ = std::max(height(A->left_), height(A->right_)) + 1;
    B->height_ = std::max(height(B->left_), height(B->right_)) + 1;

    A = B;
}

void AvlTree::LR_rotation(AvlNode*& A) {
    AvlNode* B = A->left_;
    AvlNode* C = B->right_;

    B->right_ = C->left_;
    A->left_ = C->right_;
    C->left_ = B;
    C->right_ = A;

    A->height_ = std::max(height(A->left_), height(A->right_)) + 1;
    B->height_ = std::max(height(B->left_), height(B->right_)) + 1;
    C->height_ = std::max(height(C->left_), height(C->right_)) + 1;

    A = C;
}

void AvlTree::RL_rotation(AvlNode*& A) {
    AvlNode* B = A->right_;
    AvlNode* C = B->left_;

    B->left_ = C->right_;
    A->right_ = C->left_;
    C->left_ = A;
    C->right_ = B;

    A->height_ = std::max(height(A->left_), height(A->right_)) + 1;
    B->height_ = std::max(height(B->left_), height(B->right_)) + 1;
    C->height_ = std::max(height(C->left_), height(C->right_)) + 1;

    A = C;
}
