/*
1605. Find Valid Matrix Given Row and Column Sums

You are given two arrays rowSum and colSum of non-negative integers where rowSum[i] is the sum of the elements in the ith row and colSum[j] is the sum of the elements of the jth column of a 2D matrix. 
In other words, you do not know the elements of the matrix, but you do know the sums of each row and column.

Find any matrix of non-negative integers of size rowSum.length x colSum.length that satisfies the rowSum and colSum requirements.

Return a 2D array representing any matrix that fulfills the requirements. It's guaranteed that at least one matrix that fulfills the requirements exists.

 

Example 1:

Input: rowSum = [3,8], colSum = [4,7]
Output: [[3,0],
         [1,7]]
Explanation:
0th row: 3 + 0 = 3 == rowSum[0]
1st row: 1 + 7 = 8 == rowSum[1]
0th column: 3 + 1 = 4 == colSum[0]
1st column: 0 + 7 = 7 == colSum[1]
The row and column sums match, and all matrix elements are non-negative.
Another possible matrix is: [[1,2],
                             [3,5]]
Example 2:

Input: rowSum = [5,7,10], colSum = [8,6,8]
Output: [[0,5,0],
         [6,1,0],
         [2,0,8]]
Example 3:

Input: rowSum = [14,9], colSum = [6,9,8]
Output: [[0,9,5],
         [6,0,3]]
Example 4:

Input: rowSum = [1,0], colSum = [1]
Output: [[1],
         [0]]
Example 5:

Input: rowSum = [0], colSum = [0]
Output: [[0]]
 

Constraints:

1 <= rowSum.length, colSum.length <= 500
0 <= rowSum[i], colSum[i] <= 108
sum(rows) == sum(columns)

*/
#include <vector>

using std::vector;

class RestoreMatrix {

public:

    /*
    
        1605.Find-Valid-Matrix-Given-Row-and-Column-Sums
        从一个例子入手：我们考虑一个3x3的矩阵，并且a+b+c==x+y+z

        O O O | a
        O O O | b
        O O O | c
        ______
        x y z
        我们先考虑第一行怎么填？我们先不考虑大局观，仅就第一行而言，我们只需要任填3个数字，使得sum等于a。不过，我们还有三个约束：a[0][0]<=x, a[0][1]<=y, a[0][2]<=z，否则colSum就会溢出。
        那么根据这个一个等式约束和三个不等式约束，我们一定能填出这三个非负整数来吗？答案是肯定的。因为这三个不等式约束合并起来相当于a = a[0][0]+a[0][1]+a[1][1] <= x+y+z，而这个是通过题干中a+b+c==x+y+z所能保证的。

        既然（满足上述的约束的）第一行的三个非负整数一定可以搞出来，那么我们具体设计什么策略去填写呢？可以搞一个贪心，即每个元素尽量填最大的：

        a[0][0] = min(x,a);
        a[0][1] = min(y,a-a[0][0]);
        a[0][2] = a-a[0][0]-a[0][1];
        注意第三个式子其实等价于：a[0][2] = min(z, a-a[0][0]-a[0][1])，这是因为a = a[0][0]+a[0][1]+a[0][2] <= a[0][0]+a[0][1]+z，故a-a[0][0]-a[0][1] <= z

        此时我们解决了第一行，那么剩下来我们要处理的是一个2x3的矩阵，且已有b+c==x'+y'+z'

        O O O | b
        O O O | c
        ______
        x'y'z'
        其中x'=x-a[0][0], y'=y-a[0][1], z'=z-a[0][2]. 同理，我们依然可以填写出第二行的三个非负整数，满足a[1][0]+a[1][1]+a[1][2]==b并且a[1][0]<=x', a[1][1]<=y', a[1][2]<=z'.

        那么我们就要只剩最后一行，且已有c = x*+y*+z*

        O O O | c
        ______
        x*y*z*
        其中x*=x-a[0][0]-a[1][0], y*=y-a[0][1]-a[1][1], z*=z-a[0][2]-a[1][2]. 很想然，从colSum的角度来看，此时的这三个数的值已经确定了：a[2][0]=x*, a[2][1]=y*, a[2][2]=z*。
        但是，我们从rowSum的角度来看，还需要满足a[2][0]+a[2][1]+a[2][2]==c. 很幸运，这个约束是已经满足的！因为从最初的a+b+c = x+y+z，我们已经一步步推出了c = x*+y*+z*

        综上所述，按照上面的贪心法去填写每个元素，最终一定能得到满足题意的矩阵。
    */
    vector<vector<int>> doit_greedy(vector<int>& rowSum, vector<int>& colSum) 
    {
        int m = rowSum.size();
        int n = colSum.size();
        auto ret = vector<vector<int>>(m, vector<int>(n));
        
        for (int i=0; i<m; i++)
        {
            for (int j=0; j<n; j++)
            {
                int v = min(rowSum[i], colSum[j]);
                ret[i][j] = v;
                rowSum[i] -= v;
                colSum[j] -= v;                
            }
        }
        return ret;        
    }
};