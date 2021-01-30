"""
1461. Check If a String Contains All Binary Codes of Size K


Given a binary string s and an integer k.

Return True if every binary code of length k is a substring of s. Otherwise, return False.

 

Example 1:

Input: s = "00110110", k = 2
Output: true
Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indicies 0, 1, 3 and 2 respectively.
Example 2:

Input: s = "00110", k = 2
Output: true
Example 3:

Input: s = "0110", k = 1
Output: true
Explanation: The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring. 
Example 4:

Input: s = "0110", k = 2
Output: false
Explanation: The binary code "00" is of length 2 and doesn't exist in the array.
Example 5:

Input: s = "0000000001011100", k = 4
Output: false
 

Constraints:

1 <= s.length <= 5 * 10^5
s consists of 0's and 1's only.
1 <= k <= 20
"""


class AllBinaryCodeOfSizeK:

    """
        Approach 1: Set
        Recall (part of) the problem:

        Return True if every binary code of length k is a substring of s. Otherwise, return False.

        We just need to check every substring with length k until we get all the possible binary codes. Since there are two possible char for each place: 0 or 1, there will be 2^k possible binary code.

        We can continue until we count up to 2^k. We will return false if did not get 2^k counts after iteration. To prevent repeated counting, a set can be used to store the result we previously counted.

        Note that 1 << k is the same as 2^k, and we use the previous one here.


        If you like short code, a shorter version in Python presented below. Also, when you shorten codes, it is important that the shortened version still keeps readability.

        Complexity Analysis

        Let N be the length of s.

        Time complexity: O(NK). We need to iterate the string, and use O(K) to calculate the hash of each substring.

        Space complexity: O(NK). There are at most NN strings with length KK in the set.
    """
    def doit_hashtable(self, s: str, k: int) -> bool:
        need = 1 << k
        got = set()

        for i in range(k, len(s)+1):
            tmp = s[i-k:i]

            if tmp not in got:
                got.add(tmp)
                need -= 1
                if need == 0:
                    return True

        return need == 0

    def doit_(self, s: str, k: int) -> bool:
        got = {s[i - k : i] for i in range(k, len(s) + 1)}
        return len(got) == 1 << k


    """
        Approach 2: Hash
        Maybe you think the approach above is not fast enough. Let's write the hash function ourselves to improve the speed.

        Note that we will have at most 2^k2 
        k
        string, can we map each string to a number in [00, 2^k-12 
        k
        −1]?

        We can. Recall the binary number, we can treat the string as a binary number, and take its decimal form as the hash value. In this case, each binary number has a unique hash value. Moreover, the minimum is all 0, which is zero, while the maximum is all 1, which is exactly 2^k-12 
        k
        −1.

        Because we can directly apply bitwise operations to decimal numbers, it is not even necessary to convert the binary number to a decimal number explicitly.

        What's more, we can get the current hash from the last one. This method is called Rolling Hash. All we need to do is to remove the most significant digit and to add a new least significant digit with bitwise operations.

        For example, say s="11010110", and k=3, and we just finish calculating the hash of the first substring: "110" (hash is 4+2=6, or 110). Now we want to know the next hash, which is the hash of "101".

        We can start from the binary form of our hash, which is 110. First, we shift left, resulting 1100. We do not need the first digit, so it is a good idea to do 1100 & 111 = 100. The all-one 111 helps us to align the digits. Now we need to apply the lowest digit of "101", which is 1, to our hash, and by using |, we get 100 | last_digit = 100 | 1 = 101.

        Write them together, we have: new_hash = ((old_hash << 1) & all_one) | last_digit_of_new_hash.

        With rolling hash method, we only need \mathcal{O}(1)O(1) to calculate the next hash, because bitwise operations (&, <<, |, etc.) are only cost \mathcal{O}(1)O(1).

        This time, we can use a simple list to store our hashs, and we will not have hash collision. Those advantages make this approach faster.


        Let NN be the length of s.

        Time complexity: O(N). We need to iterate the string, and use \mathcal{O}(1)O(1) to calculate the hash of each substring.

        Space complexity: O(2 k). There are 2^k elements in the list.
    """
    def doit_rollinghash(self, s: str, k: int) -> bool:
        need = 1 << k
        got = [False] * need
        all_one = need - 1
        hash_val = 0

        for i in range(len(s)):
            # calculate hash for s[i-k+1:i+1]
            hash_val = ((hash_val << 1) & all_one) | (int(s[i]))
            # hash only available when i-k+1 > 0
            if i >= k-1 and got[hash_val] is False:
                got[hash_val] = True
                need -= 1
                if need == 0:
                    return True
        return False