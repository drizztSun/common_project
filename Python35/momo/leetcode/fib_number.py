
class fib_num_Solution:
    '''
    Approach 1: Recursion
    Intuition

    Use recursion to compute the Fibonacci number of a given integer.

    Algorithm

    Check if the provided input value, N, is less than or equal to 1. If true, return N.

    Otherwise, the function fib(int N) calls itself, with the result of the 2 previous numbers being added to each other,
     passed in as the argument. This is derived directly from the recurrence
    relation: f(n) = f(n-1)+f(n-2)
    ​


    Do this until all numbers have been computed, then return the resulting answer.


    '''
    # way1 (O(2^n))

    def fib(self, a):
        if a <= 1:
            return a
        return self.fib(a - 1) + self.fib(a - 2)

    # improved way1 (O(n))
    def fib1(self, n) -> int:
        dic = {}

        def fib_cal(n):
            if n == 1:
                return 1
            elif n == 0:
                return 0
            if n not in dic:
                dic[n] = fib_cal(n-1) + fib_cal(n-2)
            return dic[n]
        return fib_cal(n)



if __name__ == '__main__':

    a = fib_num_Solution().fib1()
    print(a)
