/*
90. Subsets II

Given an integer array nums that may contain duplicates, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
 

Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10
*/
#include <vector>
#include <functional>

using std::vector;


class SubsetsWithDup {

    /*
        090.Subsets-II
    常规的DFS。本题需要特别注意的是，如何高效地避免重复搜索。比如1 2 2 2 3，中间的三个相同的2，如果只取两个，其实有三种取法。这三种取法对应的subset其实都长得一样（.. 2 2 ...）。

    去重的技巧就是：对于n个连续的相同元素，如果我们打算取k个，那么永远只取前k个。这样的话，DFS的代码可以写成：

    for (int i=cur; i<nums.size(); i++)
    {
    if (i>=1 && nums[i]==nums[i-1] && visited[i-1]==true)
        continue;
    ...
    }
    这段代码的意思是，如果nums[i]和它前面一个元素相同，但是前面一个元素并没有被选中，那么nums[i]本身也不应该被选中。否则的话，就违背了我们之前的指导方针：对于相同的元素我们不能跳跃着选取。
    
    */
    vector<vector<int>>rets;    
    vector<int>visited;

    vector<vector<int>> subsetsWithDup(vector<int>& nums) 
    {
        int n = nums.size();
        visited.resize(n);

        rets.push_back({});
        sort(nums.begin(), nums.end());
        vector<int>temp;
        dfs(nums, 0, temp);
        return rets;
    }

    void dfs(vector<int>&nums, int cur, vector<int>&temp)
    {
        if (cur==nums.size())
            return;

        for (int i=cur; i<nums.size(); i++)
        {
            if ((i>=1 && nums[i]==nums[i-1]) && visited[i-1]==0)
                continue;

            visited[i] = 1;
            temp.push_back(nums[i]);            
            rets.push_back(temp);
            dfs(nums, i+1, temp);
            temp.pop_back();
            visited[i] = 0;
        }
    }

public:
    vector<vector<int>> doit_dfs(vector<int>& nums) {
        
        std::sort(begin(nums), end(nums));
        vector<vector<int>> ans;
        vector<int> path;
        
        std::function<void(int)> dfs =[&](int index) {
            
            ans.push_back(path);
            
            if (index == nums.size()) return;    
            
            for (int i = index; i<nums.size(); i++) {
                if (i == index || nums[i] != nums[i-1]) {
                    path.push_back(nums[i]);
                    dfs(i+1);
                    path.pop_back();
                }
            }
        };
        
        dfs(0);
        
        return ans;
    }
};


/*
78. Subsets

Given an integer array nums of unique elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
 

Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10
All the numbers of nums are unique.
*/

class Subsets {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        
        vector<vector<int>> ans;
        vector<int> path;
        
        std::function<void(int)> dfs =[&](int index) {
            
            ans.push_back(path);
            
            if (index == nums.size()) return;    
            
            for (int i = index; i<nums.size(); i++) {
                path.push_back(nums[i]);
                dfs(i+1);
                path.pop_back();
            }
        };
        
        dfs(0);
        
        return ans;
    }
};