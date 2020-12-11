"""
# 30. Substring with Concatenation of All Words

You are given a string s and an array of strings words of the same length. Return all starting indices of substring(s) in s that
is a concatenation of each word in words exactly once, in any order, and without any intervening characters.

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

"""
import collections


class findSubstring(object):

    def doit(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        if not s or not words:
            return []

        from collections import Counter
        gCnt = collections.Counter(words)
        nums, wl = len(words), len(words[0])
        res = []

        if len(s) < wl * nums:
            return []

        for i in range(wl):

            lCnt = Counter()
            left, c = i, 0
            for j in range(i, len(s) - wl + 1, wl):

                sub = s[j: j + wl]

                if sub not in gCnt:
                    left = j + wl
                    lCnt = Counter()
                    c = 0

                else:
                    lCnt[sub] += 1

                    if lCnt[sub] <= gCnt[sub]:
                        c += 1
                    else:
                        while lCnt[sub] > gCnt[sub]:
                            w = s[left: left + wl]
                            lCnt[w] -= 1
                            if lCnt[w] < gCnt[sub]:
                                c -= 1
                            left += wl

                    if c == nums:
                        res.append(left)
                        c -= 1
                        lCnt[s[left: left + wl]] -= 1
                        left += wl
        return res

    def doit_1(self, s: str, words):

        from collections import Counter

        res = []
        glcnt = Counter(words)
        totalNums = len(words)
        length, wl = len(s), len(words[0])

        for i in range(wl):

            left, cnt = i, 0
            lcnt = Counter()

            for j in range(i, len(s) - wl + 1, wl):

                w = s[j: j + wl]

                if w not in glcnt:
                    left = j + wl
                    lcnt = Counter()
                    cnt = 0
                    continue

                lcnt[w] += 1
                cnt += 1
                while lcnt[w] > glcnt[w]:
                    w1 = s[left: left + wl]
                    lcnt[w1] -= 1
                    cnt -= 1
                    left += wl

                if cnt == totalNums:
                    res.append(left)
                    w1 = s[left: left + wl]
                    lcnt[w1] -= 1
                    cnt -= 1
                    left += wl

        return res

    """
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
    """
    def doit_twopointer(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        if len(words) == 0: return []
        M = len(words[0])
        Table = collections.defaultdict(int)
        COUNT = 0
        for word in words:
            Table[word] += 1
            COUNT += 1
        results = []

        for start in range(M):
            Map = collections.defaultdict(int)
            i = start
            flag = 1
            count = 0
            head = i
            while (i < len(s)):

                if i + M > len(s) or (s[i:i + M] not in Table):
                    Map.clear()
                    count = 0
                    head = i + M;
                    i = head
                elif Map[s[i:i + M]] == Table[s[i:i + M]]:
                    Map.clear()
                    count = 0
                    head += M
                    i = head
                else:
                    Map[s[i:i + M]] += 1
                    i += M
                    count += 1

                if count == COUNT:
                    results.append(head)
                    Map.clear()
                    count = 0
                    head += M
                    i = head

        return results


if __name__ == "__main__":
    
    res = findSubstring().doit("barfoothefoobarman", ["bar", "foo"])

    res = findSubstring().findSubstring("barfoofoobarthefoobarman", ["bar", "foo", "the"])

    pass