"""
332. Reconstruct Itinerary

Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order.
All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:

If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.
For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].

All airports are represented by three capital letters (IATA code).
You may assume all tickets form at least one valid itinerary.
One must use all the tickets once and only once.
Example 1:

Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
Example 2:

Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"].
             But it is larger in lexical order.

"""


class ReconstructItinerary:

    """
    greedy sort postorder
    """
    def doit_greedy_sort_postorder(self, tickets):
        """
        :type tickets: List[List[str]]
        :rtype: List[str]
        """
        import collections
        A = collections.defaultdict(list)
        for c, b in sorted(tickets, reverse=True):
            A[c].append(b)

        route = []
        def search(city):
            while A[city]:
                search(A[city].pop())
            route.append(city)

        search('JFK')
        return route[::-1]

    def doit_(self, tickets: list) -> list:
        from collections import defaultdict
        path = defaultdict(list)
        for c1, c2 in tickets:
            path[c1].append(c2)

        for k in path:
            path[k].sort(reverse=True)

        ans = []

        def visit(city):
            while path[city]:
                c = path[city].pop()
                visit(c)
            ans.append(city)

        visit('JFK')
        return ans[::-1]


if __name__ == '__main__':

    #ReconstructItinerary().doit_([["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]])

    #ReconstructItinerary().doit_([["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]])

    ReconstructItinerary().doit_([["EZE","AXA"],["TIA","ANU"],["ANU","JFK"],["JFK","ANU"],["ANU","EZE"],["TIA","ANU"],["AXA","TIA"],["TIA","JFK"],["ANU","TIA"],["JFK","TIA"]])
