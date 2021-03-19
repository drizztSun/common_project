/*
255. Verify Preorder Sequence in Binary Search Tree


Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Consider the following binary search tree: 

     5
    / \
   2   6
  / \
 1   3
Example 1:

Input: [5,2,6,1,3]
Output: false
Example 2:

Input: [5,2,1,3,6]
Output: true
Follow up:
Could you do it using only constant space complexity?



*/
#include <functional>
#include <vector>
#include <stack>

using std::stack;
using std::vector;



class VerifyBSTPreorder {

    /*
        255.Verify-Preorder-Sequence-in-Binary-Search-Tree
        解法1：常规的DFS
        根据preorder的首元素（根节点）通过大小的比较，将后续元素分为属于其左子树和右子树的子区间，分别递归调用

        bool DFS(vector<int>& preorder, int start, int end)。
        边界条件：到end-start<=1时，就可以返回true

        注意到，第一轮遍历判定完根的左子树/右子树的范围之后，还需要在第二轮对该左子树元素再做一回遍历来确定它的左子树/右子树范围。不断递归。每一轮/每一层都会要把所有序列都遍历一遍。考虑到会有log(n)层，此题需要o(NlogN)的时间复杂度。

        解法2：巧妙的o(n)解法
        对于任意一个元素a，我们考虑以它为根的子树的序列表达，一定是类似... {a[xxxxxx][yyyyyy]} ...的形式。大括号内的是以a为根的子树的元素。我们可以知道x肯定都比a小，y肯定都比a大。那么y之后的元素呢？实际上它们肯定也会比a大。因为它们肯定是与a子树相对的右子树，或者a的更高层节点的某个右子树。因此，x之后的任何元素都应该比a大。

        所以，我们遍历这个序列，一旦出现先后的两个元素满足 a<b（a和b不需要相邻），那么b之后出现的任何元素c必须要比a大，任何c<a的情况都是不合法的。

        于是本题转化为：如何在遍历preorder的过程中，不断更新a<b，使得a不断得以抬升（即维护当前所有a<b配对中最大的a），一旦出现后续的c<a即可宣告false

        怎么维护一个最新（尽量大）的a<b呢？那就是用栈来维护一个递减的序列。一旦遍历的过程中出现了preOrder[i]>Stack.top()，那就说明出现了递增序列，需要不断退栈直至保证栈本身仍然是递减的。在退栈的过程中，就不断遇到a<b的情况，借机可以抬高a。
    
    */
    bool doit_dfs(vector<int>& preorder) 
    {
        std::function<bool()> DFS = [&](int start, int end)
        {
            if (end-start<=1) return true;
            
            int root=preorder[start];
            int i = start+1;
            while (i <= end && preorder[i] < root) i++;
                    
            for (int j = i; j <= end; j++)
            {
                if (preorder[j]<=root) return false;
            }
            return DFS(start+1, i-1) && DFS(i, end);
        };

        return DFS(0,preorder.size()-1);
    }
    

public:

    bool doit_stack(vector<int>& preorder) {
        
        stack<int> buff;
        int smaller = INT_MIN;

        for (int i = 0; i < preorder.size(); i++) {

            if (preorder[i] < smaller) return false;

            while (!buff.empty() && buff.top() < preorder[i]) {
                smaller = buff.top();
                buff.pop();
            }

            buff.push(preorder[i]);
        }

        return true;
    }


    /*
    
        A preorder sequence consist of nested structure of {Node, Left subtree, Right Subtree} triplet.

        To verify a preorder sequence, we only need to verify if the sequence has the characteristics of BST, which is, For every given node,:

        1. it's the lower bound to its right subtree
        2. it's the upper bound to its left subtree.
        We use the first characteristic to implement the solution:

        1. use a "lower" to keep track of current lower bound. Initially lower = INT_MIN, which means no lower bound at first.

        2. use a stack to store cadidates of next lower bound. stack would be kept in decreasing order.

        3. when loop through the sequence, preorder[i] should be greater than "lower", otherwise return false.

        4. If preorder[i] is greater than the stack top, which indicate preorder[i] is the first node of a right subtree, and we have to update "lower" to its parent node for validating rest of the node in this right subtree.
        We updae "lower" when removing stack top.
        For each remove operation, it's like moving up to upper level in BST, when the stack top is greater than preorder[i], the last removed item is its parent node.

        5. Push preorder[i] into stack as it could be parent node for nodes that haven't been visited yet.

        Here is the first solution with O(N) space conplexity
    */
    bool verifyPreorder(vector<int>& preorder) {
        int mini = INT_MIN;
        vector<int> stack;
        
        for(auto val: preorder) {
            if(val < mini)
                return false;
            while(stack.size() && stack.back() < val) {
                mini = stack.back();
                stack.pop_back();
            }
            stack.push_back(val);
        }
        return true;
    }

    /*
        With above concept in mind.
        Instead of using an outstanding stack, we can reuse the space of visited elements of preorder sequence.

        this way we can reduce space complexity to O(1) by and using pointer "idx" to keep track of the position of stack top.
    */
    bool doit_best(vector<int>& preorder) {
        int mini = INT_MIN;
        int idx = -1;
        
        for(auto val: preorder) {
            if(val < mini)
                return false;
            while(idx > -1 && preorder[idx] < val)
                mini = preorder[idx--];
            preorder[++idx] = val;
        }
        return true;
    }
};