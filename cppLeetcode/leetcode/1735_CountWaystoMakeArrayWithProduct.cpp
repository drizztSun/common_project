/*
1735. Count Ways to Make Array With Product



You are given a 2D integer array, queries. For each queries[i], where queries[i] = [ni, ki], find the number of different ways you can place positive integers into an array of size ni such that the product of the integers is ki. 
As the number of ways may be too large, the answer to the ith query is the number of ways modulo 109 + 7.

Return an integer array answer where answer.length == queries.length, and answer[i] is the answer to the ith query.

 

Example 1:

Input: queries = [[2,6],[5,1],[73,660]]
Output: [4,1,50734910]
Explanation: Each query is independent.
[2,6]: There are 4 ways to fill an array of size 2 that multiply to 6: [1,6], [2,3], [3,2], [6,1].
[5,1]: There is 1 way to fill an array of size 5 that multiply to 1: [1,1,1,1,1].
[73,660]: There are 1050734917 ways to fill an array of size 73 that multiply to 660. 1050734917 modulo 109 + 7 = 50734910.
Example 2:

Input: queries = [[1,1],[2,2],[3,3],[4,4],[5,5]]
Output: [1,2,3,10,5]
 

Constraints:

1 <= queries.length <= 10^4
1 <= ni, ki <= 10^4

*/


#include <vector>

using std::vector;


class WaysToFillArray {

    typedef long long ll;

public:

    /*
        1735.Count-Ways-to-Make-Array-With-Product
        一个比较粗暴的方法就是递归。对于k，我们遍历它的因数x1，然后遍历k/x1的因数x2，然后遍历k/x1/x2的因数x3，...，直至遍历完所有的n个因数。因为n很大可以达到1000，这个递归深度就太深了，一定会TLE。

        有什么高效的方法来把k分解成n组因数的乘积呢？我们自然会想到质因数。比如说12=2x2x3，想要将其分割为4组的话，就是把这三个质因数分成4组（允许某组为空，也就是该组所对应的因数是1）。
        对于把x个同质球分成y份的方法数，是一个经典的组合问题，答案就是组合数C(x+y-1, y-1)。我们可以这么理解：将x+y个“虚拟球”排成一列，中间就有x+y-1个间隔，我们在其中选择y-1个间隔插入板子，就可以得到y个区间，每一个区间至少有一个“虚拟球”。
        我们约定：插板后每段区间内“虚拟球”的数目减去一，就是该区间分组的真实球的数量。我们可以想象，每一个合法的插板方法，都恰好一一映射了一种合法的“将x个同质球分成y份（允许某份为零）”的方案。

        比如说将2x2x3这3个质因数分为4份，插板方案有

            插板               每组元素个数  分解方案
        O | O O | O | O O O =>  0 1 0 2 => 1x2x1x6
        O | O O | O O | O O =>  0 1 1 1 => 1x2x2x3
        O | O O O | O O | O =>  0 2 1 0 => 1x4x3x1
        O O | O | O | O O O =>  1 0 0 2 => 2x1x1x6
        O O | O | O O | O O =>  1 0 1 1 => 2x1x2x3
        O O | O  O | O O |O =>  1 1 1 0 => 2x2x3x1
        ...
        总共有C(6,3)=6种方案。

        但是以上方案有个问题，就是没有考虑到这3个质因数(2,2,3)的permutation。我们似乎得找出所有unique permuation，然后对每种permutation都用上面的插板法来分组。

        那么如何解决呢？方法是对于每个质因数apply上述的分组方案。比如说12，它的质因数2出现了两次，那么我们就考虑如何把这两个2分成4组；
        它的质因数3出现了一次，我们就考虑如何把这一个3分成4组。这样，对于相同的质因数，它如果有x个，那么这x个元素就是“同质球”，彼此之间是没有区别的，我们就可以放心地应用插板法。

        最终的方案总数的计算法方法。分解质因数k = x1^p1 + x2^p2 + x3^p3 + ... 总方案数 = 把p1个（相同质因数x1）分成n组方案 * 把p2个（相同质因数x2）分n组方案 * 把p3个（相同质因数x3）分成n组方案 ...
    
    */
    vector<int> doit_math(vector<vector<int>>& queries) {
        ll comb[10015][15]; 
        ll M = 1e9+7;

        int maxK = 10000;
        int maxExp = 14;
        for (int i = 0; i <= (maxK+maxExp); ++i) 
        {
            comb[i][0] = 1;            
            for (int j = 1; j <= std::min(i, maxExp); ++j) 
            {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % M;
            }
        }  

        vector<int>rets;
        for (auto q : queries) {

            ll ans = 1;
            int k = q[0];
            int n = q[1];
            for (int x=2; x<=n; x++)
            {
                int count = 0;
                while (n%x==0)
                {
                    count++;
                    n/=x;
                }
                ans = ans * comb[count+k-1][count] % M;                
            }
            rets.push_back(ans);
        }
        return rets;
    }
};