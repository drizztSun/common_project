"""
1306. Jump Game III

Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach to any index with value 0.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation: 
All possible ways to reach at index 3 with value 0 are: 
index 5 -> index 4 -> index 1 -> index 3 
index 5 -> index 6 -> index 4 -> index 1 -> index 3 
Example 2:

Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true 
Explanation: 
One possible way to reach at index 3 with value 0 is: 
index 0 -> index 4 -> index 1 -> index 3
Example 3:

Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.
 

Constraints:

1 <= arr.length <= 5 * 10^4
0 <= arr[i] < arr.length
0 <= start < arr.length


Overview
You probably can guess from the problem title, this is the third problem in the series of Jump Game problems. Those problems are similar, but have considerable differences, making their solutions quite different.

Here, two approaches are introduced: Breadth-First Search approach and Depth-First Search approach.

Approach 1: Breadth-First Search

Most solutions start from a brute force approach and are optimized by removing unnecessary calculations. Same as this one.

A naive brute force approach is to iterate all the possible routes and check if there is one reaches zero. However, if we already checked one index, we do not need to check it again. We can mark the index as visited by make it negative.

Complexity Analysis

Assume NN is the length of arr.

Time complexity: \mathcal{O}(N)O(N) since we will visit every index at most once.

Space complexity : \mathcal{O}(N)O(N) since it needs q to store next index. In fact, q would keep at most two levels of nodes. Since we got two children for each node, the traversal of this solution is a binary tree. The maximum number of nodes within a single level for a binary tree would be \frac{N}{2} 
2
N
​	
 , so the maximum length of q is \mathcal{O}(\frac{N}{2} + \frac{N}{2})=\mathcal{O}(N)O( 
2
N
​	
 + 
2
N
​	
 )=O(N).


Approach 2: Depth-First Search

    DFS is similar to BFS but differs in the order of searching. You should consider DFS when you think of BFS.

    Still, we make the value negative to mark as visited.

    Complexity Analysis

    Assume NN is the length of arr.

    Time complexity: \mathcal{O}(N)O(N), since we will visit every index only once.

    Space complexity: \mathcal{O}(N)O(N) since it needs at most \mathcal{O}(N)O(N) stacks for recursions.

"""


class CanReach:

    # BFS
    def doit_dfs(self, arr: list[int], start: int):
        """
        :type arr: List[int]
        :type start: int
        :rtype: bool
        """
        n = len(arr)
        q = [start]

        while q:

            node = q.pop(0)
            if arr[node] == 0:
                return True

            if arr[node] < 0:
                continue

            for i in (node + arr[node], node - arr[node]):
                if 0 <= i < len(arr):
                    q.append(i)

            arr[node] = -arr[node]

        return False

    # DFS

    def doit_dfs(self, arr: list[int], start: int):
        """
        :type arr: List[int]
        :type start: int
        :rtype: bool
        """
        def search(seen, i):

            if i < 0 or i >= len(arr):
                return False

            if seen[i]:
                return False

            if arr[i] == 0:
                return True

            N = len(arr)

            seen[i] = True

            if search(seen, i + arr[i]) or search(seen, i-arr[i]):
                return True

            seen[i] = False

            return False

        seen = [False for _ in range(len(arr))]

        return search(seen, start)

    def doit_dfs_1(self, arr, start):
        """
        :type arr: List[int]
        :type start: int
        :rtype: bool
        """
        def dfs(arr, start):
            if 0 <= start < len(arr) and arr[start] >= 0:
                return False

            if arr[start] == 0:
                return True

            arr[start] = -arr[start]
            return dfs(arr, start+arr[start]) or dfs(arr, start-arr[start])

        return dfs(arr, start)
