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


"""
Solution
Overview
Overall, we could consider this problem as a graph traversal problem, where an airport can be viewed as a vertex in graph and flight between airports as an edge in graph.

pic

We would like to make a few clarification on the input of the problem, since it is not clear in the description of the problem.
 
As one might notice in the above example, the input graph is NOT what we call a DAG (Directed Acyclic Graph), since we could find at least a cycle in the graph.

In addition, the graph could even have some duplicate edges (i.e. we might have multiple flights with the same origin and destination).

"""

class ReconstructItinerary:

    """
        Approach 1: Backtracking + Greedy
        Intuition

        As common strategies for problems of graph traversal, we often apply the methodologies of backtracking or greedy. As it turns out, we can apply both of them for this problem.

        Typically, backtracking is used to enumerate all possible solutions for a problem, in a trial-fail-and-fallback strategy.

        At each airport, one might have several possible destinations to fly to. With backtracking, we enumerate each possible destination. We mark the choice at each iteration (i.e. trial) before we move on to the chosen destination. If the destination does not lead to a solution (i.e. fail), we would then fallback to the previous state and start another iteration of trial-fail-and-fallback cycle.

        A greedy algorithm is any algorithm that follows the problem-solving heuristic of making locally optimal choice at each step, with the intent of reaching the global optimum at the end.

        As suggested by its definition, a greedy algorithm does not necessarily lead to a globally optimal solution, but rather a reasonable approximation in exchange of less computing time.

        Nonetheless, sometimes it is the way to produce a global optimum for certain problems. This is the case for this problem as well.

        At each airport, given a list of possible destinations, while backtracking, at each step we would pick the destination greedily in lexical order, i.e. the one with the smallest lexical order would have its trial first.

        With this greedy strategy, we would ensure that the final solution that we find would have the smallest lexical order, because all other solutions that have smaller lexical order have been trialed and failed during the process of backtracking.

        Algorithm

        Here we explain how we implement a solution for this problem, by combining the strategies of backtracking and greedy.

        As the first step, we build a graph data structure from the given input. This graph should allow us to quickly identify a list of potential destinations, given an origin. Here we adopted the hashmap (or dictionary) data structure, with each entry as <origin, [destinations]>.

        Then due to our greedy strategy, we then should order the destination list for each entry in lexical order. As an alternative solution, one could use PriorityQueue data structure in the first step to keep the list of destinations, which would maintain the order at the moment of constructing the list.

        As the final step, we kick off the backtracking traversal on the above graph, to obtain the final result.

        At the beginning of the backtracking function, as the bottom case, we check if we have already obtained a valid itinerary.

        Otherwise, we enumerate the next destinations in order.

        We mark the status of visit, before and after each backtracking loop.

    """
    def findItinerary(self, tickets):
        """
        :type tickets: List[List[str]]
        :rtype: List[str]
        """
        from collections import defaultdict
        flightMap = defaultdict(list)

        def backtracking(origin, route):
            if len(route) == flights + 1:
                result = route
                return True

            for i, nextDest in enumerate(flightMap[origin]):
                if not visitBitmap[origin][i]:
                    # mark the visit before the next recursion
                    visitBitmap[origin][i] = True
                    ret = backtracking(nextDest, route + [nextDest])
                    visitBitmap[origin][i] = False
                    if ret:
                        return True
            return False

        for ticket in tickets:
            origin, dest = ticket[0], ticket[1]
            flightMap[origin].append(dest)

        visitBitmap = {}

        # sort the itinerary based on the lexical order
        for origin, itinerary in flightMap.items():
        # Note that we could have multiple identical flights, i.e. same origin and destination.
            itinerary.sort()
            visitBitmap[origin] = [False]*len(itinerary)

        flights = len(tickets)
        result = []
        route = ['JFK']
        backtracking('JFK', route)

        return result

    """
        Approach 2: Hierholzer's Algorithm

        Eulerian Cycle

        In graph theory, an Eulerian trail (or Eulerian path) is a trail in a finite graph that visits every edge exactly once (allowing for revisiting vertices).

        In our problem, we are asked to construct an itinerary that uses all the flights (edges), starting from the airport of "JFK". As one can see, the problem is actually a variant of Eulerian path, with a fixed starting point.

        Similarly, an Eulerian circuit or Eulerian cycle is an Eulerian trail that starts and ends on the same vertex.

        The Eulerian cycle problem has been discussed by Leonhard Euler back in 1736. Ever since, there have been several algorithms proposed to solve the problem.

        In 1873, Hierholzer proposed an efficient algorithm to find the Eulerian cycle in linear time (\mathcal{O}(|E|)O(∣E∣)). One could find more details about the Hierholzer's algorithm in this course.

        The basic idea of Hierholzer's algorithm is the stepwise construction of the Eulerian cycle by connecting disjunctive circles.

        To be more specific, the algorithm consists of two steps:

        It starts with a random node and then follows an arbitrary unvisited edge to a neighbor. This step is repeated until one returns to the starting node. This yields a first circle in the graph.

        If this circle covers all nodes it is an Eulerian cycle and the algorithm is finished. Otherwise, one chooses another node among the cycles' nodes with unvisited edges and constructs another circle, called subtour.

        pic

        By connecting all the circles in the above process, we build the Eulerian cycle at the end.

        Eulerian Path

        To find the Eulerian path, inspired from the original Hierzolher's algorithm, we simply change one condition of loop, rather than stopping at the starting point, we stop at the vertex where we do not have any unvisited edges.

        To summarize, the main idea to find the Eulerian path consists of two steps:

        Step 1). Starting from any vertex, we keep following the unused edges until we get stuck at certain vertex where we have no more unvisited outgoing edges.

        Step 2). We then backtrack to the nearest neighbor vertex in the current path that has unused edges and we repeat the process until all the edges have been used.

        The first vertex that we got stuck at would be the end point of our Eulerian path. So if we follow all the stuck points backwards, we could reconstruct the Eulerian path at the end.

        Algorithm

        Now let us get back to our itinerary reconstruction problem. As we know now, it is a problem of Eulerian path, except that we have a fixed starting point.

        More importantly, as stated in the problem, the given input is guaranteed to have a solution. So we have one less issue to consider.

        As a result, our final algorithm is a bit simpler than the above Eulerian path algorithm, without the backtracking step.

        The essential step is that starting from the fixed starting vertex (airport 'JFK'), we keep following the ordered and unused edges (flights) until we get stuck at certain vertex where we have no more unvisited outgoing edges.

        The point that we got stuck would be the last airport that we visit. And then we follow the visited vertex (airport) backwards, we would obtain the final itinerary.

        Here are some sample implementations which are inspired from a thread of discussion in the forum.

    """
    def findItinerary(self, tickets):
        """
        :type tickets: List[List[str]]
        :rtype: List[str]
        """
        from collections import defaultdict
        flightMap = defaultdict(list)

        def DFS(self, origin):
            destList = flightMap[origin]
            while destList:
                #while we visit the edge, we trim it off from graph.
                nextDest = destList.pop()
                DFS(nextDest)
            result.append(origin)

        for ticket in tickets:
            origin, dest = ticket[0], ticket[1]
            flightMap[origin].append(dest)

        # sort the itinerary based on the lexical order
        for origin, itinerary in flightMap.items():
        # Note that we could have multiple identical flights, i.e. same origin and destination.
            itinerary.sort(reverse=True)

        result = []
        DFS('JFK')

        # reconstruct the route backwards
        return result[::-1]


    """
    greedy sort children + postorder traversel
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

    ReconstructItinerary().doit_greedy_sort_postorder([["JFK", "KUL"], ["JFK", "NRT"], ["NRT", "JFK"]])

    ReconstructItinerary().doit_greedy_sort_postorder([["JFK", "KUL"], ["JFK", "NRT"], ["KUL", "JFK"]])

    ReconstructItinerary().doit_greedy_sort_postorder([["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]])

    ReconstructItinerary().doit_greedy_sort_postorder([["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]])

    ReconstructItinerary().doit_greedy_sort_postorder([["EZE","AXA"],["TIA","ANU"],["ANU","JFK"],["JFK","ANU"],["ANU","EZE"],["TIA","ANU"],["AXA","TIA"],["TIA","JFK"],["ANU","TIA"],["JFK","TIA"]])
