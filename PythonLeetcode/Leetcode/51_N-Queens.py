import os
import math
import cmath


# 51. N-Queens
# The n-queens puzzle is the problem of placing n queens on an n�n chessboard such that no two queens attack each other.
# Given an integer n, return all distinct solutions to the n-queens puzzle.
# Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

# For example,
# There exist two distinct solutions to the 4-queens puzzle:

# [
# [".Q..",  // Solution 1
#  "...Q",
#  "Q...",
#  "..Q."],

# ["..Q.",  // Solution 2
#  "Q...",
#  "...Q",
#  ".Q.."]
# ]


class solveNQueens:


    def doit(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        def checkPos(position, k):
            i, pos, res = 0, position[k], 1
            while i <= k - 1:
                if abs(position[i] - pos) == abs(i - k) or position[i] == pos:
                    res = 0
                i += 1

            return 2 if k == len(position)-1 else 1
        
        # 
        position, result = [-1 for x in range(n)], []
        k = 0

        while k >= 0:

            while position[k] < n - 1:

                position[k] += 1
                res = checkPos(position, k)

                if res == 1:
                    k += 1
                    continue

                elif res == 2:
                    temp, j = [], 0
                    while j < n:
                        queen = ['.']*n
                        queen[position[j]] = 'Q'
                        temp.append(''.join(map(str, queen[:])))
                        j += 1
                    result.append(temp)
                    break
                else:
                    continue

            position[k] = -1
            k -= 1

        return result

    def doit1(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        def isValid(D, n):
            j = 0
            while j < n:
                if D[j] == D[n] or abs(D[j]- D[n]) == abs(j - n):
                    return False
                j += 1

            return True

        D = [-1] * n
        i, D[0] = 0, -1
        rtv = []

        while i >= 0:

            while i < n and D[i] < n-1:
                D[i] += 1

                if isValid(D, i):
                    i += 1
                    continue

            if i >= n:
                res = []
                for num in D:
                    tmp = ['.'] * n
                    tmp[num] = 'Q'
                    res.append(''.join(tmp))
                rtv.append(res)

            elif D[i] == n-1:
                D[i] = -1

            i -= 1

        return rtv

    # Fartest one
    def doit2(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        results = []
        sol = [0]*n
        rows_av = [True] * n
        diag1_av = [True] * (2*n-1)
        diag2_av = [True] * (2*n-1)
        
        def printSol():
            results.append(["."*i+"Q"+"."*(n-i-1) for i in sol])
        
        def util(start):
            if start>=n:
                results.append(["."*i+"Q"+"."*(n-i-1) for i in sol])
                return

            for j in range(n):
                if rows_av[j] and diag1_av[n-1+start-j] and diag2_av[start+j]:

                    sol[start] = j

                    rows_av[j] = diag1_av[n-1+start-j] = diag2_av[start+j] = False

                    util(start + 1)

                    rows_av[j] = diag1_av[n-1+start-j] = diag2_av[start+j] = True
        util(0)

        return results 

    def doit4(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        def DFS(queens, xy_dif, xy_sum):
            p = len(queens)
            if p==n:
                result.append(queens)
                return None

            for q in range(n):
                if q not in queens and p-q not in xy_dif and p+q not in xy_sum: 
                    DFS(queens+[q], xy_dif+[p-q], xy_sum+[p+q])  
 
        result = []

        DFS([],[],[])

        return [ ["."*i + "Q" + "."*(n-i-1) for i in sol] for sol in result]

         
# 52. N-Queens II
# Follow up for N-Queens problem.
# Now, instead outputting board configurations, return the total number of distinct solutions.        
class totalNQueens:
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        def isValid(D, n):
            j = 0
            while j < n:
                if D[j] == D[n] or abs(D[j]- D[n]) == abs(j - n):
                    return False
                j += 1

            return True

        D = [-1] * n
        i, D[0] = 0, -1
        rtv = 0

        while i >= 0:

            while i < n and D[i] < n-1:
                D[i] += 1

                if isValid(D, i):
                    i += 1
                    continue

            if i >= n:
                rtv += 1
            elif D[i] == n-1:
                D[i] = -1

            i -= 1

        return rtv

if __name__=="__main__":
    

    res = solveNQueens().doit(4)


    pass