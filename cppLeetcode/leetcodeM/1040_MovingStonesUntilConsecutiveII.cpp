/*
 # 1040. Moving Stones Until Consecutive II


 # On an infinite number line, the position of the i-th stone is given by stones[i].
 # Call a stone an endpoint stone if it has the smallest or largest position.

 # Each turn, you pick up an endpoint stone and move it to an unoccupied position so that it is no longer an endpoint stone.

 # In particular, if the stones are at say, stones = [1, 2, 5], you cannot move the endpoint stone at position 5,
 # since moving it to any position(such as 0, or 3) will still keep that stone as an endpoint stone.

 # The game ends when you cannot make any more moves, ie. the stones are in consecutive positions.

 # When the game ends, what is the minimum and maximum number of moves that you could have made?
 # Return the answer as an length 2 array: answer = [minimum_moves, maximum_moves]


 # Example 1:

 # Input: [7, 4, 9]
 # Output: [1, 2]
 # Explanation:
 # We can move 4 -> 8 for one move to finish the game.
 # Or, we can move 9 -> 5, 4 -> 6 for two moves to finish the game.
 # Example 2:

 # Input: [6, 5, 4, 3, 10]
 # Output: [2, 3]
 # We can move 3 -> 8 then 10 -> 7 to finish the game.
 # Or, we can move 3 -> 7, 4 -> 8, 5 -> 9 to finish the game.
 # Notice we cannot move 10 -> 2 to finish the game, because that would be an illegal move.
 # Example 3:

 # Input: [100, 101, 104, 102, 103]
 # Output: [0, 0]

 */

#include <vector>
#include <algorithm>

using std::vector;

class NumMovesStonesII {

    /*
        1040.Moving-Stones-Until-Consecutive-II
        此题非常考验分析推理的能力，和编程技巧本身的关系倒是不大。

        max move
        要使得操作数尽可能地多，我们需要将end point的石头填充到下一个最靠外的空缺（但这个空缺本身不能是end point)。这样，每动一步只消灭一个最靠外的空缺，就能够使得这个move足够缓慢。举个例子：

        OOXXXOO
        1234567
        我们的方案就是将7移动到5，消灭一个最靠外的空缺；然后将6移动到4，再消灭一个此时最靠外的空缺；然后将5移动到3，再消灭一个此时最靠外的空缺...以此类推，每移动一步，我们就消灭一个空缺，因此总移动的步数，就是被初始状态的石头所“内含”的空缺个数。

        但是这个有一个特殊情况

        OOXXXOXO
        12345678
        此时第一步不允许将8移动到7.根据要求8只能移动到5，然后转换为

        OOXXOO
        123456
        此时我们就可以放心地用上运用之前的规律：需要移动的步数，就是此时"内含“的空缺数2。所以结论就是stones[n-2]-stones[0]+1-(n-1)

        当然，上面的公式考虑的是移动右边的石头往左边填充。反过来也可以考虑移动左边的石头往右边填充：stones[n-1]-stones[1]+1-(n-1)

        最终max move是两者取最大值。

        min move
        min move的基本思想是：我们尽量找初始状态下分布就相对集中靠拢的区域，尝试将其他的石头直接搬往这个区域的两边。举个例子：

        OOXOOXXXO
        123456789
        我们发现1-5这个区间里面就有四个石头，显然直接将9搬到3就可以将区间1-5填满。所以这就提示我们寻找一个长度为n的sliding window，里面的石头越多越有利。理想情况下，我们只需要搬运n-(这个长度为n的窗口里的石头数)

        但是同样有一个特殊情况

        OOOOXXXXO
        123456789
        这个时候，虽然1-5这个区间里面有四块石头，是最理想的聚集区，但是，我们无法直接将9移动到5.这是因为这个“理想聚集区”的右端点5这个位置，目前是空缺，并且窗口的右侧只有一个石头。此时我们只有多操作一步，将1移动到6，形成

        OOOXOXXO
        123456789
        的局面，使得理想聚集区变成了[2-6]，然后再使用上面的规则:搬运n-(这个长度为n的窗口里的石头数)次,将9移动到5即可。事实上，这种特殊情况只有在n-1个石头连续排放的时候才会出现，因此操作数就是2。

        所以，处理min move的逻辑是：

        for i =0; i<n; i++   // 大框架是遍历窗口的左端的位置
        {
        找到j，使得stones[j]-stones[i]+1>=n.
        if stones[j]-stones[i]+1==n
            说明从stones[i]到stones[j]这个窗口正好有n个位置，并且窗口的最右端是块石头，
            所以我们只要搬运```n-(这个长度为n的窗口里的石头数)```次，即```n-(j-i+1)```
        else 
            说明从stones[i]开始的长度为n的窗口，最右端不是石头
            if (j-i==n-1) 
            说明是分析到的特殊情况，n-1个石头连排，答案返回2
            else
            说明是一般的情况，所以我们只要搬运```n-(这个长度为n的窗口里的石头数)```次，即```n-(j-i)```
        }
    */
    vector<int> numMovesStonesII(vector<int>& stones) 
    {
        sort(stones.begin(),stones.end());
        int n = stones.size();
        
        int a = (stones[n-2]-stones[0]+1)-(n-1);
        int b = (stones[n-1]-stones[1]+1)-(n-1);
        int y = std::max(a,b);
        
        int j = 0;
        int x = INT_MAX;
        for (int i=0; i<n; i++)
        {
            while (j<n && stones[j]-stones[i]+1<n)
                j++;
            if (j==n) break;
            
            int gap;
            if (stones[j]-stones[i]+1==n)
                gap = n-(j-i+1);
            else if (j-i==n-1)
                gap = 2;
            else
                gap = n-(j-i);
            
            x = std::min(x,gap);
        }
        
        return {x,y};
    }

public:
    
    
    // Upper bound:
    // 1, move the first stone A[0] to A[n-1]-n+1
    // the total number between new left bound and A[1] is the steps to take
    // A[n-1]-n+1-A[1]+1
    // 2, or move the last stone A[n-1] to A[0]+n-1
    // the total number between new right bound and A[n-2] is the steps to take
    // A[n-2]-(A[0]+n-1)+1
    //
    // Lower bound:
    // Sliding window size of len(stones), find vacancy in the current window, and the number of vacancy is the number
    // of steps
    // Edge Case: A[j]-A[i]==n-2 && j-i+1==n-1
    // e.g. 1,2,3,4,10: we need to move 1 to 6, then 10 to 5
    
    vector<int> doit_slidingwindow(vector<int>&& stones) {

        std::sort(stones.begin(), stones.end());
        int N = stones.size();
        
        int maxv = std::max(stones[N-2] - stones[0] - (N-2), stones[N-1] - stones[1] - (N-2));
        
        int i = 0;
        int minv = maxv;
        
        for (size_t j = 0; j < stones.size(); j++) {
            
            while (stones[j] - stones[i] >= N) {
                i++;
            }
            
            if (stones[j] - stones[i] == N - 2 && j - i == N - 2) {
                minv = std::min(minv, 2);
            } else {
                int cur = N - (j - i + 1);
                minv = std::min(minv, cur);
            }
        }
        
        return {minv, maxv};
    }
    
    vector<int> doit(vector<int>&& stones) {
        
        std::sort(stones.begin(), stones.end());
        int total = 0;
        size_t N = stones.size();
        
        for (size_t i = 0; i < stones.size()-1; i++)
            total += stones[i+1] - stones[i] - 1;
        
        int maxv = total - std::min(stones[1] - stones[0] - 1, stones[N-1] - stones[N-2] - 1);

        int i = 0;
        for (size_t j = 0; j < stones.size(); j++) {
            if (stones[j] - stones[i] >= N)
                i++;
        }
        
        // (1) if there is one space in the middle, total is N + 1, i == 1 and stones[n-1] - stones[0] == N
        // (2) based on (1), if it is not N, it means there are two space exists. They are in between 0 - 1, or is between N - 2 - N-1.
        // (3) You have to first move left or right one, to the middle right and left one, then move next
        int minv = (i == 1 && stones[N-1] - stones[0] != N && (stones[N-2] - stones[0] == N - 2 || stones[N-1] - stones[1] == N - 2)) ? 2 : i;

        return {minv, maxv};
    }  
};

/*
1033. Moving Stones Until Consecutive

Three stones are on a number line at positions a, b, and c.

Each turn, you pick up a stone at an endpoint (ie., either the lowest or highest position stone), and move it to an unoccupied position between those endpoints.  
Formally, let's say the stones are currently at positions x, y, z with x < y < z.  You pick up the stone at either position x or position z, and move that stone to an integer position k, with x < k < z and k != y.

The game ends when you cannot make any more moves, ie. the stones are in consecutive positions.

When the game ends, what is the minimum and maximum number of moves that you could have made?  Return the answer as an length 2 array: answer = [minimum_moves, maximum_moves]

 

Example 1:

Input: a = 1, b = 2, c = 5
Output: [1,2]
Explanation: Move the stone from 5 to 3, or move the stone from 5 to 4 to 3.
Example 2:

Input: a = 4, b = 3, c = 2
Output: [0,0]
Explanation: We cannot make any moves.
Example 3:

Input: a = 3, b = 5, c = 1
Output: [1,2]
Explanation: Move the stone from 1 to 4; or move the stone from 1 to 2 to 4.
 

Note:

1 <= a <= 100
1 <= b <= 100
1 <= c <= 100
a != b, b != c, c != a
*/


class NumMovesStonesI {

public:

    vector<int> doit_greedy(int a, int b, int c) {
        vector<int> pos{a, b, c};
        std::sort(begin(pos), end(pos));
        int ab = pos[1] - pos[0] - 1, cb = pos[2] - pos[1] - 1;
        int maxv = ab + cb;

        //OOO
        if (ab == 0 && cb == 0) return {0, 0};
        //OOXXXO or OXXOO
        if (ab == 0 || cb == 0) return {1, maxv};
        
        //OXOXXXXO or OXXXXXOXO
        if (ab == 1 || cb == 1) return {1, maxv};
        
        // XXXOXXXXOXXXXOXX
        return {2, maxv};
    }
};