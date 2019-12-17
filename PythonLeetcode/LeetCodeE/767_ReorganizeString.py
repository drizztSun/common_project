# 767. Reorganize String

# Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.

# If possible, output any possible result.  If not possible, return the empty string.

# Example 1:

# Input: S = "aab"
# Output: "aba"
# Example 2:

# Input: S = "aaab"
# Output: ""

import heapq


class ReorganizeString:

    # dfs TLE
    def doit1(self, S: str) -> str:

        buff = {}
        for c in S:
            buff[c] = buff.get(c, 0) + 1

        keys = sorted(list(buff.keys()), key=lambda x: buff[x])
        dp = set()

        def dfs(res, buff, keys):

            if res in dp:
                return ''

            if len(res) == len(S):
                return res

            for i in range(len(keys)):

                if res and res[-1] == keys[i] or buff[keys[i]] == 0:
                    continue

                buff[keys[i]] -= 1
                l = dfs(res + keys[i], buff, keys)
                buff[keys[i]] += 1
                if l:
                    return l

            dp.add(res)
            return ''

        return dfs('', buff, keys)

    def doit(self, S: str) -> str:

        buff = {}
        for c in S:
            buff[c] = buff.get(c, 0) + 1

        items = list(buff.items())
        pq = []
        for c in items:
            heapq.heappush(pq, (-c[1], c[0]))

        res = ''
        while pq:
            c = heapq.heappop(pq)

            if not pq:
                if c[0] < -1:
                    return ''
                else:
                    res += c[1]
                    continue

            s = heapq.heappop(pq)

            res += c[1] + s[1]
            if c[0] != -1:
                heapq.heappush(pq, (c[0] + 1, c[1]))
            if s[0] != -1:
                heapq.heappush(pq, (s[0] + 1, s[1]))

        return res

    def doit(self, S):

        N = len(S)
        A = []
        for c, x in sorted((S.count(x), x) for x in set(S)):
            if c > (N+1)//2:
                return ''
            A.extend(c*x)
        ans = [None]*N
        ans[::2], ans[1::2] = A[N//2:], A[:N//2]
        return ''.join(ans)


if __name__ == '__main__':

    res = ReorganizeString().doit('aab')

    res = ReorganizeString().doit('aaab')

    res = ReorganizeString().doit('vvvlo')

    res = ReorganizeString().doit('baaba')  # ababa

    res = ReorganizeString().doit('eqpspvbpppwpgyppppe')

    pass
