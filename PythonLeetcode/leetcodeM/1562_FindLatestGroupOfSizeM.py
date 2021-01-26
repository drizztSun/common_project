"""
1562. Find Latest Group of Size M

Given an array arr that represents a permutation of numbers from 1 to n. You have a binary string of size n that initially has all its bits set to zero.

At each step i (assuming both the binary string and arr are 1-indexed) from 1 to n, the bit at position arr[i] is set to 1. 
You are given an integer m and you need to find the latest step at which there exists a group of ones of length m. A group of ones is a contiguous substring of 1s such that it cannot be extended in either direction.

Return the latest step at which there exists a group of ones of length exactly m. If no such group exists, return -1.

 

Example 1:

Input: arr = [3,5,1,2,4], m = 1
Output: 4
Explanation:
Step 1: "00100", groups: ["1"]
Step 2: "00101", groups: ["1", "1"]
Step 3: "10101", groups: ["1", "1", "1"]
Step 4: "11101", groups: ["111", "1"]
Step 5: "11111", groups: ["11111"]
The latest step at which there exists a group of size 1 is step 4.
Example 2:

Input: arr = [3,1,5,4,2], m = 2
Output: -1
Explanation:
Step 1: "00100", groups: ["1"]
Step 2: "10100", groups: ["1", "1"]
Step 3: "10101", groups: ["1", "1", "1"]
Step 4: "10111", groups: ["1", "111"]
Step 5: "11111", groups: ["11111"]
No group of size 2 exists during any step.
Example 3:

Input: arr = [1], m = 1
Output: 1
Example 4:

Input: arr = [2,1], m = 2
Output: 2
 

Constraints:

n == arr.length
1 <= n <= 10^5
1 <= arr[i] <= n
All integers in arr are distinct.
1 <= m <= arr.length

"""


class LastestStepGroup:

    """
        Explanation
        When we set bit a, where a = A[i],
        we check the length of group on the left length[a - 1]
        also the length of group on the right length[a + 1].
        Then we update length[a - left], length[a + right] to left + right + 1.

        Note that the length value is updated on the leftmost and the rightmost bit of the group.
        The length value inside the group may be out dated.

        As we do this, we also update the count of length.
        If count[m] > 0, we update res to current step index i + 1.


        Complexity
        Time O(N)
        Space O(N)


        Solution 1: Count all lengths
    """
    def doit_(self, A: list, m: int) -> int:
        if m == len(A): return m
        length = [0] * (len(A) + 2)
        res = -1
        for i, a in enumerate(A):
            left, right = length[a - 1], length[a + 1]
            if left == m or right == m:
                res = i
            length[a - left] = length[a + right] = left + right + 1
        return res

    def doit_disjoint(self, arr: list, m: int) -> int:
        
        from collections import defaultdict
        if m == len(arr): return m
        
        parent = defaultdict(int)
        size = defaultdict(int)#rank
        
        def find(x):
            if x not in parent:
                parent[x] = x
                size[x] = 1
            root = x
            while root != parent[root]:
                root = parent[root]
            while x != root:
                x, parent[x] = parent[x], root
            return root
        
        def union(x, y):
            x, y = find(x), find(y)
            if x == y: return
            if size[x] > size[y]:
                parent[y] = x
                size[x] += size[y]
            else:
                parent[x] = y
                size[y] += size[x]

        res = -1
        step = 0
        for i in arr:
            step += 1
            parent[i] = i
            size[i] = 1
            if i-1 in parent:
                if size[find(i-1)] == m:
                    res = step-1
                union(i,i-1)
            if i+1 in parent:
                if size[find(i+1)] == m:
                    res = step-1
                union(i,i+1)
            
        return res

        pass