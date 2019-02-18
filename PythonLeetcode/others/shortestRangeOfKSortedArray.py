
import heapq

class ShortestArangeInSortedArray:

    # O(n * log(k))
    def doit(self, lists: 'List[List[int]]') -> 'List[int]':

        buff = [(c[0], 0, i) for i, c in enumerate(lists)]
        
        heapq.heapify(buff)

        minv, maxv = float('inf'), float('-inf')

        while buff:

            v, i, j = heapq.heappop(buff)

            if minv == float('inf') and i + 1 == len(lists[j]):
                minv = v
            elif minv != float('inf'):
                maxv = v
            else:
                heapq.heappush(buff, (lists[j][i+1], i + 1, j ))
           
        return [minv, maxv]


if __name__ == "__main__":

    a = [ [4, 10, 15, 24], [0, 9, 12, 20], [5, 18, 22, 30]]

    res = ShortestArangeInSortedArray().doit(a)

    res = 0
