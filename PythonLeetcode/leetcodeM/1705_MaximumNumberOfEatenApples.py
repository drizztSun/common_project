"""
1705. Maximum Number of Eaten Apples


There is a special kind of apple tree that grows apples every day for n days. On the ith day, the tree grows apples[i] apples that will rot after days[i] days, 
that is on day i + days[i] the apples will be rotten and cannot be eaten. On some days, the apple tree does not grow any apples, which are denoted by apples[i] == 0 and days[i] == 0.

You decided to eat at most one apple a day (to keep the doctors away). Note that you can keep eating after the first n days.

Given two integer arrays days and apples of length n, return the maximum number of apples you can eat.

 

Example 1:

Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
Output: 7
Explanation: You can eat 7 apples:
- On the first day, you eat an apple that grew on the first day.
- On the second day, you eat an apple that grew on the second day.
- On the third day, you eat an apple that grew on the second day. After this day, the apples that grew on the third day rot.
- On the fourth to the seventh days, you eat apples that grew on the fourth day.
Example 2:

Input: apples = [3,0,0,0,0,2], days = [3,0,0,0,0,2]
Output: 5
Explanation: You can eat 5 apples:
- On the first to the third day you eat apples that grew on the first day.
- Do nothing on the fouth and fifth days.
- On the sixth and seventh days you eat apples that grew on the sixth day.
 

Constraints:

apples.length == n
days.length == n
1 <= n <= 2 * 104
0 <= apples[i], days[i] <= 2 * 104
days[i] = 0 if and only if apples[i] = 0.

"""


class EatenApples:


    def doit_sweepline(self, apples: list, days: list) -> int:

        n, m = len(days), 0
        for i, x in enumerate(days):
            m = max(i+x, m)
        
        A = [0] * (m+1)
        
        for i, (x,y) in enumerate(zip(apples, days)):
            A[i] += x
            A[i+y] -= x
        
        cnt = agg = k = 0
        
        for x in A:
            if x < 0:
                cnt += min(agg, k)
                k = 0
            if agg := agg+x:
                k += 1
        return cnt


    def doit_(self, apples: list, days: list) -> int:
        """
        use min heap to keep track the apples that will rot next
        """
        from heapq import heapify, heappush, heappop
        minheap = []
        heapify(minheap)
        day = 0
        res = 0
        for i in range(len(apples)):
            day = i
            # first thing to do is to throw away all apples in minheap that is already rotten
            # simply check if the expiration info top of the heap is smaller than i
            while minheap and minheap[0][0] < day:
                heappop(minheap)
                
            nbrApple   = apples[i]
            expiration = i + days[i]-1            
            
            # add apples got in current day to the minheap
            if nbrApple > 0:
                heappush(minheap, (expiration, nbrApple))
            
            if minheap:
                # now we can get the apple that is going to be rotten next
                date, apple = heappop(minheap)
                res += 1
                if apple > 1: 
                    # we still have some left, can put them back to the minheap
                    heappush(minheap, (date, apple-1))
        
        # have some leftovers 
        while minheap:
            day += 1
            while minheap and minheap[0][0] < day:
                heappop(minheap)
            if minheap == []:
                break
            date, apple = heappop(minheap)
            res += 1
            if apple > 1: 
                # we still have some left, can put them back to the minheap
                heappush(minheap, (date, apple-1))
            
        return res

    def doit_heap(self, apples: list, days: list) -> int:
        
        from heapq import heapify, heappush, heappop

        heap = []
        heapify(heap)
        day, eaten = 0, 0

        while day < len(apples) or heap:

            while heap and heap[0][0] < day:
                heappop(heap)

            if day < len(apples) and apples[day] > 0:
                heappush(heap, (day + days[day] - 1, apples[day]))

            if heap:
                expired_days, amount = heappop(heap)
                eaten += 1
                if amount > 1:
                    heappush(heap, (expired_days, amount-1))

            day += 1

        return eaten
            

if __name__ == '__main__':

    EatenApples().doit_heap([3,0,0,0,0,2], [3,0,0,0,0,2])

    # EatenApples().doit_heap([3,1,1,0,0,2], [3,1,1,0,0,2])

    EatenApples().doit_heap([2,1,10], [2,10,1])