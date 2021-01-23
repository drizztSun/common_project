"""
1641. Count Sorted Vowel Strings


Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.

A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.

 

Example 1:

Input: n = 1
Output: 5
Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
Example 2:

Input: n = 2
Output: 15
Explanation: The 15 sorted strings that consist of vowels only are
["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
Note that "ea" is not a valid string since 'e' comes after 'a' in the alphabet.
Example 3:

Input: n = 33
Output: 66045
 

Constraints:

1 <= n <= 50 



"""


class CountVowelStrings:


    def doit_dp_bottomup_1(self, n: int) -> int:

        #  dp[n][vowels] = dp[n - 1][vowels] + dp[n][vowels - 1]
        
        a, e, i, o, u = 5, 4, 3, 2, 1
        
        for _ in range(1, n):
            
            nu = u
            no = nu + o
            ni = no + i
            ne = ni + e
            na = ne + a
            
            a, e, i, o, u = na, ne, ni, no, nu
            
        return a
        
    
    def doit_dp_bottomup(self, n: int) -> int:

        a, e, i, o, u = 1, 1, 1, 1, 1

        for _ in range(1, n):

            na = a + e + i + o + u
            ne = e + i + o + u
            ni = i + o + u
            no = o + u
            nu = u

            a, e, i, o, u = na, ne, ni, no, nu


        return sum((a, e, i, o, u))

    """
        Approach 5: Math
        Intuition and Algorithm

        The problem is a variant of finding Combinations. Mathematically, the problem can be described as, given 5 vowels (let k = 5k=5), we want to find the number of combinations using only nn vowels. Also, we can repeat each of those vowels multiple times.

        In other words, from kk vowels (k = 5k=5), we can choose nn vowels with repetition. Denoted as Combination((n,k)), the formulae for Combination with Repetition is given by,        ​	
        

        We know that the kk value is 55 as there are always 55 vowels to choose from. Substituting k as 5 in above formulae,
        (n+4)⋅(n+3)⋅(n+2)⋅(n+1) / 24
        The derivation can be illustrated as follows.

        img

        Implementation


        Complexity Analysis

        Time Complexity: \mathcal{O}(1)O(1), as the approach runs in constant time.

        Space Complexity: \mathcal{O}(1)O(1), as the approach uses constant extra space.

    """
    def doit_math(self, n: int) -> int:

        return (n+4) * (n+3) * (n+2) * (n+1) // 24 

        