
import heapq

# 347. Top K Frequent Elements

# Given a non-empty array of integers, return the k most frequent elements.

# For example,
# Given [1,1,1,2,2,3] and k = 2, return [1,2].

# Note: 
# You may assume k is always valid, 1 ? k ? number of unique elements.
# Your algorithm's time complexity must be better than O(n log n), where n is the array's size.



class topKFrequent(object):
    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        
        counter = {}
        for c in nums:
            counter[c] = counter.get(c, 0) + 1

        D = [list() for _ in range(len(nums) + 1)]

        for c in counter:
            D[counter[c]].append(c)

        res = []
        length = len(D)
        i = len(D)-1
        while k > 0 and i > 0:

            if k >= len(D[i]):
                res.extend(D[i])
                k -= len(D[i])
            else:
                res.extend(D[i][:k])
                break

            i -= 1                  

        return res

            
    def doit1(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        dic = {}
        res = []
        for i in nums:
            if i not in dic:
                dic[i] = 1
            else:
                dic[i] += 1
        
        for item in sorted(dic.items(), key = lambda x: x[1], reverse = True):
            res.append(item[0])

        return res[:k]


    # <heapmax>

    def doit2(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        counter = {}
        for c in nums:
            counter[c] = counter.get(c, 0) + 1

        D = counter.items()

        result = heapq.nlargest(k, D, key= lambda x : x[1])
        return [x[0] for x in result]                

    


if __name__=="__main__":

    res = topKFrequent().doit2([1,1,1,2,2,3], 2)
    

    pass
        