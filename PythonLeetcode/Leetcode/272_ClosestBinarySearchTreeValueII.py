"""
270. Closest Binary Search Tree Value

Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:

Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.
Example:

Input: root = [4,2,5,1,3], target = 3.714286

    4
   / \
  2   5
 / \
1   3

Output: 4



# 272 Cloest Binary Search Tree Value II

# Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

# Note:

# Given target value is a floating point.
# You may assume k is always valid, that is: k ? total nodes.
# You are guaranteed to have only one unique set of k values in the BST that are closest to the target.


# Follow up:
# Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

# Hint:

# Consider implement these two helper functions:
# getPredecessor(N), which returns the next smaller node to N.
# getSuccessor(N), which returns the next larger node to N.
# Try to assume that each node has a parent pointer, it makes the problem much easier.
# Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
# You would need two stacks to track the path in finding predecessor and successor node separately.



"""



"""
Overview
The problem is a BST variation of the "kth-smallest" classical problem. It is popular both in Google and Facebook, 
but these two companies are waiting for you to show different approaches to this problem. We're proposing 3 solutions here, and it's more an overview.

Prerequisites

Because of that, you might want first to check out the list of prerequisites:

Inorder traversal of BST is an array sorted in the ascending order. To compute inorder traversal follow the direction Left -> Node -> Right.

Closest BST value: find one closest element.

kth-smallest problem for the array could be solved by using heap in \mathcal{O}(N \log k)O(Nlogk) time, or by using quickselect in \mathcal{O}(N)O(N) time.

Google vs. Facebook

There are three ways to solve the problem:

Approach 1. Sort, O(NlogN) time. The idea is to convert BST into an array, sort it by the distance to the target, and return the k closest elements.

Approach 2. Facebook-friendly, heap, \mathcal{O}(N \log k)O(Nlogk) time. We could use the heap of capacity k, sorted by the distance to the target. 
It's not an optimal but very straightforward solution - traverse the tree, push the elements into the heap, and then return this heap. 
Facebook interviewer would insist on implementing this solution because the interviews are a bit shorter than Google ones, 
and it's important to get problem solved end-to-end.

Approach 3. Google-friendly, quickselect, \mathcal{O}(N)O(N) time. Here you could find a very detailed explanation of quickselect algorithm. 
In this article, we're going to provide a relatively brief implementation. Google guys usually prefer the best-time solutions, well-structured clean skeleton, 
even if you have no time to implement everything in time end-to-end.

"""


class CloestBinarySearchTreeValuI:

    def doit_(self, root, target: float) -> int:

        res, absres = -1, float('inf')
        def search(node):
            nonlocal res, absres
            if not node:
                return

            if abs(node.val - target) < absres:
                absres = abs(node.val - target)
                res = node.val

            if node.val > target:
                search(node.left)
            else:
                search(node.right)

        search(root)
        return res


class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class CloestBinarySearchTreeValuII:

    """
    Approach 1: Recursive Inorder + Sort, O(N log N) time

    Complexity Analysis

    Time complexity: O(NlogN). O(N) to build inorder traversal and then O(NlogN) to sort it.

    Space complexity: O(N) to store list nums of NN elements.
    """
    def doit_sort_inorder(self, root: TreeNode, target: float, k: int) -> list:
        def inorder(r: TreeNode):
            return inorder(r.left) + [r.val] + inorder(r.right) if r else []

        nums = inorder(root)
        nums.sort(key=lambda x: abs(x - target))
        return nums[:k]

    """
    Approach 2: Recursive Inorder + Heap, O(N log k) time
    Algorithm

    Instantiate the heap with "less close element first" strategy so that the heap contains the elements that are closest to the target.
    
    Use inorder traversal to traverse the tree following the direction Left -> Node -> Right.
    
    Push all elements into heap during the traversal, keeping the heap size less than or equal to kk.
    As a result, the heap contains kk elements that are closest to target. Convert it into a list and return.
    
    Optimisations

    One could optimize the solution by adding the stop condition. Inorder traversal pops the elements in the sorted order. 
    Hence once the distance of the current element to the target becomes greater than the distance of the first element in a heap, 
    one could stop the computations. The overall worst-case time complexity would be still \mathcal{O}(N \log k)O(Nlogk), 
    but the average time could be improved to \mathcal{O}(H \log k)O(Hlogk), where HH is a tree height.
    
    Complexity Analysis
    
    Time complexity: \mathcal{O}(N \log k)O(Nlogk) to push N elements into the heap of the size kk.
    
    Space complexity: \mathcal{O}(k + H)O(k+H) to keep the heap of k elements and the recursion stack of the tree height.
    
    """
    # O(n*logk) <inorder>
    def doit_heap_inorder(self, root: TreeNode, target: float, k: int) -> list:
        from heapq import heappush, heappop
        buff = []
        def inorder(node):

            if not node:
                return

            inorder(node.left)
            heappush(buff, (-abs(node.val - target), node.val))
            if len(buff) > k:
                heappop(buff)
            inorder(node.right)

        inorder(root)
        return [x for _, x in buff]

    """
    Approach 3: QuickSelect, O(N) time.
Hoare's selection algorithm

Quickselect is a textbook algorithm typically used to solve the problems "find kth something": kth smallest, kth largest, etc. Like quicksort, quickselect was developed by Tony Hoare, and also known as Hoare's selection algorithm.

It has \mathcal{O}(N)O(N) average time complexity and widely used in practice. It is worth to note that its worst-case time complexity is \mathcal{O}(N^2)O(N 
2
 ), although the probability of this worst-case is negligible.

The approach is the same as for quicksort.

One chooses a pivot and defines its position in a sorted array in a linear time using the so-called partition algorithm.

As an output, we have an array where the pivot is on its perfect position in the ascending sorted array, sorted by the frequency. All elements on the left of the pivot are more close to the target than the pivot, and all elements on the right are less close or on the same distance from the target.

The array is now split into two parts. If by chance, our pivot element took kth final position, then kk elements on the left are these kk closest elements we're looking for. If not, we can choose one more pivot and place it in its perfect position.
    
    Complexity Analysis

Time complexity: \mathcal{O}(N)O(N), \mathcal{O}(N^2)O(N 
2
 ) in the worst case. Please refer to this card for the good detailed explanation of Master Theorem. Master Theorem helps to get an average complexity by writing the algorithm cost as T(N) = a T(N / b) + f(N)T(N)=aT(N/b)+f(N). Here we have an example of Master Theorem case III: T(N) = T \left(\frac{N}{2}\right) + NT(N)=T( 
2
N
​	
 )+N, that results in \mathcal{O}(N)O(N) time complexity. That's the case of random pivots.

In the worst-case of constantly bad chosen pivots, the problem is not divided by half at each step, it becomes just one element less, that leads to \mathcal{O}(N^2)O(N 
2
 ) time complexity. It happens, for example, if at each step you choose the pivot not randomly, but take the rightmost element. For the random pivot choice, the probability of having such a worst-case is negligibly small.

Space complexity: \mathcal{O}(N)O(N) to store nums.

    """
    def doit_quicksort_inorder(self, root: TreeNode, target: float, k: int) -> list:
        from random import randint

        def inorder(r: TreeNode):
            return inorder(r.left) + [r.val] + inorder(r.right) if r else []

        def partition(pivot_idx, left, right):
            pivot_dist = dist(pivot_idx)

            # 1. move pivot to end
            nums[right], nums[pivot_idx] = nums[pivot_idx], nums[right]
            store_idx = left

            # 2. move more close elements to the left
            for i in range(left, right):
                if dist(i) < pivot_dist:
                    nums[i], nums[store_idx] = nums[store_idx], nums[i]
                    store_idx += 1

            # 3. move pivot to its final place
            nums[right], nums[store_idx] = nums[store_idx], nums[right]

            return store_idx

        def quickselect(left, right):
            """
            Sort a list within left..right till kth less close element
            takes its place.
            """
            # base case: the list contains only one element
            if left == right:
                return

                # select a random pivot_index
            pivot_idx = randint(left, right)

            # find the pivot position in a sorted list
            true_idx = partition(pivot_idx, left, right)

            # if the pivot is in its final sorted position
            if true_idx == k:
                return

            if true_idx < k:
                # go left
                quickselect(true_idx, right)
            else:
                # go right
                quickselect(left, true_idx)

        nums = inorder(root)
        dist = lambda idx: abs(nums[idx] - target)
        quickselect(0, len(nums) - 1)
        return nums[:k]