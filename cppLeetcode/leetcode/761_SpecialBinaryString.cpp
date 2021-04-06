/*

# 761. Special Binary String

# Special binary strings are binary strings with the following two properties:

# The number of 0's is equal to the number of 1's.
# Every prefix of the binary string has at least as many 1's as 0's.
# Given a special string S, a move consists of choosing two consecutive,
# non-empty, special substrings of S, and swapping them.

# (Two strings are consecutive if the last character of the first string
# is exactly one index before the first character of the second string.)

# At the end of any number of moves, what is the lexicographically largest resulting string possible?

# Example 1:
# Input: S = "11011000"
# Output: "11100100"

# Explanation:
# The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
# This is the lexicographically largest string possible after some number of swaps.
# Note:

# S has length at most 50.
# S is guaranteed to be a special binary string as defined above.


*/

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using std::vector;
using std::string;

class MakeLargestSpecial {


	/*
		761.Special-Binary-String
		首先，应该容易分析出：对于一个special string S，它整体可以拆分为一个或若干个不可再拆分的、连续的sub special string。对于每个不可再连续拆分的sub special string S'，它的首位一定是1，末位一定是0，中间一定还是一个special string，于是可能还可以继续拆分下去。

		写成式子就是： 任何 S = （1）ABCDEF（0）,首位的1和末位的0可能存在，而中间的ABCDEF都还是不可连续拆分的speical string，

		因为题目规定的swap的规则必须是在相邻的special string之间进行，所以对于任何一个S,只能通过内部的ABCDEF这些S'之间的位置调整,使得S自身调整至字典序最大
		（暂时不考虑ABCDEF内部的调整，假设它们已经各自字典序最优）。那么如何调整ABCDEF使得S的字典序最大呢？显然，只要让ABCDEF按照字典序从大到小排列即可。

		这就有了递归的思路。把S拆成ABCDEF，让它们各自递归成字典序最大，然后优化后的ABCDF按字典序重排，技能得到字典序最大的S。
	*/
	string makeLargestSpecial(string S) 
    {
        if (S.size()==2) return S;

        vector<string>strs;
        
        for (int i=0; i<S.size(); i++)
        {
            int i0=i;
            int count=0;
            while (i<S.size())
            {
                if (S[i]=='1')
                    count++;
                else
                    count--;                
                if (count==0)
                    break;   
                i++;
            }
            strs.push_back("1"+makeLargestSpecial(S.substr(i0+1,i-i0-1))+"0");
        }
        
        sort(strs.begin(),strs.end(), std::greater<string>());
        string result;
        for (auto a:strs) result+=a;
        return result;
    }


	string largestSpecString(string S) {

		int count = 0, j = 0;
		vector<string> res;

		for (size_t i = 0; i < S.size(); i++) {

			if (S[i] == '1')
				count++;
			else
				count--;

			if (count == 0) {
				res.push_back("1" + largestSpecString(S.substr(j + 1, i - j - 1)) + "0");
				j = i + 1;
			}
		}

		sort(res.begin(), res.end(), std::greater<string>());

		string res2;
		for (auto c : res)
			res2 += c;

		return res2;
	}
};