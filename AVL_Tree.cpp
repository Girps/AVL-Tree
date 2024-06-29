#include "AVL_Tree.h"
#include <exception>

TreeNode::TreeNode(int value, TreeNode* l, TreeNode* r): val{value}, height{0}, leftChild{l},rightChild{r} {}

TreeNode::TreeNode(int value): val{value} , height{1} , leftChild{nullptr} , rightChild{nullptr}
{}

TreeNode::~TreeNode(){}

// Constructor
AVL_Tree::AVL_Tree(): root{nullptr}{}
// Destructor 
AVL_Tree::~AVL_Tree() 
{
    // Destruct each root
    if (root != nullptr)
    {
        clearTree(this->root);
    } 
}

// Public call to insert node into the tree
void AVL_Tree::insertNode(int value)
{
    this->root = insertNode(value,this->root); 
}

// Insert node into tree 
TreeNode* AVL_Tree::insertNode(int value, TreeNode*& root)
{
    // if root is nullptr 
    if(root == nullptr)
    {
        root = createNode(value);
        return root; 
    }
    else
    {
        if(root->val > value)
        {
            root->leftChild =  insertNode(value,root->leftChild);  
        }
        else
        {
            root->rightChild = insertNode(value,root->rightChild); 
        }
    }
        // Normal BST insertion done

        // Update height of ancestor 
        root->height = max(getHeight(root->leftChild), getHeight(root->rightChild) ) + 1; 

        // get BF
        int bf = getBF(root); 

        // Use BF to determine which case

        // left left case
        if(bf > 1 && value < root->leftChild->val )
        {
            // Right rot current node
            return this->rightRotate(root); 
        }

        // left right case 
        if (bf> 1 && value > root->leftChild->val )
        {
            // Left rot child and Right current node 
            root->leftChild = leftRotate(root->leftChild);
            return  rightRotate(root); 
        }

        // right right case
        if(bf < -1 && value > root->rightChild->val)
        {
            // Left rot current node
            return leftRotate(root); 
        }

        // right left case
        if(bf < -1 && value < root->rightChild->val)
        {
            // right on current and left on child
             root->rightChild = rightRotate(root->rightChild); 
             return leftRotate(root); 
        }

        // Done now return root
        return root; 
}

TreeNode* AVL_Tree::rightRotate(TreeNode* root)
{
    TreeNode* leftRoot = root->leftChild; 
    TreeNode* Tn = leftRoot->rightChild; 

    leftRoot->rightChild= root; 
    root->leftChild = Tn; 

    // make sure update root first
    root->height = max(getHeight(root->leftChild),  getHeight(root->rightChild) ) + 1;
    leftRoot->height = max(getHeight(leftRoot->leftChild),  getHeight(leftRoot->rightChild) ) + 1;

    // new root
    return leftRoot; 
}


TreeNode* AVL_Tree::leftRotate(TreeNode* root)
{
    TreeNode* rightRoot = root->rightChild; 
    TreeNode* Tn = rightRoot->leftChild;

    rightRoot->leftChild = root; 
    root->rightChild = Tn; 

    // make sure to update the root first otherwise incorrect root height
    root->height = max(getHeight(root->leftChild),  getHeight(root->rightChild) ) + 1;
    rightRoot->height = max(getHeight(rightRoot->leftChild),  getHeight(rightRoot->rightChild) ) + 1;
    // new root
    return rightRoot; 

}


int AVL_Tree::max( int a, int b)
{
    return a > b ? a : b; 
}

// Public call to delete node from tree
void AVL_Tree::removeNode(int value)
{
    removeNode(value,this->root); 
}

// Delete node in tree 
TreeNode* AVL_Tree::removeNode(int value, TreeNode*&root)
{
    // if root is empty throw exception 
    if(root == nullptr)
    {
        return nullptr; 
    }
  
    // check for value
    if( root->val == value)
    {   
        // 3 cases
        if(root->leftChild == nullptr && root->rightChild == nullptr)
        {
            // case 1 leaf node
            delete root; 
            return nullptr; 
        }
        else if(root->leftChild == nullptr)
        {
            // only right child case
            TreeNode* cursor = root->rightChild; 
            delete root; 
            return cursor; 
        }
        else if(root->rightChild == nullptr)
        {
            // only left child case
            TreeNode* cursor = root->leftChild; 
            delete root; 
            return cursor;
        }
        else
        {
            // 2 children special case get successor 
            return nullptr; 
        }
    }
    else if(root->val > value)
    {
        root->leftChild = removeNode(value,root->leftChild); 
        return root; 
    }
    else 
    {
        root->rightChild =  removeNode(value, root->rightChild);
        return root;  
    }
}


// Create Node
TreeNode* AVL_Tree::createNode(int value)
{   
    return new TreeNode(value); 
}

// Iterate through each node and delete each node in postOrder 
void AVL_Tree::clearTree(TreeNode* &root)
{
    if(root == nullptr)
    {
        return; 
    }
    else
    {
        clearTree(root->leftChild); 
        clearTree(root->rightChild); 
        delete root; 
        root = nullptr; 
    }
}

int AVL_Tree::getBF(TreeNode *root)
{
    if(root == nullptr)
    {
        return 0; 
    }
    else
    {
        return getHeight(root->leftChild) - getHeight(root->rightChild); 
    }
}

int AVL_Tree::getHeight(TreeNode* root)
{
    if(root == nullptr)
    {
        return 0;
    }
    else
    {
        return root->height; 
    }
}