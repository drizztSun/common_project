"""
825. Friends Of Appropriate Ages

Some people will make friend requests. The list of their ages is given and ages[i] is the age of the ith person.

Person A will NOT friend request person B (B != A) if any of the following conditions are true:

age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
Otherwise, A will friend request B.

Note that if A requests B, B does not necessarily request A.  Also, people will not friend request themselves.

How many total friend requests are made?

Example 1:

Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: [20,30,100,110,120]
Output: 3
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.


Notes:

1 <= ages.length <= 20000.
1 <= ages[i] <= 120.


"""


class NumFriendRequests:

    """
        O(A)
    """
    def doit_sort_slidingwindow(self, ages: list) -> int:
        import collections
        c = sorted(collections.Counter(ages).items(), reverse=True)
        # print(c)
        res = 0
        i, j = 0, 1
        acc = 0
        while i < len(c):
            # same age
            if c[i][0] > 14:
                res += c[i][1] * (c[i][1] - 1)

            # different age
            if acc > 0:
                acc -= c[i][1]  # prevent self request

            while j < len(c) and c[j][0] > 0.5 * c[i][0] + 7:
                acc += c[j][1]
                j += 1

            # print(i, j, c[i], acc)
            res += c[i][1] * acc
            i += 1
            j = max(j, i + 1)
        return res

    """
    Approach #1: Counting [Accepted]
    Intuition

    Instead of processing all 20000 people, we can process pairs of (age, count) representing how many people are that age.
    Since there are only 120 possible ages, this is a much faster loop.

    Algorithm

    For each pair (ageA, countA), (ageB, countB), if the conditions are satisfied with respect to age, then countA * countB pairs of people made friend requests.

    If ageA == ageB, then we overcounted: we should have countA * (countA - 1) pairs of people making friend requests instead, as you cannot friend request yourself.

    Complexity Analysis

    Time Complexity: O(A^2 + N), where NN is the number of people, and \mathcal{A}A is the number of ages.

    Space Complexity: O(\mathcal{A})O(A), the space used to store count.
    """
    def doit_search(self, ages: list) -> int:
        cnt = [0] * 121
        for c in ages:
            if c not in ages:
                cnt[c] = 0
            cnt[c] += 1

        ans = 0
        for ageA, cntA in enumerate(cnt):
            for ageB, cntB in enumerate(cnt):

                if ageB <= 0.5 * ageA + 7:
                    continue
                if ageB > ageA:
                    continue
                if ageA < 100 < ageB:
                    continue

                ans += cntA * cntB
                if ageA == ageB:
                    ans -= cntA

        return ans
