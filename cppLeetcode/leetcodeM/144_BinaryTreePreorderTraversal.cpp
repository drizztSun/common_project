/*
144. Binary Tree Preorder Traversal

Given the root of a binary tree, return the preorder traversal of its nodes' values.

 

Example 1:


Input: root = [1,null,2,3]
Output: [1,2,3]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]
Example 4:


Input: root = [1,2]
Output: [1,2]
Example 5:


Input: root = [1,null,2]
Output: [1,2]
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
 

Follow up: Recursive solution is trivial, could you do it iteratively?

*/

#include <vector>
#include <functional>
#include <stack>

using std::stack;
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

class PreorderTraversal {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        144.Binary-Tree-Preorder-Traversal
        二叉树中的经典题。用栈来实现二叉树的先序遍历（首先访问根节点）

        基本思路：如果root非空，则读取数值（因为此root就是根节点）并压入栈，如果可能root=root->left一路朝左遍历到底层。
        如果发现root是空，则取栈顶元素并退栈（因为根节点都已经访问过了），令root是栈顶元素的右子树。然后就是重复之前的判断。
    */
    vector<int> preorderTraversal(TreeNode* root) 
    {
        vector<int>results;
        stack<TreeNode*>Stack;
        
        while (root!=NULL || !Stack.empty())
        {
            if (root!=NULL)
            {
                Stack.push(root);
                results.push_back(root->val);
                root=root->left;
            }
            else
            {
                root=Stack.top();
                Stack.pop();
                root=root->right;
            }
        }
        
        return results;
    }

public:
    vector<int> doit_recursive(TreeNode* root) {

        std::function<vector<int>(TreeNode*)> dfs = [&](TreeNode* p) {
            
            vector<int> ans{p->val};

            if (p->left) {
                auto lefts = dfs(p->left);
                ans.insert(ans.end(), begin(lefts), end(lefts));
            }

            if (p->right) {
                auto rights = dfs(p->right);
                ans.insert(ans.end(), begin(rights), end(rights));
            }

            return ans;
        };
        
        if (!root) return {};

        return dfs(root);
    }

    vector<int> doit_iterate(TreeNode* root) {

        vector<TreeNode*> st;
        vector<int> ans;

        while (!st.empty() || root) {

            if (root) {
                ans.push_back(root->val);
                if (root->right)
                    st.push_back(root->right);
                root = root->left;
            } else {
                root = st.back();
                st.pop_back();
            }
        }

        return ans;
    }
};