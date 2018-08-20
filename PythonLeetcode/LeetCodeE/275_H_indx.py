import os

# 274. H-Index
# Given an array of citations (each citation is a non-negative integer) of a researcher, 
# write a function to compute the researcher's h-index.

# According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her
# N papers have at least h citations each, and the other N ? h papers have no more than h citations each."

# For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.
# Note: If there are several possible values for h, the maximum one is taken as the h-index.


class hIndex:

    def doit(self, citations):
        """
        :type citations: List[int]
        :rtype: int
        """
        if not citations:
            return 0

        length = len(citations)
        D = [0 for _ in range(length + 1)]
        for i in range(length):
            if citations[i] > length:
                D[length] += 1
            else:
                D[citations[i]] += 1

        t = 0
        for i in reversed(range(length + 1)):
            t += D[i]
            if t >= i:
                return i
        
        return 0

# 275. H-Index II
# Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?

class hIndexII:
    def doit(self, citations):
        """
        :type citations: List[int]
        :rtype: int
        """
        length = len(citations)
        start = 0
        count = length

        while count > 0:
            step = count // 2
            mid = start + step 

            if citations[mid] <= length - mid:
                start = mid+1
                count -= (step + 1)
            else:
                count = step

        return length - start


    def doit1(self, citations):
        """
        :type citations: List[int]
        :rtype: int
        """
        s, e = 0, len(citations)-1
        
        while s <= e:
            mid = (s + e) // 2

            if citations[mid] > len(citations) - mid:
                e = mid - 1
            else:
                s = mid + 1

        return len(citations) - s
            
                




if __name__=="__main__":

    #res = hIndex().doit([3, 0, 6, 1, 5])
    
    #res = hIndex().doit([1])

    #res = hIndex().doit([100])

    A = [3, 0, 6, 1, 5]
    A.sort()

    res = hIndexII().doit(A)
    
    res = hIndexII().doit([1])

    res = hIndexII().doit([100])

    pass
        
