/*
1535. Find the Winner of an Array Game


Given an integer array arr of distinct integers and an integer k.

A game will be played between the first two elements of the array (i.e. arr[0] and arr[1]). 
In each round of the game, we compare arr[0] with arr[1], the larger integer wins and remains at position 0 and the smaller integer moves to the end of the array. 
The game ends when an integer wins k consecutive rounds.

Return the integer which will win the game.

It is guaranteed that there will be a winner of the game.

 

Example 1:

Input: arr = [2,1,3,5,4,6,7], k = 2
Output: 5
Explanation: Let's see the rounds of the game:
Round |       arr       | winner | win_count
  1   | [2,1,3,5,4,6,7] | 2      | 1
  2   | [2,3,5,4,6,7,1] | 3      | 1
  3   | [3,5,4,6,7,1,2] | 5      | 1
  4   | [5,4,6,7,1,2,3] | 5      | 2
So we can see that 4 rounds will be played and 5 is the winner because it wins 2 consecutive games.
Example 2:

Input: arr = [3,2,1], k = 10
Output: 3
Explanation: 3 will win the first 10 rounds consecutively.
Example 3:

Input: arr = [1,9,8,2,3,7,6,4,5], k = 7
Output: 9
Example 4:

Input: arr = [1,11,22,33,44,55,66,77,88,99], k = 1000000000
Output: 99
 

Constraints:

2 <= arr.length <= 10^5
1 <= arr[i] <= 10^6
arr contains distinct integers.
1 <= k <= 10^9

*/

#include <vector>

using std::vector;


class WinnerOfArrayGame {

    /*
        1535.Find-the-Winner-of-an-Array-Game
        本题模拟一个“打擂台”的机制。对于一个数A，如果它连续大于之后的K个数，那么它是winner。

        如果数A在成为winner之前被数B压过，那么数A（以及被数A击败的数）是否要append到arr末尾来继续参与这场模拟呢？不需要。事实上没必要在考察完n个数之后继续模拟来找winner。
        因为我们在第一轮遍历这n个数的时候，必然会遇到一个全局的最大值Max，它之后的所有数（以及包括额外append到数组末尾的数）都不可能击败它。所以如果我们考察完n个数之后还没有确定winner，那么手头的最大值（就是全局最大值）就一定是winner，因为它一定会击败所有元素。

        因此，我们只需要从头开始，模拟类似“打擂台”的机制，只要某个数连胜K场，就是winner。否则考察完n个数，手头的最大值（就是全局最大值）就是winner。

        另外，如果K大于n的话，说明winner要击败所有元素（好几圈），那么同样说明winner一定就是全局最大值。
    
    */
    int doit_(vector<int>& arr, int k) 
    {
        int curMax = arr[0];
        int times = 0;
        for (int i=1; i<arr.size(); i++)
        {
            if (arr[i]>curMax)
            {
                curMax = arr[i];
                times = 1;
            }
            else
            {
                times+=1;
            }
            if (times == k) return curMax;
        }
        return curMax;
    }

public:
    
    int doit_greedy(vector<int>& arr, int k) {
        
        int cnt = 0, last = 0;
        
        for (int i = 1; i < arr.size(); i++) {
            
            if (arr[i] > arr[last]) {
                cnt = 1;
                last = i;
            } else {
                cnt++;
            }
            
            if (cnt == k) break;
        }
        
        return arr[last];
    }
};
