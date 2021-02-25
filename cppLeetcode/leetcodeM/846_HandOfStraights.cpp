/*
846. Hand of Straights

Alice has a hand of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size W, and consists of W consecutive cards.

Return true if and only if she can.

Note: This question is the same as 1296: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/

 

Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]
Example 2:

Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.

 

Constraints:

1 <= hand.length <= 10000
0 <= hand[i] <= 10^9
1 <= W <= hand.length
*/
#include <vector>
#include <map>
#include <queue>

using std::queue;
using std::map;
using std::vector;


class IsNStraightHand {

public:


    bool doit_hashtable(vector<int>& hand, int W) {
        
        map<int, int> mp;
        for (auto c : hand) mp[c]++;
        
        for (auto c : mp) {
            
            if (c.second > 0)
                for (int i = 0; i < W; i++) {
                    if ((mp[c.first+i] -= c.second) < 0) return false;
                }
        }   
        return true;
    }

    /*
        Solution 1
        Count number of different cards to a map c
        Loop from the smallest card number.
        Everytime we meet a new card i, we cut off i - i + W - 1 from the counter.

        Complexity:
        Time O(MlogM + MW), where M is the number of different cards.
    */

    bool doit_heap(vector<int>& hand, int W) {
        map<int, int> c;
        for (int i : hand) c[i]++;
        
        for (auto it : c)
            if (c[it.first] > 0)
                for (int i = W - 1; i >= 0; --i)
                    if ((c[it.first + i] -= c[it.first]) < 0)
                        return false;
        return true;
    }

    /*
        Follow Up
        We just got lucky AC solution. Because W <= 10000.
        What if W is huge, should we cut off card on by one?


        Solution 2:
        Count number of different cards to a map c
        Cur represent current open straight groups.
        In a deque start, we record the number of opened a straight group.
        Loop from the smallest card number.
        For example, hand = [1,2,3,2,3,4], W = 3
        We meet one 1:
        opened = 0, we open a new straight groups starting at 1, push (1,1) to start.
        We meet two 2:
        opened = 1, we need open another straight groups starting at 1, push (2,1) to start.
        We meet two 3:
        opened = 2, it match current opened groups.
        We open one group at 1, now we close it. opened = opened - 1 = 1
        We meet one 4:
        opened = 1, it match current opened groups.
        We open one group at 2, now we close it. opened = opened - 1 = 0

        return if no more open groups.

        Complexity
        O(MlogM + N), where M is the number of different cards.
        Because I count and sort cards.
        In Cpp and Java it's O(NlogM), which can also be improved.

    */    

    bool doit_hashtable(vector<int> hand, int W) {
        map<int, int> c;
        for (int i : hand) c[i]++;
        queue<int> start;
        int last_checked = -1, opened = 0;
        for (auto it : c) {
            int i = it.first;
            if (opened > 0 && i > last_checked + 1 || opened > c[i]) return false;
            start.push(c[i] - opened);
            last_checked = i, opened = c[i];
            if (start.size() == W) {
                opened -= start.front();
                start.pop();
            }
        }
        return opened == 0;
    }
};