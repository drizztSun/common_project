/*
99. Recover Binary Search Tree


You are given the root of a binary search tree (BST), where exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

Follow up: A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

 

Example 1:


Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.
Example 2:


Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.
 

Constraints:

The number of nodes in the tree is in the range [2, 1000].
-2^31 <= Node.val <= 2^31 - 1

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
class RecoverBST {


    /*
        099.Recover-Binary-Search-Tree
        因为是BST，所以按先序遍历访问下来应该是一个递增的数列。如果一个递增的数列里出现两个数字的对调，那么会有两个尖峰。显然，第一个尖峰的顶和第二个尖峰的谷，就是被掉包的那两个数字。

        本题按先序遍历访问BST（采用DFS递归的方法）。初始化三个公共变量

        TreeNode* first=NULL;
        TreeNode* Second=NULL;
        TreeNode* CurMax=new TreeNode(INT_MIN);
        在遍历过程中，CurMax永远存储的是上一次访问的节点，理论上是一个不断增大的值。

        如果第一次出现当前访问的节点 node->val < CurMax->val，说明遇到了第一个尖峰，那么根据之前的分析，first=CurMax 即为第一个掉包元素。怎么判断这是第一个尖峰呢？只需要看first==NULL就行。别忘了，这一回合后的CurMax应该设置为node。

        如果第二次出现当前访问的节点 node->val < CurMax->val，说明遇到了第二个尖峰，那么根据之前的分析，second=node，即为第二个掉包元素。

        这里还有一个关键点：如果整个树的两个掉包元素是相邻的，那么整个遍历只会找到一个尖峰。所以这里未雨绸缪的技巧是，在处理第一个尖峰时，同时把第二个掉包元素也设置 second==node. 后续如果找到了第二个尖峰，则second会被覆盖。
    */

public:

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };


    void recoverTree(TreeNode* root) 
    {
        TreeNode* CurMax = new TreeNode(INT_MIN);
        TreeNode* first = NULL;
        TreeNode* second = NULL;

        std::function<void(TreeNode*)> DFS = [&](TreeNode* node)
        {
            if (node==NULL) return;
            
            DFS(node->left);
            
            if (node->val >= CurMax->val)
                CurMax = node;
            else
            {
                if (first==NULL) 
                {
                    first=CurMax;
                    second=node;
                    CurMax=node;
                }
                else
                    second=node;
            }
            
            DFS(node->right);      
        };

        DFS(root);
       
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }
    
    void recoverTree(TreeNode* root) {
        
        TreeNode* curMax = new TreeNode(INT_MIN);
        TreeNode *first = NULL, *second = NULL;
        
        std::function<void(TreeNode*)> dfs = [&](TreeNode* node) {
            
            if (!node) return;
            
            dfs(node->left);
            
            if (node->val >= curMax->val) {
                curMax = node;
            } else {
                
                if (!first) {
                    
                    first = curMax;
                    second = node;
                    curMax = node;
                } else 
                    second = node;
            }
            
            dfs(node->right);
        };
        
        dfs(root);
        
        std::swap(first->val, second->val);
    }
};