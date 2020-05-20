class isPalindrome:
    def way(self, x: int) -> bool:
        a = []
        num = x
        while num > 0:
            num, v = divmod(num, 10)
            a.append(v)

        k = 0
        for c in a:
            k = k * 10 + c

        return k == x

    def way2(self, x):
        k, num = 0, x
        while num > 0:
            num, v = divmod(num, 10)
            k = k * 10 + v

        return k == x

