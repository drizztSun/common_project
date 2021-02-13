"""
1573. Number of Ways to Split a String


Given a binary string s (a string consisting only of '0's and '1's), we can split s into 3 non-empty strings s1, s2, s3 (s1+ s2+ s3 = s).

Return the number of ways s can be split such that the number of characters '1' is the same in s1, s2, and s3.

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: s = "10101"
Output: 4
Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
"1|010|1"
"1|01|01"
"10|10|1"
"10|1|01"
Example 2:

Input: s = "1001"
Output: 0
Example 3:

Input: s = "0000"
Output: 3
Explanation: There are three ways to split s in 3 parts.
"0|0|00"
"0|00|0"
"00|0|0"
Example 4:

Input: s = "100100010100110"
Output: 12
 

Constraints:

3 <= s.length <= 10^5
s[i] is '0' or '1'.


"""


class NumWays:


    def doit_(self, s: str) -> int:
		#mod param for output
        mod = (10**9) + 7
		
		#length of s and count of 1's
        n = len(s)
        cnt = s.count('1')
        
		# Base case, if count == 0 (i.e. no 1's) then it is a combination problem on the entire string (n-1)C2
        # for (1--n-1), we can pick two points as starting index of seond and third parts.
        if cnt == 0:
            return (((n-1)*(n-2)) // 2) % mod
		
		# if count % 3!=0 i.e. if the number of 1's is not divisible by 3 then we cant split them equally
        if cnt % 3 != 0:
            return 0
        
		# onethird stores the number of 1's in each division
        onethird = cnt/3
		
		# Ways1 and ways2 stores the number of ways we can create the first and second partition 
		# Example 1010001101001
		# 101, 110 and 1001 are the 3 partitions with equal 1's
		# a split can be made in 4 places at '000', 2 places are '0'
        ways1 = 0
        ways2 = 0
        cnt = 0
        for i in s:
            if i == '1':
                cnt +=1
            if cnt == onethird:
                ways1+=1
            elif cnt == 2*onethird:
                ways2+=1
        return ways1*ways2%mod

    def doit_(self, s: str) -> int:

        cnt = 0
        for c in s:
            cnt += 1 if c == '1' else 0
        
        n, hmod = len(s), 10**9 + 7
        if cnt == 0:
            return ((n-1) * (n-2) // 2) % hmod
        
        if cnt % 3 != 0: return 0
            
        i, leftparts, parts = 0, 0, cnt // 3
        while i < len(s):
            parts -= 1 if s[i] == '1' else 0
            if parts == 0:
                leftparts += 1
            elif parts == -1:
                break
            i += 1
            
        j, rightparts, parts = len(s)-1, 0, cnt // 3
        while rightparts >= 0:
            parts -= 1 if s[j] == '1' else 0
            if parts == 0:
                rightparts += 1
            elif parts == -1:
                break
            j -= 1
            
        return leftparts * rightparts % hmod