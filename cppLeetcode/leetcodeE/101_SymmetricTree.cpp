/*
 
 
 101. Symmetric Tree
 
 Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

 For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
 
     1
    / \
   2   2
  / \ / \
 3  4 4  3

 But the following [1,2,2,null,3,null,3] is not:
 
   1
  / \
 2   2
  \   \
  3    3
 
 */


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class IsSymmetric {
    
public:
    
    bool search(TreeNode* l, TreeNode* r) {
        return (!l && !r) || (l && r && l->val == r->val && search(l->left, r->right) && search(l->right, r->left));
    }
    
    bool doit(TreeNode* root) {
        if (!root)
            return true;
        return search(root->left, root->right);
    }
};

void test_101_is_symmetric_tree() {
    
}
