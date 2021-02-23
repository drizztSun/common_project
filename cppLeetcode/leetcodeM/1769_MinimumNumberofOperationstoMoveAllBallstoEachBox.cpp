/*
1769. Minimum Number of Operations to Move All Balls to Each Box

You have n boxes. You are given a binary string boxes of length n, where boxes[i] is '0' if the ith box is empty, and '1' if it contains one ball.

In one operation, you can move one ball from a box to an adjacent box. Box i is adjacent to box j if abs(i - j) == 1. Note that after doing so, there may be more than one ball in some boxes.

Return an array answer of size n, where answer[i] is the minimum number of operations needed to move all the balls to the ith box.

Each answer[i] is calculated considering the initial state of the boxes.

 

Example 1:

Input: boxes = "110"
Output: [1,1,3]
Explanation: The answer for each box is as follows:
1) First box: you will have to move one ball from the second box to the first box in one operation.
2) Second box: you will have to move one ball from the first box to the second box in one operation.
3) Third box: you will have to move one ball from the first box to the third box in two operations, and move one ball from the second box to the third box in one operation.
Example 2:

Input: boxes = "001011"
Output: [11,8,5,4,3,4]
 

Constraints:

n == boxes.length
1 <= n <= 200

boxes[i] is either '0' or '1'.

*/
#include <vector>
#include <string>

using std::vector;
using std::string;

class MinOperations {

public:

    vector<int> doit_search(string boxes) {
        
        int n = boxes.size();
        vector<int> left(n);
        int total = 0;
        
        for (int i = 0; i < boxes.size(); i++) {
            left[i] = total + (i > 0 ? left[i-1] : 0);
            total += boxes[i] == '1';
        }
        
        vector<int> right(n);
        total = 0;
        
        for (int i = boxes.size()-1; i >= 0; i--) {
            right[i] = total + (i == boxes.size()-1 ? 0 : right[i+1]);
            total += boxes[i] == '1';
        }
        
        vector<int> ans(n);
        
        for (int i = 0; i < n; i++)
            ans[i] = left[i] + right[i];
        
        return ans;
    }

    /*
        1769.Minimum-Number-of-Operations-to-Move-All-Balls-to-Each-Box
        本题的最优解可以用o(N)的复杂度实现。

        我们令leftMoves[i]表示将i元素左边所有的盒子搬运过来需要的moves。我们有递推关系：leftMoves[i] = leftMoves[i-1]+left[i]，其中left[i]表示i元素左边盒子的数目。
        理解为两步走：先将i-1左边所有的盒子搬到i-1的位置上，然后将这些盒子都再搬一步到i的位置上。left[i]的递推关系也很明显：left[i] = left[i-1]+ (boxes[i-1]=='1')

        同理我们也可以计算rightMoves[i]。那么最终的答案就是rets[i] = leftMoves[i]+rightMoves[i].
    */
    vector<int> doit_search_1(string boxes) 
    {
        int n = boxes.size();
        vector<int>leftMoves(n);
        vector<int>rightMoves(n);
        int left = 0;
        for (int i = 1; i<n; i++)
        {
            left += (boxes[i-1]=='1');
            leftMoves[i] = leftMoves[i-1] + left*1;
        }
        int right = 0;
        for (int i = n-2; i>=0; i--)
        {
            right += (boxes[i+1]=='1');
            rightMoves[i] = rightMoves[i+1] + right*1;
        }
        vector<int>rets(n);
        for (int i=0; i<n; i++)
            rets[i] = leftMoves[i]+rightMoves[i];
        return rets;
    }
};