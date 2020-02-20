# 1023. Camelcase Matching

# A query word matches a given pattern if we can insert lowercase letters to the pattern word so that it equals the query.
# (We may insert each character at any position, and may insert 0 characters.)

# Given a list of queries, and a pattern, return an answer list of booleans, where answer[i] is true if and only if queries[i] matches the pattern.


# Example 1:

# Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
# Output: [true,false,true,true,false]
# Explanation:
# "FooBar" can be generated like this "F" + "oo" + "B" + "ar".
# "FootBall" can be generated like this "F" + "oot" + "B" + "all".
# "FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".

# Example 2:

# Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
# Output: [true,false,true,false,false]
# Explanation:
# "FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
# "FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".

# Example 3:

# Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
# Output: [false,true,false,false,false]
# Explanation:
# "FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r" + "T" + "est".


class CamelMatch:
    def doit(self, queries, pattern):

        def match(pattern, s):
            i = 0
            for j in range(len(s)):
                if i < len(pattern) and pattern[i] == s[j]:
                    i += 1
                elif s[j].isupper():
                    return False

            return i == len(pattern)

        return [match(pattern, c) for c in queries]

    def doit(self, queries, pattern):

        def get_u(s):
            return [c for c in s if c.isupper()]

        def issup(p, q):
            it = iter(q)  # 迭代器使用in,迭代到就停止
            return all(letter in it for letter in p)

        return [get_u(pattern) == get_u(query) and issup(pattern, query) for query in queries]


if __name__ == '__main__':

    res = CamelMatch().doit(queries=[
        "FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"], pattern="FB")

    res = CamelMatch().doit(queries=[
        "FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"], pattern="FoBa")

    res = CamelMatch().doit(queries=[
        "FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"], pattern="FoBaT")
