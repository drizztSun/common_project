"""
1642. Furthest Building You Can Reach

You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.

You start your journey from building 0 and move to the next building by possibly using bricks or ladders.

While moving from building i to building i+1 (0-indexed),

If the current building's height is greater than or equal to the next building's height, you do not need a ladder or bricks.
If the current building's height is less than the next building's height, you can either use one ladder or (h[i+1] - h[i]) bricks.
Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.



Example 1:


Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
Output: 4
Explanation: Starting at building 0, you can follow these steps:
- Go to building 1 without using ladders nor bricks since 4 >= 2.
- Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
- Go to building 3 without using ladders nor bricks since 7 >= 6.
- Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
It is impossible to go beyond building 4 because you do not have any more bricks or ladders.
Example 2:

Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
Output: 7
Example 3:

Input: heights = [14,3,19,3], bricks = 17, ladders = 0
Output: 3


Constraints:

1 <= heights.length <= 105
1 <= heights[i] <= 106
0 <= bricks <= 109
0 <= ladders <= heights.length


"""


class FurthestBuilding:

    """
        Approach 1: Min-Heap
        Intuition

        To get started, here's an example where it's actually possible to get all the way across. You have 8 bricks, 2 ladders, and heights [2, 7, 9, 3, 1, 2, 5, 9, 4, 6]. 
        Determine where to put the bricks and ladders before reading further (remember, you do not need to use bricks or ladders to go down).
    """
    def furthestBuilding(self, heights: list, bricks: int, ladders: int) -> int:
        import heapq
        ladder_allocations = [] # We'll use heapq to treat this as a min-heap.

        for i in range(len(heights) - 1):
            climb = heights[i + 1] - heights[i]
            # If this is actually a "jump down", skip it.
            if climb <= 0:
                continue
        
            # Otherwise, allocate a ladder for this climb.
            heapq.heappush(ladder_allocations, climb)
        
            # If we haven't gone over the number of ladders, nothing else to do.
            if len(ladder_allocations) <= ladders:
                continue
        
            # Otherwise, we will need to take a climb out of ladder_allocations
            bricks -= heapq.heappop(ladder_allocations)
        
            # If this caused bricks to go negative, we can't get to i + 1
            if bricks < 0: return i
        
        # If we got to here, this means we had enough to cover every climb.
        return len(heights) - 1

    """
        It seems we use Ladder first, then bricks. if there is no Ladder, we use brick and when bricks is gonna, than we use 
    """
    def doit_heap(self, heights: list, bricks: int, ladders: int) -> int:
        from heapq import heapify, heappop, heappush

        heap = []
        for i in range(len(heights) - 1):

            diff = heights[i + 1] - heights[i]

            if diff <= 0:
                continue

            heappush(heap, diff)

            if len(heap) > ladders: 
                # if ladder is gone, we start using bricks.
                # Using heap to track minimum diff used by ladder, which will be replaced by the brick. And than the ladder could be used on new brick diff.
                # if there is 2 diff in the beginning, and cost ladder, when we find anohter diff is 200. 
                # When [2, ... 200] all into the heap, 2 is top. brick minus 2 bricks, it means we move ladder on 2 diff brick to 200 diff. 

                # Here bricks will minus the least diff, so we always use bicks on smallest items.
                bricks -= heappop(heap)

            if bricks < 0: # but if it is still out of bricks, we already get the point to leave.
                return i

        return len(heights) - 1

    """
        Max heap


        Approach 2: Max-Heap
        Intuition

        This approach is similar to Approach 1, except instead of initially allocating ladders, we allocate bricks. When we run out of bricks, we replace the longest climb with a ladder. 
        This was in contrast to before when we were replacing the shortest climb with bricks. Because we now need to retrieve maximums instead of minimums, we should use a max-heap instead of a min-heap.

        You should have a go at coding up this approach by yourself before reading any further; it's a good exercise to ensure you understood approach 1.

        Algorithm

        In addition to replacing the min-heap with a max-heap, we also need to keep track of how many bricks we've used so far (as we can't simply check the current size of the heap like we did in Approach 1). The simplest way of doing this is to subtract from the bricks input parameter and check for when it goes to zero. Here is the pseudocode for this approach.

        define function furthestBuilding(heights, bricks, ladders):
            bricks_allocations = a new max heap
            for each i from 0 to heights.length - 2 (including the end point):
                current_height = heights[i]
                next_height = heights[i + 1]
                difference = next_height - current_height
                if difference is 0 or difference is negative:
                    continue (this is a jump)
                rename difference to climb
                add climb to brick_allocations
                subtract climb from bricks
                if bricks is not negative:
                    continue (this climb is fine for now)
                if ladders is zero:
                    return i (we can't get to i + 1)
                largest_brick_allocation = remove maximum from brick_allocations
                add largest_brick_allocation onto bricks
                subtract one from ladders
            return heights.length - 1 (we must have covered all of the climbs)
        Like how we first tried to use a ladder in approach 1, in this approach, we first try to allocate bricks; this requires adding the climb to the heap and subtracting the climb from bricks. If bricks is still non-negative after doing this, then there is nothing else we need to do for this climb right now, so we continue onto the next one.

        If, however, bricks has become negative, then we'll need to make bricks positive again by reclaiming some bricks; we do this by removing the largest brick allocation from the heap and subtracting 1 from ladders to cover the removed brick allocation. This works because one of two cases is true; either there's a previous climb with more bricks to reclaim, or we've just added the largest climb onto the max-heap. So when we remove the maximum from the max-heap, we'll definitely get at least as many bricks as we just subtracted to make bricks non-negative again.

        The only case we can't simply replace the largest brick allocation with a ladder happens when ladders is already zero. In this case, we know we can't jump to the next building index and so should return the current building index. In the pseudocode, we've firstly checked for this case and then gone onto the process described above for making bricks non-negative.

        Code


        Complexity Analysis

        Let NN be the length of the heights array. Unlike approach 1, it doesn't really make sense to analyze approach 2 in terms of the number of ladders or bricks we started with.

        Time complexity : O(N \log N)O(NlogN).

        Same as Approach 1. In the worst case, we'll be adding and removing up to N - 1N−1 climbs from the heap. Heap operations are O(\log N)O(logN) in the worst case.

        Space complexity : O(N)O(N).

        Same as Approach 1. In the worst case, there'll be N - 1N−1 climbs in the heap.


    """
    def doit_heap_2(self, heights: list, bricks: int, ladders: int) -> int:

        from heapq import heapify, heappop, heappush
        heap = []
        for i in range(len(heights)-1):
            
            diff = bricks[i+1] - bricks[i]

            if diff < 0: continue

            bricks -= diff
            heappush(heap, -diff)

            if bricks < 0 and ladders == 0:
                return i

            if bricks < 0:
                # Max heap, maximumal usage brick will be one to restore and use ladder to replace.
                bricks -= heappop(heap) 
                ladders -= 1

        return len(heights) - 1


if __name__ == '__main__':

    FurthestBuilding().doit_([4,12,2,7,3,18,20,3,19], 10, 2)

    FurthestBuilding().doit_([4,2,7,6,9,14,12], 5, 1)