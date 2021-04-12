/*
1723. Find Minimum Time to Finish All Jobs

You are given an integer array jobs, where jobs[i] is the amount of time it takes to complete the ith job.

There are k workers that you can assign jobs to. Each job should be assigned to exactly one worker. 
The working time of a worker is the sum of the time it takes to complete all jobs assigned to them. 
Your goal is to devise an optimal assignment such that the maximum working time of any worker is minimized.

Return the minimum possible maximum working time of any assignment.

 

Example 1:

Input: jobs = [3,2,3], k = 3
Output: 3
Explanation: By assigning each person one job, the maximum time is 3.
Example 2:

Input: jobs = [1,2,4,7,8], k = 2
Output: 11
Explanation: Assign the jobs the following way:
Worker 1: 1, 2, 8 (working time = 1 + 2 + 8 = 11)
Worker 2: 4, 7 (working time = 4 + 7 = 11)
The maximum working time is 11.
 

Constraints:

1 <= k <= jobs.length <= 12
1 <= jobs[i] <= 10^7

*/
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>


using std::vector;

class MinimumTimeRequired {

public:

    /*
        1723.Find-Minimum-Time-to-Finish-All-Jobs
        
        解法1：状态压缩DP
        考虑到只有不超过12件jobs，可以用大小不超过4096的01二进制bit来表示任何jobs的组合状态。我们令dp[i][state]表示使用i个工人、分配state所代表的jobs时，可以得到的the minimum possible maximum working time。
        突破口是第i个工人做了哪些工作？我们可以枚举state的子集subset作为第i个工人的分配任务，那么状态转移方程
        dp[i][state] = min{max(dp[i-1][state-subset], time[subset])} for all subsets.

        解法2：二分搜值+状态压缩DFS
        解法1虽然写法简单，但是效率并不高。事实上很多dp[i][state]的状态其实早早对应了某个工人被分配了过长的时间，但是我们没有剪枝，而是暴力把这个二维循环统统计算了出来。

        高效的办法就是用二分搜值来假设单个工人的时间上限threshold。然后判断在th的前提下，能否DFS搜索出一个可行解。这里依然可以用状态压缩的DFS。初始状态是(1<<n)-1，每一个回合就减去一个subset（注意这个subset的总时间必须小于等于th）。
        经过k个回合（分配了k个工人）看看是否能将状态减至0，代表所有的任务都已经安排完毕。

        解法3：二分搜值+常规DFS
        常规的DFS也可以写，而且剪枝比状态压缩更灵活。我们令workers数组表示k个工人每人分配的时长。在递归函数dfs(i)里，我们试图分配第i个工作。只要当前workers[j]不超过th，那么我们就可以把第i个工作分配给第j个工人，然后继续递归下去。直至所有的任务都分配完。

        我们用两个剪枝来优化时间。第一，我们优先分配时间较长的工作，这样能更早的触发限制，及早终止不必要的探索。第二，在某一层递归中，我们我们已经尝试过把第i个工作分配给某个空闲的工人，那么我们就不用再尝试把第i个工作分配给其他空间的工人，因为效果是等价的。
    */

    int workers[12];
    int k;

    bool dfs(vector<int>&jobs, int curJob, int load)
    {       
        if (curJob == jobs.size()) return true;

        int flag = 0;
        for (int j=0; j<k; j++) {

            if (workers[j] + jobs[curJob] > load) continue;
            
            // *** important
            // Prior to send the job to idle worker, if an idle worker takes it and failed, other idle works have no need to try.
            // if idle work can make it correct, it will no need to try other idle work,
            // This is typical cutoff. 
            if (workers[j]==0) {
                if (flag==1) continue;
                else flag = 1;
            }

            workers[j] +=jobs[curJob];
            if (dfs(jobs, curJob+1, load)) return true;
            workers[j] -=jobs[curJob];
        }        
        return false;
    }
    
    int doit_binary_search(vector<int>& jobs, int k) {

        int n = jobs.size();
        
        // sort and sent bigger jobs, it can makes it failed so fast, then it can help dfs.
        //  
        sort(jobs.begin(), jobs.end());
        reverse(jobs.begin(), jobs.end());
        this->k = k;
        
        int high = accumulate(jobs.begin(), jobs.end(), 0);
        int low = 1;
        
        while (low < high)
        {
            for (int i=0; i<k; i++)
                workers[i] = 0;

            int mid = low + (high-low)/2;
            if (dfs(jobs, 0, mid))
                high = mid;
            else
                low = mid+1;            
        }
        return high;        
    }

    int doit_dp_bottomup(vector<int>& jobs, int k) {

            // It is not a high performance, because it calculate all dp[i][state]. but most of them is useless.
            // because of some status means one worker take care most of jobs, it doesn't make sense for our cases. because it any calculate the maximum value.
            // 

        
            int N = jobs.size();
            int totalStatus = 1 << N;

            vector<vector<int>> dp(k+1, vector<int>(totalStatus, INT_MAX/2));
            vector<int> startTimes(totalStatus);

            // non-job assigmnent on 0 workers, it is 0. but any others dp[0][status] = INT_MAX, because of 0 worker working on it, it should be INT_MAX
            dp[0][0] = 0;

            // dp[i][status]: the minimum possible maximum working time of any assignment 
            // if we use i workers and get jobs if state done

            // 00110101

            // dp[i][state] = min{max(dp[i-1][status-subset], time[subset])} over all possible subset of state.

            for (int status = 0; status < totalStatus; status++) {
                int total = 0;
                for (int i = 0; i < N; i++) {
                    if ((status >> i) & 1) total += jobs[i];
                }
                startTimes[status] = total;
            }

            for (int i = 1; i <= k; i++) {

                for (int status = 1; status < totalStatus; status++) {

                    for (int subset = status; subset > 0; subset=(subset-1)&status) {
                        // minMax, max worktime for assignment among i and i-1 works, compare with subset done by i;
                        dp[i][status] = std::min(dp[i][status], std::max(dp[i-1][status-subset], startTimes[subset]));
                    }
                }
            }

            return dp[k][totalStatus-1];
    }

    int doit_dp_binary_search(vector<int>& jobs, int k) {

        int N = jobs.size();
        int totalStatus = 1 << N;
        vector<int> startTimes(totalStatus);

        for (int status = 0; status < totalStatus; status++) {
            int total = 0;
            for (int i = 0; i < N; i++) {
                if ((status >> i) & 1) total += jobs[i];
            }
            startTimes[status] = total;
        }
    
    
        int low = 1, high = std::accumulate(begin(jobs), end(jobs), 0);
        vector<vector<int>> visited(1<<N, vector<int>(k, 0));
    
        std::function<bool(int, int, int)> dfs = [&](int status, int load, int m) {
            
            if (status == 0) return true;
            if (m == k) return false; 
            
            if (visited[status][m] == -1)
                return false;
            
            // assign subset of status to m th morkts and less than load 
            for (int subset = status; subset > 0; subset=(subset-1)&status) {
                if (startTimes[subset] > load) continue;
                if (dfs(status - subset, load, m+1)) return true;
            }
            
            visited[status][m] = -1;
            return false;
        };


        while (low < high) {
            int mid = (low + high) / 2;
            
            for (int status = 0; status < totalStatus; status++) {
                for (int i = 0; i < k; i++)
                    visited[status][i] = 0;
            }
            
            if (dfs((1<<N) - 1, mid, 0)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        return high;
    }

    int stateTime[4100];
    int visited[4100][13];
    int k;
public:
    int doit_binary_search_static_memory(vector<int>& jobs, int k) 
    {
        int n = jobs.size();        
        this->k = k;
        for (int state=0; state<(1<<n); state++)
        {
            int sum = 0;
            for (int i=0; i<n; i++)
            {
                if ((state>>i)&1)
                    sum += jobs[i];
            }
            stateTime[state] = sum;            
        }

        int high = accumulate(jobs.begin(), jobs.end(), 0);
        int low = 1;
        
        while (low < high)
        {
            for (int i=0; i<4100; i++)
                for (int j=0; j<=12; j++)
                    visited[i][j] = 0;

            int mid = low + (high-low)/2;
            if (dfs((1<<n)-1, mid, 0))
                high = mid;
            else
                low = mid+1;            
        }
        return high;        
    }
    
    bool dfs(int state, int th, int m)
    {       
        if (state == 0)
            return true;
        if (m==k)
            return false;
        
        if (visited[state][m]==1)
            return false;
        
        for (int subset=state; subset>0; subset=(subset-1)&state)
        {
            if (stateTime[subset] > th) continue;            
            if (dfs(state-subset, th, m+1))
                return true;
        }
        visited[state][m] = 1;
        return false;
    }
};