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
#include <queue>
#include <string>
#include <vector>

using namespace std;


class FrequencySort {
public:
    string doit_heap(string s) {
        std::unordered_map<char, int> cnt;
        std::priority_queue<std::pair<int, char>, vector<std::pair<int, char>>, less<std::pair<int, char>>> qu;
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
