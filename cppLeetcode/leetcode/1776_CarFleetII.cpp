/*
1776. Car Fleet II

There are n cars traveling at different speeds in the same direction along a one-lane road. You are given an array cars of length n, where cars[i] = [positioni, speedi] represents:

    . positioni is the distance between the ith car and the beginning of the road in meters. It is guaranteed that positioni < positioni+1.
    . speedi is the initial speed of the ith car in meters per second.
For simplicity, cars can be considered as points moving along the number line. Two cars collide when they occupy the same position. 
Once a car collides with another car, they unite and form a single car fleet. The cars in the formed fleet will have the same position and the same speed, which is the initial speed of the slowest car in the fleet.

Return an array answer, where answer[i] is the time, in seconds, at which the ith car collides with the next car, or -1 if the car does not collide with the next car. Answers within 10-5 of the actual answers are accepted.

 

Example 1:

Input: cars = [[1,2],[2,1],[4,3],[7,2]]
Output: [1.00000,-1.00000,3.00000,-1.00000]
Explanation: After exactly one second, the first car will collide with the second car, and form a car fleet with speed 1 m/s. After exactly 3 seconds, the third car will collide with the fourth car, and form a car fleet with speed 2 m/s.
Example 2:

Input: cars = [[3,4],[5,4],[6,3],[9,1]]
Output: [2.00000,1.00000,1.50000,-1.00000]
 

Constraints:

1 <= cars.length <= 105
1 <= positioni, speedi <= 106
positioni < positioni+1


*/
#include <vector>
#include <deque>
#include <array>
#include <stack>

using std::stack;
using std::array;
using std::deque;
using std::vector;

class CarFleetII {


    /*
        1776.Car-Fleet-II
        本题的关键是明确这样一个概念：任何一辆车的行驶历程，初始速度是它本身的速度，之后的速度如果有变化，那么只可能越来越慢（没有任何理由会让一辆车加速）。第一次变慢的原因就是因为它和前面的车相撞，速度被降下来。
        
        注意，此时的速度不一定是前车的原始速度，而是前车在碰撞时刻的速度，因为前车在之前可能也经历了一些碰撞。而第一次相撞之后，它的速度就完全和前面那辆车一样了。

        我们给每一辆车建立“速度-时间”曲线。这个曲线一定是分段阶跃函数，每一次阶跃点代表着碰撞的时刻。所以这个曲线可以用若干个{tk,vk}来表示，即tk时刻之后该车的速度变成了vk，这样在t-v曲线上就有表现为若干段柱状。这些bar围成的面积就是代表这辆车随着时间的推移，所行驶的距离。

        对于第0辆车（最前面的车），它的曲线就是{0, v0}。在图像上就是从(0,v0)开始的一条横向直线。

        对于第1辆车，如果它会与0号车相撞的话，它的曲线就是{0, v1}, {t1, v0}. 也就是在某一个时刻t之后，它的速度就变成了前车的速度v0。这个相撞时刻t1在此时并不难求。在图像上，1号车的曲线行程了两块bar（第二块bar是无限向右延申的）

        对于第2辆车，如果它会与1号车相撞的话，我们需要计算它具体的相撞时间t2。注意这个t2的时刻可能是在t1之前，那样的话，2号车的曲线就是{0,v2},{t2,v1},{t1,v0}；也有可能t2的时刻在t1之后，那么2号车的曲线局势{0,v2},{t2,v0}.

        所以对于第i辆车的曲线，它基本上是继承了第i-1辆车的曲线，区别有两处：1. 它的第一段横线开始于它的原始速度{0,vi}。 2. 第一段横线一致延伸到了与前车的相撞时刻ti。注意：ti之后的曲线完全与前车在ti之后的曲线相同。

        我们现在假设这个ti已知。从出发时刻到ti，第i号车行使的距离就是x = ti*vi。相同时间内第i-1号车行驶的距离y是可以从它的曲线里读出来的：就只要数一下ti时间内包含了几块bar以及它覆盖的面积（注意可能最后包含了某块bar的一部分）。
        
        如果两车相遇，那么一定要满足x - y = gap，即两车的初始间隔。于是，我们可以根据这个条件反推ti。

        举个例子。假设第i-1辆车的曲线是{0,v0},{t1,v1},{t2,v2},{t3,v3} .... 我们就挨个查看i号车与i-1号车相撞时间的时间ti是在{0,t1,t2,t3...}的那个区间里。即查看是否

        t1*vi >= gap + v0*(t1-0)
        如果不满足，说明在t1之前都没有追上，那么就查看

        t2*vi >= gap + v0*(t1-0) + v1*(t2-t1)
        如果还不满足，说明在t2之前都没有追上，那么就查看

        t3*vi >= gap + v0*(t1-0) + v1*(t2-t1) + v2*(t3-t2)
        假设满足了，那么说明碰撞时刻就在t2和t3之间。那么具体的时刻，就等于考察这段区间内的追及问题。在这个区间内，两辆车都是匀速运动，所以需要花费的追及时间是：

        dt = [ gap + v0*(t1-0) + v1*(t2-t1) - t2*vi ] / (vi - v2)
        也就是说在t2再过了dt之后，这两辆车相遇了，相撞之后速度都变成了v2（此时前车的速度）。于是我们就马上得到了第i号车的曲线：{0,vi},{t2+dt,v2},{t3,v3}... 这个曲线就是在第i-1辆车的曲线基础上，弹出若干个前端的区间，依次push_front两个新区间。

        时间复杂度：我们每处理一辆车，就修改部分的曲线区间。其实每一个区间其实对应的是一个撞车事件。因为总共只会有n个撞车事件，所以整体的时间复杂度就是 O(N). 这里我用了deque来方便对于前端区间的弹出、加入操作，但是本质上可以看出就等效于使用了一个栈。
    */

    vector<double> getCollisionTimes(vector<vector<int>>& cars) 
    {
        int n = cars.size();
        vector<double>rets(n);
        
        deque<array<double,2>>dq; // {t, v}
        dq.push_back({0, (double)cars.back()[1]});
        rets[n-1] = -1;
        
        
        for (int i=cars.size()-2; i>=0; i--)
        {            
            int dS = cars[i+1][0] - cars[i][0];
            double vv = cars[i][1];
            double total = 0;
            
            if (vv <= dq.back()[1])
            {
                dq.clear();
                dq.push_back({0, vv});
                rets[i] = -1;
                continue;
            }
            
            double t = dq.front()[0];
            double v = dq.front()[1];            
            dq.pop_front();
                        
            while (dq.size()>0)
            {                
                if (total + v*(dq.front()[0] - t) + dS >= vv*dq.front()[0])
                {
                    total += v*(dq.front()[0] - t);
                    t = dq.front()[0];
                    v = dq.front()[1];                    
                    dq.pop_front();
                }
                else
                    break;
            }            
            
            double dt = (dS - (t*vv - total)) *1.0 / (vv-v);
            
            dq.push_front({t+dt, v});
            dq.push_front({0, vv});
            
            rets[i] = t+dt;
        }
        
        return rets;
        
    }



    vector<double> doit_monotonic_stack(vector<vector<int>>& cars) {
        
        int n = cars.size();
        stack<int> st;
        vector<double> res(n, -1.0000);
        
        for (int i = n - 1; i >= 0; i--) {
            
            int p = cars[i][0], s = cars[i][1];
            
            while (!st.empty()) {
                int j = st.top();
                int lastp = cars[j][0], lastv = cars[j][1];
                
                if (s <= lastv || (lastp - p) * 1.0 / (s - lastv) >= res[j] && res[j] > 0)
                    st.pop();
                else
                    break;
            }
            
            
            if (!st.empty())
                res[i] = (cars[st.top()][0] - cars[i][0]) * 1.0 / (cars[i][1] - cars[st.top()][1]);
            
            st.push(i);   
        }
        
        
        return res;
    }

public:

    /*
        Intuition
        There is some similar sense from the problem of 853. Car Fleet,
        we care about the time information in front of each car.


        Explanation
        We care about the collision time of the cars in front us.
        We iteratre from the last to the first car,
        and we main a stack of car indices,
        where their collision time is strict decreasing.

        Imagine a,b,c on the road
        if the a catches b later than b catched c,
        then a won't catch b but b+c.


        Complexity
        Time O(n)
        Space O(n)

        More Good Stack Problems
        Here are some problems that impressed me.
        Good luck and have fun.

        1776. Car Fleet II
        1673. Find the Most Competitive Subsequence
        1671. Minimum Number of Removals to Make Mountain Array
        1475. Final Prices With a Special Discount in a Shop
        1425. Constrained Subsequence Sum
        1130. Minimum Cost Tree From Leaf Values
        907. Sum of Subarray Minimums
        901. Online Stock Span
        856. Score of Parentheses
        503. Next Greater Element II
        496. Next Greater Element I
        84. Largest Rectangle in Histogram
        42. Trapping Rain Water
    */
    vector<double> doit_(vector<vector<int>>& A) {
        int n = A.size();
        vector<int> stack;
        vector<double> res(n, -1);

        for (int i = n - 1; i >= 0; --i) {
            int p = A[i][0], s = A[i][1];
            while (!stack.empty()) {
                int j = stack.back(), p2 = A[j][0], s2 = A[j][1];
                // no possible to collide or collide earlier.
                if (s <= s2 || 1.0 * (p2 - p) / (s - s2) >= res[j] && res[j] > 0)
                    stack.pop_back();
                else
                    break;
            }
            if (!stack.empty())
                res[i] = 1.0 * (A[stack.back()][0] - p) / (s - A[stack.back()][1]);
            stack.push_back(i);
        }
        return res;
    }
};