

# 357. Count Numbers with Unique Digits

# Given a non-negative integer n, count all numbers with unique digits, x, where 0 ? x < 10**n.

# Example:
# Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ? x < 100, 
# excluding [11,22,33,44,55,66,77,88,99])


class countNumbersWithUniqueDigits:
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        choice = [9, 9, 8, 7, 6, 5, 4, 3, 2, 1]
        ans = 1
        produce = 1
        for i in range(n if n <= 10 else 10):
            produce *= choice[i]
            ans += produce

        return ans



if __name__=="__main__":

    res = []

    for i in range(10):
        res.append(countNumbersWithUniqueDigits().doit())

    print(res)
    
    pass

