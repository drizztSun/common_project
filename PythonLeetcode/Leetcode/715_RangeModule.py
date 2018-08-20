import os
import bisect



# 715. Range Module
# A Range Module is a module that tracks ranges of numbers. Your task is to design and implement the following interfaces in an efficient manner.

# addRange(int left, int right) Adds the half-open interval [left, right), tracking every real number in that interval. 
# Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval [left, right) that are not already tracked.
# queryRange(int left, int right) Returns true if and only if every real number in the interval [left, right) is currently being tracked.
# removeRange(int left, int right) Stops tracking every real number currently being tracked in the interval [left, right).

# addRange(10, 20) #: null
# removeRange(14, 16) #: null
# queryRange(10, 14) #: true (Every number in [10, 14) is being tracked)
# queryRange(13, 15) #: false (Numbers like 14, 14.03, 14.17 in [13, 15) are not being tracked)
# queryRange(16, 17) #: true (The number 16 in [16, 17) is still being tracked, despite the remove operation)

# Note:
# A half open interval [left, right) denotes all real numbers left <= x < right.
# 0 < left < right < 10^9 in all calls to addRange, queryRange, removeRange.
# The total number of calls to addRange in a single test case is at most 1000.
# The total number of calls to queryRange in a single test case is at most 5000.
# The total number of calls to removeRange in a single test case is at most 1000.

class Interval:
    def __init__(self, s, e):
        self.left = s
        self.right = e

class RangeModule:

    def __init__(self):
        self._intervals = []

    def addRange(self, left, right):
        """
        :type left: int
        :type right: int
        :rtype: void
        """
        if not self._intervals:
            self._intervals.append(Interval(left, right))
            return

        leftS, rightS = [], []
        for item in self._intervals:
            if item.right < left:
                leftS.append(item)

            elif item.left > right:
                rightS.append(item)

            else:
                left = min(left, item.left)
                right = max(right, item.right)

        self._intervals = leftS + [Interval(left, right)] + rightS

    def queryRange(self, left, right):
        """
        :type left: int
        :type right: int
        :rtype: bool
        """
        for item in self._intervals:
            if item.left <= left and item.right >= right:
                return True

        return False


    def removeRange(self, left, right):
        """
        :type left: int
        :type right: int
        :rtype: void
        """
        if left >= right:
            return
        
        #while i < len(self._intervals):

            #item = self._intervals[i]

        
        for i, item in enumerate(self._intervals):

            if item.right <= left:
                continue
            
            if item.left >= right:
                break

            if item.left >= left and item.right <= right:
                self._intervals.pop(i)

            elif item.left <= left < right <= item.right:
                self._intervals[i] = Interval(item.left, left)
                self._intervals.insert(i+1, Interval(right, item.right))
                break

            if item.left < left < item.right < right:
                self._intervals[i].right = left


            if left < item.left < right < item.right:
                self._intervals[i].left = right

            
            
            


class RangeModuleBisect(object):

    def __init__(self):

        self.X = [0, 10 ** 9]

        self.track = [False] * 2


    def addRange(self, left, right, track = True):

        def pos(n):
            i = bisect.bisect_left(self.X, n)
            if self.X[i] != n:
                self.X.insert(i, n)
                self.track.insert(i, self.track[i-1])

            return i
        
        i, j = pos(left), pos(right)
        self.X[i:j] = [left]
        self.track[i:j] = [track]


    def queryRange(self, left, right):

        i = bisect.bisect(self.X, left) - 1
        j = bisect.bisect_left(self.X, right)

        return all(self.track[i:j])


    def removeRange(self, left, right):
        self.addRange(left, right, False)


if __name__=="__main__":

    # Your RangeModule object will be instantiated and called as such:
    obj = RangeModuleBisect()

    obj.addRange(10, 180)

    obj.addRange(150, 200)

    obj.addRange(250, 500)

    res = obj.queryRange(50, 100) 

    res = obj.queryRange(180, 300) 

    res = obj.queryRange(600, 1000) 

    obj.removeRange(50, 150)

    res = obj.queryRange(50, 100) 


    #obj = RangeModule()

    #obj.addRange(140, 100)
    #obj.removeRange(1, 8)

    #res = obj.queryRange(77, 80)
    #res = obj.queryRange(8, 43)
    #res = obj.queryRange(4, 13)

    #res = obj.removeRange(3, 9)
    #res = obj.removeRange(45, 49)
    #res = obj.removeRange(41, 90)

    #obj.addRange(58, 79)
    #obj.addRange
    #obj.addRange

    #obj.removeRange
    #obj.addRange
    #obj.queryRange

    #obj.addRange
    #obj.addRange

    #obj.queryRange
    #obj.queryRange

    #obj.addRange
    #obj.removeRange
    #obj.removeRange
    #obj.removeRange

    #obj.queryRange
    #obj.queryRange

    #obj.addRange
    #obj.addRange

    #obj.queryRange
    #obj.addRange
    #obj.addRange
    #obj.removeRange

    #obj.addRange
    #obj.addRange

    #obj.queryRange
    #obj.removeRange

    #obj.queryRange
    #obj.removeRange

    
    





    



    pass