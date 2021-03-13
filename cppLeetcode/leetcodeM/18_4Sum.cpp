/*
18. 4Sum


Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums 
such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Notice that the solution set must not contain duplicate quadruplets.

 

Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
Example 2:

Input: nums = [], target = 0
Output: []
 

Constraints:

0 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109

*/
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_set>

using std::unordered_set;
using std::vector;

class FourSum {

    /*
        18. 4Sum
        按照3sum的思路来做4sum，需要nnn*log(n)的时间复杂度。
        需要注意必要的剪枝来减少计算量。比如第一层循环

        for (int h1=0; h1<nums.size(); h1++)
        {
        if (nums[h1]*4>target) break;
        if (nums[h1]+nums.back()*3<target) continue;
        }
        类似的第二层循环

        for (int h2=0; h2<nums.size(); h2++)
        {
        if (nums[h1]+3*nums[h2]>target) break;
        if (nums[h1]+nums[h2]+nums.back()*2<target) continue;
        }
        对于第三层循环

        int left=h2+1;
        int right=nums.size()-1;
        if (nums[h1]+nums[h2]+2*nums[left]>target) break;
        if (nums[h1]+nums[h2]+2*nums[right]<target) continue;
        对于h1(h2)避免重复元素的操作

        if (h1>0 && nums[h1]==nums[h1-1]) continue;
    */
    vector<vector<int>> fourSum(vector<int>& nums, int target) 
    {
        vector<vector<int>>results;
        if (nums.size()<4) return results;
        
        std::sort(nums.begin(),nums.end());
        
        for (int a=0; a<nums.size(); a++)
        {
            if (nums[a]*4>target) break;
            if (nums[a]+nums.back()*3<target) continue;
            
            if (a>0 && nums[a]==nums[a-1]) continue;
            
            for (int b=a+1; b<nums.size(); b++)
            {
                if (nums[a]+nums[b]*3>target) break;
                if (nums[a]+nums[b]+nums.back()*2<target) continue;
                
                if (b>a+1 && nums[b]==nums[b-1]) continue;
                
                int left = b+1;
                int right = nums.size()-1;
                if (nums[a]+nums[b]+nums[left]*2>target) break;
                                
                while (left<right)
                {
                    if (nums[a]+nums[b]+nums[left]+nums[right]==target)
                    {
                        vector<int>temp = {nums[a],nums[b],nums[left],nums[right]};
                        results.push_back(temp);
                        left++;
                        right--;
                        while (nums[left]==nums[left-1]) left++;
                        while (nums[right]==nums[right+1]) right--;
                        
                    }
                    else if (nums[a]+nums[b]+nums[left]+nums[right]>target)
                        right--;
                    else if (nums[a]+nums[b]+nums[left]+nums[right]<target)
                        left++;
                }
                
            }
            
        }
        return results;
        
    }

public:

    /*
    
        Approach 1: Two Pointers
        The two pointers pattern requires the array to be sorted, so we do that first. Also, it's easier to deal with duplicates if the array is sorted: repeated values are next to each other and easy to skip.

        For 3Sum, we enumerate each value in a single loop, and use the two pointers pattern for the rest of the array. For kSum, we will have k - 2 nested loops to enumerate all combinations of k - 2 values.

        Current
        1 / 10
        Algorithm

        We can implement k - 2 loops using a recursion. We will pass the starting point and k as the parameters. When k == 2, we will call twoSum, terminating the recursion.

        For the main function:

        Sort the input array nums.
        Call kSum with start = 0, k = 4, and target, and return the result.
        For kSum function:

        Check if the sum of k smallest values is greater than target, or the sum of k largest values is smaller than target. Since the array is sorted, the smallest value is nums[start], and largest - the last element in nums.
        If so, no need to continue - there are no k elements that sum to target.
        If k equals 2, call twoSum and return the result.
        Iterate i through the array from start:
        If the current value is the same as the one before, skip it.
        Recursively call kSum with start = i + 1, k = k - 1, and target - nums[i].
        For each returned set of values:
        Include the current value nums[i] into set.
        Add set to the result res.
        Return the result res.
        For twoSum function:

        Set the low pointer lo to start, and high pointer hi to the last index.
        While low pointer is smaller than high:
        If the sum of nums[lo] and nums[hi] is less than target, increment lo.
        Also increment lo if the value is the same as for lo - 1.
        If the sum is greater than target, decrement hi.
        Also decrement hi if the value is the same as for hi + 1.
        Otherwise, we found a pair:
        Add it to the result res.
        Decrement hi and increment lo.
        Return the result res.

        Complexity Analysis

        Time Complexity: \mathcal{O}(n^{k - 1})O(n 
        k−1
        ), or \mathcal{O}(n^3)O(n 
        3
        ) for 4Sum. We have k - 2k−2 loops, and twoSum is \mathcal{O}(n)O(n).

        Note that for k > 2k>2, sorting the array does not change the overall time complexity.

        Space Complexity: \mathcal{O}(n)O(n). We need \mathcal{O}(k)O(k) space for the recursion. kk can be the same as nn in the worst case for the generalized algorithm.

        Note that, for the purpose of complexity analysis, we ignore the memory required for the output.
    */
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        
        sort(begin(nums), end(nums));

        auto twoSum = [](vector<int>& nums, int target, int start) -> vector<vector<int>> {
            vector<vector<int>> res;
            int lo = start, hi = nums.size() - 1;
            while (lo < hi) {
                int sum = nums[lo] + nums[hi];
                if (sum < target || (lo > start && nums[lo] == nums[lo - 1]))
                    ++lo;
                else if (sum > target || (hi < nums.size() - 1 && nums[hi] == nums[hi + 1]))
                    --hi;
                else
                    res.push_back({ nums[lo++], nums[hi--]});
            }
            return res;
        };

        std::function<vector<vector<int>>(vector<int>&, int, int, int)> kSum = [&](vector<int>& nums, int target, int start, int k) -> vector<vector<int>> {
            vector<vector<int>> res;
            if (start == nums.size() || nums[start] * k > target || target > nums.back() * k)
                return res;
            if (k == 2)
                return twoSum(nums, target, start);
            for (int i = start; i < nums.size(); ++i)
                if (i == start || nums[i - 1] != nums[i])
                    for (auto &set : kSum(nums, target - nums[i], i + 1, k - 1)) {
                        res.push_back({nums[i]});
                        res.back().insert(end(res.back()), begin(set), end(set));
                    }
            return res;
        };

        return kSum(nums, target, 0, 4);
    }
    
    /*
        Approach 2: Hash Set
        Since elements must sum up to the exact target value, we can also use the Two Sum: One-pass Hash Table approach.

        In 3Sum: Hash Set, we solved the problem without sorting the array. To do that, we needed to sort values within triplets, and track them in a hash set. Doing the same for k values could be impractical.

        So, for this approach, we will also sort the array and skip duplicates the same way as in the Two Pointers approach above. Thus, the code will only differ in the twoSum implementation.

        Algorithm

        twoSum implementation here is almost the same as in Two Sum: One-pass Hash Table. The only difference is the check to avoid duplicates. Since the array is sorted, we can just compare the found pair with the last one in the result res.


        Complexity Analysis

        Time Complexity: \mathcal{O}(n^{k - 1})O(n 
        k−1
        ), or \mathcal{O}(n^3)O(n 
        3
        ) for 4Sum. We have k - 2k−2 loops iterating over nn elements, and twoSum is \mathcal{O}(n)O(n).

        Note that for k > 2k>2, sorting the array does not change the overall time complexity.

        Space Complexity: \mathcal{O}(n)O(n) for the hash set. The space needed for the recursion will not exceed \mathcal{O}(n)O(n).
    */
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        sort(begin(nums), end(nums));

        auto twoSum = [&](int target, int start) -> vector<vector<int>> {
            vector<vector<int>> res;
            unordered_set<int> s;
            for (auto i = start; i < nums.size(); ++i) {
                if (res.empty() || res.back()[1] != nums[i])
                    if (s.count(target - nums[i]))
                        res.push_back({ target - nums[i], nums[i]});
                s.insert(nums[i]);
            }
            return res;
        };

        std::function<vector<vector<int>>(int, int, int)> kSum = [&](int target, int start, int k) -> vector<vector<int>> {
            vector<vector<int>> res;
            if (start == nums.size() || nums[start] * k > target || target > nums.back() * k)
                return res;
            if (k == 2)
                return twoSum(target, start);
            for (int i = start; i < nums.size(); ++i)
                if (i == start || nums[i - 1] != nums[i])
                    for (auto &set : kSum(target - nums[i], i + 1, k - 1)) {
                        res.push_back({nums[i]});
                        res.back().insert(end(res.back()), begin(set), end(set));
                    }
            return res;
        };

        return kSum(target, 0, 4);
    }

};