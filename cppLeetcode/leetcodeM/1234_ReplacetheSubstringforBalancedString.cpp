/*
1234. Replace the Substring for Balanced String

You are given a string containing only 4 kinds of characters 'Q', 'W', 'E' and 'R'.

A string is said to be balanced if each of its characters appears n/4 times where n is the length of the string.

Return the minimum length of the substring that can be replaced with any other string of the same length to make the original string s balanced.

Return 0 if the string is already balanced.

 

Example 1:

Input: s = "QWER"
Output: 0
Explanation: s is already balanced.
Example 2:

Input: s = "QQWE"
Output: 1
Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is balanced.
Example 3:

Input: s = "QQQW"
Output: 2
Explanation: We can replace the first "QQ" to "ER". 
Example 4:

Input: s = "QQQQ"
Output: 3
Explanation: We can replace the last 3 'Q' to make s = "QWER".
 

Constraints:

1 <= s.length <= 10^5
s.length is a multiple of 4
s contains only 'Q', 'W', 'E' and 'R'.
*/
#include <string>
#include <map>
#include <unordered_map>

using std::unordered_map;
using std::map;
using std::string;

class BalancedString {

    /*
    
        1234.Replace-the-Substring-for-Balanced-String
        解法１：
        比赛的时候我用的是二分法，尝试我们需要移除的substring的宽度ｋ，它的范围是[0,n]．二分的过程中，每次确定一个ｋ，就在s上滑过一个固定长度ｋ的窗口，查看滑窗是否在哪个位置的时候满足题意．

        那么如何判断满足题意呢？令s里的字符总数是n，那么我们期望最终每种字符的个数恰好是n/4. 我们只要保证滑窗外的每种字符的个数不超过n/4，那么即说明这样的滑窗可以满足题意。
        为什么呢？显然，如果滑窗外的某种字符的个数超过了n/4，那么无论滑窗里面怎么搞，最终无法使得该字符的总数符合期望的n/4。相反，只要滑窗外的每种字符的个数都不超过n/4，那么滑窗内就可以自由安排，总能使得最终每种字符的总数恰好是n/4.

        这个复杂度其实是nlog(n).

        解法２：
        本题其实用双指针来做更简单，时间复杂度为o(n). 根据解法1的分析，我们其实只要找到一段窗口，使得窗口外的词频统计满足每种字母的频率都不超过n/4.

        基于这种算法，滑窗的两个指针是可以交替移动的．比如说当慢指针为i,快指针移动到j，满足条件．那么下一步慢指针移动到i+1,而快指针则不用动．为什么快指针不需要考察小于ｊ的位置呢？其实如果窗口[i+1,k]满足条件的话（k<j)，
        那么一定有[i,k]也满足条件，所以快指针根本就不会走到j的位置了．所以我们可以保证，并没有一个k<j使得[i+1,k]满足条件．所以快指针不需要回调．

        所以我们只要遍历左边界i，相应地单向朝右移动右边界j，使得[i:j]是一个满足条件的区间。探索所有的这样的区间，找一个最短的。
    */
    int n;
    unordered_map<char,int>count;
public:
    int doit_binary_search(string s) 
    {
        n = s.size();        
        for (auto ch:s)
            count[ch] += 1;
        int flag = 1;
        for (auto x: count)
            if (x.second!=n/4)
                flag = 0;
        if (flag==1) return 0;

        int left = 1, right = n;
        while (left<right)
        {
            int mid = left+(right-left)/2;
            if (isOK(mid, s))
                right = mid;
            else
                left = mid+1;
        }
        return left;
    }

    bool isOK(int k, string& s)
    {
        unordered_map<char,int>sum;
        for (int i=0; i<n; i++)
        {
            sum[s[i]]+=1;
            if (i>=k)
                sum[s[i-k]]-=1;

            int flag = 1;
            for (auto x: count)
            {
                char ch = x.first;
                if (count[ch]-sum[ch] > n/4)
                {
                    flag  = 0;
                    break;
                }
            }
            if (flag) return true;                    
        }
        return false;
    }

    //int n;
    //unordered_map<char,int>count;
public:
    int doit_(string s) 
    {
        n = s.size();        
        for (auto ch:s)
            count[ch] += 1;
        int flag = 1;
        for (auto x: count)
            if (x.second!=n/4)
                flag = 0;
        if (flag==1) return 0;

        int j = 0;
        unordered_map<char,int>sum;
        int ret = INT_MAX;
        for (int i=0; i<n; i++)
        {
            while (j<n && !isOK(sum))
            {
                sum[s[j]]+=1;
                j++;
            }
            if (isOK(sum))
                ret = min(ret, j-i);
            sum[s[i]] -= 1;
        }
        return ret;
    }

    bool isOK(unordered_map<char,int>&sum)
    {        
        for (auto x: count)
        {
            char ch = x.first;
            if (count[ch]-sum[ch] > n/4)
                return false;
        }
        return true;
    }

public:

    /*
        Intuition
        We want a minimum length of substring,
        which leads us to the solution of sliding window.
        Specilly this time we don't care the count of elements inside the window,
        we want to know the count outside the window.


        Explanation
        One pass the all frequency of "QWER".
        Then slide the windon in the string s.

        Imagine that we erase all character inside the window,
        as we can modyfy it whatever we want,
        and it will always increase the count outside the window.

        So we can make the whole string balanced,
        as long as max(count[Q],count[W],count[E],count[R]) <= n / 4.


        Important
        Does i <= j + 1 makes more sense than i <= n.
        Strongly don't think, and i <= j + 1 makes no sense.

        Answer the question first:
        Why do we need such a condition in sliding window problem?

        Actually, we never need this condition in sliding window solution
        (Check all my other solutions link at the bottom).

        Usually count the element inside sliding window,
        and i won't be bigger than j because nothing left in the window.

        The only reason that we need a condition is in order to prevent index out of range.
        And how do we do that? Yes we use i < n

        Does i <= j + 1 even work?
        When will i even reach j + 1?
        Does i <= j + 1 work better than i <= j?

        Please upvote for this important tip.
        Also let me know if there is any unclear, glad to hear different voices.
        But please, have a try, and show the code if necessary.

        Some people likes to criticize without even a try,
        and solve the problem by talking.
        Why talk to me? Talk to the white board.


        Complexity
        Time O(N), one pass for counting, one pass for sliding window
        Space O(1)
    */
    int doit_slidingwindow(string s) {
        unordered_map<int, int> count;
        int n = s.length(), res = n, i = 0, k = n / 4;
        for (int j = 0; j < n; ++j) {
            count[s[j]]++;
        }
        for (int j = 0; j < n; ++j) {
            count[s[j]]--;
            while (i < n && count['Q'] <= k && count['W'] <= k && count['E'] <= k && count['R'] <= k) {
                res = std::min(res, j - i + 1);
                count[s[i++]] += 1;
            }
        }
        return res;
    }

    int doit_slidingwindow(string s) {
        
        int n = s.length(), res = n;
        char kind[4] = {'Q', 'W', 'E', 'R'};
        int ave = s.length() / 4;
        unordered_map<char, int> cnt;
        for (auto c: s) {
            cnt[c]++;
        }
        
        if (cnt['Q'] <= ave && cnt['W'] <= ave && cnt['E'] <= ave && cnt['R'] <= ave) return 0;
        
        for (int i = 0, j = 0; i < s.length(); i++) {
            
            cnt[s[i]]--;
            
            while (j <= i && cnt['Q'] <= ave && cnt['W'] <= ave && cnt['E'] <= ave && cnt['R'] <= ave) {
                res = std::min(res, i - j + 1);
                cnt[s[j++]]++;
            }
        }
        
        return res;
    }

    int doit_slidingwindow(string s) {
        
        int res = s.length();
        char kind[4] = {'Q', 'W', 'E', 'R'};
        int ave = s.length() / 4;
        unordered_map<char, int> cnt;
        for (auto c: s) {
            cnt[c]++;
        }
        
        unordered_map<char, int> diff;
        int length = 0;
        for (auto it: cnt) {
            if (it.second > ave) {
                diff.emplace(it.first, it.second - ave);
                length += it.second - ave;
            }
        }
        
        if (diff.empty()) return 0;
        
        unordered_map<char, int> window;
        int curlength = 0;
        for (int i = 0, j = 0; i < s.length(); i++) {
            
            if (diff.count(s[i]) > 0) {
                if (++window[s[i]] <= diff[s[i]]) {
                    curlength++;
                }
            }
            
            
            while (curlength == length) {
                res = std::min(res, i - j + 1);
                if (diff.count(s[j]) > 0) {
                    if (--window[s[j]] < diff[s[j]]) {
                        curlength--;
                    }
                }
                j++;
            }
            
        }
        
        return res;
    }
    
    int doit_slidingwindow(string s) {
        
        map<int, int> cnt;
        for (auto c: s)
            cnt[c]++;
        
        int larger = 0;
        int ave = s.size() / 4;
        for (auto c : "QWER") {
            if (cnt[c] > ave) larger += 1;
        }
        
        if (larger == 0) return 0;
        
        int i = 0, ans = s.size();
        for (int j = 0; j < s.size(); j++) {
            
            cnt[s[j]] -= 1;
            if (cnt[s[j]] == ave)
                larger -= 1;
            
            while (i <= j && larger == 0) {
                ans = std::min(ans, j - i + 1);
                cnt[s[i]] += 1;
                if (cnt[s[i]] == ave + 1) {
                    larger += 1;
                }
                i += 1;
            }
        }
        
        return ans;
    }

    int doit_slidingwindow(string s) {

        int len = s.length();
        int count[4] = {0,0,0,0}; // Q:0 , W:1 , E:2, R:3

        auto checker =[](int*count , int*current)
        {
            for(int i=0;i<4;++i)
                if(count[i] && current[i]<count[i]) return 0;
            return 1;
        };

        auto counter = [](int *count,char &ch,bool sign) {
            int val=1;
            if(sign) val=-1;
            
            if(ch=='Q')
                count[0]+=val;
            else if(ch=='W')
                count[1]+=val;
            else if(ch=='E')
                count[2]+=val;
            else
                count[3]+=val;
        };


        // finding count of characters
        for(int i=0;i<len;++i)
           counter(count,s[i],0);
        
        int ans = INT_MAX, val = len/4; // val is the required number of count of each character
        
        for(int i=0;i<4;++i)     // here we try to find count of char that occur more than len/4 times as they can be replaced to compensate others
            count[i] -= val;
        
        // check to see if there are any extra characters
        int b=0;
        for(;b<4;++b)
            if(count[b]>0) break;
        
        if(b==4) return 0; // no extra chars
        
        b=0;
        int current[4] = {0,0,0,0};
        
        // we need to find the smallest substring that contains extra characters left in count array
        for(int i=0;i<len;++i)
        {
            counter(current,s[i],0);
            if(checker(count,current))
            {
                while(checker(count,current))
                {
                    ans = std::min(ans,i-b+1);
                    counter(current,s[b],1);
                    b++;
                }
            }
        }
        return ans;
    }
};