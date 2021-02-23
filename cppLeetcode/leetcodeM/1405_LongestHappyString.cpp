/*
1405. Longest Happy String

A string is called happy if it does not have any of the strings 'aaa', 'bbb' or 'ccc' as a substring.

Given three integers a, b and c, return any string s, which satisfies following conditions:

. s is happy and longest possible.
. s contains at most a occurrences of the letter 'a', at most b occurrences of the letter 'b' and at most c occurrences of the letter 'c'.
. s will only contain 'a', 'b' and 'c' letters.

If there is no such string s return the empty string "".

 

Example 1:

Input: a = 1, b = 1, c = 7
Output: "ccaccbcc"
Explanation: "ccbccacc" would also be a correct answer.
Example 2:

Input: a = 2, b = 2, c = 1
Output: "aabbc"
Example 3:

Input: a = 7, b = 1, c = 0
Output: "aabaa"
Explanation: It's the only correct answer in this case.
 

Constraints:

0 <= a, b, c <= 100
a + b + c > 0

*/

#include <string>
#include <queue>

using std::priority_queue;
using std::string;


class LongestDiverseString {

public:

    /*
        1405.Longest-Happy-String
        本题就是 984.String-Without-AAA-or-BBB 的升级版，只不过包含了三种字符。

        数据结构不变：就是按照频次从大到小塞进优先队列。算法的核心思想：

        1. 每个回合取频次最高的两种字符，即若干个A和一个B，目的是保证两个回合不会有相同的字符邻接在一起。

        2. 取A的个数x取决于当前A的频次比B的频次多多少，最多取两个。即 x = min(2, freq(A)-freq(B)). 目的是为了使得剩余的字符的频次尽量趋同。可以想象，如果剩下的字符频次都相同，那么只要不停输出abcabc...即可。

        当队列里只有一种字符的时候，最多只能再输出该种字符的两个。
    */
    string doit_heap(int a, int b, int c) {

        priority_queue<std::pair<int,char>> pq;
        if (a!=0) pq.push({a,'a'});
        if (b!=0) pq.push({b,'b'});
        if (c!=0) pq.push({c,'c'});

        string ret;
        while (!pq.empty())
        {
            if (pq.size()==1) 
            {
                int k = std::min(2, pq.top().first);
                for (int i=0; i<k; i++)                    
                    ret.push_back(pq.top().second);
                return ret;
            }

            auto x = pq.top();
            pq.pop();

            auto y = pq.top();
            pq.pop();

            int k = std::min(1+x.first-y.first, 2);
            for (int i=0; i<k; i++)
                ret.push_back(x.second);
            ret.push_back(y.second);

            x.first-=k;
            y.first-=1;
            if (x.first!=0) pq.push(x);
            if (y.first!=0) pq.push(y);
        }

        return ret;
    }
};