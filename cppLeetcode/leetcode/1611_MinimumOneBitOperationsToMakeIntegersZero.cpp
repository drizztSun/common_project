/*

1611. Minimum One Bit Operations to Make Integers Zero

Given an integer n, you must transform it into 0 using the following operations any number of times:

.Change the rightmost (0th) bit in the binary representation of n.
.Change the ith bit in the binary representation of n if the (i-1)th bit is set to 1 and the (i-2)th through 0th bits are set to 0.

Return the minimum number of operations to transform n into 0.

 

Example 1:

Input: n = 0
Output: 0
Example 2:

Input: n = 3
Output: 2
Explanation: The binary representation of 3 is "11".
"11" -> "01" with the 2nd operation since the 0th bit is 1.
"01" -> "00" with the 1st operation.
Example 3:

Input: n = 6
Output: 4
Explanation: The binary representation of 6 is "110".
"110" -> "010" with the 2nd operation since the 1st bit is 1 and 0th through 0th bits are 0.
"010" -> "011" with the 1st operation.
"011" -> "001" with the 2nd operation since the 0th bit is 1.
"001" -> "000" with the 1st operation.
Example 4:

Input: n = 9
Output: 14
Example 5:

Input: n = 333
Output: 393
 

Constraints:

0 <= n <= 109

*/
#include <functional>
#include <unordered_map>
#include <string>
#include <bitset>

using std::bitset;
using std::string;
using std::unordered_map;

class MinimumOneBitOperationsToMakeZero {

    /*
        1611.Minimum-One-Bit-Operations-to-Make-Integers-Zero
        解法1 递归
        我们读懂题意之后，尝试自己来挑一个数试一试。比如说1xxxxx，我们会发现要使得最高的1变成0，似乎只能通过第二条规则。那么第二条规则需要我们干什么事情呢？其实共有三步：

        1(xxxxx) -> 1(10000) -> 0(10000) -> 0(00000)
        第一步，将除最高位之外的xxxxx转化为10000;
        第二步，于是接下来我们根据规则2，可以将最高位变成0;
        第三步，解决完最高位，我们就可以递归处理剩余的数字，也就是将10000转化为00000

        对于第二步，这是规则2的操作。对于第三步，其实就是递归调用原来的函数minimumOneBitOperations。但是对于第一步，似乎是一个我们未见过的变换，那么我们暂时将其定义为helper(n)，并仔细分析一下它。

        helper(n)其实要做的事情，就是将参数n=xxxxx转化为相同位数的bit串：最高位是1，其他位是0. 这时候一个显而易见的发现就是：如果n的最高位也是1的话（即n=1xxxx），那么helper(n)的本质就是将剩下的xxxx转化为0000，咦，这不就是minimumOneBitOperations要做的事情吗，递归处理不就OK了？

        接下来我们就自然会考虑另外一种情况，如果n的最高位是0（即n=0xxxx）,那么helper(n)的作用是将0xxxx转化为10000。这时候为了能将最高位从0变成1，我们又不得不再次使用规则2，再三步走：

        0(xxxx) -> 1(1000) -> 0(1000) -> 0(0000)
        这三步走是不是很熟悉？第一步就是helper(xxxx)，第二步就是规则2的操作，第三步就是minimumOneBitOperations(1000)。

        分析到这里，我们已经可以把任意minimumOneBitOperations(n)的转化过程分析完了：这些分解可以拆成反复递归调用minimumOneBitOperations和helper，作用在更短的字符串上。只要合理地设计好这两个递归函数的边界条件，那么递归层层返回后的结果就是答案。当然，实际操作过程中我们需要记忆化的帮助来减少计算量。

        最后总结一下：

        minimumOneBitOperations(1xxxxx) = helper(xxxxx)+1+minimumOneBitOperations(10000)
        helper(xxxxx) = minimumOneBitOperations(xxxx), if the highest bit is 0
                        helper(xxxx)+1+minimumOneBitOperations(1000), if the highest bit is 1
        解法2 格雷码
        如果我们亲自拆解一个数字来试一下。当n为6时，最优的变化步骤是 110->010->011->001->000. 我们能观察到什么？每相邻两次变化，只有一个bit发生了变化！这就是格雷码序列！所谓的格雷码序列，就是对于n bit的二进制数而言，我们令00...00为序列的第一个数，可以构建一个长度为2^n的序列，序列中每相邻的两个数字只相差一个bit（包括序列的最后一个与序列的第一个）。

        关于格雷码的生成方法，可以参见089. Gray Code的解答。我们有格雷码的通项公式

        for (int i=0; i<(1<<n); i++)
            gray[i] = i^(i>>1);
        在本题中，我们只要找到n在格雷码序列中的位置（即对应的索引i），就可以判定它与0之间的距离。那么如何从gray[i]反求出i呢？其实很简单，假设i的二进制表达是 abcdef，那么

        abcdef
        ^ 0abcde
        -------
        xxxxxx (binary string of n)
        很显然，从高位开始可以逐位破解abcdef.
    */
    int minimumOneBitOperations(int n) 
    {
        if (n==0) return 0;
        string str = bitset<32>(n).to_string();
        int i = 0;
        while (i<str.size() && str[i]=='0')
            i++;
        str = str.substr(i);

        int lastDigit = 0;
        int ret = 0;
        for (int i=0; i<str.size(); i++)
        {
            // x ^ lastDigit = str[i]
            int x;
            if (str[i]=='1')
                x = lastDigit==1 ? 0 : 1;
            else
                x = lastDigit==1 ? 1 : 0;
            lastDigit = x;
            ret = ret*2+x;
        }

        return ret;        
    }

    unordered_map<string,int>mem;
    unordered_map<string,int>mem1;
public:
    int minimumOneBitOperations(int n) 
    {
        string str = bitset<32>(n).to_string();
        return dfs(str);        
    }
    
    int dfs(string n)
    {    
        if (n=="0") return 0;
        if (n=="1") return 1;
        if (mem.find(n)!=mem.end()) return mem[n];
        
        if (n[0]=='0') return dfs(n.substr(1));
        
        string m = n.substr(1);
        string p = m;
        p[0] = '1';
        for (int i=1; i<p.size(); i++)
            p[i] = '0';                        
        mem[n] = dfs1(m) + 1 + dfs(p);
        return mem[n];
    }
    
    int dfs1(string n)
    {
        if (n=="0") return 1;
        if (n=="1") return 0;
        if (mem1.find(n)!=mem1.end()) return mem1[n];
                
        if (n[0]=='1')
            mem1[n] = dfs(n.substr(1));
        else
        {
            string m = n.substr(1);
            string p = m;
            p[0] = '1';
            for (int i=1; i<p.size(); i++)
                p[i] = '0';            
            mem1[n] = dfs1(m)+1 + dfs(p);            
        }
        return mem1[n];        
    }

public:

    /*
        For 1XXXXXXX,
        we need to transfer it
        1XXXXXXX -> ... -> 11000000 -> 1000000 -> ... -> 0


        Observation 1
        The two operations are undo-able.
        If a -> b needs k operation,
        b -> a also needs k operation.


        Observation 2
        1 -> 0 needs 1 operation,
        2 -> 0 needs 3 operations,
        4 -> 0 needs 7 operations,
        2^k needs 2^(k+1)-1 operations.

        This can be easily proved.


        Solution 1: Recursion
        1XXXXXX -> 1100000 -> 100000 -> 0

        1XXXXXX -> 1100000 needs minimumOneBitOperations(1XXXXXX ^ 1100000),
        because it needs same operations 1XXXXXX ^ 1100000 -> 1100000 ^ 1100000 = 0.

        1100000 -> 100000 needs 1 operation.
        100000 -> 0, where 100000 is 2^k, needs 2^(k+1) - 1 operations.

        In total,
        f(n) = f((b >> 1) ^ b ^ n) + 1 + b - 1,
        where b is the maximum power of 2 that small or equals to n.

        Time O(logn)
        Space O(logn)
    */
    int doit_recursive(int n) {
        
        unordered_map<int, int> dp{{0, 0}};

        std::function<int(int)> search = [&](int num) {
        
            if (dp.count(num) > 0)
                return dp[num];

            int b = 1;
            while ((b << 1) <= num) {
                b <<= 1;
            }

            return dp[num] = (search(num ^ b ^ (b >> 1)) + 1 + b - 1);
        };

        return search(n);
    } 

    /*

    Note that the number of operations for n to become 0 is the same as the number of operations for 0 to become n...

    Let's see how it can be done for numbers that are powers of 2.
    1 -> 0 => 1
    10 -> 11 -> 01 -> ... => 2 + 1
    100 -> 101 -> 111 -> 110 -> 010 -> ... => 4 + 2 + 1
    1000 -> 1001 -> 1011 -> 1010 -> 1110 -> 1111 -> 1101 -> 1100 -> 0100 -> ... => 8 + 4 + 2 + 1
    We can find that for 2^n, it needs 2^(n+1) - 1 operations to become 0.

    Now suppose we want to know the number of operations for 1110 to become 0. We know it takes 15 operations for 0 to become 1000, and it takes 4 operations for 1000 to become 1110. We get the solution by 15 - 4.
    Note that 4 here is the number of operations from 1000 to become 1110, which is the same as the number of operations from 000 to 110 (ignoring the most significant bit), and it can be computed recursively. The observation gives us: minimumOneBitOperations(1110) + minimumOneBitOperations(0110) = minimumOneBitOperations(1000).

    From the above intuition, we can reduce n bit by bit, starting from the most significant bit.
    */
    int minimumOneBitOperations(int n) {
        if (n <= 1)
            return n;
        int bit = 0;
        while ((1 << bit) <= n)
            bit++;
        return ((1 << bit) - 1) - minimumOneBitOperations(n - (1 << (bit-1)));
    }

    /*
        Observation 1
        The two operations are undo-able.
        If a -> b needs k operation,
        b -> a also needs k operation.
    */
    int doit(int num) {

        int mask = num;
        
        while(mask) {
            mask >>= 1;
            num ^= mask;
        }
        
        return num;
    }

};