/*

1130. Minimum Cost Tree From Leaf Values

Given an array arr of positive integers, consider all binary trees such that:

Each node has either 0 or 2 children;
The values of arr correspond to the values of each leaf in an in-order traversal of the tree.  (Recall that a node is a leaf if and only if it has 0 children.)
The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree respectively.
Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node.  It is guaranteed this sum fits into a 32-bit integer.



Example 1:

Input: arr = [6,2,4]
Output: 32
Explanation:
There are two possible trees.  The first has non-leaf node sum 36, and the second has non-leaf node sum 32.

    24            24
   /  \          /  \
  12   4        6    8
 /  \               / \
6    2             2   4


Constraints:

2 <= arr.length <= 40
1 <= arr[i] <= 15
It is guaranteed that the answer fits into a 32-bit signed integer (ie. it is less than 2^31).


*/
#include <vector>
#include <stack>

using std::stack;
using std::vector;

/*
1130.Minimum-Cost-Tree-From-Leaf-Values
解法1：
比较容易想到的解法就是区间型的DP。令状态dp[i][j]表示将[i,j]之间的元素最终聚成一个元素所需要的cost。显然，突破点就是如何将这个区间划分为左右两个分支，这就需要遍历可能的内部分界点k。这样的话，就可以得到状态转移方程：

dp[i][j] = min(dp[i][k]+dp[k+1][j]+largest[i][k]*largest[k+1][j])
需要注意，largest[k+1][j]需要提前处理，这可能需要设计另外一个dp过程：

largest[i][j] = max(largest[i][i],largest[i+1][j])
这样的解法时间复杂度是o(N^3).

解法2：
更优秀的解法需要对于题意做进一步的理解。

我们可以想象，每一次对两个节点做“归并”，就是消灭较小的数，保留较大的数。所以整个过程可以理解为：对于arr的数组，每次取当前相邻的两个元素进行归并，较小的元素被消失，较大的元素保留，其cost是两者的乘积。注意，消失的元素会使得原先不相邻的两个元素变得相邻。问经过N-1次归并之后的最小cost总和是多少。

所以对于任何一个元素，它只能是在与更大的元素相遇之后才能被消失，否则会一直存在。那么更大的元素是什么呢？就两种选择：左边第一个比它大的数，右边第一个比它大的数。显然，为了减小cost，我们必然选择让它和较小的那个候选数去碰撞。体会一下，对于每个元素，它所作的选择都是独立的，不会相互冲突。举个例子：ABCDEF，对于D而言，如果我们可以判定它和A碰撞最优（当然A>D)，那么对于B或者C的碰撞对象的选择没有任何影响。这是因为允许D选择A的隐含信息就是BC都比A小，B和C必定只能限制在A和D之间选择。

所以算法的大致思想就是：对于每个元素arr[i]，我们考察它被消去时候的cost，然后总cost相加就是答案。（显然，我们只有N-1次相消，因为最大的元素是不可能被消去的）。单个元素的cost，就是在其左边第一个比它大的数a，右边第一个比它大的数b，两者之间选择，即 arr[i]*min(a,b)。求一个数组里每一个元素的左边（或者右边）第一个比它大的元素，就是典型的单调栈的应用。参考496.next greater element.

有两个细节需要注意。

首先，如果一个元素的左边没有比它更大的数，但它仍有可能被（右边更大的数）消去，那么我们就定义a=INT_MAX.对于右边的情况同样处理。

其次，以上的算法中严格要求了所有的元素都能比较（分出大小）。如果两个元素的数值相等，我们必须额外定义一个区分大小的原则。最简单的方法就是，数值相等的元素，右边的更大。如果我们不这样处理，会遇到这样的情况：xxxx A1 A2 xxx，当A1与A2相等时，如果我们考虑A1可以被A2消去，且考虑A2可以被A1消去，那么会有两次cost的相加。但事实上A1与A2的碰撞只应该计算一次cost。

*/

class MiniomumCostTreeFromLeafValues {

public:
    
    int doit_dp(vector<int>& arr, int target) {

        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        vector<vector<int>> larger(n, vector<int>(n, -1));

        for (int i = 0; i < n; i++) {
            dp[i][i] = 0;
            larger[i][i] = arr[i];
        }


        for (int len = 1; len < n; len++) {

            for (int i = 0; i < n - len; i++) {

                int j = i + len;

                for (int k = i; k < j; k++){

                    dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k+1][j] + larger[i][k] * larger[k+1][j]);
                    larger[i][j] = std::max(larger[i][k], larger[k+1][j]); 
                }
            }
        }
        return dp[0][n-1];
    }

    int mctFromLeafValues(vector<int>& arr) 
    {
        int n = arr.size();
        vector<int>nextGreater(n,INT_MAX);
        vector<int>prevGreater(n,INT_MAX);
        
        stack<int>Stack;
        for (int i=0; i<arr.size(); i++)
        {
            if (Stack.empty() || arr[i] <= arr[Stack.top()])
                Stack.push(i);
            else
            {
                while (!Stack.empty() && arr[Stack.top()] <= arr[i])
                {
                    int idx = Stack.top();
                    nextGreater[idx] = arr[i];
                    Stack.pop();
                }
                Stack.push(i);
            }                
        }
        
        while (!Stack.empty()) Stack.pop();
        for (int i=0; i<arr.size(); i++)
        {
            if (Stack.empty() || arr[i] <= arr[Stack.top()])
            {
                if (!Stack.empty()) prevGreater[i] = arr[Stack.top()];
                Stack.push(i);
            }
            else 
            {
                while (!Stack.empty() && arr[Stack.top()] <= arr[i])
                    Stack.pop();
                if (!Stack.empty())
                    prevGreater[i] = arr[Stack.top()];
                Stack.push(i);
            }
        }
        
        int result = 0;
        for (int i=0; i<arr.size(); i++)
        {
            int x = std::min(prevGreater[i], nextGreater[i]);
            if (x!=INT_MAX)
                result += arr[i]*x;   
        }
        return result;
    }


    /*
    DP Solution
    Find the cost for the interval [i,j].
    To build up the interval [i,j],
    we need to split it into left subtree and sub tree,
    dp[i, j] = dp[i, k] + dp[k + 1, j] + max(A[i, k]) * max(A[k + 1, j])

    If you don't understand dp solution,
    I won't explain it more and you won't find the answer here.
    Take your time,
    read any other solutions,
    and come back at your own will.

    If you got it, continue to read.

    DP Complexity
    Second question after this dp solution,
    what's the complexity?
    N^2 states and O(N) to find each.
    So this solution is O(N^3) time and O(N^2) space.

    You thought it's fine.
    After several nested for loop, you got a happy green accepted.
    You smiled and released a sigh as a winner.

    What a great practice for DP skill!
    Then you noticed it's medium.
    That's it, just a standard medium problem of dp.
    Nothing can stop you. Even dp problem.


    True story
    So you didn't Read and Upvote this post.
    (upvote is a good mark of having read)
    One day, you meet exactly the same solution during an interview.
    Your heart welled over with joy,
    and you bring up your solution with confidence.

    One week later, you receive an email.
    The second paragraph starts with a key word "Unfortunately".

    What the heck!?
    You solved the interview problem perfectly,
    but the company didn't appreciate your talent.
    What's more on earth did they want?
    WHY?


    Why
    Here is the reason.
    This is not a dp problem at all.

    Because dp solution test all ways to build up the tree,
    including many unnecessay tries.
    Honestly speaking, it's kinda of brute force.
    Yes, brute force testing, with memorization.


    Intuition
    Let's review the problem again.

    When we build a node in the tree, we compared the two numbers a and b.
    In this process,
    the smaller one is removed and we won't use it anymore,
    and the bigger one actually stays.

    The problem can translated as following:
    Given an array A, choose two neighbors in the array a and b,
    we can remove the smaller one min(a,b) and the cost is a * b.
    What is the minimum cost to remove the whole array until only one left?

    To remove a number a, it needs a cost a * b, where b >= a.
    So a has to be removed by a bigger number.
    We want minimize this cost, so we need to minimize b.

    b has two candidates, the first bigger number on the left,
    the first bigger number on the right.

    The cost to remove a is a * min(left, right).


    More Good Stack Problems
    Here are some problems that impressed me.
    Good luck and have fun.

    1130. Minimum Cost Tree From Leaf Values
    907. Sum of Subarray Minimums
    901. Online Stock Span
    856. Score of Parentheses
    503. Next Greater Element II
    496. Next Greater Element I
    84. Largest Rectangle in Histogram
    42. Trapping Rain Water

    */
   
   int mctFromLeafValues(vector<int>& A) {
        int res = 0;
        vector<int> stack = {INT_MAX};
        for (int a : A) {
            while (stack.back() <= a) {
                int mid = stack.back();
                stack.pop_back();
                res += mid * std::min(stack.back(), a);
            }
            stack.push_back(a);
        }
        for (int i = 2; i < stack.size(); ++i) {
            res += stack[i] * stack[i - 1];
        }
        return res;
    }
};