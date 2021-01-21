/*
652. Find Duplicate Subtrees


Given the root of a binary tree, return all duplicate subtrees.

For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with the same node values.

 

Example 1:


Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]
Example 2:


Input: root = [2,1,1]
Output: [[1]]
Example 3:


Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]
 

Constraints:

The number of the nodes in the tree will be in the range [1, 10^4]
-200 <= Node.val <= 200

*/
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using std::string;
using std::unordered_map;
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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class FindDuplicateSubtrees {

public:
    
    vector<TreeNode*> doit_(TreeNode* root) {

        unordered_map<string, int> buff;
        vector<TreeNode*> ans;
        std::function<string(TreeNode*)> lookup = [&](TreeNode* node) -> string {

            if (!node) return "";

            string uid = std::to_string(node->val) + "," + lookup(node->left) + "," + lookup(node->right);

            buff[uid]++;
            if (buff[uid] == 2) {
                ans.push_back(node);
            }
            return uid;
        };

        lookup(root);
        return ans;
    }
};