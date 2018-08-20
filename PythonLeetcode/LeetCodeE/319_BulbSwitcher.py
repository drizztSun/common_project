


# 319. Bulb Switcher

# There are n bulbs that are initially off. You first turn on all the bulbs. Then, you turn off every second bulb.
# On the third round, you toggle every third bulb (turning on if it's off or turning off if it's on). 
# For the ith round, you toggle every i bulb. 
# For the nth round, you only toggle the last bulb. Find how many bulbs are on after n rounds.

# Example:

# Given n = 3. 

# At first, the three bulbs are [off, off, off].
# After first round, the three bulbs are [on, on, on].
# After second round, the three bulbs are [on, off, on].
# After third round, the three bulbs are [on, off, off]. 

# So you should return 1, because there is only one bulb is on.


class bulbSwitch:
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1:
            return 1

        bulb = [True] * n

        for step in range(2, n+1):
            for j in range(0, n, step):
                c = j + step - 1
                if c < n:
                    bulb[c] = not bulb[c]

        sum = 0
        for i in bulb:
            if i == True:
                sum += 1
        
        return sum
                    


# A bulb ends up on iff it is switched an odd number of times.
# Call them bulb 1 to bulb n. Bulb i is switched in round d if and only if d divides i. 
# So bulb i ends up on if and only if it has an odd number of divisors.
# Divisors come in pairs, like i=12 has divisors 1 and 12, 2 and 6, and 3 and 4. 
# Except when i is a square, like 36 has divisors 1 and 36, 2 and 18, 3 and 12, 4 and 9, and double divisor 6. 
# So bulb i ends up on if and only if i is a square.
# So just count the square numbers.
# Let R = int(sqrt(n)). That’s the root of the largest square in the range [1,n]. 
# And 1 is the smallest root. So you have the roots from 1 to R, that’s R roots. Which correspond to the R squares. 
# So int(sqrt(n)) is the answer. (C++ does the conversion to int automatically, because of the specified return type).
                     
    def doit1(self, n):
        return math.sqrt(n)

    def doit2(self, n):
        return int(n ** 0.5)

    

            
# 672. Bulb Switcher II

# There is a room with n lights which are turned on initially and 4 buttons on the wall.
# After performing exactly m unknown operations towards buttons, you need to return how many different kinds of status of the n lights could be.

# Suppose n lights are labeled as number [1, 2, 3 ..., n], function of these 4 buttons are given below:

# Flip all the lights.
# Flip lights with even numbers.
# Flip lights with odd numbers.
# Flip lights with (3k + 1) numbers, k = 0, 1, 2, ...

#Example 1:
# Input: n = 1, m = 1.
# Output: 2
# Explanation: Status can be: [on], [off]

#Example 2:
# Input: n = 2, m = 1.
# Output: 3
# Explanation: Status can be: [on, off], [off, on], [off, off]

#Example 3:
# Input: n = 3, m = 1.
# Output: 4
# Explanation: Status can be: [off, on, off], [on, off, on], [off, off, off], [off, on, on]. 
       
class flipLights(object):

    # We only need to consider special cases which n<=2 and m < 3. When n >2 and m >=3, the result is 8.
    # The four buttons:

    # (1) Flip all the lights.
    # (2) Flip lights with even numbers.
    # (3) Flip lights with odd numbers.
    # (4) Flip lights with (3k + 1) numbers, k = 0, 1, 2, ...

    # If we use button 1 and 2, it equals to use button 3.
    # Similarly…
    
    # 2 times
    # 1 + 2 -> 3, 1 + 3-> 2, 1 + 4, 2 + 4, 3 + 4, 2 + 3 -> 1
    
    # 3 times
    # 1 + 2 + 3 -> all_on
    
    # all_on, 1, 2, 3, 4, 1 + 4, 2 + 4, 3 + 4, 

    #1 + 2 --> 3, 1 + 3 --> 2, 2 + 3 --> 1
    #So, there are only 8 cases.

    #All_on, 1, 2, 3, 4, 1+4, 2+4, 3+4

    #And we can get all the cases, when n>2 and m>=3.
    def doit(self, n, m):
        """
        :type n: int
        :type m: int
        :rtype: int
        """
        if m == 0:
            return 1
        
        if n == 1:
            return 2
        
        if n == 2 and m == 1:
            return 3

        if n == 2:
            return 4

        if m == 1:
            return 4

        if m == 2:
            return 7

        if m >= 3:
            return 8

        return 8


if __name__=="__main__":

    res = bulbSwitch().doit(3)

    res = bulbSwitch().doit(5)

    res = bulbSwitch().doit(8)



    res = flipLights().doit(3, 2)
    
    pass