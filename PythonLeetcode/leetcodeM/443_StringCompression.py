"""
443. String Compression

Given an array of characters chars, compress it using the following algorithm:

Begin with an empty string s. For each group of consecutive repeating characters in chars:

If the group's length is 1, append the character to s.
Otherwise, append the character followed by the group's length.
The compressed string s should not be returned separately, but instead be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the array.


Follow up:
Could you solve it using only O(1) extra space?



Example 1:

Input: chars = ["a","a","b","b","c","c","c"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".
Example 2:

Input: chars = ["a"]
Output: Return 1, and the first character of the input array should be: ["a"]
Explanation: The only group is "a", which remains uncompressed since it's a single character.
Example 3:

Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".
Example 4:

Input: chars = ["a","a","a","b","b","a","a"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","3","b","2","a","2"].
Explanation: The groups are "aaa", "bb", and "aa". This compresses to "a3b2a2". Note that each group is independent even if two groups have the same character.


Constraints:

1 <= chars.length <= 2000
chars[i] is a lower-case English letter, upper-case English letter, digit, or symbol.

"""


class StringCompress:

    def doit_(self, chars):
        """
        :type chars: List[str]
        :rtype: int
        """
        res = []
        current, amount = '', 0
        j = 0
        for i in range(len(chars) + 1):
        
            if i == len(chars) or chars[i] != current:
                if amount != 0 and current:
                    chars[j] = current
                    j += 1
                    if amount > 1:
                        nums = str(amount)
                        for s in nums:
                            chars[j] = s
                            j += 1
                    
                    current = ''
                    amount = 0

            if i < len(chars):
                current = chars[i]
                amount += 1

        return j

    # O(1)
    def doit_(self, a: list) -> int:

        i, j = 0, 0
        cnt = 0
        
        while j < len(a) + 1:
            
            if j < len(a) and a[i] == a[j]:
                cnt += 1
            else :
                if cnt == 1:
                    i += 1
                else:
                    for c in str(cnt):
                        a[i+1] = c
                        i += 1
                    i += 1
                cnt = 1
                if j < len(a) and i < len(a):
                    a[i] = a[j]
            j += 1
            
        return i

    def compress(self, chars):
        anchor, write = 0, 0
        for read, c in enumerate(chars):
            if read + 1 == len(chars) or chars[read + 1] != c:
                chars[write] = chars[anchor]
                write += 1
                if read > anchor:
                    for digit in str(read - anchor + 1):
                        chars[write] = digit
                        write += 1
                anchor = read + 1
        return write

if __name__ == '__main__':

    StringCompress().doit_(["a","a","b","b","c","c","c"])

    StringCompress().doit_(["a","b","b","b","b","b","b","b","b","b","b","b","b"])
