/*
390. Elimination Game

You have a list arr of all integers in the range [1, n] sorted in a strictly increasing order. Apply the following algorithm on arr:

.Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.
.Repeat the previous step again, but this time from right to left, remove the rightmost number and every other number from the remaining numbers.
.Keep repeating the steps again, alternating left to right and right to left, until a single number remains.
.Given the integer n, return the last number that remains in arr.

 

Example 1:

Input: n = 9
Output: 6
Explanation:
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
arr = [2, 4, 6, 8]
arr = [2, 6]
arr = [6]
Example 2:

Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 109

*/



class EliminationGame {

    /*
        390.Elimination-Game
        考虑第一轮：从序列 1，2，3，4，5，6，7，8，9，10，11 这11个数里面找最终存留的数的位置,定义为f(11),

        第二轮之后：转换为从序列 2,4,6,8,10 这5个数里面找最终存留的数的位置,定义为f(5),那么得到的结果(那个位置)其实放在第一轮而言,我们要把这个index乘以2.
        不仅如此,因为第二轮我们其实需要从右往左找数,所以说按照从左往右的找到的数,我们应该镜像一下才行.也就是说 f(11) = (5+1-f(5))*2 (这是因为1对应5,2对应4,...,所以用6去减)

        因此我们可以得到递推公式

        f(n) = (n/2+1-f(n/2)) *2 
        边界条件是 n==1时，f(1)=1.
    */
public:

    int lastRemaining(int n) 
    {
        if (n==1) return 1;
        
        return (n/2+1 - lastRemaining(n/2))*2;
    }
};