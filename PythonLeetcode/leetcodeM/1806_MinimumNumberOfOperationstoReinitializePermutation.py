""""
1806. Minimum Number of Operations to Reinitialize a Permutation


You are given an even integer n. You initially have a permutation perm of size n where perm[i] == i (0-indexed).

In one operation, you will create a new array arr, and for each i:

If i % 2 == 0, then arr[i] = perm[i / 2].
If i % 2 == 1, then arr[i] = perm[n / 2 + (i - 1) / 2].
You will then assign arr to perm.

Return the minimum non-zero number of operations you need to perform on perm to return the permutation to its initial value.



Example 1:

Input: n = 2
Output: 1
Explanation: prem = [0,1] initially.
After the 1st operation, prem = [0,1]
So it takes only 1 operation.
Example 2:

Input: n = 4
Output: 2
Explanation: prem = [0,1,2,3] initially.
After the 1st operation, prem = [0,2,1,3]
After the 2nd operation, prem = [0,1,2,3]
So it takes only 2 operations.
Example 3:

Input: n = 6
Output: 4


Constraints:

2 <= n <= 1000
n is even.

"""


class MinimumOperationsToReInit:

    """
        Here is the solution you are waiting for.
        You need to follow the solution one by one.
        Let me add more explanation meanwhile.


        Solution 1: Simulate the whole array
        Just do what the statements says,
        and compare if it equals to the initial state.

        At most n permuation in the process,
        each list is size of n.

        I don't give the prove here for the above analysis,
        bacause it's not my point in this post.
        The prove is obvious if you get the last soluiton.

        Time O(n^2)
        Space O(n)

    """
    def doit_(self, n):

        A, init = range(n), range(n)
        res = 0

        while res == 0 or A != init:

            A = [A[i//2] if i % 2 == 0 else A[n//2 + (i-1)//2] for i in range(n)]

            res += 1

        return res


    """
        Solution 2: Simulation an index
        Find the inverse path of i.
        
        Time O(1)
        Space O(n)
    """
    def doit_(self, n):
        res, i = 0, 1
        while res == 0 or i > 1:
            if i < n / 2:
                i *= 2
            else:
                i = (i - n / 2) * 2 + 1
            res += 1
        return res

    """
        Solution 3: Simulation an index again
        We can find that we are keep doing i *= 2 each time,
        and we mod n - 1 actually.
        So there won't be duplicate loop.
        
        Time O(1)
        Space O()
    """
    def doit_(self, n):
        res, i = 0, 1
        while res == 0 or i > 1:
            i = i * 2 % (n - 1)
            res += 1
        return res