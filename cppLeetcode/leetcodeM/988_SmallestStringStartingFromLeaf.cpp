/*
 
 988. Smallest String Starting From Leaf
 
 Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z':
 a value of 0 represents 'a', a value of 1 represents 'b', and so on.

 Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.

 (As a reminder, any shorter prefix of a string is lexicographically smaller: for example, "ab" is lexicographically smaller than "aba".
 A leaf of a node is a node that has no children.)

 Example 1:
 
 Input: [0,1,2,3,4,3,4]
 Output: "dba"
 
 Example 2:
 
 Input: [25,1,3,1,3,0,2]
 Output: "adz"
 
 Example 3:
 
 Input: [2,2,1,null,1,0,null,0]
 Output: "abc"
 
 */

#include <string>
using std::string;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class SmallestFromLeaf {
    
    void search(TreeNode* node, string path, string& ans) {
        
        string cur = static_cast<char>('a' + node->val) + path;
        
        if (!node->left && !node->right) {
            
            if (ans.empty() || ans > cur)
                ans = cur;
            return;
        }

        if (node->left)
            search(node->left, cur, ans);
        
        if (node->right)
            search(node->right, cur, ans);
    }
    
public:
    
    string firstString;
    
    void dfs(TreeNode* root, string& history) {
        if (!root) return;
        history.insert(history.begin(), root->val+'a');
        if (!root->left && !root->right) {
            if (firstString == "" || firstString > history) {
                firstString = history;
            }
        } else {
            dfs(root->left, history);
            dfs(root->right, history);
        }
        history.erase(history.begin());
    }
    
    string smallestFromLeaf(TreeNode* root) {
        string history;
        dfs(root, history);
        return firstString;
    }
    
    string doit(TreeNode* root) {
        string ans;
        search(root, "", ans);
        return ans;
    }
};

void test_988_smallest_from_leaf() {
    
    TreeNode root(4);
    TreeNode l(0);
    TreeNode ll(1);
    TreeNode rr(1);
    
    root.left = &l;
    l.left = &ll;
    root.right = &rr;
    
    auto res1 = SmallestFromLeaf().doit(&root);
    return;
}
