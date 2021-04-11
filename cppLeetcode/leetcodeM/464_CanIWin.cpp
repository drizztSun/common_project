/*
464. Can I Win

In the "100 game" two players take turns adding, to a running total, any integer from 1 to 10. The player who first causes the running total to reach or exceed 100 wins.

What if we change the game so that players cannot re-use integers?

For example, two players might take turns drawing from a common pool of numbers from 1 to 15 without replacement until they reach a total >= 100.

Given two integers maxChoosableInteger and desiredTotal, return true if the first player to move can force a win, otherwise return false. Assume both players play optimally.

 

Example 1:

Input: maxChoosableInteger = 10, desiredTotal = 11
Output: false
Explanation:
No matter which integer the first player choose, the first player will lose.
The first player can choose an integer from 1 up to 10.
If the first player choose 1, the second player can only choose integers from 2 up to 10.
The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
Same with other integers chosen by the first player, the second player will always win.
Example 2:

Input: maxChoosableInteger = 10, desiredTotal = 0
Output: true
Example 3:

Input: maxChoosableInteger = 10, desiredTotal = 1
Output: true
 

Constraints:

1 <= maxChoosableInteger <= 20
0 <= desiredTotal <= 300


*/
#include <vector>
#include <functional>

using std::vector;

class CanIWin {

    /*  
        464.Can-I-Win
        本题最关键的一点是想到要用递归。如果列举自己的所有决策，对手都是mustWin==true，那么自己的mustWin就是false；反之，自己的某一个决策能够使得对手的mustWin==false，那么就是自己mustWin就是true。想到这一点的话，大致的代码如下：

        for (int i=1; i<=maxChoosableInteger; i++)
        {
            if (used[i]==1) continue;  // 跳过已经使用过的数字
            used[i]=1;
            if (DFS(maxChoosableInteger,desiredTotal-i)==false)  // 如果下一轮（注意是对手轮）是必输决策，那么说明本轮该决策必赢
            return true;
            used[i]=0;
        }
        return false; // 遍历了本轮所有的决策后都没有跳出，说明对方都有必赢决策，那么本轮对自己而言就是必输。
        但不幸的是，以上的代码会超时。原因是每轮的决策都是近乎随机的，N轮之后会造成大量重复的决策。比如对于第三轮（我方）而言：第一轮（我方）取1，第二轮（对方）取2；这个完全等效于第一轮（我方）取2、第二轮（对方）取1。如果对于前者DFS完毕之后，其实就不需要再对后者进行相同的DFS了。所以很明显，需要利用到记忆化搜索，也就是把之前DFS得到的一些中间结果存储下来。

        本题的“中间结果”是指：在已经取走一些数字的情况下，自己做决策是会必输还是有办法包赢。所以我们需要一个Hash表，key应该是已经取数的状态，val就是bool型表明对于这种状态本方是赢还是输。怎么将已经取了哪些数的“状态”作为一个key呢？考虑到最多只有20个数，用一个20位的二进制数字就可以表示所有取数状态了。

        int status=0;
        for (int i=1; i<=maxChoosableInteger; i++)
        {
        if (((status>>i)&1)==1) continue; // 跳过已经使用过的数字
        if (DFS(maxChoosableInteger,desiredTotal-i, status|(1<<i))==false) // 如果下一轮（注意是对手轮）是必输决策，那么说明本轮该决策必赢
        {
            Map[status]=true;
            return true;
        }    
        }
        Map[status]=false; // 遍历了本轮所有的决策后都没有跳出，说明对方都有必赢决策，那么本轮对自己而言就是必输。需要记录下来，免除后续的重复搜索。
        return false; 
        上面这种每一轮互相易手的游戏规则，求最终必胜或必输策略的问题，常常被称为minMax问题。基本思路就是：当前状态下，列举自己的每一种策略，如果对方都有必胜的应手，那么本方的这个状态就是必输。如果自己有一手策略，会导致对方必输，那么本方的这个状态就是必赢。
    */
    int visited[1<<21];
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) 
    {
        int totalSum = (1+maxChoosableInteger)*maxChoosableInteger/2;
        if (totalSum < desiredTotal) return false;
        return dfs(0, 0, maxChoosableInteger, desiredTotal);
    }

    bool dfs(int state, int sum, int maxChoosableInteger, int desiredTotal)
    {
        if (visited[state]==2)
            return true;
        if (visited[state]==1)
            return false;

        for (int i=1; i<=maxChoosableInteger; i++)
        {
            if ((state>>i)&1) continue;
            if (sum+i >= desiredTotal) return true;
            
            if (dfs(state+(1<<i), sum+i, maxChoosableInteger, desiredTotal)==false)
            {
                visited[state] = 2;
                return true;
            }                
        }
        visited[state] = 1;
        return false;
    }

public:
    
    bool doit_dfs(int maxChoosableInteger, int desiredTotal) {

        vector<int> status(1 << maxChoosableInteger, -1);

        std::function<bool(int, int)> dfs = [&](int cur, int sums) ->bool {

            if (status[cur] != -1) return static_cast<bool>(status[cur]);

            for (int i = 1; i <= maxChoosableInteger; i++) {

                if ((cur >> i) & 1) continue;

                if (sums + i >= desiredTotal) return true;

                if (!dfs(cur | (1 << i), sums + i)) {
                    status[cur] = 1;
                    return true;
                }
            }
            status[cur] = 0;
            return false;
        };

        return dfs(0, 0);
    }
};