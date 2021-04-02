/*
826. Most Profit Assigning Work

We have jobs: difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job. 

Now we have some workers. worker[i] is the ability of the ith worker, which means that this worker can only complete a job with difficulty at most worker[i]. 

Every worker can be assigned at most one job, but one job can be completed multiple times.

For example, if 3 people attempt the same job that pays $1, then the total profit will be $3.  If a worker cannot complete any job, his profit is $0.

What is the most profit we can make?

Example 1:

Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
Output: 100 
Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get profit of [20,20,30,30] seperately.
Notes:

1 <= difficulty.length = profit.length <= 10000
1 <= worker.length <= 10000
difficulty[i], profit[i], worker[i]  are in range [1, 10^5]

*/
#include <vector>
#include <map>
#include <algorithm>

using std::map;
using std::vector;


class MaxProfitAssignment {

    /*
        826.Most-Profit-Assigning-Work
        此题不难想到正确的贪心解法。

        我们将所有的任务ｔａｓｋｓ按照难度从小到大进行排序然后遍历。如果难度小的任务的收益是ｐ，那么比之难度更大的任务的收益理论上不应该比ｐ更小，否则我们可以选择用难度小收益大的项目替代更划算。
        所以我们将这些任务的收益重新赋值，使得ｔａｓｋｓ按照难度从小到大排列后，收益也是递增的。

        接下来对于任何一个工人，我们在这个ｔａｓｋｓ序列中找到他所能接受的最大难度ｄ的任务，那么这个任务对应的（重新赋值后的）收益，就是这个工人所能创造的最大收益。因为这个收益，本质对应了所以难度小于等于ｄ的任务中的最高收益。每个工人都是如此计算，得到的总收益就是答案。

        本题的ｃｐｐ解法要注意下面这句：

        auto iter = upper_bound(tasks.begin(),tasks.end(),make_pair(x,INT_MAX));
        这里的第三个参数一定要用make_pair来生成，不能用{x,INT_MAX}，否则编译器不能自动正确地转化。
    
    */
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) 
    {
        vector<std::pair<int,int>>tasks;
        for (int i=0; i<difficulty.size(); i++)
            tasks.push_back({difficulty[i],profit[i]});
        
        std::sort(tasks.begin(),tasks.end());
        
        int MAX = tasks[0].second;
        for (int i=1; i<tasks.size(); i++)
        {
            tasks[i].second = std::max(tasks[i].second,MAX);
            MAX = tasks[i].second;
        }        
        
        int sum = 0;
        for (int x:worker)
        {
            auto iter = std::upper_bound(tasks.begin(),tasks.end(), {x,INT_MAX});
            if (iter!=tasks.begin())
            {
                iter = std::prev(iter,1);
                sum+=iter->second;
            }
        }
        return sum;
    }

public:
    
    int doit_greedy(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        
        map<int, int> diff2profit;
        
        for (int i = 0; i < difficulty.size(); i++) {
            diff2profit[difficulty[i]] = std::max(profit[i], diff2profit[difficulty[i]]);
        }
        
        int maxv = INT_MIN;
        for (auto it = begin(diff2profit); it != end(diff2profit); it++) {
            maxv = std::max(maxv, it->second);
            it->second = maxv;
        }
        
        int ans = 0;
        
        for (auto diff : worker) {
            
            auto it = diff2profit.lower_bound(diff);
            
            if (it == begin(diff2profit) && it->first > diff) continue;
            
            if (it == end(diff2profit) || it->first > diff) it = prev(it);
            
            ans += it->second;
        }
        
        return ans;
    }
};