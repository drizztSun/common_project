"""
1509. Minimum Difference Between Largest and Smallest Value in Three Moves


Given an array nums, you are allowed to choose one element of nums and change it by any value in one move.

Return the minimum difference between the largest and smallest value of nums after perfoming at most 3 moves.

 

Example 1:

Input: nums = [5,3,2,4]
Output: 0
Explanation: Change the array [5,3,2,4] to [2,2,2,2].
The difference between the maximum and minimum is 2-2 = 0.
Example 2:

Input: nums = [1,5,0,10,14]
Output: 1
Explanation: Change the array [1,5,0,10,14] to [1,1,0,1,1]. 
The difference between the maximum and minimum is 1-0 = 1.
Example 3:

Input: nums = [6,6,0,1,1,4,6]
Output: 2
Example 4:

Input: nums = [1,5,6,14,15]
Output: 1
 

Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9


"""



class MiniumDifferenceBetweenLargest:

    def doit_sort(self, nums: list) -> int:
        if len(nums) < 5: return 0
        nums.sort()
        return min(nums[-4]-nums[0], nums[-3]-nums[1], nums[-2]-nums[2], nums[-1]-nums[3])

    
    def doit_heap(self, nums: list) -> int:
        
        from heapq import heappush, heappop, heapify
        
        if len(nums) < 5: return 0;
        
        if len(nums) < 10:
            nums.sort()
            return min(nums[-4]-nums[0], nums[-3]-nums[1], nums[-2]-nums[2], nums[-1]-nums[3])
        
        
        minheap = []
        maxheap = []
        heapify(minheap)
        heapify(maxheap)
        
        for c in nums:
            
            heappush(minheap, -c)
            if len(minheap) > 4:
                heappop(minheap)
                
            heappush(maxheap, c)
            if len(maxheap) > 4:
                heappop(maxheap)
                
        minv = []
        while minheap:
            minv.append(-heappop(minheap))

        maxv = []
        while maxheap:
            maxv.append(heappop(maxheap))
        
        print(maxv)
        print(minv)
        ans = float('inf')
        for i in range(4):
            ans = min(ans, maxv[3-i] - minv[i])
            
        return ans


if __name__ == '__main__':


    pass
        