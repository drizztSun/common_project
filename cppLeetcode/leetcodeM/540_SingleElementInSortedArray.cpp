/*
540. Single Element in a Sorted Array


You are given a sorted array consisting of only integers where every element appears exactly twice, 
except for one element which appears exactly once. Find this single element that appears only once.

Follow up: Your solution should run in O(log n) time and O(1) space.

 

Example 1:

Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:

Input: nums = [3,3,7,7,10,11,11]
Output: 10
 

Constraints:

1 <= nums.length <= 10^5
0 <= nums[i] <= 10^5
*/
#include <vector>

using std::vector;

class SingleNonDuplicate {

public:

    int doit_xor(vector<int>& nums) {
        
        int ans = 0;
        for (auto c: nums) ans ^= c;
        
        return ans;
    }
    
    int doit_binary_search(vector<int>& nums) {

        int n = nums.size();
        
        int left = 0, right = n-1;
        
        while (left < right) {
            
            int mid = left + (right - left) / 2;
            
            if (mid % 2 == 1) mid--;
            
            if (nums[mid] == nums[mid+1]) {
                left = mid+2;
            } else {
                right = mid;
            }
        }
        return nums[left];
    }

    int doit_binary_search(vector<int>& nums) {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            bool halvesAreEven = (hi - mid) % 2 == 0;
            if (nums[mid + 1] == nums[mid]) {
                if (halvesAreEven) {
                    lo = mid + 2;
                } else {
                    hi = mid - 1;
                }
            } else if (nums[mid - 1] == nums[mid]) {
                if (halvesAreEven) {
                    hi = mid - 2;
                } else {
                    lo = mid + 1;
                }
            } else {
                return nums[mid];
            }
        }
        return nums[lo];
    }

    /*
        Approach 3: Binary Search on Evens Indexes Only
        It turns out that we only need to binary search on the even indexes. This approach is more elegant than the last, although both are good solutions.

        Intuition

        The single element is at the first even index not followed by its pair. We used this property in the linear search algorithm, where we iterated over all of the even indexes until we encountered the first one not followed by its pair.

        Instead of linear searching for this index though, we can binary search for it.

        After the single element, the pattern changes to being odd indexes followed by their pair. This means that the single element (an even index) and all elements after it are even indexes not followed by their pair. Therefore, given any even index in the array, we can easily determine whether the single element is to the left or to the right.

        Algorithm

        We need to set up the binary search variables and loop so that we are only considering even indexes. The last index of an odd-lengthed array is always even, so we can set lo and hi to be the start and end of the array.

        We need to make sure our mid index is even. We can do this by dividing lo and hi in the usual way, but then decrementing it by 1 if it is odd. This also ensures that if we have an even number of even indexes to search, that we are getting the lower middle (incrementing by 1 here would not work, it'd lead to an infinite loop as the search space would not be reduced in some cases).

        Then we check whether or not the mid index is the same as the one after it.

        If it is, then we know that mid is not the single element, and that the single element must be at an even index after mid. Therefore, we set lo to be mid + 2. It is +2 rather than the usual +1 because we want it to point at an even index.
        If it is not, then we know that the single element is either at mid, or at some index before mid. Therefore, we set hi to be mid.
        Once lo == hi, the search space is down to 1 element, and this must be the single element, so we return it.


        Complexity Analysis

        Time complexity : O(logn). Same as the binary search above, except we are only binary searching half the elements, rather than all of them.

        Space complexity : O(1). Same as the other approaches. We are only using constant space to keep track of where we are in the search.
    */
    int doit_binary_search(vector<int>& nums) {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (mid % 2 == 1) mid--;
            if (nums[mid] == nums[mid + 1]) {
                lo = mid + 2;
            } else {
                hi = mid;
            }
        }
        return nums[lo];
    }
};