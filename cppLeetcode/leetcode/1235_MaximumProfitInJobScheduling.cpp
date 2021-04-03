/*
 
 1235. Maximum Profit in Job Scheduling
 
 We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

 You're given the startTime , endTime and profit arrays, you need to output the maximum profit you can take such that there are no 2 jobs in the subset with overlapping time range.

 If you choose a job that ends at time X you will be able to start another job that starts at time X.

  

 Example 1:



 Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
 Output: 120
 Explanation: The subset chosen is the first and fourth job.
 Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
 Example 2:




 Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
 Output: 150
 Explanation: The subset chosen is the first, fourth and fifth job.
 Profit obtained 150 = 20 + 70 + 60.
 Example 3:



 Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
 Output: 6
  

 Constraints:

 1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
 1 <= startTime[i] < endTime[i] <= 10^9
 1 <= profit[i] <= 10^4
 
 */

#include <stdio.h>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <map>

using std::set;
using std::vector;
using std::unordered_map;
using std::map;


class JobScheduling {
    
public:

    /*
        1235.Maximum-Profit-in-Job-Scheduling
        考虑到我们最终选取的区间必须是non-overlapping的，所以根据经验，我们按照endTime对区间进行排序。

        假设我们按照如上排序后的顺序，遍历每个区间。我们会想，如果我们选择了第i个区间的话，那么我们就有机会更新这么一个记录dp[endTime[i]]，其中dp[t]表示截至t时刻的最大收益。显然，我们会有dp[endTime[i]] = dp[startTime[i]]+profit[i].这像不像DP的思想？

        当然，我们不可能在dp里存放每一个时刻的最大收益，我们只能离散化存放每一个endTime时刻的最大收益。也就是说，dp应该是一个哈希表。因此，可能dp记录里并没有startTime[i]，但我们只需要找到最后一个小于等于startTime[i]的时刻即可，记为t，对应的dp[t]=val。
        特别注意，我们试图记录dp[endTime[i]] = val+profit[i]的时候，前提条件是val + profit[i]一定要比dp里面最后时刻的收益还要大。也就是说，我们在dp里面只存放按收益递增的time->profit键值对。
        事实上，这也合情合理，如果t0<t1，且dp[t0]>dp[t1]的话，t1并没有必要塞入这个dp数组里面（既浪费了时间反而收益下降）。

        于是我们的算法就呼之欲出了。对于当前的区间i，我们在dp数组（或者有序的map）里面考察在startTime[i]时刻之前的最大收益val，我们可以通过二分法得到。接下来，我们就有机会添加dp[endTime[i]] = val+profit[i]。
        注意，如果dp[endTime[i]]的最优解还有另外一个可能，就是不取第i个区间，这样的话dp[endTime[i]]=dp[endTime[i-1]]。

        有了这样一个在时间和收益上都是递增的序列dp，我们就可以不断追加dp[endTime[i]]的记录，来创建更新的时刻的最大收益。
    */
    static bool cmp(vector<int>&a, vector<int>&b)
    {
        return a[1] < b[1];
    }

public:
    int doit_dp(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) 
    {
        int n = startTime.size();
        vector<vector<int>>jobs;
        for (int i=0; i<n; i++)
            jobs.push_back({startTime[i],endTime[i],profit[i]});
        
        sort(jobs.begin(), jobs.end(), cmp);
        map<int,int> dp;
        dp[-1] = 0;

        int ret = 0;
        for (int i=0; i<n; i++)
        {            
            int ans = ret;
            auto iter = dp.upper_bound(jobs[i][0]);
            ans = std::max(ans, std::prev(iter,1)->second + jobs[i][2]);
            
            dp[jobs[i][1]] = ans;
            ret = std::max(ret, ans);
        }

        return ret;
    }

    int doit_dp_1(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) 
    {
        int n = startTime.size();
        vector<vector<int>>jobs;
        for (int i=0; i<n; i++)
            jobs.push_back({startTime[i],endTime[i],profit[i]});

        sort(jobs.begin(), jobs.end(), cmp);
        vector<std::pair<int,int>>dp;
        dp.push_back({-1,0});

        int ret = 0;
        for (int i=0; i<n; i++)
        {            
            int ans = ret;
            auto iter = upper_bound(dp.begin(), dp.end(), std::make_pair(jobs[i][0], INT_MAX));
            ans = std::max(ans, std::prev(iter,1)->second + jobs[i][2]);            
            dp.push_back({jobs[i][1], ans});

            ret = std::max(ret, ans);
        }

        return ret;
    }


    
    struct box{
        int s, e, p;
    };
    
    int doit_dp(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        
        auto n = startTime.size();
        if(n == 0)
           return 0;
       
        vector<box> task(n);
        for(auto i=0; i<n; i++){
            task[i].s = startTime[i];
            task[i].e = endTime[i];
            task[i].p = profit[i];
        }

        auto comp = [](box const& b1, box const &b2){
            if(b1.e == b2.e)
                return b1.p > b2.p;
            return b1.e < b2.e;
        };

        auto binary_search = [&](int l, int r, int target){
            int res = -1;
            int mid;
            while(l<=r){
                mid = (l+r)/2;
                if(task[mid].e <= target){
                    res = mid;
                    l = mid+1;
                }
                else{
                    r = mid-1;
                }
            }
            return res;
        };
       
        std::sort(begin(task), begin(task)+n, comp);
        vector<int> dp(n);
        dp[0] = task[0].p;
       
        for(int i=1; i<n; i++){
           dp[i] = std::max(dp[i-1], task[i].p);
           int j = binary_search(0, i-1, task[i].s);
           if(j != -1)
               dp[i] = std::max(dp[i], dp[j] + task[i].p);
        }
       
        return dp[n-1];
    }
    
    
    int dpot_dp_2(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
     
        auto comp = [](const auto& b1, const auto& b2){
            if(b1[0] == b2[0]) return b1[2] > b2[2];
            return b1[0] < b2[0];
        };
        
        auto binary = [](auto& jobs, int l, int r, int target){
            int res = -1;
            while(l<=r){
                int mid = (l+r)/2;
                if(jobs[mid][0] <= target){
                    res = mid;
                    l = mid+1;
                }
                else{
                    r = mid-1;
                }
            }
            return res;
        };
        
        vector<vector<int>> jobs;
        for (auto i = 0; i < startTime.size(); i++) {
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        }
        
        auto m = startTime.size();
        sort(jobs.begin(), jobs.end(), comp);
        vector<int> dp(m, 0);
        dp[0] = jobs[0][2];
        
        for (auto i = 1; i < m; i++) {
            dp[i] = std::max(dp[i-1], jobs[i][2]);
            int j = binary(jobs, 0, i-1, jobs[i][1]);
            if (j != -1)
                dp[i] = std::max(dp[i], dp[j] + jobs[i][2]);
        }
        return dp[m-1];
    }
    
    int dpot_dp_1(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        
        vector<vector<int>> jobs;
        set<int> endTimes{0};
        for (auto i = 0; i < startTime.size(); i++) {
            jobs.push_back({endTime[i], startTime[i], profit[i]});
            endTimes.insert(endTime[i]);
        }
        
        int curval = 0;
        sort(jobs.begin(), jobs.end());
        unordered_map<int, int> timeToVals;
        timeToVals[0] = 0;
        
        for (auto& c: jobs) {
            
            int end = c[0], start = c[1], val = c[2];
            
            auto it = endTimes.upper_bound(start);
            auto lastEndTime = *prev(it, 1);
            
            timeToVals[end] = std::max(timeToVals[lastEndTime] + val, curval);
            curval = timeToVals[end];
        }
        
        return curval;
    }
};
