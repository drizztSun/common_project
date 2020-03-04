/*
 
 # 1038. Binary Search Tree to Greater Sum Tree
 
 
 # Given the root of a binary search tree with distinct values, modify it so that every node
 # has a new value equal to the sum of the values of the original tree that are greater than or equal to node.val.
 
 # As a reminder, a binary search tree is a tree that satisfies these constraints:
 
 # The left subtree of a node contains only nodes with keys less than the node's key.
 # The right subtree of a node contains only nodes with keys greater than the node's key.
 # Both the left and right subtrees must also be binary search trees.
 
 
 # Example 1:

 
 
 */

#include <queue>
using std::priority_queue;

#include <vector>
using std::vector;


 //Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BstToGst {

public:
    
    TreeNode* doit(TreeNode* root) {
        
        priority_queue<std::pair<int, TreeNode*>> pq;
        vector<TreeNode*> buff;
        buff.push_back(root);
        
        while (!buff.empty()) {
            
            TreeNode* c = buff.back();
            buff.pop_back();
            
            pq.push({c->val, c});
            if (c->left)
                buff.push_back(c->left);
            if (c->right)
                buff.push_back(c->right);
        }
        
        int cur = 0;
        while (!pq.empty()) {
            auto c = pq.top();
            pq.pop();
            cur += c.first;
            c.second->val = cur;
        }
        
        return root;
    }
};

void test_1038_Binary_Search_Tree_Greater_Sum_Tree() {
    
    TreeNode root(1);
    TreeNode left(2);
    TreeNode right(3);
    root.left = &left;
    root.right = &right;
    
    BstToGst().doit(&root);
}


