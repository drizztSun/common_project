



# 423. Reconstruct Original Digits from English


# Given a non-empty string containing an out-of-order English representation of digits 0-9, output the digits in ascending order.

# Note:
# Input contains only lowercase English letters.
# Input is guaranteed to be valid and can be transformed to its original digits. That means invalid inputs such as "abc" or "zerone" are not permitted.
# Input length is less than 50,000.

# Example 1:
# Input: "owoztneoer"

# Output: "012"

# Example 2:
# Input: "fviefuro"

# Output: "45"

class originalDigits:


# The even digits all have a unique letter while the odd digits all don�t:
# zero: Only digit with z
# two: Only digit with w
# four: Only digit with u
# six: Only digit with x
# eight: Only digit with g
# The odd ones for easy looking, each one�s letters all also appear in other digit words:
# one, three, five, seven, nine

    def doit(self, s):
        """
s        :type s: str
        :rtype: str
        """
        nums = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]

        D = {}
        for c in s:
            D[c] = D.get(c, 0) + 1

        result = []
        index = {"z":0, "x":6, "w":2, 'u': 4, 'g':8, 'f':5, 'r':3, 'o':1, 'v':7, 'i':9}
        for c in "zxwugfrovi":
            if c in D and D[c] > 0:
                word = nums[index[c]]
                s = D[c]
                result.extend([index[c]] * s)
                for w in word:
                    D[w] -= s
        
        result.sort()
        return ''.join(map(str, result))



    def doit1(self, s):
        """
        :type s: str
        :rtype: str
        """
        import collections
        d1 = {i: 0 for i in 'wxugzvhrfstoine'}
        d2 = {i: 0 for i in range(10)}

        for i in s:
            assert i in d1
            d1[i] += 1

        d2[2] = d1['w']
        d2[6] = d1['x']
        d2[4] = d1['u']
        d2[8] = d1['g']
        d2[0] = d1['z']
        d2[3] = d1['h'] - d2[8]
        d2[5] = d1['f'] - d2[4]
        d2[7] = d1['s'] - d2[6]
        d2[1] = d1['o'] - d2[0] - d2[2] - d2[4]
        d2[9] = d1['i'] - d2[5] - d2[6] - d2[8]
        assert d1['v'] == d2[5] + d2[7]
        assert d1['r'] == d2[0] + d2[3] + d2[4]
        assert d1['t'] == d2[2] + d2[3] + d2[8]
        assert d1['n'] == d2[1] + d2[7] + 2 * d2[9]
        assert d1['e'] == d2[0] + d2[1] + 2 * d2[3] + d2[5] + 2 * d2[7] + d2[8] + d2[9]

        result = []
        for i in range(10):
            for j in range(d2[i]):
                result.append(str(i))
        return ''.join(result)


if __name__=="__main__":



    res = originalDigits().doit("owoztneoer") #012


    res = originalDigits().doit("fviefuro") # 45

    res = originalDigits().doit("zerozero") # 00

    res = originalDigits().doit("nnei") # 9

    pass

        