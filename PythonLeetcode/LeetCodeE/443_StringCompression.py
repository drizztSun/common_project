



# 443. String Compression


# Given an array of characters, compress it in-place.

# The length after compression must always be smaller than or equal to the original array.

# Every element of the array should be a character (not int) of length 1.

# After you are done modifying the input array in-place, return the new length of the array.


# Follow up:
# Could you solve it using only O(1) extra space?


# Example 1:
# Input:
# ["a","a","b","b","c","c","c"]

# Output:
# Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

# Explanation:
# "aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".

# Example 2:
# Input:
# ["a"]

# Output:
# Return 1, and the first 1 characters of the input array should be: ["a"]

# Explanation:
# Nothing is replaced.

# Example 3:
# Input:
# ["a","b","b","b","b","b","b","b","b","b","b","b","b"]

# Output:
# Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

# Explanation:

# Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
# Notice each digit has it's own entry in the array.

# All characters have an ASCII value in [35, 126].
# 1 <= len(chars) <= 1000.




class compress:
    def doit(self, chars):
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


    def doit(self, chars):
        """
        :type chars: List[str]
        :rtype: int
        """
        left = i = 0
        
        while i < len(chars):
            
            char, length = chars[i], 1
            while (i + 1) < len(chars) and char == chars[i + 1]:
                length, i = length + 1, i + 1
                
            chars[left] = char
            
            if length > 1:
                len_str = str(length)
                
                chars[left + 1:left + 1 + len(len_str)] = len_str
                
                left += len(len_str)
            
            left, i = left + 1, i + 1
            
        return left

                
            
        

if __name__=="__main__":

    A = ["a","a","b","b","c","c","c"]
    res = compress().doit(A)


    pass

    
        
