# 869. Reordered Power of 2

# Starting with a positive integer N, we reorder the digits in any order (including the original order)
# such that the leading digit is not zero.

# Return true if and only if we can do this in a way such that the resulting number is a power of 2.

# Example 1:

# Input: 1
# Output: true

# Example 2:

# Input: 10
# Output: false

# Example 3:

# Input: 16
# Output: true

# Example 4:

# Input: 24
# Output: false

# Example 5:

# Input: 46
# Output: true


class ReorderedPowerOf2:

    """
    Approach 1: Permutations
    Intuition

    For each permutation of the digits of N, let's check if that permutation is a power of 2.

    Algorithm
    This approach has two steps: how will we generate the permutations of the digits,
    and how will we check that the permutation represents a power of 2?

    To generate permutations of the digits, we place any digit into the first position (start = 0),
    then any of the remaining digits into the second position (start = 1), and so on.
    In Python, we can use the builtin function itertools.permutations.

    To check whether a permutation represents a power of 2, we check that there is no leading zero,
    and divide out all factors of 2. If the result is 1 (that is, it contained no other factors besides 2), then it was a power of 2.
    In Python, we can use the check bin(N).count('1') == 1.
    """

    def doit(self, N):
        """
        Let's work through an example like N = 128.
        In the last line, 'for cand in itertools.permutations(str(N))' will
        iterate through the six possibilities cand = ('1', '2', '8'),
        cand = ('1', '8', '2'), cand = ('2', '1', '8'), and so on.

        The check cand[0] != '0' is a check that the candidate permutation
        does not have a leading zero.

        The check bin(int("".join(cand))).count('1') == 1 is a check that cand
        represents a power of 2: namely, that the number of ones in its binary
        representation is 1.

        Complexity Analysis

        Time Complexity: O((\log N)! * \log N)O((logN)!∗logN).
        Note that \log NlogN is the number of digits in the binary representation of NN.
        For each of (\log N)!(logN)! permutations of the digits of NN, we need to check that it is a power of 2 in O(\log N)O(logN) time.

        Space Complexity: O(\log N)O(logN), the space used by A (or cand in Python).
        """
        return any(cand[0] != '0' and bin(int("".join(cand))).count('1') == 1
                   for cand in itertools.permutations(str(N)))

        for cand in itertools.permutation(str(N)):
            if cand[0] != '0' and bin(int(''.join(cand))).count('1') == 1:
                return True
        return False

    """
    Approach 2: Counting
    Intuition and Algorithm

    We can check whether two numbers have the same digits by comparing the count of their digits.
    For example, 338 and 833 have the same digits because they both have exactly two 3's and one 8.

    Since NN could only be a power of 2 with 9 digits or less (namely, 2^0, 2^1, ... , 2^29),
    we can just check whether N has the same digits as any of these possibilities.

    Complexity Analysis

    Time Complexity: O(\log^2 N).
    There are \log NlogN different candidate powers of 2, and each comparison has O(logN) time complexity.

    Space Complexity: O(logN).
    """

    def doit(self, N):
        count = collections.Counter(str(N))
        return any(count == collections.Counter(str(1 << b))
                   for b in range(31))


if __name__ == '__main__':

    res = ReorderedPowerOf2().doit(1)  # true

    res = ReorderedPowerOf2().doit(10)  # false

    res = ReorderedPowerOf2().doit(16)  # true

    res = ReorderedPowerOf2().doit(24)  # false

    res = ReorderedPowerOf2().doit(46)  # true

    pass
