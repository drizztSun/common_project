



"""
743. Network Delay Time

There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.



Example 1:

Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
Output: 2


Note:

N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.
"""

from collections import defaultdict
import heapq


class NetworkDelayTime:

    def doit(self, times, N, K):
        graph = defaultdict(list)
        for u, v, w in times:
            graph[u].append((v, w))

        pq = [(0, K)]
        dist = {}
        while pq:
            d, node = heapq.heappop(pq)
            if node in dist:
                continue
            dist[node] = d
            for nei, d2 in graph[node]:
                if nei not in dist:
                    heapq.heappush(pq, (d+d2, nei))

        return max(dist.values()) if len(dist) == N else -1

    def doit2(self, times, N, K):
        dict = {}
        for u, v, w in times:
            if u - 1 not in dict:
                dict[u - 1] = [(v - 1, w)]
            else:
                dict[u - 1].append((v - 1, w))

        uv = [float('inf') for _ in range(N)]
        uv[K - 1] = 0
        done = [False] * N

        for _ in range(N):
            u, minv = -1, float('inf')
            for i in range(N):
                if not done[i] and minv > uv[i]:
                    u = i
                    minv = uv[i]

            if u in dict:
                for n, t in dict[u]:
                    if t + uv[u] < uv[n]:
                        uv[n] = t + uv[u]

            done[u] = True

        return max(uv) if float('inf') not in uv else -1

    def doit3(self, times, N, K):

        direct = defaultdict(dict)
        for u, v, w in times:
            direct[u][v] = w

        sd = {i: float('inf') for i in range(1, N + 1)}
        distance = {}
        sd[K] = 0
        cur, latency = K, -1

        while cur != -1:

            distance[cur] = sd[cur]
            del sd[cur]
            if distance[cur] > latency:
                latency = distance[cur]

            for v, w in direct[cur].items():

                if v not in sd:
                    continue

                if sd[v] > distance[cur] + w:
                    sd[v] = distance[cur] + w

            cur = -1
            for k, v in sd.items():
                if v != float('inf') and (cur == -1 or v < sd[cur]):
                    cur = k

        return -1 if sd else latency


if __name__ == '__main__':

    res = NetworkDelayTime().doit([[2,1,1],[2,3,1],[3,4,1]], 4, 2)

    res = NetworkDelayTime().doit([[1,2,1]], 2, 2)
