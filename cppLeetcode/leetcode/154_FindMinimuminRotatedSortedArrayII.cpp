/*
154. Find Minimum in Rotated Sorted Array II

Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:

    . [4,5,6,7,0,1,4] if it was rotated 4 times.
    . [0,1,4,4,5,6,7] if it was rotated 7 times.
Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.

 

Example 1:

Input: nums = [1,3,5]
Output: 1
Example 2:

Input: nums = [2,2,2,0,1]
Output: 0
 

Constraints:

n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
nums is sorted and rotated between 1 and n times.
 

Follow up: This is the same as Find Minimum in Rotated Sorted Array but with duplicates. Would allow duplicates affect the run-time complexity? How and why?
*/

#include <vector>

using std::vector;


class MinimumInRotatedSortedArray {

    /*
        154.Find-Minimum-in-Rotated-Sorted-Array-II
        解法1:
        解题思路：和153. Find Minimum in Rotated Sorted Array 一样，需要以nums[left]为基准， 分别比较nums[mid]和nums[right]，以判断三者所在的区间（左区间还是右区间，也就是交换前的小区间或者大区间）。

        此题的特别之处是，当出现x==nums[left]时，无法定位x所在的区间是左还是右。解决技巧是：

        while (left+1<right && nums[left]==nums[left+1]) left++;
        这样，当出现x==nums[left]时,x必定是在右区间，可以和x<nums[left]归并；x>nums[left]则说明x在左区间。

        所以分段讨论的方法如下：

                    if (nums[left]<nums[mid] && nums[left]<nums[right])  // left,mid,right同在一个区间
                        right=mid;  // 可以直接 return nums[left]
                    else if (nums[left]<nums[mid] && nums[left]>=nums[right]) // left,mid在左区间，right在右区间
                        left=mid+1;
                    else if (nums[left]>=nums[mid] && nums[left]<nums[right]) // mid在右区间,right在左区间，不可能
                        continue;
                    else if (nums[left]>=nums[mid] && nums[left]>=nums[right]) // left在左区间，mid,right在右区间
                        right=mid;   
        解法2:
        此题有一种更简洁的分类讨论方式，那就是查看nums[mid]和nums[right]的大小关系。

                while (left<right)
                {
                    int mid = left+(right-left)/2;  
                    if (nums[mid] > nums[right])
                        left = mid+1;
                    else if (nums[mid] < nums[right])
                        right = mid;
                    else
                        right -= 1;
                }
        第一种情况，可以轻易判断出mid在左区间。

        第二种情况，可以轻易判断出mid和right在同一个区间。考虑到我们始终往右区间收敛，所以可以判定此时mid在右区间。

        第三种情况，有一个非常tricky的技巧。既然无法判定mid是否在左区间还是右区间，但是因为nums[mid]和nums[right]一样，那么去掉nums[right]并不影响结果。\
        去掉nums[right]（将右边界左移一位）反而可以进一步帮助分析mid所属的位置：如果下一步出现nums[mid]和nums[right]不一样，那就依照之前的逻辑很好处理；否则就继续移动right，同样没有影响。
    */
    int findMin(vector<int>& nums) 
    {

        int left=0;
        int right=nums.size()-1;
        int mid;
        
        while (left<right)
        {
            while (left+1<right && nums[left]==nums[left+1])
                left++;
                
            mid=left+(right-left)/2;
            if (left==right-1) return std::min(nums[left],nums[right]);
            
            if (nums[left]<nums[mid] && nums[left]<nums[right])
                right=mid;  // return nums[left];
            else if (nums[left]<nums[mid] && nums[left]>=nums[right])
                left=mid+1;
            else if (nums[left]>=nums[mid] && nums[left]<nums[right])
                continue;
            else if (nums[left]>=nums[mid] && nums[left]>=nums[right])
                right=mid;    
        }
        
        return nums[left];
    }

    int findMin(vector<int>& nums) 
    {
        int left = 0;
        int right = nums.size()-1;
        
        while (left<right)
        {
            int mid = left+(right-left)/2;  
            if (nums[mid] > nums[right])
                left = mid+1;
            else if (nums[mid] < nums[right])
                right = mid;
            else
                right -= 1;
        }
        return nums[left];
    }


public:
    
    int doit_binary_search(vector<int>& nums) {
        
        int left = 0, right = nums.size() - 1;

        for (left < right) {
            
            int mid = (left + right) / 2;

            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else if (nums[mid] < nums[right]) {
                right = mid;
            } else {
                right--;
            }
        }
        
        return nums[left];
    }
};