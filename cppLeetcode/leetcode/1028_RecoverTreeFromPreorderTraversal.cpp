/*

 
 # 1028. Recover a Tree From Preorder Traversal

 # We run a preorder depth first search on the root of a binary tree.

 # At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)

 # If a node has only one child, that child is guaranteed to be the left child.

 # Given the output S of this traversal, recover the tree and return its root.


 # Example 1:

 # Input: "1-2--3--4-5--6--7"
 # Output: [1,2,5,3,4,6,7]

 # Example 2:

 # Input: "1-2--3---4-5--6---7"
 # Output: [1,2,5,3,null,6,null,4,null,7]

 # Example 3:
 # Input: "1-401--349---90--88"
 # Output: [1,401,null,349,88,90]

 # Definition for a binary tree node.
 
 
 */

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

 // Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     
 };

class RecoverFromPreorder {
    
    
    
public:
    
    TreeNode* doit(string S) {
    
        unordered_map<int, vector<TreeNode*>> buf;
        
        int i = 0;
        
        while (i < S.length()) {
            
            int j = i;
            while (j < S.length() && S[j] == '-') {
                j++;
            }
            
            int depth = j - i;
            i = j;
            
            int c = 0;
            while (j < S.length() && S[i] >= '0' && S[i] <= '9') {
                c = c * 10 + (S[i] - '0');
                i++;
            }
            
            TreeNode* n = new TreeNode(c);
            
            if (buf.count(depth -1) > 0)
                if (buf[depth-1].back()->left == nullptr) {
                    buf[depth-1].back()->left = n;
                }
                else {
                    buf[depth-1].back()->right = n;
                }
            buf[depth].push_back(n);
        }
        
        return buf[0].front();
    }
};

void test_1028_recover_tree_from_preorder_travels() {
    
    auto res1 = RecoverFromPreorder().doit("1-2--3--4-5--6--7");
    
    auto res2 = RecoverFromPreorder().doit("1-2--3---4-5--6---7");
                                           
    auto res3 = RecoverFromPreorder().doit("1-401--349---90--88");
    
    return;
}
