/*
98. Validate Binary Search Tree


Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 

Example 1:


Input: root = [2,1,3]
Output: true
Example 2:


Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1



*/

#include <vector>
#include <algorithm>

using std::vector;


class IsValidBST {

    /*

        98. Validate Binary Search Tree
        方法1
        BST的性质就是进行先序遍历的话，必然是第一个递增序列。

        用DFS的方法，递归进行先序遍历。将读取的数值存入一个数组。当发现数组不满足升序时返回false

        方法2
        满足BST的三个条件：

        1.左子树的最大值小于根节点，且右子树的最小值大于根节点
        2.左子树也是BST
        3. 右子树也是BST
        在判断第一个条件时，可以根据这个性质：左子树的最大值应该就是左子树最右下角的节点；右子树的最小值应该就是右子树最左下角的节点。

        因此很容易写出递归判断的表达式。
    
    */



    vector<int>q;

public:
    bool doit_(TreeNode* root) 
    {
        if (root==NULL) return true;

        if (isValidBST(root->left)==false) 
            return false;

        q.push_back(root->val);
        if (q.size()>1 && q.back()<=q[q.size()-2])
            return false;

        if (isValidBST(root->right)==false) 
            return false;

        return true;
    }


public:
    bool isValidBST(TreeNode* root) 
    {
        if (root==NULL) return true;
        
        TreeNode* node;
        
        if (root->left!=NULL)
        {
            node=root->left;
            while (node->right!=NULL)
                node=node->right;
            if (node->val >= root->val)
                return false;
        }
        
        if (root->right!=NULL)
        {
            node=root->right;
            while (node->left!=NULL)
                node=node->left;
            if (node->val<=root->val)
                return false;
        }        
        
        return isValidBST(root->left)&&isValidBST(root->right);
    }


public:

    bool isValidBST(TreeNode* root) {
        
        if (!root || (!root->left && !root->right)) return true;
        
        TreeNode *curmax = new TreeNode(INT_MIN);
        
        std::function<bool(TreeNode*)> dfs = [&](TreeNode* p) {
          
            if (!p) return true;
            
            if (!dfs(p->left)) return false;
            
            if (p != curmax && p->val <= curmax->val) return false;
            
            curmax = p;
            
            return dfs(p->right);
        };
        
        return dfs(root);
    }
}