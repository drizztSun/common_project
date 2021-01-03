"""
162. Find Peak Element

A peak element is an element that is strictly greater than its neighbors.

Given an integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞.

 

Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.
 

Constraints:

1 <= nums.length <= 1000
-231 <= nums[i] <= 231 - 1
nums[i] != nums[i + 1] for all valid i.
 

Follow up: Could you implement a solution with logarithmic complexity?

"""

class PeakElement:


    def doit_linear(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i, peak, ispeak = 0, 0, True
        while i < len(nums) - 1:
            if nums[i] > nums[i+1] and ispeak:
                return i

            ispeak = True if nums[i+1] > nums[i] else False
            i += 1

        return i if ispeak else None

    def doit_(self, nums):
        
        def checkPeak(nums, s, e):
            if s == e:
                return s
            elif s + 1 == e:
                return s if nums[s] > nums[e] else e 

            mid = (s + e) // 2
            if nums[mid-1] < nums[mid] > nums[mid+1] :
                return mid
            elif nums[mid-1] < nums[mid] < nums[mid+1]:
                return checkPeak(nums, mid+1, e)
            elif nums[mid-1] > nums[mid] > nums[mid+1]:
                return checkPeak(nums, s, mid)
            elif nums[mid-1] > nums[mid] < nums[mid+1]:
                s = checkPeak(nums, s, mid)
                if s:
                    s = checkPeak(nums, mid, e)
                return s
            else:
                return None

        return checkPeak(nums, 0, len(nums) - 1)

    """
    Approach 1: Linear Scan
    In this approach, we make use of the fact that two consecutive numbers nums[j]nums[j] and nums[j + 1]nums[j+1] are never equal. Thus, we can traverse over the numsnums array starting from the beginning. 
    Whenever, we find a number nums[i]nums[i], we only need to check if it is larger than the next number nums[i+1]nums[i+1] for determining if nums[i]nums[i] is the peak element. The reasoning behind this can be understood by taking the following three cases which cover every case into which any problem can be divided.

    Case 1. All the numbers appear in a descending order. In this case, the first element corresponds to the peak element. We start off by checking if the current element is larger than the next one. 
    The first element satisfies this criteria, and is hence identified as the peak correctly. In this case, we didn't reach a point where we needed to compare nums[i]nums[i] with nums[i-1]nums[i−1] also, to determine if it is the peak element or not.
    
    
    """
    

    """
        Approach 2: Recursive Binary Search
        Algorithm

        We can view any given sequence in numsnums array as alternating ascending and descending sequences. By making use of this, and the fact that we can return any peak as the result, we can make use of Binary Search to find the required peak element.

        In case of simple Binary Search, we work on a sorted sequence of numbers and try to find out the required number by reducing the search space at every step. In this case, we use a modification of this simple Binary Search to our advantage. We start off by finding the middle element, midmid from the given numsnums array. If this element happens to be lying in a descending sequence of numbers. or a local falling slope(found by comparing nums[i]nums[i] to its right neighbour), it means that the peak will always lie towards the left of this element. Thus, we reduce the search space to the left of midmid(including itself) and perform the same process on left subarray.

        If the middle element, midmid lies in an ascending sequence of numbers, or a rising slope(found by comparing nums[i]nums[i] to its right neighbour), it obviously implies that the peak lies towards the right of this element. Thus, we reduce the search space to the right of midmid and perform the same process on the right subarray.

        In this way, we keep on reducing the search space till we eventually reach a state where only one element is remaining in the search space. This single element is the peak element.

        To see how it works, let's consider the three cases discussed above again.



    """
    def doit_binary_search(self, nums: List[int]) -> int:
        def search(left, right):
            if left == right:
                return left
            
            mid = (left + right) // 2
            
            if nums[mid] > nums[mid+1]:
                return search(left, mid)
            
            return search(mid+1, right)
        
        return search(0, len(nums)-1)

    """
    Approach 3: Iterative Binary Search
    Algorithm

    The binary search discussed in the previous approach used a recursive method. We can do the same process in an iterative fashion also. This is done in the current approach.

    Complexity Analysis

    Time complexity : O\big(log_2(n)\big)O(log 
    2
    ​	
    (n)). We reduce the search space in half at every step. Thus, the total search space will be consumed in log_2(n)log 
    2
    ​	
    (n) steps. Here, nn refers to the size of numsnums array.

    Space complexity : O(1)O(1). Constant extra space is used.


    1) case 1, if always nums[mid] >  nums[mid+1], it gose to the left side, and 0 is the peak

    2) case 2, if always not nums[mid < nums[mid+1], it goes to the right side and last one is the peak

    3) or scope go into middle, and get the peak.

    *** It is not going to get the every peak, just one of those peaks

    """
    def doit_binary_search(self, nums: List[int]) -> int:
        l, r = 0, len(nums)-1
        
        while l < r:
            
            mid = (l + r) // 2
            
            if nums[mid] > nums[mid+1]:
                r = mid
            else:
                l = mid + 1
        return l