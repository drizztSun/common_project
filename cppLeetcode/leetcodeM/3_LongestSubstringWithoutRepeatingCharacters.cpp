/*

3. Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without repeating characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
Example 4:

Input: s = ""
Output: 0
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.

*/
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;

class LengthOfLongestSubstring {

    /*
        003.Longest Substring Without Repeating Characters
        解法1：
        双指针的基础题。用vector<int>Map(256,0)来模拟字符的Hash表。

        如果Map[s[j]]==0，移动右指针将Map[s[j]]=1； 否则移动左指针，将Map[s[i]]=0。

        解法2：
        对于上述的方法，左指针的前移其实可以跳跃，以加快效率。

        对于Map[s[j]]已经有记录的情况，此时左指针可以调到Map[s[j]]+1的地方。但是注意，这个地方可能还不及i本身，所以最终左指针的跳跃应该是max(i,Map[s[j]]+1)
    
    */
    int lengthOfLongestSubstring(string s) 
    {
        unordered_map<int,int>Map;
        int i=0;
        int result = 0;
        for (int j=0; j<s.size(); j++)
        {
            if (Map.find(s[j])!=Map.end())
                i = std::max(i,Map[s[j]]+1);
            Map[s[j]] = j;            
            result = std::max(result,j-i+1);
        }
        return result;
    }

    int lengthOfLongestSubstring(string s) 
    {
        vector<int>Map(256,0);
        int i=0;
        int j=0;
        int result=0;
        
        while (j<s.size())
        {
            if (Map[s[j]]==0)
            {
                Map[s[j]]=1;
                j++;
            }
            else if (Map[s[j]]==1)
            {
                Map[s[i]]=0;
                i++;
            }
            
            result = max(result,j-i);
        }
        
        return result;
        
    }

public:

    /*
        Approach 2: Sliding Window
        Algorithm

        The naive approach is very straightforward. But it is too slow. So how can we optimize it?

        In the naive approaches, we repeatedly check a substring to see if it has duplicate character. But it is unnecessary. If a substring s_{ij} from index i to j−1 is already checked to have no duplicate characters. 
        We only need to check if s[j] is already in the substring s_{ij}

        To check if a character is already in the substring, we can scan the substring, which leads to an O(n^2) algorithm. But we can do better.

        By using HashSet as a sliding window, checking if a character in the current can be done in O(1).

        A sliding window is an abstract concept commonly used in array/string problems. A window is a range of elements in the array/string which usually defined by the start and end indices, i.e. [i, j)[i,j) (left-closed, right-open). A sliding window is a window "slides" its two boundaries to the certain direction. For example, if we slide [i, j)[i,j) to the right by 11 element, then it becomes [i+1, j+1)[i+1,j+1) (left-closed, right-open).

        Back to our problem. We use HashSet to store the characters in current window [i, j) (j=i initially). Then we slide the index j to the right. If it is not in the HashSet, we slide jj further. Doing so until s[j] is already in the HashSet. At this point, we found the maximum size of substrings without duplicate characters start with index ii. If we do this for all ii, we get our answer.


        Complexity Analysis

        Time complexity : O(2n) = O(n)O(2n)=O(n). In the worst case each character will be visited twice by ii and jj.

        Space complexity : O(min(m, n))O(min(m,n)). Same as the previous approach. We need O(k) space for the sliding window, 
        where k is the size of the Set. The size of the Set is upper bounded by the size of the string nn and the size of the charset/alphabet m.
    */
    int doit_slidingwindow(string s) {
        int n = s.length();
        unordered_set<char> buf;
        int i = 0, j = 0, ans = 0;
        
        while (i < n && j < n) {
            
            if (buf.count(s[j]) == 0) {
                
                buf.insert(s[j++]);
                ans = std::max(ans, j - i);
            } else {
                buf.erase(s[i++]);
            }
            
        }

        return ans;
    }
        

    }

    /*
        Approach 3: Sliding Window Optimized
        The above solution requires at most 2n steps. In fact, it could be optimized to require only n steps. Instead of using a set to tell if a character exists or not, we could define a mapping of the characters to its index. 
        Then we can skip the characters immediately when we found a repeated character.

        The reason is that if s[j]s[j] have a duplicate in the range [i, j) with index j, we don't need to increase ii little by little. 
        We can skip all the elements in the range [i, j'] and let i to be j' + 1 directly.

        Java (Using HashMap)


        Here is a visualization of the above code.

        Java (Assuming ASCII 128)

        The previous implements all have no assumption on the charset of the string s.

        If we know that the charset is rather small, we can replace the Map with an integer array as direct access table.

        Commonly used tables are:

        int[26] for Letters 'a' - 'z' or 'A' - 'Z'
        int[128] for ASCII
        int[256] for Extended ASCII
    */
    int doit_hashtable(string s) {
        

        unordered_map<char, int> buf;
        int cur_len = 0, max_len = 0;

        for (int i = 0; i < s.length(); i++) {

            if (buf.count(s[i])) {

                if (i - buf[s[i]] <= cur_len) {
                    cur_len = i - buf[s[i]] - 1;
                }
            }

            cur_len++;
            buf[s[i]] = i;
            max_len = std::max(max_len, cur_len);
        }

        return max_len;
    }
};