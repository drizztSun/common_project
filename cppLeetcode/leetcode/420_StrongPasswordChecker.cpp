/*
420. Strong Password Checker

A password is considered strong if the below conditions are all met:

.It has at least 6 characters and at most 20 characters.
.It contains at least one lowercase letter, at least one uppercase letter, and at least one digit.
.It does not contain three repeating characters in a row (i.e., "...aaa..." is weak, but "...aa...a..." is strong, assuming other conditions are met).

Given a string password, return the minimum number of steps required to make password strong. if password is already strong, return 0.

In one step, you can:

.Insert one character to password,
.Delete one character from password, or
.Replace one character of password with another character.
 

Example 1:

Input: password = "a"
Output: 5
Example 2:

Input: password = "aA1"
Output: 3
Example 3:

Input: password = "1337C0d3"
Output: 0
 

Constraints:

1 <= password.length <= 50
password consists of letters, digits, dot '.' or exclamation mark '!'.


*/

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;


/*
I�ve separated the problem into three cases :
(1) s.length() < 6
(2) 6 <= s.length() <= 20
(3) s.length() > 20

Let�s look at case (1) first.If s.length() < 6, we know we have room to insert some more letters into s.

Question is how to use the insertions effectively to reduce the number of potential replacements.I�m using a greedy approach for this one: I�m inserting one char between the second and third chars whenever I see a repetition of 3 letters as substring.

	e.g.Say we have room to insert some chars in string and we see a substring of "aaaa".I�ll insert a 'B' to make it "aaBaa" to break the 3 - char repetition, thus reducing potential replacement by 1. And we�ll do this until we can�t insert any more chars into s.When we reach this point, we�ll start dealing with case (2)

	For case (2), I still follow a greedy approach.I�m simply searching for 3 - char repetitions, and replacing one of the chars to break the repetition.
	e.g.If we see a substring of "aaaa", we�ll make it "aaBa".

	My code deals with(1) and (2) together as s.length() <= 20.

	Case(3) is a little bit tricky because simple greedy doesn�t work any more.
	When s.length() > 20, we want to delete some chars instead of inserting chars to reduce potential replacements.Question is the same : how to do it effectively ? Let�s do some observations here :

Say len is the length of each repetition.
(a)len % 3 only has three possible values, namely 0, 1 and 2.
(b)Minimum number of replacements needed to break each repetition is len / 3.
� Based on(a) and (b), we know that deletion can reduce replacements only if the deletion can change the value of len / 3
(d)Based on �, we know if we want to reduce 1 replacement, we need 1 deletion for len % 3 == 0, and 2 deletions for len % 3 == 1, and 3 deletions for len % 3 == 2.

Given above observations, I simply implemented the solution to do (d).

*/

//Also note that missing of upper case char, lower case char, or digit can always be resolved by insertion or replacement.


class StrongPasswordChecker {

	/*
		420.Strong-Password-Checker
		此题感觉比较难.这里,我们约定MissingType表示缺了几种类型的字符(大写,小写,数字),取值范围是[0,3].另外约定change表示我们最终方案里需要替换的次数.deleted表示我们最终方案里需要删除的次数.

		当len(s)<6时,需要添加6-len(s)个字符.注意到,此中情况下没有重复序列的问题,并且add的操作同时可以解决MissingType的问题.所以最终答案是max(MissingType,6-len(s))

		当6<=len(s)<=20时,只存在MissingType和重复序列的问题,而没有需要删除字符的问题.我们容易计算出最高效的"替换"操作方案,也就是每遇到aaa的情况就将第三个元素替换成别的,计做一次change.这样所需的change是最少.同时,考虑到"替换"也可以解决MissingType的问题.所以最终答案是max(MissingType,change)

		当len(s)>20时,会同时存在MissingType,重复序列,删除字符的问题,情况最为复杂.我们慢慢分析.

		首先我们考虑最高效的"替换"操作,如前,我们容易计算出所需要的最少的change.完成这套操作之后,消灭了重复序列的问题.

		然后考虑字符串过长的问题,共有to_delete个元素需要删除.如果我们简单地再删除这么多字符,总计change+to_delete个操作,这是不高效的.因为我们可以用一些"删除"操作来等效之前的"替换"操作.

		举个例子来看,如果...aaa...,我们采用"替换"操作的话,需要一次change(替换最后一个a);而如果我们"删除"最后一个a的话,同样也能使这个字符串合法.所以结论是,我们在这里可以进行一次必要的"删除"操作(为什么说是必要,是因为总共有to_delete这么多元素等待删除),而之前进行的"替换"操作就不必要了,也就是change可以减一.

		再举个例子来看,如果...aaaa...,我们采用"替换"操作的话,需要一次change(替换第三个a);而如果我们"删除"两个a的话,同样也能使这个字符串合法.所以结论是,我们在这里可以进行两次必要的"删除"操作,而之前进行的"替换"操作就不必要了,即change同样可以减一.

		再举个例子来看,如果...aaaaa...,我们采用"替换"操作的话,需要一次change(替换第三个a);而如果我们"删除"三个a的话,同样也能使这个字符串合法.所以结论是,我们在这里可以进行三次必要的"删除"操作,而之前进行的"替换"操作就不必要了,即change同样可以减一.

		以上这些例子说明什么意思?因为删除to_delete个字符是"必选动作",如果我们在做这些必选动作的时候,能够代替掉越多的change的话,那就是最高效的方案.再分析一下,第一个例子代表了连续重复字串长度len%3==0,第二个例子代表了连续重复字串长度len%3==1,第三个例子代表了其他情况.我们在遍历s的时候,可以统计这些情况出现的频次,按照优先级的顺序,每做一次(或者两次,三次)"删除"操作,可以避免一次"替换"操作.

		最终的结果就是,总共进行的"删除"操作(deleted),加上没有被抵消的"替换"操作(change).注意,change操作可以抵消MissingType,不够抵消的话,需要额外考虑MissingType的个数.
	*/
	
public:
	
	int strongPasswordChecker(string s) {

		int deleteTarget = std::max(0, (int)s.length() - 20), addTarget = std::max(0, 6 - (int)s.length());

		int toDelete = 0, toAdd = 0, toReplace = 0, needUpper = 1, needLower = 1, needDigit = 1;

		///////////////////////////////////
		// For cases of s.length() <= 20 //
		///////////////////////////////////
		for (int l = 0, r = 0; r < s.length(); r++) {
			if (isupper(s[r])) { needUpper = 0; }
			if (islower(s[r])) { needLower = 0; }
			if (isdigit(s[r])) { needDigit = 0; }

			if (r - l == 2) {                                   // if it's a three-letter window
				if (s[l] == s[l + 1] && s[l + 1] == s[r]) {     // found a three-repeating substr
					if (toAdd < addTarget) { 
						// insert letter to break repetition if possible
						toAdd++, l = r; 
					}  else { 
						// replace current word to avoid three repeating chars
						toReplace++, l = r + 1; 
					}            
				} else { 
					// keep the window with no more than 3 letters
					l++; 
				}
			}
		}

		if (s.length() <= 20) { 
			return std::max(addTarget + toReplace, needUpper + needLower + needDigit);
		}
		
		//////////////////////////////////
		// For cases of s.length() > 20 //
		//////////////////////////////////
		toReplace = 0;                                          // reset toReplace
		vector<unordered_map<int, int>> lenCnts(3);             // to record repetitions with (length % 3) == 0, 1 or 2
		for (int l = 0, r = 0, len; r <= s.length(); r++) {     // record all repetion frequencies
			if (r == s.length() || s[l] != s[r]) {
				if ((len = r - l) > 2) { lenCnts[len % 3][len]++; } // we only care about repetions with length >= 3
				l = r;
			}
		}

		/*
		Use deletions to minimize replacements, following below orders:
		(1) Try to delete one letter from repetitions with (length % 3) == 0. Each deletion decreases replacement by 1
		(2) Try to delete two letters from repetitions with (length % 3) == 1. Each deletion decreases repalcement by 1
		(3) Try to delete multiple of three letters from repetions with (length % 3) == 2. Each deletion (of three
		letters) decreases repalcements by 1
		*/
		for (int i = 0, numLetters, dec; i < 3; i++) {
			for (auto it = lenCnts[i].begin(); it != lenCnts[i].end(); it++) {
				if (i < 2) {
					numLetters = i + 1;
					dec = std::min(it->second, (deleteTarget - toDelete) / numLetters);

					toDelete += dec * numLetters;               // dec is the number of repetitions we'll delete from
					it->second -= dec;                          // update number of repetitions left
																// after letters deleted, it fits in the group where (length % 3) == 2

					if (it->first - numLetters > 2) {
						lenCnts[2][it->first - numLetters] += dec; 
					}
				}

				// record number of replacements needed
				// note if len is the length of repetition, we need (len / 3) number of replacements
				toReplace += (it->second) * ((it->first) / 3);
			}
		}

		int dec = (deleteTarget - toDelete) / 3;                // try to delete multiple of three letters as many as possible
		toReplace -= dec, toDelete -= dec * 3;
		return deleteTarget + std::max(toReplace, needUpper + needLower + needDigit);
	}
};