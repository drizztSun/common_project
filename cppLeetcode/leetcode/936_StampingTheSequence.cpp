/*
 
 
 936. Stamping The Sequence
 
 
 You want to form a target string of lowercase letters.

 At the beginning, your sequence is target.length '?' marks.  You also have a stamp of lowercase letters.

 On each turn, you may place the stamp over the sequence, and replace every letter in the sequence with the corresponding letter from the stamp.  You can make up to 10 * target.length turns.

 For example, if the initial sequence is "?????", and your stamp is "abc",  then you may make "abc??", "?abc?", "??abc" in the first turn.  (Note that the stamp must be fully contained in the boundaries of the sequence in order to stamp.)

 If the sequence is possible to stamp, then return an array of the index of the left-most letter being stamped at each turn.  If the sequence is not possible to stamp, return an empty array.

 For example, if the sequence is "ababc", and the stamp is "abc", then we could return the answer [0, 2], corresponding to the moves "?????" -> "abc??" -> "ababc".

 Also, if the sequence is possible to stamp, it is guaranteed it is possible to stamp within 10 * target.length moves.  Any answers specifying more than this number of moves will not be accepted.

  

 Example 1:

 Input: stamp = "abc", target = "ababc"
 Output: [0,2]
 ([1,0,2] would also be accepted as an answer, as well as some other answers.)
 Example 2:

 Input: stamp = "abca", target = "aabcaca"
 Output: [3,0,1]
 
 
 
 
 
 Approach 1: Work Backwards
 Intuition
 Imagine we stamped the sequence with moves m_1, m_2, Now, from the final position target, we will make those moves in reverse order.

 Let's call the ith window, a subarray of target of length stamp.length that starts at i.
 Each move at position i is possible if the ith window matches the stamp.
 After, every character in the window becomes a wildcard that can match any character in the stamp.

 For example, say we have stamp = "abca" and target = "aabcaca". Working backwards, we will reverse stamp at window 1 to get "a????ca",
 then reverse stamp at window 3 to get "a??????", and finally reverse stamp at position 0 to get "???????".

 Algorithm

 Let's keep track of every window. We want to know how many cells initially match the stamp (our "made" list), and which ones don't (our "todo" list).
 Any windows that are ready (ie. have no todo list), get enqueued.

 Specifically, we enqueue the positions of each character. (To save time, we enqueue by character, not by window.)
 This represents that the character is ready to turn into a "?" in our working target string.

 Now, how to process characters in our queue? For each character, let's look at all the windows that intersect it, and update their todo lists.
 If any todo lists become empty in this manner (window.todo is empty), then we enqueue the characters in window.made that we haven't processed yet.

 Complexity Analysis

 Time Complexity: O(N(N-M)) where M, NM,N are the lengths of stamp, target.

 Space Complexity: O(N(N-M)).
 
 
 */
#include <vector>
#include <algorithm>
#include <string>
#include <deque>
#include <unordered_set>

using std::vector;
using std::string;
using std::deque;
using std::unordered_set;


class MovesToStamp {

    /*
        936.Stamping-The-Sequence
        周赛的时候想到的是递归。对于这一系列ｓｔａｍｐ的操作，只关注最后一次盖章：其实可以看成找到中间某处完全匹配的地方，将整个序列断成了两部分，能匹配的部分我们就替换成是"*****".
        这样我们将原来的问题分解为了两个子序列，可以再递归处理。其中如果遇到边界是星号的部分我们都认为能匹配上的。

        其实上面的想法再进一步的话，可以得到更优美的贪心解法。

        思想本质是：我们只要在当前的target中能够找到匹配stamp的片段，比如说是区间[a,b],我们就将标记这个操作为最后一步操作。
        然后无论我们怎么处理剩下的序列，当我们回过头来最终执行替换[a,b]的操作时，都能保证[a,b]是正确的。也就是说，无论怎么折腾剩下的，最终都不会影响[a,b]。
        同理，如果我们再在剩下的target里中能找到匹配stamp的片段，比如说[c,d]时，我们就将其标记为倒数第二次操作，那么无论再之后的操作如何，最终都不会影响[c,d]以及[a,b]。

        举个例子：

        target:
        XXXXabcabcdcdXXX

        operations:
        #N-0: XXXXXXXabcdXXXXX
        #N-1: XXXXabcd***XXXXX
        #N-2: XXXXXXX**abcdXXX
        ...
        当从下往上执行最后三步替换之后，一定能保证序列最终中间的部分是期望的abcabcdcd.原因在于，后面的操作会覆盖前面的操作，
        所以前面的操作(比如说第N-1次)只需要负责后面操作（第Ｎ次）覆盖不到的那部分即可(i.e. abc)，其他的反正都会被后面的操作覆盖(i.e. d)，当前的替换即使不正确也没关系。

        所以我们的策略是从上往下,只要能在当前序列中能找到匹配的，我们就将其置为星号。然后再剩下的序列里，只要能找到匹配的（其中如果序列中已经有星号则视为任意匹配），我们也立即将其置为星号。
        直至序列中所有的字符都已经置为星号为止。注意，最终的操作顺序则是反过来。
    */
    vector<int> movesToStamp(string stamp, string target) 
    {
        bool changed = 1;
        vector<int>results;
        
        while (changed==1)
        {
            changed = 0;
            for (int i=0; i<target.size(); i++)
            {
                if (check(stamp,target,i))
                {                    
                    for (int k=0; k<stamp.size(); k++)
                        target[i+k] = '*';       
                    results.push_back(i);
                    changed = 1;
                    break;
                }
            }
        }
        
        for (int i=0; i<target.size(); i++)        
            if (target[i]!='*') return {};
                            
        reverse(results.begin(),results.end());
        return results;
        
    }
    
    bool check(string&stamp, string&target, int pos)
    {
        int flag = 0;
        for (int i=0; i<stamp.size(); i++)
        {
            if (pos+i>=target.size()) return false;
            if (target[pos+i]=='*') continue;
            if (target[pos+i]!=stamp[i]) return false;
            flag = 1;
        }
        return flag;
    }

public:

    vector<int> doit_greedy(string stamp, string target) {
        int m = stamp.size(), n = target.size();
        vector<int> res;
        int count = 0;

        auto match = [](string s, string t) {
            int count = 0;
            for (int i = 0; i < s.size(); i++) {
                if (t[i] != '?') count++;
                if (t[i] != '?' && s[i] != t[i]) return 0;
            }
            return count;
        };
        
        while(count < n) {
            int onePass = 0;
            for (int i = 0; i <= n - m; i++) {
                string t = target.substr(i, m);
                int matched = match(stamp, t);
                if (matched) {
                    for (int j = i; j < i+m; j++)
                        target[j] = '?';
                    res.push_back(i);
                }
                onePass += matched;
            }
            if (onePass == 0) break;
            count += onePass;
        }
        if (count < n) return {};
        reverse(res.begin(), res.end());
        return res;
    }
    
    vector<int> movesToStamp(string stamp, string target) {
        
        vector<int> ans;
        
        auto check = [&](int pos) {
            
            bool flag = false;
            for (int i=0; i<stamp.size(); i++)
            {
                if (pos+i>=target.size()) return false;
                if (target[pos+i]=='*') continue;
                if (target[pos+i]!=stamp[i]) return false;
                flag = true;
            }
            return flag;
        };
        
        int t = stamp.length();
        bool found = true;
        
        while (found) {
            
            found = false;
            for (int i = 0; i < target.size(); i++) {
                if (check(i)) {
                    for (int k = 0; k < t; k++) target[i+k] = '*';
                    found = true;
                    ans.push_back(i);
                }
            }
        }
        
        for (int i = 0; i < target.size(); i++) {
            if (target[i] != '*') return {};
        }
        
        std::reverse(begin(ans), end(ans));
        return ans;
        
    }

    vector<int> doit(string stamp, string target) {
        
        vector<int> ans;
        deque<int> queue;
        int M = stamp.length(), N = target.length();
        vector<bool> done(N, false);
        vector<vector<unordered_set<int>>> A(N, vector<unordered_set<int>>(2));
        
        for (int i = 0; i < N - M + 1; i++) {
            
            for (int j = 0; j < M; j++){
                
                if (stamp[j] == target[i+j])
                    A[i][0].insert(i+j);
                else
                    A[i][1].insert(i+j);
            }
                
                
            if (A[i][1].empty()) {
                ans.push_back(i);
                for (int j = 0; j < M; j++) {
                    if (!done[i+j]) {
                        done[i+j] = true;
                        queue.push_back(i+j);
                    }
                }
            }
        }
            
        
        
        while (!queue.empty()) {
            
            int i = queue.front();
            
            for (int j = std::max(0, i - M + 1); j < std::min(i, N - M) + 1; j++) {
                
                if (A[j][1].count(i) != 0) {
                    
                    A[j][1].erase(i);
                    
                    if (A[j][1].empty()) {
                        ans.push_back(j);
                        for (auto s : A[j][0]) {
                            if (!done[s]) {
                                done[s] = true;
                                queue.push_back(s);
                            }
                        }
                    }
                }
                
            }
            queue.pop_front();
        }
        
        if (std::all_of(done.begin(), done.end(), [](bool r){
            return r == true;}) ) {
            std::reverse(ans.begin(), ans.end());
        } else {
            ans.clear();
        }
        
        return ans;
    }
    
    
    
    // best
    // Idea is to greedily match stamp with target with offset, ignoring already matched characters. Reverse the process idea from
    std::vector<int> doit2(std::string stamp, std::string target) {
        int const ns = stamp.size();
        int const nt = target.size();

        // result cache
        auto res = std::vector<int>();

        // check if we have stamped at certain positions already, if
        // so, no need to check if we should stamp here
        bool stamped[nt-ns+1];
        std::fill(stamped, stamped + (nt-ns+1), false);

        
        while (true) {

            bool keepGoing = false;
            auto vec = std::vector<int>();
            
            for (int i = 0; i<= nt-ns; ++i) {
                if (stamped[i]) {
                    continue;
                }
                
                int currentMatch = 0;
                for (int j = 0; j < ns; ++j) {
                    
                    if (target[i+j] == '*') {
                        if (currentMatch) {
                            break;
                        }
                    } else if (target[i+j] != stamp[j]) {
                        currentMatch = 0;
                        break;
                    } else {
                        ++currentMatch;
                    }
                }
                
                if (currentMatch ) {
                    res.push_back(i);
                    stamped[i] = true;
                    
                    for (int j = i; j < ns + i; ++j) {
                        target[j] = '*';
                    }
                    keepGoing = true;
                }
            }
            
            if (!keepGoing) {
                break;
            }
        }

        for (auto const& ch : target) {
            if (ch != '*') {
                return std::vector<int>();
            }
        }

        std::reverse(res.begin(), res.end());
        return res;
    }
};