# 43. Multiply Strings

# Given two non-negative integers num1 and num2 represented as strings, 
# return the product of num1 and num2, also represented as a string.

# Example 1:

# Input: num1 = "2", num2 = "3"
# Output: "6"
# Example 2:

# Input: num1 = "123", num2 = "456"
# Output: "56088"
# Note:

# The length of both num1 and num2 is < 110.
# Both num1 and num2 contain only digits 0-9.
# Both num1 and num2 do not contain any leading zero, except the number 0 itself.
# You must not use any built-in BigInteger library or convert the inputs to integer directly.

from functools import reduce

class Multiply2Nums:


    def doit(self, num1, num2):
    
        if not num1 or not num2 or num1 == '0' or num2 == '0':
            return '0'      

        res = [0] * (len(num1) + len(num2))
        
        for i, c in enumerate(reversed(num1)):

            for j, f in enumerate(reversed(num2)):

                res[i + j] += int(c) * int(f)
        
        for i in range(len(num1) + len(num2) - 1):
            accum, res[i] = divmod(res[i], 10)
            res[i+1] += accum
        
        if res[-1] == 0:
            res.pop()

        return ''.join([str(i) for i in reversed(res)])


    def doit1(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        carryover = 0
        tempresult = 0
        array1 = [x for x in num1][::-1]
        array2 = [y for y in num2][::-1]

        resultrowlst = [(0, 0) for m in range(len(array2) + len(array1))]
        addresult = 0
        i = 0

        for idx, el in enumerate(array1):
            i = idx

            for idx2, el2 in enumerate(array2):

                if idx2 != (len(array2) - 1):
                    tempresult = ((int(el) * int(el2)) % 10 + carryover)
                    carryover = (int(el) * int(el2)) // 10
                else:
                    tempresult = ((int(el) * int(el2)) + carryover)
                    carryover = 0

                resultrowlst[i] = (i, tempresult)
                i += 1

            for valuetuple in resultrowlst:
                addresult += valuetuple[1] * (10 ** valuetuple[0])

            resultrowlst = [(0, 0) for m in range(len(array2) + len(array1))]

        return str(addresult)                        


    def doit3(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        product = [0] * (len(num1) + len(num2))
        pos = len(product) - 1

        for n1 in reversed(num1):
            tempos = pos
            for n2 in reversed(num2):
                product[tempos] += int(n1) * int(n2)
                product[tempos - 1] += product[tempos] / 10
                product[tempos] = product[tempos] % 10
                tempos -= 1
            pos -= 1
    
        pt = 0
        while pt < len(product) - 1 and product[pt] == 0:
            pt += 1

        return ''.join(map(str, product[pt:]))

    def doit4(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        res = []
        for j in reversed(range(len(num2))):
            
            product, accum = '', 0
            for i in reversed(range(len(num1))):
                p = int(num1[i]) * int(num2[j]) + accum
                accum = 0
                if p > 9:
                    accum = p // 10
                    p %= 10

                product = str(p) + product

            if accum:
                product = str(accum) + product

            res.append(product + '0' * (len(num2) - j - 1))
    
        def adds(a, b):
            if len(a) > len(b):
                return add(b, a)

            A, B = list(a), list(b)

            abc, accum = [], 0
            while B:
                if A:
                    p = int(A[-1]) + int(B[-1]) + accum
                else:
                    p = int(B[-1]) + accum

                accum = 0
                if p > 9:
                    accum = 1
                    p -= 10
                abc.append(str(p))
                
                A and A.pop()
                B and B.pop()

            if accum:
                abc.append("1")

            return ''.join(abc[::-1])

        ans = reduce(adds, res)
        
        return 


if __name__ == "__main__":

    # 6
    res = Multiply2Nums().doit("2", "3");
    
    # "56088"
    res = Multiply2Nums().doit("123", "456")
    





