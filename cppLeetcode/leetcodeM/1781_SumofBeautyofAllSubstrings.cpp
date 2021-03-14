/*
1781. Sum of Beauty of All Substrings

The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.

For example, the beauty of "abaacc" is 3 - 1 = 2.
Given a string s, return the sum of beauty of all of its substrings.

 

Example 1:

Input: s = "aabcb"
Output: 5
Explanation: The substrings with non-zero beauty are ["aab","aabc","aabcb","abcb","bcb"], each with beauty equal to 1.
Example 2:

Input: s = "aabcbaa"
Output: 17
 

Constraints:

1 <= s.length <= 500
s consists of only lowercase English letters.
*/
#include <string>
#include <vector>
#include <map>

using std::vector;
using std::map;
using std::string;


class BeautySum {

public:
    
    int doit_hashtable(string s) {

        int ans = 0;
        
        for (int i = 0; i < s.length(); i++) {

            map<int, int> buf;
            vector<int> cnt(26, 0);    

            for (int j = i; j < s.length(); j++) {

                const int c = ++cnt[s[j] - 'a'];
                ++buf[c];

                if (c > 1) {
                    auto it = buf.find(c-1);
                    if (--it->second == 0)
                        buf.erase(c-1);
                }

                ans += buf.rbegin()->first - buf.begin()->first;
            }
        }

        return ans;
    }

    int doit_(string s) {
        int i, j, k, n = s.length();
		// base case
        if(n<=1)
            return 0;
        
		// freq of each char in s[0...i]
        int freq[n][26];
        memset(freq, 0, sizeof(freq));
        
        int result = 0;
		// s[0..0] has freq[s[0]-'a'] = 1
        freq[0][s[0]-'a'] = 1;
        
		// handling cases for substr s[0..i]
        for(i=1;i<n;i++){
            int mn = INT_MAX, mx = 0;
            for(j=0;j<26;j++){
				// [prev_freq == curr_freq] but only one will be modified depening upon s[i] rest will be same
                freq[i][j] = freq[i-1][j];
				// if jth char is not the current char as freq shud be modified handled later
				// and if jth char has +ve freq
                if((j!=s[i]-'a') && freq[i][j]>0)
                    mn = std::min(mn, freq[i][j]);
                mx = std::max(mx, freq[i][j]);
            }
			// curr char will be 1 more than prev_freq
            freq[i][s[i]-'a']++;
			// again checking for new max and min
            mx = std::max(mx, freq[i][s[i]-'a']);
            mn = std::min(mn, freq[i][s[i]-'a']);
            result += (mx - mn);
        }
        
		// handling cases when substr is s[i..j]
        for(i=1;i<n;i++){
            for(j=i;j<n;j++){
                int mn = INT_MAX, mx = 1;
                for(k=0;k<26;k++){
					// finding new min freq if that char has +ve freq in that segment
                    if(freq[j][k] - freq[i-1][k] > 0)
                        mn = std::min(mn, freq[j][k] - freq[i-1][k]);
					// max freq in that segment
                    mx = std::max(mx, freq[j][k] - freq[i-1][k]);
                }
				
                result += (mx - mn);
            }
        }
        return result;
    }
};