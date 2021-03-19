/*
655. Print Binary Tree

Print a binary tree in an m*n 2D string array following these rules:

The row number m should be equal to the height of the given binary tree.
The column number n should always be an odd number.
The root node's value (in string format) should be put in the exactly middle of the first row it can be put. 
The column and the row where the root node belongs will separate the rest space into two parts (left-bottom part and right-bottom part). 
You should print the left subtree in the left-bottom part and print the right subtree in the right-bottom part. 
The left-bottom part and the right-bottom part should have the same size. 
Even if one subtree is none while the other is not, you don't need to print anything for the none subtree but still need to leave the space as large as that for the other subtree. 
However, if two subtrees are none, then you don't need to leave space for both of them.
Each unused space should contain an empty string "".
Print the subtrees following the same rules.
Example 1:
Input:
     1
    /
   2
Output:
[["", "1", ""],
 ["2", "", ""]]
Example 2:
Input:
     1
    / \
   2   3
    \
     4
Output:
[["", "", "", "1", "", "", ""],
 ["", "2", "", "", "", "3", ""],
 ["", "", "4", "", "", "", ""]]
Example 3:
Input:
      1
     / \
    2   5
   / 
  3 
 / 
4 
Output:

[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
 ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
 ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
 ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]
Note: The height of binary tree is in the range of [1, 10].

*/

#include <string>
#include <vector>

using std::string;
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
class PrintBinaryTree {

    /*
        655.Print-Binary-Tree
        先求出这棵树的高度height，那么整个结果矩阵的宽度就是 pow(2,height)-1.

        如何填充这个矩阵数组呢？要利用每个父节点在下一层的相对位置，是其所有子节点的最中央的特点，用DFS来做。设置每一层的start和end，找到mid的位置放置父节点的值。
        则左子树在下一层的摆放区间就在start~mid-1，右子树在下一层的摆放区间就在mid+1~end.如此就可以设置递归函数。
    */
public:
    vector<vector<string>> printTree(TreeNode* root) 
    {
        int maxHeight = getHeight(root);
        int maxWidth = pow(2,maxHeight)-1;
        auto results=vector<vector<string>>(maxHeight,vector<string>(maxWidth));                
        DFS(root,0,0,maxWidth-1,results);        
        return results;
    }
    
    void DFS(TreeNode* root, int dep, int start, int end, vector<vector<string>>& results)
    {
        if (root==NULL) return;
        int pos=(start+end)/2;        
        results[dep][pos] = std::to_string(root->val);
        DFS(root->left,dep+1,start,pos-1,results);
        DFS(root->right,dep+1,pos+1,end,results);
    }
    
    int getHeight(TreeNode* root) {
        if (root==NULL) return 0;
        return std::max(getHeight(root->left),getHeight(root->right))+1;
    }
};