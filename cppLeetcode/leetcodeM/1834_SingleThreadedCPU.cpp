/*
1834. Single-Threaded CPU

You are given n​​​​​​ tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the i​​​​​​th​​​​ task will be available to process at enqueueTimei and will take processingTimei to finish processing.

You have a single-threaded CPU that can process at most one task at a time and will act in the following way:

If the CPU is idle and there are no available tasks to process, the CPU remains idle.
If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
Once a task is started, the CPU will process the entire task without stopping.
The CPU can finish a task then start a new one instantly.
Return the order in which the CPU will process the tasks.

 

Example 1:

Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]
Explanation: The events go as follows: 
- At time = 1, task 0 is available to process. Available tasks = {0}.
- Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
- At time = 2, task 1 is available to process. Available tasks = {1}.
- At time = 3, task 2 is available to process. Available tasks = {1, 2}.
- Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
- At time = 4, task 3 is available to process. Available tasks = {1, 3}.
- At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
- At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
- At time = 10, the CPU finishes task 1 and becomes idle.
Example 2:

Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
Output: [4,3,2,0,1]
Explanation: The events go as follows:
- At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
- Also at time = 7, the idle CPU starts processing task 4. Available tasks = {0,1,2,3}.
- At time = 9, the CPU finishes task 4 and starts processing task 3. Available tasks = {0,1,2}.
- At time = 13, the CPU finishes task 3 and starts processing task 2. Available tasks = {0,1}.
- At time = 18, the CPU finishes task 2 and starts processing task 0. Available tasks = {1}.
- At time = 28, the CPU finishes task 0 and starts processing task 1. Available tasks = {}.
- At time = 40, the CPU finishes task 1 and becomes idle.
 

Constraints:

tasks.length == n
1 <= n <= 105
1 <= enqueueTimei, processingTimei <= 10^9
*/
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;


class SingleCPU {

    /*
        1834.Single-Threaded-CPU
        我们将所有的tasks按照入列时间从早到晚排序。同时维护一个curTime表示当前的时间，初始为0。

        如果curTime晚于目前最早待入列的任务，那么我们就将该任务放入任务池。如果curTime早于目前最早待入列的任务，就在已经任务池（一个优先队列）里面挑选可以启动的任务，挑选的原则按照题目的要求：先看处理时长，再看ID大小。所以显然，任务池的数据结构就是一个优先队列。

        每处理完一个任务，curTime就更新变得更大。直至curTime大于等于当前最早待入列的任务。然后重复之前的操作，直至所有任务入列，以及所有任务池里的任务完成。
    */
    typedef long long LL;
    typedef std::pair<LL, LL> PLL;

    vector<int> getOrder(vector<vector<int>>& tasks) 
    {
        for (int i=0; i<tasks.size(); i++)
            tasks[i].push_back(i);
        
        sort(tasks.begin(), tasks.end());
        priority_queue<PLL, vector<PLL>, std::greater<>>pq;
        
        LL cur = 0;
        vector<int>rets;
        for (int i=0; i<tasks.size(); i++)
        {
            while (cur < tasks[i][0] && !pq.empty())
            {
                rets.push_back(pq.top().second);
                cur+=pq.top().first;
                pq.pop();
            }            
            
            pq.push({tasks[i][1], tasks[i][2]});
            cur = max(cur, (LL)tasks[i][0]);
        }
        while (!pq.empty())
        {
            rets.push_back(pq.top().second);
            cur+=pq.top().first;
            pq.pop();
        }
        return rets;        
    }

public:

    vector<int> doit_heap(vector<vector<int>>& tasks) {
  
        vector<int> ans;
        for (int i = 0; i < tasks.size(); i++)
            tasks[i].push_back(i);
        std::sort(begin(tasks), end(tasks), [](auto& a, auto& b){ return a[0] < b[0]; });
        priority_queue<vector<int>, vector<vector<int>>, std::greater<>> pq;
        
        int i = 0;
        long long startTime = -1;
        
        while (i < tasks.size() || !pq.empty()) { 
            
            if (pq.empty() && i<tasks.size() && tasks[i][0] > startTime) startTime = tasks[i][0];
            
            while (i < tasks.size() && tasks[i][0] <= startTime) {
                pq.push({tasks[i][1], tasks[i][2]});
                i++;
            }
            
            startTime += pq.top()[0];
            ans.push_back(pq.top()[1]);
            pq.pop();
        }
        
        return ans;
    }
};