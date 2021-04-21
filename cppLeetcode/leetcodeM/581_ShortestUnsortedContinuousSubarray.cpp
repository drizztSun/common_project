/*
581. Shortest Unsorted Continuous Subarray


Given an integer array nums, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order.

Return the shortest such subarray and output its length.

 

Example 1:

Input: nums = [2,6,4,8,10,9,15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
Example 2:

Input: nums = [1,2,3,4]
Output: 0
Example 3:

Input: nums = [1]
Output: 0
 

Constraints:

1 <= nums.length <= 10^4
-10^5 <= nums[i] <= 10^5

Follow up: Can you solve it in O(n) time complexity?

*/

#include <vector>

using std::vector;


class UnsortedSubarray {

    /*
        581.shortest-unsorted-continuous-subarray
        本题的难点是如何设计不需要排序的o(n)算法。

        找出这样一个right_bound：位于该数左边的所有数的最大值，要比这个数大，这说明这个数在排序后需要变换位置。怎么找呢？将数组从左到右过一遍，实时保存最大值即可，不断刷新这个right_bound。

        同理，找到这样一个left_bound：位于该数右边的所有数的最小值，要比这个数小，这说明这个数在排序后需要变换位置。也是讲数组从右往左过一遍，实时保存最小值。

        最后当right_bound>left_bound时，结果就是 right_bound-left_bound+1
    */
    int findUnsortedSubarray(vector<int>& nums) 
    {
        int curMax=INT_MIN;
        int right_bound=0;
        for (int i=0; i<nums.size(); i++)
        {
            if (nums[i]<curMax)
                right_bound=i;
            curMax=std::max(curMax,nums[i]);
        }
        
        int curMin=INT_MAX;
        int left_bound=nums.size()-1;
        for (int i=nums.size()-1; i>=0; i--)
        {
            if (nums[i]>curMin)
                left_bound=i;
            curMin=std::min(curMin,nums[i]);
        }
        
        return left_bound>=right_bound?0:right_bound-left_bound+1;
    }

public:

    int doit_search(vector<int>& nums) {
        
        int leftBound = nums.size(), rightBound= 0;
        
        int curmax = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            
            if (nums[i] < curmax)
                rightBound = i;
            curmax = std::max(curmax, nums[i]);
        }
        
        int curmin = INT_MAX;
        for (int i = nums.size()-1; i >= 0; i--) {
            if (nums[i] > curmin)
                leftBound = i;
            curmin = std::min(curmin, nums[i]);
        }
        
        return rightBound > leftBound ? rightBound - leftBound + 1 : 0;
    }

    /*
        Approach 2: Better Brute Force
        Algorithm

        In this approach, we make use of an idea based on selection sort. We can traverse over the given numsnums array choosing the elements nums[i]nums[i]. For every such element chosen, we try to determine its correct position in the sorted array. For this, we compare nums[i]nums[i] with every nums[j]nums[j], such that i < j < ni<j<n. Here, nn refers to the length of numsnums array.

        If any nums[j]nums[j] happens to be lesser than nums[i]nums[i], it means both nums[i]nums[i] and nums[j]nums[j] aren't at their correct position for the sorted array. Thus, we need to swap the two elements to bring them at their correct positions. Here, instead of swapping, we just note the position of nums[i]nums[i](given by ii) and nums[j]nums[j](given by jj). These two elements now mark the boundary of the unsorted subarray(atleast for the time being).

        Thus, out of all the nums[i]nums[i] chosen, we determine the leftmost nums[i]nums[i] which isn't at its correct position. This marks the left boundary of the smallest unsorted subarray(ll). Similarly, out of all the nums[j]nums[j]'s considered for all nums[i]nums[i]'s we determine the rightmost nums[j]nums[j] which isn't at its correct position. This marks the right boundary of the smallest unsorted subarray(rr).

        Unsorted_subarray

        Thus, we can determine the length of the smallest unsorted subarray as r - l + 1r−l+1.


        Complexity Analysis

        Time complexity : O(n^2)O(n 
        2
        ). Two nested loops are there.

        Space complexity : O(1)O(1). Constant space is used.    
    */
    int doit_twopointer_TLE(vector<int>& nums) {
        
        int l = nums.size(), r = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            
            for (int j = i+1; j < nums.size(); j++) {
                if (nums[j] < nums[i]) {
                    l = std::min(l, i);
                    r = std::max(r, j);
                }
            }
            
        }
        
        return r - l < 0 ? 0 : r - l + 1;
    }



    /*
        Approach 3: Using Sorting
        Algorithm

        Another very simple idea is as follows. We can sort a copy of the given array numsnums, say given by nums\_sortednums_sorted. 
        Then, if we compare the elements of numsnums and nums\_sortednums_sorted, we can determine the leftmost and rightmost elements which mismatch. The subarray lying between them is, then, the required shorted unsorted subarray.


        Complexity Analysis

        Time complexity : O(n\log n)O(nlogn). Sorting takes n\log nnlogn time.

        Space complexity : O(n)O(n). We are making copy of original array.

    */

    int doit_sort(vector<int>& nums) {
        vector<int> A = nums;
        std::sort(begin(A), end(A));
        int start = A.size(), end = -1;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != A[i]) {
                start = std::min(start, i);
                end = std::max(end, i);
            }
        } 
        
        return end - start >= 0 ? (end - start + 1) : 0; 
    }

    /*
        Approach 5: Without Using Extra Space
        Algorithm

        The idea behind this method is that the correct position of the minimum element in the unsorted subarray helps to determine the required left boundary. Similarly, the correct position of the maximum element in the unsorted subarray helps to determine the required right boundary.

        Thus, firstly we need to determine when the correctly sorted array goes wrong. We keep a track of this by observing rising slope starting from the beginning of the array. Whenever the slope falls, we know that the unsorted array has surely started. Thus, now we determine the minimum element found till the end of the array numsnums, given by minmin.

        Similarly, we scan the array numsnums in the reverse order and when the slope becomes rising instead of falling, we start looking for the maximum element till we reach the beginning of the array, given by maxmax.

        Then, we traverse over numsnums and determine the correct position of minmin and maxmax by comparing these elements with the other array elements. e.g. To determine the correct position of minmin, we know the initial portion of numsnums is already sorted. Thus, we need to find the first element which is just larger than minmin. Similarly, for maxmax's position, we need to find the first element which is just smaller than maxmax searching in numsnums backwards.

        We can take this figure for reference again:

        Unsorted_subarray

        We can observe that the point bb needs to lie just after index 0 marking the left boundary and the point aa needs to lie just before index 7 marking the right boundary of the unsorted subarray.
    */
    int findUnsortedSubarray(vector<int>& nums) {
        
        int minv = INT_MAX, maxv = INT_MIN;
        
        bool flag = false;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i-1]) flag = true;
            
            if (flag)
                minv = std::min(minv, nums[i]);
        }
        
        flag = false;
        for (int i = nums.size()-2; i >= 0; i--) {
            if (nums[i] > nums[i+1]) flag = true;
            
            if (flag) maxv = std::max(maxv, nums[i]);
        }
        
        int l, r;
        
        for (l = 0; l < nums.size() && minv >= nums[l]; l++);
        
        for (r = nums.size()-1; r >= 0 && maxv <= nums[r]; r--);
            
            
        return r - l < 0 ? 0 : r - l + 1;
    }
};


