/*
 
 # 1026. Maximum Difference Between Node and Ancestor

 # Given the root of a binary tree, find the maximum value V for which there exists different nodes A and B where V = |A.val - B.val| and A is an ancestor of B.

 # (A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.)


 # Example 1:


 # Input: [8,3,10,1,6,null,14,null,null,4,7,13]
 # Output: 7
 # Explanation:
 # We have various ancestor-node differences, some of which are given below :
 # |8 - 3| = 5
 # |3 - 7| = 4
 # |8 - 1| = 7
 # |10 - 13| = 3
 # Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.
 
 
 */

#include <vector>

struct TreeNode {
    int val;
    
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};


class MaxAncestorDiff {

public:
    
    void dfs(TreeNode* node, int& min, int& max, int& maxabs) {
        
        if (!node->left && !node->right) {
            min = node->val;
            max = node->val;
            maxabs = 0;
            return;
        }

        if (node->left) {
            int lm = INT_MIN, ln = INT_MAX, v = 0;
            dfs(node->left, ln, lm, v);
            min = std::min(min, ln);
            max = std::max(max, lm);
            maxabs = std::max(maxabs, v);
        }
        
        if (node->right) {
            int rm = INT_MIN, rn = INT_MAX, v = 0;
            dfs(node->right, rn, rm, v);
            min = std::min(min, rn);
            max = std::max(max, rm);
            maxabs = std::max(maxabs, v);
        }
        
        
        maxabs = std::max(maxabs, std::max(std::abs(min - node->val), std::abs(max - node->val)));
        min = std::min(min, node->val);
        max = std::max(max, node->val);
    }
    
    int doit(TreeNode* root) {
        
        int m = INT_MIN, n = INT_MAX;
        int maxabs = 0;
        
        dfs(root, n, m, maxabs);
        
        return maxabs;
    }
};
