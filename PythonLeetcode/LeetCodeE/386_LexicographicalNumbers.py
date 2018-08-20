

# 386. Lexicographical Numbers

# Given an integer n, return 1 - n in lexicographical order.

# For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

# Please optimize your algorithm to use less time and space. The input size may be as large as 5,000,000.

class lexicalOrder:
    def doit(self, n):
        """
        :type n: int
        :rtype: List[int]
        """

        def search(base, maxV):
            if base >= maxV:
                return [base] if base == maxV else []

            res = []
            for i in range(10):
                if base + i <= maxV:
                    res += [base+i] + search( (base+i) * 10, maxV)

            return res                                       

        res = []
        for i in range(1, 10):
            if i <= n:    
                res += [i] + search(i * 10, n)

        return res


    def doit1(self, n):
        """
        :type n: int
        :rtype: List[int]
        """ 
        x = 1
        res = []
        for _ in range(n):
        
            res.append(x)

            if x * 10 <= n:
                x *= 10

            else:

                if x >= n:
                    x //= 10

                x += 1

                while x % 10 == 0:
                    x //= 10

        return res


    def doit2(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        return sorted([i for i in range(1, n + 1)], key=str)


    def doit3(self, n):

        def addNumber(self, n, start, result):
            if start > 0:
                if start <= n:
                    result.append(start)
                else:
                    return result
                result = self.addNumber(n, start*10, result)
            for nextNumbers in range(start+1, min([start+10,n+1])):
                if nextNumbers <= n:
                    result.append(nextNumbers)
                    result = self.addNumber(n, nextNumbers*10, result)
                else:
                    break
            return result

        result = []
        return addNumber(n, 0, result)
    

        



if __name__=="__main__":

    
    res = lexicalOrder().doit(13)

    res = lexicalOrder().doit(100)

    res = lexicalOrder().doit(199)

    pass