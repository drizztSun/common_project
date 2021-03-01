/*
1774. Closest Dessert Cost

You would like to make dessert and are preparing to buy the ingredients. You have n ice cream base flavors and m types of toppings to choose from. You must follow these rules when making your dessert:

There must be exactly one ice cream base.
You can add one or more types of topping or have no toppings at all.
There are at most two of each type of topping.
You are given three inputs:

baseCosts, an integer array of length n, where each baseCosts[i] represents the price of the ith ice cream base flavor.
toppingCosts, an integer array of length m, where each toppingCosts[i] is the price of one of the ith topping.
target, an integer representing your target price for dessert.
You want to make a dessert with a total cost as close to target as possible.

Return the closest possible cost of the dessert to target. If there are multiple, return the lower one.

 

Example 1:

Input: baseCosts = [1,7], toppingCosts = [3,4], target = 10
Output: 10
Explanation: Consider the following combination (all 0-indexed):
- Choose base 1: cost 7
- Take 1 of topping 0: cost 1 x 3 = 3
- Take 0 of topping 1: cost 0 x 4 = 0
Total: 7 + 3 + 0 = 10.
Example 2:

Input: baseCosts = [2,3], toppingCosts = [4,5,100], target = 18
Output: 17
Explanation: Consider the following combination (all 0-indexed):
- Choose base 1: cost 3
- Take 1 of topping 0: cost 1 x 4 = 4
- Take 2 of topping 1: cost 2 x 5 = 10
- Take 0 of topping 2: cost 0 x 100 = 0
Total: 3 + 4 + 10 + 0 = 17. You cannot make a dessert with a total cost of 18.
Example 3:

Input: baseCosts = [3,10], toppingCosts = [2,5], target = 9
Output: 8
Explanation: It is possible to make desserts with cost 8 and 10. Return 8 as it is the lower cost.
Example 4:

Input: baseCosts = [10], toppingCosts = [1], target = 1
Output: 10
Explanation: Notice that you don't have to have any toppings, but you must have exactly one base.
 

Constraints:

n == baseCosts.length
m == toppingCosts.length
1 <= n, m <= 10
1 <= baseCosts[i], toppingCosts[i] <= 10^4
1 <= target <= 10^4

*/
#include <vector>
#include <set>

using std::set;
using std::vector;

class ClosestCost {

    /*      
        1774.Closest-Dessert-Cost
        本题需要暴力枚举所有toppings的选配方案。这样的枚举对每种topping都在0，1，2中选择，并没有任何优化、剪支的空间，所以相比于DFS的递归做法（需要递归十次），用bit mask来说更为方便。

        我们注意要toppings只有十种，如果用每两个bit位来表示一种topping的方案（00，01，10，11），那么总共需要20个bit位。
        注意到01和10都可以用来表示该topping选择一份。尽管有些状态的数目上有些浪费，但即使如此，考虑2^20是1e6量级，这样的暴力是可以接收的。      
    */

public:
    
    int doit_bruteforce(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        
        int cost;
        int diff = INT_MAX;
        int m = toppingCosts.size();

        for (int baes: baseCosts) {

            for (int status = 0; status < (1 << (2*m)); status++) {

                int sum = base;
                for (int i = 0; i < m; i++) {

                    if ((status >> (2*i)) & 1 == 1)
                        sum += toppingCosts[i];

                    if ((status >> (2*i+1)) & 1 == 1)
                        sum += toppingCosts[i];
                } 

                if (abs(sum - target) < diff || abs(sum - target) == diff && sum < cost) {
                    diff = abs(sum - target);
                    cost = sum; 
                }
            }
        }

        return cost;
    }
    
    
    int doit_dp(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        bool table[20010] = {false};
        int ans = -999999;
        for (int base : baseCosts) {
            table[base] = true;
        }
        
        for (int cost : toppingCosts) {
            for (int k = 1; k <= 2; k++) {
                for (int v = 20000; v >= 0; v--) {
                    if (v - cost >= 0 && table[v - cost] == true) {
                        table[v] = true;
                    }
                }
            }
        }
        
        for (int i = 1; i <= 20001; i++) {
            if (table[i] == true && abs(i - target) < abs(ans - target)) {
                ans = i;
            }
        }
        
        return ans;
    }


    int doit_best(vector<int>& baseCosts, vector<int>& toppingCosts, int T) {

        // init sorted buff or cost, remove duplicate ones
        set<int> cost(baseCosts.begin(), baseCosts.end());

        // copy a next for using
        set<int> next = cost;

        int bst = baseCosts[0];
        int bstD = abs(bst - T);
        
        for (int c : baseCosts) {
            // list all base ice cream, and get a candidate closest value.
            if (abs(c - T) < bstD || (abs(c-T) == bstD && c < bst)) {
                bst = c;
                bstD = abs(bst - T);
            }
        }
        
        for(int t : toppingCosts) {
            // list all possible candidate values, all base and new base+topping less then current bstD
            for (int it : cost) {
                for (int c = it + t; c <= it + 2 * t; c += t) {
                    // if c - T < bstD, it could be candidates.
                    // if c < T, it can put more topppings in the future. if c > T and c-T < bstD, it could be also.
                    // any item, its c > T + bstD, would be considers. 
                    if (c < T + bstD) next.insert(c);

                    // To check if it is new value.
                    if (abs(c - T) < bstD || (abs(c-T) == bstD && c < bst)) {
                        bst = c;
                        bstD = abs(bst - T);
                    }
                }
            }
            cost = next;
        }
        return bst;       
    }
};