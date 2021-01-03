"""
# 987. Vertical Order Traversal of a Binary Tree

# Given a binary tree, return the vertical order traversal of its nodes values.

# For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).

# Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes, we report the values of the nodes in order from top to bottom (decreasing Y coordinates).

# If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.

# Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.


# Example 1:

# Input: [3,9,20,null,null,15,7]
# Output: [[9],[3,15],[20],[7]]
# Explanation:
# Without loss of generality, we can assume the root node is at position (0, 0):
# Then, the node with value 9 occurs at position (-1, -1);
# The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
# The node with value 20 occurs at position (1, -1);
# The node with value 7 occurs at position (2, -2).

# Example 2:

# Input: [1,2,3,4,5,6,7]
# Output: [[4],[2],[1,5,6],[3],[7]]
# Explanation:
# The node with value 5 and the node with value 6 have the same position according to the given scheme.
# However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.

# Definition for a binary tree node.

"""
import collections


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class VerticalTraversal:

    def doit(self, root):

        seen = collections.defaultdict(lambda: collections.defaultdict(list))

        def depth(node, x, y):
            if not node:
                return

            seen[x][y].append(node.val)

            depth(node.left, x-1, y+1)
            depth(node.right, x+1, y+1)

        depth(root, 0, 0)

        ans = []
        for x in sorted(seen):
            report = []
            for y in sorted(seen[x]):
                report.extend(sorted(c for c in sorted(seen[x][y])))

            ans.append(report)

        return ans

    def doit(self, root):

        travels = {}
        buff = [(root, 0, 0)]

        while buff:

            buff2 = []

            while buff:
                c, x, y = buff.pop()

                if x not in travels:
                    travels[x] = []

                travels[x].append((c.val, y))

                if c.left:
                    buff2.append((c.left, x-1, y-1))

                if c.right:
                    buff2.append((c.right, x+1, y-1))

            buff = buff2

        ans = []
        for k in sorted(travels.keys()):
            ans.append([x[0] for x in sorted(
                travels[k], key=lambda x: (-x[1], x[0]))])

        return ans

    """
    Overview
    This is yet another problem about Binary Tree traversals. As one would probably know, the common strategies to traverse a Tree data structure are Breadth-First Search (a.k.a. BFS) and Depth-First Search (a.k.a. DFS).

    The DFS strategy can be further distinguished as preorder DFS, inorder DFS and postorder DFS, depending on the relative order of visit among the node itself and its child nodes.

    If one is not familiar with the concepts of BFS and DFS, we have an Explore card called Queue & Stack where we cover the BFS traversal as well as the DFS traversal. Hence, in this article, we won't repeat ourselves on these concepts.

    In this problem, we are asked to return the vertical order of a binary tree, which implies three sub-orders (denoted as <column, row, value>) as follows:

    column-wise order

    First, we look at a binary tree horizontally. Each node would be aligned to a specific column, based on its relative offset to the root node of the tree.

    Let us assume that the root node has a column index of 0, then its left child node would have a column index of -1, and its right child node would have a column index of +1, and so on.

    row-wise order

    Secondly, we look at the binary tree vertically. Each node would be assigned to a specific row, based on its level (i.e. the vertical distance to the root node).

    Let us assume that the root node has a row index of 0, then both its child nodes would have the row index of 1. Note that the convention we adopt here is slightly different from the one in the problem description where the row index of a parent node is larger than the one of its child nodes. This, though, would not jeopardize our solution. On the contrary, it would help us to simplify the solution, as one will see later.

    value-wise order

    Finally, given the definitions of the above two sub-orders, there could be a case where two different nodes have the same <column, row> index. As a result, to resolve the draw situation, as stated in the problem description, the node that has a smaller value should come first.

    Given the above definitions, we can now formulate the problem as a task to sort the nodes based on the 3-dimensional coordinates (i.e. <column, row, value>) that we defined above.

    The priority of each coordinate is determined by its order. For example, the coordinate column comes first, therefore it has the highest priority. A node with the lowest column index would come up first, regardless the other two coordinates.

    Before proceeding to the solutions, we would like to mention that there is another almost identical problem called 314. Binary Tree Vertical Order Traversal in the LeetCode.

    The only difference between these two problems lies in the third sub-order. When two nodes have the same <column, row> index, in this problem we would further order them based on their values, while in the problem of 314 we would order them based on the horizontal order from left to right. To illustrate the difference, we show an example in the following graph on how two nodes of the same <column, row> index should be ordered respectively in these two problems.

    problem 987 vs. problem 314

    A subtle difference as it seems to be, yet it has a significant impact on the solutions. As a spoiler alert, one could solve the problem of 314 without resorting to the sorting operation, while for this problem the sorting is inevitable due to the third sub-order required in the problem.

    """


    """
    Approach 1: BFS/DFS with Global Sorting
    Intuition

    In the overview section, we've reduced the problem into a sorting problem, based on the order of 3-dimensional coordinates <column, row, value> as we defined.

    As a result, the idea to solve the problem would be as intuitive as building a list where each element in the list corresponds to the 3-dimensional coordinates of each node in the tree, and then sorting the list based on the coordinates.

    To build such a list, we would need to traverse all the nodes in the tree, which we could do with either Breadth-First Search (BFS) or Depth-First Search (DFS). Most of the time, facing the problems of binary tree traversal, we need to make a choice between them. However, in this case, both of the approaches would work. Because both of them would lead to a list that contains the coordinates of all nodes. Though the order of elements in the list would differ depending on the approach, it does not matter, since we would sort the list anyway.

    Algorithm

    Based on the above intuition, we could implement the solution in 3 simple steps:

    Step 1): we traverse the input tree either by BFS or DFS, in order to generate a list that contains the 3-dimensional coordinates (i.e. <column, row, value>) of each node.

    Note that, we assign a higher row index value to a node's child node. This convention is at odds with the denotation given in the problem description. This is done intentionally, in order to keep the ordering of all coordinates consistent, i.e. a lower value in any specific coordinate represents a higher order. As a result, a sorting operation in ascending order would work for each coordinate consistently.
    Step 2): Once we generate the desired list, we then sort the list.

    Step 3): From the sorted list, we then extract the results, and group them by the column index.

    In the following, we give some sample implementations with both the BFS traversal and the DFS traversal.

    BFS Traversal

    Let NN be the number of nodes in the input tree.

    Time Complexity: O(NlogN), which applies to both the BFS and DFS approaches.
    """
    def doit_bfs(self, root: 'TreeNode') -> list:

        node_list = []

        def BFS(root):
            queue = deque([(root, 0, 0)])
            while queue:
                node, row, column = queue.popleft()
                if node is not None:
                    node_list.append((column, row, node.val))
                    queue.append((node.left, row + 1, column - 1))
                    queue.append((node.right, row + 1, column + 1))

        # step 1). construct the global node list, with the coordinates
        BFS(root)

        # step 2). sort the global node list, according to the coordinates
        node_list.sort()

        # step 3). retrieve the sorted results partitioned by the column index
        ret = OrderedDict()
        for column, row, value in node_list:
            if column in ret:
                ret[column].append(value)
            else:
                ret[column] = [value]

        return ret.values()

    def doit_dfs(self, root: 'TreeNode') -> list:
        node_list = []

        def DFS(node, row, column):
            if node is not None:
                node_list.append((column, row, node.val))
                # preorder DFS
                DFS(node.left, row + 1, column - 1)
                DFS(node.right, row + 1, column + 1)

        # step 1). construct the node list, with the coordinates
        DFS(root, 0, 0)

        # step 2). sort the node list globally, according to the coordinates
        node_list.sort()

        # step 3). retrieve the sorted results grouped by the column index
        ret = []
        curr_column_index = node_list[0][0]
        curr_column = []
        for column, row, value in node_list:
            if column == curr_column_index:
                curr_column.append(value)
            else:
                # end of a column, and start the next column
                ret.append(curr_column)
                curr_column_index = column
                curr_column = [value]
        # add the last column
        ret.append(curr_column)

        return ret

    """
    Approach 2: BFS/DFS with Partition Sorting
    Intuition

    As we can see in the above approaches, the overall time complexity is dominated by the sorting operation on the list of coordinates. In order to further optimize the solution, we can try to do something with the sorting.

    It would be hard, if not impossible, to eliminate the sorting operation, since we still need a means to resolve the draw situation when two nodes share the same <column, row> index.

    One might argue that we could use the heap data structure (also known as PriorityQueue in Java) to maintain the list of coordinates. The elements in the heap data structure are ordered automatically, and this does eliminate the sorting operation. However, to maintain the elements in order, each insertion operation in heap would take \mathcal{O}(\log N)O(logN) time complexity. In other words, one can consider the heap data structure as another form of sorting, which amortizes the cost of sorting operating over each insertion.

    One could apply the head data structure to replace the sorting operation here, which could make the code more concise. But this is not the main point here.

    That being said, one thing that we can do is to reduce the scope of sorting, by partitioning the list of coordinates into subgroups based on the column index.

    nodes partition

    Although we would still need to sort the subgroups respectively, it would be faster to sort a series of subgroups than sorting them all together in a single group. Here is a not-so-rigid proof.

    Suppose that we have a list of NN elements, it would then take \mathcal{O}(N \log N)O(NlogN) time to sort this list.

    Next, we divide the list into kk sublists equally. Each list would contain \frac{N}{k} 
    k
    N
    ​	
    elements. Similarly, it would take \mathcal{O}(\frac{N}{k} \log \frac{N}{k})O( 
    k
    N
    ​	
    log 
    k
    N
    ​	
    ) time to sort each sublist.

    In total, to sort all the kk sublists, it would take \mathcal{O}(k \cdot \frac{N}{k} \log \frac{N}{k}) = \mathcal{O}(N \log \frac{N}{k})O(k⋅ 
    k
    N
    ​	
    log 
    k
    N
    ​	
    )=O(Nlog 
    k
    N
    ​	
    ), which is less than the time complexity of sorting the original list (i.e. \mathcal{O}(N \log N)O(NlogN)).

    More importantly, another rationale to partition the list into column based groups is that this is also the format of results that are asked in the problem.

    Once we sort the column based groups, we can directly return the groups as results, without the need for extraction as we did in the previous approach.

    This is also the reason why we would not recommend to further partition the list based on the combination of <column, row> index. Although theoretically, the more groups that we partition the list into, the faster the sorting operations would be.

    If we partition the list into the groups lead by <column row> index, we would need some additional processing to extract the results. Hence, it would become an overkill.

    Algorithm

    We could implement the above intuition based on the previous approaches. Again, we could break it down into 3 steps:

    Step 1): First of all, we create a hashmap called columnTable with the column index as key and the list of <row, value> tuples as value. This hashmap is used to hold the groups of coordinates.

    We traverse the input tree by either BFS or DFS. During the traversal, we populate the hashmap that we created above.

    Meanwhile, we also note down the minimal and maximal column index during the traversal. The minimal and maximal column index defines the range of column index. With this range, we could iterate through columns in order without the need for sorting, as one will see later.

    Step 2): Once we populate the above hashmap, we then sort the value in each entry of the hashmap, i.e. we sort each group of coordinates led by the column index.

    Step 3): From the sorted hashmap, we extract the results that are grouped by the column index.

    In the following, we give some sample implementations with both the BFS traversal and the DFS traversal.

    BFS Traversal
    """
    def doit_bfs(self, root: 'TreeNode') -> list:
        from collections import defaultdict, deque
        if not root: return []

        columnTable = defaultdict(list)
        maxcol, mincol = float('-inf'), float('inf')

        def BFS():
            nonlocal maxcol, mincol
            qu = deque([(0, 0, root)])

            while qu:
                column, row, node = qu.popleft()
                if not node: continue
                    
                maxcol = max(maxcol, column)
                mincol = min(mincol, column)

                columnTable[column].append((row, node.val))

                qu.append((column-1, row+1, node.left))
                qu.append((column+1, row+1, node.right))

        BFS()

        res = []

        for col in range(mincol, maxcol + 1):
            res.append([val for row, val in sorted(columnTable[col])])

        return res


    def doit_dfs(self, root: TreeNode) -> List[List[int]]:
        if root is None:
            return []

        columnTable = defaultdict(list)
        min_column = max_column = 0

        def DFS(node, row, column):
            if node is not None:
                nonlocal min_column, max_column
                columnTable[column].append((row, node.val))
                min_column = min(min_column, column)
                max_column = max(max_column, column)

                # preorder DFS
                DFS(node.left, row + 1, column - 1)
                DFS(node.right, row + 1, column + 1)

        # step 1). DFS traversal
        DFS(root, 0, 0)

        # step 2). extract the values from the columnTable
        ret = []
        for col in range(min_column, max_column + 1):
            # sort first by 'row', then by 'value', in ascending order
            ret.append([val for row, val in sorted(columnTable[col])])

        return ret
        

if __name__ == '__main__':

    root = TreeNode(3)
    root.left = TreeNode(9)
    root.right = TreeNode(20)
    root.right.left = TreeNode(15)
    root.right.right = TreeNode(7)

    # [3,9,20,null,null,15,7]
    res = VerticalTraversal().doit(root)

    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)

    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)

    root.right.left = TreeNode(6)
    root.right.right = TreeNode(7)

    res = VerticalTraversal().doit(root)

    # [0,2,1,3,null,null,null,4,5,null,7,6,null,10,8,11,9]
    # [[4,10,11],[3,6,7],[2,5,8,9],[0],[1]]

    root = TreeNode(0)
    root.left = TreeNode(5)
    root.right = TreeNode(1)

    root.left.left = TreeNode(9)

    root.right.left = 2

    pass
