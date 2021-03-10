/*
1060. Missing Element in Sorted Array

Given a sorted array A of unique numbers, find the K-th missing number starting from the leftmost number of the array.

 

Example 1:

Input: A = [4,7,9,10], K = 1
Output: 5
Explanation: 
The first missing number is 5.
Example 2:

Input: A = [4,7,9,10], K = 3
Output: 8
Explanation: 
The missing numbers are [5,6,8,...], hence the third missing number is 8.
Example 3:

Input: A = [1,2,4], K = 3
Output: 6
Explanation: 
The missing numbers are [3,5,6,7,...], hence the third missing number is 6.
 

Note:

1 <= A.length <= 50000
1 <= A[i] <= 1e7
1 <= K <= 1e8

*/
#include <vector>

using std::vector;


class MissingElementInSortedArray {

public:


    int doit_linear(vector<int>& nums, int k) {
        
        auto missingcounter = [&](int i) {
             // Return how many numbers are missing until nums[idx]
            return nums[i] - nums[0] - i;
        };
        
        int n = nums.size();
        // If kth missing number is larger than 
        // the last element of the array
        if (k > missingcounter(n-1)) return k - missingcounter(n-1) + nums[n-1];
        
        int i = 0;
        // find idx such that 
        // missing(idx - 1) < k <= missing(idx)
        while (missingcounter(i) < k) i++;
        
        // kth missing number is greater than nums[idx - 1]
        // and less than nums[idx]
        return k - missingcounter(i-1) + nums[i-1];
    }

    /*
        Approach 2: Binary Search
        Intuition
        
        Approach 1 uses the linear search and doesn't profit from the fact that array is sorted. One could replace the linear search by a binary one and reduce the time complexity from \mathcal{O}(N)O(N) down to \mathcal{O}(\log N)O(logN).
        
        The idea is to find the leftmost element such that the number of missing numbers until this element is less or equal to k.
        
        fif
        
        Algorithm
        
        Implement missing(idx) function that returns how many numbers are missing until array element with index idx. Function returns nums[idx] - nums[0] - idx.
        
        Find an index such that missing(idx - 1) < k <= missing(idx) by a binary search.
        
        Return kth smallest nums[idx - 1] + k - missing(idx - 1).
        
        Implementation
        
        Complexity Analysis

        Time complexity: O(logN) since it's a binary search algorithm in the worst case when the missing number is less than the last element of the array.
        
        Space complexity : O(1) since it's a constant space solution.
    */
    
    int doit_binary_search(vector<int>& nums, int k) {
        // Return how many numbers are missing until nums[idx]
        auto missing = [&](int idx) {
            return nums[idx] - nums[0] - idx;
        };

        int n = nums.size();
        // If kth missing number is larger than 
        // the last element of the array
        if (k > missing(n-1))
            return nums[n-1] + k - missing(n-1);

        int left = 0, right = n-1;
        // find left = right index such that 
        // missing(left - 1) < k <= missing(left)
        while (left < right) {
            int mid = (left + right) / 2;

            if (missing(mid) < k)
                left = mid + 1;
            else
                right = mid;
        }

        // kth missing number is greater than nums[idx - 1]
        // and less than nums[idx]
        return nums[left - 1] + k - missing(left-1);
    }
};