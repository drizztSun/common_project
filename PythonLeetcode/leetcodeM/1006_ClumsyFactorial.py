# 1006. Clumsy Factorial

# Normally, the factorial of a positive integer n is the product of all positive integers less than or equal to n.
# For example, factorial(10) = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1.

# We instead make a clumsy factorial: using the integers in decreasing order, we swap out the multiply operations for a fixed rotation of operations:
# multiply (*), divide (/), add (+) and subtract (-) in this order.

# For example, clumsy(10) = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1.
# However, these operations are still applied using the usual order of operations of arithmetic:
# we do all multiplication and division steps before any addition or subtraction steps, and multiplication and division steps are processed left to right.

# Additionally, the division that we use is floor division such that 10 * 9 / 8 equals 11.  This guarantees the result is an integer.

# Implement the clumsy function as defined above: given an integer N, it returns the clumsy factorial of N.


# Example 1:

# Input: 4
# Output: 7
# Explanation: 7 = 4 * 3 / 2 + 1

# Example 2:

# Input: 10
# Output: 12
# Explanation: 12 = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1

class Clumsy:

    def doit(self, N):
        if N == 1:
            return 1
        if N == 2:
            return 2
        if N == 3:
            return 6

        def helper(M):
            if M == 0:
                return 0
            if M == 1:
                return 1
            if M == 2:
                return 1
            if M == 3:
                return 1
            if M == 4:
                return -2
            if M == 5:
                return 0
            return helper((M - 2) % 4 + 2)

        return N * (N - 1) / (N - 2) + helper(N - 3)

    def doit(self, N):
        """
        :type N: int
        :rtype: int
        """
        rem = [1, 2, 2, -1]

        if N < 3:
            return N

        if N < 5:
            return N + 3

        return N + rem[N % 4]

    def doit(self, N):
        """
        :type N: int
        :rtype: int
        """
        ops = ['*', '/', '+', '-']

        def gen_formula(num):
            st = ''
            for c in range(num, 0, -1):
                st += str(c) + ops[(num - c) % 4]
            return st[:-1]

        s = gen_formula(N)

        num, st = 0, []
        op = '+'

        for i, c in enumerate(s):

            if c.isdigit():
                num = num * 10 + int(c)

            if c in ops or i == len(s) - 1:

                if op == '+':
                    st.append(num)
                elif op == '-':
                    st.append(num)
                elif op == '*':
                    st.append(st.pop() * num)
                elif op == '/':
                    st.append(int(st.pop() / num))

                num = 0
                op = c

        return sum(st)

    def doit(self, N):

        if N == 1:
            return 1
        if N == 2:
            return 2
        if N == 3:
            return 6

        res = 0
        for m in range(N//4):
            if m == 0:
                res += (N-m*4)*(N-m*4-1)//(N-m*4-2)+(N-m*4-3)
            else:
                res -= (N-m*4)*(N-m*4-1)//(N-m*4-2)-(N-m*4-3)

        if N % 4 == 0:
            return res
        if N % 4 == 1:
            return res-1
        if N % 4 == 2:
            return res-2
        if N % 4 == 3:
            return res-6


if __name__ == '__main__':

    res = Clumsy().doit(4)

    res = Clumsy().doit(10)

    pass
