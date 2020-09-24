package leetcodem

import "math"

/*
525. Contiguous Array

Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.
*/

func findMaxLength_brute_forces(nums []int) int {

	res := 0

	for s := 0; s < len(nums); s++ {

		zeros, ones := 0, 0
		for e := s; e < len(nums); e++ {
			if nums[e] == 1 {
				ones++
			} else {
				zeros++
			}

			if zeros == ones {
				if res < e-s+1 {
					res = e - s + 1
				}
			}
		}
	}

	return res
}

/*
Approach #2 Using Extra Array [Accepted]
Algorithm

In this approach, we make use of a countcount variable, which is used to store the relative number of ones and zeros encountered so far while traversing the array.
The countcount variable is incremented by one for every \text{1}1 encountered and the same is decremented by one for every \text{0}0 encountered.

We start traversing the array from the beginning. If at any moment, the countcount becomes zero, it implies that we've encountered equal number of zeros and
nes from the beginning till the current index of the array(ii). Not only this, another point to be noted is that if we encounter the same countcount twice while traversing the array,
it means that the number of zeros and ones are equal between the indices corresponding to the equal countcount values. The following figure illustrates the observation for the sequence [0 0 1 0 0 0 1 1]:

In the above figure, the subarrays between (A,B), (B,C) and (A,C) (lying between indices corresponing to count = 2count=2) have equal number of zeros and ones.

Another point to be noted is that the largest subarray is the one between the points (A, C). Thus, if we keep a track of the indices corresponding
to the same countcount values that lie farthest apart, we can determine the size of the largest subarray with equal no. of zeros and ones easily.

Now, the countcount values can range between \text{-n}-n to \text{+n}+n, with the extreme points corresponding to the complete array being filled with
all 0's and all 1's respectively. Thus, we make use of an array arrarr(of size \text{2n+1}2n+1to keep a track of the various countcount's encountered so far.
We make an entry containing the current element's index (ii) in the arrarr for a new countcount encountered everytime. Whenever, we come across the same countcount value later while traversing the array,
we determine the length of the subarray lying between the indices corresponding to the same countcount values.
*/

func findMaxLength_array(nums []int) int {
	N := len(nums)
	countArr := make([]int, 2*N+1)

	for i := range countArr {
		countArr[i] = -2
	}
	countArr[N] = -1

	count := 0
	maxLen := 0
	for i := range nums {
		w := 1
		if nums[i] == 0 {
			w = -1
		}

		count += w
		if countArr[count+N] >= -1 {
			//fmt.Println(countArr, i, count)
			maxLen = int(math.Max(float64(maxLen), float64(i-countArr[count+N])))
		} else {
			countArr[count+N] = i
		}
	}

	return maxLen
}

/*
Approach #3 Using HashMap [Accepted]
Algorithm

This approach relies on the same premise as the previous approach. But, we need not use an array of size \text{2n+1}2n+1, since it isn't necessary that we'll encounter all the countcount values possible.
Thus, we make use of a HashMap mapmap to store the entries in the form of (index, count)(index,count). We make an entry for a countcount in the mapmap whenever the countcount is encountered first,
and later on use the correspoding index to find the length of the largest subarray with equal no. of zeros and ones when the same countcount is encountered again.

The following animation depicts the process:
*/

func findMaxLength_hashmap(nums []int) int {

	pos := map[int][]int{0: []int{-1, -1}}
	count := 0
	maxLen := 0

	for i, c := range nums {

		if c == 1 {
			count++
		} else {
			count--
		}

		if _, ok := pos[count]; !ok {
			pos[count] = []int{i, i}
		} else {
			pos[count][1] = i

			if maxLen < i-pos[count][0] {
				maxLen = i - pos[count][0]
			}
		}
	}

	return maxLen
}
