/*
517. Super Washing Machines

You have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.

For each move, you could choose any m (1 ≤ m ≤ n) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time .

Given an integer array representing the number of dresses in each washing machine from left to right on the line, 
you should find the minimum number of moves to make all the washing machines have the same number of dresses. If it is not possible to do it, return -1.

Example1

Input: [1,0,5]

Output: 3

Explanation: 
1st move:    1     0 <-- 5    =>    1     1     4
2nd move:    1 <-- 1 <-- 4    =>    2     1     3    
3rd move:    2     1 <-- 3    =>    2     2     2   
Example2

Input: [0,3,0]

Output: 2

Explanation: 
1st move:    0 <-- 3     0    =>    1     2     0    
2nd move:    1     2 --> 0    =>    1     1     1     
Example3

Input: [0,2,0]

Output: -1

Explanation: 
It's impossible to make all the three washing machines have the same number of dresses. 
Note:
The range of n is [1, 10000].
The range of dresses number in a super washing machine is [0, 1e5].

*/

#include <vector>
#include <numeric>

using std::vector;


class MinMoves {

    /*
        517.Super-Washing-Machines
        此题初看会有一种用DP的错觉．但细细想一想，其实最优策略是可以手工制定出来的，这就是贪心法．

        首先，我们应该有这样的直觉，对任意一台洗衣机，最优的转移策略肯定不会出现＂反反复复＂的情况．即经过充分的优化调度后，衣物的转移应该是单向的．假设对于第i台洗衣机，最终平衡态是k件，
        设整个过程中i总共向左边净转移了left[i]件衣物，向右边净转移了right[i]件衣物，则必定满足如下关系：

        machines[i]-k = left[i]+right[i]
        并且在实际的最优操作中，第i台一定只需要向左移动left[i]件衣物，向右移动right[i]件衣物即可（注意，这两个值可能是负数）。总之同一个边不会有多余的双向操作。

        其次，我们把所有洗衣机的初始状态想象成一座连绵起伏的山峦。每一次move前，我们知道哪些山峰是净输出的，哪些山谷是净输入的，而这一次move的效果就是：将某些山峰的一件衣物“超距作用”地转移到某些山谷中去。
        所谓的“超距作用”，就是说这种山峰填山谷的操作只需要一个回合就能完成。这是因为每个回合所有的洗衣机都在同时工作，每个洗衣机只有三种作用：净输出1，净值为0，净输入1或者2（某个山谷同时由两边来填）。
        那些净值为0的洗衣机其实就相当于传送带，某一边输入一件，同时又往另一边输出一件，从而协助了山峰填山谷的超距作用。

        很显然，整批洗衣机需要停止工作的回合，就是等到那些山峰最终夷为平地的时刻。所以最终答案，就是找到“总输出”最多的那台机器即可。为什么是要算总输出呢？因为有可能是这种情景:左边的次山峰->主山峰->填补谷底。这样的一个回合，主山峰其实并没有净输出，是次山峰在净输出。但我们可以想象，主山峰一定是在不停地输出（不一定是净输出），而当主山峰不输出了，说明肯定一切都已经夷为平地了。

        至于如何确定left[i]和right[i]是比较简单的，突破口就是最左边的洗衣机，其left[i]一定是零；次外，所有的right[i]=-left[i+1]。故这些变量都可解。
    */


public:

    int doit_greedy(vector<int>& machines) 
    {
        int n = machines.size();
        vector<int> left(n,0);
        vector<int> right(n,0);

        int sum = 0;
        for (auto x:machines) sum += x;
        
        if (sum%n!=0) return -1;
        int k = sum/n;

        right[0] = machines[0] - k;
        for (int i=1; i<n-1; i++)
        {
            left[i] = -right[i-1];
            right[i] = machines[i]-k-left[i];
        }
        left[n-1] = machines[n-1]-k;

        int ret = 0;
        for (int i=0; i<n; i++)
        {
            int t = 0;
            if (left[i]>0) t+= left[i];
            if (right[i]>0) t+= right[i];

            ret = std::max(ret,t);
        }
        return ret;
    }


    /*
        Approach 1: Greedy.
        Intuition

        This greedy problem is very similar to Gas station problem, and could be solved in linear time as well.

        First of all - could the problem be solved or not?

        Yes, if the dresses could be divided into N equal parts where N is number of machines. In other words, N should be a divisor of the number of dresses D.

        Now it's easy to compute the number of dresses that each machine should have: D / N. The starting numbers of dresses in the machines move around this D / N average value.

        The standard ML trick is to normalize the data, so that the average value would be zero. For that, one could replace the actual number of dresses in the machine by the number of dresses to be removed. 
        This number could be negative, if one actually needs to add the dresses into the machine.

        As for the gas station problem, one starts from the beginning and checks the standard set for such problems: the current element, the current sum, and the maximum sum seen so far :

        1) m. Number of dresses to be removed from the current machine.

        2) curr_sum. Number of dresses to be passed on the right.

        3) max_sum. Maximum number of dresses one had to pass on the right at this point or before.

        It's quite obvious that the result at each point is a maximum between max_sum and m, i.e. one has to compare the cumulative and the local maximums.

        Here are three different examples.

        [1, 0, 5]. The cumulative maximum is equal to the local one.
        bla

        [0, 3, 0]. The local maximum wins over the cumulative one.
        bla

        [0, 0, 3, 5]. The cumulative maximum wins over the local one.
        bla

        Algorithm

        Here is the algorithm.

        1.Check if the problem could be solved: len(machines) should be a divisor of sum(machines). Otherwise the answer is -1.

        2.Compute the number of dresses each machine should finally have: dresses_per_machine = sum(machines)/len(machines).

        3. Normalize the problem by replacing the number of dresses in each machine by the number of dresses to be removed from this machine (could be negative).

        4. Initiate curr_sum, max_sum, and res as zero.

        5. Iterate over all machines m in machines:

            Update curr_sum and max_sum at each step: curr_sum += m, max_sum = max(max_sum, abs(curr_sum)).
            Update result res = max(res, max_sum, m).

        6. Return res.

        Implementation

        Complexity Analysis

        Time complexity : O(N) since it's a three iterations over the input array.
        Space complexity : O(1) since it's a constant space solution.
    */
    int findMinMoves(vector<int>& machines) {
    
        int n = machines.size();

        int total = std::accumulate(begin(machines), end(machines), 0);
        
        if (total % n != 0) return -1;
        
        int ave = total / n;
        
        int maxv = 0, diff = 0, cnt = 0;
        
        for (auto c : machines) {
            
            diff = c - ave;
            cnt += diff;
            
            maxv = std::max({c-ave, maxv, abs(cnt)});
        }
        
        return maxv;
    }

    /*
        Approach 1: Greedy.
        Intuition

        This greedy problem is very similar to Gas station problem, and could be solved in linear time as well.

        First of all - could the problem be solved or not?

        Yes, if the dresses could be divided into N equal parts where N is number of machines. In other words, N should be a divisor of the number of dresses D.

        bla

        Now it's easy to compute the number of dresses that each machine should have: D / N. The starting numbers of dresses in the machines move around this D / N average value.

        bla

        The standard ML trick is to normalize the data, so that the average value would be zero. For that, one could replace the actual number of dresses in the machine by the number of dresses to be removed. This number could be negative, if one actually needs to add the dresses into the machine.

        bla

        As for the gas station problem, one starts from the beginning and checks the standard set for such problems: the current element, the current sum, and the maximum sum seen so far :

        m. Number of dresses to be removed from the current machine.

        curr_sum. Number of dresses to be passed on the right.

        max_sum. Maximum number of dresses one had to pass on the right at this point or before.

        It's quite obvious that the result at each point is a maximum between max_sum and m, i.e. one has to compare the cumulative and the local maximums.

        Here are three different examples.

        [1, 0, 5]. The cumulative maximum is equal to the local one.
        bla

        [0, 3, 0]. The local maximum wins over the cumulative one.
        bla

        [0, 0, 3, 5]. The cumulative maximum wins over the local one.
        bla

        Algorithm

        Here is the algorithm.

        Check if the problem could be solved: len(machines) should be a divisor of sum(machines). Otherwise the answer is -1.

        Compute the number of dresses each machine should finally have: dresses_per_machine = sum(machines)/len(machines).

        Normalize the problem by replacing the number of dresses in each machine by the number of dresses to be removed from this machine (could be negative).

        Initiate curr_sum, max_sum, and res as zero.

        Iterate over all machines m in machines:

        Update curr_sum and max_sum at each step: curr_sum += m, max_sum = max(max_sum, abs(curr_sum)).

        Update result res = max(res, max_sum, m).

        Return res.

        Implementation


        Complexity Analysis

        Time complexity : \mathcal{O}(N)O(N) since it's a three iterations over the input array.

        Space complexity : \mathcal{O}(1)O(1) since it's a constant space solution.
    
    */
    int doit_best(vector<int>& machines) {

        int n = machines.size(), dresstotal = 0;
        
        for (auto c: machines) dresstotal += c;
        
        if (dresstotal % n != 0) return -1;
        
        int dressPerMachine = dresstotal / n;
        // Change the number of dresses in the machines to
        // the number of dresses to be removed from this machine
        // (could be negative)
        for (int i = 0; i < n; i++) machines[i] -= dressPerMachine;
        
        // currSum is a number of dresses to move at this point, 
        // maxSum is a max number of dresses to move at this point or before,
        // m is number of dresses to move out from the current machine.
        int curSum = 0, maxSum = 0, tmpRes = 0, res = 0;
        for (auto m: machines) {
            curSum += m;
            maxSum = std::max(maxSum, abs(curSum));
            tmpRes = std::max(maxSum, m);
            
            res = std::max(res, tmpRes);
        }
        
        return res;
    }
};