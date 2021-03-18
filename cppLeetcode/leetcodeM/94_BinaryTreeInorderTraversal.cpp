/*
94. Binary Tree Inorder Traversal


Given the root of a binary tree, return the inorder traversal of its nodes' values.

 

Example 1:


Input: root = [1,null,2,3]
Output: [1,3,2]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]
Example 4:


Input: root = [1,2]
Output: [2,1]
Example 5:


Input: root = [1,null,2]
Output: [1,2]
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
 

Follow up:

Recursive solution is trivial, could you do it iteratively?

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

class InorderTraversal {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        094.Binary-Tree-Inorder-Traversal
        此题的代码几乎和 144. Binary Tree Preorder Traversal 完全一致。唯一的区别就是记录元素的时机。先序遍历（preorder）是首先记录根节点，所以在入栈的时候就需要读数（读完根节点，再递归左子树）。
        而中序遍历（inorder）是先记录左子树，所以需要先一路入栈到最底层，在退栈的时候再开始依次读数。

        while (root!=NULL || !Stack.empty())
        {
            if (root!=NULL)
            {
                results.push_back(root->val); // 中序遍历在此读数
                Stack.push(root);
                root=root->left;
            }
            else
            {
                root=Stack.top();
                results.push_back(root->val); // 先序遍历在此读数
                Stack.pop();
                root=root->right;
            }
        }
    */
    vector<int> inorderTraversal(TreeNode* root) 
    {
        vector<int>results;
        stack<TreeNode*>Stack;
        
        while (root!=NULL || !Stack.empty())
        {
            if (root!=NULL)
            {
                Stack.push(root);
                root=root->left;
            }
            else
            {
                root=Stack.top();
                results.push_back(root->val);
                Stack.pop();
                root=root->right;
            }
        }
        
        return results;
    }
    
public:

    vector<int> doit_(TreeNode* root) {
        
        vector<int> ans;
        
        std::function<void(TreeNode*)> build =[&](TreeNode* p) {

            if (p == nullptr) return;
            
            build(p->left);
            ans.push_back(p->val);
            build(p->right);
        };

        build(root);
        return ans;
    }


    vector<int> doit_iterate(TreeNode* root) {

        vector<int> ans;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (!st.empty() || cur) {

            if (cur) {
                st.push(cur);
                cur = cur->left;
            } else {
                cur = st.top();
                st.pop();
                ans.push_back(cur->val);
                cur = cur->right;
            }
        }

        return ans;
    }
};
