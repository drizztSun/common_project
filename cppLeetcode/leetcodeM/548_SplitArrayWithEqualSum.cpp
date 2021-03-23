/*
548. Split Array with Equal Sum


Given an array with n integers, you need to find if there are triplets (i, j, k) which satisfies following conditions:

0 < i, i + 1 < j, j + 1 < k < n - 1
Sum of subarrays (0, i - 1), (i + 1, j - 1), (j + 1, k - 1) and (k + 1, n - 1) should be equal.
where we define that subarray (L, R) represents a slice of the original array starting from the element indexed L to the element indexed R.
Example:
Input: [1,2,1,2,1,2,1]
Output: True
Explanation:
    i = 1, j = 3, k = 5. 
    sum(0, i - 1) = sum(0, 0) = 1
    sum(i + 1, j - 1) = sum(2, 2) = 1
    sum(j + 1, k - 1) = sum(4, 4) = 1
    sum(k + 1, n - 1) = sum(6, 6) = 1
Note:
1 <= n <= 2000.
Elements in the given array will be in range [-1,000,000, 1,000,000].

*/
#include <vector>
#include <unordered_set>

using std::unordered_set;
using std::vector;


class SplitArray {

public:

    /*
        Approach #5 Using Cumulative Sum and HashSet [Accepted]
        Algorithm

        In this approach, firstly we form a cumulative sum array sumsum, where sum[i]sum[i] stores the cumulative sum of the array numsnums upto the i-th index. 
        Then, we start by traversing over the possible positions for the middle cut formed by jj. For every jj, firstly, we find all the left cut's positions, ii, 
        that lead to equalizing the sum of the first and the second part (i.e. sum[i-1] = sum [j-1] - sum[i]sum[i−1]=sum[j−1]−sum[i]) and store such sums in the setset (a new HashSet is formed for every jj chosen). 
        Thus, the presence of a sum in setset implies that such a sum is possible for having equal sum of the first and second part for the current position of the middle cut(jj).

        Then, we go for the right cut and find the position of the right cut that leads to equal sum of the third and the fourth part (sum[n-1]-sum[k]=sum[k-1] - sum[j]sum[n−1]−sum[k]=sum[k−1]−sum[j]), 
        for the same middle cut as chosen earlier. We also, look if the same sum exists in the setset. If so, such a triplet (i, j, k)(i,j,k) exists which satisfies the required criteria, otherwise not.

        Look at the animation below for a visual representation of the process:

        Complexity Analysis

        Time complexity : O(n^2). One outer loop and two inner loops are used.
        Space complexity : O(n). HashSet size can go upto n.
    */
    bool doit_presums(vector<int>& nums) {
        
        int N = nums.size();
        vector<int> presums(N);
        for (int i = 0; i < N; i++)
            presums[i] = nums[i] + (i > 0 ? presums[i-1] : 0);

        for (int i = 3; i < N-3; i++) {

            unordered_set<int> buf;
            for (int j = 1; j < i; j++) {
                if (presums[j-1] == presums[i-1] - presums[j]) {
                    buf.insert(presums[j-1]);
                }
            }

            for (int k = i+2; k < N-1; k++) {
                if ((presums[k-1] - presums[i] == presums[N-1] - presums[k]) && buf.count(presums[k-1] - presums[i])) {
                    return true;
                }
            }
        }

        return false;
    }
};