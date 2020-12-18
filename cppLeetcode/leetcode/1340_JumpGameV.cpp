/*
 1340. Jump Game V
 
 Given an array of integers arr and an integer d. In one step you can jump from index i to index:

 i + x where: i + x < arr.length and 0 < x <= d.
 i - x where: i - x >= 0 and 0 < x <= d.
 In addition, you can only jump from index i to index j if arr[i] > arr[j] and arr[i] > arr[k] for all indices k between i and j (More formally min(i, j) < k < max(i, j)).

 You can choose any index of the array and start jumping. Return the maximum number of indices you can visit.

 Notice that you can not jump outside of the array at any time.

  

 Example 1:


 Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
 Output: 4
 Explanation: You can start at index 10. You can jump 10 --> 8 --> 6 --> 7 as shown.
 Note that if you start at index 6 you can only jump to index 7. You cannot jump to index 5 because 13 > 9. You cannot jump to index 4 because index 5 is between index 4 and 6 and 13 > 9.
 Similarly You cannot jump from index 3 to index 2 or index 1.
 Example 2:

 Input: arr = [3,3,3,3,3], d = 3
 Output: 1
 Explanation: You can start at any index. You always cannot jump to any index.
 Example 3:

 Input: arr = [7,6,5,4,3,2,1], d = 1
 Output: 7
 Explanation: Start at index 0. You can visit all the indicies.
 Example 4:

 Input: arr = [7,1,7,1,7,1], d = 2
 Output: 2
 Example 5:

 Input: arr = [66], d = 1
 Output: 1
  

 Constraints:

 1 <= arr.length <= 1000
 1 <= arr[i] <= 10^5
 1 <= d <= arr.length
 
 */

#include <stdio.h>
#include <vector>


using std::vector;
using std::max;


class JumpGameV {
    
public:
    
    
    /*
     Program => Find the logest path in a DAG (directed but no circle).
     Key observation: you can only jump to lower bars!
     
     Approach 1: Recursion w/ memorization
     
     def dp(i) := max # of bars you can reach i start from i
     
     Order desn't matter
     
     dp(i) = 1 or max(dp(j) + 1), if i can jimp tp j.
     
     ans = max(dp(i))
     
     Time complexity: O(n*d)
     
     Space complexity: O(n)
     
     */
    int doit_dp_recursive_Topdown(vector<int>& arr, int d) {

        int n = arr.size();
        vector<int> dp(n);

        std::function<int(int)> search = [&](int i) {
            
            int n = arr.size();
            vector<int> dp(n);
            
            if (dp[i] != 0)
                return dp[i];
            
            int ans = 1;
            
            for (int j = i + 1; j < std::min(i + d + 1, n) && arr[i] > arr[j]; j++)
                ans = std::max(ans, search(j) + 1);
            
            for (int j = i - 1; j >= std::max(0, i-d) && arr[i] > arr[j]; j--)
                ans = std::max(ans, search(j) + 1);
            
            return dp[i] = ans;
        };
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = std::max(ans, search(i));
        }
        return ans;
    }
    
    /*
    Approach 2: DP
     
     dp[i] := max # of bars you can reach if start from i
     dp(i) = 1 or max(dp(j) + 1), if i can jump to j.
     ans = max(dp)
     
     # if we fill DP in order
     dp[5] = max(dp[6] + 1)
     # wrong, dp[6] has not been filled.
     
     
     order matters for DP!!!
     We can stil use DP, but need to fill the array in the order of bar height. E.g solve lower bars first
     Did a topological sorting implicitly.
     
     Time complexity: O(n*log(n) + n*d)
     Space complexity: O(n)
     */
    
    int doit_dp_Bottomup(vector<int>& arr, int d) {
        
        const int N = arr.size();
        vector<std::pair<int, int>> heights;
        for (int i = 0; i < N; i++) {
            heights.push_back({arr[i], i});
        }
        
        std::sort(begin(heights), end(heights));
        vector<int> dp(N, 1);
        
        for (auto [h, i] : heights) {
            
            for (int j = i+1; j < std::min(N, i + d + 1) && arr[i] > arr[j]; j++)
                dp[i] = std::max(dp[i], dp[j] + 1);
            
            for (int j = i-1; j >= std::max(0, i - d) && arr[i] > arr[j]; j--)
                dp[i] = std::max(dp[i], dp[j] + 1);
        }
        
        
        return *max_element(begin(dp), end(dp));
    }
    
    
    
    struct A {
        int h, i, j = 1;
    };
    
    int maxJumps(vector<int>& arr, int d) {
        vector<A> V;
        int ret = 1, i, n = arr.size(), j, h, vsiz, k, l;
        
        for (i = 0; i < n; ++i) {
            h = arr[i];
            vsiz = V.size();
            
            if (V.empty() || V[vsiz-1].h >= h) {
                V.push_back({h, i, 1});
            } else {
                j = 1;
                while (!V.empty() && V[vsiz-1].h < h) {
                    for (k = vsiz-2; k >= 0 && V[k].h == V[vsiz-1].h; --k);
                    // populate V[l] to left and right
                    for (l = vsiz-1; l > k; --l) {
                        // populate left
                        if (k >= 0 && V[l].i - V[k].i <= d)
                            V[k].j = max(V[k].j, V[l].j + 1);
                        
                        // populate right
                        if (i - V[l].i <= d)
                            j = max(j, V[l].j + 1);
                        
                        // retire
                        ret = max(ret, V[l].j);
                        V.pop_back();
                    }
                    
                    vsiz = V.size();
                }
                
                V.push_back({h, i, j});
            }
        }
        
        // retire the rest
        while (!V.empty()) {
            vsiz = V.size();

            for (k = vsiz-2; k >= 0 && V[k].h == V[vsiz-1].h; --k);
            
            // populate V[l] to left and right
            for (l = vsiz-1; l > k; --l) {
                // populate left
                if (k >= 0 && V[l].i - V[k].i <= d)
                    V[k].j = max(V[k].j, V[l].j + 1);
                        
                // retire
                ret = max(ret, V[l].j);
                V.pop_back();
            }
        }
        
        return ret;
    }
    
};
