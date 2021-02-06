"""
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


"""


class StoneGameIV:

    """
    # Platform: leetcode.com
    # No. 1510 Stone Game IV (Buttom up with DP List implement)
    # Link: https://leetcode.com/problems/stone-game-iv/
    # Difficulty: Medium
    # Dev: Chumicat
    # Date: 2020/10/26
    # Submission:
    # (Time, Space) Complexity : O(n), O(n)
    """
    def doit_bottomup_dp(self, n: int) -> bool:
        from math import floor, sqrt

        # i stones, if 0, Alice will failed, she is facing 0
        sol_list = [False] * (n + 1)

        sqr_list = [i * i for i in range(1, floor(sqrt(n)) + 1)]

        for i in range(n):
            if sol_list[i]:
                continue
            for sqr in sqr_list:
                if i + sqr < n:
                    # Alice can take sqr, and Bob will face 0, then Alice is gonna win
                    sol_list[i + sqr] = True
                elif i + sqr == n:
                    # we can accelerate by reaching to n, first.
                    return True
                else:
                    break
        return False


    """
    Overview
    You probably can guess from the problem title, this is the fourth problem in the series of Stone Game problems.
    Those problems are similar, but have considerable differences, making their solutions quite different. It's highly recommended to finish them all.

    Here, two approaches are introduced: DFS with memorization and DP approach.
    """

    """
    Approach 1: DFS with memorization
    Intuition
    
    First, let's analyze the problem.
    
    According to Zermelo's_theorem, given n stones, either Alice has a must-win strategy, or Bob has one. Therefore, for Alice, the current state is either "must-win" or "must-lose". But how to determine which one it is?
    
    For convenience, in the following context, "the current player" refers to the player now removing the stones, and "state i" refers to when there is i stones remaining.
    
    Now the problem asks whether the current player will win in state n.
    
    If we can go to a known state where Bob must lose, then we know Alice must win in the current state. All Alice has to do is to move the corresponding number of stones to go to that state. Therefore we need to find out which state Bob must lose.
    
    Note that after going to the next state, Bob becomes the player removing the stones, which is the position of Alice in the current state. Therefore, to find out whether Bob will lose in the next state, we just need to check whether our function gives False for remaining stones.
    
    Algorithm
    
    Let function dfs(remain) represents whether the current player must win with remain stones remaining.
    
    To find out the result of dfs(n), we need to iterate k from 0 to check whether there exits dfs(remain - k*k)==False. To prevent redundant calculate, use a map to store the result of dfs function.
    
    Don't forget the base case dfs(0)==False and dfs(1)==True.
    
    Note: After reading the Algorithm part, it is recommended to try to write the code on your own before reading the solution code.
    
    There some tricks that we used in the code above.

    In the Python code, we use @lru_cache instead of a map to store the result of dfs. It's a useful grammar sugar in Python.
    
    In the Java code, we don't have things like @lru_cache in Python, so here we use a simple HashMap. However, we can still use some tricks, if you want -- using an array instead of a map: we can use 0 to mark the unvisited nodes, use 1 to mark the true results, and use 2 to mark the false results. Also, we can just use an array of bytes, which uses less memory than an array of ints.
    
    Note that the speed would be a little faster if you iterate i from sqrt_root to 0 due to the data characteristics.
    
    Complexity Analysis
    
    Assume NN is the length of arr.
    
    Time complexity: O(N*sqrt{N}) since we spend at most for each dfs call, and there are O(N) dfs calls in total.
    
    Space complexity: O(N) since we need spaces of O(N) to store the result of dfs.
    """

    def doit_dfs_dp_topdown(self, n: int) -> bool:
        from functools import lru_cache

        @lru_cache(maxsize=None)
        def dfs(remain):
            if remain == 0:
                return False

            for i in range(1, int(remain**0.5)+1):
                # if there is any chance to make the opponent lose the game in the next round,
                #  then the current player will win.
                if not dfs(remain - i*i):
                    return True

            return False

        return dfs(n)

    """
    Approach 2: DP
    Intuition
    
    DFS with memorization is very similar to dp. We can also use dp to solve this problem.
    
    We can just use a single dp[i] array to store whether the player now removing stones wins with i stones remaining.
    
    Algorithm
    
    Let dp[i] represents the result of the game with i stones. dp[i]==True means the current player must win, and dp[i]==False means the current player must lose, when both players play optimally.
    
    The next step is to find out how to calculate dp[i].
    
    We can iterate all possible movements, and check if we can move to a False state. If we can, then we found a must-win strategy, otherwise, we must lose since the opponent has a must-win strategy in this case.
    
    More clearly, we can iterate k from 0 and check if there exists dp[i - k*k]==False. Of course, i - k*k >= 0.
    
    Finally, we only need to return dp[n].

    Complexity Analysis
    
    Assume NN is the length of arr.
    
    Time complexity: \mathcal{O}(N\sqrt{N})O(N 
    N
    ​	
     ) since we iterate over the dp array and spend \mathcal{O}(\sqrt{N})O( 
    N
    ​	
     ) at most on each element.
    
    Space complexity: \mathcal{O}(N)O(N) since we need a dp array.
    
    """
    def doit_dp_bottomup(self, n: int) -> bool:
        dp = [False]*(n+1)
        for i in range(1, n+1):
            for k in range(1, int(i**0.5)+1):
                if dp[i-k*k] == False:
                    dp[i] = True
                    break
        return dp[n]

    def doit_dp(self, n: int) -> bool:
        dp = [False]*(n+1)
        for i in range(n+1):
            if dp[i]:
                continue
            for k in range(1, int(n**0.5)+1):
                if i+k*k <= n:
                    dp[i+k*k] = True
                else:
                    break
        return dp[n]


