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

    /*
        1498.Number-of-Subsequences-That-Satisfy-the-Given-Sum-Condition
        因为这题考察的是subsequence，我们选取的元素其实和顺序无关，所以我们可以将nums排个序。好处是任何subsquece的最小值都在前面，最大值在后面。

        我们遍历每个元素nums[i]，假想它是subsequence的最小值，那么我们可以容易确定可选的最大值nums[j]：只要从j=n-1往左移，找到第一个满足nums[i]+nums[j]<=target的元素j。
        确定了最大值和最小值，此时区间[i+1:j]内部的所有元素都可选可不选。所以我们的结论是：如果最小值是nums[i]，那么合法的子序列数目是2^(j-i).

        我们考察下一个i的时候，j必然只能在之前的位置继续往左移。所以这是一个双指针模式，用o(N)时间就可以搜寻所有的{i,j}配对。对于每对{i,j}我们都将子序列的数目累加起来。

        此外，我们还预处理得到一个数组power[k]来存储所有2^k % M的值供使用。
    */
    int numSubseq(vector<int>& nums, int target) 
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        long M = 1e9+7;
        long ret = 0;
        vector<long>power(n+1);

        power[0] = 1;
        for (int i=1; i<=n; i++)
            power[i] = power[i-1] * 2 % M;

        int j = n-1;    
        for (int i=0; i<n; i++)
        {            
            while (j>=0 && nums[i]+nums[j] > target)
                j--;
            if (j<i) break;                        
            ret = (ret + power[j-i]) % M;
        }
        return ret;
    }


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