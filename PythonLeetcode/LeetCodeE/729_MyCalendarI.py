# 729. My Calendar I

# Implement a MyCalendar class to store your events. A new event can be added if adding the event will not cause a double booking.

# Your class will have the method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), 
# the range of real numbers x such that start <= x < end.

# A double booking happens when two events have some non-empty intersection (ie., there is some time that is common to both events.)

# For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a double booking. 
# Otherwise, return false and do not add the event to the calendar.

# Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
# Example 1:
# MyCalendar();
# MyCalendar.book(10, 20); // returns true
# MyCalendar.book(15, 25); // returns false
# MyCalendar.book(20, 30); // returns true

# Explanation: 
# The first event can be booked.  The second can't because time 15 is already booked by another event.
# The third event can be booked, as the first event takes every time less than 20, but not including 20.
# Note:

# The number of calls to MyCalendar.book per test case will be at most 1000.
# In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].


class MyCalendar1:

    def __init__(self):
        self.timings_ = []

    def doit(self, start, end):
        """
        :type start: int
        :type end: int
        :rtype: bool
        """
        for i in range(len(self.timings_)):

            s, e = self.timings_[i]
            if start < e and s < end:
                return False

            if s > start:
                self.timings_.insert(i, (start, end))
                return True

        self.timings_.append((start, end))

        return True

                        



class MyCalendar:

    def __init__(self):        
        self.starts_ = []
        self.ends_ = []
        pass

    def book(self, start, end):
        """
        :type start: int
        :type end: int
        :rtype: bool
        """
        import bisect
        
        s = bisect.bisect_left(self.starts_, start)

        if (s > 0 and self.ends_[s-1] > start) or (s < len(self.starts_) and self.starts_[s] < end):
            return False

        self.starts_.insert(s, start)
        self.ends_.insert(s, end)

        return True   

    def book1(self, start, end):
        """
        :type start: int
        :type end: int
        :rtype: bool
        """
        import bisect
        
        s = bisect.bisect_left(self.starts_, start) - 1

        if s < 0:
            if self.starts_ and self.starts_[0] < end:
                return False

        elif self.ends_[s] > start or (start < self.ends_[s+1] and end > self.starts_[s+1]):
                return False

        self.starts_.insert(s, start)
        self.ends_.insert(s, end)

        return True 
                    
        


# Your MyCalendar object will be instantiated and called as such:
# obj = MyCalendar()
# param_1 = obj.book(start,end)
