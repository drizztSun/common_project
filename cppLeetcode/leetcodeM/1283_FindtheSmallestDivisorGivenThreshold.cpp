/*
1283. Find the Smallest Divisor Given a Threshold

Given an array of integers nums and an integer threshold, we will choose a positive integer divisor, divide all the array by it, and sum the division's result. Find the smallest divisor such that the result mentioned above is less than or equal to threshold.

Each result of the division is rounded to the nearest integer greater than or equal to that element. (For example: 7/3 = 3 and 10/2 = 5).

It is guaranteed that there will be an answer.

 

Example 1:

Input: nums = [1,2,5,9], threshold = 6
Output: 5
Explanation: We can get a sum to 17 (1+2+5+9) if the divisor is 1. 
If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5 the sum will be 5 (1+1+1+2). 
Example 2:

Input: nums = [44,22,33,11,1], threshold = 5
Output: 44
Example 3:

Input: nums = [21212,10101,12121], threshold = 1000000
Output: 1
Example 4:

Input: nums = [2,3,5,7,11], threshold = 11
Output: 3
 

Constraints:

1 <= nums.length <= 5 * 10^4
1 <= nums[i] <= 10^6
nums.length <= threshold <= 10^6

*/
#include <vector>
#include <numeric>
#include <algorithm>


using std::vector;


class SmallestDivisor {

    /*
                1283.Find-the-Smallest-Divisor-Given-a-Threshold
        典型的二分搜值。猜测一个divisor的答案k，如果所有nums[i]/k的商的和大于threshold，那么除数太小，说明需要往大猜；否则需要往小猜。
    */
    int smallestDivisor(vector<int>& nums, int threshold) 
    {
        int left = 1, right = INT_MAX;
        while (left < right)
        {
            int mid = left+(right-left)/2;
            if (isOK(mid, nums, threshold))
                right = mid;
            else
                left = mid + 1;
        }
        return left;        
    }
    
    bool isOK(int x, vector<int>& nums, int threshold)
    {
        int sum = 0;
        for (auto a: nums)
        {
            if (a%x==0)
                sum+=a/x;
            else
                sum+=a/x+1;
        }
        return sum<=threshold;
    }

    /*
        Explanation
        Binary search the result.
        If the sum > threshold, the divisor is too small.
        If the sum <= threshold, the divisor is big enough.

        Complexity
        Time O(NlogM), where M = max(A)
        Space O(1)
    */
    int binary_search(vector<int>& A, int threshold) {
        int left = 1, right = 1e6, m, sum;
        while (left < right) {
            m = (left + right) / 2, sum = 0;
            for (int i : A)
                sum += (i + m - 1) / m;
            if (sum > threshold)
                left = m + 1;
            else
                right = m;
        }
        return left;
    }

public:

    int doit_binary_search(vector<int>& nums, int threshold) {
        
        int left = 1, right = *max_element(begin(nums), end(nums));
        
        while (left <= right) {
            
            int mid = left + (right - left) / 2;
            
            int total = 0;
            for (auto c : nums)
                total += c / mid + (c % mid == 0 ? 0 : 1);
            
            if (total > threshold)
                left = mid + 1;
            else 
                right = mid - 1;
        }
        
        return left;
    }
};