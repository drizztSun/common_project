
# 159 Longest SubString with At Most Two Distinct Characters

# Given a string, find the length of the longest substring T that contains at most 2 distinct characters.
# For example, Given s = “eceba”,
# T is "ece" which its length is 3.


class LongestSubstringWithTwoDistictCharacter:

    def doit1(self, s):
        """
        type : str
        rtype : int
        """
        if len(s) <= 1:
            return len(s)

        # i is front pointer, k is back pointer
        # j is ChangePoint, like 'eeecd', j will point the third 'e'

        j, i = -1, 0
        best = 0

        for k in range(1, len(s)):
            # When s[k] != s[k-1] like 'ce', it means new different char incoming
            # J needs to point 'k-1', which is the last point of this change 'eeeeccc', like last 'e'
            #     

            if s[k] != s[k-1]:
                # if s[k] != s[j], it means like "eeeecccckkk", k is pointing 'k' and j is pointing 'e'
                # so it means in window, we get three chars. so we need to move 'i'
                # moving 'i' to j+1, 'c', so window change to only two character
                if j != -1 and s[k] != s[j]:
                    i = j+1
                j = k-1

            best = max(best, k - i + 1)

        return best

    # <hashTable> <double pointer>
    def doit(self, s):
        """
        type : str
        rtype : int
        """
        counts = [0] * 256
        i = best = numChars = 0
        
        # j is front pointer, i is back pointer
        for j in range(len(s)):

            if counts[ord(s[j])] == 0:
                numChars += 1

            counts[ord(s[j])] += 1


            while i < len(s) and numChars > 2:
                counts[ord(s[i])] -= 1
                if counts[ord(s[i])] == 0:
                    numChars -= 1
                i += 1

            best = max(best, j - i + 1)
              
        return best           

    def doit1(self, s):
        """
        type : str
        rtype : int
        """
        counts = [0] * 256
        i = numChars = best = 0                

        # i is FrontP, j is RearP
        for j in range(len(s)):

            while i < len(s) and numChars <= 2:

                if counts[ord(s[i])] == 0:
                    numChars += 1

                if numChars <= 2:
                    best = max(best, i - j + 1)

                counts[ord(s[i])] += 1
                i += 1 

            counts[ord(s[j])] -= 1
            if counts[ord(s[j])] == 0:
                numChars -= 1

        return best
            

    def doit1(self, s):
        """
        type : str
        rtype : int
        """
        import collections
        D = collections.defaultdict(int)
        i = best = 0

        for j in range(len(s)):

            while i < len(s) and len(D.keys()) <= 2:
                D[s[i]] += 1
                if len(D.keys()) <= 2:
                    best = max(best, i - j + 1)
                i += 1

            D[s[j]] -= 1
            if D[s[j]] == 0:
                del D[s[j]]

        return best

if __name__=="__main__":

    res = LongestSubstringWithTwoDistictCharacter().doit("eceba")

    res = LongestSubstringWithTwoDistictCharacter().doit("eecebaaaa")

    

    pass
