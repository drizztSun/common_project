/*
501. Find Mode in Binary Search Tree


Given the root of a binary search tree (BST) with duplicates, return all the mode(s) (i.e., the most frequently occurred element) in it.

If the tree has more than one mode, return them in any order.

Assume a BST is defined as follows:

. The left subtree of a node contains only nodes with keys less than or equal to the node's key.
. The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
. Both the left and right subtrees must also be binary search trees.
 

Example 1:


Input: root = [1,null,2,2]
Output: [2]
Example 2:

Input: root = [0]
Output: [0]
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-105 <= Node.val <= 105
 

Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).

*/
#include <functional>
#include <vector>

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
class FindModeInBST {

    /*
        501.Find-Mode-in-Binary-Search-Tree
        做中序遍历，这样保证遍历的元素都是递增的顺序。实时更新prev,currentFreq,maxFreq和results。注意maxFreq==0是做特殊处理。
    */
    int maxFreq=0;
    int currentFreq=0;
    int prev;
    vector<int>results;
public:
    vector<int> findMode(TreeNode* root) 
    {
        DFS(root);
        return results;
    }
    
    void DFS(TreeNode* root)
    {
        if (root==NULL) return;
        
        DFS(root->left);
        
        if (maxFreq==0)
        {
            maxFreq=1;
            currentFreq=1;
            prev=root->val;
            results.push_back(root->val);
        }
        else
        {
            if (root->val==prev)
            {
                prev=root->val;
                currentFreq++;
                if (currentFreq==maxFreq)
                {
                    results.push_back(root->val);                
                }
                else if (currentFreq>maxFreq)
                {
                    results={root->val};
                    maxFreq=currentFreq;
                }                    
            }
            else
            {
                prev=root->val;
                currentFreq=1;
                if (maxFreq==1)
                    results.push_back(root->val);
            }
        }
        
        DFS(root->right);
    }

public:
    
    vector<int> doit_(TreeNode* root) {

        int max_len = 0, maxv = 0;
        int cur = INT_MIN, cur_len = 0;
        vector<int> ans;


        std::function<void(TreeNode*)> dfs = [&](TreeNode* p) {

            if (!p) return;

            dfs(p->left);

            if (p->val != cur) {

                cur = p->val;
                cur_len = 0;
            }
            cur_len++;

            if (cur_len >= max_len) {
                if (cur_len > max_len)
                    ans.clear();
                ans.push_back(cur);
                max_len = cur_len;
            }

            dfs(p->right);
        };
        
        dfs(root);

        return ans;
    }
};