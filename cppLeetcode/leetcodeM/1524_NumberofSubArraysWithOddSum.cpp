/*
1524. Number of Sub-arrays With Odd Sum

Given an array of integers arr. Return the number of sub-arrays with odd sum.

As the answer may grow large, the answer must be computed modulo 10^9 + 7.



Example 1:

Input: arr = [1,3,5]
Output: 4
Explanation: All sub-arrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
All sub-arrays sum are [1,4,9,3,8,5].
Odd sums are [1,9,3,5] so the answer is 4.
Example 2:

Input: arr = [2,4,6]
Output: 0
Explanation: All sub-arrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
All sub-arrays sum are [2,6,12,4,10,6].
All sub-arrays have even sum and the answer is 0.
Example 3:

Input: arr = [1,2,3,4,5,6,7]
Output: 16
Example 4:

Input: arr = [100,100,99,99]
Output: 4
Example 5:

Input: arr = [7]
Output: 1


Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 100

*/
#include <vector>


using std::vector;

class Solution {
public:

    /*
        dp[i][0] := # end with arr[i] has even sum
        dp[i][1] := # end with arr[i] has even sum

        if arr[i] is even:

        dp[i][0]=dp[i-1][0] + 1, dp[i][1]=dp[i-1][1]

        else:

        dp[i][1]=dp[i-1][0], dp[i][0]=dp[i-1][0] + 1

        ans = sum(dp[i][1])

        Time complexity: O(n)
        Space complexity: O(n) -> O(1)
    */
    int doit_dp(vector<int>& arr) {
        const int n = arr.size();
        constexpr int kMod = 1e9 + 7;
        // dp[i][0] # of subarrays ends with a[i-1] have even sums.
        // dp[i][1] # of subarrays ends with a[i-1] have odd sums.
        vector<vector<int>> dp(n + 1, vector<int>(2));
        long ans = 0;
        
        for (int i = 1; i <= n; ++i) {
            if (arr[i - 1] & 1) {
                dp[i][0] = dp[i - 1][1];
                dp[i][1] = dp[i - 1][0] + 1;
            } else {
                dp[i][0] = dp[i - 1][0] + 1;
                dp[i][1] = dp[i - 1][1];
            }
            ans += dp[i][1];
        }
        return ans % kMod;
    }

    int doit_dp_1(vector<int>& arr) {

        int odd = 0, even = 0;
        int ans = 0, hMod = 1e9 + 7;

        for (int i = 0; i < arr.size(); i++) {
            
            even++;
            if (arr[i] % 2) {
                long tmp = even; 
                even = odd; 
                odd = tmp;
            }
                
            ans = (ans + odd) % hMod;
        }

        return ans;
    }

    /*
        dp[i][0] := how many subarry[0:..] has odd number
        dp[i][1] := how many subarry[0:..] has even number

        so ans is gonna plus (current sum minus dp[i-1][even or odd] number)
    */
    int numOfSubarrays(vector<int>& arr) {
        
        int n = arr.size();
        vector<std::pair<int, int>> cache(n+1); //odd, even
        cache[0] = {0, 1};
        long sums = 0;
        int ans = 0, hMod = 1e9 + 7;
        
        for (int i = 1; i <= n; i++) {
            sums = (sums + arr[i-1]) % hMod;
            ans = (ans + ((sums%2 == 0) ? cache[i-1].first : cache[i-1].second)) % hMod;

            cache[i].first = cache[i-1].first + ((sums % 2 == 1) ? 1 : 0);
            cache[i].second = cache[i-1].second + ((sums % 2 == 0) ? 1 : 0);
        }
        
        return ans;
    }
};