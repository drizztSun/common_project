# 504. Base 7

# Given an integer, return its base 7 string representation.

# Example 1:
# Input: 100
# Output: "202"
# Example 2:
# Input: -7
# Output: "-10"
# Note: The input will be in range of [-1e7, 1e7].

class ConvertToBase7(object):
    def doit(self, num):
        """
        :type num: int
        :rtype: str
        """
        if not num:
            return '0'
        
        res, neg = '', False
        if num < 0:
            neg = True
            num = - num
            
        while num:
            base = num % 7
            res = str(base) + res
            num //= 7
            
        
        return '-' + res if neg else res


    def doit1(self, num):
        """
        :type num: int
        :rtype: str
        """
        
        if num == 0:
            return '0'
        
        isNegative = num < 0
        
        num = abs(num)
        
        ans = ''
        while num != 0:
            rem = num % 7
            ans = str(rem) + ans
            num = num / 7
        
        if isNegative:
            return '-' + ans
        else:
            return ans


if __name__ == "__main__":

    res = ConvertToBase7().doit("100") # 202

    res = ConvertToBase7().doit("-7") # -10
             
        