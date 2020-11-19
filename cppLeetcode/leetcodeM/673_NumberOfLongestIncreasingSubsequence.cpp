/*
 
 673. Number of Longest Increasing Subsequence
 
 Given an integer array nums, return the number of longest increasing subsequences.

 Notice that the sequence has to be strictly increasing.

  

 Example 1:

 Input: nums = [1,3,5,4,7]
 Output: 2
 Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].
 Example 2:

 Input: nums = [2,2,2,2,2]
 Output: 5
 Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.

  

 Constraints:

 1 <= nums.length <= 2000
 -106 <= nums[i] <= 106
 
 */

#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;


class FindNumberOfLIS {
    
public:
    
    int doit_binary_search(vector<int>& nums) {
        
        
        vector<int> keys;
        vector<unordered_map<int, int>> buff;
        
        buff.push_back({});
        buff.back().insert(nums[0], 1);
        keys.push_back(nums[0]);
        
        auto search = [&](int a) {
            int low = 0, high = keys.size();
            
            while (low < high) {
                auto mid = (low + high) / 2;
                
                if (keys[mid] >= 0) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }
            
            return low;
        };
        
        for (auto num : nums) {
            
            int j = search(num);
            
            if (j == keys.size()-1) {
                buff.push_back({});
                keys.push_back(num);
            }
            
            int total = 0;
            for (auto iter = buff[j].begin(); iter != buff[j].end(); iter++) {
                if (iter->first < num) {
                    total += iter->second;
                } else {
                    iter = buff[j].erase(iter);
                }
            }
            
            buff[j+1].insert({num, total});
            
        }
        
        int total = 0;
        for (auto [k, v] : buff.back())
            total += v;
        
        return total;
    }
};



