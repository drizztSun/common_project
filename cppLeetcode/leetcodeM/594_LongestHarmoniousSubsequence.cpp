/*
594. Longest Harmonious Subsequence


We define a harmonious array as an array where the difference between its maximum value and its minimum value is exactly 1.

Given an integer array nums, return the length of its longest harmonious subsequence among all its possible subsequences.

A subsequence of array is a sequence that can be derived from the array by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: nums = [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
Example 2:

Input: nums = [1,2,3,4]
Output: 2
Example 3:

Input: nums = [1,1,1,1]
Output: 0
 

Constraints:

1 <= nums.length <= 2 * 10^4
-10^9 <= nums[i] <= 10^9

*/

#include <unordered_map>
#include <vector>
#include <map>

using std::map;
using std::unordered_map;
using std::vector;

class LongestHarmoniousSubsequence {

    /*
        594.Longest-Harmonious-Subsequence
        首先要正确理解题意。subsequence不一定要求连续，只要是原数列的任意部分都符合要求。

        这样的话，我们可以遍历一遍整个数列，构造频次的Hash表，而且这个表是根据key有序排列的。那么我们可以依次考察任意相邻的两个频次，如果key值只相差1的话，那么这两个key对应的频次之和就是符合题意的一个方案。不断遍历这个Hash表、更新直到得到最大值。
    */
    int findLHS(vector<int>& nums) 
    {
        map<int,int>Map;
        for (int i=0; i<nums.size(); i++)
            Map[nums[i]]++;
        
        int lastFreq=0;
        int lastNum;
        int result=0;
        for (auto a:Map)
        {
            if (lastFreq==0)
            {
                lastNum=a.first;
                lastFreq=a.second;
            }
            else
            {
                if (lastNum+1==a.first)
                    result = std::max(result,lastFreq+a.second);
                lastNum = a.first;
                lastFreq = a.second;
            }
        }
        
        return result;
    }

public:

    /*
        Exactly 1, means for [1,3,2,2,5,2,3,7], it only picks the [3, 2, 2, 2, 3]. it always pick atmost k and k-1.
    */
    int doit_(vector<int>& nums) {

        unordered_map<int, int> buf;
        for (auto c : nums) {
            buf[c]++;
        }
        
        int ans = 0;
        
        for (auto it: buf) {
            
            if (buf.count(it.first-1)) {
                ans = std::max(ans, buf[it.first] + buf[it.first-1]);
            }
        }
        
        return ans;
    }
};