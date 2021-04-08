

/*

# 564. Find the Closest Palindrome

# Given an integer n, find the closest integer (not including itself), which is a palindrome.

# The 'closest' is defined as absolute difference minimized between two integers.

# Example 1:
# Input: "123"
# Output: "121"

# Note:
# The input n is a positive integer represented by string, whose length will not exceed 18.
# If there is a tie, return the smaller one as answer.



# Let�s build a list of candidate answers for which the final answer must be one of those candidates. Afterwards,
# choosing from these candidates is straightforward.

# If the final answer has the same number of digits as the input string S, then
# the answer must be the middle digits + (-1, 0, or 1) flipped into a palindrome.
# For example, 23456 had middle part 234, and 233, 234, 235 flipped into a palindrome yields 23332, 23432, 23532.
# Given that we know the number of digits, the prefix 235 (for example) uniquely determines the corresponding palindrome 23532, so all palindromes with larger prefix like 23732 are strictly farther away from S than 23532 >= S.

# If the final answer has a different number of digits, it must be of the form 999....999 or 1000...0001, as any palindrome smaller than 99....99 or bigger than 100....001 will be farther away from S.


*/

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

class NearestPalindromic {

	/*
		564.Find-the-Closest-Palindrome
		这是一道比较难的题目。

		看到题目最直观的想法是，将数字的前半部分翻转后拼接到后半部分，比如说12345，那么我们就找12321.

		但是这样的策略不是万能的，因为找到不一定是离原数最接近的。比如12399，如果我们选择直接翻转，12321就不是最优解，最优解应该是12421. 再比如19200,直接翻转的19291不是最优解，最优解是19191. 那么我们就可以见端倪了，对于形如ABCXX的形式，我们应该在ABCBA，AB(C+1)BA，AB(C-1)BA之间选择一个最接近原数的就可以了。
		
		同理，对于ABXX的形式，我们采用类似的加一减一再复制翻转的方式，于是就应该在ABBA，A(B+1)(B+1)A，A(B-1)(B-1)A之间选择一个最接近原数的。

		但这样的话，又会有个问题，例如12088，中间的0如果减去１的话就变成9了，翻转复制就成了12921和，这与原数相差也太大了．所以我们改进上面的方法，不再只对中间的数字加减，而是对前三位120整体做加减，然后复制翻转拼接（合并掉中间一位以保证仍然是奇数位），
		
		得到11911,12021,12121．那么我们对于偶数位也采取相同的方法，例如2088,我们对20整体进行加减操作，然后复制翻转拼接（不用合并掉中间一位，因为期望仍然是偶数位），得到1991,2002,2112.

		但是，如果遇到加减之后位数变化的情况怎么办呢？比如10001,我们对前三位100减１之后得到的99，复制翻转拼接之后得到的999，位数一下子就少了两位．类似的对于999，我们如果对于前两位99加一变成100,
		
		复制翻转拼接后变成10001,位数一下子就多了两位．类似的情况对于偶数位的数字也会出现．怎么办呢？方案是，我们照做不误，反正最后筛查所有候选答案的时候，这些偏差太大的候选人一定会被去掉的．
		
		但是，我们需要同时考虑到这种位数变化的情况，所以干脆也加入到候选者来．比如给出的某个n位数，那么我们就把n+1位数的100...0001直接放入候选，n-1位数的99...99也直接放入候选．

		综上，我们有了得到五个候选人的方案,最后筛查一下．去除不是回文数的（注意有可能候选人不是回文数），选取和原数最接近的就是答案了．
	*/
	string nearestPalindromic(string n) 
    {
        int N=n.size();
        string s1,s2,s3;
        
        if (N%2==1)
        {
            string t=n.substr(0,N/2+1);
            long long num=convert(t);
            string t1,t2;
            
            // candidate 1
            t1 = to_string(num);
            t2 = t1;
            reverse(t2.begin(),t2.end());
            s1 = t1.substr(0,N/2)+t2;
            
            // candidate 2
            t1 = to_string(num-1);
            t2=t1;
            reverse(t2.begin(),t2.end());
            s2 = t1.substr(0,N/2)+t2;
            
            // candidate 3
            t1 = to_string(num+1);
            t2=t1;
            reverse(t2.begin(),t2.end());
            s3 = t1.substr(0,N/2)+t2;

            return pick(n,s1,s2,s3);
        }
        
        if (N%2==0)
        {
            string t=n.substr(0,N/2);
            long long num=convert(t);
            string t1,t2;
            
            //candidate 1
            t1 = n.substr(0,N/2);
            reverse(t1.begin(),t1.end());
            s1 = to_string(num)+t1;
            
            //candidate 2
            t1 = to_string(num-1);
            if (t1=="0")
                s2="9";
            else if (t1.size()==t.size())
            {
                t2=t1;
                reverse(t2.begin(),t2.end());
                s2=t1+t2;
            }
            else if (t1.size()!=t.size())
            {
                t2=t1;
                reverse(t2.begin(),t2.end());
                s2=t1+'9'+t2;
            }
            
            //candidate 3
            t1 = to_string(num+1);
            if (t1.size()==t.size())
            {
                t2=t1;
                reverse(t2.begin(),t2.end());
                s3=t1+t2;
            }
            else if (t1.size()!=t.size())
            {
                t2=t1;
                reverse(t2.begin(),t2.end());
                t1.pop_back();
                s3=t1+t2;
            }
            
            
            return pick(n,s1,s2,s3);
        }        
    }
    
    string pick(string n, string s1, string s2, string s3)
    {
        long long m= convert(n);
        long long n1= convert(s1);
        long long n2= convert(s2);
        long long n3= convert(s3);
        
        if (n1==m)
        {
            return abs(n2-m)<=abs(n3-m)?s2:s3;
        }
        else
        {
            long long num_temp = abs(n1-m)<=abs(n3-m)?n1:n3;
            string string_temp = abs(n1-m)<=abs(n3-m)?s1:s3;
            
            return abs(n2-m)<=abs(num_temp-m)?s2:string_temp;
        }        
    }    
    
    long long convert(string s)
    {
        long long result=0;
        for (int i=0; i<s.size(); i++)
        {
            result = result*10 + s[i]-'0';
        }
        return result;
    }


public:
	string doit(string n) {
		
		size_t numsLength = n.length();
		vector<long> candidates;

		candidates.push_back(pow(10, numsLength) + 1);
		candidates.push_back(pow(10, numsLength) - 1);

		candidates.push_back(pow(10, numsLength - 1) + 1);
		candidates.push_back(pow(10, numsLength - 1) - 1);

		long prefix = stol(n.substr(0, (numsLength + 1) / 2));
		for (long i = -1; i < 2; i++) {
			string p = to_string(prefix + i);
			string pp = p + string(p.rbegin() + (numsLength & 1), p.rend());
			candidates.push_back(stol(pp));
		}

		long ans = 0, diff = INT_MAX;
		long base = stol(n);
		for (auto c : candidates) {

			long d = abs(c - base);
			if (d == 0 || d > diff || (d == diff && c > ans))
				continue;

			ans = c;
			diff = d;
		}

		return to_string(ans);
	}


	string doit_str_best(string n) {

		int l = n.size();
		set<long> candidates;

		// biggest, one more digit, 10...01
		candidates.insert(long(pow(10, l)) + 1);
		// smallest, one less digit, 9...9 or 0
		candidates.insert(long(pow(10, l - 1)) - 1);
		
		// the closest must be in middle digit +1, 0, -1, then flip left to right
		long prefix = stol(n.substr(0, (l + 1) / 2));
		for (long i = -1; i <= 1; ++i) {
			string p = to_string(prefix + i);
			string pp = p + string(p.rbegin() + (l & 1), p.rend());
			candidates.insert(stol(pp));
		}
		
		long num = stol(n), minDiff = LONG_MAX, diff, minVal;
		candidates.erase(num);
		for (long val : candidates) {
			diff = abs(val - num);
			if (diff < minDiff) {
				minDiff = diff;
				minVal = val;
			}
			else if (diff == minDiff) {
				minVal = min(minVal, val);
			}
		}
		
		return to_string(minVal);
	}
};