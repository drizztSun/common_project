"""
433. Minimum Genetic Mutation

A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to "end"), where ONE mutation is defined as ONE single character changed in the gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations. A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the minimum number of mutations needed to mutate from "start" to "end". If there is no such a mutation, return -1.

Note:

Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be valid.
You may assume start and end string is not the same.


Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1


Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2


Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3

"""


class MinGeneticMutation:

    def doit_bfs(self, start: str, end: str, bank: list) -> int:
        from collections import deque
        
        n1 = len(start)
        n2 = len(end)
        
        if n1 != n2:
            return -1
        
        # Since it is always one step 
        # BFS
        queue = deque([(start,0)])
        bank = set(bank)
        
        while queue:
            
            cur, step = queue.popleft()
            if cur == end:
                return step
            
            for i in range(len(cur)):
                for c in "ACGT":
                    nei = cur[:i] + c + cur[i+1:]
                    
                    # here need to keep track of how many times (serve as the seen/visited role)
                    if nei in bank:
                        bank.remove(nei)
                        queue.append((nei, step+1))
            
        return -1

    def doit_bfs(self, start, end, bank):
        '''Method 1. BFS. All bank forms the edges of a graph, with nodes being all gene strings in the bank. Minimum unweighted distance cal is then converted to BFS'''
        import collections
        def is_mut(x, y):
            dif = 0
            for i in range(len(x)):
                if x[i] != y[i]:
                    dif += 1
                    if dif > 1:
                        return False
            return True

        def BFS(v):
            touched = set()
            Q = [v]
            touched.add(v)
            dist = 0
            while Q:
                s = len(Q)
                for _ in range(s):
                    e = Q.pop(0)
                    if e == end:
                        return dist
                    for nb in graph[e]:
                        if nb not in touched:
                            touched.add(nb)
                            Q.append(nb)
                dist += 1
            return -1

        graph = collections.defaultdict(list)
        for i in range(len(bank)):
            for j in range(i + 1, len(bank)):
                if is_mut(bank[i], bank[j]):
                    graph[bank[i]].append(bank[j])
                    graph[bank[j]].append(bank[i])
            if is_mut(start, bank[i]):
                graph[start].append(bank[i])
            # if is_mut(bank[i], end):
            #     graph[bank[i]].append(end)

        return BFS(start)

    def doit_bfs(self, start: str, end: str, bank: List[str]) -> int:
        import collections
        def compare(a,b):
            return 1 == sum([a[i]!=b[i] for i in range(8)])

        q = collections.deque([[start]])
        v, b = set([start]), set(bank)
        while q:
            x = q.pop()
            b -= v
            for i in b:
                if compare(i, x[-1]):
                    if i == end:
                        return len(x)
                    q.appendleft(x + [i])
                    v.add(i)
                    #b.remove(i) ####ERROR set can NOT change size during iteration
        return -1

    def doit_dfs(self, start, end, bank):

        from collections import defaultdict
        from heapq import heappop, heappush

        def can_mutate(a, b):
            res = 0
            for i in range(len(a)):
                if a[i] != b[i]:
                    res += 1
                    if res > 1:
                        break
            return res == 1

        try:
            s, e = len(bank), bank.index(end)
        except ValueError:
            return -1

        n = len(bank)
        bank.append(start)
        graph = defaultdict(set)
        for i in range(len(bank)):
            for j in range(i + 1, len(bank)):
                if can_mutate(bank[i], bank[j]):
                    graph[i].add(j)
                    graph[j].add(i)

        hp = [(0, n)]
        visited = set()

        while hp:

            step, node = heappop(hp)

            if node == e:
                return step

            if node in visited:
                continue

            visited.add(node)

            for c in graph[node]:
                if c not in visited:
                    heappush(hp, (step + 1, c))

        return -1


if __name__ == '__main__':

    MinGeneticMutation().doit_dfs("AACCGGTT", "AAACGGTA", ["AACCGGTA", "AACCGCTA", "AAACGGTA"])

    MinGeneticMutation().doit_dfs("AAAAACCC", "AACCCCCC", ["AAAACCCC", "AAACCCCC", "AACCCCCC"])