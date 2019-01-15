package leetcodeH

import (
	"fmt"
)

/*

659. Split Array into Consecutive Subsequences

You are given an integer array sorted in ascending order (may contain duplicates), you need to split them into several subsequences, where each subsequences consist of at least 3 consecutive integers. Return whether you can make such a split.

Example 1:
Input: [1,2,3,3,4,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 
1, 2, 3
3, 4, 5

Example 2:
Input: [1,2,3,3,4,4,5,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 
1, 2, 3, 4, 5
3, 4, 5

Example 3:
Input: [1,2,3,4,4,5]
Output: False

*/

func isPossible(nums []int) bool {
    
    left := make(map[int] int)
	end := make(map[int]int)
	
	for i := range nums {
		if _, ok := left[nums[i]]; !ok {
			left[nums[i]] = 0
		}
		left[nums[i]] ++
 	}
	
	for i := range nums {
		
		if left[nums[i]] == 0 {
			continue
		}
		
		left[nums[i]]--
		
		if end[nums[i] - 1] > 0 {
			end[nums[i] - 1]--
			end[nums[i]]++
		} else if left[nums[i] + 1] > 0 && left[nums[i] + 2] > 0 {
			left[nums[i] + 1]--
			left[nums[i] + 2]--
			end[nums[i]+2]++
		} else {
			return false
		}
	}
	
	return true
}