/*
30. Substring with Concatenation of All Words

You are given a string s and an array of strings words of the same length. Return all starting indices of substring(s) 
in s that is a concatenation of each word in words exactly once, in any order, and without any intervening characters.

You can return the answer in any order.


Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
Example 2:

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
Example 3:

Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
 

Constraints:

1 <= s.length <= 104
s consists of lower-case English letters.
1 <= words.length <= 5000
1 <= words[i].length <= 30
words[i] consists of lower-case English letters.

*/

#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;


// 30. Substring with Concatenation of All Words
// travel all the words combinations to maintain a window
// there are wl(word len) times travel
// each time, n/wl words, mostly 2 times travel for each word
// one left side of the window, the other right side of the window
// so, time complexity O(wl * 2 * N/wl) = O(2N)

class SubstringWConcatenationOfAllWords {

public:

	std::vector<int> doit_slidingwindow(const std::string& s, std::vector<std::string>& words) {

		auto wl = words[0].size();
		auto strlen = s.size();
		auto amount = words.size();
		std::vector<int> ans;

		if (strlen < wl * amount) return ans;

		std::unordered_map<string, int> gDict;
		for (auto word : words) gDict[word]++;

		for (auto i = 0; i < wl; i++) {
			auto left = i;
			int count = 0;

			std::unordered_map<std::string, int> tDict;
			for (auto j = i; j <= strlen - wl; j += wl) {

				std::string sub_str = s.substr(j, wl);
				if (gDict.count(sub_str) == 1) {
					tDict[sub_str]++;

					if (tDict[sub_str] <= gDict[sub_str]) {
						count++;
					}
					else {
						while (tDict[sub_str] > gDict[sub_str]) {
							auto tmp = s.substr(left, wl);
							
							tDict[tmp]--;
							if (tDict[tmp] < gDict[tmp]) {
								count--;
							}
							left += wl;
						}
					}

					if (amount == count) {
						ans.push_back(left);
						count--;
						tDict[s.substr(left, wl)]--;
						left += wl;
					}
				}
				else {
					count = 0;
					tDict.clear();
					left = j + wl;
				}
			}
		}
		return ans;
	}

	/*
		30. Substring-with-Concatenation-of-All-Words
		典型的双指针算法题，常规思路：右指针一路前进，遇到不符合条件的情况就移动左指针直至消除负面条件，再接着移动右指针。
		具体的实现比较复杂，需要注意这么几点：
		1.增加一个外层循环，双指针的起始点可以从0~M, M是每个词的长度. 注意count和showTime在每个start都要清零，故设置为循环内变量。

				for (int start=0; start<M; start++ )
				{
					int i=start;
					int j=start;
					int count=0;
					unordered_map<string,int> showTime;
					
					while (j<s.size() && i<=j)
					{
						...
					}
				}
		2.每次考察右指针对应的待加入的子串，

						string ss = s.substr(j,M);
		但不要着急移动右指针，进入如下的判断：

		(a).待加入的新元素不在字典中，则count和showTime全部都清零！移动两个指针：都移到右指针的下一个位置

						if (Map.find(ss)==Map.end())
						{
							j+=M;
							i=j;
							count=0;
							showTime.clear();
						}
		(b).待加入的新元素在字典中，且没有溢出，则加入并更新统计。移动右指针。
		注意，加入之后如果已经满足条件，则记录并处理。

						else if (Map_temp[ss]<Map[ss])
						{
							j+=M;
							showTime[ss]++;
							if (showTime[ss]==Map[ss])
								count++;
							
							if (count==N)
							{
								results.push_back(i);
								string tt = s.substr(i,M);
								showTime[tt]--;
								count--;
								i+=M;
							}
						}
		(c) 待加入的新元素虽然在字典中，但会造成溢出，则不加入统计。移动左指针，退出最左边的元素。

						else
						{
							string tt = s.substr(i,M);
							showTime[tt]--;
							if (showTime[tt]==Map[tt]-1)
								count--;
							i+=M;
						}
		5.重复循环。
	*/
    vector<int> doit_search(string s, vector<string>& words) 
    {
        int N=words[0].size();
        int COUNT=words.size();
        unordered_map<string,int>Table;
        for (int i=0; i<words.size(); i++)
            Table[words[i]]++;
                
        vector<int>results;
        for (int start=0; start<N; start++)
        {
            int i=start;
            int j=i;
            int count=0;
            unordered_map<string,int>Map;

            while (j < s.size())
            {
                if (Table.find(s.substr(j,N))==Table.end())
                {
                    Map.clear();
                    count=0;
                    j+=N;
                    i=j;
                }
                else if (Map[s.substr(j,N)]<Table[s.substr(j,N)])
                {
                    Map[s.substr(j,N)]++;
                    count++;
                    j+=N;
                }
                else if (Map[s.substr(j,N)]==Table[s.substr(j,N)])
                {
                    Map[s.substr(i,N)]--;
                    i+=N;
                    count--;
                }
                
                if (count==COUNT)
                {
                    results.push_back(i);
                    Map[s.substr(i,N)]--;
                    i+=N;
                    count--;                    
                }                                     
            }
        }
        
        return results;
    }

};