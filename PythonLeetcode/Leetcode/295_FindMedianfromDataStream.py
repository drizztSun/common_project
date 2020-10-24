"""
# 295. Find Median from Data Stream

# Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value.
# So the median is the mean of the two middle value.

# Examples:
# [2,3,4] , the median is 3

# [2,3], the median is (2 + 3) / 2 = 2.5

# Design a data structure that supports the following two operations:

# void addNum(int num) - Add a integer number from the data stream to the data structure.
# double findMedian() - Return the median of all elements so far.
# For example:

# addNum(1)
# addNum(2)
# findMedian() -> 1.5
# addNum(3)
# findMedian() -> 2

"""
import bisect


class MedianFinder1:

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.array_ = []
        
    # O(log(N)        
    def addNum(self, num):
        """
        :type num: int
        :rtype: void
        """
        bisect.insort_left(self.array_, num)

    def findMedian(self):
        """
        :rtype: float
        """
        length = len(self.array_);
        if length % 2 == 1:
            return self.array_[length // 2];
        else:
            return (self.array_[length//2] + self.array_[length//2 - 1]) / 2


from heapq import heappushpop, heappush, heappop, heapify


class MedianFinder:

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.small_, self.large_ = [], []

        heapify(self.small_)
        heapify(self.large_)

        self.even_ = True

    def addNum(self, num):
        """
        :type num: int
        :rtype: void
        """
        if self.even_:
            heappush(self.large_,  -heappushpop(self.small_, -num))
        else:
            heappush(self.small_, -heappushpop(self.large_, num))

        self.even_ = not self.even_

    def findMedian(self):
        """
        :rtype: float
        """
        if self.even_:
            return (self.large_[0] - self.small_[0]) / 2
        else:
            return self.large_[0]


if __name__=="__main__":

    obj = MedianFinder()

    obj.addNum(1)

    obj.addNum(2)

    res = obj.findMedian() # 1.5

    obj.addNum(3)

    res = obj.findMedian() # 2


    pass
    