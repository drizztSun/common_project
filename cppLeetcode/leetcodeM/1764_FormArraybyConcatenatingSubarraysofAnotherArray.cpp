/*
1764. Form Array by Concatenating Subarrays of Another Array


You are given a 2D integer array groups of length n. You are also given an integer array nums.

You are asked if you can choose n disjoint subarrays from the array nums such that the ith subarray is equal to groups[i] (0-indexed), and if i > 0, 
the (i-1)th subarray appears before the ith subarray in nums (i.e. the subarrays must be in the same order as groups).

Return true if you can do this task, and false otherwise.

Note that the subarrays are disjoint if and only if there is no index k such that nums[k] belongs to more than one subarray. A subarray is a contiguous sequence of elements within an array.

 

Example 1:

Input: groups = [[1,-1,-1],[3,-2,0]], nums = [1,-1,0,1,-1,-1,3,-2,0]
Output: true
Explanation: You can choose the 0th subarray as [1,-1,0,1,-1,-1,3,-2,0] and the 1st one as [1,-1,0,1,-1,-1,3,-2,0].
These subarrays are disjoint as they share no common nums[k] element.
Example 2:

Input: groups = [[10,-2],[1,2,3,4]], nums = [1,2,3,4,10,-2]
Output: false
Explanation: Note that choosing the subarrays [1,2,3,4,10,-2] and [1,2,3,4,10,-2] is incorrect because they are not in the same order as in groups.
[10,-2] must come before [1,2,3,4].
Example 3:

Input: groups = [[1,2,3],[3,4]], nums = [7,7,1,2,3,4,7,7]
Output: false
Explanation: Note that choosing the subarrays [7,7,1,2,3,4,7,7] and [7,7,1,2,3,4,7,7] is invalid because they are not disjoint.
They share a common elements nums[4] (0-indexed).
 

Constraints:

groups.length == n
1 <= n <= 103
1 <= groups[i].length, sum(groups[i].length) <= 10^3
1 <= nums.length <= 10^3
-10^7 <= groups[i][j], nums[k] <= 10^7

*/
#include <vector>

using std::vector;

class CanChoose {

public:

    bool doit_search(vector<vector<int>>& groups, vector<int>& nums) {
        
        int startindex = 0;
        
        for (auto& group: groups) {
            bool matched = false;
            
            while (startindex < nums.size() && !matched) {
                
                bool done = false;
                for (int i = 0; i < group.size(); i++) {
                    if (group[i] != nums[startindex + i]) {
                        done = true;
                        break;
                    }
                }
                if (!done) matched = true;
                
                if (!matched) startindex++;
            }
            
            if (!matched) return false;
            
            startindex += group.size();
        }
            
        return true;
    }

    /*
        1764.Form-Array-by-Concatenating-Subarrays-of-Another-Array
        解法1：暴力
        在长度为m的目标串里寻找长度为n的模式串，暴力法需要o(mn)的时间复杂度。如果要寻找k个模式串，总共需要o(mnk)的时间。本题中m<10^3，且有nk<10^3，所以暴力法是可以接受的。

        解法2：KMP
        我们可以用KMP的方法，将单词寻找模式串的长度减少为o(m+n)，从而降低复杂度。

        与KMP的模板题类似，我们要对每一个模式串p预处理得到它的“自相关最长前后缀数组”lsp。略微不同的是，我们在每次进行s和p的匹配时，需要在目标串s中指定一个起始位置cur。
        这样每一个回合，s和p的互相关最长前后缀数组的计算只需要从cur开始。如果能够找到匹配的起始位置i，那么下一个回合的起始位置就从cur = i+p.size()开始寻找。    
    */

    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) 
    {
        int cur = 0;

        std::function<int(int, vector<int>&)> find = [&](int cur, vector<int>&g)
        {
            for (int i=cur; i<nums.size(); i++)
            {
                int flag = 1;
                for (int j=0; j<g.size(); j++)
                    if (cur+j>=nums.size() || nums[i+j]!=g[j])
                    {
                        flag = 0;
                        break;
                    }
                if (flag) return i;
            }
            return -1;
        };

        for (int i=0; i<groups.size(); i++) {

            if (cur >= nums.size()) 
                return false;
            
            cur = find(cur, groups[i]);
            
            if (cur==-1) return false;
            
            cur += groups[i].size();
        }
        return true;
    }


    bool doit_kmp(vector<vector<int>>& groups, vector<int>& nums)
    {
        int dp[1000];

        auto preprocess = [](vector<vector<int>>& groups) -> vector<vector<int>> {

            vector<vector<int>> rets;
            for (auto &g: groups)
            {
                int n = g.size();
                vector<int>dp(n);
                dp[0] = 0;
                for (int i=1; i<n; i++)
                {
                    int j = dp[i-1];
                    while (j>0 && g[j]!=g[i])
                        j = dp[j-1];
                    dp[i] = j + (g[j]==g[i]);
                }
                rets.push_back(dp);
            }
            return rets;
        };


        auto find = [&](vector<int>&nums, int cur, vector<int>&p, vector<int>&lsp) -> int {

            int n = nums.size();
            dp[cur] = (p[0]==nums[cur]);

            if (lsp.size()==1 && dp[cur]==1)
                return cur;

            for (int i=cur+1; i<n; i++)
            {
                int j = dp[i-1];
                while (j>0 && p[j]!=nums[i])
                    j = lsp[j-1];
                dp[i] = j + (p[j]==nums[i]);
                if (dp[i] == p.size())
                    return i-p.size()+1;
            }
            return -1;
        };


        vector<vector<int>>lsps = preprocess(groups);
        int cur = 0;
        for (int i = 0; i < groups.size(); i++)
        {
            if (cur >= nums.size()) return false;
            cur = find(nums, cur, groups[i], lsps[i]);
            if (cur == -1) return false;
            cur += groups[i].size();
        }
        return true;
    }
};