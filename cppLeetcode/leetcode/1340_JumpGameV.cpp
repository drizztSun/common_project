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

#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>

using std::vector;


class JumpGameV {

    /*
        1340.Jump-Game-V
        解法1：DP o(NlogN)
        我们从最高点i开始看，它往左右两边范围d内的柱子j都可以到达。如果我们定义dp[k]为到达位置k所能经过的最多的柱子数目，显然我们有机会更新dp[j] = max(dp[j], dp[i]+1)。

        我们从高到低顺次处理完所有的柱子，最终答案就是所有dp[i]里面的最大值。

        注意，我们在向左（或者向右）遍历j的时候，如果发现arr[j]>=arr[i]，那么这个方向的搜索就可以break了。

        解法1：DFS+Memo o(N)
        以上的解法最大的缺点就是需要排序。这也是DP用法的限制：你必须提前计算出所有的前效状态才能进行状态传递。

        事实上，我们可以用递归的思想来解决这个问题。我们只需要顺次解决dp(i)。如果发现dp(i)的某个前效状态dp(j)暂时不知道，那么我们就一路追查过去先计算dp(j)然后存储下来，再返回来计算dp(i)就可以了。
    */
    int maxJumps_dp(vector<int>& arr, int d) 
    {
        int n = arr.size();
        vector<int>dp(n,1);

        vector<std::pair<int,int>>p;
        for (int i=0; i<n; i++)
            p.push_back({arr[i],i});

        std::sort(p.begin(), p.end());
        reverse(p.begin(), p.end());

        for (auto [height, idx]: p)
        {            
            for (int i=idx+1; i<=std::min(n-1,idx+d); i++)
            {
                if (arr[i] >= arr[idx]) break;                                
                dp[i] = std::max(dp[i], dp[idx]+1);
            }            
            for (int i=idx-1; i>=std::max(0, idx-d); i--)
            {
                if (arr[i] >= arr[idx]) break;                                
                dp[i] = std::max(dp[i], dp[idx]+1);
            }
        }

        int ret = 0;
        for (int i=0; i<n; i++)
            ret = std::max(ret, dp[i]);
        return ret;
    }


    int dp[1001];
    int d;

    int maxJumps(vector<int>& arr, int d) 
    {
        this->d = d;

        int ret = 0;
        for (int i=0; i<arr.size(); i++)
        {
            dfs(i, arr);
            ret = std::max(ret, dp[i]);            
        }
        return ret;
    }

    int dfs(int i, vector<int>&arr)
    {        
        if (dp[i]!=0) return dp[i];

        int ret = 1;

        for (int k=1; k<=d; k++)
        {
            if (i+k>=arr.size()) break;
            if (arr[i+k]>=arr[i]) break;
            ret = std::max(ret, dfs(i+k, arr)+1);
        }
        for (int k=1; k<=d; k++)
        {
            if (i-k<0) break;
            if (arr[i-k]>=arr[i]) break;
            ret = std::max(ret, dfs(i-k, arr)+1);
        }
        dp[i] = ret;

        return dp[i];
    }

    
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
            
            if (dp[i] != 0) return dp[i];
            
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
        
        return *std::max_element(begin(dp), end(dp));
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
