


# 732. My Calendar III

# Implement a MyCalendarThree class to store your events. A new event can always be added.

# Your class will have one method, book(int start, int end).
# Formally, this represents a booking on the half open interval [start, end),
# the range of real numbers x such that start <= x < end.

# A K-booking happens when K events have some non-empty intersection
# (ie., there is some time that is common to all K events.)

# For each call to the method MyCalendar.book, return an integer K representing the largest integer
# such that there exists a K-booking in the calendar.

# Your class will be called like this: MyCalendarThree cal = new MyCalendarThree(); MyCalendarThree.book(start, end)

# Example 1:
# MyCalendarThree();
# MyCalendarThree.book(10, 20); // returns 1
# MyCalendarThree.book(50, 60); // returns 1
# MyCalendarThree.book(10, 40); // returns 2
# MyCalendarThree.book(5, 15); // returns 3
# MyCalendarThree.book(5, 10); // returns 3
# MyCalendarThree.book(25, 55); // returns 3

# Explanation: 
# The first two events can be booked and are disjoint, so the maximum K-booking is a 1-booking.
# The third event [10, 40) intersects the first event, and the maximum K-booking is a 2-booking.
# The remaining events cause the maximum K-booking to be only a 3-booking.
# Note that the last event locally causes a 2-booking, but the answer is still 3 because
# eg. [10, 20), [10, 40), and [5, 15) are still triple booked.
# Note:

# The number of calls to MyCalendarThree.book per test case will be at most 400.
# In calls to MyCalendarThree.book(start, end), start and end are integers in the range [0, 10^9].


class MyCalendarTree1:


# This is to find the maximum number of concurrent ongoing event at any time.

# We can log the start & end of each event on the timeline, each start add a new ongoing event at that time, each end terminate an ongoing event.
# Then we can scan the timeline to figure out the maximum number of ongoing event at any time.

# The most intuitive data structure for timeline would be array, but the time spot we have could be very sparse,
# so we can use sorted map to simulate the time line to save space.

    def __init__(self):
        self.points_ = []

    def book(self, start, end):
        """
        :type start: int
        :type end: int
        :rtype: int
        """
        import bisect

        bisect.insort(self.points_, [start, 1])
        bisect.insort(self.points_, [end, -1])

        ongoing, k = 0, 0
        for P in self.points:
            ongoing += P[1]
            k = max(k, ongoing)

        return k





class node:
    def __init__(self, s, e, cnt):
        self.s_, self.e_, self.cnt_ = s, e, cnt
        self.left_, self.right_ = None, None
        self.mid_ = -1


class MyCalendarThree:

    def __init__(self):
        self.root_ = node(0, float('inf'), 0)
        self.length_ = 0

    def book(self, start, end):
        """
        :type start: int
        :type end: int
        :rtype: int
        """
        self.add(start, end, self.root_)
        return self.length_
    
    def add(self, s, e, root):
        
        if root.mid_ != -1:
            if root.mid_ >= e:
                self.add(s, e, root.left_)
            elif root.mid_ <= s:
                self.add(s, e, root.right_)
            else:
                self.add(s, root.mid_, root.left_)
                self.add(root.mid_, e, root.right_)
                
        else:
            
            if root.s_ == s and root.e_ == e:
                root.cnt_ += 1
                self.length_ = max(self.length_, root.cnt_)
            
            elif root.s_ == s:
                root.mid_ = e
                root.left_ = node(root.s_, root.mid_, root.cnt_ + 1)
                root.right_ = node(root.mid_, root.e_, root.cnt_)
                self.length_ = max(self.length_, root.cnt_ + 1)
            
            elif root.e_ == e:
                root.mid_ = s
                root.left_ = node(root.s_, root.mid_, root.cnt_)
                root.right_ = node(root.mid_, root.e_, root.cnt_ + 1)
                self.length_ = max(self.length_, root.cnt_ + 1)
                
            else:
                root.mid_ = s
                root.left_ = node(root.s_, root.mid_, root.cnt_)
                root.right_ = node(root.mid_, root.e_, root.cnt_ )
                self.add(s, e, root.right_)
            
                


# Your MyCalendarThree object will be instantiated and called as such:
# obj = MyCalendarThree()
# param_1 = obj.book(start,end)





class MyCalendarThree:

def __init__(self):
    self.sts, self.ends = [], []
    self.mxv = 0
    

def book(self, start, end):
    """
    :type start: int
    :type end: int
    :rtype: int
    """
    from bisect import bisect_left as bl, bisect_right as br, insort_left as il
    from heapq import heappop, heappush

    i, j = bl(self.ends, start), br(self.sts, end)
    il(self.sts, start, i, j)
    il(self.ends, end, i, j)
    heap = []

    for pp in range(i, j + 1):
        while heap and heap[0] <= self.sts[pp]:
            heappop(heap)
        heappush(heap, self.ends[pp])
        self.mxv = max(self.mxv, len(heap))

    return self.mxv



if __name__ == "__main__":

    obj = MyCalendarTree()

    res = obj.book(10, 20)  # returns 1
    res = obj.book(50, 60)  # returns 1
    res = obj.book(10, 40)  # returns 2
    res = obj.book(5, 15)  # returns 3
    res = obj.book(5, 10)  # returns 3
    res = obj.book(25, 55)  # returns 3

    pass