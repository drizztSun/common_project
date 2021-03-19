/*
333. Largest BST Subtree

Given the root of a binary tree, find the largest subtree, which is also a Binary Search Tree (BST), where the largest means subtree has the largest number of nodes.

A Binary Search Tree (BST) is a tree in which all the nodes follow the below-mentioned properties:

    . The left subtree values are less than the value of their parent (root) node's value.
    . The right subtree values are greater than the value of their parent (root) node's value.
Note: A subtree must include all of its descendants.

Follow up: Can you figure out ways to solve it with O(n) time complexity?

 

Example 1:



Input: root = [10,5,15,1,8,null,7]
Output: 3
Explanation: The Largest BST Subtree in this case is the highlighted one. The return value is the subtree's size, which is 3.
Example 2:

Input: root = [4,2,7,2,3,5,null,2,null,null,null,null,null,1]
Output: 2
 

Constraints:

The number of nodes in the tree is in the range [0, 104].
-104 <= Node.val <= 104

*/
#include <vector>
#include <functional>

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
class LargestBSTSubtree {

    /*
        333.Largest-BST-Subtree
        首先，看清题意，A subtree must include all of its descendants.

        要判断一个root是否代表了一颗BST，有三个条件：

        其左子树也是BST（或者NULL）
        其右子树也是BST（或者NULL）
        其根节点小于左子树的最大值，并且根节点大于右子树的最小值。
        接下来，考虑这个问题其实包括了两个任务：判断BST，以及它有多少个节点数目。怎么合并一起写这个DFS(root)递归函数呢？很容易想到这样的设计：当root是BST时返回其包含的节点数目，当root不是BST时则返回-1. 这个-1的返回值可以帮助上一级的根节点确定非BST，一举两得。

        首先,边界条件：if (root==NULL) return 0. 认为是BST，但节点数目为0。

        其次，对于非NULL的节点，我们就可以放心地为左右子树分别递归调用了

        int leftNum = DFS(root->left);
        int rightNum = DFS(root->right);
        leftNum和rightNum有任何一个为-1，都表明root都不是BST。

        此外，判断root为BST的第三个条件，等价于这样的操作：将左子树的右下节点与根节点比较、右子树的左下节点与根节点比较。设计一个while语句就可以迅速定位所需要的边界节点。

        以上三个条件都判断后，如果root不是BST，返回-1；如果是BST，返回leftNum+rightNum+1.
    */
    int result=0;
    
public:
    int largestBSTSubtree(TreeNode* root) 
    {
        int x = isBST(root);
        return result;
    }
    
    int isBST(TreeNode* root) 
    {
        if (root==NULL) return 0;
        
        int flag=1;
        
        if (root->left!=NULL)
        {
            TreeNode* node=root->left;
            while (node->right!=NULL) node=node->right;
            if (node->val>=root->val)
                flag=0;
        }
        
        if (root->right!=NULL)
        {
            TreeNode* node=root->right;
            while (node->left!=NULL) node=node->left;
            if (node->val<=root->val)
                flag=0;
        }        
        
        int leftNum = isBST(root->left);
        int rightNum = isBST(root->right);
        
        if (flag==0 || leftNum==-1 || rightNum==-1) return -1;
        
        result=max(result,leftNum+rightNum+1);
        
        return leftNum+rightNum+1;
        
    }

public:

    int doit_(TreeNode* root) {

        std::function<vector<int>(TreeNode*)> dfs = [&](TreeNode* p) -> vector<int> {
            
            if (!p) return {0, INT_MAX, INT_MIN};

            auto left = dfs(p->left);
            auto right = dfs(p->right);

            if (p->val > left[2] && p->val < right[1]) {
                return {left[0] + 1 + right[0], std::min(p->val, left[1]), std::max(p->val, right[2])};
            }

            return {std::max(left[0], right[0]), INT_MIN, INT_MAX};
        };

        return dfs(root)[0];
    }


    int doit_(TreeNode* root) {

        if (!root) return 0;

        int ans = 1;

        std::function<vector<int>(TreeNode*)> dfs = [&](TreeNode* p) -> vector<int> {
            
            if (!p->left && !p->right) return {1, 1, p->val, p->val};

            int bres = 1, cnt = 0, minv = p->val, maxv = p->val;

            if (p->left) {
                auto left = dfs(p->left);
                if (left[0] == 0 || p->val <= left[3]) bres = 0;
                
                if (bres == 1) {
                    cnt += left[1];
                    minv = std::min(minv, left[2]);
                    maxv = std::max(maxv, left[3]);
                }
            }

            if (p->right) {
                auto right = dfs(p->right);
                if (right[0] == 0 || p->val >= right[2]) bres = 0;

                if (bres == 1) {
                    cnt += right[1];
                    minv = std::min(minv, right[2]);
                    maxv = std::max(maxv, right[3]);
                }
            }

            if (bres == 0) return {0, 0, 0, 0};
            
            cnt++;
            ans = max(ans, cnt);
            return {1, cnt, minv, maxv};
        };

        dfs(root);
        return ans;
    }
};