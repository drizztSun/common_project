/*
81. Search in Rotated Sorted Array II

You are given an integer array nums sorted in ascending order (not necessarily distinct values), and an integer target.

Suppose that nums is rotated at some pivot unknown to you beforehand (i.e., [0,1,2,4,4,4,5,6,6,7] might become [4,5,6,6,7,0,1,2,4,4]).

If target is found in the array return its index, otherwise, return -1.

 

Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
 

Constraints:

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
nums is guaranteed to be rotated at some pivot.
-104 <= target <= 104
 

Follow up: This problem is the same as Search in Rotated Sorted Array, where nums may contain duplicates. Would this affect the run-time complexity? How and why?
*/
#include <vector>

using std::vector;


class SearchInRotatedSortedArrayII {

public:
    
    bool doit_search(vector<int>& nums, int target) {

        int low = 0, high = nums.size()-1;

        while (low < high) {

            int mid = (low + high) / 2;

            if (nums[mid] == target) return mid;

            if (nums[mid] > target && target >= nums[low])
                

        }
    }
};