


# 349. Intersection of Two Arrays

# Given two arrays, write a function to compute their intersection.
# Example:
# Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

class intersection:
    def doit(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        A = set()
        for c in nums1:
           A.add(c)

        B, C = [], set()
        for c in nums2:
            if c in A:
                C.add(c)

        for c in C:
            B.append(c)
        return B

    def doit1(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        nums1 = set(nums1)
        nums2 = set(nums2)
        return list(nums1 & nums2)


# 350. Intersection of Two Arrays II
        
# Given two arrays, write a function to compute their intersection.

# Example:
# Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

# Note:
# Each element in the result should appear as many times as it shows in both arrays.
# The result can be in any order.

class intersectII:
    def doit(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        C = dict()
        for c in nums1:
            if c not in C:
                C[c] = 1
            else:
                C[c] += 1

        B = []
        for c in nums2:
            if c in C and C[c] > 0:
                B.append(c)
                C[c] -= 1

        return B
        

    def doit1(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        dict1={}
        for i in range(len(nums1)):
            if nums1[i] in dict1:
                dict1[nums1[i]]+=1
            else:
                dict1[nums1[i]]=1
        
        res=[]
        for i in range(len(nums2)):
            if nums2[i] in dict1 and dict1[nums2[i]]>0:
                res.append(nums2[i])
                dict1[nums2[i]]-=1
        
        return res        



if __name__=="__main__":


    res = intersection().doit([1, 2, 2, 1], [2, 2])

    res = intersectII().doit([1, 2, 2, 1], [2, 2])

    res = intersectII().doit([1], [1])

    pass