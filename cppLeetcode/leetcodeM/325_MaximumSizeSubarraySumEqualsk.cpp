/*
325. Maximum Size Subarray Sum Equals k

Given an integer array nums and an integer k, return the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.

 

Example 1:

Input: nums = [1,-1,5,-2,3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
Example 2:

Input: nums = [-2,-1,2,1], k = 1
Output: 2
Explanation: The subarray [-1, 2] sums to 1 and is the longest.
 

Constraints:

1 <= nums.length <= 10^4
-10^4 <= nums[i] <= 10^4
-10^5 <= k <= 10^5
 

Follow Up: Can you do it in O(n) time?

*/

#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class MaxSubArrayLen {

    /*
        325.Maximum-Size-Subarray-Sum-Equals-k
        在遍历元素的过程中，建立累加和sum，并建立映射Map:sum->i。对于每个元素i，找和为k的子数组，就是寻找之前的累加和序列里是否出现过 sum-k，显然，直接从Map中就可以找到。

                for (int i=0; i<nums.size(); i++)
                {
                    sum+=nums[i];
                    Map[sum].push_back(i);
                    
                    int temp = sum-k;
                    if (Map.find(temp)!=Map.end())
                    {
                        result = max(result, i-Map[temp][0]);
                    }
                }
    */
    int maxSubArrayLen(vector<int>& nums, int k) 
    {
        unordered_map<int,vector<int>>Map;
        int sum=0;
        int result=INT_MIN;
        
        nums.insert(nums.begin(),0);
        
        for (int i=0; i<nums.size(); i++)
        {
            sum+=nums[i];
            Map[sum].push_back(i);
            
            int temp = sum-k;
            if (Map.find(temp)!=Map.end())
            {
                result = std::max(result, i-Map[temp][0]);
            }
        }
        
        if (result==INT_MIN) result=0;
        
        return result;
        
    }


public:

    int doit_hash(vector<int>& nums, int k) {
        
        unordered_map<int, int> pos;
        pos.insert({0, -1});
        int total = 0, res = 0;

        for (int i = 0; i < nums.size(); i++) {

            total += nums[i];

            if (pos.count(total - k)) {
                res = std::max(res, i - pos[total-k]);
            } 

            if (pos.count(total) == 0) 
                pos.insert({total, i});
        }

        return res;
    }
};