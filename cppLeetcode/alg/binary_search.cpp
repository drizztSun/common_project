#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;


int binary_search_1(vector<int>& nums, int target) {

    int left = 0, right = nums.size();

    // [left, right] scope, 
    while (left < right) { // left <= right

        // if left and right are all so big number, it is gonna be overflow.
        int mid = left + (right - left) / 2;

        if (nums[mid] >= target)
            // mid is correct target, so right needs tp include target. 
            // right = mid + 1;
            right = mid;
        else
            // mid is not correct, so left needs not to include target.
            left = mid + 1; 
    }

    return left;
}


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

// 1539 Missing number
int doit_binary_search(vector<int>& arr, int k) {

    int left = 0, right = arr.size()-1;

    while (left <= right) {

        int mid = left + (right - left) / 2;

        // If number of positive integers
        // which are missing before arr[pivot]
        // is less than k -->
        // continue to search on the right.
        if (arr[mid] - mid - 1 < k)
            left = mid + 1;
        // Otherwise, go left.
        else
            right = mid - 1;
    }

    // At the end of the loop, left = right + 1,
    // and the kth missing is in-between arr[right] and arr[left].
    // The number of integers missing before arr[right] is
    // arr[right] - right - 1 -->
    // the number to return is
    // arr[right] + k - (arr[right] - right - 1) = k + left
    return left + k;
}
