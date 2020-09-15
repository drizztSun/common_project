

import heapq 


if __name__ == '__main__':


    a = [10, 2, 4, 1, 3, 5, 9, 7, 8, 6]
    
    heapq.heapify(a)
    print(a)

    print(heapq.heappush(a, 10))


    print(heapq.heappop(a))


    print(heapq.heappushpop(a, 12)) 

    print(heapq.nlargest(3, [1, 2, 3, 4]))

    print(heapq.nsmallest(3, [1, 1, 2, 3, 4, 10]))

    
    print(heapq.heapreplace([1, 2, 3], 4))

    print(heapq.merge([1, 2, 3], [4, 5, 6], [9, 7, 8]))