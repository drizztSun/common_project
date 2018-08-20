


# 393. UTF-8 Validation

# A character in UTF8 can be from 1 to 4 bytes long,
# subjected to the following rules:

# For 1-byte character, the first bit is a 0, followed by its unicode code.
# For n-bytes character, the first n-bits are all one's, the n+1 bit is 0, followed by n-1 bytes with most significant 2 bits being 10.
# This is how the UTF-8 encoding would work:

#   Char. number range  |        UTF-8 octet sequence
#      (hexadecimal)    |              (binary)
#   --------------------+---------------------------------------------
#   0000 0000-0000 007F | 0xxxxxxx
#   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
#   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
#   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
# Given an array of integers representing the data, return whether it is a valid utf-8 encoding.


class validUtf8(object):


    def doit(self, data):
        """
        :type data: List[int]
        :rtype: bool
        """
        def check(data, s, n):
            for i in range(s+1, s+n+1):
                if i >= len(data) or data[i] >> 6 != 0b10:             
                    return False
            return True

        s = 0
        while s < len(data):

            num = data[s]

            if num >> 5 == 0b110 and check(data, s, 1):
                s += 2
            elif num >> 4 == 0b1110 and check(data, s, 2):
                s += 3
            elif num >> 3 == 0b11110 and check(data, s, 3):
                s += 4
            elif num < 128:
                s += 1
            else:
                return False

        return True



    def doit(self, data):
        """
        :type data: List[int]
        :rtype: bool
        """
        def isSuffix(c, b):
            return c == b
    
        s = 0

        while s < len(data):

            if data[s] < 0b10000000:
                s += 1
            else:
                number = 0
                if isSuffix(data[s] >> 5 , 0b110):
                    number = 1
                if isSuffix(data[s] >> 4, 0b1110):
                    number = 2
                if isSuffix(data[s] >> 3, 0b11110):
                    number = 3

                if number == 0 or s + number >= len(data):
                    return False
    
                while number :
                    s += 1
                    if not isSuffix(data[s] >> 6, 0b10):
                        return False 
                    number -= 1

                s += 1

        return s == len(data)
                    
                
                        
                
                
            
                




if __name__ == "__main__":


    res = validUtf8().doit([197,130,1])

    res = validUtf8().doit([255])

    res = validUtf8().doit([235,140,4])

    res = validUtf8().doit([248,130,130,130])

    pass
