/*
1589. Maximum Sum Obtained of Any Permutation

We have an array of integers, nums, and an array of requests where requests[i] = [starti, endi]. 
The ith request asks for the sum of nums[starti] + nums[starti + 1] + ... + nums[endi - 1] + nums[endi]. Both starti and endi are 0-indexed.

Return the maximum total sum of all requests among all permutations of nums.

Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [1,2,3,4,5], requests = [[1,3],[0,1]]
Output: 19
Explanation: One permutation of nums is [2,1,3,4,5] with the following result: 
requests[0] -> nums[1] + nums[2] + nums[3] = 1 + 3 + 4 = 8
requests[1] -> nums[0] + nums[1] = 2 + 1 = 3
Total sum: 8 + 3 = 11.
A permutation with a higher total sum is [3,5,4,2,1] with the following result:
requests[0] -> nums[1] + nums[2] + nums[3] = 5 + 4 + 2 = 11
requests[1] -> nums[0] + nums[1] = 3 + 5  = 8
Total sum: 11 + 8 = 19, which is the best that you can do.
Example 2:

Input: nums = [1,2,3,4,5,6], requests = [[0,1]]
Output: 11
Explanation: A permutation with the max total sum is [6,5,4,3,2,1] with request sums [11].
Example 3:

Input: nums = [1,2,3,4,5,10], requests = [[0,2],[1,3],[1,1]]
Output: 47
Explanation: A permutation with the max total sum is [4,10,5,3,2,1] with request sums [19,18,10].
 

Constraints:

n == nums.length
1 <= n <= 105
0 <= nums[i] <= 105
1 <= requests.length <= 105
requests[i].length == 2
0 <= starti <= endi < n

*/


#include <vector>
#include <map>

using std::map;
using std::vector;


class SumRangeQuery {

    /*
        1589.Maximum-Sum-Obtained-of-Any-Permutation
        理解题意之后不难分析出，为了使查询总和最大，我们对于查询频次越高的元素，希望它的值越大越好。所以显然只要将查询频率从高到低排序，同时将数组元素也从高到低排序，然后相乘相加必然就是我们期待的答案。

        那我们我们如何统计每个元素被查询的频次呢？这里需要注意一个问题。比若说查询一次区间是[1,10000]，说明这10000个元素都要被查询一次。然后再来一次[1,10000]，那么这10000个元素的查询频次是否还要再挨个增加一次呢？可以知道这样的效率是很低的。

        “差分数组”是解决这类问题的常见方法。上述区间需要自增查询频次的元素虽然很多，但是它们的变化率或者导数却是很稀疏的。对于每一个区间[start,end]，我们只要记录在start时的查询频次比start-1多一次、在end+1时的查询频次比end少一次即可。区间中部的这些元素，相邻元素之间的查询频次其实都是一样的。于是，我们只要两次改动，就可以描述这次区间查询的频次的变化。

        具体地，我们开辟数组diff，其中diff[i]表示第i个元素的查询频次要比第i-1个元素的查询频次多多少。于是对于每一个区间[start,end]，我们做diff[start]+=1，diff[end+1]-=1. 最终我们从前缀0开始，一路不停地累加diff[i]，就能得到freq[i]的值（即第i各元素的查询频次）。

        举个例子。有两个查询区间[1,3]和[2,4]，

        0  1  2  3  4  5
        +1       -1
            +1        -1
        -----------------
        0  1  2  2  1   0
        显然最终得到的就是我们期望的每个元素的频率。
    */
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) 
    {
        int n = nums.size();
        vector<int>diff(n+1);
        for (auto request: requests)
        {
            diff[request[0]]+=1;
            diff[request[1]+1]-=1;
        }
        int sum = 0;
        vector<int>count(n,0);
        for (int i=0; i<n; i++)
        {
            sum += diff[i];
            count[i] = sum;
        }
        std::sort(count.begin(), count.end());
        std::sort(nums.begin(), nums.end());
        
        long ret = 0;
        long M = 1e9+7;
        for (int i=0; i<n; i++)
            ret = (ret + (long)nums[i]*long(count[i]))%M;
        return ret;        
    }

public:

    int doit_sweeplines(vector<int>& nums, vector<vector<int>>& requests) {
        int n = nums.size();
        vector<int> cnt(n, 0);
        
        for (const auto& c: requests) {
            cnt[c[0]]++;
            
            if (c[1]+1 < n)
                cnt[c[1]+1]--;
        }
        
        int count = 0;
        map<long, int> cnts;
        for (int i = 0; i < n; i++) {
            count += cnt[i];
            if (count != 0)
                cnts[count]++;
        }
        
        std::sort(begin(nums), end(nums), [](auto& a, auto& b) { return a > b;});
        
        int i = 0;
        long long total = 0;
        int hmod = 1e9+7;
        for (auto it = rbegin(cnts); i < n && it != rend(cnts); it++) {
            
            int c = it->second;
            while (c-- && i < n) {
                total += (it->first * nums[i]) % hmod; 
                total %= hmod;
                i++;
            }
        }
        
        return total % hmod;
    }


    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        constexpr int kMod = 1e9 + 7;
        const int n = nums.size();    
        vector<long> freq(n);
        for (const auto& r : requests) {
        ++freq[r[0]];
        if (r[1] + 1 < n)
            --freq[r[1] + 1];
        }
        for (int i = 1; i < n; ++i)
        freq[i] += freq[i - 1];
        
        std::sort(begin(freq), end(freq));
        std::sort(begin(nums), end(nums));
        
        long ans = 0;
        for (int i = 0; i < n; ++i)
        ans += freq[i] * nums[i];
        
        return ans % kMod;
    }
};