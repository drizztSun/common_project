/*
513. Find Bottom Left Tree Value

Given the root of a binary tree, return the leftmost value in the last row of the tree.

Example 1:


Input: root = [2,1,3]
Output: 1
Example 2:


Input: root = [1,2,3,4,null,5,6,null,null,7]
Output: 7
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1

*/

#include <functional>
#include <stack>

using std::stack;


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
class BottomLeftValue {


    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

public:

    int doit_dfs(TreeNode* root) {
        
        int maxdepth = -1, val = INT_MAX;
        
        std::function<void(TreeNode*, int)> dfs = [&] (TreeNode* p, int depth) {
            
            if (!p) return;
            
            if (depth > maxdepth) {
                maxdepth = depth;
                val = p->val;
            }
            
            
            dfs(p->left, depth+1);
            dfs(p->right, depth+1);
        };
        
        dfs(root, 0);
        return val;
    }

    int doit_dfs(TreeNode* root) {

        stack<std::pair<TreeNode*, int>> st;
        st.push({root, 0});

        int maxdepth = -1, val = INT_MAX;

        while (!st.empty()) {

            auto it = st.top();
            TreeNode* cur = it.first;
            int depth = it.second;
            st.pop();

            if (depth > maxdepth) {
                maxdepth = depth;
                val = cur->val;
            }
            
            if (cur->right) {
                st.push({cur->right, depth+1});
            }

            if (cur->left) {
                st.push({cur->left, depth+1});
            }
        }

        return val;
    }

};