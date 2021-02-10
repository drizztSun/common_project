"""
1689. Partitioning Into Minimum Number Of Deci-Binary Numbers


A decimal number is called deci-binary if each of its digits is either 0 or 1 without any leading zeros. For example, 101 and 1100 are deci-binary, while 112 and 3001 are not.

Given a string n that represents a positive decimal integer, return the minimum number of positive deci-binary numbers needed so that they sum up to n.

 

Example 1:

Input: n = "32"
Output: 3
Explanation: 10 + 11 + 11 = 32
Example 2:

Input: n = "82734"
Output: 8
Example 3:

Input: n = "27346209830709182346"
Output: 9
 

Constraints:

1 <= n.length <= 10^5
n consists of only digits.
n does not contain any leading zeros and represents a positive integer.


"""


class MinPartitions:

    """
            Overview
        It's an interesting problem that requires a little observation and insight. It's recommended to try a few examples to find out some regular patterns. Below, we will discuss a simple approach to solve this problem.

        Approach 1: Math
        Intuition

        Let's begin with an example number n = "28734". We need to decompose it into several numbers that only include 0 and/or 1, as few as possible. Let's consider two questions.

        The first question is:

        What is the lower bound of our required answer? For this example, can the required answer be less than 8?

        No, for n = "28734", the answer can not be less than 8. Since there is an 8 in 28734 and what we have are only 0 and 1, we need at least eight 1s to add up to 8. In other words, we need at least eight numbers for n = "28734".

        Figure 1.1

        The next question is:

        Can eight numbers work? That is to say, can we make up 28734 with eight numbers that only include 0 and/or 1?

        Yes. Note that if we put 0s in the spare spaces in the above figure, we get eight numbers:

        Figure 1.2

        Each horizontal line represents a number that only includes 0 and/or 1.

        Add those numbers together, and then we have 28734.

        From those two questions, we know that 8 numbers are feasible, and we can not have an answer less than 8. That is to say, 8 is our answer to n = "28734".

        This example gives us an important insight:

        The required minimum number of deci-binary numbers is the max digit in the string n.

        Algorithm

        Return the maximum digit in the string n.

        Challenge: Can you implement the code yourself without seeing our implementations?

        Implementation


        Complexity Analysis

        Let M be the length of string n. If we treat n as an number, then O(M)=O(logn).

        Time Complexity: O(M), since we need to iterate over string n to find out the maximum digit.

        Space Complexity: O(1), since no extra data structure is required. Note that here we do not take the space of input n into account.
    """
    def doit_(self, n: str) -> int:

        return max(int(c) for c in n)
    
    