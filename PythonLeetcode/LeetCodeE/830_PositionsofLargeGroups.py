# 830. Positions of Large Groups

# In a string S of lowercase letters, these letters form consecutive groups of the same character.

# For example, a string like S = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z" and "yy".

# Call a group large if it has 3 or more characters.  We would like the starting and ending positions of every large group.

# The final answer should be in lexicographic order.


# Example 1:

# Input: "abbxxxxzzy"
# Output: [[3,6]]
# Explanation: "xxxx" is the single large group with starting  3 and ending positions 6.
# Example 2:

# Input: "abc"
# Output: []
# Explanation: We have "a","b" and "c" but no large group.
# Example 3:

# Input: "abcdddeeeeaabbbcd"
# Output: [[3,5],[6,9],[12,14]]

class LargeGroupPositions:

    def doit(self, S):
        ans = []
        i = 0  # The start of each group
        for j in range(len(S)):
            if j == len(S) - 1 or S[j] != S[j+1]:
                # Here, [i, j] represents a group.
                if j-i+1 >= 3:
                    ans.append([i, j])
                i = j+1
        return ans

    def doit(self, S):
        last, s = '', -1
        ans = []
        for i in range(len(S) + 1):
            if i == len(S) or S[i] != last:
                if i - s >= 3:
                    ans.append([s, i-1])
                last = S[i] if i < len(S) else ''
                s = i

        return ans


if __name__ == '__main__':

    res = LargeGroupPositions().doit("abbxxxxzzy")  # [[3,6]]

    res = LargeGroupPositions().doit("abc")  # []

    res = LargeGroupPositions().doit(
        "abcdddeeeeaabbbcd")  # [[3,5],[6,9],[12,14]]

    res = LargeGroupPositions().doit("aaa")  # [[0, 2]]

    pass
