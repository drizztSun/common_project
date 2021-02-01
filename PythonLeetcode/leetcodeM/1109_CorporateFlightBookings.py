"""
1109. Corporate Flight Bookings



There are n flights, and they are labeled from 1 to n.

We have a list of flight bookings.  The i-th booking bookings[i] = [i, j, k] means that we booked k seats from flights labeled i to j inclusive.

Return an array answer of length n, representing the number of seats booked on each flight in order of their label.

 

Example 1:

Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
Output: [10,55,45,25,25]
 

Constraints:

1 <= bookings.length <= 20000
1 <= bookings[i][0] <= bookings[i][1] <= n <= 20000
1 <= bookings[i][2] <= 10000


"""


class CorpFlightBookings:


    """
        Explanation
        Set the change of seats for each day.
        If booking = [i, j, k],
        it needs k more seat on ith day,
        and we don't need these seats on j+1th day.
        We accumulate these changes then we have the result that we want.


        Complexity
        Time O(booking + N) for one pass on bookings
        Space O(N) for the result

    """
    def doit_sweepline(self, bookings: list, n: int) -> list:


        ans = [0 for _ in range(n+1)]

        for c1, c2, v in bookings:
            ans[c1] += v
            ans[c2+1] -= v

        for i in range(1, n):
            ans[i] += ans[i-1]

        return ans[:-1]


        