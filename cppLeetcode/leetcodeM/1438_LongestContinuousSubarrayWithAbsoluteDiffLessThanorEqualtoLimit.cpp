/*
1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit


Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.

 

Example 1:

Input: nums = [8,2,4,7], limit = 4
Output: 2 
Explanation: All subarrays are: 
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4. 
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4. 
Therefore, the size of the longest subarray is 2.
Example 2:

Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4 
Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.
Example 3:

Input: nums = [4,2,2,2,4,4,2,2], limit = 0
Output: 3
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
0 <= limit <= 10^9

*/
#include <vector>
#include <deque>
#include <set>

using std::multiset;
using std::deque;
using std::vector;

//TC: O(n)
//SC: O(n)
class LongestContinuousSubarray {

public:


    /*
        monotonic queue, increasing and decreaing for min value and max value
    */
    int doit_(vector<int>& nums, int limit) {
        
        int l = 0;
        int r = 0;
        int res = 0;
        
        deque<int> tmin{INT_MAX};
        deque<int> tmax{INT_MIN};
        
        while(r < nums.size()){
            
            while(!tmin.empty() && tmin.back() > nums[r]) tmin.pop_back();
            while(!tmax.empty() && tmax.back() < nums[r]) tmax.pop_back();

            tmin.push_back(nums[r]);
            tmax.push_back(nums[r]);
            
            if(abs(tmax.front() - tmin.front()) <= limit)
                res = std::max(res, r - l + 1);
            
            while(l < r && abs(tmax.front() - tmin.front()) > limit){
                if(nums[l] == tmin.front()) tmin.pop_front();
                if(nums[l] == tmax.front()) tmax.pop_front();
                l++;
            }

            r++;
        }
        
        return res;
    }


    int doit_(vector<int>& nums, int limit) {
        int maxLen = 1;
        multiset<int> curEl{nums[0]};
        for (int r = 1, l = 0; r < nums.size(); r++) {
            curEl.insert(nums[r]);
            while (*curEl.rbegin() - *curEl.begin() > limit) {
                curEl.erase(curEl.find(nums[l]));
                l++;
            }
            maxLen = std::max(maxLen, static_cast<int>(curEl.size()));
        }
        return maxLen;
    }
};