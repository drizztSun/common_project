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
#include <array>
#include <algorithm>

using std::array;
using std::vector;


class MinimumNumberOfTapsToOpenToWaterGarden {
    
public:

    /*
        1326.Minimum-Number-of-Taps-to-Open-to-Water-a-Garden
        此题的本质就是寻找数目最少的、互相重叠区间，使得最终能够覆盖[0,n]。这和1024.Video-Stitching非常类似。

        我们将所有的区间按照左端点排列，如果左端点并列，那么优先选择范围大的区间。假设我们当前处理区间i，记作[a,b]，那么我们会查看i后面的、与i有交叠的区间，如果有多个，我们一定会从里面挑选右端点最远的那一个（记作区间j），因为j既能与i重叠、又能覆盖最远的地方，可以减少最终所选区间的数目。然后我们再考察区间j，重复之前的操作。

        注意无解的情况有三种：1. 最右端的位置还没有推进到n，但是区间i之后已经没有任何其他区间能与之重叠；2. 如果考察完所有的区间，最右端的位置仍然无法推进到n，3. 第一个区间的左端点在0后面。
    */
    int minTaps(int n, vector<int>& ranges) 
    {
        vector<array<int,2>>intervals(n+1);
        for (int i=0; i<=n; i++)
            intervals[i] = {i-ranges[i], i+ranges[i]};

        sort(intervals.begin(), intervals.end(), [](array<int,2>&a, array<int,2>&b){
            if (a[0]!=b[0])
                return a[0] < b[0];
            else
                return a[1] > b[1];
        });

        if (intervals[0][0]>0) return -1;

        int i = 0;
        int far = 0;
        int count = 0;
        while (i < intervals.size())
        {                        
            count += 1;
            int nextFar = far;
            while (i < intervals.size() && intervals[i][0]<=far)
            {
                nextFar = std::max(nextFar, intervals[i][1]);
                i++;
            }

            if (nextFar >= n)
                return count;
            
            if (nextFar == far)
                return -1;
            
            far = nextFar;
        }

        return -1;
    }

    int doit_best(int n, vector<int>& nums) {

        vector<int> maxRight(n+1); //maxRight[Left]=the farest index Left can reach
        
        // scan each tap, update the farest index each Left can reach.
        for (int i =0;i<=n;i++){
            int L = std::max(0,i-nums[i]);
            int R = std::min(n,i+nums[i]);
            maxRight[L] = std::max(maxRight[L],R);
        }   

        int next_right_most = maxRight[0];// the rightmost index which is accessible by one more tap
        int cur_right_most = maxRight[0];// cur right most accessible index
        int taps = 1;

        for(int i = 1; i <= n; i++){
            // i is the Left to scan.
            // for each i, we find the next right most index to cover.
            if(i > next_right_most){
               //still can't find the next connected range
               //this implies all indices in[0,next_right_most] cannot reach the rest part of the garden.
               //because if they can, the next_right_most should have been updated to larger.(contradicted)
               return -1;
            }
            
            if (i > cur_right_most){
                //this implies Left of current scan is disconnected from previous right_most index.
                //It's time to add an additional tap to cover previous indices
                taps++;
                cur_right_most = next_right_most;
            }
            
            //only update when i(which is the Left)<cur_right_most
            //because only in this case, the tap is overlapped with the previous tap
            next_right_most = std::max(next_right_most, maxRight[i]); //greedy. find the rightmost index
        }
        return taps; 
    }

    // O(n^2)
    int doit_dp(int n, vector<int>& ranges) {
        
        vector<int> dp(n+1);
        
        for (int i = 0; i <= n; ++i) {

            if (ranges[i] == 0) continue;
            int left = std::max(0, i - ranges[i]);
            dp[left] = std::max(dp[left], i + ranges[i]);
        }
        
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

    int doit_greedy_best(int n, vector<int>& ranges) {

        vector<vector<int>> intervals;
        
        for (int i = 0; i < ranges.size(); i++)
            intervals.push_back({std::max(0, i-ranges[i]), i + ranges[i]});
        
        std::sort(begin(intervals), end(intervals), [](const auto& a, const auto& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]); 
        });
        
        int i = 0, end = 0, ans = 0;
        
        while (i < intervals.size()) {
            
            int far = end;
            ans++;
            while (i <intervals.size() && intervals[i][0] <= end) {
                far = std::max(far, intervals[i][1]);
                i++;
            }
            
            if (far == end) return -1;
            
            if (far >= n) return ans;
            
            end = far;
        }
        
        return -1;
    }

    // O(n)
    int doit_greedy_best(int n, vector<int>& ranges) {
        
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
