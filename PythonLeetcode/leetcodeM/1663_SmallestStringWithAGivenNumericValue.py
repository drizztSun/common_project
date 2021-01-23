"""
1663. Smallest String With A Given Numeric Value

The numeric value of a lowercase character is defined as its position (1-indexed) in the alphabet, so the numeric value of a is 1, the numeric value of b is 2, the numeric value of c is 3, and so on.

The numeric value of a string consisting of lowercase characters is defined as the sum of its characters' numeric values. For example, the numeric value of the string "abe" is equal to 1 + 2 + 5 = 8.

You are given two integers n and k. Return the lexicographically smallest string with length equal to n and numeric value equal to k.

Note that a string x is lexicographically smaller than string y if x comes before y in dictionary order, that is, either x is a prefix of y, or if i is the first position such that x[i] != y[i], then x[i] comes before y[i] in alphabetic order.

 

Example 1:

Input: n = 3, k = 27
Output: "aay"
Explanation: The numeric value of the string is 1 + 1 + 25 = 27, and it is the smallest string with such a value and length equal to 3.
Example 2:

Input: n = 5, k = 73
Output: "aaszz"
 

Constraints:

1 <= n <= 10^5
n <= k <= 26 * n



Solution
Overview
We have to build a string of length nn that consists of English lowercase characters a-z by ensuring that following conditions are satisfied,

The numeric value of a string must be equal to a given value kk. The numeric value of a string is equal to the sum of numeric values of all its characters. 

The numeric value of alphabet characters ranges from 11 to 2626, where value of a = 1a=1, b=2b=2 and so on.

The string must be lexicographically smallest string. In other words, we must build a string that would be the smallest in its dictionary order for a given numeric value.
The value of kk would be at least nn. If k = nk=n, the numeric value of every position would be 11 (a).

Example: if n = 3 and k = 3, result would be aaa.

The value of kk would be at most (n * 26)(n∗26). If k = (n*26)k=(n∗26), the numeric value of every position would be 2626 (z).

Example: if n = 3 and k = 78 (3 * 26) , result would be zzz.

Based on these insights, let's implement the solution using different approaches.

"""


class GetSmallestString:
    
    """
        // Greedy: for each index from 1 to n, find the smallest character could be inserted.
        // The smallest possible character can be found in this way:
        // 1) Find the value of 26*(n - i) and k - accumulate_sum_so_far, saying n1 and n2.
        // 2) if (n2 - n1) <= 1, we can insert 'a' in current position.
        // 3) Otherwise the smallest possible character would be 'a' + (n2 - n1) - 1.

    """
    def doit_greedy(self, n: int, k: int) -> str:

        acc = 0
        res = ''
        for i in range(1, n+1):
            
            n1 = 26*(n - i) # How about the rest all use 'zzz****'
            n2 = k - acc # How many is the left
            
            if n2 - n1 <= 1: # if n2 <= n1 + 1, it means the rest is not enough to build 'zzzzz', we can do 'a'
                res += 'a'
                acc += 1
            else:
                res += chr(ord('a') + n2 - n1 - 1) # if the res is so much, we can do more than that, 'b~z', and than 'zzzzzz'.
                acc += n2 - n1
                
        return res