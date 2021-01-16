"""
402. Remove K Digits

Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.


"""


class RemoveKdigits:

    def doit_stack(self, num, k):
        """
        :type num: str
        :type k: int
        :rtype: str
        """
        res = []
        keep = len(num) - k
        for c in num:
            while k and res and res[-1] > c:
                res.pop()
                k -= 1
            res.append(c)

        res = res[:keep]

        while res and res[0] == '0':
            res.pop(0)

        return '0' if not res else ''.join(res)


    """
        Approach 2: Greedy with Stack

        Intuition
        
        We've got a hint while entertaining the idea of brute-force, that given two sequences of digit of the same length, it is the leftmost distinct digits that determine the superior of the two numbers, e.g. for A = 1axxx, B = 1bxxx, if the digits a > b, then A > B.
        
        With this insight, the first intuition we got for our problem is that we should iterate from the left to right, when removing the digits. The more a digit to the left-hand side, the more weight it carries.
        
        Now that we fix on the order of the iteration, it is critical to come up some criteria on how we eliminate digits, in order to obtain the minimum value.
        
        We demonstrate how the algorithm works in the above graph. Given the input sequence [1, 2, 3, 4, 5, 2, 6, 4] and the number of digits to remove k=4, the rule is triggered for the first time at the digit of 5. Once we remove the digit 5, the rule is triggered again at the digit 4 till the digit 3. And then later, at the digit 6, the rule is triggered as well.

        Out of the above main loop, we need to handle some corner cases to make the solution more complete.
        
        case 1). when we get out of the main loop, we removed m digits, which is less than asked, i.e.(m < k). In the extreme case, we would not remove any digit for the monotonic increasing sequence in the loop, i.e. m==0. In this case, we just need to remove the additional k-m digits from the tail of the sequence.
        
        case 2). once we remove all the k digits from the sequence, there could be some leading zeros left. To format the final number, we need to strip off those leading zeros.
        
        case 3). we might end up removing all numbers from the sequence. In this case, we should return zero, instead of empty string.
        
        Here are some sample implementations.


    """
    def removeKdigits(self, num: str, k: int) -> str:

        numStack = []

        # Construct a monotone increasing sequence of digits
        for digit in num:
            while k and numStack and numStack[-1] > digit:
                numStack.pop()
                k -= 1

            numStack.append(digit)

        # - Trunk the remaining K digits at the end
        # - in the case k==0: return the entire list
        finalStack = numStack[:-k] if k else numStack

        # trip the leading zeros
        return "".join(finalStack).lstrip('0') or "0"