# 605. Can Place Flowers

# Suppose you have a long flowerbed in which some of the plots are planted and some are not. However, 
# flowers cannot be planted in adjacent plots - they would compete for water and both would die.

# Given a flowerbed (represented as an array containing 0 and 1, where 0 means empty and 1 means not empty), 
# and a number n, return if n new flowers can be planted in it without violating the no-adjacent-flowers rule.

# Example 1:
# Input: flowerbed = [1,0,0,0,1], n = 1
# Output: True

# Example 2:
# Input: flowerbed = [1,0,0,0,1], n = 2
# Output: False
# Note:
# The input array won't violate no-adjacent-flowers rule.
# The input array size is in the range of [1, 20000].
# n is a non-negative integer which won't exceed the input array size.


class CanPlaceFlowers:

    def doit(self, flowerbed, n):
        """
        :type flowerbed: List[int]
        :type n: int
        :rtype: bool
        """
        i, count = 0, 0
        N = len(flowerbed)

        while i < N:

            while i < N and flowerbed[i] == 1:
                i += 1

            if i == N:
                return n <= count

            start = i
            while i < N and flowerbed[i] == 0:
                i += 1
            end = i

            if start != 0:
                if i < N:
                    if i - start > 2:
                        count += (end - start - 1) // 2
                else:
                    count += (N - start) // 2
            else:
                if i < N:
                    count += end // 2
                else:
                    count += (N + 1) // 2

        return n <= count                


    def doit1(self, flowerbed, n):
        """
        :type flowerbed: List[int]
        :type n: int
        :rtype: bool
        """
        if n ==0:
            return True
        
        count = 1
        result =0
        for i in flowerbed:
            if i ==0:
                count +=1                
            else:
                result += (count-1) // 2
                count =0

        if count !=0:
            result += count//2
        
        return n <= result
        

if __name__ == "__main__":

    res = CanPlaceFlowers().doit(flowerbed = [0, 1, 0], n = 1)

    res = CanPlaceFlowers().doit(flowerbed = [1,0,0,0,1], n = 1)

    res = CanPlaceFlowers().doit(flowerbed = [1,0,0,0,1], n = 2)

    res = True 
