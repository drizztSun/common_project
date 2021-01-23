"""
1733. Minimum Number of People to Teach

On a social network consisting of m users and some friendships between users, two users can communicate with each other if they know a common language.

You are given an integer n, an array languages, and an array friendships where:

1) There are n languages numbered 1 through n,
2) languages[i] is the set of languages the i-th user knows, and
3) friendships[i] = [ui, vi] denotes a friendship between the users ui and vi.
You can choose one language and teach it to some users so that all friends can communicate with each other. Return the minimum number of users you need to teach.

Note that friendships are not transitive, meaning if x is a friend of y and y is a friend of z, this doesn't guarantee that x is a friend of z.


Example 1:

Input: n = 2, languages = [[1],[2],[1,2]], friendships = [[1,2],[1,3],[2,3]]
Output: 1
Explanation: You can either teach user 1 the second language or user 2 the first language.
Example 2:

Input: n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
Output: 2
Explanation: Teach the third language to users 1 and 2, yielding two users to teach.


Constraints:

2 <= n <= 500
languages.length == m
1 <= m <= 500
1 <= languages[i].length <= n
1 <= languages[i][j] <= n
1 <= ui < vi <= languages.length
1 <= friendships.length <= 500
All tuples (ui, vi) are unique
languages[i] contains only unique values


"""


class MinimumNumberOfPeopleToTeach:

    """
        Explanation
        Enumerate the lanuage k we want to teach.
        For two friends,
        if they don't speak the same lanuage,
        we need to teach them speaking lanuage k.


        Complexity
        Time O(nmm)
        Space O(mn)

    """

    def doit_(self, n: int, languages: list, friendships: list) -> int:

        languages = list(map(set, languages))
        res = m = len(friendships)

        for k in range(1, n + 1):
            teach = set()
            for i, j in friendships:
                if languages[i - 1] & languages[j - 1]:
                    continue

                if k not in languages[i - 1]:
                    teach.add(i)

                if k not in languages[j - 1]:
                    teach.add(j)

            res = min(res, len(teach))

        return res


if __name__ == '__main__':

    MinimumNumberOfPeopleToTeach().doit_()