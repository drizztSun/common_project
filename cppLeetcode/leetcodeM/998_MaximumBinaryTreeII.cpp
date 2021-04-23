/*
 
 998. Maximum Binary Tree II
 
 We are given the root node of a maximum tree: a tree where every node has a value greater than any other value in its subtree.

 Just as in the previous problem, the given tree was constructed from an list A (root = Construct(A)) recursively with the following Construct(A) routine:

 If A is empty, return null.
 Otherwise, let A[i] be the largest element of A.  Create a root node with value A[i].
 The left child of root will be Construct([A[0], A[1], ..., A[i-1]])
 The right child of root will be Construct([A[i+1], A[i+2], ..., A[A.length - 1]])
 Return root.
 Note that we were not given A directly, only a root node root = Construct(A).

 Suppose B is a copy of A with the value val appended to it.  It is guaranteed that B has unique values.

 Return Construct(B).
 
 Example 1:
 
 Input: root = [4,1,3,null,null,2], val = 5
 Output: [5,4,null,1,3,null,null,2]
 Explanation: A = [1,4,2,3], B = [1,4,2,3,5]
 
 
 Example 2:
 
 Input: root = [5,2,4,null,1], val = 3
 Output: [5,2,4,null,1,null,3]
 Explanation: A = [2,1,5,4], B = [2,1,5,4,3]
 
 Example 3:
 
 Input: root = [5,2,3,null,1], val = 4
 Output: [5,2,4,null,1,3]
 Explanation: A = [2,1,5,3], B = [2,1,5,3,4]
 
 */


#include <vector>
#include <stack>
#include <functional>

using std::vector;
using std::stack;

class InsertIntoMaxTreeII {

    //Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

public:

    /*
        For any one who can't understand the question. I give my explanation.

        1. the given tree was constructed from an list A (root = Construct(A)). So, List A = new ArrayList();
        2. Suppose B is a copy of A with the value val appended to it. So, B = new ArrayList(A) and B.add(val);
        3. The left child of root will be Construct([A[0], A[1], ..., A[i-1]]),
            The right child of root will be Construct([A[i+1], A[i+2], ..., A[A.length - 1]]).
            in this case A represent B, B[B.length-1] = val, So.
        4. If val is the largest, i = B.length-1, the root node's value is val, i=0 to i-1 are in the left child of root.
            This explains why when val > root.val, root should be the left child of new node with value val.
        5. Else val is not the largest, the new node with value val is always the right child of root.
    */

    /*
        Solution 1: Recursion
        If root.val > val, recusion on the right.
        Else, put right subtree on the left of new node TreeNode(val)

        Time Complexity:
        O(N) time,
        O(N) recursion space.
    */
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        if (root && root->val > val) {
            root->right = insertIntoMaxTree(root->right, val);
            return root;
        }
        TreeNode* node = new TreeNode(val);
        node->left = root;
        return node;        
    }

    /*
        Solution 2: Iteration
        Search on the right, find the node that cur.val > val > cur.right.val
        Then create new node TreeNode(val),
        put old cur.right as node.left,
        put node as new cur.right.

        Time Complexity:
        O(N) time,
        O(1) space
    */
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        TreeNode* node = new TreeNode(val), *cur = root;
        if (root->val < val) {
            node->left = root;
            return node;
        }
        while (cur->right && cur->right->val > val) {
            cur = cur->right;
        }
        node->left = cur->right;
        cur->right = node;
        return root;
    }
    
    TreeNode* doit_(TreeNode* root, int val) {

        if (!root) return new TreeNode(val);
        
        TreeNode *parent = nullptr, *node = root;
        
        while (node && node->val > val) {
            parent = node;
            node =  node->right;
        }
        
        TreeNode *n = new TreeNode(val);
        
        if (!parent) {
            n->left = node;
            root = n;
        } else {
            parent->right = n;
            n->left = node;
        }
        
        return root;
    }
    
    TreeNode* doit_recursive(TreeNode* root, int val) {

        std::function<TreeNode*(TreeNode*, int)> search = [&](TreeNode* root, int val) {
            if (!root) return new TreeNode(val);
            
            if (root->val < val) {
                TreeNode *now = new TreeNode(val);
                now->left = root;
                return now;
            } else {
                root->right = search(root->right, val);
                return root;
            }
        };

        return search(root, val);
    }
};