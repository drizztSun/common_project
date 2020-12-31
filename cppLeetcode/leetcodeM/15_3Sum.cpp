/*
15. 3Sum

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Example 2:

Input: nums = []
Output: []
Example 3:

Input: nums = [0]
Output: []
 

Constraints:

0 <= nums.length <= 3000
-105 <= nums[i] <= 10^5

*/
#include <vector>

using std::vector;


class ThreeSum {

public:
    
    vector<vector<int>> doit_twopointer(vector<int>& nums) {
    
        std::sort(begin(nums), end(nums));
        vector<vector<int>> res;
        
        auto search = [&](int start) {
            
            int i = start + 1, j = nums.size()-1;
            while (i < j) {
                int total = nums[i] + nums[j] + nums[start];
                if (total < 0) {
                    i++;
                } else if (total > 0) {
                    j--;
                } else {
                    res.push_back(vector<int>{nums[start], nums[i], nums[j]});
                    i++;
                    j--;
                    while (i < j && nums[i-1] == nums[i])
                        i++;
                }
            }
        };
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0)
                break;
            if (i == 0 || nums[i-1] != nums[i])
                search(i);
        }
        return res;
    }
};