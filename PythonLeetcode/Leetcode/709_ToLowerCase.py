# 709. To Lower Case

# Implement function ToLowerCase() that has a string parameter str, and returns the same string in lowercase.

# Example 1:

# Input: "Hello"
# Output: "hello"
# Example 2:

# Input: "here"
# Output: "here"
# Example 3:

# Input: "LOVELY"
# Output: "lovely"


class ToLowerCase:
    def doit(self, str):
        """
        :type str: str
        :rtype: str
        """
        return ''.join([chr(ord(c) + 32) if ord(c) in range(65, 91) else c for c in str]) 
		
	def doit1():
	    """
        :type str: str
        :rtype: str
        """
	    result = ""
        for c in str:
            if ord(c) in range(65, 91):
                result += chr(ord(c) + 32))
            else:
                result += c

        return result