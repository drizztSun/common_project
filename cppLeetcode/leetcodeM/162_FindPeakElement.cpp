/*
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
*/
#include <vector>

using std::vector;


class PeakElement {

public:

    /*
        162.Find-Peak-Element
        解题思路：注意题目条件，1：相邻的元素不会相等。2： 首尾的斜率。

        我们可以根据mid本地的斜率来判断指针移动的方向，搜索方向朝向元素增大的一侧。

        因为 mid = left+(right-left)/2，所以在 while (left<right) 成立的情况下，mid永远都不会与right重合，因此 nums[mid+1]永远是合法的。 所以我们考察 nums[mid]和nums[mid+1]

                    if (nums[mid]>nums[mid+1])
                        right = mid;
                    else  // 要么右侧方向增大，要么mid本身就是极大点
                        left = mid+1;      
    */
    int findPeakElement(vector<int>& nums) 
    {

        int left = 0, right = nums.size()-1;
        int mid;
        
        while (left < right)
        {
            mid = left + (right-left)/2;
            
            if (nums[mid] > nums[mid+1])
                right = mid;
            else 
                left = mid+1;
        }
        
        return left;
    }
};