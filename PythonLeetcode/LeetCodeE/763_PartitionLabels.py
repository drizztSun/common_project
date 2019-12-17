# Partition Labels

# A string S of lowercase letters is given. We want to partition this string into as many parts as possible
# so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

# Example 1:
# Input: S = "ababcbacadefegdehijhklij"
# Output: [9,7,8]
# Explanation:
# The partition is "ababcbaca", "defegde", "hijhklij".
# This is a partition so that each letter appears in at most one part.
# A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.


class PartitionLabels:

    def doit(self, s):
        last = {}
        for i in range(len(s)):
            if s[i] not in last:
                last[s[i]] = i
            else:
                last[s[i]] = i
        anchor = 0
        j = 0
        res = []
        for i in range(len(s)):
            j = max(j, last[s[i]])
            if i == j:
                res.append(i-anchor+1)
                anchor = i+1
        return res

    def doit(self, S):

        letter_range = {}
        for i in range(len(S)):
            if S[i] not in letter_range:
                letter_range[S[i]] = [i, i]
            else:
                letter_range[S[i]][1] = i

        vals = [c for c in letter_range.values()]
        vals.sort(key=lambda a: a[0])

        res = []
        s, e = vals[0]
        for i, v in enumerate(vals):
            if v[0] > e:
                res.append((s, e))
                s, e = v[0], v[1]
            elif v[1] > e:
                e = v[1]

            if i == len(vals) - 1:
                res.append((s, e))

        return [e - s + 1 for s, e in res]


if __name__ == '__main__':

    res = PartitionLabels().doit("ababcbacadefegdehijhklij")  # [9, 7, 8]

    pass
