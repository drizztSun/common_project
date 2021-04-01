/*
 1585. Check If String Is Transformable With Substring Sort Operations
 
 Given two strings s and t, you want to transform string s into string t using the following operation any number of times:

 Choose a non-empty substring in s and sort it in-place so the characters are in ascending order.
 For example, applying the operation on the underlined substring in "14234" results in "12344".

 Return true if it is possible to transform string s into string t. Otherwise, return false.

 A substring is a contiguous sequence of characters within a string.

  

 Example 1:

 Input: s = "84532", t = "34852"
 Output: true
 Explanation: You can transform s into t using the following sort operations:
 "84532" (from index 2 to 3) -> "84352"
 "84352" (from index 0 to 2) -> "34852"
 Example 2:

 Input: s = "34521", t = "23415"
 Output: true
 Explanation: You can transform s into t using the following sort operations:
 "34521" -> "23451"
 "23451" -> "23415"
 Example 3:

 Input: s = "12345", t = "12435"
 Output: false
 Example 4:

 Input: s = "1", t = "2"
 Output: false
  

 Constraints:

 s.length == t.length
 1 <= s.length <= 105
 s and t only contain digits from '0' to '9'.
 */
#include <string>
#include <queue>
#include <vector>
#include <deque>

using std::deque;
using std::vector;
using std::queue;
using std::string;

class IsTransformable {

    /*
        1585.Check-If-String-Is-Transformable-With-Substring-Sort-Operations
        对于一个区间，操作之后最小的数字会跑到区间的最前面；如果把区间缩小一点，操作之后最小的数字依然会跑到这个区间的最前面。可见区间的大小，其实就是影响着最小数字的“迁移程度”。因此我们总结出，本题的操作，本质上就是“冒泡”：允许任何一个数字可以和它前面比它大的数字交换，并且能够连续操作，前移到所能到达的任何位置。

        分析下面这个例子

        0 1 2 3 4 5 6 7
        s: X X X 5 X X X X 
        t: 5 X X X X X X X 
        对于目标串t的第一个5会对应着s中的哪一个5呢？显然易见，我们会从s里面找出现的第一个5的位置和它配对，也就是idx=3位置。那么s[3]要挪到[0]的位置需要满足什么条件呢？那就是s[3]前面的数字不能有小于5的，否则s[3]这个数字就无法顺利挪到第一个位置。

        这就提示我们预处理所有的10种数字，将它们出现的idx按照顺序放在pos[digit]里面。此时我们只要查看pos[0]~pos[4]这些数字的第一次出现的位置，如果这个位置早于3，那么就违反了上面的要求，s[3]无法迁移到第一个位置。

        我们再接下来看一位：

        0 1 2 3 4 5 6 7
        s: X X X 5 X 6 X X 
        t: 5 6 X X X X X X 
        对于目标串t的第二位上的6，假设对应的s[5]上的6。根据之前的推理，钥匙s[5]能推进到第二位，所有小于6的数字都不能出现在idx=5的左边阻挡它的前进，除非是之前处理过的那个s[3]=5，因为它已经被迁移到了t[0]的位置，不影响s[5]=6的前进。所以我们只需要将pos[5]记载的第一个位置3提前移出，查看此时pos[0]~pos[5]这些数字的第一次出现的位置。如果这些位置都大于5，就不会阻挡s[5]=6的前进，否则就无法实现目标。

        所以这种算法的时间复杂度是O(N*C)，其中C就是10.

        本题有一个条件更宽松的原题：https://codeforces.com/contest/1187/problem/D 其中没有数字只有10种的限制。那么上述的方法就会退化成o(N^2)。我们可以用BIT或者线段树来改进。

        还是基于之前的结论：遍历t[j]，找到对应的s[i]，想要s[i]顺利到j的位置，需要所有小于s[i]的数字的idx不能早于i。所以我们可以给这些数字（枚举所有小于s[i]的数字、不包括已经处理过的）都更新一个leftLimit的限制。随着不断处理s[i]，这个数字的leftLimit会不断更新，趋势上会越来越严格（即越来越靠右）。如果发现对于某个s[i]而言，我们期望它移到的位置j要早于它被赋予的leftLimit，就注定s[i]无法实现移动，就返回false。

        这看上去依然是o(N^2)的方法。但可以优化的地方在于，我们将所有的数字排序之后，更新所有小于s[i]的数字的leftLimit，这是一个区间操作。可以用线段树或者BIT来化简到log(N)的时间复杂度。
    */
     bool isTransformable(string s, string t) 
    {
        int n = s.size();
        vector<deque<int>>pos(10);
        
        for (int i=0; i<n; i++)
        {            
            pos[s[i]-'0'].push_back(i);
        }

        for (int i=0; i<n; i++)
        {
            int num = t[i]-'0';            
            if (pos[num].empty()) return false;
            int idx = pos[num].front();
                        
            for (int digit = 0; digit < num; digit++)
                if (!pos[digit].empty() && pos[digit].front() < idx)
                    return false;
            
            pos[num].pop_front();
        }
        
        return true;        
    }

    
    
public:
    

    /*
        However do you sort the s, it can move the smaller digits to the left. but bigger number could not be moved to left. it will be keep into the right in a smaller subarry or whole string. 

        for any t[i] and s[j], t[i] == s[j], if any t[k] k < i and t[j] < t[i], and corresponding there is no t[k] in S, or t[j]'s index k is after S[j], k > j. 
        no matter how many sort, it wouldn't move t[k] in S ahead to s[j]. 
    
        for s (45623), and t (54236),  s(45) and t(54) is not possible case.
    */
    bool doit_gready(string s, string t) {
        
        vector<queue<int>> dp(10);
        
        for (auto i = 0; i < s.length(); i++)
            dp[s[i] - '0'].push(i);
        
        for(auto c : t) {
            
            int digit = c - '0';
            if (dp[digit].empty())
                return false;
            
            int pos = dp[digit].front();
            dp[digit].pop();
            
            for (auto i = 0; i < digit; i++)
                if (!dp[i].empty() && dp[i].front() < pos)
                    return false;
        }
        
        return true;
    }
    
    
    vector<int> next;
    
    bool isTransformable(string s, string t) {
        if (s.size() != t.size()) return false;
        
        next = vector<int>(10, 0);
        return internal(s, 0, t, 0);
    }
    
    bool internal(string& s, int sb, string& t, int tb) {
        while (tb < s.size()) {
            if (s[sb] == 'a')
                ++sb;
            else if (s[sb] == t[tb])
                ++sb, ++tb;
            else
                break;
        }
        
        if (tb == s.size()) return true;
        
        int cur;
        for(cur = std::max(sb, next[t[tb] - '0']); cur < s.size(); ++cur) {
            if (s[cur] == 'a') continue;
            
            if (s[cur] == t[tb]) {
                s[cur] = 'a';
                next[t[tb] - '0'] = cur + 1;
                break;
            } else if (s[cur] < t[tb]) {
                return false;
            }
        }
        
        if (cur == s.size()) return false;
        return internal(s, sb, t, tb+1);
    }
};


