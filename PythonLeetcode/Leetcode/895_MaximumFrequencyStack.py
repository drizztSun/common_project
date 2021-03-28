"""
# 895. Maximum Frequency Stack

# Implement FreqStack, a class which simulates the operation of a stack-like data structure.

# FreqStack has two functions:

# push(int x), which pushes an integer x onto the stack.
# pop(), which removes and returns the most frequent element in the stack.
# If there is a tie for most frequent element, the element closest to the top of the stack is removed and returned.


# Example 1:

# Input:
# ["FreqStack","push","push","push","push","push","push","pop","pop","pop","pop"],
# [[],[5],[7],[5],[7],[4],[5],[],[],[],[]]
# Output: [null,null,null,null,null,null,null,5,7,5,4]
# Explanation:
# After making six .push operations, the stack is [5,7,5,7,4,5] from bottom to top.  Then:

# pop() -> returns 5, as 5 is the most frequent.
# The stack becomes [5,7,5,7,4].

# pop() -> returns 7, as 5 and 7 is the most frequent, but 7 is closest to the top.
# The stack becomes [5,7,5,4].

# pop() -> returns 5.
# The stack becomes [5,7,4].

# pop() -> returns 4.
# The stack becomes [5,7].


# Note:

# Calls to FreqStack.push(int x) will be such that 0 <= x <= 10^9.
# It is guaranteed that FreqStack.pop() won't be called if the stack has zero elements.
# The total number of FreqStack.push calls will not exceed 10000 in a single test case.
# The total number of FreqStack.pop calls will not exceed 10000 in a single test case.
# The total number of FreqStack.push and FreqStack.pop calls will not exceed 150000 across all test cases.

"""


"""
    Approach 1: Stack of Stacks
    Intuition

    Evidently, we care about the frequency of an element. Let freq be a Map from xx to the number of occurrences of xx.

    Also, we (probably) care about maxfreq, the current maximum frequency of any element in the stack.
    This is clear because we must pop the element with the maximum frequency.

    The main question then becomes: among elements with the same (maximum) frequency, how do we know which element is most recent?
    We can use a stack to query this information: the top of the stack is the most recent.

    To this end, let group be a map from frequency to a stack of elements with that frequency. We now have all the required components to implement FreqStack.

    Algorithm

    Actually, as an implementation level detail, if x has frequency f, then we'll have x in all group[i] (i <= f), not just the top.
    This is because each group[i] will store information related to the ith copy of x.

    Afterwards, our goal is just to maintain freq, group, and maxfreq as described above.

"""

import collections


class FreqStack:

    def __init__(self):
        self._freq = collections.Counter()
        self._groups = collections.defaultdict(list)
        self._maxfreq = 0

    def push(self, x: int) -> None:
        self._freq[x] += 1
        f = self._freq[x]

        if f > self._maxfreq:
            self._maxfreq = f

        self._groups[f].append(x)

    def pop(self) -> int:

        x = self._groups[self._maxfreq].pop()
        self._freq[x] -= 1

        if not self._groups[self._maxfreq]:
            self._maxfreq -= 1

        return x


"""
    Hash map freq will count the frequence of elements.
    Hash map m is a map of stack.
    If element x has n frequence, we will push x n times in m[1], m[2] .. m[n]
    maxfreq records the maximum frequence.
    
    push(x) will push x tom[++freq[x]]
    pop() will pop from the m[maxfreq]
"""


class FreqStack:

    def __init__(self):
        self.freq = collections.Counter()
        self.m = collections.defaultdict(list)
        self.maxf = 0

    def push(self, x):
        freq, m = self.freq, self.m
        freq[x] += 1
        self.maxf = max(self.maxf, freq[x])
        m[freq[x]].append(x)

    def pop(self):
        freq, m, maxf = self.freq, self.m, self.maxf
        x = m[maxf].pop()
        if not m[maxf]: self.maxf = maxf - 1
        freq[x] -= 1
        return x