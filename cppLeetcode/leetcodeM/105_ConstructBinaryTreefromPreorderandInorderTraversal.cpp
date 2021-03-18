/*
105. Construct Binary Tree from Preorder and Inorder Traversal

Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]
 

Constraints:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder and inorder consist of unique values.
Each value of inorder also appears in preorder.
preorder is guaranteed to be the preorder traversal of the tree.
inorder is guaranteed to be the inorder traversal of the tree.
*/
#include <vector>
#include <unordered_map>
#include <functional>

using std::vector;
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
class BuildTree {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
105.Construct-Binary-Tree-from-Preorder-and-Inorder-Traversal
首先明确概念，先序遍历（perorder）是指第一个访问根节点；中序遍历（inorder）是指第二个访问根节点（第一个先访问左子树）。不要混淆了。

本题是经典的二叉树操作。考虑到preorder的第一个元素必定是root；所以在inorder中找到对应root的位置后，其左边就是左子树的所有节点的中序遍历，右边就是右子树的所有节点的中序遍历。

那么如何在preorder序列里面区别出哪些是左子树的节点，哪些是右子树的节点呢？通过inorder序列里左子树节点的数目！假设inorder序列里左子树节点的数目为N，那么在preorder序列里，root之后的N个元素就是左子树的先序遍历，剩下的元素就是右子树的先序遍历。

注意，需要提前根据inorder建立Hash表，这样从preorder里确定root后，就可以立即查找到其在inorder里的位置。

举个例子，DFS(vector& preorder, int a, int b, vector& inorder, int m, int n)，那么根节点在先序遍历中就一定是 preorder[a]，那么在中序遍历中的位置就一定是 pos = Map[preorder[a]]。所以inorder序列里, m到pos-1是左子树，pos+1到n是右子树。可知左子树的数目是N = pos-m。在preorder序列里，左子树从a+1开始，到a+N为止；显然，右子树从a+N+1开始，到b为止。
    */
    unordered_map<int,int>Map;

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
    {
        if (preorder.size()==0) return NULL;
        
        for (int i=0; i<inorder.size(); i++)
            Map[inorder[i]]=i;
        
        TreeNode* root = DFS(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
        
        return root;
    }
    
    TreeNode* DFS(vector<int>& preorder, int a, int b, vector<int>& inorder, int m, int n)
    {
        if (a>b)
            return NULL;
        
        TreeNode* root = new TreeNode(preorder[a]);
        
        int pos = Map[preorder[a]];
        root->left = DFS(preorder,a+1,a+pos-m,inorder,m,pos-1);
        root->right = DFS(preorder,a+pos-m+1,b,inorder,pos+1,n);
        return root;
    }

public:
    TreeNode* doit_(vector<int>& preorder, vector<int>& inorder) {
        
        unordered_map<int, int> pos;
        for (int i = 0; i < inorder.size(); i++) {
            pos[inorder[i]] = i;
        }
        
        int N = preorder.size();
        
        std::function<TreeNode*(int, int, int, int)> dfs = [&](int i1, int j1, int i2, int j2) -> TreeNode* {
        
            if (i1 > j1) return nullptr;
            
            TreeNode* head = new TreeNode(preorder[i1]);
            
            if (i1 == j1) return head;
            
            int m = pos[preorder[i1]];
            
            int left = m - i2, right = j2 - m;
            
            head->left = dfs(i1+1, i1 + m - i2, i2, m-1);
            
            head->right = dfs(i1 + 1 + m - i2, j1, m+1, j2);
            
            return head;
        };
        
        return dfs(0, N-1, 0, N-1);
    }
};