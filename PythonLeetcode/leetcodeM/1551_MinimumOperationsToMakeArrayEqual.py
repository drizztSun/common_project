"""
1551. Minimum Operations to Make Array Equal


You have an array arr of length n where arr[i] = (2 * i) + 1 for all valid values of i (i.e. 0 <= i < n).

In one operation, you can select two indices x and y where 0 <= x, y < n and subtract 1 from arr[x] and add 1 to arr[y] (i.e. perform arr[x] -=1 and arr[y] += 1). 
The goal is to make all the elements of the array equal. It is guaranteed that all the elements of the array can be made equal using some operations.

Given an integer n, the length of the array. Return the minimum number of operations needed to make all the elements of arr equal.

 

Example 1:

Input: n = 3
Output: 2
Explanation: arr = [1, 3, 5]
First operation choose x = 2 and y = 0, this leads arr to be [2, 3, 4]
In the second operation choose x = 2 and y = 0 again, thus arr = [3, 3, 3].
Example 2:

Input: n = 6
Output: 9
 

Constraints:

1 <= n <= 10^4

"""


class MinimumOperations:

    def doit_(self, n: int) -> int:
        total = sum( 2 * i + 1 for i in range(n))
        ave = total // n
        return sum((2*i+1 - ave) for i in range(n) if (2*i+1) > ave)


    """
        n is odd or even
        like [1, 3, 5, 7, ...]  ave is always n

        n = 10, [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]  => [1, 3, 5, n-1] => (n // 2 items)
        n = 11, [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21] => [2, 4, 6, n-1] => (n // 2 items)

        increasing part (greater than ave) is on the right side, from [n+1, ......., 2*n -1 ]  n//2 items
    """
    def doit_math(self, n: int) -> int:
        return ((n + 1) // 2) * (n // 2)


    def doit_math(self, n: int) -> int:
        
        return n**2 // 4 if n % 2 == 0 else (n**2 - 1) // 4 
