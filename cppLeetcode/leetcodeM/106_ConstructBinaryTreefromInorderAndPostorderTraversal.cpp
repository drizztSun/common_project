/*
106. Construct Binary Tree from Inorder and Postorder Traversal

Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: inorder = [-1], postorder = [-1]
Output: [-1]
 

Constraints:

1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder and postorder consist of unique values.
Each value of postorder also appears in inorder.
inorder is guaranteed to be the inorder traversal of the tree.
postorder is guaranteed to be the postorder traversal of the tree.
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
class BuildTreeInorderPreorder {


    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        106.Construct-Binary-Tree-from-Inorder-and-Postorder-Traversal
        本题和 105. Construct Binary Tree from Preorder and Inorder Traversal 一样的思路。根据后续遍历的性质，postorder数组的最后一个元素就是根节点。在inorder数组里面通过之前构建的hash映射找到这个根节点，就可以将整个inorder数组分成左右两部分，分别构造左子树和右子树。

        postorder数组的拆分方法：根据inorder数组拆分得到的左右子树的元素数目，来确定postorder序列里前面多少个元素属于左子树。
    */
    unordered_map<int,int>Map;
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) 
    {
        for (int i=0; i<inorder.size(); i++)
            Map[inorder[i]]=i;
        return DFS(inorder,0,inorder.size()-1,postorder,0,postorder.size()-1);
    }
    
    TreeNode* DFS(vector<int>& inorder, int a, int b, vector<int>& postorder, int m, int n)
    {
        if (a>b) return NULL;
        
        TreeNode* root=new TreeNode(postorder[n]);
        int pos=Map[postorder[n]];
        root->left = DFS(inorder,a,pos-1,postorder,m,m+pos-1-a);
        root->right = DFS(inorder,pos+1,b,postorder,m+pos-a,n-1);
        
        return root;
    }

public:
    
    TreeNode* doit_(vector<int>& inorder, vector<int>& postorder) {

                unordered_map<int, int> pos;
        for (int i = 0; i < inorder.size(); i++) pos[inorder[i]] = i;
        
        std::function<TreeNode*(int, int, int, int)> dfs = [&](int i1, int j1, int i2, int j2) -> TreeNode* {
            
            if (i1 > j1) return nullptr;
            
            if (i1 == j1) return new TreeNode(inorder[i1]);
            
            TreeNode *head = new TreeNode(postorder[j2]);
            
            int m = pos[postorder[j2]], right = j1 - m;
            
            head->right = dfs(m+1, j1, j2 - right, j2-1);
            head->left = dfs(i1, m-1, i2, j2 - right-1);
            
            return head;
        };
        
        return dfs(0, inorder.size()-1, 0, postorder.size()-1);
        
    }
};