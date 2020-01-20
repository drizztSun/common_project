# 893. Groups of Special-Equivalent Strings

# You are given an array A of strings.

# A move onto S consists of swapping any two even indexed characters of S, or any two odd indexed characters of S.

# Two strings S and T are special-equivalent if after any number of moves onto S, S == T.

# For example, S = "zzxy" and T = "xyzz" are special-equivalent because we may make the moves "zzxy" -> "xzzy" -> "xyzz" that swap S[0] and S[2], then S[1] and S[3].

# Now, a group of special-equivalent strings from A is a non-empty subset of A such that:

# Every pair of strings in the group are special equivalent, and;
# The group is the largest size possible (ie., there isn't a string S not in the group such that S is special equivalent to every string in the group)
# Return the number of groups of special-equivalent strings from A.


# Example 1:

# Input: ["abcd","cdab","cbad","xyzz","zzxy","zzyx"]
# Output: 3
# Explanation:
# One group is ["abcd", "cdab", "cbad"], since they are all pairwise special equivalent, and none of the other strings are all pairwise special equivalent to these.

# The other two groups are ["xyzz", "zzxy"] and ["zzyx"].  Note that in particular, "zzxy" is not special equivalent to "zzyx".

# Example 2:

# Input: ["abc","acb","bac","bca","cab","cba"]
# Output: 3


# Note:

# 1 <= A.length <= 1000
# 1 <= A[i].length <= 20
# All A[i] have the same length.
# All A[i] consist of only lowercase letters.

"""
Approach 1: Counting
Intuition and Algorithm

Let's try to characterize a special-equivalent string SS, by finding a function \mathcal{C}C so that S \equiv T \iff \mathcal{C}(S) = \mathcal{C}(T)S≡T⟺C(S)=C(T).

Through swapping, we can permute the even indexed letters, and the odd indexed letters. What characterizes these permutations is the count of the letters: all such permutations have the same count, and different counts have different permutations.

Thus, the function \mathcal{C}(S) =C(S)= (the count of the even indexed letters in S, followed by the count of the odd indexed letters in S) successfully characterizes the equivalence relation.

Afterwards, we count the number of unique \mathcal{C}(S)C(S) for S \in AS∈A.

Complexity Analysis

Time Complexity: O(i∑(Ai).length)

Space Complexity: O(N), where NN is the length of A.

"""


class NumSpecialEquivGroups:

    def doit(self, A):

        def count(word):
            ans = [0] * 52
            for i, c in enumerate(word):
                ans[ord(c) - ord('a') + 26 * (i % 2)] += 1
            return tuple(ans)

        return len({count(w) for w in A})

    def doit(self, A):
        return len(set("".join(sorted(s[0::2])) + "".join(sorted(s[1::2])) for s in A))


if __name__ == '__main__':

    res = NumSpecialEquivGroups().doit(
        ["abcd", "cdab", "cbad", "xyzz", "zzxy", "zzyx"])  # 3

    res = NumSpecialEquivGroups().doit(
        ["abc", "acb", "bac", "bca", "cab", "cba"])

    pass
