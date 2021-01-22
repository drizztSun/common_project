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


void test_1040_moving_stones_until_consecutive() {
    
    auto res = NumMovesStonesII().doit1(vector<int>{6, 5, 4, 3, 10});
    
    auto res1 = NumMovesStonesII().doit(vector<int>{7, 4, 9});
    
    auto res2 = NumMovesStonesII().doit(vector<int>{6, 5, 4, 3, 10});
    
    return;
}
