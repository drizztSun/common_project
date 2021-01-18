"""
241. Different Ways to Add Parentheses

Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1:

Input: "2-1-1"
Output: [0, 2]
Explanation:
((2-1)-1) = 0
(2-(1-1)) = 2

Example 2:

Input: "2*3-4*5"
Output: [-34, -14, -10, -10, 10]
Explanation:
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
"""


class DiffWaysToCompute:

    def doit_devide_and_conquor(self, input):

        def cal(formula, seen):

            if formula.isdigit():
                return [int(formula)]

            if formula in seen:
                return seen[formula]

            res = []
            for i, c in enumerate(formula):
                if c in ('+', '-', '*'):
                    res1 = cal(formula[:i], seen)
                    res2 = cal(formula[i + 1:], seen)

                    for r1 in res1:
                        for r2 in res2:
                            if c == '+':
                                res.append(r1 + r2)
                            elif c == '*':
                                res.append(r1 * r2)
                            elif c == '-':
                                res.append(r1 - r2)

            seen[formula] = res
            return res

        return cal(input, {})

    def doit_devide_and_conquor_1(self, input: str) -> list:

        def ops(os, n1, n2):
            return {
                '+': n1 + n2,
                '-': n1 - n2,
                '*': n1 * n2
            }.get(os, 0)

        def dp(nums, seen):

            if nums in seen:
                return seen[nums]

            res = []
            for i, val in enumerate(nums):
                if nums[i] in ('*', '+', '-'):
                    res1 = dp(nums[:i], seen)
                    res2 = dp(nums[i + 1:], seen)

                    for n1 in res1:
                        res.extend([ops(nums[i], n1, n2) for n2 in res2])

            if not res:
                res.append(int(nums))

            seen[nums] = res

            return res

        return dp(input, {})
