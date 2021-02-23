/*

621. Task Scheduler

Given a characters array tasks, representing the tasks a CPU needs to do, where each letter represents a different task.
Tasks could be done in any order. Each task is done in one unit of time. For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period between two same tasks (the same letter in the array),
that is that there must be at least n units of time between any two same tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.



Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation:
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.
Example 2:

Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.
Example 3:

Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation:
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A


Constraints:

1 <= task.length <= 104
tasks[i] is upper-case English letter.
The integer n is in the range [0, 100].

*/
#include <vector>
#include <unordered_map>
#include <queue>

using std::unordered_map;
using std::vector;
using std::priority_queue;


class TaskScheduler {

public:

    /*
        621.Task-Scheduler
        解法１：模拟最优解的过程
        此题非常类似 358.Rearrange-String-k-Distance-Apart。

        设计一个大顶堆的priority_queue，每次取出权重最多的n+1个（或少于这个数目）字符，将其权重减一后再放回队列中。

        需要注意的是，即使队列中的元素少于n+1，只要没有完成所有的任务，根据题意的idle设定，计数器仍需要count+=n+1. 只有最后一轮（弹出后队列为空）时，计数器才 count+= num，其中num时队列弹出前的元素个数。

        解法２：
        我们令n自加１，这样题意要求每n个相邻的位置不能有重复的元素．如果有重复的元素，则必须放在每ｎ个为一组的每个小组的前端．

        首先，我们可以在队列中找到出现的最大的字符频率maxFreq.这样我们构造maxFreq-1个容器，每个容器至少有n的容量（可以比n多，后面会讲）．暂时我们将每个位置都置为idle占位.
        然后我们将所有的字符都过一遍，如果该字符的词频<=maxFreq-1，那么我们就将它依次,均匀地放在每个容器的最前端即可．如果词频==maxFreq，那么就仍然照此方法处理其中的maxFreq-1个，剩下一个就扔到最后再处理（用count++记录一下）．
        如果一个容器装满了n个，没关系，在这个容器的后面继续添加；如果一个容器始终没有满n，那么没有满的部分我们依然设置为idle.

        最后我们把这些容器并列排成一排，再加上落单的那些可以再摆放一排，就是我们的解决方案．

        这些容器有多少个位置呢？注意到，这些容器都是均匀填充的，即任意两个容器之间的个数不会相差大于１（把idle也算上），所以无非就是两种情况，一种就是这些容器（至少部分容器）还没有填充满n个，所以我们需要的位置依然是整个矩阵的大小加上落单的个数(maxFreq-1)*n+count．
        另外一种就是这些容器都已经填充满n个了，说明没有任何需要用idle来占位的情况，那么我们需要的位置的个数就是字符的个数tasks.size()

        与本题类似的题目还有：767. Reorganize String，1054. Distant Barcodes
    */
    int doit_heap(vector<char>& tasks, int n) 
    {
        unordered_map<char,int> Map;
        for (auto ch: tasks)
            Map[ch]++;

        priority_queue<int> pq;
        for (auto a:Map) pq.push(a.second);
        
        n++;
        int count = 0;
        while (pq.size()>0)
        {                            
            int k = std::min(n, (int)pq.size());            
            
            vector<int>temp;
            for (int i=0; i<k; i++)
            {
                int a = pq.top();
                pq.pop();
                a--;
                if (a!=0) temp.push_back(a);
            }
            if (temp.size()>0)
                count+=n;
            else
                count+=k;
            
            for (auto x: temp)
                pq.push(x);
        }
        return count;        
    }

    int doit_greedy(vector<char>& tasks, int n) 
    {
        unordered_map<char,int>Map;
        for (auto ch: tasks)
            Map[ch]++;
        
        int maxFreq = 0;
        for (auto a:Map)
            maxFreq = std::max(maxFreq, a.second);
        
        int result = (maxFreq-1)*(n+1);
        int count = 0;
        for (auto a: Map) {
            if (a.second == maxFreq) count++;
        }
        return std::max(result+count, (int)tasks.size());
    }

    int doit_math(vector<char>& tasks, int n) {
        
        int cnt[26] = {0};
        for (auto c : tasks)
            cnt[c-'A']++;
        
        int maxv = -1, freq = 0, total = 0;
        for (auto i = 0; i < 26; i++) {
            if (cnt[i] == maxv)
                freq += 1;
            else if (cnt[i] > maxv) {
                maxv = cnt[i];
                freq = 1;
            }
            
            total += cnt[i];
        }

        return std::max(total, (1 + n) * (maxv-1) + freq);
    }
};