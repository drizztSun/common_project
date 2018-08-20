# 854. K-Similar Strings

# Strings A and B are K-similar (for some non-negative integer K) 
# if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.

# Given two anagrams A and B, return the smallest K for which A and B are K-similar.

# Example 1:

# Input: A = "ab", B = "ba"
# Output: 1
# Example 2:

# Input: A = "abc", B = "bca"
# Output: 2
# Example 3:

# Input: A = "abac", B = "baca"
# Output: 2
# Example 4:

# Input: A = "aabc", B = "abca"
# Output: 2
# Note:

# 1 <= A.length == B.length <= 20
# A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}

from collections import defaultdict, deque


class kSimilarity:

    # dfs
    def doit1(self, A, B):
        """
        :type A: str
        :type B: str
        :rtype: int
        """
        A, B = list(A), list(B)
        def search(a, b, pos):
            
            for i in range(pos, len(A)):
                if A[i] == B[i]:
                    continue
            
                match = []
                for j in range(i+1, len(A)):
                    if A[j] == B[i] and A[j] != B[j]:
                        match.append(j)

                        if A[i] == B[j]:
                            A[i], A[j] = A[j], A[i]
                            return 1 + search(i + 1)

                best = len(A) - 1
                for j in match:
                    A[i], A[j] = A[j], A[i]
                    best = min(best, 1 + search(i+1))
                    A[i], A[j] = A[j], A[i]

                return best

            return 0

        return search(a, b, 0)
            
    # bfs
    def doit(self, A, B):
        """
        :type A: str
        :type B: str
        :rtype: int
        """
        pos = defaultdict(list)
        for i in range(len(B)):
            pos[B[i]].append(i)
        
        qu = deque()
        qu.append((A, 0));

        while qu:

            t, d = qu.popleft()
            if t == B:
                return d

            i = 0
            while i < len(B) and t[i] == B[i]:
                i += 1

            for j in pos[t[i]]:

                if t[j] != B[j]:
                    c = t[:i] + t[j] + t[i+1: j] + t[i] + t[j+1:]                    
                    qu.append((c, d + 1))

        return -1 


    def doit2(self, A, B):
        """
        :type A: str
        :type B: str
        :rtype: int
        """
        q = collections.deque()
        q.append(A)
        vis = set()
        vis.add(A)
        step = 0
        while len(q) > 0:
            sec_q = []
            step += 1
            for s in q:
                for i, a in enumerate(s):
                    if a != B[i]:
                        break
                for j in range(i+1, len(B)):
                    if a == B[j]:
                        if i > j:
                            i, j = j, i       
                        new_s = s[:i]+s[j]+s[i+1:j]+s[i]+s[j+1:]
                        #print (new_s, step)
                        if not new_s in vis:
                            if new_s == B:
                                return step
                            vis.add(new_s)
                            sec_q.append(new_s)
            
            q = sec_q
        return 0


            
if __name__ == '__main__':

    res = kSimilarity().doit("ab", "ba")

    res = kSimilarity().doit("abc", "bca")

    res = kSimilarity().doit("abac", "baca")

    res = kSimilarity().doit("aabc", "abca")            
        
    res = kSimilarity().doit("abccaacceecdeea", "bcaacceeccdeaae")
    
