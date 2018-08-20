

# 246 Strobogrammatic Number

# A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

# Write a function to determine if a number is strobogrammatic. The number is represented as a string.

# For example, the numbers "69", "88", and "818" are all strobogrammatic.

class StrobogrammaticNumber:

    def doit(num):

        i, j = 0, len(num) - 1
        charMap = {'1':'1', '6':'9', '9':'6', '8':'8', '0':'0'}        

        while i <= j:
            if num[i] in charMap and charMap[num[i]] == num[j]:
                i += 1
                j -= 1
            else :
                return False

        return True
            


# 247 Strobogrammatic Number II

# A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
# Find all strobogrammatic numbers that are of length = n.
# For example,
# Given n = 2, return ["11","69","88","96"].

# Hint:
# Try to use recursion and notice that it should recurse with n - 2 instead of n - 1.

class StrobogrammaticNumberII:

    def doit(self, n):
        
        charMap = {'1':'1', '6':'9', '9':'6', '8':'8', '0':'0'}        

        def make(s):
            if s == 0:
                return ['']
            if s == 1:
                return ['1', '8', '0']

            keys = ['1', '6', '9', '8']
            if s < n:
                keys.append('0')

            res = []
            for child in make(s-2):
                for i in keys:
                    res.append( i + child + charMap[i])
                
            return res

        return make(n)


    def doit(self, n):
        
        ans = ['1', '8', '0'] if n % 2 == 1 else []
        n = n//2
        for i in range(n):
            tmp = []
            for word in ans:            
                tmp.append('1' + word + '1')
                tmp.append('6' + word + '9')
                tmp.append('9' + word + '6')
                tmp.append('8' + word + '8')
                if i != n-1:
                    tmp.append('0' + word + '0')
            ans = tmp
    
        return ans

# 248 Strobogrammatic Number III

# A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

# Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

# For example,
# Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.

# Note:
# Because the range might be a large number, the low and high numbers are represented as string.

# Show Tags
# Show Similar Problems

# [11, 69, 88, 96]

class StrobogrammaticNumberIII:

    
    def doit(self, low, high):
        """
        type : str
        type : str
        rtype : List[str]
        """
        def find(low, high, path):

            if len(low) <= len(path) <= len(high):
                if len(low) == len(path) and path < low or len(high) == len(path) and path > high:
                    return 0
                    
            if len(path) + 2 > len(high):
                return 0

            res = 0
            res += find(low, high, '1' + path + '1')
            res += find(low, high, '8' + path + '8')
            res += find(low, high, '6' + path + '9')
            res += find(low, high, '9' + path + '6')
            
            return res
            
        res = 0
        for i in range(len(low), len(high) + 1):

            res += find(low, high, '', i) # Even length
            
            res += find(low, high, '1', i)

            res += find(low, high, '8', i)

            res += find(low, high, '0', i)


        return res





