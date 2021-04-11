/*
 
 1681. Minimum Incompatibility
 
 You are given an integer array nums​​​ and an integer k. You are asked to distribute this array into k subsets of equal size
 such that there are no two equal elements in the same subset.

 A subset's incompatibility is the difference between the maximum and minimum elements in that array.

 Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally, or return -1 if it is not possible.

 A subset is a group integers that appear in the array with no particular order.

  

 Example 1:

 Input: nums = [1,2,1,4], k = 2
 Output: 4
 Explanation: The optimal distribution of subsets is [1,2] and [1,4].
 The incompatibility is (2-1) + (4-1) = 4.
 Note that [1,1] and [2,4] would result in a smaller sum, but the first subset contains 2 equal elements.
 Example 2:

 Input: nums = [6,3,8,1,3,1,2,2], k = 4
 Output: 6
 Explanation: The optimal distribution of subsets is [1,2], [2,3], [6,8], and [1,3].
 The incompatibility is (2-1) + (3-2) + (8-6) + (3-1) = 6.
 Example 3:

 Input: nums = [5,3,3,6,3,3], k = 3
 Output: -1
 Explanation: It is impossible to distribute nums into 3 subsets where no two elements are equal in the same subset.
  

 Constraints:

 1 <= k <= nums.length <= 16
 nums.length is divisible by k
 1 <= nums[i] <= nums.length
 
 
 
 */
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;

class MinimumIncompatibility {


    /*
        1681.Minimum-Incompatibility
        解法1：DFS
        本题初看有一种错觉，以为小的数字应该尽量和小的数字分在一组，大的数字应该尽量和大的数字分在一组。但是这个贪心策略不成立。比如：[1,1,2,2,3,3,6,8]，4, 贪心策略得到[1,2],[1,2],[3,6],[3,8]，但是最优的答案是[1,2],[1,3],[2,3],[6,8].

        结合本题的提示nums.size()<16，说明这题只能用暴力探索。

        首先我们判定一下无解的情况：当任何一个元素出现的次数大于k的话，说明至少有一组会重复出现两次该元素。于是可以提前返回false。

        在排除无解的情况后，我们就可以放心地用DFS暴力搜索：在数组里连续搜索到n/k个不同的元素后，再从头开始搜索找n/k个不同的元素，直至所有的数组元素都搜到。

        dfs搜索算法中有一个常见而且非常重要的剪枝技巧。比如nums = [1,2,2,3,4,6], k=2, 当你搜索完[1,2,x]之后，不会为第二个数再次搜索2。所以需要在搜索第二个数的时候，用一个last来避免重复搜到相同的数。

        解法2：状态压缩
        对于每一组，我们要选取n个元素中的n/k个，我们将每种选择方法看做是用01bit表示的state。可知，这样的state总共有C(n, n/k)种。然后我们会删掉其中含有重复元素的state，剩下的state可以放入一个states数组，记它的大小是m。

        于是此时我们等于需要解一个背包问题。我们要在states的m种状态中选择k种，使得拼接起来的总状态恰好是111..111，同时希望incompatibility的总和最小。大致的算法是：

        for (int i=0; i<m; i++)
        for (int dpstate=(1<<n)-1; dpstate>0; dpstate--)
            {
            if (states[i]不是dpstate的子集) continue;
            dp[dpstate] = min(dp[dpstate], dp[dpstate - states[i]] + incompatibility[i]);
            }
        上面的算法会超时，原因是dpstate会遍历到大量显然不合法的状态：因为dpstate是选择若干个互斥的state的拼接得到，故dpstate里面的1bit的数目必须是n/k的整数倍。所以我们可以提前仅把合法的dpstate放入一个dpstates的数组，来替换第二层循环。
    */
    int n;
    int k;
    vector<int>visited;
    int ret = INT_MAX;

    int minimumIncompatibility(vector<int>& nums, int k) 
    {
        unordered_map<int,int>count;
        for (auto x: nums)
            count[x]++;
        for (auto x: count)
            if (x.second > k)
                return -1;

        sort(nums.begin(), nums.end());
        this->k = k;
        this->n = nums.size();               
        visited.resize(n);
        
        visited[0] = 1;
        dfs(nums, 0, 1, nums[0], nums[0], 0);
        
        return ret;
    }
    
    void dfs(vector<int>& nums, int cur, int count, int low, int high, int sum)
    {
        if (count==n/k)
        {
            int j=0;
            while (j<n && visited[j]==1)
                j++;
            if (j==n)
            {
                ret = min(ret, sum+high-low);
            }
            else
            {
                visited[j]=1;
                dfs(nums, j, 1, nums[j], nums[j], sum+high-low);
                visited[j]=0;
            }
        }
        else
        {
            int last = -1;
            for (int i=cur+1; i<n; i++)
            {
                if (visited[i]==1) continue;
                if (nums[i]==nums[cur]) continue;
                if (i>cur+1 && nums[i]==last) continue;
                visited[i] = 1;
                dfs(nums, i, count+1, low, nums[i], sum);
                last = nums[i];
                visited[i] = 0;
            }            
        }
    }

 
public:
 
    int n;
    
    int minimumIncompatibility(vector<int>& nums, int k) 
    {
        unordered_map<int,int>count;
        for (auto x: nums)
            count[x]++;
        for (auto x: count)
            if (x.second > k)
                return -1;

        n= nums.size();        
        vector<int>states;
        vector<int>values;
        int state = (1 << n/k) - 1;            
        while (state < (1 << n))
        {
            int val;
            if (!containDuplicate(nums, state, val))
            {
                states.push_back(state);
                values.push_back(val);                
            }
            
            int c = state & - state;
            int r = state + c;
            state = (((r ^ state) >> 2) / c) | r;
        }

        vector<int>dpstates;
        for (int state=0; state<(1<<n); state++)
        {
            if (__builtin_popcount(state) % (n/k) ==0) 
                dpstates.push_back(state);
        }
        reverse(dpstates.begin(), dpstates.end());
        
        vector<int>dp(1<<n, INT_MAX/2);
        dp[0] = 0;

        for (int i=0; i<states.size(); i++)
        {            
            for (auto dpstate: dpstates)
            {                
                if ((dpstate & states[i])!=states[i]) continue;
                dp[dpstate] = min(dp[dpstate], dp[dpstate-states[i]]+values[i]);
            }
        }
        return dp[(1<<n)-1];
    }

    bool containDuplicate(vector<int>&nums, int state, int&val)
    {
        vector<int>p;
        for (int i=0; i<n; i++)
        {
            if ((state>>i)&1)
                p.push_back(nums[i]);
        }
        sort(p.begin(),p.end());
        for (int i=1; i<p.size(); i++)
            if (p[i]==p[i-1]) return true;
        val = p.back()-p.front();
        return false;
    }
    
    
    /*
     Solution -1: Seach
     let m = n/k
     C(n, m) * C(n-m, m) * ... * C(n-k*m, m) * c(m, m) => n!/m! => TLE
     
     n = 16, k = 4, m = 4 => 6306300
     
     */
    
    
public:
    
    /*
      Solution1 L Permutation -> Combination || Group numbers by their order
     (1 2 3 4) | (5 6 7 8) | (9 10 11 12) | (13 14 15 16) T(n) = O(n!) => TLE
     (7 5 8 6) | (11 12 9 10) | (4 1 3 2) | (13 ...
     However, if we have the optimal solution for a given set, the orders doesn't matter, we can convert it from permutation
     2^n( similar to TSP, LC 943/980/996/1125).
     
     dp[mask][i] := min cost to distribute numbers (as a binary mask) and the last number is i.
     
     Init: dp[1<<i][i] = 0 # cost of selecting a single number is zero.
     
     Transition:
     dp[mask | (1 << j)][j] = dp[mask][i]  # if we start a new group e.g. (1 2 3 4) | (5
     
     dp[mask | (1 << j)][j] = dp[mask][i] + nums[i] - nums[j] # if we extend the current group.
     e.g. (1 2 3 4) | (5 8 cost += 8  - 5 = 3
     
     Ans: min(dp[(1 << n) - 1]
     
     Q: How do we capture the max - min ? A: We require a group to be monotonically incresing.
     e.g. 4 8 12 19 => (8 - 5) + (12 - 8) + (19 - 12) => 19 - 5 = 14
     
     Time complexity: O(2^n * n^ 2) Space complexity: O(2^n)
     
     */
    
    int doit_(vector<int>& nums, int k) {
        const int n = nums.size();
        const int c = n / k;
        int dp[1 << 16][16];
        memset(dp, 0x7f, sizeof(dp));
        
        for (int i = 0; i < n; ++i) dp[1 << i][i] = 0;
        
        for (int s = 0; s < 1 << n; ++s)
          for (int i = 0; i < n; ++i) {
              
            if ((s & (1 << i)) == 0) continue;
              
            for (int j = 0; j < n; ++j) {
                
              if ((s & (1 << j))) continue;
                
              const int t = s | (1 << j);
              if (__builtin_popcount(s) % c == 0) {
                dp[t][j] = std::min(dp[t][j], dp[s][i]);
              } else if (nums[j] > nums[i]) {
                dp[t][j] = std::min(dp[t][j], dp[s][i] + nums[j] - nums[i]);
              }
            }
        }
        int ans = *std::min_element(std::begin(dp[(1 << n) - 1]), std::end(dp[(1 << n) - 1]));
        return ans > 1e9 ? - 1 : ans;
    }
    
    int doit_dp_bitmask_tsp(vector<int>& nums, int k) {
        
        const int size = nums.size();
        const int group = size / k;
        int N = (1 << size);
        vector<vector<int>> dp(N, vector<int>(size, 0x7F));
        
        for (int i = 0; i < size; i++) dp[1 << i][i] = 0;
        
        for (int s = 0; s < N; s++){
            
            for (int i = 0; i < size; i++) {
                
                if ((s & (1 << i)) == 0) continue;
                
                for (int j = 0; j < size; j++) {
                    if ((s & (1 << j)) == 1) continue;
                    
                    const int t = s | (1 << j);
                    
                    if (__builtin_popcount(s) % group == 0) {
                        dp[t][j] = std::min(dp[t][j], dp[s][i]);
                        
                    } else if (nums[j] > nums[i]) {
                        dp[t][j] = std::min(dp[t][j], dp[s][i] + nums[j] - nums[i]);
                    }
                }
            }
        }
        
        int ans = *min_element(begin(dp[N-1]), end(dp[N-1]));
        return ans > 1e9 ? -1 : ans;
    }
    
public:

    int ans = INT_MAX, n, m, k;
    
    int doit_backtracking(vector<int>& nums, int k) {
        n = nums.size(), m = n / k;
        this->k = k;
        if(m == 1){
            return 0;
        }
        sort(nums.begin(), nums.end());
        vector<vector<int>> subsets(k);
        backtrack(nums, 0, subsets, 0);
        return ans == INT_MAX ? -1 : ans;
    }

    void backtrack(const vector<int>& nums, int idx, vector<vector<int>>& subsets, int res){
        if(idx == n){
            ans = std::min(ans, res);
            return;
        }
        if(res >= ans){
            return;
        }
        
        for(int i = 0; i < subsets.size(); i++){
            if(subsets[i].size() == m || (!subsets[i].empty() && subsets[i].back() == nums[idx]) || (i > 0 && subsets[i] == subsets[i-1])){
                continue;
            }
            subsets[i].push_back(nums[idx]);
            int cur = 0;
            if(subsets[i].size() > 1){
                int t = subsets[i].size();
                cur = subsets[i][t-1] - subsets[i][t-2];
            }
            backtrack(nums, idx + 1, subsets, res + cur);
            subsets[i].pop_back();
        }
    }
};
