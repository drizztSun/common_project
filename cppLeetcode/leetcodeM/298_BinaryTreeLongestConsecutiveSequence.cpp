/*
298. Binary Tree Longest Consecutive Sequence


Given the root of a binary tree, return the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path needs to be from parent to child (cannot be the reverse).

 

Example 1:


Input: root = [1,null,3,2,4,null,null,null,5]
Output: 3
Explanation: Longest consecutive sequence path is 3-4-5, so return 3.
Example 2:


Input: root = [2,null,3,2,null,1]
Output: 2
Explanation: Longest consecutive sequence path is 2-3, not 3-2-1, so return 2.
 

Constraints:

The number of nodes in the tree is in the range [1, 3 * 104].
-3 * 104 <= Node.val <= 3 * 104

*/

#include <functional>

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
class LongestConsecutive {

    /*
        298.Binary-Tree-Longest-Consecutive Sequence
        这是一道基本的用DFS递归的二叉树题。需要注意的细节是，对于左右子树的递归调用，需要在判断 root->val+1==root->left->val之前。

        对于这样的调用是错误的：

        if (root->left!=NULL && root->val+1==root->left->val)
        {
            res = max(res, DFS(root->left)+1);
        }
        因为这样的话，当左节点不是根节点的增1时，左节点将永远不会被调用DFS，这样的话，左子树可能有的最长增序列将不会被搜索到。

        if (root->left!=NULL)
        {
            int temp = DFS(root->left);
            if (root->val+1==root->left->val)
            res = max(res, temp+1);
            
        }
    
    */

    int result;
    
    int longestConsecutive(TreeNode* root) 
    {
        result=0;
        int x=DFS(root);
        return result;
    }
    
    int DFS(TreeNode* root)
    {
        if (root==NULL) return 0;
        
        int res=1;
        if (root->left!=NULL)
        {
            int temp = DFS(root->left);
            if (root->left->val == root->val+1)
                res = max(res, temp+1);
        }
        
        if (root->right!=NULL)
        {
            int temp = DFS(root->right);
            if (root->right->val == root->val+1)
                res = max(res, temp+1);
        }
        
        result = max(res,result);
        return res;
        
    }

public:

    int doit_(TreeNode* root) {

        int maxlen = 0;
        
        std::function<int(TreeNode*)> dfs = [&](TreeNode* p) {
            
            if (!p) return 0;
            
            int res = 1;
            
            if (p->left) {
                int l = dfs(p->left);
                if (p->val + 1 == p->left->val) {
                    res = std::max(res, l + 1);
                }
            }

            if (p->right) {
                int l = dfs(p->right);
                if (p->val + 1 == p->right->val) {
                    res = std::max(res, l + 1);
                }
            }
            
            maxlen = std::max(maxlen, res);
            
            return res;
        };

        dfs(root);
        return maxlen;
    }
};