"""
28. Implement strStr()


Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

 

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
Example 3:

Input: haystack = "", needle = ""
Output: 0
 

Constraints:

0 <= haystack.length, needle.length <= 5 * 104
haystack and needle consist of only lower-case English characters.



"""


class StrStr:


    """
        028.Implement-strStr

        KMP算法
        首先我们要预处理模式串p（也就是needle），得到一个关于模式串的后缀数组suf。suf[i]表示在字符串p中，截止i位置的最长的后缀字符串，使得它恰好也是p的前缀。比如说，如果j=suf[i]，那么p[0:j-1]=p[i-j+1:i]。关于后缀数组的计算，请见1392.Longest-Happy-Prefix.

        假设我们已经有了模式串的后缀数组suf，那么我们如何来求解这个题呢？我们对于字符串s（也就是haystack）也定义类似的后缀数组dp。其中dp[i]表示s里截止i位置的最长的后缀字符串，使得它恰好也是p的前缀。注意，这里如果j=suf[i]，那么p[0:j-1]=s[i-j+1:i]。显然，如果dp[i]==p.size()，那么意味着以s[i]为结尾的后缀字符串与p完全匹配。

        我们试图用动态规划的想法，看看dp[i]是否能从dp[i-1]得到。如下图：我们想计算dp[i]。我们看一下dp[i-1]，记j=dp[i-1]，那么p就有一段长度为j的前缀字符串与s[i-1]结尾的后缀字符串匹配。

        s:    ________________ * * * * * * * * * * * * * * * *  X _________
                                                            i-1 i
        p:                     * * * * * * * * * * * * * * * *  Y _________
                                                            j-1 j
        此时如果有s[i]==p[j]（即X==Y），那么显然已知匹配的长度自然就可以延长1位，即dp[i]=j+1.

        那么如果没有X==Y怎么办呢？我们把眼光放到suf[j-1]上，记j'=suf[j-1]，那么p就有一段长度为j'的前缀字符串与p[j-1]结尾的后缀字符串匹配.

        s:    ________________ _______________________ + + + +  X _________
                                                            i-1 i
        p:                     + + + + Z _____________ + + + +  Y _________
                                    j'-1                    j-1 j
        不难推导出p[0:j'-1]也与s[i-j':i-1]必然是相等的。所以我们在计算dp[i]的时候可以利用这段长度：只要Z==X，那么dp[i] = j'+1.

        如果Z和X仍然不等，那么我们就再把眼光放到suf[j'-1]上，即j''=suf[j'-1]，同理推导出p[0:j''-1]也与s[i-j'':i-1]必然是相等的，此时只要考察s[i]和p[j'']是否相等个，就可以将dp[i]推至j''+1...

        依次类推j',j'',j'''..直到我们找到合适的j（注意j可以是0），使得p里面长度为j的前缀字符串，恰好等于截止s[i-1]的后缀字符串。于是dp[i]能否突破0，就取决于dp[j]+(s[i]==p[j])了。代码如下：

        for (int i=1; i<n; i++)
        {
        // compute dp[i]
        int j = dp[i-1];
        while (j>0 && p[j]!=s[i])
            j = suf[j-1];
        dp[i]  = j+(p[j]==s[i]);
        }
        注意dp[0]需要单独计算：dp[0] = (s[0]==p[0])

        当我们计算得到第一处dp[i]=p.size()时，就说明找到了完整匹配的模式串。

        Sunday算法
        预处理needle构造一个shift数组。该数组记录了needle里的字符最后一次出现的位置距离needle结尾的位移。

        举个例子，最开始将haystack和needle左对齐，如果发现needle和haystack匹配不上，就考察haystack[n]的字符（即needle长度n之后的第一个字符）。

        如果这个字符在shift里有记录，那么将needle整体右移相应的位移，这样使得haystack[n]和needle里最后一次出现的字符（这两个字符相同）对齐，再从needle首字符开始逐一判断匹配。

        如果这个字符不存在needle里面，则shift里默认给n+1，即将整个needle右移至haystack[n]之后，再从needle首字符开始逐一判断匹配。

    """


    def doit_kmp(self, haystack: str, needle: str) -> int:

        pattern = [0, 0]
        j = 0
        for i in range(1, len(needle)):

            while j > 0 and needle[j] != needle[i]:
                j = pattern[j]
            
            if needle[j] == needle[i]:
                j += 1

            pattern.append(j)
        
        m, n = len(haystack), len(needle)
        j = 0

        for i in range(m):

            while j > 0 and haystack[i] != needle[j]:
                j = pattern[j]

            if haystack[i] == needle[j]:
                j += 1

            if j == n:
                return i - n + 1

        return -1


    """
        Approach 3: Rabin Karp: Constant Time Slice
        Let's now design the algorithm with \mathcal{O}(N)O(N) time complexity even in the worst case. The idea is simple: move along the string, generate hash of substring in the sliding window and compare it with the reference hash of the needle string.

        There are two technical problems:

        How to implement a string slice in a constant time?

        How to generate substring hash in a constant time?

        String slice in a constant time

        Strings are immutable in Java and Python, and to move sliding window in a constant time one has to convert string to another data structure, for example, to integer array of ascii-values.

        Rolling hash: hash generation in a constant time

        To generate hash of array of length L, one needs \mathcal{O}(L)O(L) time.

        How to have constant time of hash generation? Use the advantage of slice: only one integer in, and only one - out.

        That's the idea of rolling hash. Here we'll implement the simplest one, polynomial rolling hash. Beware that's polynomial rolling hash is NOT the Rabin fingerprint.

        Since one deals here with lowercase English letters, all values in the integer array are between 0 and 25 : arr[i] = (int)S.charAt(i) - (int)'a'.
        So one could consider string abcd -> [0, 1, 2, 3] as a number in a numeral system with the base 26. Hence abcd -> [0, 1, 2, 3] could be hashed as

        h(0) = 0 * 26^3 + 1 * 26 ^2 + 2 * 26^1 + 3 * 26^0
        
        Let's write the same formula in a generalised way, where c_i is an integer array element and a = 26 is a system base.

        h(0) = c0*a^(l-1) + c1*a^(l-2) + ... + ci*a^(l-1-i) + ... + c(l-1)*a^(1) + c(l)*a^(0)

        h(0) = 

        Now let's consider the slice abcd -> bcde. For int arrays that means [0, 1, 2, 3] -> [1, 2, 3, 4], to remove number 0 and to add number 4.

        Now hash regeneration is perfect and fits in a constant time. There is one more issue to address: possible overflow problem.

        How to avoid overflow a^L could be a large number and hence the idea is to set limits to avoid the overflow. To set limits means to limit a hash by a given number called modulus and use everywhere not hash itself but h % modulus.

        It's quite obvious that modulus should be large enough, but how large? Here one could read more about the topic, for the problem here 2^{31}2 
        31
        is enough.

        Algorithm

        Compute the hash of substring haystack.substring(0, L) and reference hash of needle.substring(0, L).

        Iterate over the start position of possible match: from 1 to N - L.

        Compute rolling hash based on the previous hash value.

        Return start position if the hash is equal to the reference one.

        Return -1, that means that needle is not found.

        Implementation


        Complexity Analysis

        Time complexity: O(N), one computes the reference hash of the needle string in \mathcal{O}(L)O(L) time, and then runs a loop of (N - L) steps with constant time operations in it.

        Space complexity: O(1).
    """
    def doit_rollinghash(self, haystack: str, needle: str) -> int:
        L, n = len(needle), len(haystack)
        if L > n:
            return -1
        
        # base value for the rolling hash function
        a = 26
        # modulus value for the rolling hash function to avoid overflow
        modulus = 2**31
        
        # lambda-function to convert character to integer
        h_to_int = lambda i : ord(haystack[i]) - ord('a')
        needle_to_int = lambda i : ord(needle[i]) - ord('a')
        
        # compute the hash of strings haystack[:L], needle[:L]
        h = ref_h = 0
        for i in range(L):
            h = (h * a + h_to_int(i)) % modulus
            ref_h = (ref_h * a + needle_to_int(i)) % modulus
        if h == ref_h:
            return 0
              
        # const value to be used often : a**L % modulus
        aL = pow(a, L, modulus) 
        for start in range(1, n - L + 1):
            # compute rolling hash in O(1) time
            h = (h * a - h_to_int(start - 1) * aL + h_to_int(start + L - 1)) % modulus
            if h == ref_h:
                return start

        return -1

    """
        Approach 2: Two Pointers: Linear Time Slice
        Drawback of the previous algorithm is that one compares absolutely all substrings of length L with the needle. There is no need to that.

        First, let's compare only substrings which starts from the first character in the needle substring.

        fig

        Second, let's compare the characters one by one and stop immediately in the case of mismatch.

        fig

        Here it was impossible to manage the full match up to the length of needle string, which is L = 5. Let's backtrack then. Note, that we move pn pointer back to the position pn = pn - curr_len + 1, and not to the position pn = pn - curr_len, since this last one was already investigated.

        fig

        Let's try again. Here we've managed to get the full match during the second attempt, so let's return the start position of that match, pn - L.

        fig

        Algorithm

        Move pn till you'll find the first character of the needle string in the haystack.

        Compute the max string match by increasing pn, pL and curr_len in the case of equal characters.

        If you managed to get the full match, curr_len == L, return the start position of that match, pn - L.

        If you didn't, backtrack: pn = pn - curr_len + 1, pL = 0, curr_len = 0.

        Implementation


        Complexity Analysis

        Time complexity: \mathcal{O}((N - L)L)O((N−L)L) in the worst case of numerous almost complete false matches, and \mathcal{O}(N)O(N) in the best case of one single match.

        Space complexity: \mathcal{O}(1)O(1).
    """

    def strStr(self, haystack: str, needle: str) -> int:
        L, n = len(needle), len(haystack)
        if L == 0:
            return 0

        pn = 0
        while pn < n - L + 1:
            # find the position of the first needle character
            # in the haystack string
            while pn < n - L + 1 and haystack[pn] != needle[0]:
                pn += 1
            
            # compute the max match string
            curr_len = pL = 0
            while pL < L and pn < n and haystack[pn] == needle[pL]:
                pn += 1
                pL += 1
                curr_len += 1
            
            # if the whole needle string is found,
            # return its start position
            if curr_len == L:
                return pn - L
            
            # otherwise, backtrack
            pn = pn - curr_len + 1
            
        return -1