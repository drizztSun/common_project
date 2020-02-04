# 954. Array of Doubled Pairs

# Given an array of integers A with even length,
# return true if and only if it is possible to reorder it such that A[2 * i + 1] = 2 * A[2 * i] for every 0 <= i < len(A) / 2.


# Example 1:

# Input: [3,1,3,6]
# Output: false

# Example 2:

# Input: [2,1,2,6]
# Output: false

# Example 3:

# Input: [4,-2,2,-4]
# Output: true
# Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].

# Example 4:

# Input: [1,2,4,16,8,4]
# Output: false

from collections import Counter


class CanReorderDoubled:

    """
    Approach 1: Greedy
    Intuition

    If x is currently the array element with the least absolute value,
    it must pair with 2*x, as there does not exist any other x/2 to pair with it.

    Algorithm

    Let's try to (virtually) "write" the final reordered array.

    Let's check elements in order of absolute value.
    When we check an element x and it isn't used, it must pair with 2*x.
    We will attempt to write x, 2x - if we can't, then the answer is false. If we write everything, the answer is true.

    To keep track of what we have not yet written, we will store it in a count.

    Complexity Analysis

    Time Complexity: O(NlogN), where N is the length of A.
    Space Complexity: O(N).
    """

    def doit(self, A):

        count = collections.Counter(A)
        for x in sorted(A, key=abs):
            if count[x] == 0:
                continue
            if count[2*x] == 0:
                return False
            count[x] -= 1
            count[2*x] -= 1

        return True

    def doit(self, A):

        d = Counter(A)
        for num in sorted(d):
            if num < 0 and num % 2 == 0 and d[num] > 0 and num/2 in d:
                d[num/2] -= d[num]
                d[num] = 0
            elif num >= 0 and d[num] > 0 and num*2 in d:
                d[num*2] -= d[num]
                d[num] = 0
        return not any(d.values())


if __name__ == '__main__':

    res = CanReorderDoubled().doit([3, 1, 3, 6])

    res = CanReorderDoubled().doit([2, 1, 2, 6])

    res = CanReorderDoubled().doit([4, -2, 2, -4])

    res = CanReorderDoubled().doit([1, 2, 4, 16, 8, 4])

    pass
