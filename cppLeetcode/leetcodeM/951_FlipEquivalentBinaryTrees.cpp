/*
 
 # 951. Flip Equivalent Binary Trees


 # For a binary tree T, we can define a flip operation as follows: choose any node, and swap the left and right child subtrees.

 # A binary tree X is flip equivalent to a binary tree Y if and only if we can make X equal to Y after some number of flip operations.

 # Write a function that determines whether two binary trees are flip equivalent.  The trees are given by root nodes root1 and root2.


 # Example 1:

 # Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
 # Output: true
 # Explanation: We flipped at nodes with values 1, 3, and 5.
 # Flipped Trees Diagram


 # Note:

 # Each tree will have at most 100 nodes.
 # Each value in each tree will be a unique integer in the range [0, 99].
 
 
 */


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 
class FlipEquiv {
    
public:
    
    bool search(TreeNode* n1, TreeNode* n2) {
        
        if (!n1 && !n2)
            return true;
        
        if ((!n1 && n2) || (n1 && !n2))
            return false;
        
        if (n1->val != n2->val)
            return false;
        
        return search(n1->left, n2->right) && search(n1->right, n2->left) || search(n1->left, n2->left) && search(n1->right, n2->right);
    }
    
    bool doit(TreeNode* root1, TreeNode* root2) {
        
        return search(root1, root2);
    }
};


void test_951_flip_equivalent_binary_trees() {
    
}
