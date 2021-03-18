/*
450. Delete Node in a BST

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Follow up: Can you solve it with time complexity O(height of tree)?

 

Example 1:


Input: root = [5,3,6,2,4,null,7], key = 3
Output: [5,4,6,2,null,null,7]
Explanation: Given key to delete is 3. So we find the node with value 3 and delete it.
One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
Please notice that another valid answer is [5,2,6,null,4,null,7] and it's also accepted.

Example 2:

Input: root = [5,3,6,2,4,null,7], key = 0
Output: [5,3,6,2,4,null,7]
Explanation: The tree does not contain a node with value = 0.
Example 3:

Input: root = [], key = 0
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 104].
-105 <= Node.val <= 105
Each node has a unique value.
root is a valid binary search tree.
-105 <= key <= 105
*/


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
class DeleteNode {

    /*
        450.Delete-Node-in-a-BST
        寻找要被删除的节点时，不着急利用BST的性质一下子循着key找出来，想办法用递归的形式去做。
        if (key < root->val) 
        {
            root->left = deleteNode(root->left,key);
            return root;
        }
        else if (key > root->val) 
        {
            root->right = deleteNode(root->right,key);
            return root;
        }
        找到要被删除的节点时，一个非常迫切的问题是：如果把这个root删了，我应该把大于这个root的节点替代上去（以维持BST的性质）。但是这样又会造成右子树的结构变化，这种变化有可能很复杂。不着急，我们还是想办法搞成递归。我们不需要“删除”这个root，仅把root->val替换成仅大于root的那个节点（假设为node）的权值就可以了。那么右子树需要做什么变化呢？那就是在右子树中删除node（此时整棵树中相当于有两个node），这恰恰就是重复利用了deleteNode()函数的作用。
        else if (root->val==key)
        {
            if (root->right==NULL)
                    return root->left;				
            else
                {
                    TreeNode* node=root->right;
                    while (node->left!=NULL)
                            node = node->left;  // 找到那个仅大于root的那个节点node
                    root->val=node->val; // 替换root->val
                    root->right = deleteNode(root->right,node->val); // 递归处理右子树
                    return root;
                }
        }
    */
   TreeNode* deleteNode(TreeNode* root, int key) 
    {
        if (root==NULL) return NULL;
        
        if (root->val!=key)
        {
            if (key < root->val) 
                root->left = deleteNode(root->left,key);
            else
                root->right = deleteNode(root->right,key);
        }
        else
        {
            if (root->left==NULL && root->right==NULL)
                return NULL;
            else if (root->left==NULL)
                return root->right;
            else if (root->right==NULL)
                return root->left;    
            else
            {
                TreeNode* node=root->right;
                while (node->left!=NULL)
                    node = node->left;
                root->val = node->val;
                root->right = deleteNode(root->right,node->val);
            }
        }
        return root;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root==NULL) return NULL;
        
        if (root->val<key)
        {
            root->right = deleteNode(root->right,key);
            return root;
        }
        else if (root->val>key)
        {
            root->left = deleteNode(root->left,key);
            return root;
        }
        else if (root->val==key)
        {
            if (root->right==NULL)
                    return root->left;				
            else
            {
                TreeNode* node=root->right;
                while (node->left!=NULL)
                        node = node->left;
                root->val=node->val;
                root->right = deleteNode(root->right,node->val);
                return root;
            }
        }
    }

public:

    TreeNode* doit_(TreeNode* root, int key) {
        
        TreeNode *cur = root, *last = NULL;
        
        while (cur && cur->val != key) {
            last = cur;
            if (cur->val > key)
                cur = cur->left;
            else
                cur = cur->right;            
        }
        
        if (!cur) return root;
        
        
        if (cur->right && cur->left) {
            
            TreeNode * right = cur->right;
            
            while(right->left) right = right->left;
            
            right->left = cur->left;
        }
        
        TreeNode * childnode = cur->right ? cur->right : cur->left;
        
        if (!last) return childnode;
        
        if (last->left == cur)
            last->left = childnode;
        else
            last->right = childnode;
        
        //cur->left = NULL, cur->right = NULL;
        
        return root;
        
    }
};