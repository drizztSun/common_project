"""
871. Minimum Number of Refueling Stops

A car travels from a starting position to a destination which is target miles east of the starting position.

Along the way, there are gas stations.  Each station[i] represents a gas station that is station[i][0] miles east of the starting position, and has station[i][1] liters of gas.

The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it.  It uses 1 liter of gas per 1 mile that it drives.

When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.

What is the least number of refueling stops the car must make in order to reach its destination?  If it cannot reach the destination, return -1.

Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there.  If the car reaches the destination with 0 fuel left, it is still considered to have arrived.

Example 1:

Input: target = 1, startFuel = 1, stations = []
Output: 0
Explanation: We can reach the target without refueling.
Example 2:

Input: target = 100, startFuel = 1, stations = [[10,100]]
Output: -1
Explanation: We can't reach the target (or even the first gas station).
Example 3:

Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
Output: 2
Explanation:
We start with 10 liters of fuel.
We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the target.
We made 2 refueling stops along the way, so we return 2.



"""


class MinRefuelStops:

    def doit(self, target, startFuel, stations):
        """
        :type target: int
        :type startFuel: int
        :type stations: List[List[int]]
        :rtype: int
        """
        import heapq

        can_reach = startFuel
        fuel = []
        stops = 0

        for i in range(len(stations)):

            if can_reach >= target:
                return stops

            while fuel and can_reach < stations[i][0]:
                can_reach -= heapq.heappop(fuel)
                stops += 1

            if not fuel and can_reach < stations[i][0]:
                return -1

            heapq.heappush(fuel, -stations[i][1])

        while fuel and can_reach < target:
            can_reach -= heapq.heappop(fuel)
            stops += 1

        return -1 if can_reach < target else stops


if __name__ == '__main__':

    MinRefuelStops().doit(100, 50, [[25,25],[50,50]])

    MinRefuelStops().doit(target=100, startFuel=10, stations=[[10,60],[20,30],[30,30],[60,40]])

    MinRefuelStops().doit(1000, 299, [[13,21],[26,115],[100,47],[225,99],[299,141],[444,198],[608,190],[636,157],[647,255],[841,123]])

