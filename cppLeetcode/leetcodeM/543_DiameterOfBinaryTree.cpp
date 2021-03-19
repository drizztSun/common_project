/*
543. Diameter of Binary Tree


Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

 

Example 1:


Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3is the length of the path [4,2,1,3] or [5,2,1,3].
Example 2:

Input: root = [1,2]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-100 <= Node.val <= 100

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
class DiameterOfBinaryTree {

    /*
        543.Diameter-of-Binary-Tree
        对于所有可能的diameter，本质都对应了一个节点作为“拐点”。所以本题的基本思想就是遍历所有的节点，对每个节点找最长的左子树-根-右子树的路径。

        如果从上往下地DFS，要避免这种情况：先算出根节点的路径，再计算左子树和右子树的路径。因为在算根节点的最长路径时，必然会考察其左子树和右子树；这样，如果再计算左子树和右子树的最长路径，必然会浪费之前的计算结果。所以我们应该设计这样的DFS函数：

        int DFS(TreeNode* root)
        {
        int info_left = DFS(root->left);
        int info_right = DFS(root->left);
        result = max(result, f1(info_left,info_right));  // 以该节点为拐点的最长路径
        return f2(info_left,info_right);  // 设计的返回值
        }
        这样本质上就实现了自底向上的遍历。那么我们需要提取什么样的信息呢？我们其实需要一个节点到叶子节点的最长路径即可。

            int LongestPathToLeaf(TreeNode* root) // 返回以该节点为顶点到叶子节点的最长路径
            {
                if (root==NULL) return 0;        
                int left = LongestPathToLeaf(root->left);
                int right = LongestPathToLeaf(root->right);
                result = max(result,left+right+1);  // 以该节点为拐点的最长路径
                return max(left,right)+1;  // 以该节点为顶点到叶子节点的最长路径
            }
    */
    int result;
public:
    int diameterOfBinaryTree(TreeNode* root) 
    {
        if (root==NULL) return 0;
        int temp = LongestPathToLeaf(root);
        return result-1;
    }
    
    int LongestPathToLeaf(TreeNode* root)
    {
        if (root==NULL) return 0;
        
        int left = LongestPathToLeaf(root->left);
        int right = LongestPathToLeaf(root->right);
        result = max(result,left+right+1);
        return max(left,right)+1;
    }


public:
    int doit_(TreeNode* root) {
        
        int ans = 0;
        
        std::function<int(TreeNode*)> dfs = [&](TreeNode* p) {
            
            if (!p) return 0;
            
            int l = dfs(p->left), r = dfs(p->right);
            
            ans = std::max(ans, l + r);
            
            return std::max(l, r) + 1;
        };
        
        dfs(root);
        
        return ans;
    }
};