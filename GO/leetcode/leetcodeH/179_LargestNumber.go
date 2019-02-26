package leetcodeH

import (
	"fmt"
	"strconv"
	"strings"
)

/*
179. Largest Number

#Given a list of non negative integers, arrange them such that they form the largest number.

#Example 1:

#Input: [10,2]
#Output: "210"
#Example 2:

#Input: [3,30,34,5,9]
#Output: "9534330"
#Note: The result may be very large, so you need to return a string instead of an integer.

# The main idea is to compare two str(str1+str2 and str2 + str1), and using built-in function sorted to sort list,
#and then produce the result string, but the speed is slow, i guess that sorting step consume much time. Can somebody modify the code to speeding up

*/

func bindAndCompare(a, b string) bool {
	return a+b < b+a
}

func partition(numstr []string, l, h int) int {
	c, j := numstr[l], l+1
	for s := j; s <= h; s++ {
		if bindAndCompare(c, numstr[s]) {
			numstr[j], numstr[s] = numstr[s], numstr[j]
			j++
		}
	}
	numstr[j-1], numstr[l] = numstr[l], numstr[j-1]
	return j - 1
}

func quicksort(numstr []string, l, h int) {
	if l >= h {
		return
	}

	mid := partition(numstr, l, h)
	quicksort(numstr, l, mid-1)
	quicksort(numstr, mid+1, h)
}

func largestNumber(nums []int) string {
	numstr := make([]string, len(nums), len(nums))
	for i := range nums {
		numstr[i] = strconv.Itoa(nums[i])
	}

	quicksort(numstr, 0, len(nums)-1)

	if numstr[0][0] == '0' {
		return "0"
	}

	return strings.Join(numstr, "")
}

func Test_179LargetNumber() {

	fmt.Println(largestNumber([]int{10, 2}))

	fmt.Println(largestNumber([]int{3, 30, 34, 5, 9}))
}
