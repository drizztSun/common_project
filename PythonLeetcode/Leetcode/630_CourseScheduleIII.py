"""
630. Course Schedule III


There are n different online courses numbered from 1 to n. Each course has some duration(course length) t and closed on dth day. 
A course should be taken continuously for t days and must be finished before or on the dth day. You will start at the 1st day.

Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.

Example:

Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation: 
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
 

Note:

The integer 1 <= d, t, n <= 10,000.
You can't take two courses simultaneously.



"""


class CourseScheduleIII:

    """

    """
    def doit_heap(self, courses: list) -> int:
        from heapq import heappush, heappop

        pq, start = [], 0

        # sort by end time, we need to handle endtime eariler first
        # heap save the as max heap about the course being taken.
        # if take to more, caused start > end, we have to pull out some big course like duration time. 
        for t, end in sorted(courses, key = lambda(t, end): end):
            start += t
            heappush(pq, -t)
            while start > end:
                start += heappop(pq)

        return len(pq)

    def doit_heap(self, courses):
        """
        :type courses: List[List[int]]
        :rtype: int
        """
        import heapq
        courses = sorted(courses, key=lambda p: p[1])
        heap = []
        
        k, T = 0, 0
        #print courses
        for t, e in courses:
            #print T, k
            if T + t <= e:
                T += t
                k += 1
                heapq.heappush(heap, -t)
            elif len(heap) > 0 and t < -heap[0]:
                T = T - (-heap[0]) + t
                heapq.heappushpop(heap, -t)
        return k