/*
767. Reorganize String

Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.

If possible, output any possible result.  If not possible, return the empty string.

Example 1:

Input: S = "aab"
Output: "aba"
Example 2:

Input: S = "aaab"
Output: ""
Note:

S will consist of lowercase letters and have length in range [1, 500].

*/
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <set>

using std::multiset;
using std::priority_queue;
using std::vector;
using std::string;
using std::unordered_map;



class ReorganizeString {

public:

    /*
        767.Reorganize-String
        本题本质上就是 358. Rearrange String k Distance Apart 当k=2时的特例。

        基本的思想就是尽量使用当前频次最多的两个字母。如果不优先使用频次最多的字母，则手头该字母会越积越多。当最终手头只剩一种字母时，构造就会失败。

        数据结构上，维护一个优先队列来实时得到当前频次最多的两个字母。只要每次能取两个不同字母组成一对加入字符串，可以保证顺利构造结果。记得使用完之后，将这两种字母频次减一之后再放入队列之中。

        失败的条件：队列中只有一种字母，并且字母的频次大于等于2.
    */
    string doit_heap(string S) 
    {
        unordered_map<char,int> Map;
        for (auto ch:S) Map[ch]++;

        priority_queue<std::pair<int,char>> pq;        
        for (auto a:Map) pq.push({a.second,a.first});        
        
        string result;
        while (!pq.empty())
        {
            int k = std::min(2, static_cast<int>(pq.size()));
            vector<std::pair<int,char>> temp;
            
            for (int i = 0; i < k; i++)
            {
                int ch = pq.top().second;
                int num = pq.top().first;
                pq.pop();
                result += ch;
                num--;
                if (num!=0) 
                    temp.push_back({num,ch});                
            }
            
            if (k<2 && temp.size()>0) return "";
            
            for (auto a:temp) pq.push(a);
        }
        return result;
    }

    string doit_heap_1(string S) {
        
        unordered_map<char, int> cnt;
        for (auto c: S) cnt[c]++;
        
        //multiset<std::pair<int, char>> pq;
        priority_queue<std::pair<int, char>> pq;
        for (auto x: cnt) pq.push({x.second, x.first});
        
        string ans;
        while (!pq.empty()) {
            
            auto it1 = pq.top(); pq.pop();
            ans.push_back(it1.second);
            if (pq.empty()) {
                return it1.first > 1 ? "": ans; 
            }
            
            auto it2 = pq.top(); pq.pop();
            ans.push_back(it2.second);
            
            if (it1.first > 1)
                pq.push({it1.first-1, it1.second});
            
            if (it2.first > 1)
                pq.push({it2.first-1, it2.second});
        }
        
        return ans;
    }

    /*

        Approach #2: Greedy with Heap [Accepted]
        Intuition
        
        One consequence of the reasoning in Approach #1, is that a greedy approach that tries to write the most common letter (that isn't the same as the previous letter written) will work.
        
        The reason is that the task is only impossible if the frequency of a letter exceeds (N+1) / 2. Writing the most common letter followed by the second most common letter keeps this invariant.
        
        A heap is a natural structure to repeatedly return the current top 2 letters with the largest remaining counts.
        
        Approach
        
        We store a heap of (count, letter). [In Python, our implementation stores negative counts.]
        
        We pop the top two elements from the heap (representing different letters with positive remaining count), and then write the most frequent one that isn't the same as the most recent one written. After, we push the correct counts back onto the heap.
        
        Actually, we don't even need to keep track of the most recent one written. If it is possible to organize the string, the letter written second can never be written first in the very next writing.
        
        At the end, we might have one element still on the heap, which must have a count of one. If we do, we'll add that to the answer too.
        
        Proof of Invariant
        
        Complexity Analysis

        Time Complexity: O(NlogA)), where N is the length of S, and A is the size of the alphabet. If A is fixed, this complexity is O(N).
        
        Space Complexity: O(A). If A is fixed, this complexity is O(1).
    */
    string doit_heap_2(string S) {
        
        unordered_map<char, int> cnt;
        for (auto c: S) cnt[c]++;
        
        multiset<std::pair<int, char>> pq;
        //priority_queue<std::pair<int, char>> pq;
        for (auto x: cnt) pq.insert({x.second, x.first});
        
        string ans;
        while (!pq.empty()) {
            
            auto it1 = *pq.rbegin(); 
            pq.erase(it1);
            ans.push_back(it1.second);
            if (pq.empty()) {
                return it1.first > 1 ? "": ans; 
            }
            
            auto it2 = *pq.rbegin(); 
            pq.erase(it2);
            ans.push_back(it2.second);
            
            if (it1.first > 1)
                pq.insert({it1.first-1, it1.second});
            
            if (it2.first > 1)
                pq.insert({it2.first-1, it2.second});
        }
        
        return ans;
    }


};