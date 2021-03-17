/*
446. Arithmetic Slices II - Subsequence


A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequences:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7
 
A zero-indexed array A consisting of N numbers is given. A subsequence slice of that array is any sequence of integers (P0, P1, ..., Pk) such that 0 ≤ P0 < P1 < ... < Pk < N.

A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic. In particular, this means that k ≥ 2.

The function should return the number of arithmetic subsequence slices in the array A.

The input contains N integers. Every integer is in the range of -231 and 231-1 and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 231-1.

 
Example:

Input: [2, 4, 6, 8, 10]

Output: 7

Explanation:
All arithmetic subsequence slices are:
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]


*/

#include <vector>
#include <unordered_map>
#include <map>

using std::map;
using std::unordered_map;
using std::vector;

class ArithmeticSlicesII {

    /*
        446.Arithmetic-Slices-II-Subsequence
        解法1
        首先我们会想，如何能够确定一个等差数列．知道了首项，公差，就能往后推序列的其他元素．所以本题容易想到的一个思路就是正向地搜索．这样的话，光遍历首项和公差就是o(N^2)的复杂度，后续的DFS更是计算量巨大．

        搜索不成的话，DP是个很常规的替代方案．考虑到本题是求方案的数量，所以DP解法的嫌疑就更大了．最常见的DP套路，就是考察待求的状态量DP[i]与之前的状态量DP[j]之间的推导关系，这里的DP[i]不妨就设计为题意要求的以元素j结尾的的等差数列的个数．

        如果i是等差数列的最后一个，那么它之前的一个元素是什么呢？那么j=0~i-1都是有可能的，只要元素j是某个相同公差的等差数列的结尾元素．如果是的话，显然DP[i]+=DP[j]．由此，我们看到一个重要的因素，那就是公差diff．也就是说，判断j是否和i构成等差数列的条件，就是先计算diff=A[j]-A[i]，然后再考察j是否为一个公差为diff的等差数列的尾项．于是我们还需要在DP数组中给Ａ的每个元素开辟一个Hash，用来存储它所涉及的公差．

        我们令dp[i][diff]表示以元素i结尾、公差为diff的等差数列（长度>=2）有多少个。为什么我们会这么定义“长度>=2”？假设我们后面能接上一个元素k并保持这个公差diff的话，对于k而言，以其为结尾的长度>=3的等差数列那就是dp[i][diff]，恰好就是我们想统计的。可见这样定义dp[i][diff]能给我们带来极大的方便。

        当然，对于k而言，你也必须正确地更新dp[k][diff]。注意DP变量的定义，以k为结尾的长度>=2的等差数列应该有dp[i][diff]+1个，这“+1”就是代表着仅包含{i,k}两个元素的数列。

        核心代码如下：

        vector<unorderd_map<int,int>>DP(N);
        int count = 0;
        for (int i=0; i<N; i++)
        for (int j=0; j<i; j++)
        {
            diff = A[i]-A[j];
            count += dp[j][diff]; // 构建了以j,i为倒数两位，且公差为diff的新等差数列(保证长度>=3)
            
            if (dp[j].find(diff)==dp[j].end())
                dp[i][diff] = 1;
            else
                dp[i][diff] += dp[j][diff]+1;  // 更新以i为结尾，且公差为diff的等差数列(长度>=2)的个数。
        }
        return count;  
        这个思想和1027.Longest-Arithmetic-Sequence的解法一致。

        解法2
        一个等差数列,可以通过后两位元素就能唯一确定.所以另一个很常见的DP解法,就是定义状态变量DP[i][j]表示为以元素i,j结尾的等差数列的个数.

        我们通过i,j,查找之前是否存在一个索引k使得A[i]*2=A[k]+A[j].如果找到的话那就说明DP[i][j]+=DP[k][i]+1。其中DP[k][i]+1的意思是：以i,j为结尾的等差数列，大部分可以由以k,i为结尾的等差数列延长而来（多加上一个A[i]而已），但还多出来的一个就是仅含有k,i,j三个元素的等差数列。另外，这里为什么是+=而不是=，那是因为这样的k可能会有好几个(对应相同的A[k]值).

        想通过A[k]值找到k,需要提前处理,用到一个一对应多的hash表unordered_map<int,vector>Map.
    */
    int numberOfArithmeticSlices(vector<int>& A) 
    {
        int n = A.size();
        vector<unordered_map<long,int>>dp(n);
        int count = 0;
        
        for (int i=1; i<A.size(); i++)
        {
            for (int j=i-1; j>=0; j--)
            {
                long diff = (long)A[i]-(long)A[j];
                count += dp[j][diff];
                
                if (dp[j].find(diff) != dp[j].end())
                    dp[i][diff] += dp[j][diff]+1;
                else
                    dp[i][diff] = 1;
            }
        }
            
        return count;
    }

    int numberOfArithmeticSlices(vector<int>& A) 
    {
        unordered_map<int,vector<int>>Map;
        for (int i=0; i<A.size(); i++)
            Map[A[i]].push_back(i);
        
        int N = A.size();
        auto dp = vector<vector<int>>(N,vector<int>(N,0));
        for (int i=0; i<N; i++)
            for (int j=0; j<i; j++)
            {
                long m = A[j]*2L-A[i];
                if (m>INT_MAX || m<INT_MIN) continue;
                for (int k:Map[m])
                {
                    if (k<j)
                        dp[j][i] += dp[k][j]+1;
                }
            }
        int count = 0;
        for (int j=0; j<N; j++)
            for (int i=j+1; i<N; i++)
                count+=dp[j][i];
        return count;
    }

public:
    
    int doit_(vector<int>& A) {
        int n = A.size();
        using LL = long long;
        LL ans = 0;
        vector<map<LL, int>> cnt(n);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                LL delta = (LL)A[i] - (LL)A[j];
                int sum = 0;
                if (cnt[j].find(delta) != cnt[j].end()) {
                    sum = cnt[j][delta];
                }
                cnt[i][delta] += sum + 1;
                ans += sum;
            }
        }

        return (int)ans;
    }

    int doit_dp(vector<int>& A) {

        using LL = long long;

        unordered_map<LL, int> post;
        unordered_map<int, vector<int>> position;

        for (int i = 0; i < A.size(); i++) {
            post[A[i]]++;
            position[A[i]].push_back(i);
        }

        unordered_map<LL, int> pre;
        vector<unordered_map<int, int>> sequence(A.size());

        for (int i = 0; i < A.size(); i++) {
            int a = A[i];
            post[a]--;

            for (auto [b, v]: pre) {

                LL c = a - b + a;

                if (post.count(c) > 0 && post[c] > 0) {
                    
                    // count [b..a]
                    int n = v;

                    if (sequence[i].count(b) > 0) {
                        // at i, count of [c1, c2, b, .., a]
                        n += sequence[i][b];
                    }

                    for (auto j : position[c]) {
                        if (j > i)
                            // at j, add sequence number [c1, c2, b, .. a, C-next]
                            sequence[j][a] += n;
                    }
                }

            }

            pre[A[i]]++;
        }

        int ans = 0;
        for (int i = 0; i < sequence.size(); i++) {
            for (auto it : sequence[i])
                ans += it.second;
        }

        return ans;
    }


};