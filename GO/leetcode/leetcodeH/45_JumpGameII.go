package leetcodeH

/*
45. Jump Game II

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

Example:

Input: [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
    Jump 1 step from index 0 to 1, then 3 steps to the last index.
Note:

You can assume that you can always reach the last index.
*/

func jumpGameII_1(nums []int) int {

	if len(nums) < 2 {
		return 0
	}

	i := 0
	left, right := 0, nums[0]
	mv, cnt := right, 0

	for right < len(nums)-1 {

		for i < right {
			i++

			if i+nums[i] > mv {
				mv = i + nums[i]
				left = i
				if mv >= len(nums)-1 {
					break
				}
			}
		}
		cnt++
		right, i = mv, left
	}

    if right >= len(nums) - 1  {
        return cnt + 1
    }
	return 0
}

func jumpGameII_2(nums []int) int {

	if len(nums) < 2 {
		return 0
	}

	i := 0
	currentMax, nextMax := 0, 0
	cnt := 0

	for currentMax-i+1 > 0 {

		cnt++

		for ; i <= currentMax; i++ {

			if i+nums[i] > nextMax {
				nextMax = i + nums[i]

				if nextMax >= len(nums)-1 {
					return cnt
				}
			}
		}

		currentMax = nextMax
	}

	return 0
}

func Test_45_jumpgameII() {

	jumpGameII_1([]int{2, 3, 1, 1, 4})

	jumpGameII_1([]int{3, 4, 3, 1, 0, 7, 0, 3, 0, 2, 0, 3})
}
