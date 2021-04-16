/*
1654. Minimum Jumps to Reach Home

A certain bug's home is on the x-axis at position x. Help them get there from position 0.

The bug jumps according to the following rules:

It can jump exactly a positions forward (to the right).
It can jump exactly b positions backward (to the left).
It cannot jump backward twice in a row.
It cannot jump to any forbidden positions.
The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.

Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, 
return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.

 

Example 1:

Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
Output: 3
Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
Example 2:

Input: forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
Output: -1
Example 3:

Input: forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
Output: 2
Explanation: One jump forward (0 -> 16) then one jump backward (16 -> 7) will get the bug home.
 

Constraints:

1 <= forbidden.length <= 1000
1 <= a, b, forbidden[i] <= 2000
0 <= x <= 2000
All the elements in forbidden are distinct.
Position x is not forbidden.


*/
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>

using std::set;
using std::unordered_set;
using std::queue;
using std::vector;

class MinimumJumpsToReachHome {

    /*
        1654.Minimum-Jumps-to-Reach-Home
        本题看上去是一个常规的BFS求最短路径问题：每到一处新的位置，我们有两种选择，向左走或者向右走。已经走过的地方就标记visited以后不再访问。直至访问到x位置。

        但是在写代码的过程中，我们会发现一个问题，那就是如果无限制使用朝右走的权利的话，永远不会停止，这样这个队列不会收敛到空。所以我们似乎应该有一个limit，往右边超越这个limit的时候就不该继续走下去。

        这个limit如何设计呢？我们假设整个路径是通过m次右移和n次左移实现从0到x的。我们可以知道这m次右移和n次左移，我们任意打乱先后顺序的话（但这个乱序要避免碰到forbidden），并不影响最终到达x的结论。
        
        既然如此，我们就没有必要让人一路狂飙到右极限再一路狂飙回来。只要出现cur-b > x的状态，那么就意味着我们之后至少需要一次左移（目的是拉回x附近），那么我们索性就规定这种情况下只能左移，不允许右移。
        如果需要右移，可以安排在这一步之后再走，并且这不会影响到达x的结论。

        于是我们就找到了这样的一个limit = x + b，如果当前位置cur超过了这个limit的话就只可以选择左移。

        但是这个limit有一个bug，那就是如果cur>limit，但是选择左移的时候碰到的是一个forbidden位置，岂不是意味着这个状态就没有任何后继节点了？这就涉及到了上面提到的那个问题，理论上m次右移和n次左移都可以实现从0到x，但是条件是该行走顺序中间不能碰到任何forbidden。为了解决这个问题，我们松弛这个limit的要求，如果能保证 cur-b 大于x、并且也大于任何可能的forbidden位置，那么我们就可以放心地只选择左移。因此这个limit的边界定义为 max(x, max_forbidden) + b。

        综上，本题的BFS策略是：

        1. 如果cur <= limit，允许往右移动（前提是不触碰forbidden）
        2. 如果到达cur时是右移的，那么允许往左移动（前提是不触碰forbidden且不越过0点）
    */
    int visited[8001][2];

    int minimumJumps(vector<int>& forbidden, int a, int b, int x) 
    {
        if (x==0) return 0;
        int max_forbid = *max_element(forbidden.begin(), forbidden.end());
        int limit = std::max(x, max_forbid)+b;

        for (auto x:forbidden)
        {
            visited[x][0] = -1;
            visited[x][1] = -1;
        }
        visited[0][0] = 0;
        
        queue<std::pair<int,int>>q;
        q.push({0,0});
        int step = 0;

        while (!q.empty())
        {
            int len = q.size();
            step++;
            while (len--)
            {
                int i = q.front().first;
                int k = q.front().second;
                q.pop();

                if (i <= limit && visited[i+a][0] == 0)
                {
                    visited[i+a][0] = 1;
                    q.push({i+a,0});
                    if (i+a==x) return step;
                }
                
                if (k==0)
                {
                    if (i-b>=0 && visited[i-b][1] == 0)
                    {
                        visited[i-b][1] = 1;
                        q.push({i-b,1});
                        if (i-b==x) return step;
                    }
                }
            }
        }
        return -1;
    }

public:

    int doit_bfs(vector<int>& forbidden, int a, int b, int x) {
    
        if (x == 0) return 0;
        
        vector<vector<int>> steps(2, vector<int>(6001, INT_MAX));
        
        for(int i = 0; i < forbidden.size(); i++) 
        {
            if(forbidden[i] < steps[0].size())
                steps[0][forbidden[i]] = steps[1][forbidden[i]] = -1;
        }
        
        queue<std::pair<int, int>> q;
        q.push({0, 0});
        int step = 0;
        
        while(!q.empty())
        {
            int size = q.size();
            for(int i = 0; i < size; i++)
            {
                int pos = q.front().first;
                int dir = q.front().second;
                if(pos == x) {
                    return step;
                }
                
                if (pos + a < steps[0].size() && steps[0][pos + a] == INT_MAX) {
                    steps[0][pos + a] = 1 + step;
                    q.push({pos + a, 0});
                }
                
                if (dir == 0 && pos - b >= 0 && steps[1][pos - b] == INT_MAX) {
                    steps[1][pos - b] = 1 + step;
                    q.push({pos - b, 1});
                }
                q.pop();
            }
            step++;    
        }
        return -1;
    }
};