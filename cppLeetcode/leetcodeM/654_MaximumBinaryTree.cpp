/*
 
 
 654. Maximum Binary Tree
 
 
 Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

 The root is the maximum number in the array.
 The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
 The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
 Construct the maximum tree by the given array and output the root node of this tree.

 Example 1:
 Input: [3,2,1,6,0,5]
 Output: return the tree root node representing the following tree:

       6
     /   \
    3     5
     \    /
      2  0
        \
         1
 Note: The size of the given array will be in the range [1,1000].
 
 */

#include <vector>
using std::vector;

#include <stack>
using std::stack;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class ConstructMaximumBinaryTree {
    
    TreeNode* build(vector<int>& nums, int s, int e) {
        
        auto max_index = [](vector<int>& nums, int s, int e) {
            int index = s;
            for (int j = s; j < e + 1; j++)
                if (nums[j] > nums[index])
                    index = j;
            return index;
        };
        
        int m = max_index(nums, s, e);
        TreeNode *r = new TreeNode(nums[m]);
        if (s != m)
            r->left = build(nums, s, m-1);
        
        if (e != m)
            r->right = build(nums, m+1, e);
        
        return r;
    }
    
public:
    
    TreeNode* doit(vector<int>&& nums) {
        return build(nums, 0, nums.size()-1);
    }
    
    
    TreeNode* doit1(vector<int>&& nums){
         stack<TreeNode*> s;
         int n = nums.size();
        
         s.push(new TreeNode(nums[0]));
         TreeNode* temp, *root;
        
         for(int i = 1; i < n; i++)
         {
             while(!s.empty())
             {
                 if(s.top()->val < nums[i])
                 {
                     temp = s.top();
                     s.pop();
                 }
                 else
                 {
                     root = new TreeNode(nums[i]);
                     if(s.empty())
                     {
                         root->left = temp;
                     }
                     else
                     {
                         temp = s.top()->right;
                         s.top()->right = root;
                         root->left = temp;
                     }
                     s.push(root);
                     break;
                 }
             }
             if(s.empty())
             {
                 root = new TreeNode(nums[i]);
                 root->left = temp;
                 s.push(root);
             }
         }
        
         while(!s.empty())
         {
             temp = s.top();
             s.pop();
         }
        
         return temp;
    }
};


void test_654_maximum_binary_tree() {
    
    auto res = ConstructMaximumBinaryTree().doit(vector<int>{3,2,1,6,0,5});
    
    return;
}
