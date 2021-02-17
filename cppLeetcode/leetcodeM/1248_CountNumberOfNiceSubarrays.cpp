/*
1248. Count Number of Nice Subarrays


Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.

 

Example 1:

Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].
Example 2:

Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There is no odd numbers in the array.
Example 3:

Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16
 

Constraints:

1 <= nums.length <= 50000
1 <= nums[i] <= 10^5
1 <= k <= nums.length

*/
#include <vector>

using std::vector;

class NumberOfSubarrays {

public:

    /*
        Solution 1: atMost
        Have you read this? 992. Subarrays with K Different Integers
        Exactly K times = at most K times - at most K - 1 times


        Complexity
        Time O(N) for one pass
        Space O(1)
    */
    int doit_slidingwindow(vector<int>& A, int k) {

        std::fucntion<int(int)> atMost = [&](int k) {
            int res = 0, i = 0, n = A.size();
            for (int j = 0; j < n; j++) {
                k -= A[j] % 2;
                while (k < 0)
                    k += A[i++] % 2;
                res += j - i + 1;
            }
            return res;
        };

        return atMost(A, k) - atMost(A, k - 1);
    }

    /*
        Solution II: One pass
        Actually it's same as three pointers.
        Though we use count to count the number of even numebers.
        Insprired by @yannlecun.

        Time O(N) for one pass
        Space O(1)
    */
    int doit_slidingwindow_1(vector<int>& A, int k) {
        int res = 0, i = 0, count = 0, n = A.size();
        
        for (int j = 0; j < n; j++) {
        
            if (A[j] & 1)
                --k, count = 0;

            while (k == 0)
                k += A[i++] & 1, ++count;
        
            res += count;
        }
        
        return res;
    }
};