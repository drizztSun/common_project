package leetcodem

/*
300. Longest Increasing Subsequence

Given an unsorted array of integers, find the length of longest increasing subsequence.

Example:

Input: [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
Note:

There may be more than one LIS combination, it is only necessary for you to return the length.
Your algorithm should run in O(n2) complexity.
Follow up: Could you improve it to O(n log n) time complexity?


*/

/*
   Approach 4: Dynamic Programming with Binary Search
   Algorithm

   In this approach, we scan the array from left to right. We also make use of a dp array initialized with all 0's.
   This dp array is meant to store the increasing subsequence formed by including the currently encountered element. While traversing the nums array,
   we keep on filling the dp array with the elements encountered so far.

   For the element corresponding to the j th index (nums[j]), we determine its correct position in the dp array(say i^{th} by making use of
   Binary Search(which can be used since the dp array is storing increasing subsequence) and also insert it at the correct position.

   An important point to be noted is that for Binary Search, we consider only that portion of the dp array in which we have made the updates
   by inserting some elements at their correct positions(which remains always sorted). Thus, only the elements up to the i^{th}i th
     index in the dpdp array can determine the position of the current element in it. Since, the element enters its correct position(ii) in an ascending order
     in the dpdp array, the subsequence formed so far in it is surely an increasing subsequence. Whenever this position index ii becomes equal to the length of the LIS formed so far(lenlen),
     it means, we need to update the lenlen as len = len + 1len=len+1.

   Note: dpdp array does not result in longest increasing subsequence, but length of dpdp array will give you length of LIS.

   Consider the example:

   input: [0, 8, 4, 7, 12, 2]

   dp: [0]

   dp: [0, 8]

   dp: [0, 4, 7]

   dp: [0, 4, 7, 12]

   dp: [0 , 2, 7, 12] which is not the longest increasing subsequence, but length of dp array results in length of Longest Increasing Subsequence.

   Note: Arrays.binarySearch() method returns index of the search key, if it is contained in the array, else it returns (-(insertion point) - 1).
   The insertion point is the point at which the key would be inserted into the array: the index of the first element greater than the key,
   or a.length if all elements in the array are less than the specified key.

   Complexity Analysis

   Time complexity : O(nlogn). Binary search takes nlogn time and it is called nn times.

   Space complexity : O(n). dpdp array of size nn is used.
*/
func lengthOfLIS_dp_binary_search(nums []int) int {

	if len(nums) == 0 {
		return 0
	}

	help := func(d []int, cur int) int {

		s, e := 0, len(d)

		for s <= e {

			m := (s + e) / 2
			if d[m] >= cur {
				e = m - 1
			} else {
				s = m + 1
			}
		}

		return s
	}

	dp := []int{nums[0]}

	for _, c := range nums {

		if dp[len(dp)-1] < c {
			dp = append(dp, c)
		} else {
			dp[help(dp, c)] = c
		}
	}

	return len(dp)
}
