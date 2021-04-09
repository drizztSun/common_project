/*
1818. Minimum Absolute Sum Difference


You are given two positive integer arrays nums1 and nums2, both of length n.

The absolute sum difference of arrays nums1 and nums2 is defined as the sum of |nums1[i] - nums2[i]| for each 0 <= i < n (0-indexed).

You can replace at most one element of nums1 with any other element in nums1 to minimize the absolute sum difference.

Return the minimum absolute sum difference after replacing at most one element in the array nums1. Since the answer may be large, return it modulo 109 + 7.

|x| is defined as:

x if x >= 0, or
-x if x < 0.
 

Example 1:

Input: nums1 = [1,7,5], nums2 = [2,3,5]
Output: 3
Explanation: There are two possible optimal solutions:
- Replace the second element with the first: [1,7,5] => [1,1,5], or
- Replace the second element with the third: [1,7,5] => [1,5,5].
Both will yield an absolute sum difference of |1-2| + (|1-3| or |5-3|) + |5-5| = 3.
Example 2:

Input: nums1 = [2,4,6,8,10], nums2 = [2,4,6,8,10]
Output: 0
Explanation: nums1 is equal to nums2 so no replacement is needed. This will result in an 
absolute sum difference of 0.
Example 3:

Input: nums1 = [1,10,4,4,2,7], nums2 = [9,3,5,1,7,4]
Output: 20
Explanation: Replace the first element with the second: [1,10,4,4,2,7] => [10,10,4,4,2,7].
This yields an absolute sum difference of |10-9| + |10-3| + |4-5| + |4-1| + |2-7| + |7-4| = 20
 

Constraints:

n == nums1.length
n == nums2.length
1 <= n <= 105
1 <= nums1[i], nums2[i] <= 105

*/
#include <vector>
#include <set>

using std::set;
using std::vector;


class MinAbsoluteSumDiff {



public:

    /*
        I missread the description at first and solved a wrong (and more difficult) problem.
        So, for each position, we need to find the best potential replacement to minimize abs(n1[i] - n2[i]). 
        We can track the biggest gain between original and replaced value among all numbers, and use it in the end.
        To find the best potential replacement, we can sort numbers in n1 and use binary search to find numbers close to n2[i].
    */
    int minAbsoluteSumDiff(vector<int>& n1, vector<int>& n2) {
        long res = 0, gain = 0;
        set<int> s(begin(n1), end(n1));
        for (int i = 0; i < n1.size(); ++i) {
            long original = abs(n1[i] - n2[i]);
            res += original;
            if (gain < original) {
                auto it = s.lower_bound(n2[i]);
                if (it != end(s))
                    gain = std::max(gain, original - abs(*it - n2[i]));
                if (it != begin(s))
                    gain = std::max(gain, original - abs(*prev(it) - n2[i]));
            }
        }
        return (res - gain) % 1000000007;
    }

    /*
        LeetCode 1818. Minimum Absolute Sum Difference 这道题目有点阴险，贪心找diff最大的pair来替换是不对的，反例：[7, 9], [1, 4]。每对pair都可能是candidate，正确的做法是老老实实处理每个pair，
        使用二分搜索/lower_bound在nums1中找到和nums2[i]最接近的数。时间复杂度：O(nlogn)，空间复杂度：O(n)。
    */
    int doit_(vector<int>& nums1, vector<int>& nums2) {

        constexpr int hmod = 1e9+7;
        const int n = nums1.size();
        long ans = 0;
        int gain = 0;
        set<int> s(begin(nums1), end(nums1));

        for (int i = 0; i < n; i++) {
            
            const int diff = abs(nums1[i] - nums2[i]);
            ans += diff;
            if (diff <= gain) continue;
            
            auto it = s.lower_bound(nums2[i]);
            if (it != s.end())
                gain = std::max(gain, diff - abs(*it - nums2[i]));
        
            if (it != s.begin())
                gain = std::max(gain, diff - abs(*prev(it) - nums2[i]));
        }

        return (ans - gain) % hmod;
    }


    int doit_(vector<int>& nums1, vector<int>& nums2) {
        
        vector<int> sortednums1(nums1);
        std::sort(begin(sortednums1), end(sortednums1));
        
        int gain = 0, index = -1, can = 0;

        for (int i = 0; i < nums2.size(); i++) {

            auto it = lower_bound(begin(sortednums1), end(sortednums1), nums2[i]);
            
            int org = abs(nums1[i] - nums2[i]);
            
            if (it != begin(sortednums1) && *prev(it) != nums1[i] && org - abs(*prev(it)-nums2[i]) > gain) {
                gain = org - abs(*prev(it)-nums2[i]);
                can = *prev(it);
                index = i;
            }

            if (it != end(sortednums1)  && *it != nums1[i] && org - abs(*it - nums2[i]) > gain) {
                gain = org - abs(*it - nums2[i]);
                can = *it;
                index = i;
            }
        }
        
        if (index != -1) nums1[index] = can;
        
        long ans = 0;
        int hmod = 1e9+7;
        
        for (int i = 0; i < nums1.size(); i++)
            ans = (ans + abs(nums1[i] - nums2[i])) % hmod;

        return ans;
    }
};