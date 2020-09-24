/*
4. Median of Two Sorted Arrays

Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

Follow up: The overall run time complexity should be O(log (m+n)).



Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
Example 3:

Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000
Example 4:

Input: nums1 = [], nums2 = [1]
Output: 1.00000
Example 5:

Input: nums1 = [2], nums2 = []
Output: 2.00000
 

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
*/

struct MedianTwoSortedArray (u8);

impl MedianTwoSortedArray {

    pub fn doit_divide_and_conquer(nums1: Vec<i32>, nums2: Vec<i32>) -> f64 {

        if nums1.len() > nums2.len() {
            return Self::doit_divide_and_conquer(nums2, nums1);
        }

        let m = nums1.len();
        let n = nums2.len();
        let half = (m + n + 1) / 2;
        let mut low = 0;
        let mut high = m;

        while low <= high {

            let c1 = (low + high) / 2;
            let c2 = half - c1;

            if c1 < m && nums1[c1] < nums2[c2-1] {
                low = c1 +1;
            } else if c1 > 0 && nums1[c1-1] > nums2[c2] {
                high = c1 - 1;
            } else {

                let mut left = 0;
                let mut right = 0;

                if c1 == 0 {
                    left = nums1[c2-1];
                } else if c2 == 0 {
                    left = nums1[c1-1];
                } else {
                    left = nums1[c1-1];
                    if left < nums2[c2-1] {
                        left = nums2[c2-1];
                    }
                }

                if (m+n) % 2 == 1 {
                    return left as f64;
                }

                if c1 == m {
                    right = nums2[c2];
                } else if c2 == n {
                    right = nums1[c1];
                } else {
                    right = nums1[c1];
                    if right > nums2[c2] {
                        right = nums2[c2];
                    }
                }

                return (left as f64 + right as f64) / 2 as f64;
            }
        }

        0 as f64
    }


}


pub fn test_4_MedianTwoSortedArrays() {

    println!("result {}", MedianTwoSortedArray::doit_divide_and_conquer(vec![1,2], vec![3, 4]));
}