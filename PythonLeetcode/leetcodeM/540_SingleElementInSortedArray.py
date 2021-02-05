"""
540. Single Element in a Sorted Array

You are given a sorted array consisting of only integers where every element appears exactly twice,
except for one element which appears exactly once. Find this single element that appears only once.

Follow up: Your solution should run in O(log n) time and O(1) space.



Example 1:

Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:

Input: nums = [3,3,7,7,10,11,11]
Output: 10


Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5

"""


class SingleNonDuplicate:


    """
    Approach 2: Binary Search
    Intuition

    It makes sense to try and convert the linear search into a binary search.
    In order to use binary search, we need to be able to look at the middle item and then determine whether the solution is the middle item, or to the left, or to the right.
    The key observation to make is that the starting array must always have an odd number of elements (be odd-lengthed), because it has one element appearing once, and all the other elements appearing twice.

    Like the original array, the subarray containing the single element must be odd-lengthed. The subarray not containing it must be even-lengthed. So by taking a pair out of the middle and then calculating which side is now odd-lengthed, we have the information needed for binary search.

    Algorithm

    We start by setting lo and hi to be the lowest and highest index (inclusive) of the array, and then iteratively halve the array until we find the single element or until there is only one element left. We know that if there is only one element in the search space, it must be the single element, so should terminate the search.

    On each loop iteration, we find mid, and determine the odd/ evenness of the sides and save it in a variable called halvesAreEven. By then looking at which half the middle element's partner is in (either last element in the left subarray or first element in the right subarray), we can decide which side is now (or remained) odd-lengthed and set lo and hi to cover the part of the array we now know the single element must be in.

    The trickiest part is ensuring we update lo and hi correctly based on the values of mid and halvesAreEven. These diagrams should help you understand the cases. When solving problems like this, it's often good to draw a diagram and think really carefully about it to avoid off-by-one errors. Avoid using a guess and check approach.

    Case 1: Mid’s partner is to the right, and the halves were originally even.

    The right side becomes odd-lengthed because we removed mid's partner from it. We need to set lo to mid + 2 so that the remaining array is the part above mid's partner.


    """
    def doit_binary_search(self, nums):

        lo, hi = 0, len(nums) - 1
        
        while lo < hi:
            mid = lo + (hi - lo) // 2
            halves_are_even = (hi - mid) % 2 == 0
            if nums[mid + 1] == nums[mid]:
                if halves_are_even:
                    lo = mid + 2
                else:
                    hi = mid - 1
            elif nums[mid - 1] == nums[mid]:
                if halves_are_even:
                    hi = mid - 2
                else:
                    lo = mid + 1
            else:
                return nums[mid]
        return nums[lo]


    """
    Approach 3: Binary Search on Evens Indexes Only
    It turns out that we only need to binary search on the even indexes. This approach is more elegant than the last, although both are good solutions.
    
    Intuition
    
    The single element is at the first even index not followed by its pair. We used this property in the linear search algorithm, where we iterated over all of the even indexes until we encountered the first one not followed by its pair.
    
    Instead of linear searching for this index though, we can binary search for it.
    
    After the single element, the pattern changes to being odd indexes followed by their pair. This means that the single element (an even index) and all elements after it are even indexes not followed by their pair. Therefore, given any even index in the array, we can easily determine whether the single element is to the left or to the right.
    
    Algorithm
    
    We need to set up the binary search variables and loop so that we are only considering even indexes. The last index of an odd-lengthed array is always even, so we can set lo and hi to be the start and end of the array.
    
    We need to make sure our mid index is even. We can do this by dividing lo and hi in the usual way, but then decrementing it by 1 if it is odd. This also ensures that if we have an even number of even indexes to search, that we are getting the lower middle (incrementing by 1 here would not work, it'd lead to an infinite loop as the search space would not be reduced in some cases).
    
    Then we check whether or not the mid index is the same as the one after it.
    
    If it is, then we know that mid is not the single element, and that the single element must be at an even index after mid. Therefore, we set lo to be mid + 2. It is +2 rather than the usual +1 because we want it to point at an even index.
    If it is not, then we know that the single element is either at mid, or at some index before mid. Therefore, we set hi to be mid.
    Once lo == hi, the search space is down to 1 element, and this must be the single element, so we return it.
    
    Complexity Analysis

    Time complexity : O(logn). Same as the binary search above, except we are only binary searching half the elements, rather than all of them.
    
    Space complexity : O(1). Same as the other approaches. We are only using constant space to keep track of where we are in the search.
    """

    def doit_binary_search(self, nums):

        low, high = 0, len(nums) - 1

        while low < high:

            mid = (low + high) // 2

            if mid % 2 == 1:
                mid -= 1

            if nums[mid] == nums[mid+1]:
                low = mid + 2
            else:
                high = mid

        return nums[low]



if __name__ == '__main__':

    SingleNonDuplicate().doit_binary_search()

    SingleNonDuplicate().doit_binary_search()
