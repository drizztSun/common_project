# 788. Rotated Digits

# X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X.  
# Each digit must be rotated - we cannot choose to leave it alone.

# A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 
# 2 and 5 rotate to each other; 6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number and become invalid.

# Now given a positive number N, how many numbers X from 1 to N are good?

# Example:
# Input: 10
# Output: 4
# Explanation: 
# There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
# Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
# Note:

# N  will be in range [1, 10000].

class RotatedDigits:

    def doit(self, N):
        valid = {'2','5','6','9'}
        invalid = {'3','4','7'}
        result = 0
        for num in range(2, N+1):
            s = set(str(num))
            if s & invalid:
                continue
            elif s & valid:
                result += 1
        return result

    def doit(self, N):
        s1 = set([0, 1, 8])
        s2 = set([0, 1, 8, 2, 5, 6, 9])
        s = set()
        res = 0
        N = list(map(int, str(N)))
        for i, v in enumerate(N):
            for j in range(v):
                if s.issubset(s2) and j in s2:
                    res += 7**(len(N) - i - 1)
                if s.issubset(s1) and j in s1:
                    res -= 3**(len(N) - i - 1)
            if v not in s2:
                return res
            s.add(v)
        return res + (s.issubset(s2) and not s.issubset(s1))

    def doit(self, N: int) -> int:
        res = 0
        bad = [3, 4, 7]
        good = [2, 5, 6, 9]
        for i in range(1, N+1):
            ok = True
            at_least_one_good = False
            while i:
                i, r = divmod(i, 10)
                if r in bad:
                    ok = False
                    break
                if r in good:
                    at_least_one_good = True
            if ok and at_least_one_good:
                res += 1
        return res

    def doit1(self, N: int) -> int:
        N, t, c = str(N), 0, 1
        L, a, b = len(N) - 1, [1,2,3,3,3,4,5,5,6,7], [1,2,2,2,2,2,2,2,3,3]

        for i in range(L):
            if N[i] == '0':
                continue
            t += a[int(N[i])-1] * 7**(L-i) - c * b[int(N[i])-1] * 3**(L-i)
            if N[i] in '347':
                return t
            if N[i] not in '18':
                c = 0

        return t + a[int(N[-1])] - c * b[int(N[-1])]

    def doit(self, N):

        A = list(map(int, str(N)))
        memo = {}

        def dp(i, equality_flag, involution_flag):
            if i == len(A):
                return + (involution_flag)

            if (i, equality_flag, involution_flag) not in memo:
                ans = 0
                for d in range(A[i] + 1 if equality_flag else 10):
                    if d in {3, 4, 7}: 
                        continue
                    ans += dp(i+1, equality_flag and d == A[i],
                                involution_flag or d in {2, 5, 6, 9})
                memo[i, equality_flag, involution_flag] = ans
            
            return memo[i, equality_flag, involution_flag]

        return dp(0, True, False)

    def doit(self, N):
        smallSet = {0,1,8}
        bigSet = {2,5,6,9}

        smallNum = [0,0,1,1,1,2,3,3,3,4][N % 10]
        bigNum = [1,2,3,3,3,4,5,5,6,7][N % 10]

        N = N // 10
        smInc, bgInc = 4, 7

        while N:
            x = N % 10
            N = N // 10
            sm, bg = 0, 0
            for i in range(x):
                if i in smallSet:
                    sm += smInc
                    bg += bgInc
                elif i in bigSet:
                    sm += bgInc
                    bg += bgInc
            if x in smallSet:
                smallNum += sm
                bigNum += bg
            elif x in bigSet:
                smallNum = bigNum + sm
                bigNum += bg
            else:
                smallNum = sm
                bigNum = bg
            smInc, bgInc = 4*bgInc + 3*smInc, bgInc * 7
        return smallNum


if __name__ == '__main__':

    res = RotatedDigits().doit1(120368) # 4

    pass
