"""
1345. Jump Game IV


Given an array of integers arr, you are initially positioned at the first index of the array.

In one step you can jump from index i to index:

1) i + 1 where: i + 1 < arr.length.
2) i - 1 where: i - 1 >= 0.
3) j where: arr[i] == arr[j] and i != j.

Return the minimum number of steps to reach the last index of the array.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
Example 2:

Input: arr = [7]
Output: 0
Explanation: Start index is the last index. You don't need to jump.
Example 3:

Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: You can jump directly from index 0 to index 7 which is last index of the array.
Example 4:

Input: arr = [6,1,9]
Output: 2
Example 5:

Input: arr = [11,22,7,7,7,7,7,7,7,22,13]
Output: 3
 

Constraints:

1 <= arr.length <= 5 * 104
-108 <= arr[i] <= 108

"""


class JumpGameIV:

    """
        Approach 1: Breadth-First Search
        Most solutions start from a brute force approach and are optimized by removing unnecessary calculations. Same as this one.

        A naive brute force approach is to iterate all the possible routes and check if there is one reaches the last index. However, if we already checked one index, we do not need to check it again. 
        We can mark the index as visited by storing them in a visited set.

        From convenience, we can store nodes with the same value together in a graph dictionary. 
        With this method, when searching, we do not need to iterate the whole list to find the nodes with the same value as the next steps, but only need to ask the precomputed dictionary. 
        However, to prevent stepping back, we need to clear the dictionary after we get to that value.

        Complexity Analysis

        Assume N is the length of arr.
        Time complexity: O(N) since we will visit every node at most once.
        Space complexity: O(N) since it needs curs and nex to store nodes.

    """
    def doit_bfs(self, arr: list) -> int:
        from collections import defaultdict

        n = len(arr)
        if n <= 1 : return 0

        graph = defaultdict(list)
        for i in range(n):
            graph[arr[i]].append(i)

        cur = [0]  # store current layers
        visited = {0}
        step = 0

        # when current layer exists
        while cur:
            next = []

            # iterate the layer
            for node in cur:
                # check if reached end
                if node == n-1:
                    return step
                # check same value
                for ns in graph[arr[node]]:
                    if ns not in visited:
                        visited.add(ns)
                        next.append(ns)

                # clear the list to prevent redundant search
                graph[arr[node]].clear()

                # check neighbors
                for ns in (node-1, node+1):
                    if 0 <= ns < n and ns not in visited:
                        visited.add(ns)
                        next.append(ns)
            step += 1
            cur = next
        
        return -1


    """
        Approach 2: Bidirectional BFS
        In the later part of our original BFS method, the layer may be long and takes a long time to compute the next layer. In this situation, we can compute the layer from the end, which may be short and takes less time.

        Complexity Analysis

        Assume NN is the length of arr.

        Time complexity: O(N) since we will visit every node at most once, but usually faster than approach 1.

        Space complexity: O(N) since it needs curs, other and nex to store nodes.

    """
    def doit_bfs_bidirect(self, arr) -> int:
        from collections import defaultdict
        n = len(arr)
        if n <= 1:
            return 0

        graph = defaultdict(list)
        for i in range(n):
            graph[arr[i]].append(i)

        curs = set([0])  # store layers from start
        visited = {0, n-1}
        step = 0
        other = set([n-1]) # store layers from end

        # when current layer exists
        while curs:
            # search from the side with fewer nodes
            if len(curs) > len(other):
                curs, other = other, curs
            nex = set()

            # iterate the layer
            for node in curs:

                # check same value
                for child in graph[arr[node]]:
                    if child in other:
                        return step + 1

                    if child not in visited:
                        visited.add(child)
                        nex.add(child)

                # clear the list to prevent redundant search
                graph[arr[node]].clear()

                # check neighbors
                for child in [node-1, node+1]:
                    if child in other:
                        return step + 1
                    
                    if 0 <= child < len(arr) and child not in visited:
                        visited.add(child)
                        nex.add(child)

            curs = nex
            step += 1

        return -1

                






        