/*
60. Permutation Sequence

The set [1, 2, 3, ..., n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

 

Example 1:

Input: n = 3, k = 3
Output: "213"
Example 2:

Input: n = 4, k = 9
Output: "2314"
Example 3:

Input: n = 3, k = 1
Output: "123"
 

Constraints:

1 <= n <= 9
1 <= k <= n!
*/

#include <string>
#include <vector>

using std::vector;
using std::string;


class Permutation {

    /*
        060.Permutation-Sequence
        首先，创建一个集合，存储数字选项1,2,3,4,5,6,7,8,9。

        假设第一个位置的数字是1，那么总共有多少个这样的全排列呢？显然就是考虑第2~N位上用数字2~N去做全排列，就是(N-1)!个可能。同理，第一个位置如果是2的话，那么也有(N-1)!个可能；第一个数字是3，同理也有(N-1)!个可能……

        所以，用k除以(N-1)!得到的结果，就可以确定第一个位置的数字。例如：4xxxxxxxx符合要求的全排列共有(N-1)!*4个，形如5xxxxxxxx符合要求的全排列共有(N-1)!*5个，假设k除以(N-1)!的结果大于4且小于5，那么说明所需要的第k大的全排列一定在这两者之间。故它的第一个位置的数字一定是5。这里需要注意一个技巧，我们预先将k减去1，这样我们其实寻找的是0-index标准下的第k个全排列。这样a=k/(N-1)!无论是否整除，a的值就意味着我们需要在digit（剩余）的集合里面找第a个元素（同样是0-index）。

        同理，接下来考虑第二个位置的数字。注意到刚才已经排除了形如4xxxxxxxx的排列，剩下来我们其实寻找的就是以5开头的、第k-(N-1)!*4个全排列。所以我们更新k-=(N-1)!*4，此时的任务演变成了：求由N-1个元素组成的全排列里面第k个是多少。我们可以重复上面的方法，通过查看k/(N-2)!的结果来判定第二位上的数字是什么。注意，每确定了一个数字，就需要从digit集合中删除那一个避免重复使用。

        依次类推，就可以确定所有位置上的数字。值得指出的是，当n降为1的时候，此时的k一定会是零。
    */
    string getPermutation(int n, int k) 
    {
        vector<int>digits;
        for (int i=1; i<=n; i++)
            digits.push_back(i);
        
        k--;
        
        string ret;
        while (n>0)
        {
            int a = k/ fact(n-1);
            ret.push_back('0'+digits[a]);
            
            k -= a * fact(n-1);
            n -= 1;
            
            digits.erase(digits.begin()+a);
        }
        
        return ret;
    }
    
    int fact(int k)
    {
        int ret = 1;
        for (int i=1; i<=k; i++)
            ret *= i;
        return ret;
    }

public:
    
    string doit_(int n, int k) {
        
        vector<int> factor{ 1 };
        vector<char> chr;

        for (int i = 1; i <= n; i++) {
            // generate factorial system bases 0!, 1!, ..., (n - 1)!
            factor.push_back(factor.back() * i);
            // generate nums 1, 2, ..., n
            chr.push_back('0' + i);
        }

        // fit k in the interval 0 ... (n! - 1)
        k -= 1;
        string ans;

        // compute factorial representation of k
        for (int i = n - 1; i >= 0; i--) {

            int idx = k / factor[i];
            k -= idx * factor[i];

            ans.push_back(chr[idx]);
            chr.erase(begin(chr) + idx);
        }

        return ans;
    }
};