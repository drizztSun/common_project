import os

try:
    from Queue import Queue
except:
    from multiprocessing import Queue

#97. Interleaving String

#Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

#For example,
#Given:
#s1 = "aabcc",
#s2 = "dbbca",

#When s3 = "aadbbcbcac", return true.
#When s3 = "aadbbbaccc", return false.


class isInterleave(object):
    def doit(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        r1, r2, r3 = len(s1), len(s2), len(s3)

        if r1 + r2 != r3:
            return False

        D = [[False for _ in range(r1+1)] for _ in range(r2+1)]
        D[0][0] = True

        for i in range(1, r1+1):
            D[0][i] = D[0][i-1] and s1[i-1] == s3[i-1]

        for j in range(1, r2+1):
            D[j][0] = D[j-1][0] and s2[j-1] == s3[j-1]


        for j in range(1, r2+1):

            for i in range(1, r1+1):

                D[j][i] = D[j-1][i] and s2[j-1] == s3[i+j-1] or D[j][i-1] and s1[i-1] == s3[i+j-1]


        return D[-1][-1]


        
    def doit3(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        r1, r2, r3 = len(s1), len(s2), len(s3)

        if r1 + r2 != r3:
            return False

        dp = [False for _ in range(r3+1)]
        dp[0] = True

        for i in range(1, r2+1):
            dp[i] = dp[i-1] and s2[i-1] == s3[i-1]

        for j in range(1, r1+1):
            tmp = dp[j-1 : j + r2]

            dp[j] = dp[j-1] and s1[j-1] == s3[j-1]
            
            for i in range(1, r2+1):

                dp[i+j] = (dp[i+j-1] and s2[i-1] == s3[i-1+j] ) or (tmp[i] and s1[j-1] == s3[i-1+j])

        return dp[-1]
                    

    def doit2(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        def search(s1, i, s2, j, s3, z, record):

            if i == len(s1) and j == len(s2) and z == len(s3):
                return True

            if (i, j) in record:
                return record[(i, j)]

            res = False
            if i  < len(s1) and z < len(s3) and s1[i] == s3[z]:
                res = search(s1, i+1, s2, j, s3, z+1)
                

            if j < len(s2) and z < len(s3) and s3[z] == s2[j]:
                res = res or search(s1, i, s2, j+1, s3, z+1)

            record[(i, j)] = res
            return res

        if len(s1) + len(s2) != len(s3):
            return False

        return search(s1, 0, s2, 0, s3, 0, {})

    # DFS 
    def doit4(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        r1, r2, r3 = len(s1), len(s2), len(s3)
        if r1 + r2 != r3:
            return False
        
        buff, visited = [(0, 0)], set((0,0)) 

        while buff:
            x, y = buff.pop()
            if x + y == r3:
                return True

            if x + 1 <= r1 and s1[x] == s3[x+y] and (x+1, y) not in visited:
                buff.append((x+1, y))
                visited.add((x+1, y))

            if y + 1 <= r2 and s2[y] == s3[x+y] and (x, y+1) not in visited:
                buff.append((x, y+1))
                visited.add((x, y+1))

        return False

    # BFS
    def doit5(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        r1, r2, r3 = len(s1), len(s2), len(s3)
        if r1 + r2 != r3:
            return False

        steps, overlooks = [(0,0)], set((0, 0))

        while steps:
            x, y = steps.pop(0)
            if x + y == r3:
                return True
    
            if x + 1 <= r1 and s1[x] == s3[x+y] and (x+1, y) not in overlooks:
                steps.append((x+1, y))
                overlooks.add((x+1, y))

            if y + 1 <= r2 and s2[y] == s3[x+y] and (x, y+1) not in overlooks:
                steps.append((x, y+1))
                overlooks.add((x, y+1))

        return False

if __name__=="__main__":

    res = isInterleave().doit3("a", "b", "ab")

    res = isInterleave().doit3("aabcc", "dbbca", "aadbbcbcac")

    res = isInterleave().doit3("aabcc", "dbbca", "aadbbbaccc")

    res = isInterleave().doit5("", "b", "b")

    res = isInterleave().doit3("aa", "ab", "aaba")

    pass