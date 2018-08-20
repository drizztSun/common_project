# 805. Split Array With Same Average

# In a given integer array A, we must move every element of A to either list B or list C. (B and C initially start empty.)

# Return true if and only if after such a move, it is possible that the average value of 
# B is equal to the average value of C, and B and C are both non-empty.

# Example :

# Input: 
# [1,2,3,4,5,6,7,8]

# Output: true
# Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have the average of 4.5.

# Note:

# The length of A will be in the range [1, 30].
# A[i] will be in the range of [0, 10000].
 
class SplitArraySameAverage1:

    # <DFS> TLS
    def doit4(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """
        def dfs(i, n, total):
            if n == 0:
                return total == 0
            
            while i < len(A) and total >= A[i] * n:
                if dfs(i+1, n - 1, total - A[i]):
                    return True
                i += 1

            return False

        N, M = len(A), sum(A)
        A.sort()
        for i in range(1, int(N/2) + 1):
            if i * M % N == 0 and dfs(0, i, i * M / N):
                return True

        return False

    # <BFS> almost TLE
    def doit5(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """
        if len(A) < 2:
            return False

        M, N = sum(A), len(A)
        A.sort()
        st = []
        visited = set()

        for v in A:

            extra = []
            for c in st:
                
                v1, v2 = c[0] * M, c[1] * N
                if v1 == v2:
                    return True
                
                if v1 > v2:
                    n = (c[0] + 1, c[1] + v )
                    if n not in visited:
                        extra.append(n)
                        visited.add(n)
            
            if (1, v) not in visited:
                st.append((1, v))
                visited.add((1, v))
                if v * N == M:
                    return True

            st.extend(extra)

        return False


# We split the array into two parts with same size. (call it "left" and "right" subarray)

# Then enumerate every possible combination of two sub-arrays.

# Assume there is a combination of l1 numbers which sum is s1 in the "left subarray". Similarly, a combination of l2 numbers and s2 summary is in the "right subarray". If we concat the two combinations, the average should be: (s1 + s2) / (l1 + l2).

# So, if and only if (s1 + s2) / (l1 + l2) equals the average of the array, we can make the conclusion that we can split the array with equal average, and the average must be equal to the average of the whole array. As a result, if we know s1, l1, then we enumerate l2 (which could as large as 15 at most), and try to find out if there is an available s2.

# The time complexity is O(N * 2^(N / 2)). As N is as large as 30, there is no chance for a TLE.

# The code is a little bit ... nasty. But it works well.                
class Solution(object):
    # Divide and Conquer Solution without DFS
    def splitArraySameAverage(self, A):
        n = len(A)
        
        if n == 1:
            return False
        
        acc = sum(A)
        ave = 1.0 * sum(A) / n
        
        l, r = A[:n / 2], A[n / 2:]
        
        s = set()

        for i in range(1, 1 << len(l)):
            cnt, tot = 0, 0
            for j in range(len(l)):
                if i & (1 << j):
                    cnt += 1
                    tot += l[j]
            s.add((cnt, tot))
            
            if cnt * acc == tot * n:
                return True

        for i in range(1, 1 << len(r)):
            cnt, tot = 0, 0
            for j in range(len(r)):
                if i & (1 << j):
                    cnt += 1
                    tot += r[j]

            if cnt * acc == tot * n:
                return True
            
            for j in range(1, len(l) + 1):
                if j + cnt == n:
                    continue

                if acc * (cnt + j) % n != 0:
                    continue

                b = acc * (cnt + j) / n - tot

                if (j, b) in s:
                    return True

        return False



# Stefan Pochman
class SplitArraySameAverage:
    
    # NumPy with dynamic programming. If B and C have the same average, then that average is also the average of A. Looking at it the other way around,
    # I find out whether there's a subsequence of A with the same average as A. That will then be B and the rest will be C. 
    # So I want the subsequence to be non-empty and not the whole A.

    # Let N and S be the size and sum of A and n and s the size and sum of the subsequence. 
    # So I want S/N == s/n. I go through n ∈ [1,N) and check whether s = S*n/N is an integer and whether there is a subsequence of size n with sum s. 
    # My p[n][s] tells me whether it's possible to build a subsequence of size n with sum s.
    def doit3(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """
        import numpy as np
        N, S = len(A), sum(A)
        p = np.zeros((N, S+1), dtype=bool)
        p[0][0] = 1

        for a in A:
            p[1:, a:] |= np.array(p[:-1, :-a or None])

        return any( S * i % N == 0 and p[i][S*i/N] for i in range(1, N) )

    # An alternative, where I use reversed indexing so I don't have to make a copy of the slice to prevent overwriting it with itself, 
    # and also did the last part in a NumPy way:
    def doit2(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """
        import numpy as np
        S, N = sum(A), len(A)
        P = np.zeros((N, S + 1), dtype=bool)
        P[~0][~0] = 1

        for a in A:
            P[:-1, :-a or None] |= P[1:, a:]

        n = np.arange(1, N)
        s = S * n // N

        return any( (s * N == n * S) & P[~n, ~s] )
        
    # Another alternative, using ints as bitsets to get rid of the N-dimension:
    def doit1(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """
        import numpy as np
        S, N = sum(A), len(A)
        P = np.zeros(S + 1, dtype=int)
        P[~0] = 1

        for a in A:
            P[:-a or None] |= P[a:] << 1

        n = np.arange(1, N)
        s = n * S // N
 
        return any((s * N == n * S) & (P[~s] >> n))

    # Using dynamic programming. Bit n of p[s] tells me whether it’s possible to build a subset of size n with sum s.
    def doit(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """
        N, S = len(A), sum(A)
        P = [1] + [0] * S

        for a in A:
            for s, p in enumerate(P[:-a or None]):
                P[s + a] |= p << 1

        return any( S * n % N == 0 and P[S * n // N] & 1 << n for n in range(1, N))


    # My fastest Python solution so far, gets accepted in about 44 ms (tried five times, took 44, 48, 44, 40 and 44 ms).
    # After using bitset over size N I realized I could do bitset over sum S instead, using Python's big integers.
    # Then almost all action is in Python's C code (for big integers). Which is fast and saves me code.
    def doit4(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """
        N, S, P = len(A), sum(A), [1]

        for a in A:
            P[1:] = [ (p << a) | q for p, q in zip(P, P[1:] + [0])]
        
        return any( n * S % N == 0 and P[n] & (1 << n * S // N )  for n in range(1, N))
        


if __name__ == "__main__":

    res = SplitArraySameAverage().doit1([1,2,3,4,5,6,7,8])

    res = SplitArraySameAverage().doit2([17,5,5,1,14,10,13,1,6])

    res = SplitArraySameAverage().doit3([904,8738,6439,1889,138,5771,8899,5790,662,8402,3074,1844,5926,8720,7159,6793,7402,9466,1282,1748,434,842,22])

    pass    