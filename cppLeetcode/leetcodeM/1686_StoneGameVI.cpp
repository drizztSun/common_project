/*
 
 1686. Stone Game VI
 
 Alice and Bob take turns playing a game, with Alice starting first.

 There are n stones in a pile. On each player's turn, they can remove a stone from the pile and receive points based on the stone's value. Alice and Bob may value the stones differently.

 You are given two integer arrays of length n, aliceValues and bobValues. Each aliceValues[i] and bobValues[i] represents how Alice and Bob, respectively, value the ith stone.

 The winner is the person with the most points after all the stones are chosen. If both players have the same amount of points, the game results in a draw. Both players will play optimally.

 Determine the result of the game, and:

 If Alice wins, return 1.
 If Bob wins, return -1.
 If the game results in a draw, return 0.
  

 Example 1:

 Input: aliceValues = [1,3], bobValues = [2,1]
 Output: 1
 Explanation:
 If Alice takes stone 1 (0-indexed) first, Alice will receive 3 points.
 Bob can only choose stone 0, and will only receive 2 points.
 Alice wins.
 Example 2:

 Input: aliceValues = [1,2], bobValues = [3,1]
 Output: 0
 Explanation:
 If Alice takes stone 0, and Bob takes stone 1, they will both have 1 point.
 Draw.
 Example 3:

 Input: aliceValues = [2,4,3], bobValues = [1,6,7]
 Output: -1
 Explanation:
 Regardless of how Alice plays, Bob will be able to have more points than Alice.
 For example, if Alice takes stone 1, Bob can take stone 2, and Alice takes stone 0, Alice will have 6 points to Bob's 7.
 Bob wins.
  

 Constraints:

 n == aliceValues.length == bobValues.length
 1 <= n <= 105
 1 <= aliceValues[i], bobValues[i] <= 100
 
 
 
 
 */
#include <vector>
#include <algorithm>

using std::vector;


class StoneGameVI {
    
public:


    /*
        1686.Stone-Game-VI
        对于Alice而言，什么才是最优的决策吗？是优先选择自己能得到的最大值吗？并不是，通过这个例子就可以看出来：

        Alice: 1 2
        Bob:   3 1
        如果Alice优先选择第二个元素的话，那么Bob选择第一个元素反而会有更高的总分。于是我们显然发现，对于Alice而言，每一步的决策不仅要使自己的得分高，而且需要使对手的得分低。
        对于Alice而言，如果选择了第二个元素，那么Alice得了2分，Bob失去了一个得1分的机会，这一反一正差距是3分。同理，对于Bob而言，如果选择了第一个元素，那么自己得了3分，Alice失去了一个得1分的机会，这一反一正就是4分。

        所以，不管对哪个选手而言，一个元素的价值其实体现在了这个一反一正上。即使我自己得的分少，如果能让你失去了得高分的机会，也是一个成功的策略。

        所以本题的算法很简单，将所有元素按照AliceValues[i]+BobValues[i]的大下排列。然后Alice和Bob轮流选取，对它们而言就是最优的决策。
    */
    int doit_sort(vector<int>& aliceValues, vector<int>& bobValues) 
    {
        int n = aliceValues.size();
        vector<std::pair<int,int>> tmp(n);
        for (int i=0; i<n; i++)
        {
            tmp[i] = {aliceValues[i]+bobValues[i],i};
        }
        sort(tmp.begin(), tmp.end());
        reverse(tmp.begin(), tmp.end());
               
        int x = 0, y = 0;
        for (int i=0; i<n; i++)
        {
            if (i%2==0)
                x += aliceValues[tmp[i].second];                                
            else            
                y += bobValues[tmp[i].second];            
        }
        
        if (x>y)
            return 1;
        else if (x==y)
            return 0;
        else
            return -1;
        
    }
    
    int doit_sort_seach(vector<int>& aliceValues, vector<int>& bobValues) {
        
        vector<std::pair<int, int>> ps;
        
        for (int i = 0; i < aliceValues.size(); i++) {
            ps.push_back({aliceValues[i] + bobValues[i], i});
        }
        
        std::sort(begin(ps), end(ps), [](auto& a, auto& b) {
            return a.first > b.first;
        });
        
        int A = 0, B = 0;
        for (int i = 0; i < ps.size(); i++) {
            if (i % 2 == 0) {
                A += aliceValues[ps[i].second];
            } else {
                B += bobValues[ps[i].second];
            }
        }
        
        if (A == B) return 0;
        
        return A > B ? 1 : -1;
    }
};
