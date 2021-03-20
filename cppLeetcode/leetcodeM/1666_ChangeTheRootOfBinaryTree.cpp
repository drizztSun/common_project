/*
1666. Change the Root of a Binary Tree


Given the root of a binary tree and a leaf node, reroot the tree so that the leaf is the new root.

You can reroot the tree with the following steps for each node cur on the path starting from the leaf up to the root​​​ excluding the root:

    1. If cur has a left child, then that child becomes cur's right child.
    2. cur's original parent becomes cur's left child. Note that in this process the original parent's pointer to cur becomes null, making it have at most one child.
Return the new root of the rerooted tree.

Note: Ensure that your solution sets the Node.parent pointers correctly after rerooting or you will receive "Wrong Answer".

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], leaf = 7
Output: [7,2,null,5,4,3,6,null,null,null,1,null,null,0,8]
Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], leaf = 0
Output: [0,1,null,3,8,5,null,null,null,6,2,null,null,7,4]
 

Constraints:

The number of nodes in the tree is in the range [2, 100].
-10^9 <= Node.val <= 10^9
All Node.val are unique.
leaf exist in the tree.

*/

#include <functional>


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class FlipBinaryTree {

    class Node {
    public:
        int val;
        Node* left;
        Node* right;
        Node* parent;
    };

    /*
        1666.Change-the-Root-of-a-Binary-Tree
        这道题的dfs过程其实应该是从leaf往上走直至root。对于每一个node，我们要更改它的left，right和parent。
        
        node->parent应该指向node的前驱节点（也就是处于leaf->root路径上的那个child）。node->left应该指向往上的路径（也就是原先的parent）。
        
        node->right应该指向它的另外一个child（即非leaf->root路径上的那个child）。然后递归处理leaf->root路径上的下一个节点。

        此题另外有一个陷阱是题意要求对于root的处理，与其他node的处理方法略有不同。只需要将node->parent指向前驱节点，再将处于leaf->root路径上的那个child置为NULL即可。
        
        不需一定要将非路径上的child迁移到右节点。    
    */
    Node* flipBinaryTree(Node* root, Node * leaf) {
        dfs(NULL,leaf);
        return leaf;
    }
    
    void dfs(Node* pre,Node* node)
    {
        if (node==NULL) return;
        
        Node* p=node->parent;
        node->parent=pre;
                
        if (p==NULL)
        {
            if(node->left==pre)
            {
                node->left = NULL;
            }            
            else if(node->right==pre)
            {
                node->right = NULL;
            }            
        }
        else
        {
            if(node->left==pre)
            {
                node->left = p;
            }            
            else if(node->right==pre)
            {
                node->right=node->left;
                node->left = p;
            }
        }
            
        dfs(node,p);
    }

public:

    Node* flipBinaryTree(Node* root, Node * leaf) {

        std::function<bool(Node*)> dfs = [&](Node* cur) {

            if (!cur) return false;

            if (cur == leaf) {
                leaf->left = leaf->parent;
                leaf->parent = nullptr;
                return true;
            }
            
            Node *left = cur->left, *right = cur->right, *parent = cur->parent;
            bool bres = false;

            if (dfs(left)) {
                cur->parent = left;
                cur->left = parent;
                bres = true;
            } else if (dfs(right)) {
                cur->parent = right;
                if (parent) {
                    cur->right = left;
                    cur->left = parent;
                } else {
                    cur->right = parent;
                }
                bres = true;
            }

            return bres;
        };

        dfs(root);
        return leaf;
    }
};