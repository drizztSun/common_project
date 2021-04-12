/*
465. Optimal Account Balancing

You are given an array of transactions transactions where transactions[i] = [fromi, toi, amounti] indicates that the person with ID = fromi gave amounti $ to the person with ID = toi.

Return the minimum number of transactions required to settle the debt.

 

Example 1:

Input: transactions = [[0,1,10],[2,0,5]]
Output: 2
Explanation:
Person #0 gave person #1 $10.
Person #2 gave person #0 $5.
Two transactions are needed. One way to settle the debt is person #1 pays person #0 and #2 $5 each.
Example 2:

Input: transactions = [[0,1,10],[1,0,1],[1,2,5],[2,0,5]]
Output: 1
Explanation:
Person #0 gave person #1 $10.
Person #1 gave person #0 $1.
Person #1 gave person #2 $5.
Person #2 gave person #0 $5.
Therefore, person #1 only need to give person #0 $4, and all debt is settled.
 

Constraints:

1 <= transactions.length <= 8
transactions[i].length == 3
0 <= fromi, toi <= 20
fromi != toi
1 <= amounti <= 100

*/

#include <vector>
#include <map>
#include <functional>

using std::map;
using std::vector;


class MinTransfers {

    /*
        465.Optimal-Account-Balancing
        首先，此题是NP-complete问题，只能用暴力的搜索．

        我们比较容易想到的DFS方法是，对于第一个人净值不为零的话，我们找所有其他净值不为零的人匹配，将第一个人先填成零再说．然后递归处理剩下的．这种方法在lintcode上会超时．

        另一种巧妙的方法是，其思想是：将这组人分成若干组，使得每组人的净值加和为零．这样总共Ｎ个人，如果能找到K个这样的组，那么实际交换的次数就是N-K．
        也就是每组内部每个人循环交换一次，而组间就不用交换了．所以如果能找到最大的分组数，那么总的最小的交换次数就是N-maxGroup

        令一个Ｎ位的二进制数mask来记录每个人的状态．初始值mask=(1<<N)-1，其所有的bit位为一，表示这些人都还没有被考察.我们逐一遍历每种bit位的可能情况：

        for (int subset=mask; subset!=0; subset=(subset-1)&mask) 
        如果遇到一个subset，其bit位为１的人的净值加和为零，那么我们就可以递归考察剩下的：

        if (zeroSum(subset)) DFS(mask-subset, groupCount+1);
        递归的结束条件是mask变成了零，说明了所有的zero-sum subsequence已经遍历完了．
    */
    vector<int>q;
    int maxGroup=0, N;
    
    int minTransfers(vector<vector<int>>& transactions) 
    {
        map<int,int>Map;
        for (int i=0; i<transactions.size(); i++)
        {
            Map[transactions[i][0]]+=transactions[i][2];
            Map[transactions[i][1]]-=transactions[i][2];
        }        
        for (auto a:Map)
        {   
            if (a.second!=0)
                q.push_back(a.second);
        }
            
        N = q.size();
        int GroupCount = 0; 
        DFS((1<<N)-1, GroupCount);        
        return N-maxGroup;
    }
    
    void DFS(int mask, int GroupCount)
    {
        if (mask==0)
        {
            maxGroup = std::max(maxGroup,GroupCount);
            return;
        }
        for (int subSet = mask; subSet!=0; subSet=((subSet-1)&mask))
        {
            if (zeroSum(subSet))
                DFS(mask-subSet, GroupCount+1);
        }
    }
    
    bool zeroSum(int mask)
    {
        int sum = 0;
        for (int i=0; i<N; i++)
        {
            if ((mask>>i)&1)
                sum+=q[i];
        }
        return sum==0;            
    }

public:
    
    int minTransfers(vector<vector<int>>& transactions) {
        
        
        unordered_map<int, int> Map;
        
        for (const auto& c: transactions) {
            Map[c[0]] += c[2];
            Map[c[1]] -= c[2];
        }
        
        vector<int> debets;
        
        for (auto it: Map)
            if (it.second != 0) debets.push_back(it.second);
        
        int N = debets.size();
        
        int maxgroups = 0;
        
        auto zeromask = [&](int subset) {
            int total = 0;
            for (int i = 0; i < N; i++)
                total += ((subset >> i) & 1) * debets[i];
            return total == 0;
        };
        
        std::function<void(int, int)> dfs = [&](int masks, int curgroups) {
            
            if (masks == 0) {
                maxgroups = std::max(maxgroups, curgroups);
                return;
            }
            
            for (int subset = masks; subset != 0; subset=((subset-1)&masks)) {
             
                if (zeromask(subset)) {
                    dfs(masks-subset, curgroups+1);
                }
            }
        };
        
        dfs((1<<N)-1, 0);
        return N - maxgroups;
    }
};