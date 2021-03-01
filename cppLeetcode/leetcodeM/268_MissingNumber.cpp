/*
268. Missing Number

Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?

 

Example 1:

Input: nums = [3,0,1]
Output: 2
Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.
Example 2:

Input: nums = [0,1]
Output: 2
Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number in the range since it does not appear in nums.
Example 3:

Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number in the range since it does not appear in nums.
Example 4:

Input: nums = [0]
Output: 1
Explanation: n = 1 since there is 1 number, so all numbers are in the range [0,1]. 1 is the missing number in the range since it does not appear in nums.
 

Constraints:

n == nums.length
1 <= n <= 104
0 <= nums[i] <= n
All the numbers of nums are unique.


*/
#include <vector>

using std::vector;


class Solution {

    /*
        268.Missing-Number
        解法1：
        对于凡是与“从0到N”数字相关的题目，indexing sort（或者叫cyclic sort？）总是一个值得尝试的角度。我们试图将0~N这些数字依次填充到nums的第0~N个位置。移动的方法就是逐个考察每个index，如果第i个位置的数字不是nums[i]，那么我们就交换nums[i]和nums[nums[i]]：目的是把nums[i]直接送到它应该所在的地方（也就是index是nums[i]的位置）；同时，如果交换来的nums[nums[i]]依然不是我们想要的数字i，那么我们就重复这个swap的操作，直至：

        当前的第i个位置放的就是数字i；or
        nums[i]和nums[nums[i]]相等，也就是说swap(nums[i], nums[nums[i]])没有任何效果；or
        nums[nums[i]]越界了，也就是nums[i]不是一个合法的index
        按照以上规则处理完所有的index之后，我们就已经竭尽全力地把所有数字和索引相match。此时再扫一遍nums数组，唯一的一处nums[i]!=i的地方，就是说明数字i是missing的。

        解法2：
        有一个更优雅的做法。nums[i]包含了0~N的所有数（除了一个missing number，假设是x）。我们将其亦或起来。同时将这个结果再与0~N都亦或一遍。这样，除了x，其他的数字都被xor了两遍而被消除。剩下的结果就是x。
    
    */
    int doit_(vector<int>& nums) 
    {
        int n = nums.size();
        nums.push_back(n+1);
        for (int i=0; i<=n; i++)
        {
            while (nums[i]!=i && nums[i]<=n && nums[i]!=nums[nums[i]])
                std::swap(nums[i], nums[nums[i]]);
        }
        for (int i=0; i<=n; i++)
            if (nums[i]!=i)
                return i;
        return 0;
    }

    int doit_bit(vector<int>& nums) 
    {
        int k=0;
        for (int i=0; i<=nums.size(); i++)
            k = k^i;

        for (int i=0; i<nums.size(); i++)
            k = k^nums[i];
        
        return k;
    }
};