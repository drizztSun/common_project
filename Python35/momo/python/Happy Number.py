class Solution:
    def isHappy(self, n: int) -> bool:

        def happy_step(num):
            a = []
            while num > 0:
                num, v = divmod(num, 10)
                a.append(v)
            a = reversed(a)

            return sum(i ** 2 for i in a)

        set1 = set()
        while True:
            n = happy_step(n)
            if n == 1:
                return True
            elif n in set1:
                return False
            set1.add(n)
    def is_happy1(self, n):
        s = set()
        while n != 1 and n not in s:
            s.add(n)
            m = 0
            while n > 0:
                m += (n % 10) ** 2
                n = n // 10
            n = m
        return n == 1


if __name__ == "__main__":
    Solution().isHappy(n=19)
