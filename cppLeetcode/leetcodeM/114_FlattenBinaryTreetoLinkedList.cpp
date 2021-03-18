/*
114. Flatten Binary Tree to Linked List

Given the root of a binary tree, flatten the tree into a "linked list":

. The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
. The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 

Example 1:


Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [0]
Output: [0]
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-100 <= Node.val <= 100
 

Follow up: Can you flatten the tree in-place (with O(1) extra space)?

*/

#include <functional>
#include <vector>

using std::vector;


class FlattenBinaryTree {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        114.Flatten-Binary-Tree-to-Linked-List
        用递归的思路。先各自flattern(root->left)和flattern(root->right)将左右子树分别扁平化。然后进入左子树一路向右找到最底层的节点node。将整颗右子树拼接到node->right，再把整颗左子树拼接到root->right。

        最后重点，不要忘了把 root->left=NULL
    */
    void flatten(TreeNode* root) 
    {
        if (root==NULL) return;
        
        if (root->left!=NULL)
        {
            flatten(root->left);
            flatten(root->right);
            
            TreeNode* node = root->left;
            while (node->right!=NULL)
                node=node->right;
            
            node->right = root->right;
            root->right = root->left;
            root->left = NULL;
            
        }
        else
        {
            flatten(root->right);
        }        
    }


public:

    void doit_recursive(TreeNode* root) {
        
        std::function<std::pair<TreeNode*, TreeNode*>(TreeNode*)> dfs = [&](TreeNode* p) -> std::pair<TreeNode*, TreeNode*> {

            TreeNode *left = p->left, *right = p->right, *last = p;
            p->left = NULL, p->right = NULL;

            if (left) {
                auto it = dfs(left);
                last->right = it.first;
                last = it.second;
            }
            
            if (right) {
                auto it = dfs(right);
                last->right = it.first;
                last = it.second;
            }

            return {p, last};
        };

        if (!root) return;
        
        dfs(root);
    }

    void doit_(TreeNode *root) {
        
        if (!root) return;
        
        TreeNode *cur = root;
        
        while (cur) {
            
            if (cur->left) {
                
                TreeNode *left = cur->left, *right = cur->right;
                
                cur->left = NULL;
                cur->right = left;
                
                while (left->right) {
                    left = left->right;
                }
                
                left->right = right;
            }
            
            cur = cur->right;
            
        }
    }
};