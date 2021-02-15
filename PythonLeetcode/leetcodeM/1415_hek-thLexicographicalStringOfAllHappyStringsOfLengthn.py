"""
1415. The k-th Lexicographical String of All Happy Strings of Length n


A happy string is a string that:

consists only of letters of the set ['a', 'b', 'c'].
s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.

Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.

Return the kth string of this list or return an empty string if there are less than k happy strings of length n.



Example 1:

Input: n = 1, k = 3
Output: "c"
Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
Example 2:

Input: n = 1, k = 4
Output: ""
Explanation: There are only 3 happy strings of length 1.
Example 3:

Input: n = 3, k = 9
Output: "cab"
Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"
Example 4:

Input: n = 2, k = 7
Output: ""
Example 5:

Input: n = 10, k = 100
Output: "abacbabacb"


Constraints:

1 <= n <= 10
1 <= k <= 100


"""


class HappyString:

    def doit_(self, n: int, k: int) -> str:

        buff = []
        res, cnt = '', 0

        def search(i, last):
            nonlocal cnt, res
            if i == n:
                cnt += 1
                if cnt == k:
                    res = ''.join(buff)
                return

            for char in 'abc':
                if char != last:
                    buff.append(char)
                    search(i+1, char)
                    buff.pop()

        search(0, '0')
        return '' if k > cnt else res

    def doit_(self, n: int, k: int) -> str:

        cnt = 3 * (1 << (n-1))
        if cnt < k:
            return ''

        res = ''
        if cnt // 3 >= k:
            res = 'a'
        elif 2 * cnt // 3 >= k:
            res = 'b'
            k -= cnt // 3
        else:
            res = 'c'
            k -= 2 * cnt // 3

        cnt //= 3

        while len(res) < n:

            cnt >>= 1
            if res[-1] == 'a':
                res += 'b' if k < cnt else 'c'
            elif res[-1] == 'b':
                res += 'a' if k < cnt else 'c'
            elif res[-1] == 'c':
                res += 'a' if k < cnt else 'b'

            if k > cnt:
                k -= cnt

        return res

    def doit_(self, n: int, k: int) -> str:

        t = 2**(n-1)     # consider the HappyString as combined by 3 trees, root as 'a', 'b' and 'c'
        l = ['a','b','c']
        k -= 1   # index start from 0
        res =''
        if k//t >= 3: return ''   # k//t denote which tree the result in, thus put the first char into res
        if k//t == 0: res += 'a'
        if k//t == 1: res += 'b'
        if k//t == 2: res += 'c'
        if n == len(res): return res

        d = bin(k%t)[2:]     # k%t denote which leaf the result is, transfer it to binary 0 means the smaller char, vice versa
        s = '0'*(n-len(d)-1)+d    # already wrote the first char into result, so make the string's length equal with n-1

        for i in s:
            tl = [] + l
            tl.remove(res[-1])  # remove the last char in res  from tl, so tl only have 2 elements
            res += tl[int(i)]
        return res
