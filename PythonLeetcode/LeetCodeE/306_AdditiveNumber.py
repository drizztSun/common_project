


# 306. Additive Number

# Additive number is a string whose digits can form additive sequence.

# A valid additive sequence should contain at least three numbers. 
# Except for the first two numbers, each subsequent number in the sequence 
# must be the sum of the preceding two.

# For example:
# "112358" is an additive number because the digits can form an additive sequence: 1, 1, 2, 3, 5, 8.

# 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
# "199100199" is also an additive number, the additive sequence is: 1, 99, 100, 199.
# 1 + 99 = 100, 99 + 100 = 199
# Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.

# Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.


class isAdditiveNumber:
    def doit(self, num):
        """
        :type num: str
        :rtype: bool
        """

        def cal(nums, i, buff):
            
            if len(buff) >= 3 and buff[-3] + buff[-2] != buff[-1]:
                return False
    
            if i >= len(nums):
                return len(buff) >= 3

            res = False
            if nums[i] == '0':
                buff.append(0)
                res = cal(nums, i+1, buff)
                buff.pop()
            else:
                for j in range(i+1, len(nums)+1):

                    buff.append(int(nums[i:j]))
            
                    if cal(nums, j, buff):
                        return True

                    buff.pop()

            return res
            
        res = []
        return cal(num, 0, res)


    def doit1(self, num):
        """
        :type num: str
        :rtype: bool
        """
        def is_addictive(n1, n2, idx, lst):
            if idx >= len(lst):
                return True

            sum = n1 + n2
            n3 = 0

            for i in range(idx, len(lst)):
                n3 = n3 * 10 + lst[i]

                if n3 == sum:
                    if is_addictive(n2, n3, i + 1, lst):
                        return True

                elif n3 > sum:
                    break
                if n3 == 0 and i == idx:
                    break

            return False
        
        #####################
        if len(num) < 3:
            return False

        n = 0
        lst = [int(c) for c in num]

        for i, c in enumerate(lst):
            n = n * 10 + c
            n2 = 0

            for j in range(i + 1, len(lst)):
                n2 = n2 * 10 + lst[j]
                sum = n + n2
                n3 = 0

                for k in range(j + 1, len(lst)):

                    n3 = n3 * 10 + lst[k]
                    if n3 == sum:
                        if is_addictive(n2, n3, k + 1, lst):
                            return True
                    elif n3 > sum:
                        break

                    if n3 == 0 and k == j + 1:
                        break

                if n2 == 0 and j == i + 1:
                    break

            if n == 0 and i == 0:
                break

        return False
    
        



if __name__=="__main__":

    res = isAdditiveNumber().doit('1')

    res = isAdditiveNumber().doit('101')

    res = isAdditiveNumber().doit("112358")

    res = isAdditiveNumber().doit("199100199")

    res = isAdditiveNumber().doit("12012122436")

    pass
        