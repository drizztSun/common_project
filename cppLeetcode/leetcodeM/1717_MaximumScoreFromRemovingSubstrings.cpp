/*
1717. Maximum Score From Removing Substrings



You are given a string s and two integers x and y. You can perform two types of operations any number of times.

*Remove substring "ab" and gain x points.
*For example, when removing "ab" from "cabxbae" it becomes "cxbae".

*Remove substring "ba" and gain y points.
*For example, when removing "ba" from "cabxbae" it becomes "cabxe".

Return the maximum points you can gain after applying the above operations on s.

 

Example 1:

Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19
Explanation:
- Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
- Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
- Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
- Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.
Example 2:

Input: s = "aabbaaxybbaabb", x = 5, y = 4
Output: 20
 

Constraints:

1 <= s.length <= 10^5
1 <= x, y <= 10^4
s consists of lowercase English letters.
*/
#include <string>
#include <functional>

using std::string;


class MaximumGain {

public:

    /*
        1717.Maximum-Score-From-Removing-Substrings
        此题就是一个简单的贪心法。如果ab的收益比ba大，那么从头到尾我们就尽量删除ab。一遍走完之后，剩下的就一定只是bbbaaa的形式，那么我们就只需要再走一遍删ba了。

        如果ba的收益比ab大，我们有一个比较巧妙的处理方法。就是将s逆序，并把x和y对换。这样我们依然重用上面的代码，第一遍删ab，第二遍删ba。


    */
    int doit_greedy(string s, int x, int y) 
    {
        if (x < y) {
            reverse(s.begin(), s.end());
            std::swap(x,y);
        }

        int ret = 0;
        string t;
        for (auto ch: s)
        {
            t.push_back(ch);
            while (t.size()>=2 && t.substr(t.size()-2)=="ab")
            {
                t.pop_back();
                t.pop_back();
                ret += x;
            }
        }

        string w;
        for (auto ch: t)
        {
            w.push_back(ch);
            while (w.size()>=2 && w.substr(w.size()-2)=="ba")
            {
                w.pop_back();
                w.pop_back();
                ret += y;
            }
        }
        
        return ret;
    }
    
    int doit_(string s, int x, int y) {
        int r = 0;

        std::function<int(string&, char, char)> do_rem = [&](string& s, char c1, char c2) {
            int cnt = 0;
            string o = ".";
            for (char c: s) {
                if (c == c2 && o.back() == c1) {
                    ++ cnt;
                    o.pop_back();
                } else {
                    o.push_back(c);
                }
            }
            s = o;
            return cnt;
        };

        if (x > y) {
            r += x * do_rem(s, 'a', 'b');
            r += y * do_rem(s, 'b', 'a');
        } else {
            r += y * do_rem(s, 'b', 'a');
            r += x * do_rem(s, 'a', 'b');
        }
        return r;
    }

    int doit_greedy_2(string s, int x, int y) {

        string target = (x > y) ? "ab" : "ba";
        string buff;
        buff.reserve(s.length());
        int ans = 0;

        for (int i = 0; i < s.length(); i++) {
            buff.push_back(s[i]);
            if (buff.length() >= 2 && buff.substr(buff.length() - 2) == target) {
                ans += std::max(x, y);
                buff.resize(buff.length()-2);
            }
        }

        target = (x > y) ? "ba" : "ab";
        string w;
        for (int i = 0; i < buff.length(); i++) {
            w.push_back(buff[i]);

            if (w.length() >= 2 && w.substr(w.length() - 2) == target) {
                ans += std::min(x, y);
                w.resize(w.length() - 2);
            }
        }

        return ans;
    }
};

