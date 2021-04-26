/*
698. Partition to K Equal Sum Subsets

Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k non-empty subsets whose sums are all equal.

 

Example 1:

Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
 

Note:

1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.

*/
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

using std::vector;

class CanPartitionKSubsets {

    /*
        698.Partition-to-K-Equal-Sum-Subsets
        此题据说是NP-hard，没有什么特别高明的算法，就是老老实实地DFS，尝试将所有元素挨个尝试放入k个分类里，直至找到满足条件的分类。

        设计如下的递归函数：DFS(nums, curPos, curGroup, curSum). 注意边界条件的转换：

                if (curGroup==k) return true;
                if (curSum>SUM) return false;        
                if (curSum==SUM) return DFS(nums,0,curGroup+1,0);        
        另外，如果提前将所有元素从大到小排序，则有额外的优化效果：从大元素开始尝试的话，则可以迅速排除一些因为元素过大造成的negative测例。

        此外，在for循环里遍历下一个候选元素时，有一个重要的剪枝手段：

        last = -1;
        for (int i=curPos; i<n; i++)
        {
            //...
            if (nums[i]==last)
                continue;
            last = nums[i];
            //...
        这是因为若nums[i]=a已经被搜索过并且失败后回溯的话，有着相同数值a的其他nums元素就不需要再次被搜索了，注定是失败的。因为我们已经提前把nums排个序，保证了所有相同数值的元素都是相邻的，故很容易skip掉相同的候选元素。

        与本题非常相似的题目有： 473. Matchsticks to Square, 416. Partition Equal Subset Sum, 996. Number of Squareful Arrays
    */
    int total;
    int k;
    int visited[16];

    bool canPartitionKSubsets_dfs_best(vector<int>& nums, int k) 
    {
        std::sort(nums.begin(), nums.end());
        reverse(nums.begin(),nums.end());
        total = std::accumulate(nums.begin(), nums.end(), 0);
        this->k = k;
        if (total%k!=0) return false;

        return dfs(nums, 0, 0, 0);
    }

    bool dfs(vector<int>&nums, int cur, int group, int sum)
    {
        if (group==k)
            return true;
        
        if (sum > total/k)
            return false;

        if (sum == total/k)
            return dfs(nums, 0, group+1, 0);

        int last = -1;
        for (int i=cur; i<nums.size(); i++)
        {
            if (visited[i]==1) continue;
            if (nums[i]==last) continue;
            last = nums[i];
            visited[i] = 1;
            if (dfs(nums, i, group, sum+nums[i]))
                return true;            
            visited[i] = 0;
        }
        return false;
    }

public:

    bool doit_dfs(vector<int>& nums, int k) {
        
        int total = accumulate(begin(nums), end(nums), 0);
        if (total % k != 0) return false;
        
        int ave = total/k;
        int n = nums.size();

        std::sort(begin(nums), end(nums));
        vector<bool> visited(nums.size(), false);
        
        std::function<bool(int, int, int)> dfs = [&](int index, int sums, int group) {
            
            if (group == k) return true;
            
            int last = -1;
            for (int i = index; i < n; i++) {
                
                if (visited[i]) continue;
                
                if (last == nums[i]) continue;
                
                last = nums[i];
                
                if (sums + nums[i] > ave) break;
                
                visited[i] = true;

                if (sums+nums[i] == ave && dfs(0, 0, group+1)) return true;
                    
                if (dfs(index+1, sums+nums[i], group)) return true;
                
                visited[i] = false;
            }
            
            return false;
        };
        
        return dfs(0, 0, 0);
    }
};