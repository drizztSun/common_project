/*
280. Wiggle Sort

Given an integer array nums, reorder it such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

You may assume the input array always has a valid answer.

 

Example 1:

Input: nums = [3,5,2,1,6,4]
Output: [3,5,1,6,2,4]
Explanation: [1,6,2,5,3,4] is also accepted.
Example 2:

Input: nums = [6,6,5,6,3,8]
Output: [6,6,5,6,3,8]
 

Constraints:

1 <= nums.length <= 5 * 104
0 <= nums[i] <= 104
It is guaranteed that there will be an answer for the given input nums.
 

Follow up: Could you do it without sorting the array?

*/

#include <vector>
#include <algorithm>

using std::vector;


class wiggleSort {

public:
    
    /*
        Approach #1 (Sorting) [Accepted]
        The obvious solution is to just sort the array first, then swap elements pair-wise starting from the second element. For example:

        [1, 2, 3, 4, 5, 6]
            ↑  ↑  ↑  ↑
            swap  swap

        => [1, 3, 2, 5, 4, 6]

        Complexity analysis

        Time complexity : O(nlogn). The entire algorithm is dominated by the sorting step, which costs O(n \log n)O(nlogn) time to sort nn elements.

        Space complexity : O(1). Space depends on the sorting implementation which, usually, costs O(1)O(1) auxiliary space if heapsort is used.
    */
    void doit_sort(vector<int>& nums) {

        std::sort(begin(nums), end(nums));
        
        for (int i = 1; i < nums.size(); i+=2) {
            if (i+1 < nums.size())
                std::swap(nums[i], nums[i+1]);
        }    
    }

    /*
        Approach #2 (One-pass Swap) [Accepted]
        Intuitively, we should be able to reorder it in one-pass. As we iterate through the array, we compare the current element to its next element and if the order is incorrect, we swap them
        
        Complexity analysis

        Time complexity : O(n). In the worst case we swap at most n/2 times. An example input is [2,1,3,1,4,1].
        Space complexity : O(1).
    */
    void doit(vector<int>& nums) {

        bool less = true;
        for (int i = 1; i < nums.size(); i++) {

            if (less) {
                if (nums[i-1] > nums[i]) std::swap(nums[i-1], nums[i]);
            } else {
                if (nums[i-1] < nums[i]) std::swap(nums[i-1], nums[i]);
            }

            less = !less;
        }
    }
};