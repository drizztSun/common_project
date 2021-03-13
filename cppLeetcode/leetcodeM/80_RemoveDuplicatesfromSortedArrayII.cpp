/*
80. Remove Duplicates from Sorted Array II

Given a sorted array nums, remove the duplicates in-place such that duplicates appeared at most twice and return the new length.

Do not allocate extra space for another array; you must do this by modifying the input array in-place with O(1) extra memory.

Clarification:

Confused why the returned value is an integer, but your answer is an array?

Note that the input array is passed in by reference, which means a modification to the input array will be known to the caller.

Internally you can think of this:

// nums is passed in by reference. (i.e., without making a copy)
int len = removeDuplicates(nums);

// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
 

Example 1:

Input: nums = [1,1,1,2,2,3]
Output: 5, nums = [1,1,2,2,3]
Explanation: Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively. It doesn't matter what you leave beyond the returned length.
Example 2:

Input: nums = [0,0,1,1,1,1,2,3,3]
Output: 7, nums = [0,0,1,1,2,3,3]
Explanation: Your function should return length = 7, with the first seven elements of nums being modified to 0, 0, 1, 1, 2, 3 and 3 respectively. It doesn't matter what values are set beyond the returned length.
 

Constraints:

1 <= nums.length <= 3 * 10^4
-10^4 <= nums[i] <= 10^4
nums is sorted in ascending order.

*/
#include <vector>

using std::vector;

class RemoveDuplicates {

    /*
        080.Remove-Duplicates-from-Sorted-Array-II
        要实现in-place的功能，利用快慢指针。right指针判定合格的，就拷贝到left指针上去。

        注意：初始值left=1，right=2。保证有不超过两个重复的判断条件是

        if (nums[right]==nums[left] && nums[right]==nums[left-1])
        right++;
        else
        {
        left++;
        nums[left]=nums[right];
        right++;
        }
        分析：因为所有合格的元素都已经移到了左指针上，所以每次考察右指针的新元素时，需要和左指针进行比较。
    */
    int removeDuplicates(vector<int>& nums) 
    {
        if (nums.size()==0) return 0;
        if (nums.size()==1) return 1;
        
        int i=1;
        for (int j=0; j<nums.size(); j++)
        {
            if (j==0 || j==1) 
                continue;
            else if (nums[j]==nums[i] && nums[j]==nums[i-1])
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
            
            if (i < 2 || nums[j-2] != nums[i]) {
                nums[j++] = nums[i];
            }
        }
        
        return j;
    }
};