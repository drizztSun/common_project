/*
473. Matchsticks to Square

You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. 
You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.

Return true if you can make this square and false otherwise.

 

Example 1:


Input: matchsticks = [1,1,2,2,2]
Output: true
Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
Example 2:

Input: matchsticks = [3,3,3,3,4]
Output: false
Explanation: You cannot find a way to form a square with all the matchsticks.
 

Constraints:

1 <= matchsticks.length <= 15
0 <= matchsticks[i] <= 109

*/
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <functional>

using std::unordered_set;
using std::vector;


class Solution {

    /*
        473.Matchsticks-to-Square
        本题是NP-hard的搜索题，基本思想就是无脑的DFS,挨个尝试所有的nums元素的组合,是否能恰好构成四段大小相等的sum(这个sum就是nums总数和的四分之一).

        本题设计的递归函数: bool DFS(vector<int>& nums, int curIdx, int curEdge, int curSum, vector<int>& visited)

        curEdge表示当前我们在凑第几条边.如果凑满四条边,就说明成功.

        curSum表示对于当前的边,我们已经累加了多少数字.如果累加到恰好curSum==sum,那么我们就清零开始DFS下一条边.如果curSum>sum,就可以终止当前搜索.如果curSum<sum,则当前边还需要尝试搜索更多数字加入进去.

        visited是标记每个数字是否被访问过.因为是整体就是深度搜索+回溯的算法,所以要记得退出时要恢复标记.

        另外，一个常用的节省时间的技巧是将nums按照从大到小排序，这样能更容易遇到不合条件的情况，及早剪枝，避免过深的探索。

        LC上有一道几乎一模一样的题目：698. Partition to K Equal Sum Subsets
    */
    bool visited[15];
    int total;
    bool makesquare(vector<int>& nums) 
    {
        if (nums.size()==0) return false;
        total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total%4!=0) return false;
        sort(nums.begin(), nums.end());
        reverse(nums.begin(), nums.end());

        return dfs(nums, 0, 0, 0);
    }

    bool dfs(vector<int>& nums, int cur, int group, int sum)
    {
        if (group==4) return true;
        if (sum > total/4) return false;
        if (sum == total/4)
            return dfs(nums, 0, group+1, 0);
        
        int last = -1;
        for (int i=cur; i<nums.size(); i++)
        {
            if (visited[i]==1) continue;
            if (nums[i]==last) continue;
            visited[i] = 1;            
            last = nums[i];
            if (dfs(nums, i+1, group, sum+nums[i]))
                return true;
            visited[i] = 0;
        }
        return false;
    }

public:

    bool doit_dfs(vector<int>& matchsticks) {
        
        int total = std::accumulate(begin(matchsticks), end(matchsticks), 0);
        if (total % 4 != 0) return false;

        int n = matchsticks.size();
        int line = total / 4;

        unordered_set<int> nogood;

        std::function<bool(int, int, int)> dfs = [&](int mask, int sums, int group) {

            if (nogood.count(mask) > 0) return false;

            if (sums == 0 && group == 4 && mask == (1 << n) - 1) return true;

            for (int i = 0; i < n; i++) {

                if (mask & (1 << i)) continue;

                if (sums + matchsticks[i] > line) continue;

                if (dfs(mask | (1 << i), sums + matchsticks[i] == line ? 0 : sums + matchsticks[i], sums + matchsticks[i] == line ? group + 1 : group))
                    return true;
            }

            nogood.insert(mask);
            return false;
        };

        return dfs(0, 0, 0);
    }
};