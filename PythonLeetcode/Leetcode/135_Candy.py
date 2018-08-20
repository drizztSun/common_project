

import os


# There are N children standing in a line. Each child is assigned a rating value.
# You are giving candies to these children subjected to the following requirements:
#    Each child must have at least one candy.
#    Children with a higher rating get more candies than their neighbors.
# What is the minimum candies you must give?


class candy(object):

    def doit(self, ratings):
        """
        :type ratings: List[int]
        :rtype: int
        """
        D = [0] * (len(ratings))

        extra, i = 1, 1
        while i < len(ratings):
            if ratings[i] > ratings[i-1]:
                D[i] += extra
                extra += 1
            else:
                extra = 1  
            i += 1

        extra, i = 1, len(ratings) - 1
        while i > 0:
            if ratings[i-1] > ratings[i]:
                if i-2 < 0 or ratings[i-2] >= ratings[i-1]:
                    D[i-1] += extra
                    extra += 1
            else:
                extra = 1
            i -= 1

        i = 1
        while i < len(ratings)-1:
            if ratings[i] > max(ratings[i-1], ratings[i+1]) and D[i] <= max(D[i+1], D[i-1]):
                D[i] = max(D[i+1], D[i-1]) + 1
            i += 1

        return len(ratings) + sum(D)

    def doit2(self, ratings):
        """
        :type ratings: List[int]
        :rtype: int
        """       
        if len(ratings) <= 1:
            return len(ratings)

        num = [1 for x in range(len(ratings))]
        for i in range(1, len(ratings)):
            if ratings[i] > ratings[i-1]:
                num[i] = num[i-1] + 1
        
        for i in reversed(range(1, len(ratings))):
            if ratings[i] < ratings[i-1]:
                num[i-1] = max(num[i-1], num[i] + 1)

        return sum(num)
        

    def doit1(self, ratings):
        """
        :type ratings: List[int]
        :rtype: int
        """
        lr = len(ratings)        
        downwards = False
        peak = 0
        prevn = 1
        total = 1
        
        for i in xrange(1, lr):
            if ratings[i] >= ratings[i-1]:
                if downwards:
                    diff = 1 - prevn
                    total += diff * (i - peak - (1 if diff <= 0 else 0))
                    downwards = False
                    prevn = 1
                    
                peak = i
                if ratings[i] > ratings[i-1]:
                    prevn += 1
                else:
                    prevn = 1
                total += prevn
                    
            else:
                downwards = True
                prevn -= 1
                total += prevn
                
        if downwards:
            diff = 1 - prevn
            total += diff * (lr - peak - (1 if diff <= 0 else 0))
        
        return total
                

if __name__=="__main__":


    ratings = [1,3,4,3,2,1] # 13
    res = candy().doit(ratings)    

    ratings = [2,3,2] # 4
    res = candy().doit(ratings)

    ratings = [2,2,1] # 4
    res = candy().doit(ratings)

    ratings = [4,2,3,4,1]
    res = candy().doit(ratings)

    ratings = [1, 0, 2]
    res = candy().doit(ratings)


    ratings = [1, 3, 2, 5, 4, 8, 7, 9, 10]
    res = candy().doit(ratings)

    pass
