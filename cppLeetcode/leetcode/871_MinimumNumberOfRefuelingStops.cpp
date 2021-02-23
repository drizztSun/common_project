/*
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
 */
#include <vector>
#include <queue>

using std::priority_queue;
using std::vector;

class MinRefuelStops {

public:

    /*
        // max heap nlogn solution
        // the idea is that we refuel only when the need arises
        // AND when does the need arise:
        // 1. when we are short of visiting the next fuel stations
        // 2. When we have gone past all gas stations and are short on fuel and haven't reached the target yet
        
        // Now we have the occassions as to when we have to refill ..now how do we refill
        // whenver we are short i.e in the above 2 cases we search for the stations that we have covered till now which has the max fuel and if the max fuel station can not provide enough fuel
        // so that we reach the next station or the target then we need to refuell again
        
        // used max heap for effiicent max fuel station search
    */
    int doit_heap(int target, int startFuel, vector<vector<int>>& stations) {
  
        auto n = stations.size();
        priority_queue<int> pq;

        int can_coverdist = startFuel;    //can_coverdist tells the total dist we can cover cover using the available fuel
        int stops = 0;
        for(auto i = 0; i < n; i++){
            
            if(can_coverdist >= target)
                return stops;
        
            while(!pq.empty() && can_coverdist < stations[i][0])  //can't reach the curr station so refuelling
            {
                can_coverdist += pq.top();
                pq.pop();
                stops++;
            }
            
            if(pq.empty() && can_coverdist < stations[i][0])    //can't reach the curr station even with refuelling at all the stations
                return -1;
            
            pq.push(stations[i][1]);        //if code reaches here that means we can reach till this station so we push into heap so that we can refuel in the future if necessary
        }
        
        //case when we have covered all the stations by refuelling at 0 or more stations and still we haven't reached the target
        while(!pq.empty() && can_coverdist < target) {
            can_coverdist += pq.top();
            pq.pop();
            stops++;
        }
        
        return can_coverdist >= target ? stops: -1;
    }

    /*
        871.Minimum-Number-of-Refueling-Stops
        我们可以这样考虑．现在有一定量的startFuel，假设可以驶过两个加油站，但是达不到第三个加油站．说明我们应该在前两个加油站中的某一个或全部两个停下来加油．但是该加多少呢？

        其实，我们不用想的太远，千里之行始于足下，目前只需要加油使得能够开到第三个加油站即可．于是，我们优先考虑前两个加油站里较多的那一个，不够的话就算上另一个．反正到了第三个加油站后，我们就又多了一个option．
        等过了第三个加油站，我们再类似地考虑，是否需要加油才能开到第四个加油站．如果需要，就在前三个加油站里面尚未加过油的那些里，选择油量最多的那个即可；不需要的话，就把第四个加油站放入option list,考虑是否需要加油才能开到第五个加油站...

        这就是贪心法的最优策略．特别注意，我们得把target当做一个加油站来处理。不能只用贪心法处理到最后一个加油站，再用剩下的curFuel来考虑是否能到target，那样是错误的：因为这样的话你只是用尽全力到达最后一个加油站，而并没有用尽全力去到达target。    
    */
    int doit_heap_1(int target, int startFuel, vector<vector<int>>& stations) 
    {
        if (startFuel>=target) return 0;
        
        stations.push_back({target,0});
        
        int stationID = 0;
        int curFuel = startFuel;
        priority_queue<int> pq;
        int count = 0;
        
        while (stationID < stations.size())
        {
            if (curFuel >= stations[stationID][0])
            {
                pq.push(stations[stationID][1]);
                stationID++;                
            }
            else
            {
                while (curFuel < stations[stationID][0] && pq.size() > 0)
                {
                    curFuel += pq.top();
                    pq.pop();
                    count++;
                }
                
                if (curFuel<stations[stationID][0] && pq.size() == 0) return -1;
            }
        }
        
        return count;        
    }
};
