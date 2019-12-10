# 791. Custom Sort String

# S and T are strings composed of lowercase letters. In S, no letter occurs more than once.
#
# S was sorted in some custom order previously. We want to permute the characters of T so that they match the order
# that S was sorted. More specifically, if x occurs before y in S, then x should occur before y in the returned string.
#
# Return any permutation of T (as a string) that satisfies this property.
#
# Example :
# Input:
# S = "cba"
# T = "abcd"
# Output: "cbad"
# Explanation:
# "a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a".
# Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
#
#
# Note:
#
# S has length at most 26, and no character is repeated in S.
# T has length at most 200.
# S and T consist of lowercase letters only.

from collections import Counter, defaultdict

class CustomSortString:

    def doit1(self, S, T):

        order_list = {S[i]: i for i in range(len(S))}

        def helper(cur, tmp, currentRes):
            if len(tmp) == 1:
                return None if tmp in order_list and order_list[tmp] < cur else currentRes + tmp

            for i, c in enumerate(tmp):
                if c in order_list and order_list[c] < cur:
                    return

                res = helper(order_list[c], tmp[:i]+tmp[i+1:], currentRes + c)
                if res:
                    return res

            return

        return helper(-1, T, '')


    def doit(self, S, T):
        counter = Counter(T)
        output = []

        for s in S:
            if s in counter:
                output.append(s * counter[s])
                del counter[s]

        for c, freq in counter.items():
            output.append(c * freq)

        return ''.join(output)


    def doit(self, S, T):
        d = {l:"" for l in S}
        out = ""
        end = ""
        for t in T:
            if t in d:
                d[t]+=t
            else:
                end+=t
        for key in d:
            out+=d[key]

        return out+end

    def doit(self, S, T):
        S_set = set(S)
        occurrence = defaultdict(int)
        remaining = ""

        for c in T:
            if c in S_set:
                occurrence[c] += 1
            else:
                remaining += c

        result = ""
        for c in S:
            result += c * occurrence[c]

        result += remaining
        return result


if __name__ == '__main__':

    res = CustomSortString().doit("cba", "abcd") # cbad

    res = CustomSortString().doit("exv", "xwvee") #
