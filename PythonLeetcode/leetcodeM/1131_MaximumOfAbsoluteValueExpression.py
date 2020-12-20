"""
1131. Maximum of Absolute Value Expression

Given two arrays of integers with equal lengths, return the maximum value of:

|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|

where the maximum is taken over all 0 <= i, j < arr1.length.



Example 1:

Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
Output: 13
Example 2:

Input: arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
Output: 20


Constraints:

2 <= arr1.length == arr2.length <= 40000
-10^6 <= arr1[i], arr2[i] <= 10^6
"""


class MaximumAbsoluteValueExpressions:

    """
    First thing we can notice is that we don't have to worry about the absolute
    value sign on i - j, since if we swapped i and j, we would get the same
    sum. This is because the values inside the absolute value would be negated,
    leaving the absolute value unchanged. From here we will assume i ≥ j.

    In the hint it says:

    Use the idea that abs(A) + abs(B) = max(A+B, A-B, -A+B, -A-B).

    This is a great insight and we can make use of it to get an O(n) solution; much
    better than the naiive O(n2) solution of checking every pair.

    Now we know that our result will be the maximum of

     (arr1[i] - arr1[j]) + (arr2[i] - arr2[j]) + (i - j)
     (arr1[i] - arr1[j]) - (arr2[i] - arr2[j]) + (i - j)
    -(arr1[i] - arr1[j]) + (arr2[i] - arr2[j]) + (i - j)
    -(arr1[i] - arr1[j]) - (arr2[i] - arr2[j]) + (i - j)
    We can remove the brackets and multiply out the signs to get

     arr1[i] - arr1[j] + arr2[i] - arr2[j] + i - j
     arr1[i] - arr1[j] - arr2[i] + arr2[j] + i - j
    -arr1[i] + arr1[j] + arr2[i] - arr2[j] + i - j
    -arr1[i] + arr1[j] - arr2[i] + arr2[j] + i - j
    If we collect the terms with i and the terms with j, we get

     (arr1[i] + arr2[i] + i) - (arr1[j] + arr2[j] + j)
     (arr1[i] - arr2[i] + i) - (arr1[j] - arr2[j] + j)
    (-arr1[i] + arr2[i] + i) - (-arr1[j] + arr2[j] + j)
    (-arr1[i] - arr2[i] + i) - (-arr1[j] - arr2[j] + j)
    Now, all the i terms and the j terms have the same form, just with different
    signs. We can define this form as a cost function:

    def cost(i, sign1, sign2):
      return sign1 * arr1[i] + sign2 * arr2[i] + i

    The maximum difference in costs for each pair of signs will just be the maximum
    cost, minus the minimum cost for those signs. Therefore the total maximum will
    be the maximum over all possible combinations of signs:

    def helper(sign1, sign2, arr1, arr2):
      minSoFar = float('inf')
      maxSoFar = float('-inf')

      for i in range(len(arr1)):
        cost = sign1 * arr1[i] + sign2 * arr2[i] + i
        minSoFar = min(minSoFar, cost)
        maxSoFar = max(maxSoFar, cost)

      return maxSoFar - minSoFar

    def maxAbsValExpr(arr1, arr2):
      return max(
        self.helper(sign1, sign2, arr1, arr2)
        for sign1, sign2 in [(1,1), (1,-1), (-1,1), (-1, -1)]
      )

    The helper method runs in O(n) time, and we run it four times, giving us a
    total runtime complexity of O(n). We do not need any extra space except for the
    local variables in helper, and the overheads for running max, the generator
    inside it, and the helper method itself, giving us O(1) space complexity.
    """
    def doit_math(self, arr1: list, arr2: list) -> int:

        def helper(sig1, sig2):

            minv, maxv = float('inf'), float('-inf')

            for i, a1, a2 in enumerate(zip(arr1, arr2)):

                total = i + sig1 * a1 + sig2 * a2

                maxv = max(total, maxv)
                minv = min(minv, total)

            return maxv - mnv

        return max(helper(s1, s2) for s1, s2 in ((1, 1), (-1, 1), (1, -1), (-1, -1)))

    def doit_(self, arr1: list, arr2: list) -> int:
        one = []
        two = []
        three = []
        four = []
        for i, (x, y) in enumerate(zip(arr1, arr2)):
            one.append(x + y + i)
            two.append(x + y - i)
            three.append(x - y - i)
            four.append(x - y + i)
        res = 0
        res = max(res, max(one) - min(one))
        res = max(res, max(two) - min(two))
        res = max(res, max(three) - min(three))
        res = max(res, max(four) - min(four))
        return res



