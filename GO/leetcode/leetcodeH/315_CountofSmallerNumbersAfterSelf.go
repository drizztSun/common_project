package leetcodeH

/*
315. Count of Smaller Numbers After Self

You are given an integer array nums and you have to return a new counts array.
The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].



Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.


Constraints:

0 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

*/

func countSmaller_one(nums []int) []int {

	binary_search := func(pos []int, n int) int {

		s, e := 0, len(pos)-1

		for s <= e {

			m := (s + e) / 2

			if pos[m] >= n {
				e = m - 1
			} else {
				s = m + 1
			}
		}
		return s
	}

	pos := make([]int, 0)
	res := make([]int, len(nums))

	for i := len(nums) - 1; i >= 0; i-- {

		index := binary_search(pos, nums[i])

		pos = append(pos[:index], append([]int{nums[i]}, pos[index:]...)...)

		res[i] = index
	}

	return res
}

type Pair struct {
	inx int
	val int
}

func mergeSort(nums []Pair, lo, hi int, ret *[]int) []Pair {
	if lo == hi {
		return []Pair{nums[lo]}
	}
	mid := lo + (hi-lo)/2

	left := mergeSort(nums, lo, mid, ret)
	right := mergeSort(nums, mid+1, hi, ret)
	// fmt.Println(left, right)
	arr := make([]Pair, hi-lo+1)
	i, j := 0, 0
	for j != len(right) || i != len(left) {
		if j == len(right) || i < len(left) && left[i].val <= right[j].val {
			// fmt.Println(left[i].inx, j)
			(*ret)[left[i].inx] += j
			arr[i+j] = left[i]
			i++
		} else {
			arr[i+j] = right[j]
			j++
		}
	}
	return arr
}

func countSmaller_two(nums []int) []int {
	if len(nums) == 0 {
		return []int{}
	}
	pairs := make([]Pair, len(nums))
	for ix, n := range nums {
		pairs[ix] = Pair{inx: ix, val: n}
	}
	ret := make([]int, len(nums))
	mergeSort(pairs, 0, len(nums)-1, &ret)
	return ret
}
