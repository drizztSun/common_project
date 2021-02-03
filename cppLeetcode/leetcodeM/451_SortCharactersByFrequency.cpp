/*
 451. Sort Characters By Frequency
 
 Given a string, sort it in decreasing order based on the frequency of characters.

 Example 1:

 Input:
 "tree"

 Output:
 "eert"

 Explanation:
 'e' appears twice while 'r' and 't' both appear once.
 So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
 Example 2:

 Input:
 "cccaaa"

 Output:
 "cccaaa"

 Explanation:
 Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
 Note that "cacaca" is incorrect, as the same characters must be together.
 Example 3:

 Input:
 "Aabb"

 Output:
 "bbAa"

 Explanation:
 "bbaA" is also a valid answer, but "Aabb" is incorrect.
 Note that 'A' and 'a' are treated as two different characters.
 
 */
#include <unordered_map>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

using std::map;
using std::vector;
using std::string;
using std::unordered_map;


class FrequencySort {

public:

    string doit_bucket_sort(string s) {
        
        auto N = static_cast<int>(s.size());

        // Count frequencies
        int freq[256] = { 0 };
        for (auto ch : s)
            freq[ch]++;

        // Distribute in buckets
        vector<string> buckets(N + 1);
        for (int i = 0; i < 256; ++i)
            if(freq[i] != 0)
                buckets[N - freq[i]] += char(i);

        // Accumulate result
        string res;
        for (auto item : buckets)
            for (auto ch : item)
                res.append(freq[ch], ch);

        return res;
    }
    
    string doit_sort(string s) {

        unordered_map<char, int> buff;

        for (char c: s) {
            buff[c]++;
        }

        vector<std::pair<int, char>> chars;
        for (auto c : buff) {
            if (c.second != 0)
                chars.push_back({c.second, c.first});
        }

        std::sort(begin(chars), end(chars), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

        string res;
        for (auto c: chars) {
            //printf("%c, %d", c.second, c.first);
            while (c.first--)
                res += c.second;
        }

        return res;
    }
    
    string doit_heap(string s) {

        std::unordered_map<char, int> cnt;
        std::priority_queue<std::pair<int, char>, vector<std::pair<int, char>>, std::less<std::pair<int, char>>> qu;
        for (auto c: s)
            cnt[c]++;
        
        for (auto k : cnt) {
            qu.push(std::make_pair(k.second, k.first));
        }
        
        string res = "";
        while (!qu.empty()) {
            std::pair<int, char> pt = qu.top();
            for (; pt.first > 0; pt.first--)
                res += pt.second;
            qu.pop();
        }
        
        return res;
    }
};
