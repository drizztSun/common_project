"""
1585. Check If String Is Transformable With Substring Sort Operations

Given two strings s and t, you want to transform string s into string t using the following operation any number of times:

Choose a non-empty substring in s and sort it in-place so the characters are in ascending order.
For example, applying the operation on the underlined substring in "14234" results in "12344".

Return true if it is possible to transform string s into string t. Otherwise, return false.

A substring is a contiguous sequence of characters within a string.



Example 1:

Input: s = "84532", t = "34852"
Output: true
Explanation: You can transform s into t using the following sort operations:
"84532" (from index 2 to 3) -> "84352"
"84352" (from index 0 to 2) -> "34852"
Example 2:

Input: s = "34521", t = "23415"
Output: true
Explanation: You can transform s into t using the following sort operations:
"34521" -> "23451"
"23451" -> "23415"
Example 3:

Input: s = "12345", t = "12435"
Output: false
Example 4:

Input: s = "1", t = "2"
Output: false


Constraints:

s.length == t.length
1 <= s.length <= 105
s and t only contain digits from '0' to '9'.

"""


class IsTransformable:

    """
    queue, simulation

    We can always move a single digit to the left until there is a smaller one just lke bubble sort by swapping adjacent elements.

    37584 -> 34758
    steps:
    37584 -> 37548
    37548 -> 37458
    37458 -> 34758
    34758 -> END

    This problem then reduced to: can we transform the string S to T by moving smaller digits to the left?

    Solution 1: simulation /Greedy/ Queue
    for each digit c in T:
        move the first c in s to the left most

    Simulation take O(n^2) time, we don't actually need to move.

    Create 10 queues, one for each digits to store the indices of each digits in S.
    We can check whether there is any smaller digits in front of the one to be moved to the front.

    Time Complexity: O(n)
    Space Complexity: O(n)

    """
    def doit_greedy(self, s: str, t: str) -> bool:
        from collections import defaultdict, deque
        idx = defaultdict(deque)
        for i, c in enumerate(s):
            idx[int(c)].append(i)
        for c in t:
            d = int(c)
            if not idx[d]:
                return False
            for i in range(d):
                if idx[i] and idx[i][0] < idx[d][0]:
                    return False
            idx[d].popleft()
        return True

    def doit_gready_way(self, s: str, t: str) -> bool:
        from collections import deque, defaultdict
        digits = [deque() for _ in range(10)]
        for i, c in enumerate(s):
            digits[int(c)].append(i)

        print(digits)
        for c in t:
            d = int(c)
            if not digits[d]:
                return False

            pos = digits[d].popleft()

            for i in range(d):
                if digits[i] and digits[i][0] < pos:
                    return False
        return True


if __name__ == '__main__':

    IsTransformable().doit_dp(s = "84532", t = "34852")

    IsTransformable().doit_dp(s = "34521", t = "23415")

    IsTransformable().doit_dp(s = "12345", t = "12435")

    IsTransformable().doit_dp(s = "1", t = "2")