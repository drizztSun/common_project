/*
1510. Stone Game IV

Alice and Bob take turns playing a game, with Alice starting first.

Initially, there are n stones in a pile.  On each player's turn, that player makes a move consisting of removing any non-zero square number of stones in the pile.

Also, if a player cannot make a move, he/she loses the game.

Given a positive integer n. Return True if and only if Alice wins the game otherwise return False, assuming both players play optimally.

 

Example 1:

Input: n = 1
Output: true
Explanation: Alice can remove 1 stone winning the game because Bob doesn't have any moves.
Example 2:

Input: n = 2
Output: false
Explanation: Alice can only remove 1 stone, after that Bob removes the last one winning the game (2 -> 1 -> 0).
Example 3:

Input: n = 4
Output: true
Explanation: n is already a perfect square, Alice can win with one move, removing 4 stones (4 -> 0).
Example 4:

Input: n = 7
Output: false
Explanation: Alice can't win the game if Bob plays optimally.
If Alice starts removing 4 stones, Bob will remove 1 stone then Alice should remove only 1 stone and finally Bob removes the last one (7 -> 3 -> 2 -> 1 -> 0). 
If Alice starts removing 1 stone, Bob will remove 4 stones then Alice only can remove 1 stone and finally Bob removes the last one (7 -> 6 -> 2 -> 1 -> 0).
Example 5:

Input: n = 17
Output: false
Explanation: Alice can't win the game if Bob plays optimally.
 

Constraints:

1 <= n <= 10^5

*/
#include <vector>
#include <functional>

using std::vector;

class StoneGameIV {

public:

    /*
        1510.Stone-Game-IV
        很显然的决策问题。假设dp[n]表示我方手头数字是n时能否胜利。那么遍历自己的决策（减去某个平方数），将剩下的数字（假设是m）转移给对手。一旦对手处理的数字m最终得到的结果是失败，那么说明我方肯定能赢。如果无论什么m，对手都能处理成功，那么说明我方肯定输。

        本题的递归和DP写法都很好写。
    */

    bool doit_dp_topdown(int n) 
    {
        vector<int> dp(n+1, -1);
        
        std::function<bool(int>) solve = [&](int n){

            if (dp[n]!=-1)
                return dp[n];

            for (int i=1; i*i<=n; i++)
            {
                if (solve(n-i*i) == 0)
                {
                    dp[n] = 1;
                    return true;
                }
            }
            dp[n] = 0;
            return false;
        };

        return solve(n);
    }
    
    bool doit_dp_bottomup(int n) {

        vector<bool> dp(n+1, false);

        for (int i = 1; i <= n; i++) {

            //  if there is any chance to make the opponent lose the game in the next round,
            //  then the current player will win.
            for (int j = 1; j*j < i+1; j++) {

                if (dp[i - j*j] == false) {
                    dp[i] = true;
                }
            }
        }
        
        return dp[n];
    }
};