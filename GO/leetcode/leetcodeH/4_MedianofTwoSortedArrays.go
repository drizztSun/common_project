package leetcodeH

import (
	"fmt"
	"math"
)

/*
4. Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	m, n := len(nums1), len(nums2)

	if m > n {
		return findMedianSortedArrays(nums2, nums1)
	}

	low, high := 0, m
	half := (m + n + 1) / 2
	for low <= high {

		i := (low + high) / 2
		j := half - i

		if i > 0 && nums1[i-1] > nums2[j] {
			high = i - 1
		} else if i < m && nums1[i] < nums2[j-1] {
			low = i + 1
		} else {
			left, right := 0, 0

			if i == 0 {
				left = nums2[j-1]
			} else if j == 0 {
				left = nums1[i-1]
			} else {
				left = int(math.Max(float64(nums1[i-1]), float64(nums2[j-1])))
			}

			if (m+n)%2 == 1 {
				return float64(left)
			}

			if i == m {
				right = nums2[j]
			} else if j == n {
				right = nums1[i]
			} else {
				right = int(math.Min(float64(nums2[j]), float64(nums1[i])))
			}

			return float64(left+right) / 2
		}
	}
	return float64(0)
}

func Test_4_Median() {

	fmt.Println(findMedianSortedArrays([]int{1, 2}, []int{3,4}))
}
