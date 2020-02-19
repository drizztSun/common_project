# 1016. Binary String With Substrings Representing 1 To N

#  Given a binary string S (a string consisting only of '0' and '1's) and a positive integer N,
# return true if and only if for every integer X from 1 to N, the binary representation of X is a substring of S.


# Example 1:

# Input: S = "0110", N = 3
# Output: true

# Example 2:

# Input: S = "0110", N = 4
# Output: false


class QueryString:

    def doit(self, S: str, N: int):
        return all('{:b}'.format(n) in S for n in range(N, 0, -1))

    def doit(self, S: str, N: int):

        for i in range(1, N+1):
            if '{:b}'.format(i) not in S:
                return False
        return True


if __name__ == '__main__':

    res = QueryString().doit(S="0110", N=3)

    res = QueryString().doit(S="0110", N=4)
