/*
156. Binary Tree Upside Down

Given the root of a binary tree, turn the tree upside down and return the new root.

You can turn a binary tree upside down with the following steps:

The original left child becomes the new root.
The original root becomes the new right child.
The original right child becomes the new left child.


The mentioned steps are done level by level, it is guaranteed that every node in the given tree has either 0 or 2 children.

 

Example 1:


Input: root = [1,2,3,4,5]
Output: [4,5,2,null,null,3,1]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]
 

Constraints:

The number of nodes in the tree will be in the range [0, 10].
1 <= Node.val <= 10
Every node has either 0 or 2 children.


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
class UpsideDownBinaryTree {


    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        156.Binary-Tree-Upside-Down
        此题的意思是：对于一个根-左-右的基本树状结构，右子树保证只有一个或为空。要求变形后，以左子树为根，把原来的根和右节点作为新根节点的右、左节点。

        解决此题的思路应该坚定不移地寻找递归方案。

        经过分析，应该能够发现，对于一个root,left,right的基本结构，变形后的新结构应该变为：递归(root->left)作为根，root作为右，root->left作为左。于是代码就非常好写了。

        注意到递归(root->left)返回的是它的根节点。怎么把root作为递归(root->left)的右子树呢？只要不停地从根节点往右子树方向移动就可以了。

        基本代码思路

        head=upsideDownBinaryTree(root->left);
        node=head一路向右；
        node->right=root;
        node->left=root->right;
        root->left=NULL; //root原本的左右子节点要清空
        root->right=NULL;
    
    */
    TreeNode* upsideDownBinaryTree(TreeNode* root) 
    {
        if (root==NULL) return NULL;
        
        if (root->left==NULL) 
            return root;
        else
        {
            TreeNode* nextRoot = root->left;
            TreeNode* nextRootAlien = new TreeNode(root->left->val);
            nextRootAlien->right = root;
            nextRootAlien->left = root->right;
            root->left=NULL;
            root->right=NULL;
            return DFS(nextRoot,nextRootAlien);
        }
    }
    
    TreeNode* DFS(TreeNode* root, TreeNode* rootAlien)
    {
        if (root->left==NULL) 
            return rootAlien;
        else
        {
            TreeNode* nextRoot = root->left;
            TreeNode* nextRootAlien = new TreeNode(root->left->val);
            nextRootAlien->right = rootAlien;
            nextRootAlien->left = root->right;
            return DFS(nextRoot,nextRootAlien);
        }
        
    }

public:

    TreeNode* doit_(TreeNode* root) {
        
        using tt = std::pair<TreeNode*, TreeNode*>;
        
        if (!root) return root;
        
        std::function<std::pair<TreeNode*, TreeNode*>(TreeNode*)> dfs = [&](TreeNode* p) ->std::pair<TreeNode*, TreeNode*> {
            
            if (!p->left && !p->right) return {p, p};
            
            auto itleft = dfs(p->left);
            auto itright = p->right ? dfs(p->right) : tt{NULL, NULL};
            
            p->left = NULL, p->right = NULL;
            
            itleft.second->left = itright.first; 
            itleft.second->right = p;
            
            return {itleft.first, p};
        };
        
        return dfs(root).first;
    }
};