/*
1477. Find Two Non-overlapping Sub-arrays Each With Target Sum

Given an array of integers arr and an integer target.

You have to find two non-overlapping sub-arrays of arr each with sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.

Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.

 

Example 1:

Input: arr = [3,2,2,4,3], target = 3
Output: 2
Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
Example 2:

Input: arr = [7,3,4,7], target = 7
Output: 2
Explanation: Although we have three non-overlapping sub-arrays of sum = 7 ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as the sum of their lengths is 2.
Example 3:

Input: arr = [4,3,2,6,2,3,4], target = 6
Output: -1
Explanation: We have only one sub-array of sum = 6.
Example 4:

Input: arr = [5,5,4,4,5], target = 3
Output: -1
Explanation: We cannot find a sub-array of sum = 3.
Example 5:

Input: arr = [3,1,1,1,5,1,2,1], target = 3
Output: 3
Explanation: Note that sub-arrays [1,2] and [2,1] cannot be an answer because they overlap.
 

Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 1000
1 <= target <= 10^8

*/
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;

class MinSumOfLengths {

public:

    int doit_slidingwindow_dp(vector<int>& arr, int target) {


        int i = 0, cur = 0;
        int n = arr.size();
        vector<int> minlength{n+1};
        int ans = INT_MAX;
        
        for (int j = 0; j < arr.size(); j++) {
            cur += arr[j];
            
            while (cur > target) {
                cur -= arr[i++];
            }
            
            if (cur != target) {
                minlength.push_back(minlength.back());
                continue;
            }
            
            ans = std::min(ans, j - i + 1 + minlength[i]);
            minlength.push_back(std::min(minlength.back(), j - i + 1));
        }
        
        return ans > arr.size() ? -1 : ans;   
    }

    int minSumOfLengths(vector<int>& arr, int target) {
        
        int n = arr.size();
        unordered_map<int, int>hm;
        hm[0] = -1;
        int sum = 0;
        
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            hm[sum] = i;
        }
        
        sum = 0;
        int msize = INT_MAX, res = INT_MAX;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            
            if (hm.find(sum-target) != hm.end())
                msize = std::min(msize, i-hm[sum-target]);
            
            if (hm.find(sum+target) != hm.end() && msize != INT_MAX)
                res = std::min(res, msize + hm[sum+target]-i);
        }
        
        return res == INT_MAX ? -1 : res;
    }

};