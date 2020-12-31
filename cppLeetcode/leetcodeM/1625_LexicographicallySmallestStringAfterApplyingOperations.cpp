/*
1625. Lexicographically Smallest String After Applying Operations

You are given a string s of even length consisting of digits from 0 to 9, and two integers a and b.

You can apply either of the following two operations any number of times and in any order on s:

Add a to all odd indices of s (0-indexed). Digits post 9 are cycled back to 0. For example, if s = "3456" and a = 5, s becomes "3951".
Rotate s to the right by b positions. For example, if s = "3456" and b = 1, s becomes "6345".
Return the lexicographically smallest string you can obtain by applying the above operations any number of times on s.

A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "0158" is lexicographically smaller than "0190" because the first position they differ is at the third letter, and '5' comes before '9'.

 

Example 1:

Input: s = "5525", a = 9, b = 2
Output: "2050"
Explanation: We can apply the following operations:
Start:  "5525"
Rotate: "2555"
Add:    "2454"
Add:    "2353"
Rotate: "5323"
Add:    "5222"
​​​​​​​Add:    "5121"
​​​​​​​Rotate: "2151"
​​​​​​​Add:    "2050"​​​​​​​​​​​​
There is no way to obtain a string that is lexicographically smaller then "2050".
Example 2:

Input: s = "74", a = 5, b = 1
Output: "24"
Explanation: We can apply the following operations:
Start:  "74"
Rotate: "47"
​​​​​​​Add:    "42"
​​​​​​​Rotate: "24"​​​​​​​​​​​​
There is no way to obtain a string that is lexicographically smaller then "24".
Example 3:

Input: s = "0011", a = 4, b = 2
Output: "0011"
Explanation: There are no sequence of operations that will give us a lexicographically smaller string than "0011".
Example 4:

Input: s = "43987654", a = 7, b = 3
Output: "00553311"
 

Constraints:

2 <= s.length <= 100
s.length is even.
s consists of digits from 0 to 9 only.
1 <= a <= 9
1 <= b <= s.length - 1

*/
#include <string>
#include <queue>
#include <unordered_set>

using std::queue;
using std::unordered_set;
using std::string;


class FindLexSmallestString {

public:


    /*
    Explaination:
    the question asks to find the smallest string given an original string, and two type of operation that we can perform
    we can perform the operations on the string unlimited amount of time, so it is hard to simulate that process(when do we stop applying the operation?)
    But after some observation we can see that if we apply operation A or B continously on the string, it will end up like a loop

    let's say s = 5252, a = 5
    if we apply A (Add a to all odd indices of s (0-indexed)):
    5252 -> 5757 -> 5252 -> 5757
    --- loop1--- ----loop2---
    if a = 3
    5252 -> 5555 -> 5858 ->5151 -> 5454 -> 5757 -> 5050 -> 5353 -> 5656 -> 5959 -> 5252 (we are back!)

    The chain will no exceed 10, it will eventually loops back to the original string
    so does the operation B (Rotate s to the right by b positions), if u keep applying the same operation it will goes like a loop as well , and it will not exceed N( N is the length of s the worst case is when b is 1, and u can shift N - 1 times)
    after these thought process , we can tell that the states are not infinite, we just need to find out a way to enumerate all possibilities, what I did in the following code is to perform a BFS and enumerate all possible sequences
    */
    string doit_bfs(string s, int a, int b) {
        string smallest = s;
        const int N = s.size();
        queue<string> q;
        unordered_set<string> seen;

        q.push(s);
        seen.insert(s);
        while (!q.empty()) {
            string cur = q.front(); q.pop();
            if (cur < smallest) smallest = cur; // we found a new state, lets check if it's the smallest 
            for (int i = 1; i < N; i += 2)  // operation A
                cur[i] = ((cur[i] - '0') + a) % 10 + '0';
            if (seen.insert(cur).second) q.push(cur); // only insert if this is a new state (otherwise we will stuck in the loop)
            cur = (cur.substr(N - b) + cur.substr(0, N - b)); // operation B
            if (seen.insert(cur).second) q.push(cur); // same 
        }
        return smallest;
    }


    string findLexSmallestString(string s, int a, int b) {

        unordered_set<string> mark;
        string ans = s;

        std::function<string(string, int)> add = [&](string s, int a) {
            int n = s.size();
            bool flag = true;
            for(int i = n-1; i >= 0; i--) {
                if(flag) {
                    int val = a + (s[i] - '0');
                    val = val % 10;
                    s[i] = val + '0';
                    flag = false;
                }
                else
                    flag = true;
            }
            return s;
        };

        std::function<void(string, int, int)> dfs = [&](string s, int a, int b) {
            if(mark.find(s) != mark.end())
                return;
            mark.insert(s);
            ans = min(ans, s);
            dfs(s.substr(b) + s.substr(0, b), a, b);
            dfs(add(s, a), a, b);
        };


        dfs(s, a, b);
        return ans;
    }

    /*

    */
    string findLexSmallestString(string s, int a, int b) {

        auto gcd = [](int m, int n) {
            while(n != 0) { 
                int r = m % n; 
                m = n; 
                n = r; 
            } 
            return m;
        };
        
        auto add = [](string& s, int a, bool odd) {
            int i = (odd == false ? 0 : 1);
            for (i; i < s.size(); i += 2) {
                char tmp = (s[i] - '0' + a) % 10 + '0';
                s[i] = tmp;
            }
        };

        int add_times = 10 / gcd(10, a);
        int rotate_times = s.size() / gcd(s.size(), b);
        string res = s;

        for (int i = 0; i < add_times; i++) {
            if (b % 2 != 0) {
                string tmp = s;
                for (int j = 0; j < add_times; j++) {
                    string tmp2 = tmp;
                    for (int k = 0; k < rotate_times; k++) {
                        tmp2 = tmp2.substr(tmp2.size()-b)+tmp2.substr(0,tmp2.size()-b);
                        if (res.compare(tmp2) > 0) {
                            res = tmp2;
                        }
                    }
                    add(tmp, a, false);
                }
            } else {
                string tmp = s;
                for (int j = 0; j < rotate_times; j++) {
                    tmp = tmp.substr(tmp.size()-b)+tmp.substr(0,tmp.size()-b);
                    if (res.compare(tmp) > 0) {
                        res = tmp;
                    }
                }
            } 
            add(s, a, true);
        }
        return res;
    }

    string doit_bfs(string s, int a, int b) {
        
        auto addString = [](string s, int a)
        {
            for(int i=1; i<s.length(); i += 2)
            {
                int x = s[i] - '0';
                x = (x + a) % 10;
                s[i] = x + '0';
            }
            return s;
        };

        auto rotateString = [](string s, int b)
        {
            for(int i=0; i<b; i++)
            {
                char c = s[s.length()-1];
                s.pop_back();
                s.insert(s.begin(), c);
            }
            return s;
        };

        unordered_set<string> stringSet;        //to store visited strings
        queue<string> q;
        q.push(s);
        stringSet.insert(s);
        string ans = s;

        while(!q.empty())
        {
            string temp = q.front();
            q.pop();
            ans = min(ans, temp);
            string rotate = rotateString(temp, b);
            string add = addString(temp, a);
            if(stringSet.find(rotate) == stringSet.end())
            {
                q.push(rotate);
                stringSet.insert(rotate);
            }
            if(stringSet.find(add) == stringSet.end())
            {
                q.push(add);
                stringSet.insert(add);
            }
        }
        return ans;
    }

    string doit_bfs_1(string s, int a, int b) {
        int n = s.length();
        
        int vis[105];
        memset(vis, false, sizeof(vis));
        int i = 0;
        string best = s;
        while (!vis[i]){
            vis[i] = true;
            string seq = s.substr(i) + s.substr(0, i);
            string seq_best = seq;

            if (b%2==0){
                bool addVis[15];
                memset(addVis, false, sizeof(addVis));
                int j = 0;
                while (!addVis[j]){
                    addVis[j] = true;
                    string temp = seq;
                    for (int k=1; k<n; k+=2){
                        temp[k] = (temp[k]-'0'+j)%10 + '0';
                    }
                    if (seq_best.compare(temp) > 0) seq_best = temp;
                    j = (j+a)%10;
                }
            } else {
                bool addVis[15];
                memset(addVis, false, sizeof(addVis));
                int j = 0;
                while (!addVis[j]){
                    addVis[j] = true;
                    string temp = seq;
                    for (int k=1; k<n; k+=2){
                        temp[k] = (temp[k]-'0'+j)%10 + '0';
                    }
                    if (seq_best.compare(temp) > 0) seq_best = temp;
                    j = (j+a)%10;
                }
                
                string new_seq = seq_best;
                memset(addVis, false, sizeof(addVis));
                j = 0;
                while (!addVis[j]){
                    addVis[j] = true;
                    string temp = new_seq;
                    for (int k=0; k<n; k+=2){
                        temp[k] = (temp[k]-'0'+j)%10 + '0';
                    }
                    if (seq_best.compare(temp) > 0) seq_best = temp;
                    j = (j+a)%10;
                }
            }
            
            if (best.compare(seq_best) > 0) best = seq_best;
            
            i = (i+b)%n;
        }
        return best;
    }
};
