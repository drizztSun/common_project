# 815. Bus Routes

# We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever.
# For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) travels 
# in the sequence 1->5->7->1->5->7->1->... forever.

# We start at bus stop S (initially not on a bus), and we want to go to bus stop T.
# Travelling by buses only, what is the least number of buses we must take to reach our destination?
# Return -1 if it is not possible.

# Example:
# Input: 
# routes = [[1, 2, 7], [3, 6, 7]]
# S = 1
# T = 6
# Output: 2
# Explanation: 
# The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
# Note:

# 1 <= routes.length <= 500.
# 1 <= routes[i].length <= 500.
# 0 <= routes[i][j] < 10 ^ 6.


class NumBusesToDestination:

    # <BFS>
    def doit(self, routes, S, T):
        """
        :type routes: List[List[int]]
        :type S: int
        :type T: int
        :rtype: int
        """
        if S == T:
            return 0
            
        from collections import defaultdict
        s2r = defaultdict(set)
        r2s = defaultdict(set)
        for i in range(len(routes)):
            for j in routes[i]:
                s2r[j].add(i)
                r2s[i].add(j)

        st = list(s2r[S])
        visited = set()
        times = 0
        while st:
            nst = []
            times += 1

            for c in st:
                if c not in visited:
                    visited.add(c)
                    if T in r2s[c]:
                        return times

                    for s in r2s[c]:
                        for r in s2r[s]:
                            if r not in visited:
                                nst.append(r)
            st = nst
  
        return -1


if __name__ == "__main__":

    res = NumBusesToDestination().doit([[1, 2, 7], [3, 6, 7]], 1, 6)

    res = NumBusesToDestination().doit([[1,7],[3,5]], 5, 5)

    pass
        