/*
1542. Find Longest Awesome Substring

Given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it palindrome.

Return the length of the maximum length awesome substring of s.

 

Example 1:

Input: s = "3242415"
Output: 5
Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
Example 2:

Input: s = "12345678"
Output: 1
Example 3:

Input: s = "213123"
Output: 6
Explanation: "213123" is the longest awesome substring, we can form the palindrome "231132" with some swaps.
Example 4:

Input: s = "00"
Output: 2
 

Constraints:

1 <= s.length <= 10^5
s consists only of digits.


*/
#include <string>
#include <vector>
#include <unordered_map>


using std::unordered_map;
using std::vector;
using std::string;




class LongestAwesomeString {

    /*
        1542.Find-Longest-Awesome-Substring
        本题的本质是求一个最长的区间，使得区间内的字符能够重组成为回文数。重组成为回文数的条件是：统计每个字符的词频，词频为奇数的字符最多只能有1个。

        对于区间的词频统计，我们不会手工来数。用前缀数组的方法比较常见，也就是转化成了前缀数组的减法。我们用prefix[j]-prefix[i-1]，就可以求出区间[i:j]范围内每个字符的频次。

        现在我们固定区间的右端点j，来探索区间的左端点i在哪里？我们希望找到这样的一个左端点i：使得区间[i:j]的字符频次满足重组回文数的要求，那么就是说prefix[j]-prefix[i-1]需要满足重组回文数的要求。我们可以发现两种情况：

        1. 所有的字符，prefix[j]和prefix[i-1]的奇偶性相同，那么说明prefix[j]-prefix[i-1]必然是偶数，即[i:j]区间里所有字符的词频必然都是偶数，即满足重组回文数的要求。
        
        2. 只有一种字符，prefix[j]和prefix[i-1]的奇偶性不同，那么对于该字符而言prefix[j]-prefix[i-1]必然是奇数，即[i:j]区间里仅有一种字符的词频是奇数，也满足重组回文数的要求。
        
        也就是说，我们知道了prefix[j]的奇偶性，想求一个最小的i，使得prefix[i-1]的奇偶性满足特定的条件。这就需要用到hash表。key是前缀频次的奇偶性（我们想要的），value是相应的前缀的index（我们相查的）。

        那么如何用一个key来表达十个字符的频次奇偶性呢？显然我们用10个二进制位来编码就行了。注意，如果你用10个字01符组成的字符串来作为key存储，会TLE。

        具体的做法就是我们每次处理完一个元素k之后，都会将截止k的所有字符的前缀频次编码为key放入hash表。如果后续操作中，需要寻找特定的“字符频次奇偶性”，就可以通过这个表找到这个前缀所在的位置i，那么[i:j]就是一个符合要求的subarray。

        注意上述的第二种情况，我们需要创建10个新key来在hash表中查找。比如说pefix[j]的所有字符奇偶性是1000000001，那么我们会操作十次，每次将1000000001中的一个bit反转，查看hash表中是否存在了这样的一个key。如果存在的话，说明在这个区间内，该字符对应的频次是奇数，而其他的都是偶数，故符合重组回文数的要求。
    
    */
    int longestAwesome(string s) 
    {
        vector<int>count(10,0);
        int n = s.size();
        s="#"+s;
        
        unordered_map<int,int>Map;
        Map[0] = 0;
        int ret = 0;
        
        for (int i=1; i<=n; i++)
        {            
            count[s[i]-'0']+=1;
            int key = makeKey(count);
            
            if (Map.find(key)!=Map.end())
                ret = std::max(ret, i - Map[key]);
            
            for (int k=0; k<10; k++)
            {
                int newKey = key;
                
                if (((key>>k)&1)==0)
                    newKey |= (1<<k);
                else
                    newKey -= (1<<k);
                
                if (Map.find(newKey)!=Map.end())
                    ret = std::max(ret, i - Map[newKey]);                    
            }
            if (Map.find(key)==Map.end()) Map[key] = i;            
        }
        
        return ret;
    }
    
    int makeKey(vector<int>&count)
    {
        int key=0;
        for (int i=0; i<10; i++)
        {
            if (count[i]%2==0)
                key+=(0<<i);
            else
                key+=(1<<i);
        }
        return key;
    }


public:

    /*
        Longest/Shortest substring of XXX

        Solution 0: Brute Force(n^2) TLE

        Solution 1L Prefix + Hashtable O(n)

        Define a state of prefix string input[0~i], update the state when extend the prefix

        index[S] := first/last index when state S occurred

        Let's assume state Si, Sj occurred at [i, j], i < j, connd(Si, Sj) = True, input[i+1~j] is a solution 
        ans its length is j - (i+1) + 1 = j - i

        index[S init] = -1 # base state "occured" before the start, this handles the case when entire prefix is a solution.

        ans = max/min{i - index[S cur]} 0 <= i < n

        325. Maximum Size Subarray Sum Equals K (locked) state: prefix sum, Sj = s, Si = s - k => sum(input[i+1 ~ j]) == k

        Awesine string / Palindrome:

        1) 0 or 1 char occurs odd times and rest of the chars occur even times.

        Since we only care about parity, we can use 1 bit for each digit

        1) state is a 10bit binary string in int format.
        2) 0: even times, 1: odd times

        If the state occurred twice at [i, j] means all digits in s[i+1~j] 
    */
    
    int doit_prefix_hashtable(string s) {

        const int kInf = 1e9 + 7;
        vector<int> idx(1<<10, kInf);
        idx[0] = -1;

        int mask = 0;
        int ans = 0;
        for (int i = 0; s[i]; i++) {

            mask ^= (1 << (s[i] - '0'));
            ans = std::max(ans, i - idx[mask]);

            for (int j = 0; j < 10; j++) {
                ans = std::max(ans, i - idx[mask ^ (1 << j)]);
            }

            idx[mask] = std::min(idx[mask], i);
        }

        return ans;
    }
};