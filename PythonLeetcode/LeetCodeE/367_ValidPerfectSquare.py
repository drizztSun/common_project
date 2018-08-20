


# 367. Valid Perfect Square

# Given a positive integer num, write a function which returns True if num is a perfect square else False.

# Note: Do not use any built-in library function such as sqrt.

# Example 1:

# Input: 16
# Returns: True
# Example 2:

# Input: 14
# Returns: False



class isPerfectSquare:
    def doit(self, num):
        """
        :type num: int
        :rtype: bool
        """
        s, e = 0, num

        while s <= e:

            mid = (s + e) // 2
            res = mid ** 2
            
            if res == num:
                return True

            elif res < num:
                s = mid + 1 

            else:
                e = mid - 1

        return False
    





if __name__ == "__main__":


    res = isPerfectSquare().doit(14)

    res = isPerfectSquare().doit(16)

    pass
        

