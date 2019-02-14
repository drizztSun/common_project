package leetcodeE

/*
# 658. Find K Closest Elements

# Given a sorted array, two integers k and x, find the k closest elements to x in the array.
# T# he result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.

# Example 1:
# Input: [1,2,3,4,5], k=4, x=3
# Output: [1,2,3,4]
# Example 2:
# Input: [1,2,3,4,5], k=4, x=-1
# Output: [1,2,3,4]
# Note:
# The value k is positive and will always be smaller than the length of the sorted array.
# Length of the given array is positive and will not exceed 104
# Absolute value of elements in the array and x will not exceed 104

*/

func findClosestElements(arr []int, k int, x int) []int {

	l, r := 0, len(arr)-k

	for l < r {
		m := l + (r-l)/2

		if x-arr[m] > arr[m+k]-x {
			l = m + 1
		} else {
			r = m
		}
	}

	return arr[l : l+k]
}

func abs(x int) int {
	if x < 0 {
		return x * -1
	}
	return x
}

func findClosestElements1(arr []int, k int, x int) []int {
	if len(arr) == 0 {
		return []int{}
	}

	lowestDiff := abs(arr[0] - x)
	lowestPos := 0

	for i, v := range arr {
		if abs(v-x) < lowestDiff {
			lowestPos, lowestDiff = i, abs(v-x)
		}
	}

	L, R := lowestPos, lowestPos
	for R+1-L != k {
		if L == 0 {
			R++
			continue
		}

		if R == len(arr)-1 {
			L--
			continue
		}

		rightMag := abs(arr[R+1] - x)
		leftMag := abs(arr[L-1] - x)
		if leftMag <= rightMag {
			L--
		} else {
			R++
		}
	}

	return arr[L : R+1]
}
