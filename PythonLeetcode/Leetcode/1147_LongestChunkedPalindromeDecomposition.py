"""
1147. Longest Chunked Palindrome Decomposition

Return the largest possible k such that there exists a_1, a_2, ..., a_k such that:

Each a_i is a non-empty string;
Their concatenation a_1 + a_2 + ... + a_k is equal to text;
For all 1 <= i <= k,  a_i = a_{k+1 - i}.


Example 1:

Input: text = "ghiabcdefhelloadamhelloabcdefghi"
Output: 7
Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
Example 2:

Input: text = "merchant"
Output: 1
Explanation: We can split the string on "(merchant)".
Example 3:

Input: text = "antaprezatepzapreanta"
Output: 11
Explanation: We can split the string on "(a)(nt)(a)(pre)(za)(tpe)(za)(pre)(a)(nt)(a)".
Example 4:

Input: text = "aaa"
Output: 3
Explanation: We can split the string on "(a)(a)(a)".


Constraints:

text consists only of lowercase English characters.
1 <= text.length <= 1000


"""
import functools

class LongestChunkedPanlindrome:

    def doit_dp(self, text: str) -> int:

        @functools.lru_cache(None)
        def search(i, j):

            if i >= j:
                return 0

            ans = 1
            for k in range(1, (j - i) // 2 + 1):

                if text[i:i + k] == text[j - k:j]:
                    ans = max(ans, search(i + k, j - k) + 2)

            return ans

        return search(0, len(text))

    def doit_dp_dfs(self, text: str) -> int:
        def solve(i,j):
            ans = 0
            for k in range(i+1,j+1):
                if i == j-k+i and k == j:
                    return 1
                elif text[i:k] == text[j-k+i:j]:
                    return 2 + solve(k,j-k+i)
            return ans
        return solve(0,len(text))


if __name__ == '__main__':

    LongestChunkedPanlindrome().doit_dp("ghiabcdefhelloadamhelloabcdefghi")

    LongestChunkedPanlindrome().doit_dp("elvtoelvto")


