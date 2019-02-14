# 703. Kth Largest Element in a Stream

# Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, 
# not the kth distinct element.

# Your KthLargest class will have a constructor which accepts an integer k and an integer array nums, 
# which contains initial elements from the stream. For each call to the method KthLargest.add, 
# return the element representing the kth largest element in the stream.

# Example:

# int k = 3;
# int[] arr = [4,5,8,2];
# KthLargest kthLargest = new KthLargest(3, arr);
# kthLargest.add(3);   // returns 4
# kthLargest.add(5);   // returns 5
# kthLargest.add(10);  // returns 5
# kthLargest.add(9);   // returns 8
# kthLargest.add(4);   // returns 8
# Note: 
# You may assume that nums' length ≥ k-1 and k ≥ 1.

import bisect

class KthLargestBisect:

    def __init__(self, k: 'int', nums: 'List[int]'):
        
        self.buff = []
        self.k = k
        for c in nums:
            self.add(c)

    def add(self, val: 'int') -> 'int':
        if len(self.buff) == self.k and val <= -self.buff[-1]:
            return -self.buff[-1]
        
        bisect.insort(self.buff, -val)
        if len(self.buff) == self.k + 1:
            self.buff.pop()
        
        return -self.buff[-1]

import heapq

class KthLargestHeap:

    def __init__(self, k : 'int', nums: 'List[int]'):

        self.__buff = nums
        heapq.heapify(self.__buff)
        self.__k = k

    def add(self, val: 'int') -> 'int':

        heapq.push(self.__buff, val)

        while len(self.__buff) > self.__k:
            heapq.pop(self.__buff)

        return self.__buff[0]
        

