/*
1815. Maximum Number of Groups Getting Fresh Donuts

There is a donuts shop that bakes donuts in batches of batchSize. They have a rule where they must serve all of the donuts of a batch before serving any donuts of the next batch. 
You are given an integer batchSize and an integer array groups, where groups[i] denotes that there is a group of groups[i] customers that will visit the shop. Each customer will get exactly one donut.

When a group visits the shop, all customers of the group must be served before serving any of the following groups. A group will be happy if they all get fresh donuts. 
That is, the first customer of the group does not receive a donut that was left over from the previous group.

You can freely rearrange the ordering of the groups. Return the maximum possible number of happy groups after rearranging the groups.

 

Example 1:

Input: batchSize = 3, groups = [1,2,3,4,5,6]
Output: 4
Explanation: You can arrange the groups as [6,2,4,5,1,3]. Then the 1st, 2nd, 4th, and 6th groups will be happy.
Example 2:

Input: batchSize = 4, groups = [1,3,2,5,2,2,1,6]
Output: 4
 

Constraints:

1 <= batchSize <= 9
1 <= groups.length <= 30
1 <= groups[i] <= 109

*/

#include <vector>
#include <array>
#include <unordered_map>
#include <map>
#include <functional>

using std::map;
using std::unordered_map;
using std::array;
using std::vector;


class MaxHappyGroups {

    /*
            1815.Maximum-Number-of-Groups-Getting-Fresh-Donuts
        我们从数据的规模上来看，应该猜测这是一个NP问题，解法应该是基于搜索。因为groups的总数最多只有30，暴力搜索也许可行？于是我们可以写出第一个版本：

            int dfs(vector<int>&count, int presum, int i)
            {
                if (i==n) 
                    return 0;

                int bonus = (presum % b == 0);
                int ret = 0;
                for (int j=0; j<b; j++)
                {
                    if (count[j]==0) continue;
                    count[j]--;
                    ret = max(ret, dfs(count, (presum+j) % b, i+1));
                    count[j]++;
                }

                return ret + bonus;
            }
        上面的dfs(count, presum, i)表示我们已经选择了i-1个groups（它们的前缀和是presum、已有的得分是prescore），我们从剩下的groups挑选一个安排在第i个。选哪个好呢？我们不知道，必须每种可能都尝试一次，结合相应的dfs(..., i+1)来判断。这里需要注意的是，如果此时的presum恰好被batch整除，那么说明无论第i个元素取谁，我们都可以得到1分，所以下次递归的时候perscore可以增加1。

        以上的解法自然会TLE，原因是什么呢？显然是没有记忆化。我们可以发现，dfs函数中，其实只要确定了当前的count（即未被安排的groups），其他的参数presum本质上就是确定了的。所以记忆化的key其实就是count。但是count是一个数组，如何将转化为一个方便的key呢？和状态压缩相同的原因。因为count[i]最多30个，用五个bit就能表示（0~32）。batch最多是9，所以总共45位的二进制数就可以表述count数组。这就要求这个key是long long类型。

        我们再分析一下这样的记忆化搜索为什么不会超时？因为每次dfs我们都在查询/创建一个key，我们就思考一下我们最多会有多少个key？看上去似乎count的每个bin最多会有30个，总共有9个bin，因此有30^9个。但实际上并没有这么多，因为这30个元素是分布在9个bin里面的，这是一个约束。只有当每个bin的频次均匀分布时，才对应着最复杂的情况，即(30/9)^9=50805种。试想一下，如果30个元素属于同一个bin里面，那么其实只有30种key。综上所述，dfs是复杂度可行的算法。
    */
    using LL = long long;

    array<int, 10>count;
    int b, n;

    int maxHappyGroups(int batchSize, vector<int>& groups) 
    {
        b = batchSize;                
        n = groups.size();

        for (int i=0; i<10; i++)
            count[i] = 0;
        for (auto x: groups)
            count[x%batchSize]++;
                
        return dfs(count, 0, 0);
    }
    
    int dfs(array<int, 10>&count, int presum, int i)
    {
        if (i==n) 
            return 0;

        int bonus = (presum % b == 0);
        int ret = 0;
        for (int j=0; j<b; j++)
        {
            if (count[j]==0) continue;
            count[j]--;
            ret = std::max(ret, dfs(count, (presum+j) % b, i+1));
            count[j]++;
        }

        return ret + bonus;
    }

public:

    int b, n;
    unordered_map<LL, int>memo;

    int maxHappyGroups(int batchSize, vector<int>& groups) 
    {
        b = batchSize;                
        n = groups.size();

        vector<int>count(b);
        for (auto x: groups)
            count[x%batchSize]++;

        LL state = 0;
        for (int i=0; i<b; i++)
        {
            state += (LL)count[i]<<(i*5);
        }
                
        return dfs(state, 0, 0);
    }
    
    int dfs(LL state, int presum, int i)
    {
        if (i==n) return 0;
        if (memo.find(state)!=memo.end())
            return memo[state];

        int bonus = (presum % b == 0);
        int ret = 0;
        for (int j=0; j<b; j++)
        {
            if ((state>>(j*5))%32 == 0) continue;            
            ret = std::max(ret, dfs(state-(1ll<<(j*5)), (presum+j) % b, i+1));            
        }
        memo[state] = ret + bonus;
        return ret + bonus;
    }

public:

    int doit_dfs_hashtable_dp(int bz, vector<int>& groups) {
        vector<int> cnt(bz);
        int res = 0;
        for (auto group : groups) {
            if (group % bz == 0)
                ++res;
            else if (cnt[bz - group % bz]) {
                --cnt[bz - group % bz];
                ++res;
            }
            else 
                ++cnt[group % bz];
        }

        map<vector<int>, int> dp;
        
        std::function<int(vector<int>&, int)> dfs = [&](vector<int>& cnt, int left) {
            auto it = dp.find(cnt);
            if (it != end(dp)) return it->second;

            int res = 0, bz = cnt.size();
            for (auto j = 1; j < bz; ++j) {
                if (--cnt[j] >= 0)
                    res = std::max(res, (left == 0) + dfs(cnt, (bz + left - j) % bz));
                ++cnt[j];
            }
            return dp[cnt] = res;
        };

        return dfs(cnt, 0) + res;
    }

    /*
            Key observation
        1. If groups have sizes that are fatctor of batch size, we can put it in the front and all of them will be happy, and it is optimal.
        2. For groups if sizes that are larger than batch size, we can use n % k as the new group size which will not affect the final results.

        Similar to LC 1799 this is also a permutation problem.
        [1, 2, 3, 4, 5, 6] => [6, 2, 4, 5, 1, 3]

        Enumerate all possible arrangments to find optimal ones.

        Time complexity: O(n!) = O(30!) => TLE

        Assuming we already know the optinal sequence of the first k groups, the order of the prior sequence not affect the decision of the k+1 group sunce the sum is fixed.
        thus we can convert it to a combination problem.

        Time complexity: O(n*2^n) = (n*2^30) => TLE.

        We need to find more efficient solutions.  
    */
    int doit_dp_bitmask_TLE(int batchSize, vector<int>& groups) {
        const int n = groups.size();
        vector<int> dp(1<<n);

        for (int mask = 0; mask < (1<<n); ++mask) {

            int s = 0;
            for (int i = 0; i < n; i++)
                if (mask & (1<<i)) s = (s + groups[i]) % b;

            for (int i = 0; i < n; i++) {
                if(!(mask & (1<i)))
                    dp[mask | (1<<i)] = std::max(dp[mask|(1<<i)], dp[mask] + (s==0)); // fresh batch happy group
            }
        }

        return dp[(1<<n)-1];
    }

    /*
        The key is the small batch size (k <= 9), using n % k, we have at most 8 different group sizes.
        This could significantly reduce the state space (deduplication).

        State: A counter, {group_size: count}

        Best case:
            . all groups fall into the same bin
            . states: {x: n}, {x: n-1}, ...., {x: 1}, n in total
        
        Worst case:
            . Even distribution?
            . Each bin ahs n/k groups
            . States: (n/k)^k

        Space complexity: O((n/k)^k) ~ 
        Time complexity: O(k*(n/k)^k)
    */
    int doit_dfs_bitmask(int batchSize, vector<int>& groups) {

        int b = batchSize;
        int n = groups.size();
        vector<int> counter(batchSize,0);
        for (auto c: groups) counter[c%b]++;

        map<vector<int>, int> cache;

        std::function<int(int)> dfs = [&](int s) {

            if (cache.count(counter) > 0) return cache[counter];

            int ans = 0;
            for (int i = 1; i < b; i++) {
                if (counter[i] == 0) continue;
                counter[i]--;
                ans = std::max(ans, (s == 0) + dfs((s+i)%b));
                counter[i]++;

            }
            return cache[counter] = ans;
        };
 
        return counter[0] + dfs(0);
    }

};