/*
 
 
 1335. Minimum Difficulty of a Job Schedule
 
 You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).

 You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done in that day.

 Given an array of integers jobDifficulty and an integer d. The difficulty of the i-th job is jobDifficulty[i].

 Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.

  

 Example 1:


 Input: jobDifficulty = [6,5,4,3,2,1], d = 2
 Output: 7
 Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
 Second day you can finish the last job, total difficulty = 1.
 The difficulty of the schedule = 6 + 1 = 7
 Example 2:

 Input: jobDifficulty = [9,9,9], d = 4
 Output: -1
 Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.
 Example 3:

 Input: jobDifficulty = [1,1,1], d = 3
 Output: 3
 Explanation: The schedule is one job per day. total difficulty will be 3.
 Example 4:

 Input: jobDifficulty = [7,1,7,1,7,1], d = 3
 Output: 15
 Example 5:

 Input: jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
 Output: 843

 */
#include <vector>

using std::vector;



class MinDifficulty {
    
public:
    
    
    
    int doit_dp_1(vector<int>&& jobDifficulty, int d) {
        
        auto m = jobDifficulty.size();
        vector<vector<int>> maxv(m, vector<int>(m, 0));
        
        if (d > m)
            return -1;
        
        for (auto i = 0; i < m; i++) {
            for (auto j = i; j > -1; j--) {
                if (i == j)
                    maxv[i][i] = jobDifficulty[i];
                else {
                    maxv[j][i] = std::max(jobDifficulty[j], maxv[j+1][i]);
                }
            }
        }
        
        vector<vector<int>> dp(d, vector<int>(m, INT_MAX));
        
        for (auto i = 0; i < d; i++) {
            for (auto j = i; j < m; j++) {
                if (i == 0)
                    dp[i][j] = maxv[i][j];
                else {
                    for (auto k = i-1; k < j; k++)
                        dp[i][j] = std::min(dp[i][j], dp[i-1][k] + maxv[k+1][j]);
                }
            }
        }
        
        return dp[d-1][m-1] == INT_MAX ? -1 : dp[d-1][m-1];
    }
    
    int doit_dp(vector<int>&& jobs, int d) {
        
        auto m = jobs.size();
        if (m < d)
            return -1;
        
        vector<int> dp(m, INT_MAX);
        
        for (int i = 0; i < d; i++) {
            vector<int> stack;
            vector<int> dp2(m, 0);
            
            for (int j = i; j < m; j++) {
                
                if (i == 0) {
                    dp2[j] = j == 0 ? jobs[j] : std::max(jobs[j], dp2[j-1]);
                } else {
                    dp2[j] = j == 0 ? jobs[j] : dp[j-1] + jobs[j];
                }
                
                while (!stack.empty() && jobs[stack.back()] <= jobs[j]) {
                    int last = stack.back();
                    stack.pop_back();
                    dp2[j] = std::min(dp2[j], dp2[last] - jobs[last] + jobs[j]);
                }
                
                if (!stack.empty())
                    dp2[j] = std::min(dp2[j], dp2[stack.back()]);
                
                stack.push_back(j);
            }
            dp = dp2;
        }
        
        return dp.back();
    }
    
    /*
     
     Think this question like a maze problem on a grid where each cell has a value and you are trying to reach to bottom right corner from top left corner while trying to keep the sum of all visited cells to minimum.

     Set up the grid:

     Given sizen and days d; within a day you can complete n-d+1 many jobs.
     So your grid dimensions are going to be n x (n-d+1)
     You can either go right or bottom on your grid.

     Find the path with min weight:
     Let's call the grid above vals type of vector<vector<int>> and build the solution vector of same type sols. We need to traverse vals from the bottom right corner to the top left corner. sols[0][0] is going to be the answer.

     If you are on the right bottom cell (base case), the answer is that cell
     If you are on a bottom cell, all the remaining jobs need to be done on that same day.
     The answer is max(vals[i][j], sols[i][j+1])
     If you are on a right-most cell; that means all the remaining jobs need to be done on a separate day.
     So, the answer is vals[i][j] + sols[i+1][j]
     Else; we need to find the min path weight based on how many jobs we can finish that day. Let's say the index of the last job finished that day was k where k >= j
     Then answer is max(jobs_done_that_day) + sols[i+1][k]
     Here's the code does that:
     
     */
    
    int doit_dp_1(vector<int>& jobDifficulty, int d) {
        
        int maxd = jobDifficulty.size()-d+1;  // max num jobs can be done on the same day
        
        if (maxd < 1) {
            return -1;
        }
        
        int size = jobDifficulty.size()-maxd+1;
        vector<vector<int>> vals;
        vector<vector<int>> sols;
        
        // set up the grid
        for (int i=0; i<size; ++i) {
            vals.push_back(vector<int>(maxd, -1));
            sols.push_back(vector<int>(maxd, -1));
            for (int j=0; j<maxd; ++j) {
                vals[i][j] = jobDifficulty[i+j];
            }
        }
        
        // build the solution
        for (int i=size-1; i>=0; --i) {
            for (int j=maxd-1; j>=0; --j) {
                if (j == maxd-1 && i == size-1) {
                    sols[i][j] = vals[i][j];
                } else if (j == maxd-1) {
                    sols[i][j] = vals[i][j] + sols[i+1][j];
                } else if (i == size-1) {
                    sols[i][j] = std::max(vals[i][j], sols[i][j+1]);
                } else {
                    // int val = numeric_limits<int>::max();
                    int val = INT_MAX;
                    int temp = 0;
                    for (int k=j; k<maxd; ++k) {
                        temp = std::max(temp, vals[i][k]);
                        val = std::min(val, temp + sols[i+1][k]);
                    }
                    sols[i][j] = val;
                }
            }
        }
        
        return sols[0][0];
    }
};


void test_1335_minimum_difficulty_jobschedule() {
    
    MinDifficulty().doit_dp(vector<int>{6,5,4,3,2,1}, 2);
    
    MinDifficulty().doit_dp(vector<int>{9, 9, 9}, 4);
    
    MinDifficulty().doit_dp(vector<int>{1, 1, 1}, 3);
}
