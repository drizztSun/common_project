/*
424. Longest Repeating Character Replacement

Given a string s that consists of only uppercase English letters, you can perform at most k operations on that string.

In one operation, you can choose any character of the string and change it to any other uppercase English character.

Find the length of the longest sub-string containing all repeating letters you can get after performing the above operations.

Note:
Both the string's length and k will not exceed 104.

Example 1:

Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.
 

Example 2:

Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.

*/


#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::vector;
using std::unordered_map;
using std::string;


class CharacterReplacement {

    /*
        424.Longest-Repeating-Character-Replacement
        本题的本质就是用一个滑动窗口，查找最长的sub array，使得其最多含有ｋ-1个与majority不相同的字符．这里majority指的是窗口中出现最多的那个字符．

        很显然，我们需要一个hash map或者字典来存放每个字符出现的次数．在不断拓宽窗口的过程中，如果

        窗口长度数M - majority元素的个数N > K
        那么就需要移动左指针缩短窗口．为什么呢？因为如果只移动右指针，即使加入了majority元素，窗口内的那些非majority元素仍然多于Ｋ，使得整体无法成为一个合法的窗口．

        分析： １．为什么左指针移动之后不用更新结果？

        这是因为，我们移动左指针的起因是之前s[j]的引入，它必然是一个非majority的字符（否则整个窗口应该会继续保持合法），而无论左指针弹出的是否majority元素，都不会得到更好的结果，最多持平，所以我们不需要更新结果．

        ２．为什么左指针移动只需要一步？

        因为我们求最长的窗口，左指针的移动不用太大．事实上，只要移动左指针一步，那么整个窗口还是有机会通过移动右指针找到下一个可能的窗口．参看上面的那个公式．
    
    */
    int characterReplacement(string s, int k) 
    {
        vector<int>Count(26,0);        
        int i = 0;        
        int result = 0;
        
        for (int j=0; j<s.size(); j++)
        {
            Count[s[j]-'A']++;
            int majorityNum = *max_element(Count.begin(),Count.end());
            
            if (j-i+1-majorityNum <=k)
                result = std::max(result, j-i+1);
            else
            {
                Count[s[i]-'A']--;
                i++;
            }
            
        }
        return result;
    }

    int characterReplacement(string s, int k) 
    {
        vector<int>Count(26,0);
        
        int i = 0;        
        int result = 0;
        
        for (int j=0; j<s.size(); j++)
        {
            Count[s[j]-'A']++;
            
            while (j-i+1-*max_element(Count.begin(),Count.end()) >k)
            {
                Count[s[i]-'A']--;
                i++;                       
            }
            result = std::max(result, j-i+1);                                    
        }
        return result;
    }


public:

    /*
        Solution 1
        we can replace maxf with max(count.values()),
        it's easier to understand and only O(26N).
        Now I improve it using a variable maxf so that it's O(N).

        Time O(N)
        Space O(26)
    */
    int characterReplacement(string s, int k) {
        int res = 0, maxf = 0;
        unordered_map<int, int> count;
        for (int i = 0; i < s.length(); ++i) {
            maxf = std::max(maxf, ++count[s[i]]);
            if (res - maxf < k)
                res++;
            else
                count[s[i - res]]--;
        }
        return res;
    }

    /*
        Solution 2
        Another version of same idea.
        In a more standard format of sliding window.
        Maybe easier to understand

        Time O(N)
        Space O(26)
    */
    int characterReplacement(string s, int k) {
        int maxf = 0, i = 0, n = s.length();
        vector<int> count(26);
        for (int j = 0; j < n; ++j) {
            maxf = std::max(maxf, ++count[s[j] - 'A']);
            if (j - i + 1 > maxf + k)
                --count[s[i++] - 'A'];
        }
        return n - i;
    }

    int doit_hashtable(string s, int k) {
    
        int maxlen = 0, length = 0;
        unordered_map<char, int> cnt;
        
        for (int i = 0; i < s.length(); i++) {
            
            maxlen = std::max(maxlen, ++cnt[s[i]]);
            
            if (length - maxlen < k) {
                length++;
            } else {
                cnt[s[i-length]]--;
            }
        }
        
        return length;
    }
};