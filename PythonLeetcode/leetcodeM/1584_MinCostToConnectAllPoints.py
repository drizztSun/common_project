"""
1584. Min Cost to Connect All Points


You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

 

Example 1:



Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation:

We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.
Example 2:

Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18
Example 3:

Input: points = [[0,0],[1,1],[1,0],[-1,1]]
Output: 4
Example 4:

Input: points = [[-1000000,-1000000],[1000000,1000000]]
Output: 4000000
Example 5:

Input: points = [[0,0]]
Output: 0
 

Constraints:

1 <= points.length <= 1000
-106 <= xi, yi <= 10^6
All pairs (xi, yi) are distinct.


"""


class MinCostConnectPoints:

    """
        O(n^2) Min Spinning Tree
    """
    def doit_prims(self, points: list) -> int:

        from heapq import heappush, heappop, heapify
        N = len(points)
        visited = [False for _ in range(N)]
        heap = []
        heapify(heap)
        i, res = 0, 0
        
        def mahaten_distance(a, b):
            return abs(points[a][0] - points[b][0]) + abs(points[a][1] - points[b][1])
        
        for _ in range(N):
            
            visited[i] = True
            
            for j in range(N):
                if not visited[j]:
                    heappush(heap, (mahaten_distance(i, j), j))
                             
            while heap and visited[heap[0][1]]:
                heappop(heap)
            
            
            c , i = heappop(heap)
            res += c
                             
        return res

    """
        There are many articles online describing this O(nlogn) approach, the basic idea is that for each point we don't need to consider all other points as our candidates to send edges to.

        In fact, for each point, we can use it as the origin to establish a cartesian coordinate system, and then divide each quadrant into two 45 degree regions (using either line y=x or y=-x). It can be proven that in each region we only need to consider the point closest to the origin (current point of interest) to send our edge to, thus reduce the number of edge candidates from O(n^2) to O(n). We can then use Kruskal algorithm to build the MST in O(nlogn) time.

        Let's consider the region enclosed by x>x0 and x-y<x0-y0, where (x0,y0) is our current point of interest. Finding the closest point is equivalent to finding the point with the smallest x+y value, this can be done using a Binary Indexed Tree built for minimum range query. For all 8 regions, we transform them to this region and only need to do this 4 times due to symmetry.

        More details/code of this algorithm can be found: here, here, here and here
    """

    def minCostConnectPoints(self, points: list) -> int:
        n=len(points)
        edges=[]
        
        # transform the x,y coordinates so 4 of the 8 regions are considered
        for dirc in range(4): 
            if dirc==1 or dirc==3:
                for i in range(n): points[i].reverse()    # swap x,y coordinates
            elif dirc==2:
                for i in range(n): points[i][0]*=-1    #  flip x coordinates
                    
            # sort by x values (descending x0<x1), if same x values, sort by y values (y0-x0<y1-x1)
            p1=sorted(enumerate(points),key=itemgetter(1),reverse=True)
            
            # sort by x-y values (x0-y0<x1-y1), if same x-y values, sort by x values (descending)
            p2=sorted([(i,(x-y,-x)) for i,(x,y) in enumerate(points)],key=itemgetter(1))
            
            # compress the x-y values
            d=[0]*n            
            for v,(i,_) in enumerate(p2,1): d[i]=v
                
            # initialize a binary indexed tree for minimum range query
            # array index: compressed x-y, array value: x+y and the index in the `points` array
            # we loop over points from larger x to smaller x (x0<x1)
            # query the point that has the minimum x+y value from all points that have smaller x-y values
            # add the edge to our candidates
            ft=BIT(n+1)
            for i,(x,y) in p1:
                j=ft.minq(d[i])
                if j!=-1:
                    xj,yj=points[j]
                    edges.append((i,j,abs(x-xj)+abs(y-yj)))
                ft.update(d[i],x+y,i)
        
        # Kruskal
        edges.sort(key=itemgetter(2))
        dsu=UF(n)
        ans=0
        for i,j,w in edges:
            if dsu.union(i,j):
                ans+=w
        return ans
            
class BIT:
    def __init__(self,n):
        self.n=n
        self.tree=[(10**12,-1) for _ in range(n)]
    
    def minq(self,k):
        v,i=10**12,-1
        while k>=1:
            if self.tree[k][0]<v:
                v,i=self.tree[k]
            k-=k&-k
        return i
    
    def update(self,k,x,i):
        while k<self.n:
            if self.tree[k][0]>x:
                self.tree[k]=(x,i)
            k+=k&-k

class UF:
    def __init__(self,n):
        self.p=list(range(n))
        self.s=[1]*n
    
    def find(self,x):
        if self.p[x]!=x:
            self.p[x]=self.find(self.p[x])
        return self.p[x]

    def union(self,x,y):
        xr,yr=self.find(x),self.find(y)
        if xr==yr:
            return False
        if self.s[xr]<self.s[yr]:
            xr,yr=yr,xr
        self.p[yr]=xr
        self.s[xr]+=self.s[yr]
        return True

if __name__ == '__main__':

    MinCostConnectPoints().doit_prims([[0,0],[2,2],[3,10],[5,2],[7,0]])