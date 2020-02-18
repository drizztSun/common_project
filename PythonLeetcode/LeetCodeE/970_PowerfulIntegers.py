# 970. Powerful Integers

# Given two positive integers x and y, an integer is powerful if it is equal to x^i + y^j for some integers i >= 0 and j >= 0.

# Return a list of all powerful integers that have value less than or equal to bound.

# You may return the answer in any order.  In your answer, each value should occur at most once.


# Example 1:

# Input: x = 2, y = 3, bound = 10
# Output: [2,3,4,5,7,9,10]
# Explanation:
# 2 = 2^0 + 3^0
# 3 = 2^1 + 3^0
# 4 = 2^0 + 3^1
# 5 = 2^1 + 3^1
# 7 = 2^2 + 3^1
# 9 = 2^3 + 3^0
# 10 = 2^0 + 3^2

# Example 2:

# Input: x = 3, y = 5, bound = 15
# Output: [2,4,6,8,10,14]

class PowerfulIntegers:

    def doit(self, x, y, bound):
        data_1, data_2 = [], []

        i, j = 0, 0
        if (x == 1):
            data_1.append(1)
        else:
            while (x**i <= bound):
                data_1.append(x**i)
                i += 1

        if (y == 1):
            data_2.append(1)
        else:
            while (y**j <= bound):
                data_2.append(y**j)
                j += 1

        print("data_1 = ", data_1)
        print("data_2 = ", data_2)

        res = []
        for d1 in data_1:
            for d2 in data_2:
                tmp = d1 + d2
                if (tmp <= bound and tmp not in res):
                    res.append(tmp)

        return res

    def doit(self, x, y, bound):
        import collections
        xset, yset = collections.OrderedDict(), collections.OrderedDict()

        if x == 1:
            xset[1] = 1
        else:
            i = 0
            while x**i < bound:
                xset[x**i] = 1
                i += 1

        if y == 1:
            yset[1] = 1
        else:
            j = 0
            while y**j < bound:
                yset[y**j] = 1
                j += 1

        ans = []
        for n in range(bound+1):
            for x in xset:
                if x >= n:
                    break
                if (n - x) in yset:
                    ans.append(n)
                    break
        return ans

    def doit(self, x, y, bound):

        ans = set()
        # 2**18 > bound
        for i in range(18):
            for j in range(18):
                v = x**i + y**j
                if v <= bound:
                    ans.add(v)
        return list(ans)

    def doit(self, x: int, y: int, bound: int):

        buff = [(0, 0)]
        seen = set()
        ans = set()

        while buff:

            z, k = buff.pop()
            if (z, k) in seen:
                continue

            seen.add((z, k))
            power = x ** z + y ** k

            if power > bound:
                continue

            ans.add(power)
            buff.append((z+1, k))
            buff.append((z, k+1))

        return list(ans)


if __name__ == '__main__':

    res = PowerfulIntegers().doit(x=2, y=3, bound=10)  # [2,3,4,5,7,9,10]

    res = PowerfulIntegers().doit(x=3, y=5, bound=15)  # [2,4,6,8,10,14]

    pass
