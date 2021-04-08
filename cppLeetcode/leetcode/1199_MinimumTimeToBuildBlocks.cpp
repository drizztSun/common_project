/*
 1199. Minimum Time to Build Blocks
 
 You are given a list of blocks, where blocks[i] = t means that the i-th block needs t units of time to be built. A block can only be built by exactly one worker.

 A worker can either split into two workers (number of workers increases by one) or build a block then go home. Both decisions cost some time.

 The time cost of spliting one worker into two workers is given as an integer split. Note that if two workers split at the same time, they split in parallel so the cost would be split.

 Output the minimum time needed to build all blocks.

 Initially, there is only one worker.

  

 Example 1:

 Input: blocks = [1], split = 1
 Output: 1
 Explanation: We use 1 worker to build 1 block in 1 time unit.
 Example 2:

 Input: blocks = [1,2], split = 5
 Output: 7
 Explanation: We split the worker into 2 workers in 5 time units then assign each of them to a block so the cost is 5 + max(1, 2) = 7.
 Example 3:

 Input: blocks = [1,2,3], split = 1
 Output: 4
 Explanation: Split 1 worker into 2, then assign the first worker to the last block and split the second worker into 2.
 Then, use the two unassigned workers to build the first two blocks.
 The cost is 1 + max(3, 1 + max(1, 2)) = 4.
 
 */
#include <vector>
#include <algorithm>

using std::vector;

class MinBuildTime {

    /*
        1199.Minimum-Time-to-Build-Blocks
        感觉本题用top-down的递归要比bottom up的动态规划更好写。

        我们将所有任务按照从大到小的顺序排序。令dp[i][j]表示用j个工人完成blocks[i:end]的最少时间。我们有两种决策：

        当前我们不派工人干活，只派工人分裂，这样需要花费固定split的时间，索性贪心些，将人数double一下。所以dfs(i,j) = split + dfs(i, j*2)
        当前我们至少派一个工人干活，干什么活呢？肯定是干耗时最长的活（也就是blocks[i]），因为我们可以把耗时短的工作放在稍后去做，起到尽量并行完成的目的。因此dfs(i,j) = blocks[i] + dfs(i+1, j-1).
        当然，我们也可以在当前派两个工人干活，这样的话就是dfs(i,j) = blocks[i] + dfs(i+1, j-2).但是注意到，这个决策其实是包含在上面的第二个决策里的，我们不需要重复去列举。否则我们如果枚举当前指派干活的工人人数，会TLE。

        边界条件有这么几种：

        工作干完了，即i=blocks.size().
        工作没干完，但没有工人了，即j==0，这时候无法做任何操作了（包括分裂）。
        工人比工作的数量多，那么就直接让所有工人都并行开工，这样答案就是blocks[i].
    
    */
    int dp[1000][1001];
    vector<int>blocks;
    int n;
    int split;

    int minBuildTime(vector<int>& blocks, int split) 
    {
        n = blocks.size();
        sort(blocks.begin(), blocks.end(), std::greater<int>());        
        this->blocks = blocks;
        this->split = split;
        
        for (int i=0; i<1000; i++)
            for (int j=0; j<1001; j++)
                dp[i][j] = -1;
        
        return dfs(0, 1);
    }

    int dfs(int i, int j) // the min time to use j workers to finish blocks[i:end]
    {
        if (i == n) return 0; // we are done with all jobs
        if (j == 0) return INT_MAX/2; // we do not have any workers to move on
        if (j > n-i) return blocks[i]; // we have enough workers to start all remaining jobs simutaneously
        if (dp[i][j] != -1) return dp[i][j];
        
        dp[i][j] = min(split + dfs(i, j*2), max(blocks[i], dfs(i+1, j-1)));
        
        return dp[i][j];
    }


public:

    int doit_binary_search(vector<int>& blocks, int split) {
    
        std::sort(rbegin(blocks), rend(blocks));
        
        auto search = [&](int cost) {
            
            int worker = 1;
            
            for (int i = 0; i < blocks.size(); i++) {
                
                if (worker == 0 || blocks[i] > cost) return false;
                
                while (blocks[i] + split <= cost) {
                    worker *= 2;
                    if (worker >= blocks.size()-i) return true;
                    cost -= split;
                }
                worker--;
            }
            return true;
        };
        
        int left = 0, right = 1e9+7;
        
        while (left < right) {
            
            int mid = left + (right - left) / 2;
            
            
            if (search(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
            
        }
        
        return left;
    }

    
    int doit_binary_search(vector<int>& blocks, int split) {
        
        std::sort(blocks.rbegin(), blocks.rend());
        int l = 0;
        int r = 1e9 + 7;
        int ans = -1;
        
        while(l <= r) {
            
            int m = (l + r) / 2;
            
            if(bs(blocks, split, m)) {
                ans = m;
                r = m - 1;
            }
            else
                l = m + 1;
        }
        
        return ans;
    }
    
    bool bs(vector<int>& blocks, int split, int time) {
        int workers = 1;
        
        for(int i = 0; i < blocks.size(); i++) {
            if(!workers || blocks[i] > time)
                return false; // No time or no free workers left
            
            // Keep splitting as long as we can split such that the biggest block can be built
            while(blocks[i] + split <= time) {
                workers *= 2;
                if(workers > blocks.size())
                    return true; // We have more workers than no. of blocks, so exit as possible
                time-= split;
            }
            workers--;
        }
        
        return true;
        
    }
};
