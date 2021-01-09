"""
1094. Car Pooling

You are driving a vehicle that has capacity empty seats initially available for passengers.  The vehicle only drives east (ie. it cannot turn around and drive west.)

Given a list of trips, trip[i] = [num_passengers, start_location, end_location] contains information about the i-th trip: the number of passengers that must be picked up, and the locations to pick them up and drop them off. 
The locations are given as the number of kilometers due east from your vehicle's initial location.

Return true if and only if it is possible to pick up and drop off all passengers for all the given trips. 

 

Example 1:

Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false
Example 2:

Input: trips = [[2,1,5],[3,3,7]], capacity = 5
Output: true
Example 3:

Input: trips = [[2,1,5],[3,5,7]], capacity = 3
Output: true
Example 4:

Input: trips = [[3,2,7],[3,7,9],[8,3,9]], capacity = 11
Output: true
 
 

Constraints:

trips.length <= 1000
trips[i].length == 3
1 <= trips[i][0] <= 100
0 <= trips[i][1] < trips[i][2] <= 1000
1 <= capacity <= 100000



Solution
Overview
It is one of the classical problems related to intervals, and we have some similar problems such as Meeting Rooms II at LeetCode. Below, two approaches are introduced: the simple Time Stamp approach, and the Bucket Sort approach.

"""


class CarPooling:

    """
        Approach 1: Time Stamp
        Intuition

        A simple idea is to go through from the start to end, and check if the actual capacity exceeds capacity.

        To know the actual capacity, we just need the number of passengers changed at each timestamp.

        We can save the number of passengers changed at each time, sort it by timestamp, and finally iterate it to check the actual capacity.

        Algorithm

        We will initialize a list to store the number of passengers changed and the corresponding timestamp and then sort it.

        Note that in Java, we do not have a nice API to do this. However, we can use a TreeMap, which can help us to sort during insertion. You can use a PriorityQueue instead.

        Finally, we just need to iterate from the start timestamp to the end timestamp and check if the actual capacity meets the condition.

        Complexity Analysis

        Assume NN is the length of trips.

        Time complexity: O(Nlog(N)) since we need to iterate over trips and sort our timestamp. Iterating costs \mathcal{O}(N)O(N), and sorting costs \mathcal{O}(N\log(N))O(Nlog(N)), and adding together we have \mathcal{O}(N) + \mathcal{O}(N\log(N)) = \mathcal{O}(N\log(N))O(N)+O(Nlog(N))=O(Nlog(N)).

        Space complexity: O(N) since in the worst case we need \mathcal{O}(N)O(N) to store timestamp.
    """
    def doit_interval(self, trips: list, capacity: int) -> bool:
        timestamp = []
        for trip in trips:
            timestamp.append([trip[1], trip[0]])
            timestamp.append([trip[2], -trip[0]])

        timestamp.sort()

        used_capacity = 0
        for time, passenger_change in timestamp:
            used_capacity += passenger_change
            if used_capacity > capacity:
                return False

        return True

    """
        Approach 2: Bucket Sort
        Intuition

        Note that in the problem there is a interesting constraint:

        0 <= trips[i][1] < trips[i][2] <= 1000
        What pops into the mind is Bucket Sort, which is a sorting algorithm in \mathcal{O}(N)O(N) time but requires some prior knowledge for the range of the data.

        We can use it instead of the normal sorting in this method.

        What we do is initial 1001 buckets, and put the number of passengers changed in corresponding buckets, and collect the buckets one by one.

        Algorithm

        We will initial 1001 buckets, iterate trip, and save the number of passengers changed at i mile in the i-th bucket.


    """
    def doit_interval_2(self, trips: List[List[int]], capacity: int) -> bool:
        timestamp = [0] * 1001
        for trip in trips:
            timestamp[trip[1]] += trip[0]
            timestamp[trip[2]] -= trip[0]

        used_capacity = 0
        for passenger_change in timestamp:
            used_capacity += passenger_change
            if used_capacity > capacity:
                return False

        return True

    def doit_heap(self, trips: List[List[int]], capacity: int) -> bool:
        from heapq import heapify, heappush, heappop

        trips.sort(key=lambda x: x[1])
        persons, heap = 0, []

        for p, s, e in trips:

            while heap and heap[0][0] <= s:
                _, dropoff = heappop(heap)
                persons -= dropoff

            if persons + p > capacity:
                return False

            heappush(heap, (e, p))
            person += p

        return True


        