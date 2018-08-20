


# 352. Data Stream as Disjoint Intervals

# Given a data stream input of non-negative integers a1, a2, ..., an, ...,
# summarize the numbers seen so far as a list of disjoint intervals.

# For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:

# [1, 1]
# [1, 1], [3, 3]
# [1, 1], [3, 3], [7, 7]
# [1, 3], [7, 7]
# [1, 3], [6, 7]

# Definition for an interval.
class Interval(object):
    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e


import bisect
class SummaryRanges1(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """ 
        self.group_ = [] #set()
        self.table_ = set()

    def addNum(self, val):
        """
        :type val: int
        :rtype: void
        """
        #self.group_.add(val)
        if val not in self.table_:
            self.table_.add(val)
            bisect.insort(self.group_, val)
        

    def getIntervals(self):
        """
        :rtype: List[Interval]
        """
        res = []
        if not self.group_:
            return res

        res.append(Interval(self.group_[0], self.group_[0]))
        i = 1
        while i < len(self.group_):
            
            if self.group_[i] == res[-1].end + 1:
                res[-1].end = self.group_[i]
            
            else:
                res.append(Interval(self.group_[i], self.group_[i]))    
    
            i += 1

        return res

        
        
import heapq
class SummaryRanges2(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """ 
        self.group_ = [] #set()
        self.table_ = set()

    def addNum(self, val):
        """
        :type val: int
        :rtype: void
        """
        if val not in self.table_:
            self.table_.add(val)
            heapq.heappush(self.group_, (val, Interval(val, val)))       

    def getIntervals(self):
        """
        :rtype: List[Interval]
        """
        res = []

        while self.group_:
        
            val, interval = heapq.heappop(self.group_)

            if not res:
                res.append( (val, interval) )

            else:
                if val == res[-1][1].end + 1:
                    res[-1][1].end = max(res[-1][1].end, interval.end)
                else:
                    res.append( (val, interval))

        self.group_ = res

        return list(map(lambda x : x[1], res))
            

# Your SummaryRanges object will be instantiated and called as such:
# obj = SummaryRanges()
# obj.addNum(val)
# param_2 = obj.getIntervals()


class SummaryRanges(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.interval = []
        self.reg = []

    def addNum(self, val):
        """
        :type val: int
        :rtype: void
        """
        self.reg.append( val )
        

    def getIntervals(self):
        """
        :rtype: List[Interval]
        """
        while(self.reg != []):

            self.cur = self.reg.pop(0)

            if self.interval == []:
                self.interval.append(Interval(self.cur, self.cur))
                continue

            if self.interval[0].start > self.cur:
                if self.interval[0].start - 1 == self.cur:
                    self.interval[0].start = self.cur
                
                else:
                    self.interval.insert(0,Interval(self.cur, self.cur))
                continue

            if self.interval[-1].end < self.cur:
                if self.interval[-1].end + 1 == self.cur:
                    self.interval[-1].end = self.cur
                
                else:
                    self.interval.append(Interval(self.cur, self.cur))
                continue

            pre = -1
            l = 0
            r = len(self.interval) - 1

            while(l < r):

                mid = ( l + r ) / 2
                if self.interval[mid].end >= self.cur:
                    r = mid

                elif self.interval[mid+1].start <= self.cur:
                    l = mid + 1

                else:
                    pre = mid
                    break

            if pre != -1:
                if self.interval[pre].end == self.cur - 1 and self.interval[pre+1].start == self.cur + 1:
                    self.interval[pre].end = self.interval[pre+1].end
                    del self.interval[pre + 1]

                elif self.interval[pre].end != self.cur - 1 and self.interval[pre+1].start == self.cur + 1:
                    self.interval[pre+1].start = self.cur

                elif self.interval[pre].end == self.cur - 1 and self.interval[pre+1].start != self.cur + 1:
                    self.interval[pre].end = self.cur

                else:
                    self.interval.insert(pre+1, Interval(self.cur, self.cur))

        return self.interval
    



import heapq

class SummaryRanges(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """ 
        self.intervals_ = []
        self.group_ = [] 

    def addNum(self, val):
        """
        :type val: int
        :rtype: void
        """
        self.group_.append(val)        

    def getIntervals(self):
        """
        :rtype: List[Interval]
        """
        while self.group_:
            
            A = self.group_.pop(0)
            
            if not self.intervals_:
                self.intervals_.append(Interval(A, A))
                continue 
                
            elif A < self.intervals_[0].start:
                if self.intervals_[0].start - 1 == A:
                    self.intervals_[0].start = A
                else:
                    self.intervals_.insert(0, Interval(A, A))
                continue
                    
            elif A > self.intervals_[-1].end < A:
                if self.intervals_[-1].end +1 == A:
                    self.intervals_[-1].end = A
                else:
                    self.intervals_.append(Interval(A, A))
                continue
                    
            l, r = 0, len(self.intervals_)-1
            pre = -1

            while l < r:
                mid = (l + r) // 2

                if self.intervals_[mid].end >= A:
                    r = mid
        
                elif self.intervals_[mid+1].start <= A:
                    l = mid + 1
                    
                else:
                    pre = mid
                    break
                    
            if pre != -1:
                
                if self.intervals_[pre].end + 1 == A and self.intervals_[pre+1].start -1 == A:
                    self.intervals_[pre].end = self.intervals_[pre + 1].end
                    self.intervals_.pop(pre + 1)
                    
                elif self.intervals_[pre].end + 1 != pre and self.intervals_[pre+1].start - 1 == A:
                    self.intervals_[pre+1].start = A
                    
                elif self.intervals_[pre].end +1 == A and self.intervals_[pre+1].start != A:
                    self.intervals_[pre].end = A
                    
                else:
                    self.intervals_.insert(pre+1, Interval(A, A))
                
                    
        return self.intervals_                 
        

if __name__=="__main__":

    obj = SummaryRanges()

    obj.addNum(6)
    res = obj.getIntervals()
    
    obj.addNum(6)
    res = obj.getIntervals()

    obj.addNum(0)
    res = obj.getIntervals()
    
    obj.addNum(4)
    res = obj.getIntervals()
    
    obj.addNum(8)
    res = obj.getIntervals()
    
    obj.addNum(7)
    res = obj.getIntervals()

    obj.addNum(6)
    res = obj.getIntervals()

    obj.addNum(4)
    res = obj.getIntervals()

    obj.addNum(7)
    res = obj.getIntervals()

    obj.addNum(5)
    res = obj.getIntervals()

    pass