#ifndef AVL_Tree_H
#define AVL_Tree_H


// Struct will be node of the Tree
struct TreeNode
{ 
    TreeNode* leftChild; 
    TreeNode* rightChild; 
    int val; 
    int height; 
    TreeNode(int value); 

    TreeNode(int value, TreeNode* l, TreeNode* r);  

    ~TreeNode(); 
}; 

// Class represent tree stores TreeNodes in edges 
class AVL_Tree
{
    TreeNode* root; 
    public: 

    // class instructor destructor 
    AVL_Tree(); 
    ~AVL_Tree();

    // Insert into Tree 
    void insertNode(int value); 
    // Remove from Tree
    void removeNode(int value); 

    private: 
    void clearTree(TreeNode* &root); 
    TreeNode* createNode(int val); 
    TreeNode* insertNode(int value,TreeNode*&root); 
    TreeNode* removeNode(int value, TreeNode*&root); 
    TreeNode* rightRotate(TreeNode *root);
    TreeNode* leftRotate(TreeNode *root); 
    int getBF(TreeNode* root); 
    int getHeight(TreeNode* root); 
    int max(int a, int b); 
}; 

#endif 