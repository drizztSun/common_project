'''
Approach 1: Recursion
Intuition

Use recursion to compute the Fibonacci number of a given integer.

Algorithm

Check if the provided input value, N, is less than or equal to 1. If true, return N.

Otherwise, the function fib(int N) calls itself, with the result of the 2 previous numbers being added to each other, passed in as the argument. This is derived directly from the recurrence 
relation: f(n) = f(n-1)+f(n-2)
​	
 

Do this until all numbers have been computed, then return the resulting answer.


'''