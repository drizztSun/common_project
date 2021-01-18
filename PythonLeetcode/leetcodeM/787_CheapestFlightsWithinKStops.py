"""
787. Cheapest Flights Within K Stops


There are n cities connected by m flights. Each flight starts from city u and arrives at v with a price w.

Now given all the cities and flights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.

Example 1:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
Output: 200
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
Example 2:
Input: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
Output: 500
Explanation: 
The graph looks like this:


The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
 

Constraints:

The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
The size of flights will be in range [0, n * (n - 1) / 2].
The format of each flight will be (src, dst, price).
The price of each flight will be in the range [1, 10000].
k is in the range of [0, n - 1].
There will not be any duplicated flights or self cycles.



"""


class CheapestFlightsWithKStops:



    def doit_dfs_dijstra(self, n: int, flights: list, src: int, dst: int, K: int) -> int:
        import heapq
        flightsMap = [[-1] * n for _ in range(n)]
        for c in flights:
            flightsMap[c[0]][c[1]] = c[2]

        pq = [(0, src, -1)]

        while pq:
            cost, cur, stops = heapq.heappop(pq)
            if cur == dst:
                return cost
            
            for i in range(n):
                if flightsMap[cur][i] != -1:
                    if stops + 1 <= K:
                        heapq.heappush(pq, (cost + flightsMap[cur][i], i, stops + 1))

        return -1


    """
        Solution
        Approach 1: Dijkstra's Algorithm
        Intuition

        If we forget about the part where the number of stops is limited, then the problem simply becomes the shortest path problem on a weighted graph, right? We can treat this as a graph problem where:

        the cities can be treated as nodes in a graph
        the connections between each of the cities can be treated as the edges and finally
        the cost of going from one city to another would be the weight of the edges in the graph.
        It's important to model the problem in a way that standard algorithms or their slight variations can be used for the solutions. 
        Whenever we have a problem where we're given a bunch of entities and they have some sort of connections between them, more often than not it can be modeled as a graph problem. 
        Once you've figured out that the question can be modeled as a graph problem, you then need to think about the various aspects of a graph i.e.

        directed vs undirected
        weighted vs unweighted
        cyclic vs acyclic
    """
    def doit_dfs_dijstra(self, n: int, flights: list, src: int, dst: int, K: int) -> int:
        import heapq
        # Build the adjacency matrix
        adj_matrix = [[0 for _ in range(n)] for _ in range(n)]
        for s, d, w in flights:
            adj_matrix[s][d] = w
            
        # Shortest distances array
        distances = [float("inf") for _ in range(n)]
        current_stops = [float("inf") for _ in range(n)]
        distances[src], current_stops[src] = 0, 0
        
        # Data is (cost, stops, node)
        minHeap = [(0, 0, src)]     
        
        while minHeap:
            
            cost, stops, node = heapq.heappop(minHeap)
            
            # If destination is reached, return the cost to get here
            if node == dst:
                return cost
            
            # If there are no more steps left, continue 
            if stops == K + 1:
                continue
             
            # Examine and relax all neighboring edges if possible 
            for nei in range(n):
                if adj_matrix[node][nei] > 0:
                    dU, dV, wUV = cost, distances[nei], adj_matrix[node][nei]
                    
                    # Better cost?
                    if dU + wUV < dV:
                        distances[nei] = dU + wUV
                        heapq.heappush(minHeap, (dU + wUV, stops + 1, nei))
                    elif stops < current_stops[nei]:
                        
                        #  Better steps?
                        current_stops[nei] = stops
                        heapq.heappush(minHeap, (dU + wUV, stops + 1, nei))
            
        return -1 if distances[dst] == float("inf") else distances[dst]

    """
        Approach 2: Depth-First-Search with Memoization
        Intuition

        This problem can easily be modeled as a dynamic programming problem on graphs. What does a dynamic programming problem entail?

        It has a recursive structure.
        A bunch of choices to explore at each step.
        Use the optimal solutions for sub-problems to solve top-level problems.
        A base case.

        Algorithm

        We'll define a function called recurse which will take two inputs: node and stops.

        We'll also define a dictionary memo of tuples that will store the optimal solution for each recursion state encountered.

        At each stage, we'll first check if we have reached the destination or not. If we have, then no more moves have to be made and we return a value of 0 since the destination is at a zero distance from itself.

        Next, we check if we have any more stops left. If we don't then we return inf basically representing that we cannot reach the destination from the current recursion state.

        Finally, we check if the current recursion state is cached in the memo dictionary and if it is, we return the answer right away.

        If none of these conditions are met,we progress in our recursion. For that we will iterate over the adjacency matrix to obtain the neighbors for the current node and make a recursive call for each one of them. The node would be the neighboring node and the number of stops would incremeneted by 1.

        To each of these recursion calls, we add the weight of the corresponding edge i.e.

        recurse(neighbor, stops + 1) + weight(node, neighbor)
        We need to return the result of recurse(src, 0) as the answer.


        Complexity Analysis

        Time Complexity: The time complexity for a recursive solution is defined by the number of recursive calls we make and the time it takes to process one recursive call. The number of recursive calls we can potentially make is \text{O}(\text{V} \cdot \text{K})O(V⋅K). In each recursive call, we iterate over a given node's neighbors. That takes time O(\text{V})O(V) because we are using an adjacency matrix. Thus, the overall time complexity is \text{O}(\text{V}^2 \cdot \text{K})O(V 
        2
        ⋅K).
        Space Complexity: \text{O}(\text{V} \cdot \text{K} + \text{V}^2)O(V⋅K+V 
        2
        ) where \text{O}(\text{V} \cdot \text{K})O(V⋅K) is occupied by the memo dictionary and the rest by the adjacency matrix structure we build in the beginning.
    """
    def doit_dfs(self, n: int, flights: list, src: int, dst: int, K: int) -> int:
        
        adj_matrix = [[0 for _ in range(n)] for _ in range(n)]
        memo = {}

        for s, d, w in flights:
            self.adj_matrix[s][d] = w

        def findShortest(node, stops, dst, n):
            
            # No need to go any further if the destination is reached    
            if node == dst:
                return 0
            
            # Can't go any further if no stops left
            if stops < 0:
                return float("inf")
            
            # If the result of this state is already cached, return it
            if (node, stops) in memo:
                return memo[(node, stops)]
            
            # Recursive calls over all the neighbors
            ans = float("inf")
            for neighbor in range(n):
                if adj_matrix[node][neighbor] > 0:
                    ans = min(ans, findShortest(neighbor, stops-1, dst, n) + adj_matrix[node][neighbor])
            
            # Cache the result
            memo[(node, stops)] = ans        
            return ans
        
        result = findShortest(src, K, dst, n)
        return -1 if result == float("inf") else result


    """
        Approach 3: Bellman-Ford
        Intuition

        Let's look at the official definition of the Bellman-Ford algorithm straight from Wikipedia:

        Like Dijkstra's algorithm, Bellman-Ford proceeds by relaxation, in which approximations to the correct distance are replaced by better ones until they eventually reach the solution. 
        In both algorithms, the approximate distance to each vertex is always an overestimate of the true distance and is replaced by the minimum of its old value and the length of a newly found path.

        Complexity Analysis

        Time Complexity: O(K⋅E) since we have K+1 iterations and in each iteration, we go over all the edges in the graph.
        Space Complexity: O(V) occupied by the two distance arrays.
    """
    def doit_bellman_ford(self, n: int, flights: list, src: int, dst: int, K: int) -> int:
        
        # We use two arrays for storing distances and keep swapping
        # between them to save on the memory
        distances = [[float('inf')] * n for _ in range(2)]
        distances[0][src] = distances[1][src] = 0
        
        # K + 1 iterations of Bellman Ford
        for iterations in range(K + 1):
            
            # Iterate over all the edges
            for s, d, wUV in flights:
                
                # Current distance of node "s" from src
                dU = distances[1 - iterations&1][s]
                
                # Current distance of node "d" from src
                # Note that this will port existing values as
                # well from the "previous" array if they didn't already exist
                dV = distances[iterations&1][d]
                
                # Relax the edge if possible
                if dU + wUV < dV:
                    distances[iterations&1][d] = dU + wUV
                    
        return -1 if distances[K&1][dst] == float("inf") else distances[K&1][dst]


    """
        Approach 4: Breadth First Search
        Intuition

        We say that the breadth-first search is a good algorithm to use if we want to find the shortest path in an undirected, unweighted graph. The claim for BFS is that the first time a node is discovered during the traversal, that distance from the source would give us the shortest path. The same cannot be said for a weighted graph. For a weighted graph, there is no correlation between the number of edges composing the path and the actual length of the path which is composed of the weights of all the edges in it. Thus, we cannot employ breadth-first search for weighted graphs.

        Breadth-first search has no way of knowing if a particular discovery of a node would give us the shortest path to that node. And so, the only possible way for BFS (or DFS) to find the shortest path in a weighted graph is to search the entire graph and keep recording the minimum distance from source to the destination vertex.

        That being said, Breadth-first search is actually a great algorithm of choice for this problem because the number of levels to be explored by the algorithm is bounded by K

        The number of levels that the search would go to is limited by the value K+1 in the question. So essentially, we would be trying to find the shortest path, but we won’t have to explore the entire graph as such. We will just go up to the level K+1 and we just need to return the shortest path to the destination (if reachable by level K+1) at the end of the algorithm.

        An important consideration here is the size of the queue. We need to control it somehow otherwise, even at very small depths, the graph could grow exponentially. For this very problem however, we will be able to bound the size of a given level (and hence the queue) by VV, the number of vertices in the graph. Let's think about what it means to encounter the same node multiple times during breadth first traversal.

        Since we will be going only till the level K+1, we don't really have to worry about the number of stops getting exhausted or something. So if the number of stops are out of the way, the only way we will consider adding a node again to the queue is if we found a shorter distance from the source than what we already have stored for that node. If that is not the case then on encountering a node again during the traversal, we can safely discard it i.e not add it to the queue again.

        Since this is weighted graph, we cannot assume anything about the shortest distance from source to a node when its first discovered after being popped from the queue. We will have to go to all the K+1 levels and once we've exhausted K+1 levels, we can be sure that the shortest distances we have are the "best" we can find with K+1 edges or less.

        Algorithm

        This is standard BFS and we'll be using a queue here. Let's call it Q.
        We'll need a dictionary to keep track of shortest distances from the source. An important thing to note in this approach is that we need to keep a dictionary with the node, stops as the key. Basically, we need to keep track of the shortest distance of a node from the source provided that it takes stops stops to reach it.
        Add the source node to the queue. There are multiple ways of tracking the level of a node during breadth-first traversal. We'll be using the size of the queue at the beginning of the level to loop over a particular level.
        We iterate until we exhaust the queue or K+1 levels whichever comes first.
        For each iteration, we pop a node from the queue and iterate over its neighbors which we can get from the adjacency matrix.
        For each of the neighbors, we check if the current edge improves that neighbor's shortest distance from source or not. If it does, then we update the shortest distance dictionary (array) accordingly and also add the neighbor to the queue.
        We continue doing this for until one of our terminal conditions are met.
        We will also maintain an ans variable to track the minimum distance of the destination from the source. At each step, whenever we update the shortest distance of a node from source, we check if that node is the destination and if it is, we will update the ans variable accordingly.
        At the end, we simply check if we were able to reach the destination node by looking at the ans variable's value. If we did reach it, then the recorded distance would be the shortest in under K hops (or K + 1 edges at most).


        Complexity Analysis

        Time Complexity: O(E⋅K) since we can process each edge multiple times depending upon the improvement in the shortest distances. However, the maximum number of times an edge would be processed is bounded by \text{K + 1}K + 1 since that's the number of levels we are going to explore in this algorithm.
        Space Complexity: O(V^2 + V⋅K). The first part is the standard memory occupied by the adjacency matrix and in addition to that, the distances dictionary can occupy a maximum of O(V⋅K).
    """
    def doit_bfs(self, n: int, flights: list, src: int, dst: int, K: int) -> int:
        from collections import deque
        # Build the adjacency matrix
        adj_matrix = [[0 for _ in range(n)] for _ in range(n)]
        for s, d, w in flights:
            adj_matrix[s][d] = w
            
        # Shortest distances dictionary
        distances = {}
        distances[(src, 0)] = 0
        
        # BFS Queue
        bfsQ = deque([src])
        
        # Number of stops remaining
        stops = 0
        ans = float("inf")
        
        # Iterate until we exhaust K+1 levels or the queue gets empty
        while bfsQ and stops < K + 1:
            
            # Iterate on current level
            length = len(bfsQ)
            for _ in range(length):
                node = bfsQ.popleft()
                
                # Loop over neighbors of popped node
                for nei in range(n):
                    if adj_matrix[node][nei] > 0:
                        dU = distances.get((node, stops), float("inf"))
                        dV = distances.get((nei, stops + 1), float("inf"))
                        wUV = adj_matrix[node][nei]
                        
                        # No need to update the minimum cost if we have already exhausted our K stops. 
                        if stops == K and nei != dst:
                            continue
                        
                        if dU + wUV < dV:
                            distances[nei, stops + 1] = dU + wUV
                            bfsQ.append(nei)
                            
                            # Shortest distance of the destination from the source
                            if nei == dst:
                                ans = min(ans, dU + wUV)
            stops += 1   
        
        return -1 if ans == float("inf") else ans