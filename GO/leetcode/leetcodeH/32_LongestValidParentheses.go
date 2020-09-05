package leetcodeH

/*

32. Longest Valid Parentheses

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Example 1:

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"



# My solution uses DP.
# The main idea is as follows: I construct a array <b>longest[]</b>, for any longest[i], it stores the longest length of valid parentheses which is end at i.
# And the DP idea is :
# If s[i] is ‘(’, set longest[i] to 0,because any string end with ‘(’ cannot be a valid one.
# Else if s[i] is ‘)’
#    If s[i-1] is ‘(’, longest[i] = longest[i-2] + 2
#    Else if s[i-1] is ‘)’ and s[i-longest[i-1]-1] == ‘(’, longest[i] = longest[i-1] + 2 + longest[i-longest[i-1]-2]
# For example, input “()(())”, at i = 5, longest array is [0,2,0,0,2,0], longest[5] = longest[4] + 2 + longest[1] = 6.
#

*/

// (DP)
func longestValidParentheses_dp(s string) int {
	N := len(s)
	dp := make([]int, N)
	res := 0

	for i := 1; i < N; i++ {
		dp[i] = 0

		if s[i] == ')' {
			if s[i-1] == '(' {
				dp[i] += 2
				if i-1 > 0 {
					dp[i] += dp[i-2]
				}
			} else if i-dp[i-1] > 0 && s[i-dp[i-1]-1] == '(' {
				dp[i] += 2 + dp[i-1]
				if i-dp[i-1]-1 > 0 {
					dp[i] += dp[i-dp[i-1]-2]
				}
			}
		}

		if res < dp[i] {
			res = dp[i]
		}
	}

	return res
}

/*
Approach 3: Using Stack
Algorithm

Instead of finding every possible string and checking its validity, we can make use of stack while scanning the given string to check if the string scanned so far is valid, and also the length of the longest valid string.
In order to do so, we start by pushing -1−1 onto the stack.

For every \text{‘(’}‘(’ encountered, we push its index onto the stack.

For every \text{‘)’}‘)’ encountered, we pop the topmost element and subtract the current element's index from the top element of the stack, which gives the length of the currently encountered valid string of parentheses.
If while popping the element, the stack becomes empty, we push the current element's index onto the stack. In this way, we keep on calculating the lengths of the valid substrings, and return the length of the longest valid string at the end.

See this example for better understanding.
Complexity Analysis

Time complexity : O(n). nn is the length of the given string..

Space complexity : O(n). The size of stack can go up to nn.

*/
func longestValidParentheses_stack(s string) int {

	st, max_len := []int{-1}, 0

	for i := 0; i < len(s); i++ {

		if s[i] == '(' {
			st = append(st, i)
		} else {
			st = st[:len(st)-1]
			if len(st) == 0 {
				st = append(st, i)
			} else if max_len < i-st[len(st)-1] {
				max_len = i - st[len(st)-1]
			}
		}
	}

	return max_len
}

/*

Approach 4: Without extra space
Algorithm

In this approach, we make use of two counters left and right.
First, we start traversing the string from the left towards the right and for every ‘(’ encountered, we increment the left counter and for every ‘)’ encountered, we increment the right counter.
Whenever left becomes equal to right, we calculate the length of the current valid string and keep track of maximum length substring found so far.
If right becomes greater than left we reset left and right to 0.

Next, we start traversing the string from right to left and similar procedure is applied.

Example of this approach:
*/
func longestValidParentheses_(s string) int {

	left, right := 0, 0
	maxLen := 0

	for i := 0; i < len(s); i++ {
		if s[i] == '(' {
			left++
		} else {
			right++
		}

		if left == right && maxLen < 2*right {
			maxLen = 2 * right
		} else if right > left {
			left, right = 0, 0
		}
	}

	left, right = 0, 0
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] == '(' {
			left++
		} else {
			right++
		}
		if left == right && maxLen < 2*right {
			maxLen = 2 * right
		} else if left > right {
			left, right = 0, 0
		}
	}

	return maxLen
}
