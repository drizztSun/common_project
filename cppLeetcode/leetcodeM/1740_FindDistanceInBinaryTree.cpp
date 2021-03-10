/*
1740. Find Distance in a Binary Tree


Given the root of a binary tree and two integers p and q, return the distance between the nodes of value p and value q in the tree.

The distance between two nodes is the number of edges on the path from one to the other.

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 0
Output: 3
Explanation: There are 3 edges between 5 and 0: 5-3-1-0.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 7
Output: 2
Explanation: There are 2 edges between 5 and 7: 5-2-7.
Example 3:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 5
Output: 0
Explanation: The distance between a node and itself is 0.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 109
All Node.val are unique.
p and q are values in the tree.

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
class Distance {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        1740.Find-Distance-in-a-Binary-Tree
        解决Lowest Common Ancestor (LCA)的一个递归套路是：定义dfs(node, p, q)，返回值是一个pair，包含node与子节点p的距离、node与子节点q的距离。如果node下属没有子节点是p和q，那么对应的值是-1.

        先分别递归ans1 = dfs(node->left, p, q)和ans2 = dfs(node->left, p, q). 分情况讨论：

        如果ans1->first!=-1，那么说明node到p的距离是ans1->first+1
        如果ans2->first!=-1，那么说明node到p的距离是ans2->first+1
        如果node->val==p，那么说明node到p的距离是0
        其余的情况，node到p的距离标记为-1
        同理，处理对于node到q的距离处理。

        如果第一次出现node到p和q的距离都不是-1，那么node就是p和q的LCA。答案就是两距离之和。
    */
     int ret = -1;
public:
    int findDistance(TreeNode* root, int p, int q) 
    {
        dfs(root, p, q);        
        return ret;
    }
    
    pair<int,int> dfs(TreeNode* root, int p, int q)
    {
        if (ret!=-1) return {-1,-1};
        if (root==NULL) return {-1, -1};
        
        auto ans1 = dfs(root->left, p, q);
        auto ans2 = dfs(root->right, p, q);
        
        int a = -1, b = -1;
        if (ans1.first!=-1)
            a = ans1.first+1;
        else if (ans2.first!=-1)
            a = ans2.first+1;
        else if (root->val==p)
            a = 0;
        
        if (ans1.second!=-1)
            b = ans1.second+1;
        else if (ans2.second!=-1)
            b = ans2.second+1;
        else if (root->val==q)
            b = 0;
        
        if (ret==-1 && a!=-1 && b!=-1)
        {
            ret = a+b;
        }
        return {a,b};
    }

    
public:
    
    int doit_search(TreeNode* root, int p, int q) {

        int ans = 0;
        
        std::function<int(TreeNode*)> search = [&](TreeNode* pnode) {

            if (!pnode) return 0;

            int l = search(pnode->left), r = search(pnode->right);

            int res = l + r;
            
            if (l != 0 && r != 0 || l + r != 0 && (pnode->val == p || pnode->val == q))
                ans = l + r;
            
            return l + r > 0 || pnode->val == p || pnode->val == q ? l + r + 1 : 0;
        };

        search(root);

        return ans;
    }
};