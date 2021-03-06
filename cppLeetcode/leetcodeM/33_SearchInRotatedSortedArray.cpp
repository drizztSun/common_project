/*
33. Search in Rotated Sorted Array

You are given an integer array nums sorted in ascending order (with distinct values), and an integer target.

Suppose that nums is rotated at some pivot unknown to you beforehand (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

If target is found in the array return its index, otherwise, return -1.

 

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1
 

Constraints:

1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
All values of nums are unique.
nums is guaranteed to be rotated at some pivot.
-10^4 <= target <= 10^4



*/
#include <vector>
using std::vector;


class SearchInRotatedSortedArray {

public:
    /*
        Approach 2: One-pass Binary Search
        Instead of going through the input array in two passes, we could achieve the goal in one pass with an revised binary search.

        The idea is that we add some additional condition checks in the normal binary search in order to better narrow down the scope of the search.

        Algorithm

        As in the normal binary search, we keep two pointers (i.e. start and end) to track the search scope. At each iteration, we reduce the search scope into half, by moving either the start or end pointer to the middle (i.e. mid) of the previous search scope.

        Here are the detailed breakdowns of the algorithm:

        Initiate the pointer start to 0, and the pointer end to n - 1.

        Perform standard binary search. While start <= end:

        Take an index in the middle mid as a pivot.

        If nums[mid] == target, the job is done, return mid.

        Now there could be two situations:

        Pivot element is larger than the first element in the array, i.e. the subarray from the first element to the pivot is non-rotated, as shown in the following graph.
    */
    int doit_binary_search(vector<int>& nums, int target) {

        int left = 0, right = nums.size()-1;
        
        while (left <= right) {
            
            int mid = (left + right) / 2;
            
            if (nums[mid] == target) return mid;
            
            if (nums[mid] >= nums[left]) {
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            } else {
                if (target <= nums[right] && target > nums[mid])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        
        return -1;
    }


    int doit_binary_search_1(vector<int>& nums, int target) {

        int left = 0, right = nums.size()-1;
        
        while (left <= right) {
            
            int mid = (left + right) / 2;
            
            if (nums[mid] == target) return mid;
            
            if (nums[mid] <= nums[right]) {
                if (target <= nums[right] && target > nums[mid])
                    left = mid + 1;
                else
                    right = mid - 1;
            } else {
                if (target >= nums[left] && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
        }
        
        return -1;
    }

    // Function to find an element `x` in a circularly sorted array
    int doit_(int A[], int n, int x)
    {
        // search space is `A[low…high]`
        int low = 0, high = n - 1;
    
        // loop till the search space is exhausted
        while (low <= high)
        {
            // find the mid-value in the search space and
            // compares it with the target
            int mid = (low + high)/2;
    
            // if the target is found, return its index
            if (x == A[mid]) {
                return mid;
            }
    
            // if right half `A[mid…high]` is sorted and `mid` is not
            // the target element
            if (A[mid] <= A[high])
            {
                // compare target with `A[mid]` and `A[high]`to know
                // if it lies in `A[mid…high]` or not
                if (x > A[mid] && x <= A[high]) {
                    low = mid + 1;    // go searching in the right sorted half
                } else {
                    high = mid - 1;    // go searching left
                }
            }
    
            // if left half `A[low…mid]` is sorted, and `mid` is not
            // the target element
            else
            {
                // compare target with `A[low]` and `A[mid]` to know
                // if it lies in `A[low…mid]` or not
                if (x >= A[low] && x < A[mid]) {
                    high = mid - 1;    // go searching in the left sorted half
                } else {
                    low = mid + 1;    // go searching right
                }
            }
        }
    
        // target not found or invalid input
        return -1;
    }
};