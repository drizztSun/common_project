/*
 863. All Nodes Distance K in Binary Tree
 
 We are given a binary tree (with root node root), a target node, and an integer value K.

 Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.

 Example 1:

 Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2

 Output: [7,4,1]

 Explanation:
 The nodes that are a distance 2 from the target node (with value 5)
 have values 7, 4, and 1.



 Note that the inputs "root" and "target" are actually TreeNodes.
 The descriptions of the inputs above are just serializations of these objects.
  

 Note:

 The given tree is non-empty.
 Each node in the tree has unique values 0 <= node.val <= 500.
 The target node is a node in the tree.
 0 <= K <= 1000.

 */

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <deque>
#include <unordered_set>

using std::unordered_set;
using std::unordered_map;
using std::vector;
using std::deque;


class AllDistanceKInBinaryTree {

    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    /*
        863.All-Nodes-Distance-K-in-Binary-Tree
        本题的关键点是，任何两个节点AB之间的路径，都可以想象成有一个“拐点”O，其中OA是沿左子树向下的路径，OB是沿右子树向下的路径。我们可以递归处理每一个节点node，设想它是这个拐点，A是target并位于其中一个分支，那么如何在另一个分支中找到B？显然，假设我们能得到target到node->left之间的距离是t，那么我们只需要从node->right出发往下走k-2-t步，所抵达的节点就都是符合要求的B点。同理，如果target位于node->right分支，类似的处理。

        需要单独处理的情况就是node==target，此时我们找的就是从node开始往下走k步到达的节点。

        注意，DFS(node)函数的一个副产品就是可以返回target到达node的距离（假设target在node的下方），这样就可以避免再多写一个递归函数。

        本题和543.Diameter-of-Binary-Tree的套路是一样的。也就是说，对于树里面任何两点之间的距离，优先去想它的拐点。
    */
    vector<int>rets;

    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) 
    {
        DFS(root, target, K);
        return rets;
    }
    
    int DFS(TreeNode* node, TreeNode* target, int k)
    {
        if (node==NULL) return -1;
        
        if (node==target)
        {
            fetch(node, k);
            return 0;
        }
            
        
        int depth1 = DFS(node->left, target, k);        
        if (depth1 != -1)
        {
            if (depth1 == k-1)
                rets.push_back(node->val);
            else                
                fetch( node->right, k - depth1 -2 );
                
            return depth1+1;
        }
        
        int depth2 = DFS(node->right, target, k);
        if (depth2 != -1)
        {
            if (depth2 == k-1)
                rets.push_back(node->val);
            else    
                fetch( node->left, k - depth2 -2 );
            return depth2+1;
        }
        
        return -1;
    }
    
    void fetch(TreeNode* node, int k)
    {
        if (node==NULL) return;
        if (k<0) return;
        if (k==0)
        {
            rets.push_back(node->val);
            return;
        }
        fetch(node->left, k-1);
        fetch(node->right, k-1);        
    }


public:
    
    void dfs(TreeNode* m, TreeNode* p, unordered_map<TreeNode*, TreeNode*>& parent) {
        if (m) {
            parent.insert({m, p});
            dfs(m->left, m, parent);
            dfs(m->right, m, parent);
        }
    }
    
    vector<int> doit_dfs(TreeNode* root, TreeNode* target, int K) {
        
        unordered_map<TreeNode*, TreeNode*> parent;
        dfs(root, nullptr, parent);
        
        vector<int> res;
        deque<std::pair<TreeNode*, int>> qu{{target, 0}};
        unordered_set<TreeNode*> seen;
        seen.insert(target);
        
        while (!qu.empty()) {
            auto c = qu.front();
            if (c.second == K) {
                res.push_back(c.first->val);
            } else {
                TreeNode* related[3]{parent[c.first], c.first->left, c.first->right};
                for (auto n : related) {
                    if (seen.count(n) > 0 && n) {
                        seen.insert(n);
                        qu.push_back({n, c.second+1});
                    }
                }
            }
            qu.pop_front();
        }
        
        return res;
    }
    
public:
    vector<int> doit_2(TreeNode* root, TreeNode* target, int K) {
        vector<TreeNode*> path;
        if (root == nullptr || target == nullptr) {
            return {};
        }
        
        if(!findPath(root, target, path)) {
            return {};
        }
       
        if (path.empty()) {
            return {};
        }
        
        vector<int> res;
        helper(path[0], nullptr, K, res);
        
        for (int i = 1; i < path.size(); ++i) {
            if (K - i < 0) {
                break;
            }
            helper(path[i], path[i-1], K-i, res);
        }
        return res;
    }
    
    bool findPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
        if (root == nullptr) {
            return false;
        }
        if (root == target) {
            path.push_back(root);
            return true;
        }
        if (findPath(root->left, target, path) || findPath(root->right, target, path)) {
            path.push_back(root);
            return true;
        }
        
        return false;
    }
    
    void helper(TreeNode* start, TreeNode* searched, int k, vector<int>& res) {
        if (start == nullptr) {
            return;
        }
        if (k == 0) {
            res.push_back(start->val);
            return;
        }
        if (searched == nullptr || start->left != searched) {
            helper(start->left, nullptr, k-1, res);
        }
        if (searched == nullptr || start->right != searched) {
            helper(start->right, nullptr, k-1, res);
        }
    }
};
