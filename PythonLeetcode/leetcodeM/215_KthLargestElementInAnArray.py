"""
215. Kth Largest Element in an Array

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order,
not the kth distinct element.

Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.



"""


"""
Approach 2: Quickselect
This textbook algorthm has \mathcal{O}(N)O(N) average time complexity. Like quicksort, it was developed by Tony Hoare, and is also known as Hoare's selection algorithm.

The approach is basically the same as for quicksort. For simplicity let's notice that kth largest element is the same as N - kth smallest element, hence one could implement kth smallest algorithm for this problem.

First one chooses a pivot, and defines its position in a sorted array in a linear time. This could be done with the help of partition algorithm.

To implement partition one moves along an array, compares each element with a pivot, and moves all elements smaller than pivot to the left of the pivot.

As an output we have an array where pivot is on its perfect position in the ascending sorted array, all elements on the left of the pivot are smaller than pivot, and all elements on the right of the pivot are larger or equal to pivot.

Hence the array is now split into two parts. If that would be a quicksort algorithm, one would proceed recursively to use quicksort for the both parts that would result in \mathcal{O}(N \log N)O(NlogN) time complexity. Here there is no need to deal with both parts since now one knows in which part to search for N - kth smallest element, and that reduces average time complexity to \mathcal{O}(N)O(N).

Finally the overall algorithm is quite straightforward :

Choose a random pivot.

Use a partition algorithm to place the pivot into its perfect position pos in the sorted array, move smaller elements to the left of pivot, and larger or equal ones - to the right.

Compare pos and N - k to choose the side of array to proceed recursively.


"""


class FindKthLargest:

    def doit_quicksort(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        import random

        def partition(left, right, pivot_index):
            pivot = nums[pivot_index]
            # 1. move pivot to end
            nums[pivot_index], nums[right] = nums[right], nums[pivot_index]

            # 2. move all smaller elements to the left
            store_index = left
            for i in range(left, right):
                if nums[i] < pivot:
                    nums[store_index], nums[i] = nums[i], nums[store_index]
                    store_index += 1

            # 3. move pivot to its final place
            nums[right], nums[store_index] = nums[store_index], nums[right]

            return store_index

        def select(left, right, k_smallest):
            """
            Returns the k-th smallest element of list within left..right
            """
            if left == right:  # If the list contains only one element,
                return nums[left]  # return that element

            # select a random pivot_index between
            pivot_index = random.randint(left, right)

            # find the pivot position in a sorted list
            pivot_index = partition(left, right, pivot_index)

            # the pivot is in its final sorted position
            if k_smallest == pivot_index:
                return nums[k_smallest]
            # go left
            elif k_smallest < pivot_index:
                return select(left, pivot_index - 1, k_smallest)
            # go right
            else:
                return select(pivot_index + 1, right, k_smallest)

        # kth largest is (n - k)th smallest
        return select(0, len(nums) - 1, len(nums) - k)

    """
        A naive solution would be sort the whole array and return the kth to last element
        O(NlogN) time
    """
    def doit_sort(self, nums: list, k: int) -> int:
        return sorted(nums)[-k]

    
    """
        A slightly improved solution is to maintain a min heap of size k, and return the element on top.
        O(NlogK) time
    """
    def doit_heap(self, nums: list, k: int) -> int:
        from heapq import heappush, heappop

        pq = [] #min heap of size k
        for x in nums:
            heappush(pq, x)
            if len(pq) > k: heappop(pq)
        return pq[0]

    def doit_(self, nums: list, k: int) -> int:
        from heapq import nlargest
        return nlargest(k, nums)[-1]

    """
        quick select (Hoare's selection algo)
        O(N) time
    """
    def doit_quickselect(self, nums: list, k: int) -> int:
        from random import randint
        def fn(lo, hi): 
            """Partition nums[lo:hi+1] into two parts"""
            p = randint(lo, hi) #random pivot
            nums[lo], nums[p] = nums[p], nums[lo] #relocate to front 
            p, lo = lo, lo+1
            while lo <= hi: 
                if nums[lo] < nums[p]: lo += 1
                elif nums[hi] > nums[p]: hi -= 1
                else: 
                    nums[lo], nums[hi] = nums[hi], nums[lo]
                    lo += 1
                    hi -= 1
            nums[p], nums[hi] = nums[hi], nums[p]
            return hi 
        
        lo, hi = 0, len(nums)
        while lo < hi: 
            p = fn(lo, hi-1)
            if p + k == len(nums): return nums[p]
            elif p + k > len(nums): hi = p
            else: lo = p + 1