/*

395. Longest Substring with At Least K Repeating Characters

Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.

 

Example 1:

Input: s = "aaabb", k = 3
Output: 3
Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input: s = "ababbc", k = 2
Output: 5
Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 

Constraints:

1 <= s.length <= 104
s consists of only lowercase English letters.
1 <= k <= 105

*/
#include <string>
#include <unordered_map>
#include <functional>

using std::unordered_map;
using std::string;

class LongestSubstringWithAtLeastKRepeatingChar {

public:

    /*
    Approach 3: Sliding Window
    Intuition

    There is another intuitive method to solve the problem by using the Sliding Window Approach. The sliding window slides over the string s and validates each character. Based on certain conditions, the sliding window either expands or shrinks.

    A substring is valid if each character has at least k frequency. The main idea is to find all the valid substrings with a different number of unique characters and track the maximum length. Let's look at the algorithm in detail.

    Algorithm

    Find the number of unique characters in the string s and store the count in variable maxUnique. For s = aabcbacad, the unique characters are a,b,c,d and maxUnique = 4.

    Iterate over the string s with the value of currUnique ranging from 1 to maxUnique. In each iteration, currUnique is the maximum number of unique characters that must be present in the sliding window.

    The sliding window starts at index windowStart and ends at index windowEnd and slides over string s until windowEnd reaches the end of string s. At any given point, we shrink or expand the window to ensure that the number of unique characters is not greater than currUnique.

    If the number of unique character in the sliding window is less than or equal to currUnique, expand the window from the right by adding a character to the end of the window given by windowEnd

    Otherwise, shrink the window from the left by removing a character from the start of the window given by windowStart.

    Keep track of the number of unique characters in the current sliding window having at least k frequency given by countAtLeastK. Update the result if all the characters in the window have at least k frequency.
    */
    
    // get the maximum number of unique letters in the string s
    int getMaxUniqueLetters(string s) {
        bool map[26] = {0};
        int maxUnique = 0;
        for (int i = 0; i < s.length(); i++) {
            if (!map[s[i] - 'a']) {
                maxUnique++;
                map[s[i] - 'a'] = true;
            }
        }
        return maxUnique;
    }

    int longestSubstring(string s, int k) {

        int countMap[26];
        int maxUnique = getMaxUniqueLetters(s);
        int result = 0;
        for (int currUnique = 1; currUnique <= maxUnique; currUnique++) {
            // reset countMap
            memset(countMap, 0, sizeof(countMap));
            int windowStart = 0, windowEnd = 0, idx = 0, unique = 0, countAtLeastK = 0;
            while (windowEnd < s.size()) {
                // expand the sliding window
                if (unique <= currUnique) {
                    idx = s[windowEnd] - 'a';
                    if (countMap[idx] == 0) unique++;
                    countMap[idx]++;
                    if (countMap[idx] == k) countAtLeastK++;
                    windowEnd++;
                }
                // shrink the sliding window
                else {
                    idx = s[windowStart] - 'a';
                    if (countMap[idx] == k) countAtLeastK--;
                    countMap[idx]--;
                    if (countMap[idx] == 0) unique--;
                    windowStart++;
                }
                if (unique == currUnique && unique == countAtLeastK)
                    result = std::max(windowEnd - windowStart, result);
            }
        }

        return result;
    }

    int doit_best_slidingwindows(string s, int k) {
 
        std::function<int(string, int)> search = [&](string s, int) -> int{

            unordered_map<int,int>Map;
            for (int i=0; i<s.size(); i++)
                Map[s[i]]++;
                
            int result = 0;
            for (int i=0; i<s.size(); i++)
            {
                if (Map[s[i]]<k) 
                    continue;
                
                int j = i;
                while (j<s.size() && Map[s[j]] >= k)
                    j++;
                
                if (j-i==s.size())
                    return s.size();
                
                result = std::max(result, search(s.substr(i,j-i),k));
                i = j-1;
            }
            return result;
        };
        
        return search(s, k);
    }

    /*
    395.Longest-Substring-with-At-Least-K-Repeating-Characters
    此题其实并不容易。首先常规的双指针并不适用，假设我们固定左指针是第一个元素，那么右指针最远能移动到哪里呢？我们无法确定。其次，也无法用二分搜值的方法，因为满足条件的substring的长度并不一定是连续比变化的。

    解法1：递归
    如果把整个序列遍历完，那么我们就得到了所有字符和它出现的频次。对于那些出现次数少于k的字符，是“害群之马”，它们放在任何一个子序列中都会违反题意的。所以一个直观的想法是，将那些“害群之马”作为splitor，
    将原序列分割成若干子序列，然后递归调用函数本身，找到最长的有效子序列。递归的边界是，如果整个序列所有的字符频次都大于等于k，就可以返回序列的长度；如果整个序列的总长度都小于k，那么就返回零。

    注意，这种写法的时间复杂度其实是o(N^2)。虽然有o(N)的分治（递归）写法，但是不是很容易想到，这里省略。

    解法2：双指针
    本题其实确实有双指针的方法，但是比较特殊。那就是固定“滑窗里不同字母的个数”，这个数目m可以从1遍历到26。只要固定了左指针和区间不同字母的个数，那么我们就可以确定右指针最远的位置，然后查看区间内是否每个字母出现的频次都大于k。最后的答案就是遍历所有m时能够得到的最大滑窗长度。这种算法的时间复杂度是o(26N).
    */

    int doit_recursive(string s, int k) 
    {
        unordered_map<char,int>Map;
        for (auto ch: s)
            Map[ch]++;
        
        int flag = 1;
        for (auto x: Map)
            if (x.second < k)
            {
                flag = 0;
                break;
            }
            
        if (flag) 
            return s.size();
                
        int ret = 0;
        for (int i=0; i<s.size(); i++)
        {
            if (Map[s[i]]<k) continue;
            int j = i;
            while (j<s.size() && Map[s[j]]>=k)
                j++;
            ret = std::max(ret, doit_recursive(s.substr(i,j-i), k));
            i = j;
        }
        
        return ret;        
    }
    
    int doit_slidingwindow(string s, int k) {
        

        std::function<int(int, int)> helper = [&](int m, int k) {

            unordered_map<int, int> cnt;
            int j = 0;
            int ans = 0;
            int count = 0;

            for (int i = 0; i < s.size(); i++) {
                
                while  (j < s.size() && cnt.size() <= m) {

                    cnt[s[j]]++;

                    if (cnt[s[j]] == k)
                        count++;

                    j++;

                    if (cnt.size() == m && count == m)
                        ans = std::max(ans, j - i);
                }

                cnt[s[i]]--;

                if (cnt[s[i]] == k - 1)
                    count--;

                if (cnt[s[i]] == 0)
                    cnt.erase(s[i]);
            }

            return ans;
        };

        int ret = 0;
        for (int c = 1; c <= 26; c++) {
            ret = std::max(ret, helper(c, k));
        }

        return ret;
    }
};