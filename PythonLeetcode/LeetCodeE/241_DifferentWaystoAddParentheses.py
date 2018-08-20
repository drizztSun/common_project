import os



# leetcode 241. Different Ways to Add Parentheses


# Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators.
# The valid operators are +, - and *.


# Example 1
# Input: "2-1-1".

# ((2-1)-1) = 0
# (2-(1-1)) = 2
# Output: [0, 2]


# Example 2
# Input: "2*3-4*5"

# (2*(3-(4*5))) = -34
# ((2*3)-(4*5)) = -14
# ((2*(3-4))*5) = -10
# (2*((3-4)*5)) = -10
# (((2*3)-4)*5) = 10
# Output: [-34, -14, -10, -10, 10]


class diffWaysToCompute:


    def doit1(self, input):
        """
        :type input: str
        :rtype: List[int]
        """ 
        def compute(nums):
            res = []
            for i in range(len(nums)):
                if nums[i] in ('*', '+', '-'):
                    res1 = compute(nums[:i])
                    res2 = compute(nums[i+1:])
                    c = 0
                    for n1 in res1:
                        for n2 in res2:
                            c = {
                                '+' : n1 + n2,
                                '-' : n1 - n2,
                                '*' : n1 * n2
                            }.get(nums[i], 0)
                            res.append(c)

            if not res:
                res.append(int(nums))

            return res

        return compute(input)


    def doit2(self, input):
        """
        :type input: str
        :rtype: List[int]
        """
        def op(op, x, y):
            if op == '+':
                return x+y
            elif op == '-':
                return x-y
            elif op == '*':
                return x*y
            
        def dp(tokens, a, b, h):
            if a == b:
                h[(a,b)] = [tokens[a]]

            if (a,b) in h:
                return h[(a,b)]
        
            ways = []
            for root in range(a+1, b, 2):
                left = dp(tokens, a, root-1, h)
                right = dp(tokens, root+1, b, h)
                for val1 in left:
                    ways.extend([op(tokens[root], val1, val2) for val2 in right])

            h[(a,b)] = ways
          
            return ways


        # 
        if len(input) == 0:
            return []
        
        h = {}
        i = prev = 0
        tokens = []
        for i in range(len(input)):
            if input[i] in ['+','-','*']:
                tokens.extend([int(input[prev:i]), input[i]])
                prev = i+1
        tokens.append(int(input[prev:]))

        return dp(tokens, 0, len(tokens)-1, h)

    def doit(self, input);
        """
        :type input: str
        :rtype: List[int]
        """
        def ops(os, n1, n2):
            return {
                '+': n1 + n2,
                '-': n1 - n2,
                '*': n1 * n2
            }.get(os, 0)
        
        def dp(nums):
            
            res = []
            for i, val in enumerate(nums):
                if nums[i] in ('*', '+', '-'):
                    res1 = dp(nums[:i])
                    res2 = dp(nums[i+1:])
                    
                    for n1 in res1:
                        res.extend([ops(nums[i], n1, n2) for n2 in res2])
                        
            if not res:
                res.append(int(nums))
            return res
        
        return dp(input)

    # duplicate result issue
    def doit4(self, input):
        """
        :type input: str
        :rtype: List[int]
        """
        def operator(ops, x, y):
            return {
                '*': x * y,
                '-': x - y,
                '+': x + y
            }.get(ops, 0)

        
        def calculate(nums, res):
            if len(nums) == 1:
                res.append(nums[0])

            i = 0
            while i < len (nums):
                if nums[i] in ('+', '-', '*'):
                    tmp = operator(nums[i], nums[i-1], nums[i+1])
                    calculate(nums[:i-1] + [tmp] + nums[i+2:], res)
                    i += 1
                i += 1

            return

        res, prev, inputElement = [], 0, []
        for i in range(len(input)):
            if input[i] in ('*', '+', '-'):
                inputElement.extend([int(input[prev:i]), input[i]])
                prev = i + 1
        inputElement.append(int(input[prev:]))
        calculate(inputElement, res)
        return res

if __name__ == "__main__":

    res = diffWaysToCompute().doit("2-1-1")

    res = diffWaysToCompute().doit("2*3-4*5")

    pass