/*
549. Binary Tree Longest Consecutive Sequence II


Given the root of a binary tree, return the length of the longest consecutive path in the tree.

This path can be either increasing or decreasing.

For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path [1,2,4,3] is not valid.
On the other hand, the path can be in the child-Parent-child order, where not necessarily be parent-child order.

 

Example 1:


Input: root = [1,2,3]
Output: 2
Explanation: The longest consecutive path is [1, 2] or [2, 1].
Example 2:


Input: root = [2,1,3]
Output: 3
Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
 

Constraints:

The number of nodes in the tree is in the range [1, 3 * 104].
-3 * 104 <= Node.val <= 3 * 104

*/
#include <vector>
#include <functional>
#include <unordered_map>

using std::unordered_map;

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
class LongestConsecutiveII {

    /*
        549.Binary-Tree-Longest-Consecutive-Sequence-II
        第一步：从上到下递归调用所有的节点，每个节点都算出以其为顶点的最长增序列和最长减序列，并将这两个长度存放在两个作为全局的Hash表中。

        第二部：DFS遍历所有节点，遇到每个节点时，都可以算出它的longest consecutive sequence长度 IS[node]+DS[node]-1，不断更新最终结果。
    */
    unordered_map<TreeNode*,int>IS;
    unordered_map<TreeNode*,int>DS;
    int result=0;
public:
    int longestConsecutive(TreeNode* root) 
    {
        if (root==NULL) return 0;
        
        int x=longest_increase(root);
        int y=longest_decrease(root);
        DFS(root);
        return result;
    }
    
    void DFS(TreeNode* node)
    {
        if (node==NULL) return;
        DFS(node->left);
        result = max(result,IS[node]+DS[node]-1);
        //cout<<node->val<<" "<<IS[node]<<" "<<DS[node]<<endl;
        DFS(node->right);
    }
    
    int longest_increase(TreeNode* node)
    {
        if (node==NULL) return 0;
        
        int res = 1;
        if (node->left!=NULL)
        {
            int temp = longest_increase(node->left);
            if (node->val+1==node->left->val)
                res = max(res,temp+1);
        }
        if (node->right!=NULL)
        {
            int temp = longest_increase(node->right);
            if (node->val+1==node->right->val)
                res = max(res,temp+1);
        }
        
        IS[node]=res;
        return res;
    }

    int longest_decrease(TreeNode* node)
    {
        if (node==NULL) return 0;
        
        int res = 1;
        if (node->left!=NULL)
        {
            int temp = longest_decrease(node->left);
            if (node->val-1==node->left->val)
                res = max(res,temp+1);
        }
        if (node->right!=NULL)
        {
            int temp = longest_decrease(node->right);
            if (node->val-1==node->right->val)
                res = max(res,temp+1);
        }
        DS[node]=res;
        return res;
    }  

public:

    int doit_(TreeNode* root) {

        int ans = 0;

        std::function<vector<int>(TreeNode*)> dfs = [&](TreeNode* p) -> vector<int>{

            if (!p) return {0, 0};

            auto lefts = dfs(p->left);
            auto rights = dfs(p->right);

            if (p->left && abs(p->val - p->left->val) == 1) {
                if (p->val == p->left->val + 1) {
                    lefts[0]++; 
                    lefts[1] = 1;
                } else {
                    lefts[0] = 1;
                    lefts[1]++;
                }
            } else {
                lefts[0] = 1, lefts[1] = 1;
            }

            if (p->right && abs(p->val - p->right->val) == 1) {
                if (p->val == p->right->val + 1) {
                    rights[0]++;
                    rights[1] = 1;
                } else {
                    rights[0] = 1;
                    rights[1]++;
                }
            } else {
                rights[0] = 1, rights[1] = 1;
            }

            ans = std::max({ans, lefts[0]+rights[1]-1, lefts[1]+rights[0]-1});

            return {std::max(lefts[0], rights[0]), std::max(lefts[1], rights[1])};
        };


        dfs(root);
        return ans;
    }
};