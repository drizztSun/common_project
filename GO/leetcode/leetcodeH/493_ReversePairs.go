package leetcodeH

/*
493. Reverse Pairs
*/

import (
	"fmt"
)

func merge(left, right []int) int {
    i, j := 0, 0
    res := 0
    
    for i < len(left) && j < len(right) {
        if left[i] > 2 * right[j] {        
            res += len(left) - i
            j += 1
        } else {
            i += 1
        }
    }
    
    return res
}

func iter(nums []int, s, e int) int {
    if e - s > 1 {
        defer sort.Ints(nums[s:e])
        return iter(nums, s, (s+e)/2) + iter(nums, (s+e)/2, e) + merge(nums[s:(s+e)/2], nums[(s+e)/2:e])
    } else {
        return 0
    }
}

func reversePairs(nums []int) int {
    
    return iter(nums, 0, len(nums))
}

func main() {

	fmt.Println("[1,3,2,3,1] has : ", reversePairs([]int{1,3,2,3,1}))

	fmt.Println("[2,4,3,5,1] has : ", reversePairs([]int{2,4,3,5,1}))

	fmt.Println("[2147483647,2147483647,-2147483647,-2147483647,-2147483647,2147483647] has : " + reversePairs([]int 
		{2147483647,2147483647,-2147483647,-2147483647,-2147483647,2147483647}))
}