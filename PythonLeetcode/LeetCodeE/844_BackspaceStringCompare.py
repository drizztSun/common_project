# 844. Backspace String Compare

# Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

# Example 1:

# Input: S = "ab#c", T = "ad#c"
# Output: true
# Explanation: Both S and T become "ac".

# Example 2:

# Input: S = "ab##", T = "c#d#"
# Output: true
# Explanation: Both S and T become "".

# Example 3:

# Input: S = "a##c", T = "#a#c"
# Output: true
# Explanation: Both S and T become "c".

# Example 4:

# Input: S = "a#c", T = "b"
# Output: false
# Explanation: S becomes "c" while T becomes "b".
# Note:

# 1 <= S.length <= 200
# 1 <= T.length <= 200
# S and T only contain lowercase letters and '#' characters.
# Follow up:

# Can you solve it in O(N) time and O(1) space?


class BackspaceCompare:
    def doit(self, S, T):

        s = []
        for c in S:
            if c == '#':
                if s:
                    s.pop()
            else:
                s.append(c)

        t = []
        for c in T:
            if c == '#':
                if t:
                    t.pop()
            else:
                t.append(c)
        return s == t

    def doit(self, S, T):

        def build(S):
            ans = []
            for c in S:
                if c != '#':
                    ans.append(c)
                elif ans:
                    ans.pop()
            return "".join(ans)

        return build(S) == build(T)


if __name__ == '__main__':

    res = BackspaceCompare().doit(S="ab#c", T="ad#c")  # true

    res = BackspaceCompare().doit(S="ab##", T="c#d#")  # true

    res = BackspaceCompare().doit(S="a##c", T="#a#c")  # true

    res = BackspaceCompare().doit(S="a#c", T="b")  # false

    res = BackspaceCompare().doit(S="y#fo##f", T="y#f#o##f")  # true

    pass
