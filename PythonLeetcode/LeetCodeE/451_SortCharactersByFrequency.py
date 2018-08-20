


# 451. Sort Characters By Frequency

# Given a string, sort it in decreasing order based on the frequency of characters.

# Example 1:

# Input:
# "tree"
# Output:
# "eert"

# Explanation:
# 'e' appears twice while 'r' and 't' both appear once.
# So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.

# Example 2:

# Input:
# "cccaaa"
# Output:
# "cccaaa"

# Explanation:
# Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
# Note that "cacaca" is incorrect, as the same characters must be together.

# Example 3:

# Input:
# "Aabb"
# Output:
# "bbAa"

# Explanation:
# "bbaA" is also a valid answer, but "Aabb" is incorrect.
# Note that 'A' and 'a' are treated as two different characters.



class frequencySort(object):

    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        alphabet = {}
        for c in s:
            alphabet[c] = alphabet.get(c, 0) + 1
        
        data = []
        for c in alphabet.keys():
            data.append((alphabet[c], c))

        data.sort(key=lambda x: x[0], reverse=1)
        
        res = ''
        for c in data:
            res += c[1] * c[0]

        return res

    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        dic = collections.defaultdict(int)
        for i in s:
            dic[i]+=1

        ans = ''
        for i in sorted(dic, key = dic.get, reverse=True):
            ans += i * dic[i]
        return ans


if __name__=="__main__":

    res = frequencySort().doit("tree")

    res = frequencySort().doit("cccaaa")

    res = frequencySort().doit("Aabb")

    res = frequencySort().doit("loveleetcode")
    
    pass