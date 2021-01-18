/*
1382. Balance a Binary Search Tree

Given a binary search tree, return a balanced binary search tree with the same node values.

A binary search tree is balanced if and only if the depth of the two subtrees of every node never differ by more than 1.

If there is more than one answer, return any of them.



Example 1:



Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2,null,null] is also correct.


Constraints:

The number of nodes in the tree is between 1 and 10^4.
The tree nodes will have distinct values between 1 and 10^5.


*/
#include <vector>
#include <functional>
using std::vector;


// Definition for a binary tree node.
struct TreeNode {
    
    int val;
    TreeNode *left;
    TreeNode *right;
    
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {

public:
    
    TreeNode* balanceBST(TreeNode* root) {
        
        vector<TreeNode*> buff;
        TreeNode* cur = root;
        vector<int> inorder;

        while (cur || !buff.empty()) {

            if (cur) {
                buff.push_back(cur);
                cur = cur->left;
            } else {

                cur = buff.back();
                buff.pop_back();

                inorder.push_back(cur->val);
                cur = cur->right;
            }
        }

        std::function<TreeNode*(int, int)> build = [&](int l, int r) -> TreeNode* {

            if (l > r) return nullptr;
            int mid = (l + r) / 2;

            TreeNode* node = new TreeNode(inorder[mid]);

            node->left = build(l, mid-1);
            node->right = build(mid+1, r);

            return node;
        };

        return build(0, inorder.size()-1);
    }


    TreeNode* balanceBST(TreeNode* root) {
        
        vector<TreeNode*> buff;
        TreeNode* cur = root;
        vector<TreeNode*> inorder;

        while (cur || !buff.empty()) {

            if (cur) {
                buff.push_back(cur);
                cur = cur->left;
            } else {

                cur = buff.back();
                buff.pop_back();

                inorder.push_back(cur);
                cur = cur->right;
            }
        }

        std::function<TreeNode*(int, int)> build = [&](int l, int r) -> TreeNode* {

            if (l > r) return nullptr;
            int mid = (l + r) / 2;

            TreeNode* node = inorder[mid];

            node->left = build(l, mid-1);
            node->right = build(mid+1, r);

            return node;
        };

        return build(0, inorder.size()-1);
    }
};