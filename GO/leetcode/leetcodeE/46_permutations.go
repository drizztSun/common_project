package leetcodeE

import (
	"fmt"
)

func permute_recursive(a []int) [][]int {
	if len(a) == 1 {
		return [][]int{a}
	}

	// res := make([][]int)
	var res [][]int
	for i := 0; i < len(a); i++ {
		n := append(a[:i], a[i+1:]...)
		s := permute_recursive(n)
		for _, c := range s {
			res = append(res, append([]int{a[i]}, c[:]...))
		}
	}

	return res
}

func permute_recursive_1(nums []int, current int, res *[][]int) *[][]int {

	if current >= len(nums) - 1{
		r := append([]int{}, nums...)
		*res = append(*res, r)
		return res
	}

	for i := current; i < len(nums); i++ {
		nums[current], nums[i] = nums[i], nums[current]
		permute_recursive_1(nums, current+1, res)
		nums[current], nums[i] = nums[i], nums[current]
	}

	return res
}

//way3
func getNextPermute(m map[int]struct{}, nums []int, level int) [][]int {
	var s [][]int

	for i := 0; i < len(nums); i++ {
		if _, ok := m[i]; !ok {
			m[i] = struct{}{}
			if level == 1 {
				s = append(s, []int{nums[i]})
			} else {
				n := getNextPermute(m, nums, level-1)
				for _, v := range n {
					s = append(s, append([]int{nums[i]}, v...))
				}
			}
			delete(m, i)
		}
	}
	return s
}

func permute_3(nums []int) [][]int {
	m := make(map[int]struct{})
	return getNextPermute(m, nums, len(nums))
}

// way2
func permute2(nums []int) [][]int {
	var result [][]int
	var current []int
	return backtrack(result, nums, current)
}

func backtrack(result [][]int, nums []int, current []int) [][]int {
	if len(current) == len(nums) {
		temp := make([]int, len(nums))
		copy(temp, current)
		return append(result, temp)
	}
	for i := 0; i < len(nums); i++ {
		if notIn(current, nums[i]) {
			current = append(current, nums[i])
			result = backtrack(result, nums, current)
			current = current[:len(current)-1]
		}
	}
	return result
}

func notIn(nums []int, num int) bool {
	for _, v := range nums {
		if v == num {
			return false
		}
	}
	return true
}

// way1
func permute1(nums []int) [][]int {
	var result [][]int
	if len(nums) == 0 {
		return result
	}
	used := make([]bool, len(nums))
	temp := []int{}
	helper(nums, used, &result, temp)
	return result
}

func helper(nums []int, used []bool, result *[][]int, temp []int) {
	if len(nums) == len(temp) {
		r := append([]int{}, temp...)
		*result = append(*result, r)
		return
	}

	for i, num := range nums {
		if used[i] {
			continue
		}

		used[i] = true
		temp = append(temp, num)
		helper(nums, used, result, temp)
		temp = temp[:len(temp)-1]
		used[i] = false
	}
}

func Test_46_permutations() {

	var nums = []int{1, 2, 3, 4, 5}
	nums[0], nums[1] = nums[1], nums[0]

	var res [][]int
	c := permute_recursive_1([]int{1, 2, 3}, 0, &res)
	fmt.Println(c)

	a := permute1([]int{1, 2, 3})
	fmt.Println(a)
}
