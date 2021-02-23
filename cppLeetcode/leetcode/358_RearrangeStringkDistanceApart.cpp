/*
358. Rearrange String k Distance Apart

Given a non-empty string s and an integer k, rearrange the string such that the same characters are at least distance k from each other.

All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".

Example 1:

Input: s = "aabbcc", k = 3
Output: "abcabc" 
Explanation: The same letters are at least distance 3 from each other.
Example 2:

Input: s = "aaabc", k = 3
Output: "" 
Explanation: It is not possible to rearrange the string.
Example 3:

Input: s = "aaadbbcc", k = 2
Output: "abacabcd"
Explanation: The same letters are at least distance 2 from each other.
*/

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using std::vector;
using std::unordered_map;
using std::string;
using std::priority_queue;


class RearrangeString {

public:

    /*

        358.Rearrange-String-k-Distance-Apart
        构建priority_queue<pair<int,char>>q; q的元素表示字符及其频次。注意到priority_queue默认大顶堆，自动按照频次从大到小排列。

                unordered_map<char,int>Map;
                for (int i=0; i<s.size(); i++)
                    Map[s[i]]++;
                
                priority_queue<pair<int,char>>q;
                for (auto a:Map)
                    q.push({a.second,a.first});
        每次取q中的前K个元素（每个元素代表不同的字符）加入临时数组temp；取完后将这些temp里的元素的个数减一后再放回q中。直至某一回合，如果pq的字符种类个数小于K，但是该轮结束后temp非空，说明我们还需要往result里加字符，这样就会违法K个相邻字符不能有相同字符的规则，返回空。

                while (!pq.empty())
                {
                    int n = min(k, (int)pq.size());
                    vector<pair<int,char>>temp;
                    
                    for (int i=0; i<n; i++)
                    {
                        int num = pq.top().first;
                        int ch = pq.top().second;
                        pq.pop();
                        result+=ch;
                        num--;
                        if (num!=0) temp.push_back({num,ch});
                    }
                    if (n<k && temp.size()>0) return "";
                    for (auto a:temp) pq.push(a);
                }
    */

    string doit_heap(string s, int k) {
        
        if (k == 0) return s;
        
        unordered_map<char, int> counter;
        for (const auto c: s) counter[c]++;

        priority_queue<std::pair<int, char>> pq;
        for (const auto& it: counter)
            pq.push({it.second, it.first});

        string ret;

        while (!pq.empty()) {

            if (pq.size() < k && pq.top().first > 1) return "";

            vector<std::pair<int, char>> tmp;
            int cnt = std::min(k, static_cast<int>(pq.size()));

            for (int i = 0; i < cnt; i++) {
                ret.push_back(pq.top().second);
                tmp.push_back(pq.top());
                pq.pop();
            }

            for (auto x: tmp) {
                if (x.first > 1)
                    pq.push({x.first-1, x.second});
            }
        } 

        return ret;
    }
};