/*
687. Longest Univalue Path

Given the root of a binary tree, return the length of the longest path, where each node in the path has the same value. This path may or may not pass through the root.

The length of the path between two nodes is represented by the number of edges between them.

 

Example 1:


Input: root = [5,4,5,1,1,5]
Output: 2
Example 2:


Input: root = [1,4,5,4,4,5]
Output: 2
 

Constraints:

The number of nodes in the tree is in the range [0, 104].
-1000 <= Node.val <= 1000
The depth of the tree will not exceed 1000.

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
class LongestUnivaluePath {

    /*
        687.Longest-Univalue-Path
        设计DFS(node)函数，返回的是以node为起点，朝某个单向下行最长的Univalue path

        每一次调用DFS(node)，都要先调用L=DFS(node->left)和R=DFS(node->right)，将左右节点都递归遍历完毕。

        如果左节点、当前节点、右节点的数值相等，说明可以形成一个完整的uniValuePath，用Ｌ＋Ｒ＋１来刷新全局的longest变量。

        那么考虑DFS(node)自己的返回值是什么呢？显然是１，或Ｌ＋１（如果根与左节点相同），或Ｒ＋１（如果根与右节点相同）
    */
    int result=0;
public:
    int longestUnivaluePath(TreeNode* root) 
    {
        int temp = DFS(root);
        return max(0,result-1);
    }
    
    int DFS(TreeNode* root)
    {
        if (root==NULL) return 0;
        int L = DFS(root->left);
        int R = DFS(root->right);

        int LL=0;
        int RR=0;
        if (root->left!=NULL && root->left->val==root->val)
            LL = L;
        if (root->right!=NULL && root->right->val==root->val)
            RR = R;
        result = std::max(result, LL+RR+1);
        return std::max(LL+1,RR+1);        
    }

public:
    
    int doit_(TreeNode* root) {

        int ans = 0;
        
        std::function<int(TreeNode*, int, int)> dfs =[&](TreeNode* p, int parent, int depth) {
            
            
            ans = std::max(ans, depth);
            
            if (!p) return 0;
            
            if (p->val == parent)
                depth++;
            else
                depth = 0;
            
            int l = dfs(p->left, p->val, depth), r = dfs(p->right, p->val, depth);
            
            ans = std::max({ans, l + r, depth});
            
            return p->val != parent ? 0 : std::max(l, r) + 1;
        };
        
        dfs(root, INT_MAX, 0);
        
        return ans;
        
    }
};