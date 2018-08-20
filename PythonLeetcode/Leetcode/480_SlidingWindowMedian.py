


# 480. Sliding Window Median

# Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value.
# So the median is the mean of the two middle value.

# Examples: 
# [2,3,4] , the median is 3

# [2,3], the median is (2 + 3) / 2 = 2.5

# Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right.
# You can only see the k numbers in the window. Each time the sliding window moves right by one position.
# Your job is to output the median array for each window in the original array.

# For example,
# Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

# Window position                Median
# ---------------               -----
# [1  3  -1] -3  5  3  6  7       1
#  1 [3  -1  -3] 5  3  6  7       -1
#  1  3 [-1  -3  5] 3  6  7       -1
#  1  3  -1 [-3  5  3] 6  7       3
#  1  3  -1  -3 [5  3  6] 7       5
#  1  3  -1  -3  5 [3  6  7]      6
# Therefore, return the median sliding window as [1,-1,-1,3,5,6].

import bisect

from heapq import heappush, heappop

class MedianSlidingWindow:


    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[float]
        """
        def median(wind, k):
            return wind[k//2] if k % 2 == 1  else (wind[k//2] + wind[k//2 - 1]) / 2

        window = sorted(nums[:k])
        Median = [float(median(window, k))]

        for i in range(k, len(nums)):
            
            if nums[i] != nums[i-k]:
                
                window.remove(nums[i-k])

                bisect.insort_left(window, nums[i])

            Median.append(float(median(window, k)))

        return Median
            
                

            
    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[float]
        """
        window = sorted(nums[:k])
        medians = []

        for a, b in zip(nums, nums[k:] + [0]):

            medians.append((window[k//2] + window[-(k//2)-1]) // 2 )

            window.pop(bisect.bisect(window, a) - 1)
            
            bisect.insort(window, b)

        return medians

            
        
        
    def doit(self, nums, k):             
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[float]
        """
        first, second = [], []
        size1, size2 = 0, 0
        ans = []
        lookup = collections.defaultdict(int)

        for i in range(k-1):
            heappush(first, -nums[i])
            size1 += 1

        for _ in range((k-1)//2):
            heappush(second, -heappop(first))
            size1 -= 1
            size2 += 1

        # print(first, second)
        for i in range(k-1, len(nums)):
            # print("first", i, first, second, size1, size2, lookup)
            if not first or nums[i] < -first[0]:
                heappush(first, -nums[i])
                size1 += 1
            else:
                heappush(second, nums[i])
                size2 += 1
            # print("first----", i, first, second, size1, size2, lookup)
            if i >= k:
                lookup[nums[i-k]] += 1
                if nums[i-k] <= -first[0]:
                    size1 -= 1
                else:
                    size2 -= 1
            # print(i, first, second)
            
            
            # print("third", i, first, second, size1, size2, lookup)
            if size1 > size2 + 1:
                heappush(second, -heappop(first))
                size1 -= 1
                size2 += 1
            elif size2 > size1:
                heappush(first, -heappop(second))
                size1 += 1
                size2 -= 1
            # print("fourth", i, first, second, size1, size2, lookup)
            
            while first and lookup[-first[0]] > 0:
                lookup[-first[0]] -= 1
                heappop(first)
            while second and lookup[second[0]] > 0:
                lookup[second[0]] -= 1
                heappop(second)    
            # print("second", i, first, second, size1, size2, lookup)
            if (size1 + size2) %2 == 1:
                ans.append(-first[0]*1.0)
            else:
                ans.append((-first[0] + second[0])*0.5)
            # print(ans)
        return ans        
        



if __name__=="__main__":



    msw = MedianSlidingWindow();

    res = msw.doit([1,3,-1,-3,5,3,6,7], 3)


    pass

    


        


