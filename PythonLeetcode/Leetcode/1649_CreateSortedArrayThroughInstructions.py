"""
1649. Create Sorted Array through Instructions

Given an integer array instructions, you are asked to create a sorted array from the elements in instructions.
You start with an empty container nums. For each element from left to right in instructions, insert it into nums.
The cost of each insertion is the minimum of the following:

   1) The number of elements currently in nums that are strictly less than instructions[i].
   2) The number of elements currently in nums that are strictly greater than instructions[i].

For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1)
(elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].

Return the total cost to insert all elements from instructions into nums. Since the answer may be large, return it modulo 10**9 + 7



Example 1:

Input: instructions = [1,5,6,2]
Output: 1
Explanation: Begin with nums = [].
Insert 1 with cost min(0, 0) = 0, now nums = [1].
Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
The total cost is 0 + 0 + 0 + 1 = 1.
Example 2:

Input: instructions = [1,2,3,6,5,4]
Output: 3
Explanation: Begin with nums = [].
Insert 1 with cost min(0, 0) = 0, now nums = [1].
Insert 2 with cost min(1, 0) = 0, now nums = [1,2].
Insert 3 with cost min(2, 0) = 0, now nums = [1,2,3].
Insert 6 with cost min(3, 0) = 0, now nums = [1,2,3,6].
Insert 5 with cost min(3, 1) = 1, now nums = [1,2,3,5,6].
Insert 4 with cost min(3, 2) = 2, now nums = [1,2,3,4,5,6].
The total cost is 0 + 0 + 0 + 0 + 1 + 2 = 3.
Example 3:

Input: instructions = [1,3,3,3,2,4,2,1,2]
Output: 4
Explanation: Begin with nums = [].
Insert 1 with cost min(0, 0) = 0, now nums = [1].
Insert 3 with cost min(1, 0) = 0, now nums = [1,3].
Insert 3 with cost min(1, 0) = 0, now nums = [1,3,3].
Insert 3 with cost min(1, 0) = 0, now nums = [1,3,3,3].
Insert 2 with cost min(1, 3) = 1, now nums = [1,2,3,3,3].
Insert 4 with cost min(5, 0) = 0, now nums = [1,2,3,3,3,4].
Insert 2 with cost min(1, 4) = 1, now nums = [1,2,2,3,3,3,4].
Insert 1 with cost min(0, 6) = 0, now nums = [1,1,2,2,3,3,3,4].
Insert 2 with cost min(2, 4) = 2, now nums = [1,1,2,2,2,3,3,3,4].
The total cost is 0 + 0 + 0 + 0 + 1 + 0 + 1 + 0 + 2 = 4.


Constraints:

1 <= instructions.length <= 105
1 <= instructions[i] <= 105


"""


"""
Overview
The problem is straightforward. We need to obtain the cost of inserting each element in sorted order and return the total cost.

How to determine the cost? According to the description, we need to find the number of elements on the left side strictly
less/larger than the current element.

One natural idea is to maintain a sorted array and search with Binary Search. However, the array insertion takes O(M),
given that M is the length of the array, which is too slow. We need something quicker.

Luckily, there are two helpful and fast data structures: Segment Tree and Binary Indexed Tree.

Also, if one is not familiar with those trees, a solution of simple modifications on Merge Sort is available.

Below, we will discuss three approaches: Segment Tree, Binary Indexed Tree, and Merge Sort.

At the end of the article, in Extra part, we will present some interesting relevant facts that may not be useful in the interview though.
We leave that for interested readers.

Complexity Analysis

Let N be the length of instructions and M be the maximum value in instructions.

Time Complexity: O(Nlog(M)). We need to iterate over instructions, and for each element, the time to find the left cost and right cost is O(log(M)), 
and we spend O(log(M)) inserting the current element into the Segment Tree. 

In total, we need O(N⋅log(M))=O(Nlog(M)).

Space Complexity: O(M), since we need an array of size 2M to store Segment Tree.

"""


class CreateSortedArray:

    """
    Updating the segment tree is also easy. We just need to add 1 to the node of the current element and all the path up to the root.

    Algorithm

    Step 1: Implement the Segment Tree. Since the tree is initialized to all zeros, only update and query needs to be implemented.

    Step 2: Iterate over instructions. For each element:

    Calculate the left cost (smaller cost) and right cost (larger cost).
    Add the minimal one to the total cost.
    Update the element into the Segment Tree.
    Step 3: Return the total cost after iteration.

    """
    def doit_segment_tree(self, instructions: list) -> int:
        # implement Segment Tree
        def update(index, value, tree, m):
            index += m
            tree[index] += value
            while index > 1:
                index >>= 1
                tree[index] = tree[index << 1] + tree[(index << 1)+1]

        def query(left, right, tree, m):
            result = 0
            left += m
            right += m
            while left < right:
                if left & 1:
                    result += tree[left]
                    left += 1
                left >>= 1
                if right & 1:
                    right -= 1
                    result += tree[right]
                right >>= 1
            return result

        MOD = 10**9+7
        m = max(instructions)+1
        tree = [0]*(2*m)
        cost = 0
        for x in instructions:
            left_cost = query(0, x, tree, m)
            right_cost = query(x+1, m, tree, m)
            cost += min(left_cost, right_cost)
            update(x, 1, tree, m)
        return cost % MOD

    """
    Approach 2: Binary Indexed Tree (BIT)
    Intuition
    
    Binary indexed tree (or Fenwick Tree, BIT) is a data structure similar to the segment tree that maintains information about the prefix.
    
    Compared with the segment tree, BIT has smaller space complexity and faster performance (same complexity but smaller constant) 
    but lower expandability. For example, it is hard for BIT to address the interval minimum problem while the segment tree can easily handle it.
    
    You can find some relevant tutorials on Reverse Pairs or Range Sum Query 2D - Mutable.
    
    Now, we will have a quick review of BIT and then explain how we can use it to tackle our problem.
    
    Like the segment tree, BIT empowers us to update the values of elements and to query the information from node 0 to node i. 
    It can answer both actions in \mathcal{O}(\log(M))O(log(M)) time, given that the size of BIT is \mathcal{O}(M)O(M).
    
    For intuitive understanding, it is not recommended to view BIT as a tree but as an array with parents relationship for beginners.
    """
    def dpit_bit(self, instructions: list) -> int:
        # implement Binary Index Tree
        def update(index, value, bit, m):
            index += 1
            while index < m:
                bit[index] += value
                index += index & -index

        def query(index, bit):
            index += 1
            result = 0
            while index >= 1:
                result += bit[index]
                index -= index & -index
            return result

        MOD = 10 ** 9 + 7
        m = max(instructions) + 2
        bit = [0] * m
        cost = 0

        n = len(instructions)
        for i in range(n):
            left_cost = query(instructions[i] - 1, bit)
            right_cost = i - query(instructions[i], bit)
            cost += min(left_cost, right_cost)
            update(instructions[i], 1, bit, m)
        return cost % MOD

    def test_merge_sort(self, instructions: list) -> int:
        n = len(instructions)
        smaller = [0] * n
        larger = [0] * n
        temp = [0] * n  # record some temporal information

        def sort_smaller(arr, left, right):
            if left == right:
                return
            mid = (left + right) // 2
            sort_smaller(arr, left, mid)
            sort_smaller(arr, mid + 1, right)
            merge_smaller(arr, left, right, mid)

        def merge_smaller(arr, left, right, mid):
            # merge [left, mid] and [mid+1, right]
            i = left
            j = mid + 1
            k = left
            # use temp[left...right] to temporarily store sorted array
            while i <= mid and j <= right:
                if arr[i][0] < arr[j][0]:
                    temp[k] = arr[i]
                    k += 1
                    i += 1
                else:
                    temp[k] = arr[j]
                    smaller[arr[j][1]] += i - left
                    k += 1
                    j += 1

            while i <= mid:
                temp[k] = arr[i]
                k += 1
                i += 1
            while j <= right:
                temp[k] = arr[j]
                smaller[arr[j][1]] += i - left
                k += 1
                j += 1
            # restore from temp
            for i in range(left, right + 1):
                arr[i] = temp[i]

        def sort_larger(arr, left, right):
            if left == right:
                return
            mid = (left + right) // 2
            sort_larger(arr, left, mid)
            sort_larger(arr, mid + 1, right)
            merge_larger(arr, left, right, mid)

        def merge_larger(arr, left, right, mid):
            # merge [left, mid] and [mid+1, right]
            i = left
            j = mid + 1
            k = left
            # use temp[left...right] to temporarily store sorted array
            while i <= mid and j <= right:
                if arr[i][0] <= arr[j][0]:
                    temp[k] = arr[i]
                    k += 1
                    i += 1
                else:
                    temp[k] = arr[j]
                    larger[arr[j][1]] += mid - i + 1
                    k += 1
                    j += 1

            while i <= mid:
                temp[k] = arr[i]
                k += 1
                i += 1
            while j <= right:
                temp[k] = arr[j]
                larger[arr[j][1]] += mid - i + 1
                k += 1
                j += 1
            # restore from temp
            for i in range(left, right + 1):
                arr[i] = temp[i]

        MOD = 10 ** 9 + 7
        cost = 0

        arr_smaller = [[v, i] for i, v in enumerate(instructions)]
        arr_larger = [[v, i] for i, v in enumerate(instructions)]

        sort_smaller(arr_smaller, 0, n - 1)
        sort_larger(arr_larger, 0, n - 1)

        for i in range(n):
            cost += min(smaller[i], larger[i])
        return cost % MOD