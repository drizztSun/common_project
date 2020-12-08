/*
 1326. Minimum Number of Taps to Open to Water a Garden
 
 There is a one-dimensional garden on the x-axis. The garden starts at the point 0 and ends at the point n. (i.e The length of the garden is n).

 There are n + 1 taps located at points [0, 1, ..., n] in the garden.

 Given an integer n and an integer array ranges of length n + 1 where ranges[i] (0-indexed) means the i-th tap can water the area [i - ranges[i], i + ranges[i]] if it was open.

 Return the minimum number of taps that should be open to water the whole garden, If the garden cannot be watered return -1.

  

 Example 1:


 Input: n = 5, ranges = [3,4,1,1,0,0]
 Output: 1
 Explanation: The tap at point 0 can cover the interval [-3,3]
 The tap at point 1 can cover the interval [-3,5]
 The tap at point 2 can cover the interval [1,3]
 The tap at point 3 can cover the interval [2,4]
 The tap at point 4 can cover the interval [4,4]
 The tap at point 5 can cover the interval [5,5]
 Opening Only the second tap will water the whole garden [0,5]
 Example 2:

 Input: n = 3, ranges = [0,0,0,0]
 Output: -1
 Explanation: Even if you activate all the four taps you cannot water the whole garden.
 Example 3:

 Input: n = 7, ranges = [1,2,1,0,2,1,0,1]
 Output: 3
 Example 4:

 Input: n = 8, ranges = [4,0,0,0,0,0,0,0,4]
 Output: 2
 Example 5:

 Input: n = 8, ranges = [4,0,0,0,4,0,0,0,4]
 Output: 1
  

 Constraints:

 1 <= n <= 10^4
 ranges.length == n + 1
 0 <= ranges[i] <= 100
 
 */
#include <vector>


using std::vector;


class MinimumNumberOfTapsToOpenToWaterGarden {
    
public:
    
    int doit_dp(int n, vector<int>& ranges) {
        
        vector<int> dp(n+1);
        
        for (int i = 0; i <= n; ++i) {
            if (ranges[i] == 0) continue;
            int left = std::max(0, i - ranges[i]);
            dp[left] = std::max(dp[left], i + ranges[i]);
        }
        
        // for (auto c: dp) cout << c << " ";
        // cout << endl;
        
        int res = 0, cur_end = 0, cur_far = 0;
        for (int i = 0; i <= n && cur_end < n; ++i) {
            cur_far = std::max(cur_far, dp[i]);
            if (i == cur_end) {
                if (cur_far == cur_end)
                    return -1;
                res++;
                cur_end = cur_far;
            }
        }
        
        return res;
    }
    
    /*
     
     Reduction
     If problem A can be reduced to problem B efficiently (polynomial time), solving A is no harder htan solving B.
     We write A =< B, which mean A is easier.
     We have a change (but not guaranteed) to find a better solution (lower time/space complexity) for A!
 
     
     1306 -> O(n) 1024 Video stitching and 45 Jump Game II

     
     1024. Video stitching
     
     clips[i] = {1 - ranges[i], i + ranges[i]}
     Reduction take O(n) time and space.
     
     Find minimum # of clops to cover [0, n]
     
     Approach: Greedy
     
     Sort clips by starting time, find the clip with maximum end time w.r.t clips[i].start <= last_end and extedn the tape to clips[i].end
     
     Time complexity: O(n * log(n))
     Space complexity: O(n) / O(1)
     
     */

    int doit_sort_greedy(int n, vector<int>& ranges) {
    
        vector<std::pair<int, int>> t;
        // O(n) reduction
        for (int i = 0; i <= n; ++i)
          t.emplace_back(std::max(0, i - ranges[i]), std::min(i + ranges[i], n));
        
        // 1024. Video Stiching
        sort(begin(t), end(t));
        int ans = 0;
        int i = 0;
        int l = 0;
        int e = 0;
        while (e < n) {
          // Extend to the right most w.r.t t[i].first <= l
          while (i <= n && t[i].first <= l)
            e = std::max(e, t[i++].second);
          if (l == e) return -1; // Can not extend
          l = e;
          ++ans;
        }
        return ans;
    }
    
    
    // O(n)
    int doit_greedy(int n, vector<int>& ranges) {
        
       vector<int> nums(ranges.size());
       
        for (int i = 0; i <= n; ++i) {
         int s = std::max(0, i - ranges[i]);
         nums[s] = std::max(nums[s], i + ranges[i]);
       }
        
       // 45. Jump Game II
       int steps = 0;
       int l = 0;
       int e = 0;
       for (int i = 0; i <= n; ++i) {
         if (i > e) return -1;
         if (i > l) { ++steps; l = e; }
         e = std::max(e, nums[i]);
       }
       return steps;
     }
};
