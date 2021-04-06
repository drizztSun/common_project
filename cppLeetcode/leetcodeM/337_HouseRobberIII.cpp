/*
337. House Robber III


The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.

Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. 
It will automatically contact the police if two directly-linked houses were broken into on the same night.

Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.

 

Example 1:


Input: root = [3,2,3,null,3,null,1]
Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:


Input: root = [3,4,5,1,3,null,1]
Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 104

*/

#include <functional>
#include <vector>

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
class RobIII {

public:
    
    int doit_search(TreeNode* root) {
        
        std::function<vector<int>(TreeNode*)> dfs = [&](TreeNode* p) ->vector<int> {
            
            if (!p) return {0, 0};

            if (!p->left && !p->right) return {p->val, 0};

            auto l = dfs(p->left);
            auto r = dfs(p->right);

            return {p->val + l[1] + r[1], std::max(r[0], r[1]) + std::max(l[0], l[1])};
        };

        auto res = dfs(root);
        return std::max(res[0], res[1]);
    }
};