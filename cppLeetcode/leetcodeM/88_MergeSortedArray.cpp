/*
88. Merge Sorted Array

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

The number of elements initialized in nums1 and nums2 are m and n respectively. 

You may assume that nums1 has a size equal to m + n such that it has enough space to hold additional elements from nums2.

 

Example 1:

Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Example 2:

Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
 

Constraints:

nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-10^9 <= nums1[i], nums2[i] <= 10^9
*/
#include <vector>

using std::vector;


class MergeSortedArray {

    /*
        88. Merge Sorted Array
        算法：双指针
        从nums1的第m+n-1的位置开始降序填充，进行归并排序。
    */
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
    {
        int p1=m-1;
        int p2=n-1;
        
        for (int i=m+n-1; i>=0; i--)
        {
            if (p1<0)
            {
                nums1[i]=nums2[p2];
                p2--;
            }
            else if (p2<0)
            {
                nums1[i]=nums1[p1];
                p1--;
            }
            else if (nums1[p1]>nums2[p2])
            {
                nums1[i]=nums1[p1];
                p1--;
            }
            else
            {
                nums1[i]=nums2[p2];
                p2--;
            }                
        }
    }

public:
    
    void doit_(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        
        int p1 = m-1, p2 = n-1;
        
        for (int i = m + n - 1; i >= 0; i--) {
            if (p1 < 0)
                nums1[i] = nums2[p2--];
            else if (p2 < 0)
                nums1[i] = nums1[p1--];
            else if (nums1[p1] < nums2[p2])
                nums1[i] = nums2[p2--];
            else
                nums1[i] = nums1[p1--];
        }
    }
};