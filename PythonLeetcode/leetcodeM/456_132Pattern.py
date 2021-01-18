"""
456. 132 Pattern

Given an array of n integers nums, a 132 pattern is a subsequence of three integers
nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].

Return true if there is a 132 pattern in nums, otherwise, return false.

Follow up: The O(n^2) is trivial, could you come up with the O(n logn) or the O(n) solution?



Example 1:

Input: nums = [1,2,3,4]
Output: false
Explanation: There is no 132 pattern in the sequence.
Example 2:

Input: nums = [3,1,4,2]
Output: true
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:

Input: nums = [-1,3,2,0]
Output: true
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].


Constraints:

n == nums.length
1 <= n <= 104
-109 <= nums[i] <= 109



"""


class Find132pattern:

    def doit_stack_1(self, nums) -> bool:
        from itertools import accumulate
        min_list = list(accumulate(nums, min))
        stack, n = [], len(nums)

        for j in range(n - 1, -1, -1):
            if nums[j] > min_list[j]:
                while stack and stack[-1] <= min_list[j]:
                    stack.pop()
                if stack and stack[-1] < nums[j]:
                    return True
                stack.append(nums[j])
        return False

    """
        O(n)
    """

    def doit_stack(self, nums: list) -> bool:

        i = len(nums) - 1
        st = [] 
        last = float('-inf')
        
        # st is a ascending stack[ i, j]. iterate from end to start, so for index, i > j and also nums[i] < nums[j]
        # also we have last to keep the popout element, it must be smaller than top one in
        # last < st[-1], index[last] > index[st[-1]]
        # so any nums[i] < last, will makt it done, nums[i] < last < st[-1], i < k < j 

        while i >= 0:
            if nums[i] < last:
                return True
            else:
                while st and st[-1] < nums[i]:
                    last = st.pop()

            st.append(nums[i])

            i -= 1

        return False

    """
        Approach 5: Binary Search
        Algorithm

        In the last approach, we've made use of a separate stackstack to push and pop the nums[k]nums[k]'s. But, we can also note that when we reach the index jj while scanning backwards for finding nums[k]nums[k], the stackstack can contain atmost n-j-1n−j−1 elements. Here, nn refers to the number of elements in numsnums array.

        We can also note that this is the same number of elements which lie beyond the j^{th}j 
        th
        index in numsnums array. We also know that these elements lying beyond the j^{th}j 
        th
        index won't be needed in the future ever again. Thus, we can make use of this space in numsnums array instead of using a separate stackstack. The rest of the process can be carried on in the same manner as discussed in the last approach.

        We can try to go for another optimization here. Since, we've got an array for storing the potential nums[k]nums[k] values now, we need not do the popping process for a min[j]min[j] to find an element just larger than min[j]min[j] from amongst these potential values.

        Instead, we can make use of Binary Search to directly find an element, which is just larger than min[j]min[j] in the required interval, if it exists. If such an element is found, we can compare it with nums[j]nums[j] to check the 132 criteria. Otherwise, we continue the process as in the last approach.
        
        Complexity Analysis

        Time complexity : O(nlogn). Filling minmin array requires O(n) time. The second traversal is done over the whole numsnums array of length nn. For every current nums[j] we need to do the Binary Search, which requires O(logn). 
        In the worst case, this Binary Search will be done for all the nn elements, and the required element won't be found in any case, leading to a complexity of O\big(n \log n\big)O(nlogn).

        Space complexity : O(n). minmin array of size nn is used.


        if (nums.length < 3)
            return false;
        int[] min = new int[nums.length];
        min[0] = nums[0];

        for (int i = 1; i < nums.length; i++)
            min[i] = Math.min(min[i - 1], nums[i]);

        for (int j = nums.length - 1, k = nums.length; j >= 0; j--) {
            if (nums[j] > min[j]) {
                k = Arrays.binarySearch(nums, k, nums.length, min[j] + 1);
                if (k < 0)
                    k = -1 - k;
                if (k < nums.length && nums[k] < nums[j])
                    return true;
                nums[--k] = nums[j];
            }
        }
        return false;
    """
    def doit_binary_search(self, nums: list) -> list:
        import bisect

        st = []

        for c in nums:

            while st and st[-1] 



 

        




if __name__ == '__main__':

    Find132pattern().doit_stack([4, 6, 5, 1])

    Find132pattern().doit_stack([1,0,1,-4,-3])

    Find132pattern().doit_stack([1,2,3,4])

    Find132pattern().doit_stack([3, 1, 4, 2])

    Find132pattern().doit_stack([-1, 3, 2, 0])