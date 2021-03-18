/*
124. Binary Tree Maximum Path Sum

A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. 
A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any path.

 

Example 1:


Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
Example 2:


Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
 

Constraints:

The number of nodes in the tree is in the range [1, 3 * 104].
-1000 <= Node.val <= 1000
*/
#include <functional>


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
class BinaryTreeMaxPathSum {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        124.Binary-Tree-Maximum-Path-Sum
        任何一个max-sum-path必然会有唯一的一个最高节点（或者看作是拐点）。我们的基本思想就是遍历所有的node，计算它作为拐点所能取到的max-sum-path。然后用一个全局变量做实时的更新。

        对于以node作为拐点的maxTurnSum，肯定包括了自己本身。那么往node的左节点再往下能走多远呢？其实取决于maxDownSum(node->left)。maxDownSum的意思是从起点出发往下“不拐弯”所能得到的最大路径和。如果maxDownSum(node->left)>0，那么maxTurnSum肯定会选择往左边继续往下，否则maxTurnSum就不会有左边的支路。对于右子树的分析同理。

        所以我们有这样的表达式：

        maxTurnSum(node) = node->val + max(0, maxDownSum(node->left)) + max(0, maxDownSum(node->right))
        显然，我们真正需要写的递归函数应该是maxDownSum(node)：

        1. 它的返回值所对应的是不要求拐弯的最大权重路径，所以 maxDownSum(node) = node->val + max(maxDownSum(node), maxDownSum(node->right)。
        2. 因为这个递归函数会遍历所有的node，所以利用访问node的机会，顺便计算maxTurnSum(node)，注意这个才是最终答案所需要的。
    */
    int ret = INT_MIN;
public:
    int maxPathSum(TreeNode* root) 
    {
        MaxDownPath(root);
        return ret;
    }
    
    int MaxDownPath(TreeNode* node)  // starting from node downward only, the max-sum path
    {
        if (node==NULL) return 0;
        
        int leftSum = MaxDownPath(node->left);
        int rightSum = MaxDownPath(node->right);
        
        int maxTurnSum = node->val;
        if (leftSum >= 0) maxTurnSum += leftSum;
        if (rightSum >= 0) maxTurnSum += rightSum;
        ret = std::max(ret, maxTurnSum);
        
        if (leftSum < 0 && rightSum < 0)
            return node->val;
        else
            return std::max(leftSum, rightSum) + node->val;
    }

public:
    
    int doit_(TreeNode* root) {
        
        int max_sums = INT_MIN;

        std::function<int(TreeNode*)> search =[&](TreeNode* p) {

            if (p == nullptr) return 0;
            
            int l = std::max(0, search(p->left)), r = std::max(0, search(p->right));

            max_sums = std::max(max_sums, l + r + p->val);

            return std::max({l ,r, 0}) + p->val;
        };

        search(root);
        return max_sums;
    }
};