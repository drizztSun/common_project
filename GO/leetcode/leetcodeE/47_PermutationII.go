package leetcodeE

import (
	"fmt"
	"sort"
)

func permuteUnique_1(nums []int) [][]int {

	sort.Ints(nums)

	if len(nums) == 1 {
		r := append([]int{}, nums...)
		return [][]int{r}
	}

	res := make([][]int, 0)
	for i := 0; i < len(nums); i++ {

		if i != len(nums)-1 && nums[i] == nums[i+1] {
			continue
		}

		next := nums
		next = append(next[:i], next[i+1:]...)
		for _, c := range permuteUnique_1(next) {
			res = append(res, append([]int{nums[i]}, c...))
		}
	}

	return res
}

func permuteUnique_2(nums []int, used []bool, result *[][]int, temp []int) {
	if len(nums) == len(temp) {
		r := append([]int{}, temp...)
		*result = append(*result, r)
		return
	}

	for i, num := range nums {
		if used[i] || (i > 0 && nums[i] == nums[i-1] && !used[i-1]) {
			continue
		}

		used[i] = true
		temp = append(temp, num)
		permuteUnique_2(nums, used, result, temp)
		temp = temp[:len(temp)-1]
		used[i] = false
	}
}

func permuteUnique_(nums []int) [][]int {

	var result [][]int
	if len(nums) == 0 {
		return result
	}

	sort.Ints(nums)
	used := make([]bool, len(nums))
	temp := []int{}
	permuteUnique_2(nums, used, &result, temp)
	return result
}

func permuteUnique(nums []int) [][]int {
	res := make([][]int, 0)
	m := getCounts(nums)
	return permute([]int{}, m, res, len(nums))
}

func getCounts(nums []int) map[int]int {
	m := make(map[int]int)
	for _, num := range nums {
		m[num] += 1
	}
	return m
}

func permute_3(prefix []int, counts map[int]int, res [][]int, n int) [][]int {
	if len(prefix) == n {
		completed := append([]int{}, prefix...)
		return append(res, completed)
	}

	for k, v := range counts {
		if v > 0 {
			counts[k] -= 1
			res = permute_3(append(prefix, k), counts, res, n)
			counts[k] += 1
		}
	}

	return res
}

func Test_47_permuteII() {

	fmt.Println(permuteUnique_1([]int{1, 1, 2}))

	fmt.Println(permuteUnique_1([]int{1, 2, 2, 3, 3, 4}))
}
