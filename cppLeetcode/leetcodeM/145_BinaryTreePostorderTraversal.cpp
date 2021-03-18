/*
145. Binary Tree Postorder Traversal

Given the root of a binary tree, return the postorder traversal of its nodes' values.

 

Example 1:


Input: root = [1,null,2,3]
Output: [3,2,1]
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
Output: [2,1]
 

Constraints:

The number of the nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
 

Follow up:

Recursive solution is trivial, could you do it iteratively?

*/

#include <vector>
#include <functional>
#include <deque>
#include <stack>
#include <unordered_set>

using std::unordered_set;
using std::stack;
using std::vector;
using std::deque;


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
class PostorderTraversal {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
    
        145.Binary-Tree-Postorder-Traversal
        本题和用栈实现二叉树的先序遍历和中序遍历的基本思路很相似，但更难一些。

        既然是后序遍历，那么就要在遍历完左子树、右子树之后再读取数值。所以作为中继点的根节点会经过三次。第一次是通过根节点把左子树压入栈，第二次是通过根节点把右子树压入栈，第三次才是读取。所以我们设置一个set，来标记每个在退栈时被访问过的节点。

        算法的基本结构保持和先序遍历算法一致：

        如果遇到非空节点，从根节点开始一路靠左入栈，入栈时不读取节点数值；
        当遇到空节点时，找到栈顶元素（局部的根节点）。如果之前没有被收录在set里，则记录之，并通过它把其右子树压入栈；
        如果栈顶元素已经被set记录过，此时说明其右节点已经遍历完毕，可以读取数值并将该节点退栈。（思考，退栈后root应该如何赋值？答案：把root赋值为NULL，这样就可以循环到第2步）
                while(root!=NULL || !Stack.empty())
                {
                    if (root!=NULL)
                    {
                        Stack.push(root);
                        root=root->left;
                    }
                    else
                    {
                        root=Stack.top();
                        if (Map.find(root)==Map.end())
                        {
                            Map[root]=1;
                            root=root->right;
                        }
                        else
                        {
                            results.push_back(root->val);
                            Stack.pop();
                            root=NULL;
                        }
                    }
                }
    */
    vector<int> postorderTraversal(TreeNode* root) 
    {
        vector<int>results;
        stack<TreeNode*>Stack;
        unordered_set<TreeNode*>Set;
        
        while (!Stack.empty() || root!=NULL)
        {
            if (root!=NULL)
            {
                Stack.push(root);
                root=root->left;
            }
            else
            {
                root=Stack.top();
                if (Set.find(root)==Set.end())
                {
                    Set.insert(root);
                    root = root->right;
                }
                else
                {
                    results.push_back(root->val);
                    Stack.pop();
                    root=NULL;
                }
            }
        }
        
        return results;
    }

public:

    vector<int> doit_recursive(TreeNode* root) {
        
        std::function<vector<int>(TreeNode*)> dfs = [&](TreeNode* p) {
            
            vector<int> ans;

            if (p->left) {
                auto lefts = dfs(p->left);
                ans.insert(ans.end(), begin(lefts), end(lefts));
            }

            if (p->right) {
                auto rights = dfs(p->right);
                ans.insert(ans.end(), begin(rights), end(rights));
            }

            ans.push_back(p->val);

            return ans;
        };
        
        if (!root) return {};

        return dfs(root);
    }

    vector<int> doit_iterate(TreeNode* root) {

        vector<TreeNode*> st;
        deque<int> ans;

        while (!st.empty() || root) {

            if (root) {
                ans.push_front(root->val);
                if (root->left)
                    st.push_back(root->left);
                root = root->right;
            } else {
                root = st.back();
                st.pop_back();
            }
        }

        return {begin(ans), end(ans)};
    }
};