"""
324. Wiggle Sort II

Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:

Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].
Example 2:

Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].
Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?



Explanation / Proof
I put the smaller half of the numbers on the even indexes and the larger half on the odd indexes, both from right to left:

Example nums = [1,2,...,7]      Example nums = [1,2,...,8] 

Small half:  4 . 3 . 2 . 1      Small half:  4 . 3 . 2 . 1 .
Large half:  . 7 . 6 . 5 .      Large half:  . 8 . 7 . 6 . 5
--------------------------      --------------------------
Together:    4 7 3 6 2 5 1      Together:    4 8 3 7 2 6 1 5
I want:

Odd-index numbers are larger than their neighbors.
Since I put the larger numbers on the odd indexes, clearly I already have:

Odd-index numbers are larger than or equal to their neighbors.
Could they be "equal to"? That would require some number M to appear both in the smaller and the larger half. It would be the largest in the smaller half and the smallest in the larger half. Examples again, where S means some number smaller than M and L means some number larger than M.

Small half:  M . S . S . S      Small half:  M . S . S . S .
Large half:  . L . L . M .      Large half:  . L . L . L . M
--------------------------      --------------------------
Together:    M L S L S M S      Together:    M L S L S L S M
You can see the two M are quite far apart. Of course M could appear more than just twice, for example:

Small half:  M . M . S . S      Small half:  M . S . S . S .
Large half:  . L . L . M .      Large half:  . L . M . M . M
--------------------------      --------------------------
Together:    M L M L S M S      Together:    M L S M S M S M
You can see that with seven numbers, three M are no problem. And with eight numbers, four M are no problem. Should be easy to see that in general, with n numbers, floor(n/2) times M is no problem. 
Now, if there were more M than that, then my method would fail. But... it would also be impossible:

If n is even, then having more than n/2 times the same number clearly is unsolvable, because you'd have to put two of them next to each other, no matter how you arrange them.
If n is odd, then the only way to successfully arrange a number appearing more than floor(n/2) times is if it appears exactly floor(n/2)+1 times and you put them on all the even indexes. 

And to have the wiggle-property, all the other numbers would have to be larger. But then we wouldn't have an M in both the smaller and the larger half.
So if the input has a valid answer at all, then my code will find one.

"""


class WiggleSort:
    """
        # Roughly speaking I put the smaller half of the numbers on the even indexes and the larger half on the odd indexes.
        1) sort the array,
        2) First half nums[:half:-1] smaller one, second half nums[half::-1] larger one
        3) nums[::2] even position, nums[1::2] odd position
    """
    def doit_sort(self, nums):
        nums.sort()
        half = len(nums[::2])
        nums[::2], nums[1::2] = nums[:half][::-1], nums[half:][::-1]

    """
        # Roughly speaking I put the smaller half of the numbers on the even indexes and the larger half on the odd indexes.
        1) sort the array,
        2) First half nums[half::-1], second half nums[:half:-1]
        3) nums[::2] even position, nums[1::2] odd position
    """
    # O(nlogn)
    def doit_sort(self, nums: list) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        nums.sort()
        half = len(nums[::2]) - 1
        nums[::2], nums[1::2] = nums[half::-1], nums[:half:-1]

    # O(n)
    def doit(self, nums: list) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        import random
        mid = len(nums) // 2

        def quickselect(arr, lo, hi, k):
            pivot = random.randint(lo, hi)
            arr[pivot], arr[hi] = arr[hi], arr[pivot]
            pivot = lo
            for i in range(lo, hi):
                if arr[i] < arr[hi]:
                    arr[i], arr[pivot] = arr[pivot], arr[i]
                    pivot += 1
            arr[pivot], arr[hi] = arr[hi], arr[pivot]
            if k == pivot:
                return arr[pivot]
            elif k < pivot:
                return quickselect(arr, lo, pivot - 1, k)
            else:
                return quickselect(arr, pivot + 1, hi, k)

        median = quickselect(nums, 0, len(nums) - 1, mid)

        # virtual index
        vi = lambda x: x * 2 + 1 if x < mid else (x - mid) * 2
        
        i, j, k = 0, 0, len(nums) - 1
        while j <= k:
            if nums[vi(j)] < median:
                nums[vi(j)], nums[vi(k)] = nums[vi(k)], nums[vi(j)]
                k -= 1
            elif nums[vi(j)] > median:
                nums[vi(j)], nums[vi(i)] = nums[vi(i)], nums[vi(j)]
                i += 1
                j += 1
            else:
                j += 1

