# 679. 24 Game

# You have 4 cards each containing a number from 1 to 9.
# You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.

# Example 1:
# Input: [4, 1, 8, 7]
# Output: True
# Explanation: (8-4) * (7-1) = 24

# Example 2:
# Input: [1, 2, 1, 2]
# Output: False

# Note:
# The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
# Every operation done is between two numbers. In particular, we cannot use - as a unary operator.
# For example, with [1, 1, 1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
# You cannot concatenate numbers together. For example, if the input is [1, 2, 1, 2], we cannot write this as 12 + 12.


import math
import itertools


import operator


class JudgePoint24:

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        ops = {'+': operator.add, '-': operator.sub, '*': operator.mul, '/': operator.truediv}
        difference = math.pow(10, -5)

        def search(num):

            if len(num) == 1:

                return abs(num[0] - 24.0) <= difference
            else:

                for i in range(len(num)):
                    for j in range(len(num)):
                        if i == j:
                            continue

                        current = []
                        for z in range(len(num)):
                            if z != i and z != j:
                                current.append(num[z])

                        for k in ops.keys():

                            if (k == '+' or k == '*') and i > j :
                                continue

                            if k == '/' and abs(num[j] - 0.0) <= difference:
                                continue

                            current.append(ops[k](num[i], num[j]))

                            if search(current):
                                return True

                            current.pop()

                return False

        nums = list(map(float, nums))
        return search(nums)


class Solution:
    # There are really only 495 possible inputs, of which 404 are solvable and 91 aren't.
    # The above is the shortest encoding of those 91 that I could think of.
    # One character for each case. The +42921 is for getting all characters from the same unicode range
    # (from the "Hangul Syllables" range) so that it looks good.
    # For extra style points I shuffled them, otherwise they'd look somewhat sorted.
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        bad = '떢븻각걎냇갅갸꺚뵟숣욄뵴뵞뤼갈갌뤔떌옊메늄숭캸긶꺛옖갍뇐쩢곴듇걯궄옕왹눞솴걃끗긬땉궿가쌀낐걄숤뺴늘걘꽸숢걂갋갃쫐꼔솾쩡쇔솿끛뤜간븺쩬웨딴옠뤛갂뵪덠놤빐옋귒늂갰갖놥궾갆옌뼘묰거갎긷낤겼'
        return chr(int(''.join(map(str, sorted(nums)))) + 42921) not in bad
        pass



class Solution1(object):

    def judgePoint24(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        hs = {}
        return self.helper(nums, hs)
    
    def helper(self, nums, hs):
        #print "debug", nums
        if len(nums) == 1:
            if 23.9 <= nums[0] <= 24.1:
                return True
            else:
                return False
        
        nums = sorted(nums)
        if "".join(str(nums) + ",") in hs:
            return False
        
        for i in range(len(nums) - 1):
            for j in range(i + 1, len(nums)):

                a = nums[i]
                b = nums[j]

                if self.helper(nums[:i] + nums[i + 1:j] + nums[j + 1:] + [a + b], hs) == True:
                    return True

                if self.helper(nums[:i] + nums[i + 1:j] + nums[j + 1:] + [a * b], hs) == True:
                    return True

                if b != 0 and self.helper(nums[:i] + nums[i + 1:j] + nums[j + 1:] + [float(a) / b], hs) == True:
                    return True

                if self.helper(nums[:i] + nums[i + 1:j] + nums[j + 1:] + [a - b], hs) == True:
                    return True

                if a != 0 and self.helper(nums[:i] + nums[i + 1:j] + nums[j + 1:] + [float(b) / a], hs) == True:
                    return True

                if self.helper(nums[:i] + nums[i + 1:j] + nums[j + 1:] + [b - a], hs) == True:
                    return True
        
        hs["".join(str(nums) + ",")] = True

        return False


if __name__ == "__main__":

    res = JudgePoint24().doit([4, 1, 8, 7])

    res = JudgePoint24().doit([1, 2, 1, 2])

    res = JudgePoint24().doit([8, 1, 6, 6])

    pass        
