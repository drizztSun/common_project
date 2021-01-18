"""
1062. Longest Repeating Substring

Given a string S, find out the length of the longest repeating substring(s). Return 0 if no repeating substring exists.



Example 1:

Input: S = "abcd"
Output: 0
Explanation: There is no repeating substring.
Example 2:

Input: S = "abbaba"
Output: 2
Explanation: The longest repeating substrings are "ab" and "ba", each of which occurs twice.
Example 3:

Input: S = "aabcaabdaab"
Output: 3
Explanation: The longest repeating substring is "aab", which occurs 3 times.
Example 4:

Input: S = "aaaaa"
Output: 4
Explanation: The longest repeating substring is "aaaa", which occurs twice.


Constraints:

The string S consists of only lowercase English letters from 'a' - 'z'.
1 <= S.length <= 1500



"""


class LongestRepeatingSubstring:

    """
        O(n^2)
    """
    def doit_dp_(self, S: str) -> int:

        n = len(S)
        S = '#' + S

        dp = [[0 for _ in range(n+1)] for _ in range(n+1)]
        ans = 0

        for i in range(1, n+1):
            for j in range(1, n+1):

                if i != j and S[i] == S[j]:
                    dp[i][j] = dp[i-1][j-1] + 1

                ans = max(ans, dp[i][j])

        return ans


    """
        Approach 1: Binary Search + Hashset of Already Seen Strings
        The idea is straightforward :

        Move a sliding window of length L along the string of length N.

        Check if the string in the sliding window is in the hashset of already seen strings.

        If yes, the duplicate substring is right here.

        If not, save the string in the sliding window in the hashset.

        Obvious drawback of this approach is a huge memory consumption in the case of large strings.

        Complexity Analysis

        Time complexity : \mathcal{O}(N \log N)O(NlogN) in the average case and \mathcal{O}(N^2)O(N 
        2
        ) in the worst case. One needs \mathcal{O}((N - L)L)O((N−L)L) for one duplicate check, and one does up to \mathcal{O}(\log N)O(logN) checks. Together that results in \mathcal{O}(\sum\limits_{L}{(N - L)L})O( 
        L
        ∑
        ​	
        (N−L)L), i.e. in \mathcal{O}(N \log N)O(NlogN) in the average case and in \mathcal{O}(N^2)O(N 
        2
        ) in the worst case of L close to N/2N/2.

        Space complexity : \mathcal{O}(N^2)O(N 
        2
        ) to keep the hashset.
    """
    def doit_binary_search(self, S: str) -> str:

        n = len(S)

        def search(L: int, n: int, S: str) -> str:
            """
            Search a substring of given length
            that occurs at least 2 times.
            @return start position if the substring exits and -1 otherwise.
            """
            seen = set()
            for start in range(0, n - L + 1):
                tmp = S[start:start + L]
                if tmp in seen:
                    return start
                seen.add(tmp)
            return -1
        
        # binary search, L = repeating string length
        left, right = 1, n
        
        while left <= right:
            
            L = left + (right - left) // 2

            if search(L, n, S) != -1:
                left = L + 1
        
            else:
                right = L - 1
               
        return left - 1


    """
        Approach 2: Binary Search + Hashset of Hashes of Already Seen Strings
        To reduce the memory consumption by the hashset structure, one could store not the full strings, but their hashes.

        The drawback of this approach is a time performance, which is still not always linear.
    """

        
    def longestRepeatingSubstring(self, S: str) -> str:
        n = len(S)

        def search(L: int, n: int, S: str) -> str:
            """
            Search a substring of given length
            that occurs at least 2 times.
            @return start position if the substring exits and -1 otherwise.
            """
            seen = set()
            for start in range(0, n - L + 1):
                tmp = S[start:start + L]
                h = hash(tmp)
                if h in seen:
                    return start
                seen.add(h)
            return -1
        
        # binary search, L = repeating string length
        left, right = 1, n
        while left <= right:
            L = left + (right - left) // 2
            if self.search(L, n, S) != -1:
                left = L + 1
            else:
                right = L - 1
               
        return left - 1

    """
        Approach 3: Binary Search + Rabin-Karp
        Rabin-Karp algorithm is used to perform a multiple pattern search in a linear time and with a moderate memory consumption suitable for the large strings.

        The linear time implementation of this idea is a bit tricky because of two technical problems:

        How to implement a string slice in a constant time?

        Hashset memory consumption could be huge for very long strings. One could keep the string hash instead of string itself but hash generation costs \mathcal{O}(L)O(L) for the string of length L, and the complexity of algorithm would be \mathcal{O}((N - L)L)O((N−L)L), N - L for the slice and L for the hash generation. One has to think how to generate hash in a constant time here.

        Let's now address these problems.

        String slice in a constant time

        That's a very language-dependent problem. For the moment for Java and Python there is no straightforward solution, and to move sliding window in a constant time one has to convert string to another data structure.

        The simplest solution both for Java and Python is to convert string to integer array of ascii-values.

        Rolling hash : hash generation in a constant time

        To generate hash of array of length L, one needs \mathcal{O}(L)O(L) time.

        Rabin-Karp algorithm

        search(L) :

        Compute the hash of substring S.substring(0, L) and initiate the hashset of already seen substring with this value.

        Iterate over the start position of substring : from 1 to N - LN−L.

        Compute rolling hash based on the previous hash value.

        Return start position if the hash is in the hashset, because that means one met the duplicate.

        Otherwise, add hash in the hashset.

        Return -1, that means there is no duplicate string of length L.

        Implementation



    """    
    def longestRepeatingSubstring(self, S: str) -> str:
        n = len(S)
        # convert string to array of integers
        # to implement constant time slice
        nums = [ord(S[i]) - ord('a') for i in range(n)]
        # base value for the rolling hash function
        a = 26
        # modulus value for the rolling hash function to avoid overflow
        modulus = 2**24

        def search(L: int, a: int, modulus: int, n: int, nums: list) -> str:
            """
            Rabin-Karp with polynomial rolling hash.
            Search a substring of given length
            that occurs at least 2 times.
            @return start position if the substring exits and -1 otherwise.
            """
            # compute the hash of string S[:L]
            h = 0
            for i in range(L):
                h = (h * a + nums[i]) % modulus
                
            # already seen hashes of strings of length L
            seen = {h} 
            # const value to be used often : a**L % modulus
            aL = pow(a, L, modulus) 
            for start in range(1, n - L + 1):
                # compute rolling hash in O(1) time
                h = (h * a - nums[start - 1] * aL + nums[start + L - 1]) % modulus
                if h in seen:
                    return start
                seen.add(h)
            return -1
        
        # binary search, L = repeating string length
        left, right = 1, n
        while left <= right:
            L = left + (right - left) // 2
            if self.search(L, a, modulus, n, nums) != -1:
                left = L + 1
            else:
                right = L - 1
               
        return left - 1