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

using std::set;
using std::unordered_map;
using std::deque;
using std::vector;

class IncreasingSubsequence {

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