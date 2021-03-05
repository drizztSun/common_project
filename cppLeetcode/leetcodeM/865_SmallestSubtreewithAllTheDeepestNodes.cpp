/*
865. Smallest Subtree with all the Deepest Nodes

Given the root of a binary tree, the depth of each node is the shortest distance to the root.

Return the smallest subtree such that it contains all the deepest nodes in the original tree.

A node is called the deepest if it has the largest depth possible among any node in the entire tree.

The subtree of a node is tree consisting of that node, plus the set of all descendants of that node.

Note: This question is the same as 1123: https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: We return the node with value 2, colored in yellow in the diagram.
The nodes coloured in blue are the deepest nodes of the tree.
Notice that nodes 5, 3 and 2 contain the deepest nodes in the tree but node 2 is the smallest subtree among them, so we return it.
Example 2:

Input: root = [1]
Output: [1]
Explanation: The root is the deepest node in the tree.
Example 3:

Input: root = [0,1,3,null,2]
Output: [2]
Explanation: The deepest node in the tree is 2, the valid subtrees are the subtrees of nodes 2, 1 and 0 but the subtree of node 2 is the smallest.
 

Constraints:

The number of nodes in the tree will be in the range [1, 500].
0 <= Node.val <= 500
The values of the nodes in the tree are unique.

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

class Solution {

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };


public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        
        int maxv = 0;
        TreeNode* res = root;
        
        
        std::function<int(TreeNode*, int)> dfs = [&](TreeNode* node, int depth) {
          
            if (!node) return 0;
            
            if (!node->left && !node->right) {
                if (depth > maxv) {
                    maxv = depth;
                    res = node;
                }
                return depth;
            }
            
            int l = dfs(node->left, depth+1), r = dfs(node->right, depth+1);
            
            int base = std::max(l, r);
            
            if (l == r && l == base && base >= maxv) {
                res = node;
                maxv = base;
            } 
            return base;
        };
        
        dfs(root, 0);
        
        return res;
    }

    
    TreeNode* lcaDeepestLeaves(TreeNode* root) {

        if (!root) return root;
        
        std::function<int(TreeNode*)> countDepth = [&](TreeNode* node) -> int{
            if(node == NULL ) return 0 ; 
            return 1 + std::max(countDepth(node->left), countDepth(node->right));
        };

        int l = countDepth(root->left);
        int r = countDepth(root->right);
        
        if(l == r) return root;

        return (l > r) ? lcaDeepestLeaves(root->left) : lcaDeepestLeaves(root->right) ;
    }

    TreeNode* lcaDeepestLeaves(TreeNode* root) {

        int deepest = 0;
        TreeNode* ans;

        std::function<int(TreeNode*, int)> dfs = [&](TreeNode* root, int deep) {
            deepest = std::max(deepest, deep);
            
            if (!root) {
                return deep;
            }
            
            int left = dfs(root->left, deep + 1);
            int right = dfs(root->right, deep + 1);
            
            if (left == deepest && right == deepest) {
                ans = root;
            }
            
            return std::max(left, right);
        };

        dfs(root, 0);
        
        return ans;
    }
    

};