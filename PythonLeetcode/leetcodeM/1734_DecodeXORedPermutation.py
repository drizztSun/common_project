"""
1720. Decode XORed Array

There is a hidden integer array arr that consists of n non-negative integers.

It was encoded into another integer array encoded of length n - 1, such that encoded[i] = arr[i] XOR arr[i + 1]. For example, if arr = [1,0,2,1], then encoded = [1,2,3].

You are given the encoded array. You are also given an integer first, that is the first element of arr, i.e. arr[0].

Return the original array arr. It can be proved that the answer exists and is unique.



Example 1:

Input: encoded = [1,2,3], first = 1
Output: [1,0,2,1]
Explanation: If arr = [1,0,2,1], then first = 1 and encoded = [1 XOR 0, 0 XOR 2, 2 XOR 1] = [1,2,3]
Example 2:

Input: encoded = [6,2,7,3], first = 4
Output: [4,2,0,7,4]


Constraints:

2 <= n <= 104
encoded.length == n - 1
0 <= encoded[i] <= 10^5
0 <= first <= 10^5
"""


class DecodeXOR:

    def doit_(self, encoded: list, first: int) -> list:
        res = [first] + [0] * len(encoded)
        for i in range(len(encoded)):
            res[i + 1] = res[i] ^ encoded[i]
        return res

    """
        Explanation
        cur means the current decoded element.
        
        For each element we have
        A[i] = res[i] ^ res[i+1]
        A[i] ^ A[i] ^ res[i+1] = res[i] ^ res[i+1] ^ A[i] ^ res[i+1]
        res[i+1] = res[i] ^ A[i]
        
        So we use the conslusion above,
        iterate the input encoded array A,
        update res[i + 1] = res[i] ^ A[i].
        
        
        Complexity
        Time O(n)
        Space O(n)
    """

    def doit_(self, A, first):
        res = [first]
        for a in A:
            res.append(res[-1] ^ a)
        return res

    def doit_(self, A: list, first: int) -> list:
        from itertools import accumulate
        return list(accumulate([first] + A, lambda x, y: x ^ y))


"""
1734. Decode XORed Permutation


There is an integer array perm that is a permutation of the first n positive integers, where n is always odd.

It was encoded into another integer array encoded of length n - 1, such that encoded[i] = perm[i] XOR perm[i + 1]. For example, if perm = [1,3,2], then encoded = [2,1].

Given the encoded array, return the original array perm. It is guaranteed that the answer exists and is unique.



Example 1:

Input: encoded = [3,1]
Output: [1,2,3]
Explanation: If perm = [1,2,3], then encoded = [1 XOR 2,2 XOR 3] = [3,1]
Example 2:

Input: encoded = [6,5,4,6]
Output: [2,4,1,5,3]


Constraints:

3 <= n < 10^5
n is odd.
encoded.length == n - 1


"""


class DecodeXORedPermutation:

    """
        Intuition
        If the first element is determined,
        the whole array can be decoded.
        1720. Decode XORed Array

        But if we enumerate the first element,
        the overall complexity will be O(n^2),
        which will be TLE.

        Explanation
        We make good use of the condition "n is odd" as follow
        a1,(a2,a3),(a4,a5).....,
        making the decoded into pairs.
        a2^a3 = A[1]
        a4^a5 = A[3]
        a6^a7 = A[5]
        ...
        so we can have the result of a2^a2^a3...^an.
        And a1,a2,a3... is a permuatation of 1,2,3,4..n

        so we can have
        a1 = 1^2^3...^n^a2^a2^a3...^an

        Then we can deduct the whole decoded array.

        Complexity
        Time O(n)
        Space O(n)
    """
    def doit_(self, A: list) -> list:
        from functools import reduce
        from itertools import accumulate
        from operator import ixor

        first = reduce(ixor, A[::-2] + list(range(len(A) + 2)))
        return list(accumulate([first] + A, ixor))

    def doit_(self, A: list) -> list:

        a1 = 0
        for i in range(1, len(A) + 2):
            # xor from 1 => n
            a1 ^= i

        for i in range(1, len(A), 2):
            # xor from a2 ^ a3, a4 ^ a5, ..., a5 ^ a6, ... , an-1 ^ an
            a1 ^= A[i]

        res = [a1]
        for c in A:
            res.append(res[-1] ^ c)

        return res
