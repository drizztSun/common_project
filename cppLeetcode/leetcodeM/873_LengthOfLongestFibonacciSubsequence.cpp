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

    int doit_(vector<int>& arr) {
        
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

                    longest[k*N+j] = longest[j*N+i] + 1;
                    ans = std::max(ans, longest[k*N+j]);
                }
            }

        }
        
        return ans > 2 ? 0 : ans;
    }
};