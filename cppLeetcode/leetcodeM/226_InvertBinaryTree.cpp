/*
226. Invert Binary Tree


Given the root of a binary tree, invert the tree, and return its root.

 

Example 1:


Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]
Example 2:


Input: root = [2,1,3]
Output: [2,3,1]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {

    /*
    
        226.Invert-Binary-Tree
        本题有两种做法。常规的递归想法是：

        root->left=invert(root->right);
        root->right=invert(root->left);
        但注意上述的写法是有问题的，因为第一行里已经把root->left改变了，所以第二行就不成立了。所以应该用temp把invert(root->right)存起来，之后再传给root->left.

        另外一种就很巧妙：

        swap(root->left,root->right);
        root->left=invert(root->left);
        root->right=invert(root->right);
        注意代码第一行，作用是把整个根节点的左右子树都整体对换了。
    */

    TreeNode* invertTree(TreeNode* root) 
    {
        if (root==NULL) return NULL;
        TreeNode* temp=invertTree(root->right);
        root->right=invertTree(root->left);
        root->left=temp;
        return root;
    }

    TreeNode* invertTree(TreeNode* root) 
    {
        if (root==NULL) return NULL;
        
        std::swap(root->left,root->right);
        
        root->left = invertTree(root->left);
        root->right = invertTree(root->right);
        
        return root;
    }

public:
    TreeNode* invertTree(TreeNode* root) {
        
        std::function<void(TreeNode*)> dfs = [&](TreeNode* p) {
            
            if (!p) return;
            
            std::swap(p->left, p->right);
            
            dfs(p->left), dfs(p->right);
        };
        
        dfs(root);
        return root;
    }
};