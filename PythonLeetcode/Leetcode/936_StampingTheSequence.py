# 936. Stamping The Sequence

# You want to form a target string of lowercase letters.
#
# At the beginning, your sequence is target.length '?' marks.  You also have a stamp of lowercase letters.
#
# On each turn, you may place the stamp over the sequence, and replace every letter in the sequence with the corresponding letter from the stamp.
# You can make up to 10 * target.length turns.
#
# For example, if the initial sequence is "?????", and your stamp is "abc",  then you may make "abc??", "?abc?", "??abc" in the first turn.
# (Note that the stamp must be fully contained in the boundaries of the sequence in order to stamp.)
#
# If the sequence is possible to stamp, then return an array of the index of the left-most letter being stamped at each turn.
# If the sequence is not possible to stamp, return an empty array.
#
# For example, if the sequence is "ababc", and the stamp is "abc", then we could return the answer [0, 2],
# corresponding to the moves "?????" -> "abc??" -> "ababc".
#
# Also, if the sequence is possible to stamp, it is guaranteed it is possible to stamp within 10 * target.length moves.
# Any answers specifying more than this number of moves will not be accepted.

# Example 1:
#
# Input: stamp = "abc", target = "ababc"
# Output: [0,2]
# ([1,0,2] would also be accepted as an answer, as well as some other answers.)
# Example 2:
#
# Input: stamp = "abca", target = "aabcaca"
# Output: [3,0,1]

import collections


class MovesToStamp(object):


    """
    Approach 1: Work Backwards
    Intuition
    Imagine we stamped the sequence with moves m_1, m_2, Now, from the final position target, we will make those moves in reverse order.

    Let's call the ith window, a subarray of target of length stamp.length that starts at i.
    Each move at position i is possible if the ith window matches the stamp.
    After, every character in the window becomes a wildcard that can match any character in the stamp.

    For example, say we have stamp = "abca" and target = "aabcaca". Working backwards, we will reverse stamp at window 1 to get "a????ca",
    then reverse stamp at window 3 to get "a??????", and finally reverse stamp at position 0 to get "???????".

    Algorithm

    Let's keep track of every window. We want to know how many cells initially match the stamp (our "made" list), and which ones don't (our "todo" list).
    Any windows that are ready (ie. have no todo list), get enqueued.

    Specifically, we enqueue the positions of each character. (To save time, we enqueue by character, not by window.)
    This represents that the character is ready to turn into a "?" in our working target string.

    Now, how to process characters in our queue? For each character, let's look at all the windows that intersect it, and update their todo lists.
    If any todo lists become empty in this manner (window.todo is empty), then we enqueue the characters in window.made that we haven't processed yet.

    Complexity Analysis

    Time Complexity: O(N(N-M)) where M, NM,N are the lengths of stamp, target.

    Space Complexity: O(N(N-M)).
    """

    def doit1(self, stamp, target):
        """
        :type stamp: str
        :type target: str
        :rtype: List[int]
        """
        M, N = len(stamp), len(target)

        queue = collections.deque()
        done = [False] * N
        ans = []
        A = []
        for i in range(N - M + 1):
            # For each window [i, i+M),
            # A[i] will contain info on what needs to change
            # before we can reverse stamp at i.

            made, todo = set(), set()
            for j, c in enumerate(stamp):
                a = target[i+j]
                if a == c:
                    made.add(i+j)
                else:
                    todo.add(i+j)
            A.append((made, todo))

            # If we can reverse stamp at i immediately,
            # enqueue letters from this window.
            if not todo:
                ans.append(i)
                for j in range(i, i + len(stamp)):
                    if not done[j]:
                        queue.append(j)
                        done[j] = True

        # For each enqueued letter,
        while queue:
            i = queue.popleft()

            # For each window that is potentially affected,
            # j: start of window
            for j in range(max(0, i-M+1), min(N-M, i)+1):
                if i in A[j][1]:  # This window is affected
                    A[j][1].discard(i) # Remove it from todo list of this window
                    if not A[j][1]:  # Todo list of this window is empty
                        ans.append(j)
                        for m in A[j][0]: # For each letter to potentially enqueue,
                            if not done[m]:
                                queue.append(m)
                                done[m] = True

        return ans[::-1] if all(done) else []


    def doit(self, stamp, target):

        M, N = len(stamp), len(target)
        ans = []
        stamped = [False for _ in range(N-M + 1)]
        keepgoing = True

        while keepgoing:

            keepgoing = False
            for i in range(N - M + 1):

                if stamped[i]:
                    continue

                currentMatch = False
                for j in range(M):

                    if target[i + j] == '*':
                        if currentMatch:
                            break
                    elif target[i + j] != stamp[j]:
                        currentMatch = False
                        break
                    else:
                        currentMatch = True

                if currentMatch:
                    ans.append(i)
                    keepgoing = True
                    stamped[i] = True
                    target = target[:i] + ''.join(['*'] * M) + target[i + M:]


        for i in range(N):
            if target[i] != '*':
                ans = []
                break
        else:
            ans = ans[::-1]

        return ans

    def checker(self, stamp, target):
        for i, j in zip(stamp, target):
            if i != j and j != "?":
                return False
        return True

    def doit2(self, stamp: str, target: str) -> List[int]:

        t_len = len(target)
        s_len = len(stamp)
        index = 0
        res = []
        for i in range(0, 5):
            while index < t_len - s_len + 1:
                if target[index:index + s_len] != "?" * s_len:
                    if self.checker(stamp, target[index:index + s_len]):
                        res.append(index)
                        target = target[:index] + "?" * s_len + target[index + s_len:]
                        index = max(-1, index - s_len)

                index += 1
                # print(target,index)
        if target != "?" * t_len:
            return []

        return res[::-1]


if __name__ == '__main__':

    test = MovesToStamp().doit(stamp = "abc", target = "ababc")

    res = MovesToStamp().doit(stamp = "abca", target = "aabcaca")