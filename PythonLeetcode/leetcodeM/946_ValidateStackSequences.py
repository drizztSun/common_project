# 946. Validate Stack Sequences

# Given two sequences pushed and popped with distinct values,
# return true if and only if this could have been the result of a sequence of push and pop operations on an initially empty stack.


# Example 1:

# Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
# Output: true
# Explanation: We might do the following sequence:
# push(1), push(2), push(3), push(4), pop() -> 4,
# push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1

# Example 2:

# Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
# Output: false
# Explanation: 1 cannot be popped before 2.


# Note:

# 0 <= pushed.length == popped.length <= 1000
# 0 <= pushed[i], popped[i] < 1000
# pushed is a permutation of popped.
# pushed and popped have distinct values.


class ValidateStackSequences:

    def doit(self, pushed, popped):

        i, j = 0, 0
        buff = []

        while i < len(pushed):

            if not buff or buff[-1] != popped[j]:
                buff.append(pushed[i])

            while buff and j < len(popped) and buff[-1] == popped[j]:
                buff.pop()
                j += 1

            i += 1

        return not buff and j == len(popped) and i == len(pushed)

    """
    Approach 1: Greedy
    Intuition

    We have to push the items in order, so when do we pop them?

    If the stack has say, 2 at the top, then if we have to pop that value next, we must do it now. That's because any subsequent push will make the top of the stack different from 2, and we will never be able to pop again.

    Algorithm

    For each value, push it to the stack.

    Then, greedily pop values from the stack if they are the next values to pop.

    At the end, we check if we have popped all the values successfully.

    Complexity Analysis

    Time Complexity: O(N), where NN is the length of pushed and popped.

    Space Complexity: O(N).
    """

    def doit(self, pushed, popped):
        j = 0
        stack = []
        for x in pushed:
            stack.append(x)
            while stack and j < len(popped) and stack[-1] == popped[j]:
                stack.pop()
                j += 1

        return j == len(popped)


if __name__ == '__main__':

    res = ValidateStackSequences().doit(
        pushed=[1, 2, 3, 4, 5], popped=[4, 5, 3, 2, 1])  # true

    res = ValidateStackSequences().doit(
        pushed=[1, 2, 3, 4, 5], popped=[4, 3, 5, 1, 2])  # false

    pass
