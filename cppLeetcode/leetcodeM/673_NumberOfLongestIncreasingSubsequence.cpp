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
#include <algorithm>

using std::vector;
using std::unordered_map;


class FindNumberOfLIS {
    
public:
    
    // O(n*log(n))
    int doit_dp_binary_search(vector<int>& nums) {

        int minv = *min_element(nums.begin(), nums.end()) - 1;
        vector<unordered_map<int, int>> dp;
        vector<int> base;
        base.push_back(minv);
        dp.push_back(unordered_map<int, int>{{minv, 1}});
        /*
            # DP is array, index is the length of LIS, value is {key: value }, key is number end with, value is the cnt of LIS. 
            # DP is {different length: {end with this number: how many sequence}}
            # base is the sorted sequence of number has been handler.
        */
        
        for (auto c : nums) {
            /*
                # i is the new positon of x, means it can build sequence of length i. 
                # if it is end of the sorted sequence that meeans it is end and new max length
            */
            auto i = std::lower_bound(base.begin(), base.end(), c) - begin(base) - 1;
            auto t = 0;
            
            // if i == len(a)-1, it means it will build a longer length then any existed, so put it into the tails.
            if (i == base.size()-1) {
                dp.push_back(unordered_map<int,int>{});
                base.push_back(c);
            }

            /*
                # [1, 2, 6, 3, 4, 7]
                # the sequence would be [1,2,6 ..], then [1, 2, 3 ...] then [1, 2, 3, 4]
                # when we don't know 4, [1, 2, 6 ..] and [1, 2, 3 ..] all candidates, and being in index 3 of
                # when we meet 4, it will be [1, 2, 3, 4], the number from [1, 2, 36 ..] became invalid and need to remove.
            */
            
            for (auto iter = dp[i].begin(); iter != dp[i].end();) {
                // # list all {key, value} with x, 
                if (iter->first < c) {
                    t += iter->second;
                    iter++;
                } else{
                    // # remove useless one, if it is greater than x. because of no sequence needs it. if it is greater y, 
                    // # it will use x to build longer sequence
                    iter = dp[i].erase(iter);
                }
            }
            
            base[i+1] = std::min(base[i+1], c); // # update the value of i+1, so it can use new value to build sequence.
            dp[i+1][c] += t;
        
        }
        
        int res = 0;
        for (auto [k,v] : dp[dp.size()-1])
            res += v;
        return res;
    }


    // O(n^2)
    int doit_dp(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> c(n, 1);
        vector<int> l(n, 1);
        
        for (int i = 1; i < n; ++i)
            for(int j = 0; j < i; ++j)
                if (nums[i] > nums[j]) {
                    if (l[j] + 1 > l[i]) {
                        l[i] = l[j] + 1;
                        c[i] = c[j];
                    } else if (l[j] + 1 == l[i]) {
                        c[i] += c[j];
                    }
                }
        
        int max_len = *max_element(l.begin(), l.end());
        
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (l[i] == max_len)
                ans += c[i];
        
        return ans;
    }

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
};



