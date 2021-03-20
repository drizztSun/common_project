/*
1660. Correct a Binary Tree

You have a binary tree with a small defect. There is exactly one invalid node where its right child incorrectly points to another node at the same depth but to the invalid node's right.

Given the root of the binary tree with this defect, root, return the root of the binary tree after removing this invalid node and every node underneath it (minus the node it incorrectly points to).

Custom testing:

The test input is read as 3 lines:

. TreeNode root
. int fromNode (not available to correctBinaryTree)
. int toNode (not available to correctBinaryTree)
After the binary tree rooted at root is parsed, the TreeNode with value of fromNode will have its right child pointer pointing to the TreeNode with a value of toNode. 
Then, root is passed to correctBinaryTree.

 

Example 1:



Input: root = [1,2,3], fromNode = 2, toNode = 3
Output: [1,null,3]
Explanation: The node with value 2 is invalid, so remove it.
Example 2:



Input: root = [8,3,1,7,null,9,4,2,null,null,null,5,6], fromNode = 7, toNode = 4
Output: [8,3,1,null,null,9,4,null,null,5,6]
Explanation: The node with value 7 is invalid, so remove it and the node underneath it, node 2.
 

Constraints:

The number of nodes in the tree is in the range [3, 104].
-109 <= Node.val <= 109
All Node.val are unique.
fromNode != toNode
fromNode and toNode will exist in the tree and will be on the same depth.
toNode is to the right of fromNode.
fromNode.right is null in the initial tree from the test data.

*/

#include <queue>
#include <unordered_map>
#include <unordered_set>

using std::unordered_set;
using std::queue;
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
class CorrectBinaryTree {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        1660.Correct-a-Binary-Tree
        用BFS进行层级遍历。对于出队列的节点node，我们查看node的右节点p（如果存在的话）：如果p的右节点存在并且是已经访问过的（设置一个集合盛装访问过的节点数值），那说明p是非法节点，把node->righ指向空。
        否则接下来考察node的左节点（如果存在的话），重复之前的操作。最后把所有的节点都层级遍历完。
    */
    TreeNode* correctBinaryTree(TreeNode* root) 
    {
        unordered_set<int>Set;
        queue<TreeNode*>q;
        q.push(root);
        Set.insert(root->val);
        while (!q.empty())
        {
            int len = q.size();
            while (len--)
            {
                TreeNode* node = q.front();                
                q.pop();
                
                if (node->right)
                {
                    TreeNode* p = node->right;
                    if (p->right && Set.find(p->right->val)!=Set.end())
                    {
                        node->right = NULL;
                        return root;
                    }
                    q.push(p);
                    Set.insert(p->val);
                }
                if (node->left)
                {
                    TreeNode* p = node->left;
                    if (p->right && Set.find(p->right->val)!=Set.end())
                    {
                        node->left = NULL;
                        return root;
                    }
                    q.push(p);
                    Set.insert(p->val);
                }
            }
        }
        return root;
    }

public:
        
    TreeNode* doit_(TreeNode* root) {

        queue<TreeNode*> qu;
        qu.push(root);
        unordered_map<TreeNode*, TreeNode*> parent;
        bool done = false;
        
        while (!qu.empty() && !done) {
            
            int size = qu.size();
            
            unordered_map<TreeNode*, TreeNode*> visited;
            
            while(size--) {
                
                auto cur = qu.front();
                qu.pop();
                
                if (cur->left) {
                    qu.push(cur->left);
                    parent[cur->left] = cur;            
                }
                
                if (cur->right) {
                    qu.push(cur->right);
                    parent[cur->right] = cur;
                    visited[cur->right] = cur;
                }
                
                if (visited.count(cur)) {
                    
                    TreeNode* delobj = visited[cur];
                    TreeNode* delparent = parent[delobj];
                    
                    printf("%d\n", delparent->val);
                    printf("%d\n", delobj->val);
                    
                    if (delparent->left == delobj)
                        delparent->left = nullptr;
                    else
                        delparent->right = nullptr;
                    
                    done = true;
                }
            }
        }
        
        return root;
        
    }
};