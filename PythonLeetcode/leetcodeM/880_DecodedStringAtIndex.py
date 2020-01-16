# 880. Decoded String at Index

# An encoded string S is given.
# To find and write the decoded string to a tape, the encoded string is read one character at a time and the following steps are taken:

# If the character read is a letter, that letter is written onto the tape.
# If the character read is a digit (say d), the entire current tape is repeatedly written d-1 more times in total.
# Now for some encoded string S, and an index K, find and return the K-th letter (1 indexed) in the decoded string.


# Example 1:

# Input: S = "leet2code3", K = 10
# Output: "o"
# Explanation:
# The decoded string is "leetleetcodeleetleetcodeleetleetcode".
# The 10th letter in the string is "o".

# Example 2:

# Input: S = "ha22", K = 5
# Output: "h"
# Explanation:
# The decoded string is "hahahaha".  The 5th letter is "h".

# Example 3:

# Input: S = "a2345678999999999999999", K = 1
# Output: "a"
# Explanation:
# The decoded string is "a" repeated 8301530446056247680 times.  The 1st letter is "a".

class DecodeAtIndex:

    # Memory Limit Exceeded
    def doit(self, S, K):
        last = -1
        curbase = ''
        times = 0

        for i in range(len(S)+1):
            if i == len(S) or S[i].isdigit():
                sublength = i - last - 1
                times = int(S[i]) if i != len(S) else 1
                curbase = curbase + S[last + 1: i]

                if len(curbase) * times >= K:
                    while len(curbase) < K:
                        K -= len(curbase)
                    return curbase[K-1]
                curbase *= times
                last = i

    """
    Approach 1: Work Backwards
    Intuition

    If we have a decoded string like appleappleappleappleappleapple and an index like K = 24, the answer is the same if K = 4.

    In general, when a decoded string is equal to some word with size length repeated some number of times (such as apple with size = 5 repeated 6 times),
    the answer is the same for the index K as it is for the index K % size.

    We can use this insight by working backwards, keeping track of the size of the decoded string.
    Whenever the decoded string would equal some word repeated d times, we can reduce K to K % (word.length).

    Algorithm
    First, find the length of the decoded string.
    After, we'll work backwards, keeping track of size: the length of the decoded string after parsing symbols S[0], S[1], ..., S[i].

    If we see a digit S[i], it means the size of the decoded string after parsing S[0], S[1], ..., S[i-1] will be size / Integer(S[i]).
    Otherwise, it will be size - 1.

    Complexity Analysis

    Time Complexity: O(N), where NN is the length of S.
    Space Complexity: O(1).
    """

    def doit(self, S, K):
        size = 0
        # Find size = length of decoded string
        for c in S:
            if c.isdigit():
                size *= int(c)
            else:
                size += 1

        for c in reversed(S):
            K %= size
            if K == 0 and c.isalpha():
                return c

            if c.isdigit():
                size /= int(c)
            else:
                size -= 1

    # better
    def doit(self, S, K):
            length = 0
        for i in range(len(S)):
            if S[i].isdigit():
                length *= int(S[i])
            else:
                length += 1

            if length >= K:
                break

        for j in range(i, -1, -1):
            if S[j].isdigit():
                length /= int(S[j])
                K %= length
            else:
                if K == length or K == 0:
                    return S[j]
                else:
                    length -= 1

    def doit(self, S, K):
        stck = []
        cnt = 0
        tms = 1
        cur = ''
        K -= 1
        for c in S:
            if c.isdigit():
                tms *= int(c)
                if tms*cnt > K:
                    K %= cnt
                    while K < cnt-len(cur):
                        cur, cnt, tms = stck.pop()
                        K %= cnt
                    return cur[K-cnt+len(cur)]
            else:
                if tms > 1:
                    if K < cnt * tms:
                        K %= cnt
                        while K < cnt - len(cur):
                            cur, cnt, tms = stck.pop()
                            K %= cnt
                        return cur[K-cnt+len(cur)]
                    stck.append((cur, cnt, tms))
                    cur = ''
                    cnt = cnt*tms
                    tms = 1
                cur += c
                cnt += 1
                if cnt > K:
                    return c




if __name__ == '__main__':

    res = DecodeAtIndex().doit(S="leet2code3", K=10)  # "0"

    res = DecodeAtIndex().doit(S="abc", K=1)  # a

    res = DecodeAtIndex().doit(S="abc", K=3)  # c

    res = DecodeAtIndex().doit(S="ha22", K=5)  # "h"

    res = DecodeAtIndex().doit(S="a2345678999999999999999", K=1)  # "a"

    pass
