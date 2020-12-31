/*
314. Binary Tree Vertical Order Traversal

Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Examples 1:

Input: [3,9,20,null,null,15,7]

   3
  /\
 /  \
 9  20
    /\
   /  \
  15   7 

Output:

[
  [9],
  [3,15],
  [20],
  [7]
]
Examples 2:

Input: [3,9,8,4,0,1,7]

     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7 

Output:

[
  [4],
  [9],
  [3,0,1],
  [8],
  [7]
]
Examples 3:

Input: [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5)

     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
    /\
   /  \
   5   2

Output:

[
  [4],
  [9,5],
  [3,0,1],
  [8,2],
  [7]
]

*/
#include <vector>
#include <queue>
#include <unordered_map>

using std::queue;
using std::unordered_map;
using std::vector;


class BinaryTreeVerticalOrderTraversal {

struct TreeNode {

        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

public:
    vector<vector<int>> doit_search(TreeNode* root) {
        
        int minv = INT_MAX, maxv = INT_MIN;

        queue<std::pair<TreeNode*,int>> qu;
        qu.push({root, 0});
        unordered_map<int, vector<int>> levels;

        while (!qu.empty()) {

            auto& iter = qu.front();
            TreeNode* node = iter.first;
            int l = iter.second;
            qu.pop();

            if (node) {

                levels[l].push_back(node->val);

                maxv = std::max(maxv, l);
                minv = std::min(minv, l);

                qu.push({node->left, l-1});
                qu.push({node->right, l+1});
            }
        }

        vector<vector<int>> ans;
        for (int i = minv; i <= maxv; i++) {
            if (levels.count(i) > 0)
                ans.push_back(levels[i]);
        }
        return ans;
    }
};