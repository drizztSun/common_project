/*
763. Partition Labels



A string S of lowercase English letters is given. 
We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

 

Example 1:

Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
 

Note:

S will have length in range [1, 500].
S will consist of lowercase English letters ('a' to 'z') only.

*/
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class PartitionLabels {

public:
    
    vector<int> doit_sort(string S) {

        unordered_map<char, std::pair<int, int>> counter;
        for (int i = 0; i < S.size(); i++) {
            if (counter.find(S[i]) == counter.end())
                counter[S[i]] = {i, i};
            else
                counter[S[i]].second = i;
        }

        vector<std::pair<int, int>> buff;
        for (auto c: counter) {
            buff.push_back({c.second.first, c.second.second});
        }

        std::sort(begin(buff), end(buff), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });

        int s = 0, e = 0;
        vector<int> ans;
        for (auto c : buff) {

            if (c.first > e) {
                ans.push_back(e - s + 1);
                s = c.first, e = c.second;
            } else if (c.second > e)
                e = c.second;
        }
        ans.push_back(e - s + 1);
        return ans;
    }

    /*
        Approach 1: Greedy
        Intuition

        Let's try to repeatedly choose the smallest left-justified partition. Consider the first label, say it's 'a'. The first partition must include it, and also the last occurrence of 'a'. 
        However, between those two occurrences of 'a', there could be other labels that make the minimum size of this partition bigger. 
        For example, in "abccaddbeffe", the minimum first partition is "abccaddb". 
        
        This gives us the idea for the algorithm: For each letter encountered, process the last occurrence of that letter, extending the current partition [anchor, j] appropriately.

        Algorithm

        We need an array last[char] -> index of S where char occurs last. Then, let anchor and j be the start and end of the current partition. 
        If we are at a label that occurs last at some index after j, we'll extend the partition j = last[c]. 
        If we are at the end of the partition (i == j) then we'll append a partition size to our answer, and set the start of our new partition to i+1.


        Complexity Analysis

        Time Complexity: O(N), where NN is the length of SS.

        Space Complexity: O(1) to keep data structure last of not more than 26 characters.
    
    */
    vector<int> doit_greedy(string S) {

        unordered_map<char, int> lastPos;
        for (int i = 0; i < S.size(); i++) {
            lastPos[S[i]] = i;
        }

        vector<int> ans;
        int end = 0, start = 0;
        for (int i = 0; i < S.size(); i++) {

            end = std::max(end, lastPos[S[i]]);

            if (i == end) {
                ans.push_back(end - start + 1);
                start = i + 1;
            }
        }

        return ans;
    }
};

