"""
261. Graph Valid Tree


Given n nodes labeled from 0 to n-1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

Example 1:

Input: n = 5, and edges = [[0,1], [0,2], [0,3], [1,4]]
Output: true
Example 2:

Input: n = 5, and edges = [[0,1], [1,2], [2,3], [1,3], [1,4]]
Output: false
Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0,1] is the same as [1,0] and thus will not appear together in edges.





Solution
For this article, we'll assume that you've already learned the basics of graph theory, and how to perform a simple depth-first search. Most text books on algorithms or discrete math have a section on it.

There are a lot of different ways to solve this problem, and it's impossible to cover them all. For that reason, I've tried to split the ways into a few general approaches, and then for each I discuss a few additional variants. 
ome of the ideas that were covered in Approach 1 might apply to Approach 2 as well.



"""


class GraphValidTree:

    """
        Approach 1: Graph Theory + Iterative Depth-First Search
        Intuition

        Note that this same approach also works with recursive depth-first search and iterative breadth-first search. We'll look at these briefly in the Algorithm section.

        Recall that a graph, G, is a tree iff the following two conditions are met:

        G is fully connected. In other words, for every pair of nodes in G, there is a path between them.
        G contains no cycles. In other words, there is exactly one path between each pair of nodes in G.
        Depth-first search is a classic graph-traversal algorithm that can be used to check for both of these conditions:

        G is fully connected if, and only if, we started a depth-first search from a single source and discovered all nodes in G during it.
        G contains no cycles if, and only if, the depth-first search never goes back to an already discovered node. We need to be careful though not to count trivial cycles of the form A → B → A that occur with most implementations of undirected edges.
        Depth-first search requires being able to look up the adjacent (immediate neighbours) of a given node. Like many graph interview problems though, the input format we're given doesn't allow us to quickly get the neighbours of a node. Therefore, our first step is to convert the input into an adjacency list. Recall that an adjacency list is where we have a list of sub-lists, where each sub-list is the list of the immediate neighbours for the i'th node.



    """
    def doit_dfs(self, n: int, edges: list) -> bool:
        
        if len(edges) != n - 1: return False
        
        adj_list = [[] for _ in range(n)]
        for A, B in edges:
            adj_list[A].append(B)
            adj_list[B].append(A)
        
        parent = {0: -1}
        stack = [0]
        
        while stack:
            node = stack.pop()
            for neighbour in adj_list[node]:
                if neighbour == parent[node]:
                    continue
                if neighbour in parent:
                    return False
                parent[neighbour] = node
                stack.append(neighbour)
        
        return len(parent) == n

    """
        Alternatively, you could use recursion, as long as you're fairly confident with it. The recursive approach is more elegant, but is considered inferior to the iterative version in some programming languages, 
        such as Python. This is because the space used by run-time stacks vary between programming languages.

        On the plus side, we can use a simple seen set and just pass a parent parameter. This makes the code a bit simpler!
    """
    def doit_dfs_recursive(self, n: int, edges: list) -> bool:
    
        if len(edges) != n - 1: return False
        
        adj_list = [[] for _ in range(n)]
        for A, B in edges:
            adj_list[A].append(B)
            adj_list[B].append(A)
        
        seen = set()
        
        def dfs(node, parent):
            if node in seen: return;
            seen.add(node)
            for neighbour in adj_list[node]:
                if neighbour == parent:
                    continue
                if neighbour in seen:
                    return False
                result = dfs(neighbour, node)
                if not result: return False
            return True
        
        # We return true iff no cycles were detected,
        # AND the entire graph has been reached.
        return dfs(0, -1) and len(seen) == n

    """
        Yet another variant is to use iterative breadth-first search. Recall that breadth-first search and depth-first search are almost the same algorithm, just with a different data structure.

        Complexity Analysis

        Let EE be the number of edges, and NN be the number of nodes.

        Time Complexity : O(N + E)O(N+E).

        Creating the adjacency list requires initialising a list of length NN, with a cost of O(N)O(N), and then iterating over and inserting EE edges, for a cost of O(E)O(E). This gives us O(E) + O(N) = O(N + E)O(E)+O(N)=O(N+E).

        Each node is added to the data structure once. This means that the outer loop will run NN times. For each of the NN nodes, its adjacent edges is iterated over once. In total, this means that all EE edges are iterated over once by the inner loop. This, therefore, gives a total time complexity of O(N + E)O(N+E).

        Because both parts are the same, we get a final time complexity of O(N + E)O(N+E).

        Space Complexity : O(N + E)O(N+E).

        The adjacency list is a list of length NN, with inner lists with lengths that add to a total of EE. This gives a total of O(N + E)O(N+E) space.

        In the worst case, the stack/ queue will have all NN nodes on it at the same time, giving a total of O(N)O(N) space.

        In total, this gives us O(E + N)O(E+N) space.
    """
    def validTree(self, n: int, edges: list) -> bool:
        import collections
        if len(edges) != n - 1: return False
        
        adj_list = [[] for _ in range(n)]
        for A, B in edges:
            adj_list[A].append(B)
            adj_list[B].append(A)
        
        parent = {0: -1}
        queue = collections.deque([0])
        
        while queue:
            node = queue.popleft()
            for neighbour in adj_list[node]:
                if neighbour == parent[node]:
                    continue
                if neighbour in parent:
                    return False
                parent[neighbour] = node
                queue.append(neighbour)
        
        return len(parent) == n

    """
        Approach 2: Advanced Graph Theory + Iterative Depth-First Search
        Intuition

        Depending on how much graph theory you know, there's a better definition for determining whether or not a given graph is a tree.

        For the graph to be a valid tree, it must have exactly n - 1 edges. Any less, and it can't possibly be fully connected. Any more, and it has to contain cycles. Additionally, if the graph is fully connected and contains exactly n - 1 edges, it can't possibly contain a cycle, and therefore must be a tree!

        These facts are fairly straightforward to prove. We won't go into why they are true here, but if you're not familiar with these facts, then we recommend reading up on graph theory. It is very important to be confident with graph theory in-order to pass the interviews at a top tech company.

        Going by this definition, our algorithm needs to do the following:

        Check whether or not there are n - 1 edges. If there's not, then return false.
        Check whether or not the graph is fully connected. Return true if it is, false if otherwise.
        Recall that the most complicated part of Approach 1 was in checking whether or not the graph contained cycles. This was because in an undirected graph, we needed to be careful of trivial cycles. Checking whether or not a graph is fully connected is straightforward—we simply checked if all nodes were reachable from a search starting at a single node.

        Like before, we can can check for connectivity using recursive depth-first search, iterative depth-first search, or iterative breadth-first search. We still need to use a seen set to prevent the algorithm getting caught in an infinite loop if there are indeed cycles (and to prevent looping on the trivial cycles).

        Algorithm

        Again, we've provided code for all three variants.

        Iterative Depth-First Search.

        Complexity Analysis

        Let EE be the number of edges, and NN be the number of nodes.

        Time Complexity : O(N).

        When E ≠ N - 1, we simply return false. Therefore, the worst case is when E = N - 1E=N−1. Because EE is proportional to NN, we'll say E = NE=N to simplify the analysis.

        As said above, creating an adjacency list has a time complexity of O(N + E)O(N+E). Because EE is now bounded by NN, we can reduce this slightly to O(N + N) = O(N)O(N+N)=O(N).

        The iterative breadth-first search and depth-first search are almost identical. Each node is put onto the queue/stack once, ensured by the seen set. Therefore, the inner "neighbour" loop runs once for each node. Across all nodes, the number of cycles this loop does is the same as the number of edges, which is simply NN. Therefore, these two algorithms have a time complexity of O(N)O(N).

        The recursive depth-first search's "neighbour" loop runs only once for each node. Therefore, in total, the function is called once for each edge. So it is called $E = N times, and NN of those times, it actually enters the "neighbour" loop. Collectively, the total number of iterations of the "neighbour" loop is E = NE=N. So we get O(N)O(N), as these all simply add.

        Space Complexity : O(N)O(N).

        Previously, we determined that the adjacency list took O(E + N)O(E+N) space. We now know this is simply O(N)O(N).

        In the worst case, the search algorithms will require an additional O(N)O(N) space; this is if all nodes were on the stack/queue at the same time.

        So again we get a total of O(N)O(N).
    """
    def doit_dfs_1(self, n: int, edges: list) -> bool:
        
        # find the loop
        if len(edges) != n - 1: return False
        
        # Create an adjacency list.
        adj_list = [[] for _ in range(n)]
        for A, B in edges:
            adj_list[A].append(B)
            adj_list[B].append(A)
        
        # We still need a seen set to prevent our code from infinite
        # looping if there *is* cycles (and on the trivial cycles!)
        seen = {0}
        stack = [0]
        
        while stack:
            node = stack.pop()
            for neighbour in adj_list[node]:
                if neighbour in seen:
                    continue
                seen.add(neighbour)
                stack.append(neighbour)
        
        return len(seen) == n

    def doit_dfs_recursive(self, n: int, edges: list) -> bool:
        
        if len(edges) != n - 1: return False
        
        # Create an adjacency list.
        adj_list = [[] for _ in range(n)]
        for A, B in edges:
            adj_list[A].append(B)
            adj_list[B].append(A)
        
        # We still need a seen set to prevent our code from infinite
        # looping if there *is* cycles (and on the trivial cycles!)
        seen = set()

        def dfs(node):
            if node in seen: return
            seen.add(node)
            for neighbour in adj_list[node]:
                dfs(neighbour)

        dfs(0)
        return len(seen) == n

    def doit_bfs(self, n: int, edges: list) -> bool:
        import collections
        if len(edges) != n - 1: return False
        
        # Create an adjacency list.
        adj_list = [[] for _ in range(n)]
        for A, B in edges:
            adj_list[A].append(B)
            adj_list[B].append(A)
        
        # We still need a seen set to prevent our code from infinite
        # looping if there *is* cycles (and on the trivial cycles!)
        seen = {0}
        queue = collections.deque([0])
        
        while queue:
            node = queue.popleft()
            for neighbour in adj_list[node]:
                if neighbour in seen:
                    continue
                seen.add(neighbour)
                queue.append(neighbour)
        
        return len(seen) == n

"""
    Approach 3: Advanced Graph Theory + Union Find
    Intuition

    In Approach 2, we used this definition for a tree:

    For the graph to be a valid tree, it must have exactly n - 1 edges. Any less, and it can't possibly be fully connected. Any more, and it has to contain cycles. Additionally, if the graph is fully connected and contains exactly n - 1 edges, it can't possibly contain a cycle, and therefore must be a tree!

    This definition simplified the problem down to checking whether or not the graph is fully connected. If it is, and if it contains n - 1 edges, then we know it's a tree. In the previous approaches, we used graph search algorithms to check whether or not all nodes were reachable, starting from a single source node.

    Another way we could approach the problem is by considering each connected component to be a set of nodes. When an edge is put between two separate connected components, they are merged into a single connected component. We'll use the example n = 6 and edges = [(0, 5), (4, 0), (1, 2), (4, 5), (3, 2)]. Before we look at the edges, we have 6 sets.


    Complexity Analysis

    Let EE be the number of edges, and NN be the number of nodes.

    α(N)α(N) is the Inverse Ackermann Function.

    Time Complexity : O(N \cdot α(N))O(N⋅α(N)).

    When E ≠ N - 1, we simply return false. Therefore, the worst case is when E = N - 1E=N−1. Because EE is proportional to NN, we'll say E = NE=N to simplify the analysis.

    We are putting each of the NN edges into the UnionFind data structure, using the union(...) method. The union(...) method itself has no loops or recursion, so the entire cost of calling it is dependent on the cost of the find(...) method that it calls.

    find(...)'s cost is dependent on how far the node it was searching for is from the root. Using the naïve implementation of union find, this depth could be NN. If this was the case for all of the calls, we'd have a final cost of O(N^2)O(N 
    2
    ).

    However, remember those optimizations we did? Those keep the tree depths very shallow. It turns out that find(...) amortizes to O(α(N))O(α(N)), where α is the Inverse Ackermann Function. The incredible thing about this function is that it grows so slowly that NN will never go higher than 44 in the universe as we know it! So while in "practice" it is effectively O(1)O(1), in "theory" it is not.

    Actually proving this upper bound on the depth is a very advanced proof, which I'd certainly hope you'd never need to do in an interview! If you're interested though, I recommend looking in a good algorithm's text book or paper.

    Anyway, this gives us a total of N \cdot O(α(N)) = O(N \cdot α(N))N⋅O(α(N))=O(N⋅α(N)).

    Space Complexity : O(N)O(N).

    The UnionFind data structure requires O(N) space to the store the arrays it uses.
"""
class UnionFind:
    
    # For efficiency, we aren't using makeset, but instead initialising
    # all the sets at the same time in the constructor.
    def __init__(self, n):
        self.parent = [node for node in range(n)]
        
    # The find method, without any optimizations. It traces up the parent
    # links until it finds the root node for A, and returns that root.
    def find(self, A):
        while A != self.parent[A]:
            A = self.parent[A]
        return A
        
    # The union method, without any optimizations. It returns True if a
    # merge happened, False if otherwise.
    def union(self, A, B):
        # Find the roots for A and B.
        root_A = self.find(A)
        root_B = self.find(B)
        # Check if A and B are already in the same set.
        if root_A == root_B:
            return False
        # Merge the sets containing A and B.
        self.parent[root_A] = root_B
        return True

class Solution:
    def validTree(self, n: int, edges: list) -> bool:
        # Condition 1: The graph must contain n - 1 edges.
        if len(edges) != n - 1: return False
        
        # Condition 2: The graph must contain a single connected component.
        # Create a new UnionFind object with n nodes. 
        unionFind = UnionFind(n)
        # Add each edge. Check if a merge happened, because if it 
        # didn't, there must be a cycle.
        for A, B in edges:
            if not unionFind.union(A, B):
                return False
        # If we got this far, there's no cycles!
        return True


class UnionFind:
    
    # For efficiency, we aren't using makeset, but instead initialising
    # all the sets at the same time in the constructor.
    def __init__(self, n):
        self.parent = [node for node in range(n)]
        # We use this to keep track of the size of each set.
        self.size = [1] * n
        
    # The find method, with path compression. There are ways of implementing
    # this elegantly with recursion, but the iterative version is easier for
    # most people to understand!
    def find(self, A):
        # Step 1: Find the root.
        root = A
        while root != self.parent[root]:
            root = self.parent[root]
        # Step 2: Do a second traversal, this time setting each node to point
        # directly at A as we go.
        while A != root:
            old_root = self.parent[A]
            self.parent[A] = root
            A = old_root
        return root
        
    # The union method, with optimization union by size. It returns True if a
    # merge happened, False if otherwise.
    def union(self, A, B):
        # Find the roots for A and B.
        root_A = self.find(A)
        root_B = self.find(B)
        # Check if A and B are already in the same set.
        if root_A == root_B:
            return False
        # We want to ensure the larger set remains the root.
        if self.size[root_A] < self.size[root_B]:
            # Make root_B the overall root.
            self.parent[root_A] = root_B
            # The size of the set rooted at B is the sum of the 2.
            self.size[root_B] += self.size[root_A]
        else:
            # Make root_A the overall root.
            self.parent[root_B] = root_A
            # The size of the set rooted at A is the sum of the 2.
            self.size[root_A] += self.size[root_B]
        return True

class Solution:
    def validTree(self, n: int, edges: list) -> bool:
        # Condition 1: The graph must contain n - 1 edges.
        if len(edges) != n - 1: return False
        
        # Create a new UnionFind object with n nodes. 
        unionFind = UnionFind(n)
        
        # Add each edge. Check if a merge happened, because if it 
        # didn't, there must be a cycle.
        for A, B in edges:
            if not unionFind.union(A, B):
                return False
        
        # If we got this far, there's no cycles!
        return True