/*
113. Path Sum II

Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where each path's sum equals targetSum.

A leaf is a node with no children.

 

Example 1:


Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Example 2:


Input: root = [1,2,3], targetSum = 5
Output: []
Example 3:

Input: root = [1,2], targetSum = 0
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 5000].
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000

*/

#include <vector>
#include <functional>

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
class PathSumII {

public:
    
    vector<vector<int>> doit_(TreeNode* root, int targetSum) {

        vector<vector<int>> ans;
        
        if (!root) return {}; 

        std::function<void(TreeNode*, int, vector<int>& )> dfs = [&](TreeNode* p, int total, vector<int>& cur) {

            if (!p->left && !p->right) {
                if (total + p ->val == targetSum) {
                    cur.push_back(p->val);
                    ans.push_back(cur);
                    cur.pop_back();
                }
                return;
            }

            cur.push_back(p->val);
            if (p->left)
                dfs(p->left, total + p->val, cur);
            
            if (p->right)
                dfs(p->right, total + p->val, cur);
            cur.pop_back();
        };
        
        vector<int> cur;
        dfs(root, 0, cur);
        return ans;
    }
};