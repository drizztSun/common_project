


# 321. Create Maximum Number

# Given two arrays of length m and n with digits 0-9 representing two numbers.
# Create the maximum number of length k <= m + n from digits of the two.
# The relative order of the digits from the same array must be preserved.
# Return an array of the k digits. You should try to optimize your time and space complexity.

# Example 1:
# nums1 = [3, 4, 6, 5]
# nums2 = [9, 1, 2, 5, 8, 3]
# k = 5
# return [9, 8, 6, 5, 3]

# Example 2:
# nums1 = [6, 7]
# nums2 = [6, 0, 4]
# k = 5
# return [6, 7, 6, 0, 4]

# Example 3:
# nums1 = [3, 9]
# nums2 = [8, 9]
# k = 3
# return [9, 8, 9]

# <important> <hard>
class maxNumber(object):

    # 
    def doit(self, a, b, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[int]
        """
        lena = len(a)
        lenb = len(b)


        def fill(a, c):
            last = [-1] * 10
            for i, v in enumerate(a):
                c[v][last[v]+1:i+1] = [i] * (i-last[v])
                last[v] = i

        if k <= (lena+lenb)*5/6:
            N = 50
            if lena >= N:
                c = [[None] * lena for i in range(10)]
                fill(a, c)
            else:
                c = None
                
            if lenb >= N:
                d = [[None] * lenb for i in range(10)]
                fill(b, d)
            else:
                d = None
        else:
            c = None
            d = None

        def maxd(a, i, b, j, k, c):
            ln1 = len(a) - i
            n1 = ln1 - (k - len(b) + j) + 1
            n1 = min(ln1, n1)
            if n1 == 1:
                return 0, a[i]

            if c is None or (n1 <= 5):
                i0 = i
                nums = a[i0:i0+n1]

                m = max(nums)
                i = nums.index(m)
                m1 = i, m
                return m1
            
            for d in range(9, -1, -1):
                dn = c[d][i]
                if dn is None:
                    continue
                r = dn - i
                if r < n1:
                    ret = r, d
                    break

            return ret

        ret = []
        s = set()
        s.add((0, 0))
        while k > 0:
            m = -1
            ss = [None for _ in range(10)]
            for i, j in s:
                if i < lena:
                    m1 = maxd(a, i, b, j, k, c)
                    if m1 and m1[1] >= m:
                        m = m1[1]
                        if ss[m] is None:
                            ss[m] = set()
                        new_i = i+m1[0]+1
#                        if new_i > len(a):
#                            print('vvv')
                        ss[m].add( (new_i, j))
                if j < lenb:
                    m2 = maxd(b, j, a, i, k, d)
                    if m2 and m2[1] >= m:
                        m = m2[1]
                        if ss[m] is None:
                            ss[m] = set()
                        ss[m].add( (i, j+m2[0]+1))

            ret.append(m)
            s = ss[m]#set([x for x in d if d[x] == m])
            k -= 1
        return ret

    # <steve>
    def doit(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[int]
        """
        def merge(a, b):
            return [max(a, b).pop(0) for _ in a + b]
        
        def prepare(a, k):
            drop = len(a) - k
            out = []

            for c in a:
                while drop and out and out[-1] < c:
                    out.pop()
                    drop -= 1

                out.append(c)
            return out[:k]


        return max([ merge(prepare(nums1, i), prepare(nums2, k-i)) for i in range(k+1)
                        if i <= len(nums1) and k-i <= len(nums2)])           
            
                



    # <myown>
    def doit(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[int]
        """
        def getSubArray(A, n):
            needRemoved = len(A) - n
            if needRemoved == 0:
                return A[:]
            
            result = []
            for i in range(len(A)):
                while needRemoved and result and A[i] > result[-1]:
                    result.pop()
                    needRemoved -= 1
                result.append(A[i])
            return result[:n]


        ans = []
        for i in range(k+1):
            if len(nums1) >= i and len(nums2) >= k - i: 
                s1 = getSubArray(nums1, i)
                s2 = getSubArray(nums2, k-i)

                result, s = [], None
                while s1 or s2:
                    i = 0
                    while i < len(s1) and i < len(s2) and s1[i] == s2[i]:
                        i += 1
                            
                    if i == len(s1) or i == len(s2):
                        s = s2 if i == len(s1) else s1
                    else:
                        s = s1 if s1[i] > s2[i] else s2

                    result.append(s.pop(0))

                ans = max(result, ans)                        
            
        return ans


if __name__=="__main__":


    res = maxNumber().doit([3, 4, 6, 5], [9, 1, 2, 5, 8, 3], 5) # [9, 8, 6, 5, 3]

    res = maxNumber().doit([6, 7], [6, 0, 4], 5) # [6, 7, 6, 0, 4]

    res = maxNumber().doit([3, 9], [8, 9], 3) # [9, 8, 9]

    pass
