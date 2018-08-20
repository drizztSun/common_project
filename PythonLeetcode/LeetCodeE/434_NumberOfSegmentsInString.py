



# 434. Number of Segments in a String

# Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

# Please note that the string does not contain any non-printable characters.

# Example:

# Input: "Hello, my name is John"


class countSegments(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        prev = ''
        nums = 0
        for i, c in enumerate(s):
            if (c == ' ' and prev not in(' ', '')) or (i == len(s) - 1 and c != ' '):
                nums += 1
            prev = c

        return nums


    def doit1(self, s):
        """
        :type s: str
        :rtype: int
        """
        # s = s.split(' ')
        # s = [x for x in s if x!= '']
        # return len(s)

        return len(s.split())

   def doit2(self, s):
        """
        :type s: str
        :rtype: int
        """
        count = 0
        state = 0
        for i in range(0, len(s)):
            if state == 0:
                if s[i] != ' ':
                    count += 1
                    state = 1
            else:
                if s[i] == ' ':
                    state = 0
        
        return counts
    

if __name__=="__main__":

        res = countSegments().doit("       ")

        res = countSegments().doit("a")

        res = countSegments().doit("a, b, c")


        res = countSegments().doit("Hello, my name is John")


        pass
