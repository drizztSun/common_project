# 973. K Closest Points to Origin

# We have a list of points on the plane.  Find the K closest points to the origin (0, 0).
# (Here, the distance between two points on a plane is the Euclidean distance.)
# You may return the answer in any order.  The answer is guaranteed to be unique (except for the order that it is in.)

# Example 1:

# Input: points = [[1,3],[-2,2]], K = 1
# Output: [[-2,2]]
# Explanation: 
# The distance between (1, 3) and the origin is sqrt(10).
# The distance between (-2, 2) and the origin is sqrt(8).
# Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
# We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].

# Example 2:

# Input: points = [[3,3],[5,-1],[-2,4]], K = 2
# Output: [[3,3],[-2,4]]
# (The answer [[-2,4],[3,3]] would also be accepted.)
 
# Note:

# 1 <= K <= points.length <= 10000
# -10000 < points[i][0] < 10000
# -10000 < points[i][1] < 10000


class kClosest:

    def doit(self, points: 'List[List[int]]', K: 'int') -> 'List[List[int]]':

        dis = []    
        for c in points:
            dis.append((c[0]**2 + c[1]**2, c))

        def partition(low, high):

            c, i, j = dis[high], low-1, low
            
            while j < high - 1:
                
                if dis[j] < c:
                    i += 1
                    dis[i], dis[j] = dis[j], dis[i]

                j += 1

            dis[i+1], dis[high] = dis[high], dis[i+1]

            return i + 1


        low, high = 0, len(dis)-1
        while True:
            a = partition(low, high)
            if a == K:
                return dis[:K]

            if a > K:
                low, high = 0, a-1
            else:
                low, high = a+1, len(dis-1)                


    def doit(self, points: 'List[List[int]]', K: 'int') -> 'List[List[int]]':
        
        distance = {}
        for c in points:
            dis = c[0] ** 2 + c[1] ** 2
            if dis not in distance:
                distance[dis] = []
            distance[dis].append(c)
            
        ans = []    
        for c in sorted(distance.keys()):
            if K > len(distance[c]): 
                ans.extend(distance[c])
            else:
                ans.extend(distance[c][:K])
                
            K -= len(distance[c])
            if K <= 0:
                break
                
        return ans


    def doit1(self, points: 'List[List[int]]', K: 'int') -> 'List[List[int]]':
        import heapq
        distance = []
        for c in points:
            heapq.heappush(distance, (c[0] ** 2 + c[1] ** 2, c[0], c[1]))
        
        ans = []
        while K > 0:
            c = heapq.heappop(distance)    
            ans.append([c[1], c[2]])
            K -= 1

        return ans


    def doit2(self, points: 'List[List[int]]', K: 'int') -> 'List[List[int]]':

        points.sort(key=lambda x: x[0] ** 2 + x[1] ** 2)
        return points[:K]

    

if __name__ == "__main__":

    res = kClosest().doit([[1,3],[-2,2]], 1)
            