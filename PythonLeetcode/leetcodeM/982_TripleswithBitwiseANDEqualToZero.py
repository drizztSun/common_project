# 982. Triples with Bitwise AND Equal To Zero

from collections import Counter


class CountTriplets:
    def doit(self, A):

        N = len(A)
        cnt = [0 for _ in range(1 << 16)]
        ans = 0

        for x in A:
            for y in A:
                cnt[x & y] += 1

        for k in A:

            #bits = (~k) & 0xFFFFFFF
            bits = k ^ 0xffffffff

            k = bits
            while k:
                ans += cnt[k]
                k = (k - 1) & bits

            ans += cnt[0]

        return ans

    def doit2(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        d={}
        res=0
        for a in A:
            for b in A:
                t=a&b
                if t in d:
                    d[t]+=1
                else:
                    d[t]=1
        for a in A:
            for k,v in d.items():
                if a&k==0:
                    res+=v
        return res

    def doit1(self, A):

        c = Counter(x & y for x in A for y in A)

        return sum(c[xy] for xy in c for z in A if xy & z == 0)


if __name__ == "__main__":

    res = CountTriplets().doit([2, 1, 3])

    pass
