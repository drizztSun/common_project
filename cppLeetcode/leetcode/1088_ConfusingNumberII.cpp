/*
1056. Confusing Number


Given a number N, return true if and only if it is a confusing number, which satisfies the following condition:

We can rotate digits by 180 degrees to form new digits. When 0, 1, 6, 8, 9 are rotated 180 degrees, they become 0, 1, 9, 8, 6 respectively. When 2, 3, 4, 5 and 7 are rotated 180 degrees, they become invalid. A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.

 

Example 1:



Input: 6
Output: true
Explanation: 
We get 9 after rotating 6, 9 is a valid number and 9!=6.
Example 2:



Input: 89
Output: true
Explanation: 
We get 68 after rotating 89, 86 is a valid number and 86!=89.
Example 3:



Input: 11
Output: false
Explanation: 
We get 11 after rotating 11, 11 is a valid number but the value remains the same, thus 11 is not a confusing number.
Example 4:



Input: 25
Output: false
Explanation: 
We get an invalid number after rotating 25.
 

Note:

0 <= N <= 10^9
After the rotation we can ignore leading zeros, for example if after rotation we have 0008 then this number is considered as just 8.
*/
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <functional>

using std::string;
using std::unordered_map;
using std::vector;
using std::unordered_set;


class ConfusingNumber {
public:
    bool doit_(int N) {

        vector<int> nums{0, 1, 6, 8, 9};
        unordered_set<int> Confusing(begin(nums), end(nums));
        
        int res = 0, org = N;
        
        while (N > 0) {
         
            int m = N%10;
            
            if (Confusing.count(m) == 0) return false;
   
            if (m == 6 || m == 9)
                m = m == 6 ? 9 : 6;
            
            res = res * 10 + m;
            
            N /= 10;
        }
        
        return res != org;
    }
};



/*
1088. Confusing Number II


We can rotate digits by 180 degrees to form new digits. When 0, 1, 6, 8, 9 are rotated 180 degrees, they become 0, 1, 9, 8, 6 respectively. When 2, 3, 4, 5 and 7 are rotated 180 degrees, they become invalid.

A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.(Note that the rotated number can be greater than the original number.)

Given a positive integer N, return the number of confusing numbers between 1 and N inclusive.

 

Example 1:

Input: 20
Output: 6
Explanation: 
The confusing numbers are [6,9,10,16,18,19].
6 converts to 9.
9 converts to 6.
10 converts to 01 which is just 1.
16 converts to 91.
18 converts to 81.
19 converts to 61.
Example 2:

Input: 100
Output: 19
Explanation: 
The confusing numbers are [6,9,10,16,18,19,60,61,66,68,80,81,86,89,90,91,98,99,100].
 

Note:

1 <= N <= 10^9

*/

class ConfusingNumberII {

    /*
        1088.Confusing-Number-II
    这题和902.Numbers-At-Most-N-Given-Digit-Set很像，只能够用0,1,6,8,9这五个数字嘛。

    最基本的方法，就是用递归遍历所有可能生成的数（by不断增长位数），每一步都判断是否小于等于N并且是否confusing number，满足条件就计数器加一。当然这个方法非常低效，在902是无法AC的，但是在这里也能够过了，大概beat 20%。

    有一种稍微优化点的方案，就是对于digit位数小于N的confusing number，我们不需要一一列举，而是用数学方法直接表达。举个例子，当N是六位数时，所有五位数的confusing number都不会大于N，也就不用考虑这个约束。那么如何求长度为len的confusing number有多少个呢？

    首先，我们知道confusing number只能用0,1,6,8,9这五个数字组数。先考虑给定这个digit集合能组成多少个长度为len的数？显然答案是4*pow(5,len-1)，其中4是考虑到了高位首位不能为零。

    然后我们考虑在上述这些数中间有多少non-confusing number呢？Non-confusing number的定义就是翻转之后和原来的数字一样，也就是说，相对中间位置对称的两个digit需要是翻转对称的（也就是1->1,6->9,8->8,9->6,0->0），并且如果长度是奇数那么中间一个digit与自己翻转堆成（也就是1->1,8->8,0->0）.所以对于长度为len的数，non-confusing number的个数的计算方法：

            if (len%2==0)        
                return 4*pow(5,len/2-1);
            else
                return 4*pow(5,len/2-1)*3;
    同理，4表示高位第一位不能是0，所以是四种选择。3表示长度是奇数时，中间一个digit的选择只有三种。其他位置（从高位第一位到中间一位）的选择是五种。len/2的操作是因为，对于non-confusing number，只要确定了前一般长度的digit，后一半的digit也就确定了。

    所以对于长度为len的confusing number，就是上面计算得到的两个结果之差。同理，所有小于N的长度的len，我们可以这样用数学方法计算长度为len的confusing number的数目。

    至于len等于N的长度的情况，我们依然可以采用DFS（也就是递归）的笨办法。最终version 2的时间复杂度能够beat 50%.

    当然，还可以有更多的优化，基本思路就是参照902：DFS只贴着N的大小走，如果选取某一位的digit比N对应的那位要小，则摆脱了必须小于N的约束，剩下的digit的组合数目就可以用数学表达式来写。不过感觉有些复杂，我就没有继续深入研究下去。
        
    */
    unordered_map<char,char>Map;
    unordered_set<int>candidates;
    int count = 0;
    int N;
    
    int confusingNumberII(int N) 
    {
        candidates={0,1,6,8,9};
        Map={{'0','0'},{'1','1'},{'6','9'},{'8','8'},{'9','6'}};
        
        this->N = N;
        for (auto x: {1,6,8,9})
            dfs(x);
        return count;
    }
    
    void dfs(long num)
    {
        if (num>N) return;
        
        if (isConfusing(num)) count++;
            
        for (auto x:candidates)
            dfs(num*10+x);
    }
    
    bool isConfusing(int num)
    {
        string s = std::to_string(num);
        int i=0;
        int j=s.size()-1;
        while (i<=j)
        {
            if (Map[s[i]]!=s[j])
                return true;
            i++;
            j--;
        }                
        return false;
    }


public:

    unordered_map<char,char>Map={{'0','0'},{'1','1'},{'6','9'},{'8','8'},{'9','6'}};
    int count = 0;    
    int N;
    string n;
    
    long perm(int l)
    {
        return 4*pow(5,l-1);
    }
    
    long symmetric(int l)
    {
        if (l%2==0)        
            return 4*pow(5,l/2-1);
        else
            return 4*pow(5,l/2-1)*3;
    }
    
    int confusingNumberII(int N) 
    {        
        this->N = N;
        n = std::to_string(N);
        
        for (int l=1; l<n.size(); l++)
        {
            count += perm(l) - symmetric(l);
        }
        
        for (long x: {1,6,8,9})
            dfs(x,1);
        return count;
    }
    
    void dfs(long num, int k)
    {
        if (k==n.size())
        {
            if (num>N) return;
            if (isConfusing(num)) count++;
            return;
        }
            
        for (auto x:{0,1,6,8,9})        
            dfs(num*10+x, k+1);
    }
    
    bool isConfusing(int num)
    {
        string s = std::to_string(num);
        int i=0;
        int j=s.size()-1;
        while (i<=j)
        {
            if (Map[s[i]]!=s[j])
                return true;
            i++;
            j--;
        }                
        return false;
    }

public:

    int doit_(int N) {
        vector<long> bases = {0, 1, 6, 8, 9};
        int count = 0;
        
        auto isconfusing = [](long num) {
           
            long res = 0, org = num;
            while (num) {
                int n = num % 10;
                if (n == 6 || n == 9)
                    n = n == 6 ? 9 : 6;
                res = res * 10 + n;
                num /= 10;
            }
            return res != org;
        };

        std::function<void(long)> dfs = [&](long num) {
            if (num > N) return;
            
            if (isconfusing(num)) count++;
            
            for (auto c:bases) {
                dfs(num*10 + c);
            }
        };
        
        for (auto c : bases) {
            if (c != 0) dfs(c);
        }
        
        return count;
    }
};
