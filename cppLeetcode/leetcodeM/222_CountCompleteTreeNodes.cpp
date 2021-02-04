/*
222. Count Complete Tree Nodes

Given the root of a complete binary tree, return the number of the nodes in the tree.

According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. 
It can have between 1 and 2h nodes inclusive at the last level h.

 

Example 1:


Input: root = [1,2,3,4,5,6]
Output: 6
Example 2:

Input: root = []
Output: 0
Example 3:

Input: root = [1]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [0, 5 * 104].
0 <= Node.val <= 5 * 104
The tree is guaranteed to be complete.



*/
#include <cmath>
#include <functional>


class CountCompleteTreeNodes {


//Definition for a binary tree node.
struct TreeNode {
    
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


public:

    // O(n)
    int doit_search_1(TreeNode* root) {

        std::function<int(TreeNode*)> build = [&](TreeNode* p) {
            if (!p) return 0;

            return build(p->left) + build(p->right) + 1;
        };

        return build(root);
    }

    // O(log(n) ^ 2)
    int doit_search(TreeNode* root) {
        
        if (!root) return 0;
        
        int depth = 0;
        TreeNode *p = root->left;
        while (p) {
            depth++;
            p = p->left;
        }
        
        if (depth == 0) return 1;
        
        int base = std::pow(2, depth) - 1;
        
        auto search = [&](int val, int d, TreeNode* p) {
            
            int left = 0, right = base;
            
            while (d--) {
                int mid = left + (right - left) / 2;
                if (mid >= val) {
                    p = p->left;
                    right = mid;
                } else {
                    p = p->right;
                    left = mid + 1;
                }
            }
            return p != nullptr;
        };
        
        int left = 1, right = base;

        while (left <= right) {
        
            int mid = left + (right - left) / 2;
        
            if (search(mid, depth, root)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return base + left;
    }
};