/*
110. Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the left and right subtrees of every node differ in height by no more than 1.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: true
Example 2:


Input: root = [1,2,2,3,3,null,null,4,4]
Output: false
Example 3:

Input: root = []
Output: true
 

Constraints:

The number of nodes in the tree is in the range [0, 5000].
-10^4 <= Node.val <= 10^4
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

#include <functional>

class IsBalanced {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        110.Balanced-Binary-Tree
        将判断isBalanced(root)转为考察depth(root). 递归的过程中一旦发现depth(node->left)和depth(node->right)不合条件、或其中任何一个已经为-1，则depth(node)就直接返回-1。

            int depth(TreeNode* node)
            {
                if (node==NULL) return 0;
                
                int d1=depth(node->left);
                int d2=depth(node->right);
                if (d1==-1 || d2==-1 || abs(d1-d2)>1) 
                    return -1;
                else
                    return max(d1,d2)+1;
            }
        这样当depth(node)为正数时，就保证了该节点已经balanced。

            bool isBalanced(TreeNode* root) 
            {
                if (depth(root)==-1)
                    return false;
                else
                    return true;
            }
    */
    bool isBalanced(TreeNode* root) 
    {
        if (depth(root)==-1)
            return false;
        else
            return true;
    }
    
    int depth(TreeNode* node)
    {
        if (node==NULL) return 0;
        
        int d1=depth(node->left);
        int d2=depth(node->right);
        if (d1==-1 || d2==-1 || abs(d1-d2)>1) 
            return -1;
        else
            return std::max(d1,d2)+1;
    }

public:
    
    bool doit_(TreeNode* root) {

        std::function<int(TreeNode*)> dfs = [&](TreeNode* p) {
            
            if (!p) return 0;

            int l = dfs(p->left), r = dfs(p->right);

            if (l == -1 || r == -1 || abs(l - r) > 1) return -1;

            return std::max(l, r) + 1;
        };

        return dfs(root) != -1;
    }
};