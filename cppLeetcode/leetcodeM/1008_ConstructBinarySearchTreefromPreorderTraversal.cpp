/*
 
 
 # 1008. Construct Binary Search Tree from Preorder Traversal

 # Return the root node of a binary search tree that matches the given preorder traversal.

 # (Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val,
 # and any descendant of node.right has a value > node.val.
 # Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)


 # Example 1:

 # Input: [8,5,1,7,10,12]
 # Output: [8,5,10,1,7,null,12]
 
 
 */

#include <algorithm>
#include <vector>

using std::vector;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 
class BstFromPreorder {
    
public:
    
    TreeNode* doit(vector<int>&& preorder) {
        
        vector<TreeNode*> buf;
        TreeNode* root = nullptr;
        
        for (auto c : preorder) {
            TreeNode* a = new TreeNode(c);
            
            if (buf.empty()) {
                buf.push_back(a);
                if (!root)
                    root = a;
            } else if (buf.back()->val > c) {
                buf.back()->left = a;
                buf.push_back(a);
            } else {
                TreeNode* last = nullptr;
                while ( !buf.empty() && buf.back()->val < c) {
                    last = buf.back();
                    buf.pop_back();
                }
                last->right = a;
                buf.push_back(a);
            }
        }
        
        return root;
    }
    
    
    TreeNode* doit2(vector<int>& preorder) {
        vector<int> inorder(preorder);
        std::sort(inorder.begin(), inorder.end());
        int inL = 0, inR = inorder.size()-1, prL = 0, prR = preorder.size()-1;
        return helper(preorder, prL, prR, inorder, inL, inR);
    }
    
    TreeNode* helper(vector<int>& preorder, int prL, int prR, vector<int>& inorder, int inL, int inR)
    {
        if(inL > inR || prL > prR) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[prL]);
        
        // cout << prL << " " << prR << " " << root->val << "\n";
        if(prL == prR) {
            return root;
        }
         
        auto itr = (lower_bound(inorder.begin(), inorder.end(), preorder[prL]) - inorder.begin());
        //Left subtree
        int l_prL = prL+1, l_prR;
        int l_inL = inL, l_inR = itr-1;
        l_prR = l_prL + (itr-inL) -1 ;
        //Right subtree
        int r_prL, r_prR = prR;
        int r_inL = itr+1, r_inR = inR;
        r_prL = l_prR + 1;
        
        root->left = helper(preorder, l_prL, l_prR, inorder, l_inL, l_inR);
        root->right = helper(preorder, r_prL, r_prR, inorder, r_inL, r_inR);
        
        return root;
    }
};


void test_1008_constrcut_binary_search_tree_from_preorder_traversal() {
    
    auto res = BstFromPreorder().doit(vector<int>{8,5,1,7,10,12});
    
    return;
}
