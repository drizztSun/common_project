/*
 1262. Greatest Sum Divisible by Three
 
 
 Given an array nums of integers, we need to find the maximum possible sum of elements of the array such that it is divisible by three.

  

 Example 1:

 Input: nums = [3,6,5,1,8]
 Output: 18
 Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
 Example 2:

 Input: nums = [4]
 Output: 0
 Explanation: Since 4 is not divisible by 3, do not pick any number.
 Example 3:

 Input: nums = [1,2,3,4,4]
 Output: 12
 Explanation: Pick numbers 1, 3, 4 and 4 their sum is 12 (maximum sum divisible by 3).
  

 Constraints:

 1 <= nums.length <= 4 * 10^4
 1 <= nums[i] <= 10^4
 
 
 */
#include <vector>

using std::vector;


class GreatestSumDivisibleByThree {
    
public:
    
    int doit_dp(vector<int>& nums) {
        
        int dp[3] = {0, INT_MIN, INT_MIN};
        
        for (auto c : nums) {
            
            int ndp[3] = {dp[0], dp[1], dp[2]};
            
            for (auto i = 0; i < 3; i++) {
                
                dp[i] = std::max(dp[i], c + ndp[(i-c%3+3)%3]);
            }
            
        }
        
        return dp[0];
    }
    
    int doit_dp_1(vector<int>& nums) {
        int temp[3];
        int result[3];
        temp[0] = 0;
        result[0] = 0;
        temp[1] = -1;
        temp[2] = -1;
        result[1] = -1;
        result[2] = -1;
        
        for(int i = 0; i != nums.size(); ++i)
        {
            int resi = nums[i];
            for(int j = 0; j < 3; ++j)
            {
                if(result[j] != -1)
                {
                    temp[(j + resi) % 3] = result[j] + nums[i];
                }
            }
            
            for(int j = 0; j < 3; ++j)
            {
                result[j] = std::max(result[j], temp[j]);
            }
        }
        return result[0];
    }
};
