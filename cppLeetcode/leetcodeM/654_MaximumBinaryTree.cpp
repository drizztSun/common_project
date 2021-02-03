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
    
public:

    /*
        Using stack and Monotonic queue(decreasing)
        Using current value to create a node, if node.val is greater than any top in staock. Poping out it and being left of this node.
        Until stack.top() is larger than it, current node will be the right tree of top() node.
        finally, stack[0] will be root node.
    */
    TreeNode* doit_stack(vector<int>& nums) {
        
        vector<TreeNode*> st;
        
        for (auto c: nums) {
            
            TreeNode* cur = new TreeNode(c);
            
            while (!st.empty() && st.back()->val < c) {
                cur->left = st.back();
                st.pop_back();
            }
            
            if (!st.empty())
                st.back()->right = cur;
            
            st.push_back(cur);
        }
        
        return st[0];
    }

    /*
        Approach 1: Recursive Solution
        The current solution is very simple. We make use of a function construct(nums, l, r), which returns the maximum binary tree consisting of numbers within the indices ll and rr in the given numsnums array(excluding the r^{th}r 
        th
        element).

        The algorithm consists of the following steps:

        Start with the function call construct(nums, 0, n). Here, nn refers to the number of elements in the given numsnums array.

        Find the index, max_imax 
        i
        ​	
        , of the largest element in the current range of indices (l:r-1)(l:r−1). Make this largest element, nums[max\_i]nums[max_i] as the local root node.

        Determine the left child using construct(nums, l, max_i). Doing this recursively finds the largest element in the subarray left to the current largest element.

        Similarly, determine the right child using construct(nums, max_i + 1, r).

        Return the root node to the calling function.


        Complexity Analysis

        Time complexity : O(n^2). The function construct is called nn times. At each level of the recursive tree, we traverse over all the nn elements to find the maximum element. 
            In the average case, there will be a \log nlogn levels leading to a complexity of O\big(n\log n\big)O(nlogn). In the worst case, the depth of the recursive tree can grow upto nn, 
            which happens in the case of a sorted numsnums array, giving a complexity of O(n^2).

        Space complexity : O(n). The size of the setset can grow upto nn in the worst case. In the average case, the size will be \log nlogn for nn elements in numsnums, giving an average case complexity of O(logn)
    
    */
    
    TreeNode* doit(vector<int>&& nums) {

        std::function<TreeNode*(vector<int>&, int, int)> build = [&](vector<int>& nums, int s, int e) {
        
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
        };

        return build(nums, 0, nums.size()-1);
    }
};
