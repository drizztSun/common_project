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


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class AllDistanceKInBinaryTree {
    
public:
    
    void dfs(TreeNode* m, TreeNode* p, unordered_map<TreeNode*, TreeNode*>& parent) {
        if (m) {
            parent.insert({m, p});
            dfs(m->left, m, parent);
            dfs(m->right, m, parent);
        }
    }
    
    vector<int> doit_1(TreeNode* root, TreeNode* target, int K) {
        
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
