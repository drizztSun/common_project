/*
15. 3Sum

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Example 2:

Input: nums = []
Output: []
Example 3:

Input: nums = [0]
Output: []
 

Constraints:

0 <= nums.length <= 3000
-105 <= nums[i] <= 10^5

*/
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <unordered_map>


using std::set;
using std::unordered_set;
using std::unordered_map;
using std::vector;


class ThreeSum {

    /*
        15.3Sum
        这是双指针算法的基本题，必须熟练掌握，快速准确地实现。

        需要注意的细节：
        一定要先排序。
        为了避免重复，仅在确认发现了一组解之后再移动left和right指针略过重复项。不要先略过重复项再判断是否解成立。
        if (nums[left]+nums[right]==sum)
        {
            记录结果;
            left++;
            right--;
            while (left<right && nums[left]==nums[left-1]) left++;
            while (left<right && nums[right]==nums[right+1]) right--;
        }
        对于最外层的循环，也是确定一个，先展开内层循环，再略过最外层的重复项。
        for (int a=0; a<nums.size(); a++)
        {
            inner loop;
            while (nums[a]==nums[a+1]) a++;
        }


        [Leetcode Link](https://leetcode.com/problems/3sum)
    */
    vector<vector<int>> threeSum(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>>result;
        
        for (int a=0; a<nums.size(); a++)
        {

            int sum=-nums[a];
            
            int left=a+1;
            int right=nums.size()-1;
            
            while (left<right)
            {
                if (nums[left]+nums[right]==sum)
                {
                    result.push_back({nums[a],nums[left],nums[right]});
                    left++;
                    right--;
                    while (left<right && nums[left]==nums[left-1]) left++;
                    while (left<right && nums[right]==nums[right+1]) right--; 
                }
                else if (nums[left]+nums[right]<sum)
                    left++;
                else if (nums[left]+nums[right]>sum)
                    right--;
            }
            
            while (a+1<nums.size() && nums[a]==nums[a+1])
                a++;
        }
        
        return result;
    }


public:
    
    vector<vector<int>> doit_twopointer(vector<int>& nums) {
    
        std::sort(begin(nums), end(nums));
        vector<vector<int>> res;
        
        auto search = [&](int start) {
            
            int i = start + 1, j = nums.size()-1;
            while (i < j) {
                int total = nums[i] + nums[j] + nums[start];
                if (total < 0) {
                    i++;
                } else if (total > 0) {
                    j--;
                } else {
                    res.push_back({nums[start], nums[i], nums[j]});
                    i++;
                    j--;
                    while (i < j && nums[i-1] == nums[i])
                        i++;
                }
            }
        };
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0)
                break;
            if (i == 0 || nums[i-1] != nums[i])
                search(i);
        }
        return res;
    }

    /*
        Approach 1: Two Pointers
        We will follow the same two pointers pattern as in Two Sum II. It requires the array to be sorted, so we'll do that first. As our BCR is \mathcal{O}(n^2)O(n 
        2
        ), sorting the array would not change the overall time complexity.

        To make sure the result contains unique triplets, we need to skip duplicate values. It is easy to do because repeating values are next to each other in a sorted array.

        If you are wondering how to solve this problem without sorting the array, go over the "No-Sort" approach below. There are cases when that approach is preferable, and your interviewer may probe your knowledge there.

        After sorting the array, we move our pivot element nums[i] and analyze elements to its right. We find all pairs whose sum is equal -nums[i] using the two pointers pattern, so that the sum of the pivot element (nums[i]) and the pair (-nums[i]) is equal to zero.

        As a quick refresher, the pointers are initially set to the first and the last element respectively. We compare the sum of these two elements to the target. If it is smaller, we increment the lower pointer lo. Otherwise, we decrement the higher pointer hi. Thus, the sum always moves toward the target, and we "prune" pairs that would move it further away. Again, this works only if the array is sorted. Head to the Two Sum II solution for the detailed explanation.

        Current
        1 / 14
        Algorithm

        The implementation is straightforward - we just need to modify twoSumII to produce triplets and skip repeating values.

        For the main function:

        Sort the input array nums.
        Iterate through the array:
        If the current value is greater than zero, break from the loop. Remaining values cannot sum to zero.
        If the current value is the same as the one before, skip it.
        Otherwise, call twoSumII for the current position i.
        For twoSumII function:

        Set the low pointer lo to i + 1, and high pointer hi to the last index.
        While low pointer is smaller than high:
        If sum of nums[i] + nums[lo] + nums[hi] is less than zero, increment lo.
        If sum is greater than zero, decrement hi.
        Otherwise, we found a triplet:
        Add it to the result res.
        Decrement hi and increment lo.
        Increment lo while the next value is the same as before to avoid duplicates in the result.
        Return the result res.


        Complexity Analysis

        Time Complexity: (n^2). twoSumII is O(n), and we call it nn times.

        Sorting the array takes O(nlogn), so overall complexity is O(nlogn + n^2). This is asymptotically equivalent to O(n^2).

        Space Complexity: from O(logn) to O(n), depending on the implementation of the sorting algorithm. For the purpose of complexity analysis, we ignore the memory required for the output.
    */
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(begin(nums), end(nums));
        vector<vector<int>> res;
        for (int i = 0; i < nums.size() && nums[i] <= 0; ++i)
            if (i == 0 || nums[i - 1] != nums[i]) {
                twoSumII(nums, i, res);
            }
        return res;
    }
    void twoSumII(vector<int>& nums, int i, vector<vector<int>> &res) {
        int lo = i + 1, hi = nums.size() - 1;
        while (lo < hi) {
            int sum = nums[i] + nums[lo] + nums[hi];
            if (sum < 0) {
                ++lo;
            } else if (sum > 0) {
                --hi;
            } else {
                res.push_back({ nums[i], nums[lo++], nums[hi--] });
                while (lo < hi && nums[lo] == nums[lo - 1])
                    ++lo;
            }
        }
    }

    /*
        Approach 2: Hashset
        Since triplets must sum up to the target value, we can try the hash table approach from the Two Sum solution. This approach won't work, however, if the sum is not necessarily equal to the target, like in 3Sum Smaller and 3Sum Closest.

        We move our pivot element nums[i] and analyze elements to its right. We find all pairs whose sum is equal -nums[i] using the Two Sum: One-pass Hash Table approach, so that the sum of the pivot element (nums[i]) and the pair (-nums[i]) is equal to zero.

        To do that, we process each element nums[j] to the right of the pivot, and check whether a complement -nums[i] - nums[j] is already in the hashset. If it is, we found a triplet. Then, we add nums[j] to the hashset, so it can be used as a complement from that point on.

        Like in the approach above, we will also sort the array so we can skip repeated values. We provide a different way to avoid duplicates in the "No-Sort" approach below.

        Algorithm

        The main function is the same as in the Two Pointers approach above. Here, we use twoSum (instead of twoSumII), modified to produce triplets and skip repeating values.

        For the main function:

        Sort the input array nums.
        Iterate through the array:
        If the current value is greater than zero, break from the loop. Remaining values cannot sum to zero.
        If the current value is the same as the one before, skip it.
        Otherwise, call twoSum for the current position i.
        For twoSum function:

        For each index j > i in A:
        Compute complement value as -nums[i] - nums[j].
        If complement exists in hashset seen:
        We found a triplet - add it to the result res.
        Increment j while the next value is the same as before to avoid duplicates in the result.
        Add nums[j] to hashset seen
        Return the result res.

        Complexity Analysis

        Time Complexity: (n^2). twoSumII is O(n), and we call it nn times.

        Sorting the array takes O(nlogn), so overall complexity is O(nlogn + n^2). This is asymptotically equivalent to O(n^2).

        Space Complexity: O(n) for the hashset.
    */
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(begin(nums), end(nums));
        vector<vector<int>> res;
        for (int i = 0; i < nums.size() && nums[i] <= 0; ++i)
            if (i == 0 || nums[i - 1] != nums[i]) {
                twoSum(nums, i, res);
            }
        return res;
    }
    void twoSum(vector<int>& nums, int i, vector<vector<int>> &res) {
        unordered_set<int> seen;
        for (int j = i + 1; j < nums.size(); ++j) {
            int complement = -nums[i] - nums[j];
            if (seen.count(complement)) {
                res.push_back({nums[i], complement, nums[j]});
                while (j + 1 < nums.size() && nums[j] == nums[j + 1]) {
                    ++j;
                }
            }
            seen.insert(nums[j]);
        }
    }


    /*
        Approach 3: "No-Sort"
        What if you cannot modify the input array, and you want to avoid copying it due to memory constraints?

        We can adapt the hashset approach above to work for an unsorted array. We can put a combination of three values into a hashset to avoid duplicates. Values in a combination should be ordered (e.g. ascending). Otherwise, we can have results with the same values in the different positions.

        Algorithm

        The algorithm is similar to the hashset approach above. We just need to add few optimizations so that it works efficiently for repeated values:

        Use another hashset dups to skip duplicates in the outer loop.
        Without this optimization, the submission will time out for the test case with 3,000 zeroes. This case is handled naturally when the array is sorted.
        Instead of re-populating a hashset every time in the inner loop, we can use a hashmap and populate it once. Values in the hashmap will indicate whether we have encountered that element in the current iteration. When we process nums[j] in the inner loop, we set its hashmap value to i. This indicates that we can now use nums[j] as a complement for nums[i].
        This is more like a trick to compensate for container overheads. The effect varies by language, e.g. for C++ it cuts the runtime in half. Without this trick the submission may time out.

        Complexity Analysis

        Time Complexity: \mathcal{O}(n^2)O(n 
        2
        ). We have outer and inner loops, each going through nn elements.

        While the asymptotic complexity is the same, this algorithm is noticeably slower than the previous approach. Lookups in a hashset, though requiring a constant time, are expensive compared to the direct memory access.

        Space Complexity: \mathcal{O}(n)O(n) for the hashset/hashmap.

        For the purpose of complexity analysis, we ignore the memory required for the output. However, in this approach we also store output in the hashset for deduplication. In the worst case, there could be \mathcal{O}(n^2)O(n 
        2
        ) triplets in the output, like for this example: [-k, -k + 1, ..., -1, 0, 1, ... k - 1, k]. Adding a new number to this sequence will produce n / 3 new triplets.
    */
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> res;
        unordered_set<int> dups;
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); ++i)
            if (dups.insert(nums[i]).second) {
                for (int j = i + 1; j < nums.size(); ++j) {
                    int complement = -nums[i] - nums[j];
                    auto it = seen.find(complement);
                    if (it != end(seen) && it->second == i) {
                        vector<int> triplet = {nums[i], nums[j], complement};
                        sort(begin(triplet), end(triplet));
                        res.insert(triplet);
                    }
                    seen[nums[j]] = i;
                }
            }
        return vector<vector<int>>(begin(res), end(res));
    }

};