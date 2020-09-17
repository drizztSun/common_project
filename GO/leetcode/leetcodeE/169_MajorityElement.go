package leetcodeE

/*
169. Majority Element

Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

Example 1:

Input: [3,2,3]
Output: 3
Example 2:

Input: [2,2,1,1,1,2,2]
Output: 2
*/


func majorityElement_1(nums []int) int {
	count := 1
	target := nums[0]
	for _, num := range nums[1:] {
		if count == 0 {
			target = num
		}
		if num == target {
			count += 1
		} else {
			count -= 1
		}
	}
	return target
}

func majorityElement_2(nums []int) int {
    
    buf := make(map[int]int, 0)    
    
    for _, c := range nums {
        buf[c]++
        if buf[c] > len(nums) / 2 {
            return c
        }
    }
    
    return 0
}