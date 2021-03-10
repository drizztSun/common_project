/*
938. Range Sum of BST

Given the root node of a binary search tree, return the sum of values of all nodes with a value in the range [low, high].

 

Example 1:


Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
Output: 32
Example 2:


Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
Output: 23
 

Constraints:

The number of nodes in the tree is in the range [1, 2 * 104].
1 <= Node.val <= 105
1 <= low <= high <= 105
All Node.val are unique.
*/
#include <functional>
#include <queue>

using std::queue;

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
class RangeSumBST {


    struct TreeNode {
       int val;
       TreeNode *left;
       TreeNode *right;
       TreeNode() : val(0), left(nullptr), right(nullptr) {}
       TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
       TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

public:

    int doit_(TreeNode* root, int low, int high) {
        
        std::function<int(TreeNode*)> build = [&](TreeNode* node) -> int {
        
            if (!node) return 0;
            
            int res = 0;
            if (node->val >= low && node->val <= high)
                res = node->val;
            
            if (node->val >= low)
                res += build(node->left);
            
            if (node->val <= high)
                res += build(node->right);
            
            return res;
        };
        
        return build(root);
    }

    int rangeSumBST(TreeNode* root, int low, int high) {
        
        if (!root) return 0;
        
        queue<TreeNode*> qu;
        qu.push(root);
        
        int res = 0;
        
        while (!qu.empty()) {
            
            TreeNode* cur = qu.front(); 
            qu.pop();
            
            if (cur->val >= low && cur->val <= high)
                res += cur->val;
            
            if (cur->val >= low && cur->left)
                qu.push(cur->left);
            
            if (cur->val <= high && cur->right)
                qu.push(cur->right);
        }
        
        return res;
    }
};