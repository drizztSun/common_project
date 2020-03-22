/*
 
 
 968. Binary Tree Cameras
 
 Given a binary tree, we install cameras on the nodes of the tree.

 Each camera at a node can monitor its parent, itself, and its immediate children.

 Calculate the minimum number of cameras needed to monitor all nodes of the tree.

 
 
 
 Approach 1: Dynamic Programming
 Intuition

 Let's try to cover every node, starting from the top of the tree and working down. Every node considered must be covered by a camera at that node or some neighbor.

 Because cameras only care about local state, we can hope to leverage this fact for an efficient solution.
 Specifically, when deciding to place a camera at a node, we might have placed cameras to cover some subset of this node, its left child, and its right child already.

 Algorithm

 Let solve(node) be some information about how many cameras it takes to cover the subtree at this node in various states. There are essentially 3 states:

 [State 0] Strict subtree: All the nodes below this node are covered, but not this node.
 [State 1] Normal subtree: All the nodes below and including this node are covered, but there is no camera here.
 [State 2] Placed camera: All the nodes below and including this node are covered, and there is a camera here (which may cover nodes above this node).
 Once we frame the problem in this way, the answer falls out:

 To cover a strict subtree, the children of this node must be in state 1.
 To cover a normal subtree without placing a camera here, the children of this node must be in states 1 or 2, and at least one of those children must be in state 2.
 To cover the subtree when placing a camera here, the children can be in any state.

 
 
 */

#include <algorithm>
using std::min_element;

#include <vector>
using std::vector;

#include <limits>

 //Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };
 
class MinCameraCover {
    
    vector<int> search(TreeNode* node) {
        
        if (!node)
            return {0, 0, 1000000};
        
        vector<int> l = search(node->left);
        vector<int> r = search(node->right);
        
        vector<int> ans(3, 0);
        ans[0] = l[1] + r[1];
        ans[1] = std::min(r[2] + std::min(l[1], l[2]), std::min(r[1], r[2]) + l[2]);
        ans[2] = 1 + *min_element(r.begin(), r.end()) + *min_element(l.begin(), l.end());
        
        return ans;
    }
    
public:
    int doit(TreeNode* root) {
        
        auto res = search(root);
        return std::min(res[1], res[2]);
    }
    
    

    
    void post_order(TreeNode* root, int &res)
    {
       if(root->left != NULL)
       {
           post_order(root->left,res);
       }
        
       if(root->right != NULL)
       {
           post_order(root->right,res);
       }
        
       if((root->left != NULL && root->left->val == 0) || (root->right != NULL && root->right->val == 0))
       {
           res++;
           root->val = 2;
           if(root->left!=NULL && root->left->val != 2)root->left->val = 1;
           if(root->right!=NULL && root->right->val != 2)root->right->val = 1;
       }
        
       else if((root->left!=NULL && root->left->val == 2) || (root->right!=NULL && root->right->val == 2))
       {
           if(root->val != 2)root->val = 1;
       }
    }
    
    int minCameraCover(TreeNode* root) {
        int res = 0;
        post_order(root,res);
        if(root->val == 0)
            res++;
        
        return res;
    }
};

void test_968_binary_tree_camera() {
    
    TreeNode root(0);
    TreeNode r1(0);
    TreeNode r3(0);
    TreeNode r4(0);
    
    root.left = &r1;
    r1.left = &r3;
    r1.right = &r4;
    
    auto res = MinCameraCover().doit(&root);
    
    TreeNode n(0);
    auto res1 = MinCameraCover().doit(&n);
    return;
}
