/*
483. Smallest Good Base

For an integer n, we call k>=2 a good base of n, if all digits of n base k are 1.

Now given a string representing n, you should return the smallest good base of n in string format.

Example 1:

Input: "13"
Output: "3"
Explanation: 13 base 3 is 111.
 

Example 2:

Input: "4681"
Output: "8"
Explanation: 4681 base 8 is 11111.
 

Example 3:

Input: "1000000000000000000"
Output: "999999999999999999"
Explanation: 1000000000000000000 base 999999999999999999 is 11.
 

Note:

The range of n is [3, 10^18].
The string representing n is always valid and will not have leading zeros.
*/

#include <string>

using std::string;


class SmallestGoodBase {

    /*
        483.Smallest-Good-Base
        问题转化为等比数列 n = k^0 + k^1 +k^2 + … + k^(m-1)，对于给定的n，求最大的 m  

        分析：
        根据等比数列求和公式：n = (k^m-1)/(k-1)。可以看出，k越小，m越大；反之k越大，m越小。

        先看m的范围：因为k最小是2，那么对应项数m最大就是 log(n)/log(2)+1；m最小是1（其实是2，无所谓了），说明m是有范围的.

        如果固定m之后，再查看k的范围：因为 n > k^(m-1)，所以 k< pow(n, 1/(m-1))，也有上界。k的最小值已知是2了。说明k也是有范围的。

        所以我们遍历m的值（注意从大到小遍历），然后对于固定的m，对k采用二分搜索，查找是否有(k,m)满足等比数列求和是n。

        注意：

        给出的n是字符型。
        全体变量需要用长整形。
        k的上限 pow(n,1.0/(m-1))，注意1.0
        二分法搜索k的时候，if (sum>N) right=k-1，否则会死循环
        不能使用等比公式求和公式，计算n的时候会有误差。应该采用如下的方法：
        long long sum=1;
        for (int i=1; i<m-1; i++)
            sum = sum*k+1;
    */
    string doit_binary_search(string n) 
    {
        long long N=0;
        for (int i=0; i<n.size(); i++)
            N=N*10+n[i]-'0';
        
        if (N==1) return "2";
        
        long long m_max = log(N+1)/log(2)+1;
        
        for (long long m=m_max; m>=2; m--)
        {
            long long left = 2;
            long long right = pow(N,1.0/(m-1));
            long long mid;

            while (left<=right)  // 两个边界都需要探查
            {
                
                mid = left+(right-left)/2;
                long long k=mid;
                long long sum=1;
                
                for (int i=1; i<m; i++){
                    sum=sum*k+1;
                }

                if (sum==N)
                    return std::to_string(k);
                else if (sum<N)
                    left = mid+1;
                else
                    right = mid-1;  // 注意，因为mid已经排除，所以right的更新值不应该包括mid本身，否则死循环。
            }
        }
        
        return std::to_string(N-1);
    }
};