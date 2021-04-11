/*
40. Combination Sum II

Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

 

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]
 

Constraints:

1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30

*/

#include <vector>
#include <functional>

using std::vector;


class combinationSum2 {

    /*
        040.Combination-Sum-II
        本题和LC 039非常类似。但有一个非常重要的情况需要考虑。假设target=5，candidates={3,1,1}，那么按照传统的DFS方法，会搜索到两个组合{3,1}，这两个组合中的1其实对应着的是candidates里面不同的元素。如何高效地去除这种重复的情况呢？

        我们先将candidates排序。然后规定：凡是相同的元素，我们只能按先后次序连续取，而不能跳着取。比如上面的例子，我们如果需要取一个1，那么就取第一个1.如果需要取两个1，那么就取前两个1.以此类推。

        那么如何在代码中高效地实现这个过滤呢？非常简单。

        for (int i=idx; i<candidates.size(); i++)
        {
        if (i>idx && candidates[i]==candidates[i-1])
            continue;
        
        // do you recursion here
        }
        这段代码的语境是，在这一轮中，我们需要在candidates[idx:end]中间选取一个数加入comb。如果我们选中了candidates[i]，那么说明candidates[i-1]就没有被选中。此时如果发现candidates[i]==candidates[i-1]，则意味着相同的元素我们“跳着”选取了，这是上面指定的规则所不允许的，就可以终止。

        当然有一个特例，如果i选中的就是candidates[idx]，那是可以豁免的。这是因为上一轮我们选中的就是candidates[idx-1]。这样即使candidates[i]==candidates[i-1]，其实恰好说明我们就是顺着连续选取地这个元素。

        这个处理技巧在DFS的题目中会经常遇到，需要能够熟练掌握。
    */
    vector<vector<int>>rets;
public:
    vector<vector<int>> dfs(vector<int>& candidates, int target) 
    {
        sort(candidates.begin(), candidates.end());
        vector<int>comb = {};
        DFS(candidates, target, 0, 0, comb);
        return rets;
    }
    
    void DFS(vector<int>& candidates, int target, int idx, int sum, vector<int>&comb)
    {
        if (target==sum)
        {
            rets.push_back(comb);
            return;
        }
        if (sum>target)
        {
            return;
        }
        
        for (int i=idx; i<candidates.size(); i++)
        {
            if (i>idx && candidates[i]==candidates[i-1])
                continue;
            
            comb.push_back(candidates[i]);
            DFS(candidates, target, i+1, sum+candidates[i], comb);
            comb.pop_back();
        }
    }

public:
    
    vector<vector<int>> doit_dfs(vector<int>& candidates, int target) {
        
        vector<vector<int>> ans;
        vector<int> path;
        int n = candidates.size();
        std::sort(begin(candidates), end(candidates));
        
        std::function<void(int, int)> dfs = [&](int index, int sums) {
            
            if (sums == target) {
                ans.push_back(path);
                return;
            }
            
            if (index == n) return;
            
            for (int i = index; i < n; i++) {
                
                if (i != index && candidates[i] == candidates[i-1]) continue;
                
                if (sums + candidates[i] > target) break;
                
                path.push_back(candidates[i]);
                dfs(i+1, sums+candidates[i]);
                path.pop_back();
            }
            
        };
        
        dfs(0, 0);
        
        return ans;
    }
};


/*

77. Combinations

Given two integers n and k, return all possible combinations of k numbers out of the range [1, n].

You may return the answer in any order.

 

Example 1:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
Example 2:

Input: n = 1, k = 1
Output: [[1]]
 

Constraints:

1 <= n <= 20
1 <= k <= n
*/


class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        
        vector<vector<int>> ans;
        vector<int> path;
        vector<int> candidates(n);
        std::iota(begin(candidates), end(candidates), 1);
        
        std::function<void(int, int)> dfs = [&](int index, int count) {
            
            if (count == k) {
                ans.push_back(path);
                return;
            }
            
            if (n - index < k - count) return;
            
            for (int i = index; i < n; i++) {
                path.push_back(candidates[i]);
                dfs(i+1, count+1);
                path.pop_back();
            }
        };
        
        dfs(0, 0);
        
        return ans;
    }
};