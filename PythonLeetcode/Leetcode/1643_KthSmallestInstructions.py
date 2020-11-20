"""
1643. Kth Smallest Instructions

Bob is standing at cell (0, 0), and he wants to reach destination: (row, column). He can only travel right and down. You are going to help Bob by providing instructions for him to reach destination.

The instructions are represented as a string, where each character is either:

'H', meaning move horizontally (go right), or
'V', meaning move vertically (go down).
Multiple instructions will lead Bob to destination. For example, if destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.

However, Bob is very picky. Bob has a lucky number k, and he wants the kth lexicographically smallest instructions that will lead him to destination. k is 1-indexed.

Given an integer array destination and an integer k, return the kth lexicographically smallest instructions that will take Bob to destination.



Example 1:



Input: destination = [2,3], k = 1
Output: "HHHVV"
Explanation: All the instructions that reach (2, 3) in lexicographic order are as follows:
["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH", "VHVHH", "VVHHH"].
Example 2:



Input: destination = [2,3], k = 2
Output: "HHVHV"
Example 3:



Input: destination = [2,3], k = 3
Output: "HHVVH"


Constraints:

destination.length == 2
1 <= row, column <= 15
1 <= k <= nCr(row + column, row), where nCr(a, b) denotes a choose b.

"""


class KthSmallestPath:

    def doit_dp(self, destination: list, k: int) -> str:

        V, H = destination
        num, res = 0, ''
        v = 0

        def steps(a, b): # step for each (i+1, j)
            res = 1
            for i in range(0, b): # each v step, how many can go to h
                res *= (a-i)
                # h / v will be the ways to go
                res /= i
            return res

        for i in range(V+H):
            s = steps(V + H -i - 1, V - v)
            if num + s >= k: # if v-direct + s > k, we have to go H
                res += 'H'
            else:
                res += 'V'
                num += s
                v += 1

        return res

    def doit_dp_1(self, destination: list, k: int) -> str:
        import math
        def combos(a, b):
            # a choose b
            return int(math.factorial(a) / (math.factorial(b) * math.factorial(a - b)))

        result = []
        vCount, hCount = destination
        k -= 1

        while hCount or vCount:
            # print(k,hCount,vCount)
            if hCount > 0:
                c = combos(hCount - 1 + vCount, hCount - 1)
                # print(" ",c)
                if k < c:
                    result.append("H")
                    hCount -= 1
                else:
                    result.append("V")
                    k -= c
                    vCount -= 1
            else:
                result.append("V")
                vCount -= 1
            # print(" ", k,hCount,vCount,"".join(result))

        return "".join(result)


if __name__ == '__main__':

    KthSmallestPath().doit_dp(destination = [2,3], k = 1)

    KthSmallestPath().doit_dp(destination = [2,3], k = 2)

    KthSmallestPath().doit_dp(destination = [2,3], k = 3)

