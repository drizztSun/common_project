/*
1676. Lowest Common Ancestor of a Binary Tree IV


Given the root of a binary tree and an array of TreeNode objects nodes, return the lowest common ancestor (LCA) of all the nodes in nodes. All the nodes will exist in the tree, and all values of the tree's nodes are unique.

Extending the definition of LCA on Wikipedia: "The lowest common ancestor of n nodes p1, p2, ..., pn in a binary tree T is the lowest node that has every pi as a descendant
 (where we allow a node to be a descendant of itself) for every valid i". A descendant of a node x is a node y that is on the path from node x to some leaf node.

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [4,7]
Output: 2
Explanation: The lowest common ancestor of nodes 4 and 7 is node 2.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [1]
Output: 1
Explanation: The lowest common ancestor of a single node is the node itself.

Example 3:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [7,6,2,4]
Output: 5
Explanation: The lowest common ancestor of the nodes 7, 6, 2, and 4 is node 5.
Example 4:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [0,1,2,3,4,5,6,7,8]
Output: 3
Explanation: The lowest common ancestor of all the nodes is the root node.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-109 <= Node.val <= 109
All Node.val are unique.
All nodes[i] will exist in the tree.
All nodes[i] are distinct.
*/

#include <vector>
#include <unordered_set>
#include <functional>

using std::vector;
using std::unordered_set;

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
class LowestCommonAncestor {
 
    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        1676.Lowest-Common-Ancestor-of-a-Binary-Tree-IV
        一个比较简单的算法思想就是，深度搜索每个节点node，查看它的子节点（包括自身）有多少个节点是在集合nodes里面的。如果数目和nodes的集合大小相同，那么node就是集合里所有节点的ancestor。

        注意，只有在DFS过程中第一个被检测到的这样的节点才是答案。更高层的节点，虽然也满足判定条件，但并不是lowest common ancestor.
    
    */
    unordered_set<TreeNode*>Set;
    TreeNode* ret = NULL;

    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) 
    {
        for (auto x: nodes)
            Set.insert(x);
        
        dfs(root);
        return ret;
    }
    
    int dfs(TreeNode* node)
    {
        if (node==NULL) return 0;
        int left = dfs(node->left);
        int right = dfs(node->right);
        int cur = Set.find(node)!=Set.end();
        if (ret==NULL && left+right+cur==Set.size())
            ret = node;
        return left+right+cur;
    }



public:
    TreeNode* doit_search(TreeNode* root, vector<TreeNode*> &nodes) {
        
        int total = nodes.size();
        TreeNode* ans = nullptr;
        unordered_set<int> values;
        for (auto it : nodes) values.insert(it->val);
        
        
        std::function<int(TreeNode*)> search = [&](TreeNode* p) {
            
            if (!p) return 0;
            
            int res = int(values.find(p->val) != values.end()) + search(p->left) + search(p->right);
            
            if (!ans && res == total)
                ans = p;
            
            return res;
        };
        
        search(root);
        
        return ans;
    }
};