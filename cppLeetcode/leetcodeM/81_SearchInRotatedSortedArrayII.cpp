/*
81. Search in Rotated Sorted Array II

You are given an integer array nums sorted in ascending order (not necessarily distinct values), and an integer target.

Suppose that nums is rotated at some pivot unknown to you beforehand (i.e., [0,1,2,4,4,4,5,6,6,7] might become [4,5,6,6,7,0,1,2,4,4]).

If target is found in the array return its index, otherwise, return -1.

 

Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
 

Constraints:

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
nums is guaranteed to be rotated at some pivot.
-104 <= target <= 104
 

Follow up: This problem is the same as Search in Rotated Sorted Array, where nums may contain duplicates. Would this affect the run-time complexity? How and why?
*/
#include <vector>

using std::vector;


class SearchInRotatedSortedArrayII {

    /*
        81.Search-in-Rotated-Sorted-Array-II
        解法1:
        此题是154和33的结合体。

        解题思路大致是：  

        1. 比较nums[left]和nums[mid]、target的大小，确定三者所处的区间关系。
        2. 因为允许重复元素的存在，当x==nums[left]时是无法确定x所处的区间。提前如下处理，这样x<=nums[left]可以归并一类，定位在右区间。    
        while (left+1<right && nums[left]==nums[left+1]) left++;
        3. 每个循环都提前处理 nums[left],nums[mid],nums[right]等于target的情况。  
        
        解法2:
        和33题的解法2一样。总体思想就是查看nums[mid]和target是否在同一个单调区间。如果是的话，就套用传统的二分搜索，这个对于非严格递增的递增序列也是适用的。如果不是的话，则直接将搜索范围移向target所在单调区间。

        和33题唯一的区别就是，当出现类似于1 1 1 2 3 4 0 1 1这种情况时，if (nums[mid]>=nums[0] == target>=nums[0])这个语句会失效，无法正确判断nums[mid]和target是否在同一个区间里。解决方法非常简单，就是将数组末尾的这些与nums[0]相同的数都去掉就行了。
    
    */
    bool search(vector<int>& nums, int target) 
    {
        if (nums.size()==0) return false;
        
        int left=0;
        int right=nums.size()-1;
        int mid;
        
        while (left<right)
        {            
            while (left+1<right && nums[left]==nums[left+1])
                left++;
            mid=left+(right-left)/2;      
            
            if (nums[left]==target || nums[right]==target || nums[mid]==target) return true;
            
            if (nums[mid]>nums[left] && target>nums[left])
            {
                if (nums[mid]>target)
                    right=mid-1;
                else
                    left=mid+1;
            }
            else if (nums[mid]>nums[left] && target<=nums[left])
                left=mid+1;
            else if (nums[mid]<=nums[left] && target>nums[left])
                right=mid-1;
            else if (nums[mid]<=nums[left] && target<=nums[left])
            {
                if (nums[mid]>target)
                    right=mid-1;
                else
                    left=mid+1;
            }
        }
        
        if (nums[left]==target) 
            return true;
        else
            return false;
    }

    bool search(vector<int>& nums, int target) 
    {
        while (nums.size()>1 && nums.back()==nums[0])
            nums.pop_back();
        
        int left = 0;
        int right = nums.size()-1;
        
        while (left<right)
        {
            int mid = left+(right-left)/2;
            
            if (nums[mid] == target) return true;
            
            if (nums[mid]>=nums[0] == target>=nums[0])
            {
                if (nums[mid]<target)
                    left = mid+1;
                else
                    right = mid-1;
            }
            else if (target>=nums[0])
                right = mid-1;
            else
                left = mid+1;
        }
        
        if (left==right && nums[left]==target)
            return true;
        else
            return false;
    }




public:

    bool doit_binary_search(vector<int>& nums, int target) {

        int l = 0, r = nums.size()-1;
        
        while (l <= r) {

            int mid = (r-l)/2+l;
            
            if (nums[mid] == target)
                return true;
        
            if (nums[mid] < nums[r]) {
                if (nums[mid]<target && target<=nums[r])
                    l = mid+1;
                else
                    r = mid-1;
            } else if (nums[mid] > nums[r]) {
                if (nums[l]<=target && target<nums[mid])
                    r = mid-1;
                else
                    l = mid+1;
            } else
                r--;
        
        }
        return false;
    }
    
    bool doit_binary_search(vector<int>& nums, int target) {

        int low = 0, high = nums.size()-1;

        while (low <= high) {

            int mid = (low + high) / 2;

            if (nums[mid] == target) return true;

            if (nums[mid] > nums[low]) {

                if (target < nums[mid] && target >= nums[low])
                    high = mid - 1;
                else
                    low = mid + 1;

            } else if (nums[mid] < nums[low]) {

                if (target > nums[mid] && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;

            } else {
                low++;
            }

        }

        return false;
    }

    /*
        Approach 1: Binary Search
        This problem is an extension to 33. Search in Rotated Sorted Array. The only difference is that this problem allows duplicate elements.

        Intuition

        Recall that after rotating a sorted array, what we get is two sorted arrays appended to each other.

        rotating a sorted array

        Let's refer to the first sorted array as F and second as S.

        rotating a sorted array

        Also, we can observe that all the elements of the second array S will be smaller or equal to the first element start of F.

        rotating a sorted array

        With this observation in mind, we can easily tell which of the 2 arrays (F or S) does a target element lie in by just comparing it with the first element of the array.

        Let's say we are looking for element target in array arr:

        Case 1: If target > arr[start]: target exists in the first array F.
        rotating a sorted array

        Case 2: If target < arr[start]: target exists in the second array S.
        rotating a sorted array

        Case 3: If target == arr[start]: target obviously exists in the first array F, but it might also be present in the second array S.
        rotating a sorted array

        Let's define a helper function that tells us which array a target element might be present in:


        Algorithm

        Recall that in standard binary search, we keep two pointers (i.e. start and end) to track the search scope in an arr array. We then divide the search space in three parts [start, mid), [mid, mid], (mid, end]. Now, we continue to look for our target element in one of these search spaces.

        By identifying the positions of both arr[mid] and target in F and S, we can reduce search space in the very same way as in standard binary search:

        Case 1: arr[mid] lies in F, target lies in S: Since S starts after F ends, we know that element lies here:(mid, end].
        rotating a sorted array

        Case 2: arr[mid] lies in the S, target lies in F: Similarly, we know that element lies here: [start, mid).
        rotating a sorted array

        Case 3: Both arr[mid] and target lie in F: since both of them are in same sorted array, we can compare arr[mid] and target in order to decide how to reduce search space.
        rotating a sorted array

        Case 4: Both arr[mid] and target lie in S: Again, since both of them are in same sorted array, we can compare arr[mid] and target in order to decide how to reduce search space.
        rotating a sorted array

        But there is a catch, if arr[mid] equals arr[start], then we know that arr[mid] might belong to both F and S and hence we cannot find the relative position of target from it.

        rotating a sorted array


        In this case, we have no option but to move to next search space iteratively. Hence, there are certain search spaces that allow a binary search, and some search spaces that don't.


        Complexity Analysis

        Time complexity : O(N) worst case, O(logN) best case, where NN is the length of the input array.

        Worst case: This happens when all the elements are the same and we search for some different element. At each step, we will only be able to reduce the search space by 1 since arr[mid] equals arr[start] and it's not possible to decide the relative position of target from arr[mid]. Example: [1, 1, 1, 1, 1, 1, 1], target = 2.

        Best case: This happens when all the elements are distinct. At each step, we will be able to divide our search space into half just like a normal binary search.

        This also answers the following follow-up question:

        Would this (having duplicate elements) affect the run-time complexity? How and why?
        As we can see, by having duplicate elements in the array, we often miss the opportunity to apply binary search in certain search spaces. Hence, we get O(N)O(N) worst case (with duplicates) vs O(\log N)O(logN) best case complexity (without duplicates).

        Space complexity : O(1).
    */
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return false;
        int end = n - 1;
        int start = 0;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] == target) {
                return true;
            }
            
            if (!isBinarySearchHelpful(nums, start, nums[mid])) {
                start++;
                continue;
            }
            
            // which array does pivot belong to.
            bool pivotArray = existsInFirst(nums, start, nums[mid]);

            // which array does target belong to.
            bool targetArray = existsInFirst(nums, start, target);
            if (pivotArray ^ targetArray) { // If pivot and target exist in different sorted arrays, recall that xor is true only when both the operands are distinct
                if (pivotArray) {
                    start = mid + 1; // pivot in the first, target in the second
                } else {
                    end = mid - 1; // target in the first, pivot in the second
                }
            } else { // If pivot and target exist in same sorted array
                if (nums[mid] < target) {
                    start = mid + 1;
                } else {
                    end = mid - 1;
                }
            }
        }
        return false;
    }
    
    // returns true if we can reduce the search space in current binary search space
    bool isBinarySearchHelpful(vector<int>& nums, int start, int element) {
        return nums[start] != element;
    }

    // returns true if element exists in first array, false if it exists in second
    bool existsInFirst(vector<int>& nums, int start, int element) {
        return nums[start] <= element;
    }
};