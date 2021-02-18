/*
918. Maximum Sum Circular Subarray

Given a circular array C of integers represented by A, find the maximum possible sum of a non-empty subarray of C.

Here, a circular array means the end of the array connects to the beginning of the array.  (Formally, C[i] = A[i] when 0 <= i < A.length, and C[i+A.length] = C[i] when i >= 0.)

Also, a subarray may only include each element of the fixed buffer A at most once.  (Formally, for a subarray C[i], C[i+1], ..., C[j], there does not exist i <= k1, k2 <= j with k1 % A.length = k2 % A.length.)

 

Example 1:

Input: [1,-2,3,-2]
Output: 3
Explanation: Subarray [3] has maximum sum 3
Example 2:

Input: [5,-3,5]
Output: 10
Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10
Example 3:

Input: [3,-1,2,-1]
Output: 4
Explanation: Subarray [2,-1,3] has maximum sum 2 + (-1) + 3 = 4
Example 4:

Input: [3,-2,2,-3]
Output: 3
Explanation: Subarray [3] and [3,-2,2] both have maximum sum 3
Example 5:

Input: [-2,-3,-1]
Output: -1
Explanation: Subarray [-1] has maximum sum -1
 

Note:

-30000 <= A[i] <= 30000
1 <= A.length <= 30000
*/ 
#include <vector>

using std::vector;


class MaxSubarraySumCircular {

public:

    int doit_(vector<int>& A) {

        int minv = INT_MAX, maxv = INT_MIN;
        int curmax = 0, curmin = 0;
        int total = 0;
        
        for (auto a: A) {

            curmax = std::max(curmax + a, a);
            maxv = std::max(maxv, curmax);

            curmin = std::min(curmin + a, a);
            minv = std::min(minv, curmin);

            total += a;
        }

        return maxv < 0 ? maxv : std::max(maxv, total - minv);
    }


    int doit_slidingwindow(vector<int>& A) {
        
        int ans = INT_MIN, cursum = 0;
        for (auto c : A) {
            cursum = c + std::max(cursum, 0);
            ans = std::max(ans, cursum);
        }
        
        int N = A.size();
        vector<int> rightsum(N);
        rightsum[N-1] = A[N-1];
        cursum = A[N-1];
        for (int i = N-2; i > -1; i--) {
            cursum += A[i];
            rightsum[i] = std::max(cursum, rightsum[i+1]);
        }
        
        int leftsum = 0;
        for (int i = 0; i < N-2; i++) {
            leftsum += A[i];
            ans = std::max(ans, leftsum + rightsum[i+1]);
        }
        
        return ans;
    }

    /*
        There are only 2 cases where a subarray completely lie between 2 ends i.e
        s[i...j] where both i and j are between 0 to n-1 and [i <= j]
        other case is where we take some part of prefix and some part of suffix and add them which is handled in second loop
    */
    int doit_(vector<int>& a){
        int i, n = a.size();
        int s = 0, mx = INT_MIN, mn = 0, pref[n], suff[n], mxp[n];
        for(i=0;i<n;i++){    
            s += a[i];
            pref[i] = s;
            if(i==0)
                mxp[i] = std::max(0, s);
            else
                mxp[i] = std::max({mxp[i-1], s});
            mx = std::max(mx, s - mn);
            mn = std::min(s, mn);
        }
        
        s = 0;
        for(i = n-1; i > 1; i--){
            s += a[i];
            suff[i] = s;
            mx = std::max(mx, suff[i] + mxp[i-1]);
        }
        
        return mx;
        
    }
};