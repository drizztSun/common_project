/*
665. Non-decreasing Array


Given an array nums with n integers, your task is to check if it could become non-decreasing by modifying at most one element.

We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for every i (0-based) such that (0 <= i <= n - 2).

 

Example 1:

Input: nums = [4,2,3]
Output: true
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:

Input: nums = [4,2,1]
Output: false
Explanation: You can't get a non-decreasing array by modify at most one element.
 

Constraints:

n == nums.length
1 <= n <= 10^4
-10^5 <= nums[i] <= 10^5


*/


#include <vector>

using std::vector;



class Possibility {

    /*
        665.Non-decreasing-Array
        此题属于贪心法。考虑为了满足数列递增关系，遇到“坏点”的时候，最优的改动策略是什么。

        遍历数列一路查验是否递增，如果发现nums[i-1]>nums[i]，首先考虑的改动方案是将nums[i-1]=nums[i]，这样就避免改动nums[i]引发后续的变动。
        但是，如果又有nums[i-2]>nums[i]的话，那没有办法，为了避免改动两次，只能令nums[i]=nums[i-1]。此时计数1次。如果下次再出现了nums[i-1]>nums[i]的话，就返回false。
    */
    bool checkPossibility(vector<int>& nums) 
    {
        int count=0;
        for (int i=1; i<nums.size(); i++)
        {            
            if (nums[i-1]>nums[i])
            {
                count++;
                
                if (count==2) return false;
                
                if (i>=2 && nums[i-2]>nums[i])
                    nums[i]=nums[i-1];
                else
                    nums[i-1]=nums[i];
            }
        }
        return true;
    }

public:

    bool doit_greedy(vector<int>& nums) {
        
        int cnt = 0;
        
        for (int i = 0; i < nums.size()-1; i++) {
            
            if (nums[i] <= nums[i+1]) continue;
            
            cnt++;
            
            if (cnt == 2) return false;
            
            if (i == 0 || nums[i-1] <= nums[i+1]) {
                nums[i] = nums[i+1];
            } else {
                nums[i+1] = nums[i];
            }
        }
        
        return true;
    }

};