# 728. Self Dividing Numbers

# A self-dividing number is a number that is divisible by every digit it contains.

# For example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and 128 % 8 == 0.

# Also, a self-dividing number is not allowed to contain the digit zero.

# Given a lower and upper number bound, output a list of every possible self dividing number, including the bounds if possible.

# Example 1:
# Input: 
# left = 1, right = 22
# Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]


COMPUTED = []

def IsSelfDividingNumber(n):
    m = n
    while m > 0:
        m, k = divmod(m, 10)
        if k == 0:
            return False
        if n % k != 0:
            return False
    return True

def Init():
    for k in range(1, 10001):
        if IsSelfDividingNumber(k):
            COMPUTED.append(k)

# 2 6 10 12,    (5, 10) -> 6, 10  (5, 11) -> 6, 10
def upper_bound(n):
    lo, hi = 0, len(COMPUTED) - 1
    while lo < hi:
        mid = (hi-lo)//2 + lo
        if n > COMPUTED[mid]:
            lo = mid + 1
        else:
            hi = mid
    return lo

def lower_bound(n):
    lo, hi = 0, len(COMPUTED) - 1
    while lo < hi:
        mid = (hi-lo+1)//2 + lo
        if n < COMPUTED[mid]:
            hi = mid - 1
        else:
            lo = mid
    return hi
    
class Solution:
    
    def __init__(self):
        if not COMPUTED:
            Init()
    
    def selfDividingNumbers(self, left, right):
        """
        :type left: int
        :type right: int
        :rtype: List[int]
        """
        lo = upper_bound(left)
        hi = lower_bound(right)

        if (hi < lo):
            return []

        return COMPUTED[lo:hi+1]


class SelfDividingNumbers:
    def doit(self, left: 'int', right: 'int') -> 'List[int]':
        
        nums = []
        for i in range(left, right + 1):
            
            for c in str(i):
                if int(c) == 0 or i % int(c) != 0:
                    break
            else:
                nums.append(i)
                
        return nums

    def doit(self, left: 'int', right: 'int') -> 'List[int]':
        """
        :type left: int
        :type right: int
        :rtype: List[int]
        """
        l = []
        for i in range(left,right+1):
            if i<10:
                l.append(i)
            else:
                temp = i
                flag = True

                while(i>0):
                    r = i%10
                    if r==0 or temp%r != 0:
                        flag = False
                        break
                    i = i//10

                if flag == True:
                    l.append(temp)
        return l
                    

if __name__ == "__main__":

    res = SelfDividingNumbers().doit(1, 22)
