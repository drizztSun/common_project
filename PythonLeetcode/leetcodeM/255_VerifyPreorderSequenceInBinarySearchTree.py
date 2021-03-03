"""
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


"""


class VerifyPreorder:

    def doit_stack(self, preorder: list) -> bool:
        
        st, smaller = [], float('-inf')
        
        for p in preorder:
            
            if p < smaller: return False
            
            while st and st[-1] < p:
                smaller = st.pop()
                
            st.append(p)
            
        return True

    def doit_O1(self, preorder: list) -> bool:
        
        idx, smaller = -1, float('-inf')
        
        
        for c in preorder:
            
            if c < smaller: return False
            
            while idx > - 1 and preorder[idx] < c:
                smaller = preorder[idx]
                idx -= 1
                
            idx += 1
            preorder[idx] = c
            
        return True
            
        
        