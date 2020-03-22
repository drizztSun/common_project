/*
 
 971. Flip Binary Tree To Match Preorder Traversal
 
 # Given a binary tree with N nodes, each node has a different value from {1, ..., N}.

 # A node in this binary tree can be flipped by swapping the left child and the right child of that node.

 # Consider the sequence of N values reported by a preorder traversal starting from the root.  Call such a sequence of N values the voyage of the tree.

 # (Recall that a preorder traversal of a node means we report the current node's value, then preorder-traverse the left child, then preorder-traverse the right child.)

 # Our goal is to flip the least number of nodes in the tree so that the voyage of the tree matches the voyage we are given.

 # If we can do so, then return a list of the values of all nodes flipped.  You may return the answer in any order.

 # If we cannot do so, then return the list [-1].

 # Definition for a binary tree node.
 
 */

#include <vector>
using std::vector;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    
};


class FlipMatchVoyage {
    
    bool search(TreeNode* root, vector<int>& voyage, int& index, vector<int>& res) {
        
        if (! root)
            return true;
        
        if (root->val != voyage[index])
            return false;
        
        index += 1;
        if (index < voyage.size() && root->left && root->left->val != voyage[index]) {
            res.push_back(root->val);
            return search(root->right, voyage, index, res) && search(root->left, voyage, index, res);
        } else {
            return search(root->left, voyage, index, res) && search(root->right, voyage, index, res);
        }
    }
    
    void preorder(int &now, TreeNode *root, vector<int> &voyage, vector<int> &res) {
        if (root->val != voyage[now]) {
            res = {-1};
            return;
        }
        if (root->left && root->left->val != voyage[now+1]) {
            res.push_back(root->val);
            std::swap(root->left, root->right);
        }
        ++now;
        if (root->left)
            preorder(now, root->left, voyage, res);
        if (root->right)
            preorder(now, root->right, voyage, res);
    }
    
public:
    
    vector<int> doit(TreeNode* root, vector<int>&& voyage) {
        int index = 0;
        vector<int> res;
        return search(root, voyage, index, res) ? res : vector<int>{-1};
    }
    
    vector<int> doit1(TreeNode* root, vector<int>&& voyage) {
        vector<int> res;
        int now = 0;
        preorder(now, root, voyage, res);
        return res;
    }
};

void test_971_flip_match_voyage() {
    TreeNode root(1);
    TreeNode l(2);
    root.left = &l;
    
    auto res1 = FlipMatchVoyage().doit(&root, vector<int>{2, 1});
    
    TreeNode r(3);
    root.right = &r;
    
    auto res2 = FlipMatchVoyage().doit(&root, vector<int>{1, 3, 2});
    
    
    auto res3 = FlipMatchVoyage().doit(&root, vector<int>{1, 2, 3});
    
    return;
}
