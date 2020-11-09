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

using std::set;
using std::vector;
using std::unordered_map;


class JobScheduling {
    
public:
    
    struct box{
        int s, e, p;
    };

    
    int dpot_dp(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        
        auto comp = [](box const& b1, box const &b2){
            if(b1.e == b2.e)
                return b1.p > b2.p;
            return b1.e < b2.e;
        };
        
        auto binary = [](box task[], int l, int r, int target){
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
        
        
        auto n = startTime.size();
        if(n == 0)
           return 0;
       
        box task[n];
        for(auto i=0; i<n; i++){
            task[i].s = startTime[i];
            task[i].e = endTime[i];
            task[i].p = profit[i];
        }
       
        std::sort(task, task+n, comp);
        int dp[n];
        dp[0] = task[0].p;
       
        for(int i=1; i<n; i++){
           dp[i] = std::max(dp[i-1], task[i].p);
           int j = binary(task, 0, i-1, task[i].s);
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
