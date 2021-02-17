/*
1498. Number of Subsequences That Satisfy the Given Sum Condition

Given an array of integers nums and an integer target.

Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum element on it is less or equal to target. Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [3,5,6,7], target = 9
Output: 4
Explanation: There are 4 subsequences that satisfy the condition.
[3] -> Min value + max value <= target (3 + 3 <= 9)
[3,5] -> (3 + 5 <= 9)
[3,5,6] -> (3 + 6 <= 9)
[3,6] -> (3 + 6 <= 9)
Example 2:

Input: nums = [3,3,6,8], target = 10
Output: 6
Explanation: There are 6 subsequences that satisfy the condition. (nums can have repeated numbers).
[3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]
Example 3:

Input: nums = [2,3,3,4,6,7], target = 12
Output: 61
Explanation: There are 63 non-empty subsequences, two of them don't satisfy the condition ([6,7], [7]).
Number of valid subsequences (63 - 2 = 61).
Example 4:

Input: nums = [5,2,4,1,7,6,8], target = 16
Output: 127
Explanation: All non-empty subset satisfy the condition (2^7 - 1) = 127
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^6
1 <= target <= 10^6

*/
#include <vector>
#include <algorithm>

using std::vector;

class NumberSequenceThatSatisfy {

public:

    /*
        Intuition
        Almost same as problem two sum.
        If we want to know the count of subarray in sorted array A,
        then it's exactly the same.
        Make sure you can do two sum before continue.


        Explanation
        Sort input A first,
        For each A[i], find out the maximum A[j]
        that A[i] + A[j] <= target.

        For each elements in the subarray A[i+1] ~ A[j],
        we can pick or not pick,
        so there are 2 ^ (j - i) subsequences in total.
        So we can update res = (res + 2 ^ (j - i)) % mod.

        We don't care the original elements order,
        we only want to know the count of sub sequence.
        So we can sort the original A, and the result won't change.


        Complexity
        Time O(NlogN)
        Space O(1) for python
        (O(N) space for java and c++ can be save anyway)
    */
    int doit_sort(vector<int>& A, int target) {
        
        std::sort(A.begin(), A.end());
        int res = 0, n = A.size(), l = 0, r = n - 1, mod = 1e9 + 7;
        vector<int> pows(n, 1);
        
        for (int i = 1 ; i < n ; ++i)
            pows[i] = pows[i - 1] * 2 % mod;
        
        while (l <= r) {
            if (A[l] + A[r] > target) {
                r--;
            } else {
                res = (res + pows[r - l++]) % mod;
            }
        }
        
        return res;    
    }
};