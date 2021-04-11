/*
491. Increasing Subsequences


Given an integer array, your task is to find all the different possible increasing subsequences of the given array, 
and the length of an increasing subsequence should be at least 2.

 

Example:

Input: [4, 6, 7, 7]
Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
 

Constraints:

The length of the given array will not exceed 15.
The range of integer in the given array is [-100,100].
The given array may contain duplicates, and two equal integers should also be considered as a special case of increasing sequence.

*/
#include <vector>
#include <deque>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <functional>

using std::unordered_set;
using std::set;
using std::unordered_map;
using std::deque;
using std::vector;

class IncreasingSubsequence {

    /*                
        491.Increasing-Subsequences
        典型的DFS的应用。在nums数组中遍历递增序列的第一项的可能值，确定了这个位置start之后，把锅甩给DFS让它从start+1开始找接下来的递增序列。

        构造DFS函数：nums是题目给的数组，start表示需要开始探索的位置，curRes存放的是之前已经找到的递增序列。

        void DFS(vector<int>& nums, int start, vector<int>curRes)
        用循环 for (int i=start; i<nums.size; i++) 遍历第一项的可能性。要排除几种情况：

        DFS的终止条件：start已经超过了nums.size()，没有元素可以加入队列，就地返回。
        新元素无法接上之前的序列构成新的递增序列，即 nums[i]<curRes.back()
        重复。究竟什么情况会造成重复呢？假设i在遍历过程中先选择了a，加入了队列并以此进行深度搜索，穷尽了之后所有可能的答案；然后回溯到这一轮，i又选择了b，恰好nums[a]==nums[b]，那么以nums[b]为首的所有可能的答案，必然是之前以nums[a]为首的答案的子集，也就是说一定已经被之前探索a进行DFS时穷尽过了，如果再探索b得到的一定都是之前的重复答案。显然，我们应该在这个for循环的轮回里设置一个集合，凡是已经出现过的数字，都不用再基于它进行DFS了。
        最后要注意的一个细节就是，不必搜索到nums的结尾再确定一个可行解加入results。只要curRes新增了一个元素，都满足题意，可以立即加入results.
    */
    vector<vector<int>> findSubsequences(vector<int>& nums) 
    {
        vector<vector<int>>results;
        vector<int>curRes;
        DFS(nums,0,curRes,results);
        return results;
    }
    
    void DFS(vector<int>& nums, int idx, vector<int>&curRes, vector<vector<int>>&results)
    {
        if (curRes.size()>1) results.push_back(curRes);
        if (idx==nums.size()) return;                

        unordered_set<int>Set;
        for (int i=idx; i<nums.size(); i++)
        {            
            if (curRes.size()!=0 && nums[i]<curRes.back() ) continue;
            if (Set.find(nums[i])!=Set.end()) continue;            
            Set.insert(nums[i]);
            
            curRes.push_back(nums[i]);
            DFS(nums,i+1,curRes,results);
            curRes.pop_back();                        
        }
    }

public:
    
    vector<vector<int>> doit_bfs(vector<int>& nums) {

        deque<vector<int>> seqs = {{}};
        deque<int> last_idxs = {0};
        unordered_map<int,int> last_occ;
        
        for (auto i = 0; i < nums.size(); ++i) {
            auto n = nums[i];
            auto& last_occ_idx = last_occ[n];
            auto sz = seqs.size();
            for (auto j = 0; j < sz; ++j) {
                if ((seqs[j].empty() || seqs[j].back() <= n) && last_idxs[j] >= last_occ_idx) {
                    seqs.emplace_back(seqs[j]);
                    last_idxs.emplace_back(i+1);
                    seqs.back().push_back(n);
                }
            }
            last_occ_idx = i+1;
        }
        vector<vector<int>> v;
        v.reserve(seqs.size() - last_occ.size() - 1);
        while (!seqs.empty()) {
            if (seqs.front().size() >= 2) 
                v.emplace_back(move(seqs.front()));
            seqs.pop_front();
        }
        return v;
    }

    vector<vector<int>> doit_backtracking(vector<int>& nums){

        vector<int> curr;
        set<vector<int>> res;
        
        std::function<void(int)> backtracing = [&](int startIndex) {
            if (curr.size() >= 2) {
                res.insert(curr);
            }
            
            for (int i=startIndex; i<nums.size(); i++) {
                if (curr.empty() || curr.back() <= nums[i]) {
                    curr.push_back(nums[i]);
                    backtracing(i+1);
                    curr.pop_back();
                }
            }
        };

        backtracing(0);
        return vector<vector<int>>(res.begin(), res.end());
    }

    vector<vector<int>> doit_dp(vector<int>& nums) {
        
        int n = nums.size();
        
        vector<vector<int>>increasingSequences;
        set<vector<int>>sequenceSet;
        
        vector<std::pair<int,int>> dp(n,{-1,-1});
                
        for(int i=1;i<n;i++)
        {
            int l = increasingSequences.size();
            
            for(int j=0;j<i;j++)
            {
                if(nums[j]<=nums[i])
                {
                    increasingSequences.push_back({nums[j],nums[i]});
                    sequenceSet.insert({nums[j],nums[i]});
                    
                    for(int k=dp[j].first;k<dp[j].second;k++)
                    {
                        increasingSequences.push_back(increasingSequences[k]);
                        increasingSequences.back().push_back(nums[i]); 
                        sequenceSet.insert(increasingSequences.back());
                    }
                }
            }
            
            int h = increasingSequences.size();
            
            if(l<h)dp[i] = {l,h};
        }
        
        vector<vector<int>>result(sequenceSet.begin(),sequenceSet.end());

        return result;
    }
};