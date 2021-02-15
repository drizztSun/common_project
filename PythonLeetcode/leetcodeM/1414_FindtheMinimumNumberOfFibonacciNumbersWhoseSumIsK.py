"""
1414. Find the Minimum Number of Fibonacci Numbers Whose Sum Is K


Given an integer k, return the minimum number of Fibonacci numbers whose sum is equal to k. The same Fibonacci number can be used multiple times.

The Fibonacci numbers are defined as:

F1 = 1
F2 = 1
Fn = Fn-1 + Fn-2 for n > 2.
It is guaranteed that for the given constraints we can always find such Fibonacci numbers that sum up to k.


Example 1:

Input: k = 7
Output: 2
Explanation: The Fibonacci numbers are: 1, 1, 2, 3, 5, 8, 13, ...
For k = 7 we can use 2 + 5 = 7.
Example 2:

Input: k = 10
Output: 2
Explanation: For k = 10 we can use 2 + 8 = 10.
Example 3:

Input: k = 19
Output: 3
Explanation: For k = 19 we can use 1 + 5 + 13 = 19.


Constraints:

1 <= k <= 10^9

"""


class MinimumNumberOfFibonnacciSum:


    """
        Intuition
        We greedily subtract the biggest Fibonacci number x from k,
        and recursive to find the result for k - x.
        Then f(k) = f(k - x) + 1


        Intuition II
        The feeling seems good,
        but what if the interviewer ask for a prove?

        Well, I can figure this out.
        Will the interviewer really expect the prove during 45min?

        If the interviewer doesn't request it,
        can I ask them for the prove?

        If they cannot even give me a prove,
        why the hell they ask me this question?

        Weak application for the company!


        Prove
        Among all resolution with the minimum number of Fibonacci numbers,
        we are find the lexicographically largest one.
        In this resolution, we must:

        uses each Fibonacci number at most once
        never uses two consecutive Fibonacci numbers
        First
        In best resolution of k,
        there is no two adjacent Fibonacci number.

        This can be easily obtained,
        because if we have fibo[i] + fibo[i+1],
        we can have fibo[i+2] instead,
        and we save one number.


        Second
        In one of the best resolution of k,
        there can be no duplicate Fibonacci number.
        Assume we have two fibo[i].

        I noticed that fibo[i] * 2 = fibo[i - 2] + fibo[i + 1]
        For example
        Assuming fibo = [1,2,3,5,8,13,21,33]
        2 + 2 = 1 + 3
        3 + 3 = 1 + 5
        5 + 5 = 2 + 8
        8 + 8 = 3 + 13
        13 + 13 = 5 + 21
        21 + 21 = 8 + 33

        If we have two same number,
        we can always transfor to two different number.

        Don't need worrying about if this process will cause other duplicate.
        We clear the duplicate from the small to big.


        Third
        If no dup, no adjacent, we must take the biggest.
        fibo[0] + fibo[2] + fibo[4] + ... + fibo[2n] = fibo[2n + 1] - 1
        fibo[1] + fibo[3] + fibo[5] + .... + fibo[2n-1] = fibo[2n] - 1

        For example:
        1 = 2 - 1
        1 + 3 = 5 - 1
        1 + 3 + 8 = 13 - 1
        1 + 3 + 8 + 21 = 34 - 1

        2 = 3 - 1
        2 + 5 = 8 - 1
        2 + 5 + 13 = 21 - 1
        2 + 5 + 13 + 34 = 55 - 1

        So if k >= fibo[2n],
        and we don't take fibo[2n]
        the rest sum of every two Fibo numbers can only reach a maximum fibo[2n] - 1

        The same for the case where k >= fibo[2n + 1]


        @OneSheep supported a supplement explanation here:
        If we use [1,1,2,3,5,8,13,21,34].

        f[2n+1]
        =f[2n]+f[2n-1]
        =f[2n]+f[2n-2]+f[2n-3]
        =f[2n]+f[2n-2]+...+f[6]+f[5]
        =...+f[6]+f[4]+f[3]
        =...+f[6]+f[4]+f[2]+f[1]
        =...+f[6]+f[4]+f[2]+f[0] (because f[0]==f[1])

        f[2n]
        =f[2n-1]+f[2n-2]
        =f[2n-1]+f[2n-3]+f[2n-4]
        =...+f[5]+f[4]
        =...+f[5]+f[3]+f[2]
        =...+f[5]+f[3]+f[1]+f[0]


        Solution 1: Recursion
        Time O((logk)^2), since O(log k) Fibonacci numbers smaller than k.
        Space O(logK), can be saved by tail recursion.
    """
    def doit_recursive(self, k):
        def search(k):
            if k < 2: return k
            a, b = 1, 1
            while b <= k:
                a, b = b, a + b
            return search(k - a) + 1

        return search(k)


    """
        Solution 2: Iteration
        Time O(logk)
        Space O(1)
        Python:
    """
    def doit_greedy(self, k):
        res, a, b = 0, 1, 1
        while b <= k:
            a, b = b, a + b
        while a > 0:
            if a <= k:
                k -= a
                res += 1
            a, b = b - a, a
        return res