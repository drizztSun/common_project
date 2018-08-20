


# 340 Longest Sub String With At Most K Distinct Characters

# Given a string, find the length of the longest substring T that contains at most k distinct characters.
# For example, Given s = "eceba" and k = 2,
# T is "ece" which its length is 3.

class KthDistinctChar :

    def doit(self, s, k):
        """
        type: str
        type: int
        rtype: int
        """
        # j is front pointer, i is back pointer
        counter = [0] * 256
        i = numChars = k = 0

        for j in range(len(s)):

            if counter[ord(s[j])] == 0:
                numChars += 1

            counter[ord(s[j])] += 1

            while i < len(s) and  numChars > k:
                counter[ord(s[i])] -= 1
                if counter[ord(s[i])] == 0:
                    numChars -= 1
                i += 1

            best = max(best, j - i + 1)

        return best
        

    def doit(self, s, k):
        """
        type: str
        type: int
        rtype: int
        """
        # j is front pointer, i is back pointer
        counter = [0] * 256
        j = best = numChars = 0        

        for i in range(len(s)):

            while j < len(s) and numChars <= 2:
                if counter[ord(s[j])] == 0:
                    numChars += 1 
                                   
                counter[ord(s[j])] += 1

                if numChars > 2:
                    break

                best = max(best, i - j + 1)
                j += 1


            if counter[ord(s[j])] == 1:
                numChars -= 1
                        
            counter[ord(s[j])] -= 1
        
        return numChars

if __name__=="__main__":

    

    res = KthDistinctChar().doit("eceba", 2)

    pass        