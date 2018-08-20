# 547. Friend Circles


# There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. 
# For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. 
# And we defined a friend circle is a group of students who are direct or indirect friends.

# Given a N*N matrix M representing the friend relationship between students in the class. 
# If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. 
# And you have to output the total number of friend circles among all the students.


# Example 1:

# Input: 
# [[1,1,0],
#  [1,1,0],
#  [0,0,1]]
# Output: 2
# Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
# The 2nd student himself is in a friend circle. So return 2.

# Example 2:
# Input: 
# [[1,1,0],
#  [1,1,1],
#  [0,1,1]]
# Output: 1
# Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
# so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.
# Note:
# N is in range [1,200].
# M[i][i] = 1 for all students.
# If M[i][j] = 1, then M[j][i] = 1.


class FriendCircles:

    def findCircleNum(self, M):
        """
        :type M: List[List[int]]
        :rtype: int
        """
        def find(node):
            if circles[node] == node: 
                return node
            
            root = find(circles[node])
            circles[node] = root
            return root
        
        n = len(M)
        circles = {x:x for x in range(n)}
        for i in range(n):
            for j in range(i, n):
                if i != j and M[i][j] == 1 and find(i) != find(j):
                    circles[find(i)] = find(j)   
                    
        return sum([1 for k, v in circles.items() if k == v])

    def doit(self, M):
        """
        :type M: List[List[int]]
        :rtype: int
        """
        def parent(i):
            if circle[i] != i:
                circle[i] = parent(circle[i])
            return circle[i]

        circle = [x for x in range(len(M))]

        for i in range(len(M)):

            for j in range(i+1, len(M)):

                if M[i][j] == 1 and parent(i) != parent(j):
                    circle[parent(j)] = parent(i)

        return sum(1 for i in range(len(circle)) if i == circle[i])


    def doit1(self, M):
        """
        :type M: List[List[int]]
        :rtype: int
        """
        def dfs(i, visited):
            visited.add(i)
            for j in range(len(M)):
                if M[i][j] == 1 and j not in visited:
                    dfs(j, visited)
                    
        
        count, visited = 0, set()
        for i in range(len(M)):
            if i not in visited:
                dfs(i, visited)
                count += 1
        
        return count



class UnionFind(object):
    def __init__(self, grid):
        self.n = len(grid)
        self.parent = [-1] * self.n
        for idx in xrange(self.n):
            self.parent[idx] = idx

    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, x, y):
        rootx = self.find(x)
        rooty = self.find(y)
        if rootx != rooty:
            self.parent[rooty] = rootx

    def diff_groups(self):
        diff_groups = set()
        for i in xrange(self.n):
            diff_groups.add(self.find(i))
        return len(diff_groups)

class Solution(object):
    def findCircleNum(self, M):
        """
        :type M: List[List[int]]
        :rtype: int
        """
        n = len(M)
        uf = UnionFind(M)

        for i in xrange(n):
            for j in xrange(n):
                if M[i][j] == 1:
                    uf.union(i, j)

        return uf.diff_groups()


if __name__ == "__main__":

    res = FriendCircles().doit([[1, 1, 0],
                                [1, 1, 0],
                                [0, 0, 1]])


    res = FriendCircles().doit([[1, 1, 0],
                                [1, 1, 1],
                                [0, 1, 1]])


    res = FriendCircles().doit([[1, 0, 0, 1],
                                [0, 1, 1, 0],
                                [0, 1, 1, 1],
                                [1, 0, 1, 1]])

    res = FriendCircles().findCircleNum([[1, 0, 0, 1],
                                         [0, 1, 1, 0],
                                         [0, 1, 1, 1],
                                         [1, 0, 1, 1]])

    pass
