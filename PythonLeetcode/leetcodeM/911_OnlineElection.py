# 911. Online Election

# In an election, the i-th vote was cast for persons[i] at time times[i].

# Now, we would like to implement the following query function:
# TopVotedCandidate.q(int t) will return the number of the person that was leading the election at time t.

# Votes cast at time t will count towards our query.  In the case of a tie, the most recent vote (among tied candidates) wins.


# Example 1:

# Input: ["TopVotedCandidate","q","q","q","q","q","q"], [[[0,1,1,0,0,1,0],[0,5,10,15,20,25,30]],[3],[12],[25],[15],[24],[8]]
# Output: [null,0,1,1,0,0,1]
# Explanation:
# At time 3, the votes are [0], and 0 is leading.
# At time 12, the votes are [0,1,1], and 1 is leading.
# At time 25, the votes are [0,1,1,0,0,1], and 1 is leading (as ties go to the most recent vote.)
# This continues for 3 more queries at time 15, 24, and 8.


# Note:

# 1 <= persons.length = times.length <= 5000
# 0 <= persons[i] <= persons.length
# times is a strictly increasing array with all elements in [0, 10^9].
# TopVotedCandidate.q is called at most 10000 times per test case.
# TopVotedCandidate.q(int t) is always called with t >= times[0].

from bisect import bisect_right


class TopVotedCandidate:

    def __init__(self, persons, times):

        self._times = times
        self._res = []
        cnt, maxk = {}, (-1, -1)

        for i in range(len(persons)):
            cnt[persons[i]] = cnt.get(persons[i], 0) + 1
            if maxk[0] <= cnt[persons[i]]:
                maxk = (cnt[persons[i]], persons[i])
            self._res.append(maxk[1])

    def q(self, t):
        import bisect
        i = bisect.bisect_right(self._times, t)
        return self._res[i-1]


class Solution:

    def __init__(self, persons, times):
        idx, n0, p0 = {}, -1, -1
        for i, (p, t) in enumerate(zip(persons, times)):
            idx[p] = n = idx.get(p, 0) + 1
            if n < n0:
                persons[i] = p0
            else:
                n0, p0 = n, p
        self.ps, self.ts = persons, times

    def q(self, t: int):
        ps, ts = self.ps, self.ts
        if t < ts[-1]:
            return ps[bisect_right(ts, t) - 1]
        return ps[-1]


"""
Approach 1: List of Lists + Binary Search
Intuition and Algorithm

We can store the votes in a list A of lists of votes. Each vote has a person and a timestamp, and A[count] is a list of the count-th votes received for that person.

Then, A[i][0] and A[i] are monotone increasing, so we can binary search on them to find the most recent vote by time.

Complexity Analysis

Time Complexity: O(N + Q \log^2 N), where NN is the number of votes, and QQ is the number of queries.

Space Complexity: O(N).

"""


class TopVotedCandidate1(object):

    def __init__(self, persons, times):
        self.A = []
        self.count = collections.Counter()
        for p, t in zip(persons, times):
            self.count[p] = c = self.count[p] + 1
            while len(self.A) <= c:
                self.A.append([])
            self.A[c].append((t, p))

    def q(self, t):
        lo, hi = 1, len(self.A)
        while lo < hi:
            mi = (lo + hi) / 2
            if self.A[mi][0][0] <= t:
                lo = mi + 1
            else:
                hi = mi
        i = lo - 1
        j = bisect.bisect(self.A[i], (t, float('inf')))
        return self.A[i][j-1][1]


"""
Approach 2: Precomputed Answer + Binary Search
Intuition and Algorithm

As the votes come in, we can remember every event (winner, time) when the winner changes.
After, we have a sorted list of these events that we can binary search for the answer.

Complexity Analysis

Time Complexity: O(N+QlogN), where NN is the number of votes, and QQ is the number of queries.

Space Complexity: O(N).
"""


class TopVotedCandidate(object):
    def __init__(self, persons, times):
        self.A = []
        count = collections.Counter()
        leader, m = None, 0  # leader, num votes for leader

        for p, t in itertools.izip(persons, times):
            count[p] += 1
            c = count[p]
            if c >= m:
                if p != leader:  # lead change
                    leader = p
                    self.A.append((t, leader))

                if c > m:
                    m = c

    def q(self, t):
        i = bisect.bisect(self.A, (t, float('inf')), 1)
        return self.A[i-1][1]


if __name__ == '__main__':

    obj = TopVotedCandidate([0, 1, 1, 0, 0, 1, 0], [0, 5, 10, 15, 20, 25, 30])

    res = obj.q(3)

    res = obj.q(12)

    res = obj.q(25)

    res = obj.q(15)

    res = obj.q(24)

    res = obj.q(8)

    obj = TopVotedCandidate([0, 1, 2, 2, 1], [20, 28, 29, 54, 56])

    res = obj.q(28)

    res = obj.q(53)

    res = obj.q(57)

    res = obj.q(29)

    res = obj.q(29)

    res = obj.q(28)

    res = obj.q(30)

    res = obj.q(20)

    res = obj.q(56)

    res = obj.q(55)

    pass
