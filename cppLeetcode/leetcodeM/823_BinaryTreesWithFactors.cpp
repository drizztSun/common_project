/*
823. Binary Trees With Factors

Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.

We make a binary tree using these integers, and each number may be used for any number of times. Each non-leaf node's value should be equal to the product of the values of its children.

Return the number of binary trees we can make. The answer may be too large so return the answer modulo 109 + 7.

 

Example 1:

Input: arr = [2,4]
Output: 3
Explanation: We can make these trees: [2], [4], [4, 2, 2]
Example 2:

Input: arr = [2,4,5,10]
Output: 7
Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].
 

Constraints:

1 <= arr.length <= 1000
2 <= arr[i] <= 109
All the values of arr are unique.

*/

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using std::vector;
using std::unordered_set;
using std::unordered_map;

class FactoredBinaryTrees {

    int numFactoredBinaryTrees(vector<int>& A)
    {
        sort(A.begin(),A.end());
        
        int N=A.size();
        vector<long long>dp(N,1);
        long long M=pow(10,9)+7;
        unordered_map<int,long long>Map;
        
        for (int i=0; i<A.size(); i++)
            Map[A[i]]=i;
        
        for (int i=0; i<A.size(); i++)
        {
            for (int j=0; j<=i; j++)
            {                                
                if (A[i]%A[j]==0 && Map.find(A[i]/A[j])!=Map.end())
                {                    
                    int idx = Map[A[i]/A[j]];
                    dp[i]+=(dp[idx]*dp[j])%M;
                }
            }
            if (i>0 && A[0]==1)
                dp[i]+=2;
        }
        
        long long sum=0;
        for (int i=0; i<A.size(); i++)
            sum = (sum+dp[i])%M;
        
        return sum%M;
    }


public:

    /*
        Approach #1: Dynamic Programming [Accepted]
        Intuition

        For any valid tree, the largest value v, in that tree, must be the root. So, let's say that dp(v) is the number of ways to make a tree with root node v.

        If the root node of the tree (with value v) has children with values x and y (where x * y == v must be true), then there are dp(x) * dp(y) ways to make this tree.

        Each unique value in A is a valid root value for at least one tree - a tree containing just that node.

        To get the total number of valid trees, we should calculate how many valid trees there are with each possible root value, and then add them all together.

        Algorithm

        Let dp[i] be the number of ways to have a root node with value A[i].

        Since in the above example we always have x < v and y < v, we can calculate the values of dp[i] in increasing order using dynamic programming.

        For some root value A[i], let's try to find candidates for the children with values A[j] and A[i] / A[j] (so that evidently A[j] * (A[i] / A[j]) = A[i]). 
        To do this quickly, we will need index which looks up this value: if A[k] = A[i] / A[j], then index[A[i] / A[j]] = k.

        After, we'll add all possible dp[j] * dp[k] (with j < i, k < i) to our answer dp[i]. In our Java implementation, we carefully used long so avoid overflow issues.


        Complexity Analysis

        Time Complexity: O(N^2), where NN is the length of A. This comes from the two for-loops iterating i and j.

        Space Complexity: O(N), the space used by dp and index.    
    */
    int doit_dp(vector<int>& arr) {

        using ll = long long;
        int n = arr.size();
        std::sort(begin(arr), end(arr));
        int hmod = 1e9 + 7;

        vector<ll> dp(n, 1);
        unordered_map<int, int> visited; 

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < i; j++) {

                if (arr[i] % arr[j] == 0 && visited.count(arr[i] / arr[j]) > 0) {

                    int other = arr[i]/arr[j];

                    dp[i] = (dp[i] + dp[j] * dp[visited[other]]) % hmod;
                }
            }
            
            visited.emplace(arr[i], i);
        }

        ll total = 0;
        for (auto c: dp) {
            total = (total + c) % hmod;
        }
        
        return total;
    }
};