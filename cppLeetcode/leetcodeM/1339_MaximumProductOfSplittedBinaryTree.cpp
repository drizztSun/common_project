/*
1339. Maximum Product of Splitted Binary Tree

Given a binary tree root. Split the binary tree into two subtrees by removing 1 edge such that the product of the sums of the subtrees are maximized.

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:



Input: root = [1,2,3,4,5,6]
Output: 110
Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)
Example 2:



Input: root = [1,null,2,3,4,null,null,5,6]
Output: 90
Explanation:  Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)
Example 3:

Input: root = [2,3,9,10,7,8,6,5,4,11,1]
Output: 1025
Example 4:

Input: root = [1,1]
Output: 1
 

Constraints:

Each tree has at most 50000 nodes and at least 2 nodes.
Each node's value is between [1, 10000].

*/

#include <functional>
#include <vector>
#include <unordered_set>

using std::unordered_set;
using std::vector;

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
class MaximumProductSplittedBinaryTree {

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} 
    };

public:

    int doit_recursive(TreeNode* root) {
        
        using ll = long long;
        
        std::function<ll(TreeNode*)> dfs = [&](TreeNode* p) -> ll{
          
            if (!p) return 0;
            
            ll val = dfs(p->left) + p->val + dfs(p->right);
            
            return val;
        };
        
        int total = dfs(root), hmod = 1e9 + 7;
        long long best = 0;
        
        std::function<ll(TreeNode*)> cal = [&](TreeNode* p) -> ll{
          
            if (!p) return 0;
            
            ll val = cal(p->left) + p->val + cal(p->right);
            
            best = std::max(best, static_cast<long long>(val * (total - val)));
            
            return val;
        };
        
        cal(root);
        
        return best % hmod;
    }
    
    int doit_(TreeNode* root) {
    
        using ll = long long;
        
        vector<ll> sums;
        std::function<ll(TreeNode*)> dfs = [&](TreeNode* p) -> ll{
          
            if (!p) return 0;
            
            ll val = dfs(p->left) + p->val + dfs(p->right);
            
            sums.push_back(val);
            
            return val;
        };
        
        int total = dfs(root), hmod = 1e9 + 7;
        long long best = 0;
        for (auto c : sums) {
            best = std::max(best, static_cast<long long>(c * (total - c)));
        }
        
        return best % hmod;
    }

    int doit_hashtable(TreeNode* root) {
        
        using ll = long long;
        
        unordered_set<ll> sums;
        std::function<ll(TreeNode*)> dfs = [&](TreeNode* p) -> ll{
          
            if (!p) return 0;
            
            ll val = dfs(p->left) + p->val + dfs(p->right);
            
            sums.insert(val);
            
            return val;
        };
        
        int total = dfs(root), hmod = 1e9 + 7;
        long long best = 0;
        for (auto c : sums) {
            best = std::max(best, static_cast<long long>(c * (total - c)));
        }
        
        return best % hmod;
    }
};