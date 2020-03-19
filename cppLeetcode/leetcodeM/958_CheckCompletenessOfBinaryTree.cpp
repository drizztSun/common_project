/*
 
 958. Check Completeness of a Binary Tree
 
 # 958. Check Completeness of a Binary Tree

 # Given a binary tree, determine if it is a complete binary tree.

 # Definition of a complete binary tree from Wikipedia:
 # In a complete binary tree every level, except possibly the last, is completely filled,
 # and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.


 # Example 1:

 # Input: [1,2,3,4,5,6]
 # Output: true
 # Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.

 # Example 2:

 # Input: [1,2,3,4,5,null,7]
 # Output: false
 # Explanation: The node with value 7 isn't as far left as possible.

 # Note:

 # The tree will have between 1 and 100 nodes.
 
 */

#include <vector>
using std::vector;

#include <queue>
using std::queue;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class IsCompleteTree {
    
public:
    
    
    // TLE, overflow, because 2 * v could be very big
    bool doit(TreeNode* root) {
        
        vector<std::pair<TreeNode*, int>> buf;
        buf.push_back({root, 1});
        int i = 0;
        
        while (i < buf.size()) {
            
            TreeNode *n = buf[i].first;
            int v = buf[i].second;
            i += 1;
            
            if (n) {
                buf.push_back({n->left, 2 * v});
                buf.push_back({n->right, 2 * v + 1});
            }
        }
        
        return buf.size() == buf.back().second;
    }
    
    bool doit1(TreeNode *root) {
        
        bool pre = true;
        queue<TreeNode*> nq;
        nq.push(root);
        
        while(!nq.empty()){
            TreeNode* node = nq.front();
            nq.pop();
            
            if(node == NULL){
                pre = false;
            }
            else{
                if(pre == false)
                    return false;
                
                nq.push(node->left);
                nq.push(node->right);
            }
            
        }
        
        return true;
    }
    
    
    // DFS
    bool isCompleteTree(TreeNode*& root, int i, int n) {
        
        if (!root)  return true;
        else if (i >= n) return false;
        return isCompleteTree(root->left, 2 * i + 1, n) && isCompleteTree(root->right, 2 * i + 2, n);
    }
    
    int countNodes(TreeNode*& root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    bool doit2(TreeNode* root) {
        
        return isCompleteTree( root, 0, countNodes(root));
    }
};


void test_958_check_completeness_of_binary_tree() {
    
    TreeNode r1(1);
    TreeNode r2(2);
    TreeNode r3(3);
    TreeNode r4(4);
    TreeNode r5(5);
    TreeNode r6(6);
    
    r1.left = &r2;
    r1.right = &r3;
    r2.left = &r4;
    r2.right = &r5;
    
    r1.right = &r3;
    r3.left = &r6;
    
    auto res1 = IsCompleteTree().doit1(&r1);
}
