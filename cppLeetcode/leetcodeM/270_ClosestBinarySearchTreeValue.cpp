/*

270. Closest Binary Search Tree Value

Given the root of a binary search tree and a target value, return the value in the BST that is closest to the target.

 

Example 1:


Input: root = [4,2,5,1,3], target = 3.714286
Output: 4
Example 2:

Input: root = [1], target = 4.428571
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 10^9
-10^9 <= target <= 10^9


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
class CloestBinarySearchTree {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        270.Closest-Binary-Search-Tree-Value
        利用BST的性质不断朝target搜索，直至最底层。记录一路经过的根节点，不断更新 (root->val - target)的最小结果。

        注意：result的初始值必须设置为root->val。
    */
    double closestValue(TreeNode* root, double target) 
    {

        
        if (root==NULL)
            return 0;
        
        double temp = root->val;        
        
       while (root!=NULL)
       {
           
           if (fabs(root->val-target) < fabs(temp-target))
                temp=root->val;
           
           if (root->val == target)
                return target;
           else if(root->val < target)
                root=root->right;
           else if(root->val > target)
                root=root->left;             
       }
       
       return temp;
    }


public:

    int doit_dfs(TreeNode* root, double target) {
        
        double diff = INT_MAX, res = 0;
        
        std::function<void(TreeNode*)> dfs = [&](TreeNode* p) {
            
            if (!p) return;
            
            if (abs(p->val - target) < diff) {
                diff = abs(p->val - target);
                res = p->val;
                
                if (diff == 0) return;
            }
            
            if (p->val < target) {
                dfs(p->right);
            } else {
                dfs(p->left);
            }
        };
        
        dfs(root);
        
        return res;
    }

    int doit_bfs(TreeNode* root, double target) {
        
        double diff = INT_MAX, res = 0;
        queue<TreeNode*> qu;
        qu.push(root);
        
        
        while (!qu.empty()) {
            
            
            auto p = qu.front();
            qu.pop();
            
            if (diff > abs(p->val - target)) {
                diff = abs(p->val - target);
                res = p->val;
                
                if (diff == 0) break;
            }
            
            
            if (p->val < target && p->right) {
                qu.push(p->right);
            } else if (p->val > target && p->left) {
                qu.push(p->left);
            } 
            
        }
        
        return res;
    }
};
