/*
26. Remove Duplicates from Sorted Array

Given a sorted array nums, remove the duplicates in-place such that each element appears only once and returns the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

Clarification:

Confused why the returned value is an integer but your answer is an array?

Note that the input array is passed in by reference, which means a modification to the input array will be known to the caller as well.

Internally you can think of this:

// nums is passed in by reference. (i.e., without making a copy)
int len = removeDuplicates(nums);

// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
 

Example 1:

Input: nums = [1,1,2]
Output: 2, nums = [1,2]
Explanation: Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the returned length.
Example 2:

Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4]
Explanation: Your function should return length = 5, with the first five elements of nums being modified to 0, 1, 2, 3, and 4 respectively. It doesn't matter what values are set beyond the returned length.
 

Constraints:

0 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
nums is sorted in ascending order.


*/

#include <vector>

using std::vector;




class RemoveDuplicates {

    /*
        26. Remove Duplicates from Sorted Array
        注意去除重复元素后仍然要求保持原始顺序，必须in-place实现，故考虑快慢双指针。

        遍历快指针，将快指针所指向的所有有效元素都移动到左指针的位置上。

        对于快指针经过的所有重复元素则continue。重复元素的判定方法是比较nums[right]==nums[left]（或者nums[right]==nums[right-1]，取决于left和right的初始状态）。

        最后输出左指针的位置，因为如前所述，所有的有效元素都已经在左指针上了。
    */
    int removeDuplicates(vector<int>& nums) 
    {
        int i=0;
        int j=1;
        
        while (j<nums.size())
        {
            if (nums[j]==nums[j-1])
            {
                j++;
            }
            else
            {
                i++;
                swap(nums[i],nums[j]);
                j++;
            }
        }
        return i+1;
    }

    int removeDuplicates(vector<int>& nums) 
    {
        if (nums.size()==0) return 0;
        
        int i=0;
        for (int j=0; j<nums.size(); j++)
        {
            if (j==0)
                continue;
            else if (nums[j]==nums[i])
                continue;
            else
            {
                i++;
                nums[i]=nums[j];
            }
        }
        
        return i+1;
        
    }
    
public:

    int doit_twopointer(vector<int>& nums) {
        
        int j = 0;
        for (int i = 0; i < nums.size(); i++) {
            
            if (i == 0 || nums[i] != nums[j-1]) {
                nums[j++] = nums[i]; 
            }
        }
        
        return j;
    }

    /*
        Approach 1: Two Pointers
        Algorithm

        Since the array is already sorted, we can keep two pointers ii and jj, where ii is the slow-runner while j is the fast-runner. As long as nums[i]=nums[j], we increment j to skip the duplicate.
        When we encounter nums[j]=nums[i], the duplicate run has ended so we must copy its value to nums[i + 1]. i is then incremented and we repeat the same process again until j reaches the end of array.

        Complexity analysis

        Time complextiy : O(n). Assume that nn is the length of array. Each of i and j traverses at most nn steps.

        Space complexity : O(1).
    */
    int doit_(vector<int>& nums) {
        
        if (nums.empty()) return 0;

        int j = 0;
        for (int i = 1; i < nums.size(); i++) {
            
            if (nums[i] != nums[j]) {
                nums[++j] = nums[i]; 
            }
        }
        
        return j+1;
    }
};