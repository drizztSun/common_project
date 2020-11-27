"""
1057. Campus Bikes

On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. Each worker and bike is a 2D coordinate on this grid.

Our goal is to assign a bike to each worker. Among the available bikes and workers, we choose the (worker, bike) pair
with the shortest Manhattan distance between each other, and assign the bike to that worker.
(If there are multiple (worker, bike) pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index;
if there are multiple ways to do that, we choose the pair with the smallest bike index). We repeat this process until there are no available workers.

The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.

Return a vector ans of length N, where ans[i] is the index (0-indexed) of the bike that the i-th worker is assigned to.



Example 1:



Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
Output: [1,0]
Explanation:
Worker 1 grabs Bike 0 as they are closest (without ties), and Worker 0 is assigned Bike 1. So the output is [1, 0].

Example 2:



Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
Output: [0,2,1]
Explanation:
Worker 0 grabs Bike 0 at first. Worker 1 and Worker 2 share the same distance to Bike 2, thus Worker 1 is assigned to Bike 2,
and Worker 2 will take Bike 1. So the output is [0,2,1].


Note:

0 <= workers[i][j], bikes[i][j] < 1000
All worker and bike locations are distinct.
1 <= workers.length <= bikes.length <= 1000


"""


class CampusBikes:

    def doit_(self, workers: list, bikes: list) -> list:

        from collections import defaultdict
        distance = defaultdict(list)

        def caldistance(a, b):
            return abs(a[0] - b[0]) + abs(a[1] - b[1])

        for i in range(len(workers)):
            for j in range(len(bikes)):
                distance[caldistance(workers[i], bikes[j])].append((i, j))


        bikes_visited = [False] * len(bikes)
        workers_visited = [False] * len(workers)
        res = [-1] * len(workers)

        for c in sorted(distance.keys()):

            for w, b in distance[c]:

                if workers_visited[w] or bikes_visited[b]:
                    continue

                if res[w] == -1:
                    res[w] = b
                    workers_visited[w] = True
                    bikes_visited[b] = True

        return res

    def doit_heap(self, workers, bikes):
        import heapq
        N = len(workers)
        distances = []
        ans = [0] * N
        used_bikes = set()

        for i, [x, y] in enumerate(workers):
            distances.append([])
            for j, (xb, yb) in enumerate(bikes):
                dist = abs(xb - x) + abs(yb - y)
                distances[-1].append((dist, i, j))
            distances[-1].sort(reverse=True)

        heap = [distances[i].pop() for i in range(N)]
        heapq.heapify(heap)

        while len(used_bikes) < N:

            dist, worker, bike = heapq.heappop(heap)

            if bike not in used_bikes:
                used_bikes.add(bike)
                ans[worker] = bike
            else:
                heapq.heappush(heap, distances[worker].pop())

        return ans

    def doit_buckert_sort(self, workers: List[List[int]], bikes: List[List[int]]) -> List[int]:
        # O(nm) time and space
        buckets = [[] for i in range(2001)]
        for worker_idx, worker in enumerate(workers):
            for bike_idx, bike in enumerate(bikes):
                dist = abs(worker[0] - bike[0]) + abs(worker[1] - bike[1])
                buckets[dist].append((worker_idx, bike_idx))

        solution_pairs = [-1] * len(workers)
        used_bikes = set()
        for bucket in buckets:
            for worker, bike in bucket:
                if solution_pairs[worker] == -1 and bike not in used_bikes:
                    solution_pairs[worker] = bike
                    used_bikes.add(bike)
        return solution_pairs

if __name__ == '__main__':

    CampusBikes().doit_dp_bitmask_backtracking([[0,0],[2,1]], [[1,2],[3,3]])









