/*
134. Gas Station

There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique

 

Example 1:

Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
Example 2:

Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
 

Constraints:

gas.length == n
cost.length == n
1 <= n <= 10^4
0 <= gas[i], cost[i] <= 10^4
*/

#include <vector>

using std::vector;


class GasStation {

    /*
        134.Gas-Station
        此题和 135.Candy 等都是LC比较经典的贪心法的题目，没有固定的套路可以用在其他题目上，但是这两题各自经典的解法值得深刻地记住。

        这里，先考虑是否能够成功绕行一圈的问题。这个比较好理解，将所有的gas之和减去所有的cost之和，如果是负数，那么就说明无法绕行成功。

        那么可以绕行成功，那么该如何选择起点呢？这里有个先行的结论需要先理解一下：如果从A点出发，走到B点就走不下去了，那么从A点到B点之间的任意一点出发，都不可能走过B点（甚至可能在B点之前就走不下去）。
        这个还是比较好理解的。因为假设能从A点走到B点，说明在走到A+1这个点的时候，肯定是有一部分A点的汽油还富余着的。那么说明如果直接从A+1点作为起点出发，肯定相比于从A点作为起点出发，资源更为紧缺，肯定更不可能超越B点。

        所以我们从0点开始出发，假设到了B点走不下去了，那么说明从0点到B点都不可能是作为起点。那么起点从哪里开始呢？我们可以从B+1点作为起点开始尝试。
        如果从B+1点作为起点走到C点就走不下去了，说明B+1点到C点也都不可能作为起点。所以我们可以从C+1点开始尝试...如此下来，我们只要转一圈，就能最终确定从哪里作为起点可以到达0点，即成功环绕一周。
    */
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
    {
        int sum = 0;
        for (int i=0; i<gas.size(); i++)
            sum+= gas[i]-cost[i];
        if (sum<0) return -1;
        
        sum = 0;
        int result=0;
        for (int i=0; i<gas.size(); i++)
        {
            sum+= gas[i]-cost[i];
            if (sum<0)
            {
                sum = 0;
                result = i+1;
            }                
        }
        return result;
    }

public:

    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        int total_tank = 0;
        int curr_tank = 0;
        int starting_station = 0;
        for (int i = 0; i < n; ++i) {
            total_tank += gas[i] - cost[i];
            curr_tank += gas[i] - cost[i];
            // If one couldn't get here,
            if (curr_tank < 0) {
                // Pick up the next station as the starting one.
                starting_station = i + 1;
                // Start with an empty tank.
                curr_tank = 0;
            }
        }
        return total_tank >= 0 ? starting_station : -1;
    }

    int doit_greedy(vector<int>& gas, vector<int>& cost) {
        
        int n = gas.size();
        int start = 0;

        while (start < n) {

            int s = start;
            int total = 0;
            int length = 0;

            while (length < n && total + gas[s] >= cost[s]) {
                length++;
                total += gas[s] - cost[s];
                s = (s+1) % n;
            }

            if (length == n) return start;

            start += length+1;
        }

        return -1;
    }

    int doit_greedy(vector<int>& gas, vector<int>& cost) {    
        
        int n = gas.size();
        vector<int> diff(n, 0);
        
        for (int i = 0; i < gas.size(); i++)
            diff[i] = gas[i] - cost[i];
        
        
        int i = 0;
        
        while (i < n) {
            
            if (diff[i] < 0) {
                i++;
                continue;
            }
        
            int steps = 0, total = 0;
            int j = i;
            while (steps < n) {
                
                if (total + diff[j%n] < 0) break;
                
                total += diff[j%n];
                j++;
                steps++;
            }
            
            if (steps == n) return i;
        
            i = j;
        }
        
        return -1;
    }
};