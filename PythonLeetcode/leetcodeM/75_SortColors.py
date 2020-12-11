"""
75. Sort Colors

Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Follow up:

Could you solve this problem without using the library's sort function?
Could you come up with a one-pass algorithm using only O(1) constant space?


Example 1:

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]
Example 3:

Input: nums = [0]
Output: [0]
Example 4:

Input: nums = [1]
Output: [1]


Constraints:

n == nums.length
1 <= n <= 300
nums[i] is 0, 1, or 2.

"""


class SetColors:

    """
    075.Sort-Colors
    难点在于如何in-palce实现。基本思想是设置三个指针：

    int left=0;
    int mid=0;
    int right=nums.size()-1;
    遍历mid指针，当遇到2号球时，便和right指针进行交换；遇到1号球时，继续前进；与到0号球时，便和left指针进行交换。 理解的难点在于：

    if (nums[mid]==0)
    {
      swap(nums[left],nums[mid]);
      left++;
      mid++;
    }
    因为left和mid初始位置相同，他们之间出现异步只是因为1号球的出现。所以这两个指针之间间隔的永远只会是1号球，所以当left和mid交换时，left指针传给mid的一定会是1号球而不是0号球。
    """

    def doit_twopointer(self, nums: list) -> None:

        left, right = 0, len(nums) - 1
        cur = 0

        while cur <= right:

            if nums[cur] == 0:
                nums[left], nums[cur] = nums[cur], nums[left]
                left += 1

            if nums[cur] == 2:
                nums[right], nums[cur] = nums[cur], nums[right]
                right -= 1
                continue

            cur += 1

    def doit_copy(self, nums: list) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """

        target = [0, 0, 0]

        for c in nums:
            target[c] += 1

        nums[:target[0]] = [0] * target[0]
        nums[target[0]+1: target[0] + target[1]] = [1] * target[1]
        nums[target[1] + target[0]:] = [2] * target[2]


