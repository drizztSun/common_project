/*
873. Length of Longest Fibonacci Subsequence

A sequence X1, X2, ..., Xn is Fibonacci-like if:

n >= 3
Xi + Xi+1 = Xi+2 for all i + 2 <= n
Given a strictly increasing array arr of positive integers forming a sequence, return the length of the longest Fibonacci-like subsequence of arr. If one does not exist, return 0.

A subsequence is derived from another sequence arr by deleting any number of elements (including none) from arr, without changing the order of the remaining elements. For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].

 

Example 1:

Input: arr = [1,2,3,4,5,6,7,8]
Output: 5
Explanation: The longest subsequence that is fibonacci-like: [1,2,3,5,8].
Example 2:

Input: arr = [1,3,7,11,12,14,18]
Output: 3
Explanation: The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or [7,11,18].
 

Constraints:

3 <= arr.length <= 1000
1 <= arr[i] < arr[i + 1] <= 109

*/


#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class LongestFibSubseq {

public:

    /*
        Approach 2: Dynamic Programming
        Intuition

        Think of two consecutive terms A[i], A[j] in a fibonacci-like subsequence as a single node (i, j), and the entire subsequence is a path between these consecutive nodes. For example, with the fibonacci-like subsequence (A[1] = 2, A[2] = 3, A[4] = 5, A[7] = 8, A[10] = 13), we have the path between nodes (1, 2) <-> (2, 4) <-> (4, 7) <-> (7, 10).

        The motivation for this is that two nodes (i, j) and (j, k) are connected if and only if A[i] + A[j] == A[k], and we needed this amount of information to know about this connection. Now we have a problem similar to Longest Increasing Subsequence.

        Algorithm

        Let longest[i, j] be the longest path ending in [i, j]. Then longest[j, k] = longest[i, j] + 1 if (i, j) and (j, k) are connected. Since i is uniquely determined as A.index(A[k] - A[j]), this is efficient: we check for each j < k what i is potentially, and update longest[j, k] accordingly.


        Complexity Analysis

        Time Complexity: O(N^2)O(N 
        2
        ), where NN is the length of A.

        Space Complexity: O(N \log M)O(NlogM), where MM is the largest element of A. We can show that the number of elements in a subsequence is bounded by O(\log \frac{M}{a})O(log 
        a
        M
        ​	
        ) where aa is the minimum element in the subsequence.

    
    */

    int doit_dp_best(vector<int>& arr) {
        
        int N = arr.size();
        unordered_map<int, int> index;
        for (int i = 0; i < N; i++) {
            index[arr[i]] = i;
        }

        unordered_map<int, int> longest;
        int ans = 0;
        for (int k = 0; k < N; k++) {

            for (int j = 0; j < k; j++) {

                if (arr[k] - arr[j] < arr[j] && index.count(arr[k]-arr[j]) > 0) {

                    int i = index[arr[k] - arr[j]];

                    longest[j*N+k] = longest[i*N+j] + 1;
                    ans = std::max(ans, longest[j*N+k]+2);
                }
            }

        }
        
        return ans > 2 ? ans : 0;
    }
};