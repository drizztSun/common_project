/*
 673. Number of Longest Increasing Subsequence
 
 
 Given an integer array nums, return the number of longest increasing subsequences.

 Notice that the sequence has to be strictly increasing.

  

 Example 1:

 Input: nums = [1,3,5,4,7]
 Output: 2
 Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
 Example 2:

 Input: nums = [2,2,2,2,2]
 Output: 5
 Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.

  

 Constraints:

 1 <= nums.length <= 2000
 -106 <= nums[i] <= 106

 */
#include <vector>
#include <unordered_map>
#include <map>
#include <numeric>
#include <algorithm>

using std::map;
using std::vector;
using std::unordered_map;



class NumberOfLongestIncreasingSubsequence {

    /*
        673.Number-of-Longest-Increasing-Subsequence
        在传统的LIS的DP解法基础上，再设置一个表征LIS数目的数组。len[i]表示以i元素结尾的LIS的长度；num[i]表示以i元素结尾的LIS的数目。

        递推关系是：

        len[i] = max (len[j]+1) for 0<=j<i && nums[j]<nums[i]

        num[i] = sum (num[j]) for 0<=j<i && len[j]+1=len[i]
    */
    int findNumberOfLIS(vector<int>& nums) 
    {
        int N=nums.size();
        vector<int>len(N,1);
        vector<int>num(N,1);
        
        for (int i=1; i<N; i++)
        {
            int maxLen=1;
            int maxNum=1;
            for (int j=0; j<i; j++)
            {
                if (nums[i]<=nums[j])
                    continue;
                    
                if (len[j]+1>maxLen)
                {
                    maxLen=len[j]+1;
                    maxNum=num[j];
                }
                else if (len[j]+1==maxLen)
                {
                    maxNum+=num[j];
                }
            }
            len[i]=maxLen;
            num[i]=maxNum;
        }
        
        int maxLen=1;
        int maxNum=0;
        for (int i=0; i<N; i++)
        {
            if (len[i]>maxLen)
            {
                maxLen=len[i];
                maxNum=num[i];
            }
            else if (len[i]==maxLen)
                maxNum+=num[i];
        }
        
        return maxNum;
    }
    
public:
    
    int doit_dp_1(vector<int>& nums)
    {
        vector<int> lis(nums.size(), 1);
        vector<int> numOf(nums.size(), 1);
        int res = 0, length = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    if (lis[i] < 1 + lis[j])
                        numOf[i] = numOf[j], lis[i] = 1 + lis[j];
                    else if (lis[i] == 1 + lis[j])
                        numOf[i] += numOf[j];
                }
            }
            
            if (lis[i] == length)
                res += numOf[i];
            else if (lis[i] > length)
                res = numOf[i], length = lis[i];
        }
        
        return res;
    }
    
    int doit_dp_best_LIS(vector<int>&& nums) {
        
        int minv = *min_element(nums.begin(), nums.end()) - 1;
        vector<map<int, int>> dp;
        vector<int> base;
        base.push_back(minv);
        dp.push_back(map<int, int>{{minv, 1}});
        
        for (auto c : nums) {
            
            auto i = std::lower_bound(base.begin(), base.end(), c) - begin(base) - 1;
            auto t = 0;
            
            if (i == base.size()-1) {
                dp.push_back(map<int,int>{});
                base.push_back(c);
            }
            
            auto iter = dp[i].begin();
            while (iter != dp[i].end()) {
                if (iter->first < c) {
                    t += iter->second;
                    iter++;
                } else{
                    iter = dp[i].erase(iter);
                }
            }
            
            base[i+1] = std::min(base[i+1], c);
            dp[i+1][c] += t;
        
        }
        
        int res = 0;
        for (auto [k,v] : dp[dp.size()-1])
            res += v;
        return res;
    }
    
    int doit_dp_2(vector<int>&& nums) {
        
        int minv = *min_element(nums.begin(), nums.end()) - 1;
        vector<unordered_map<int, int>> dp;
        vector<int> base;
        base.push_back(minv);
        dp.push_back(unordered_map<int, int>{{minv, 1}});
        
        for (auto c : nums) {
            
            auto i = std::lower_bound(base.begin(), base.end(), c) - begin(base) - 1;
            auto t = 0;
            
            if (i == base.size()-1) {
                dp.push_back(unordered_map<int,int>{});
                base.push_back(c);
            }
            
            for (auto iter = dp[i].begin(); iter != dp[i].end();) {
                if (iter->first < c) {
                    t += iter->second;
                    iter++;
                } else{
                    iter = dp[i].erase(iter);
                }
            }
            
            base[i+1] = std::min(base[i+1], c);
            dp[i+1][c] += t;
        }
        
        int res = 0;
        for (auto [k,v] : dp[dp.size()-1])
            res += v;
        return res;
    }
};