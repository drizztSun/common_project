/*
1703. Minimum Adjacent Swaps for K Consecutive Ones

You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.

Return the minimum number of moves required so that nums has k consecutive 1's.

 

Example 1:

Input: nums = [1,0,0,1,0,1], k = 2
Output: 1
Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
Example 2:

Input: nums = [1,0,0,0,0,0,1,1], k = 3
Output: 5
Explanation: In 5 moves, the leftmost 1 can be shifted right until nums = [0,0,0,0,0,1,1,1].
Example 3:

Input: nums = [1,1,0,1], k = 2
Output: 0
Explanation: nums already has 2 consecutive 1's.
 

Constraints:

1 <= nums.length <= 105
nums[i] is 0 or 1.
1 <= k <= sum(nums)




*/
#include <vector>
#include <algorithm>
using std::vector;

class MinimumAdjacentSwapKConsecutiveOnes {

public:

    /*
    Short Explanation
    Find all index of nums[i] if nums[i] == 1.
    Now the problem changes to find k consecute element in A, that has minimum distance to their median sequence.
    To solve this, we need to use the prefix sum of A, which is B in this solution.

    Complexity
    Time O(n)
    Space O(n)
    */
    int doit_slidingwindows(vector<int>& nums, int k) {

        vector<long> pos;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1)
                pos.push_back(i);
        }

        long n = pos.size(), res = 2e9;
        vector<long> B(1);
        for (int i = 0; i < n; i++) {
            B.push_back(B[i] + pos[i]);
        }

        /*
        B[i + k] - B[k / 2 + i] - B[(k + 1) / 2 + i] + B[i])
        (B[i + k] - B[(k + 1) / 2 + i]) - (B[k / 2 + i] - B[i]);

        example indices (A):
        [0 3 5 6 7 9 10]
        mid = 6
        sum before mid => (6 - 6 - 0) + (6 - 3 - 1) + (6 - 5 - 2) + (6 - 0 - 3)
        => 6 * 4 - (0 + 3 + 5 + 6) - (0 + 1 + 2 + 3)

        sum after mid => (6 - 6 - 0) + (7 - 6 - 1) + (9 - 6 - 2) + (10 - 6 - 3)
        => (6 + 7 + 9 + 10) - 6 * 4 - (0 + 1 + 2 + 3)

        before + after => (6 + 7 + 9 + 10) - (0 + 3 + 5 + 6) - 2 * (1+2+3)
        => A[3]->A[6] - A[0]->A[3] - 2 * (3)(3+1) / 2
        => (B[7] - B[3]) - (B[4] - B[0]) - (k//2)*((k+1)//2)
        */

        for (int i = 0; i < n-k+1; i++) {
            
            // B[i + k] - B[k / 2 + i] - B[(k + 1) / 2 + i] + B[i])
            res = std::min(res, B[i+k] - B[k/2 + i] - B[(k+1)/2 + i] + B[i]);
        }

        res -= (k / 2) * ((k+1/2));
        return res;
    }
};