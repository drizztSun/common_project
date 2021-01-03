"""
1570. Dot Product of Two Sparse Vectors

Given two sparse vectors, compute their dot product.

Implement class SparseVector:

SparseVector(nums) Initializes the object with the vector nums
dotProduct(vec) Compute the dot product between the instance of SparseVector and vec
A sparse vector is a vector that has mostly zero values, you should store the sparse vector efficiently and compute the dot product between two SparseVector.

Follow up: What if only one of the vectors is sparse?

 

Example 1:

Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
Output: 8
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 1*0 + 0*3 + 0*0 + 2*4 + 3*0 = 8
Example 2:

Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
Output: 0
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 0*0 + 1*0 + 0*0 + 0*0 + 0*2 = 0
Example 3:

Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
Output: 6
 

Constraints:

n == nums1.length == nums2.length
1 <= n <= 10^5
0 <= nums1[i], nums2[i] <= 100



"""


class SparseVector:
    def __init__(self, nums: List[int]):
        self._vec = {i: x for i, x in enumerate(nums) if nums[i] != 0}
        
    # Return the dotProduct of two sparse vectors
    def dotProduct(self, vec: 'SparseVector') -> int:
        res = 0
        for k in self._vec.keys() & vec._vec.keys():
            res += self._vec[k] * vec._vec[k]
        return res
        

"""
Approach 2: Hash Set
Intuition

Store the non-zero values and their corresponding indices in a dictionary, with the index being the key. Any index that is not present corresponds to a value 0 in the input array.

Algorithm

Complexity Analysis

Let nn be the length of the input array and LL be the number of non-zero elements.

Time complexity: O(n)O(n) for creating the Hash Map; O(L)O(L) for calculating the dot product.

Space complexity: O(L)O(L) for creating the Hash Map, as we only store elements that are non-zero. O(1)O(1) for calculating the dot product.
"""
class SparseVector:
    def __init__(self, nums: List[int]):
        self.nonzeros = {}
        for i, n in enumerate(nums):
            if n != 0:
                self.nonzeros[i] = n              

    def dotProduct(self, vec: 'SparseVector') -> int:
        result = 0
        # iterate through each non-zero element in this sparse vector
        # update the dot product if the corresponding index has a non-zero value in the other vector
        for i, n in self.nonzeros.items():
            if i in vec.nonzeros:
                result += n * vec.nonzeros[i]
        return result


"""
Approach 3: Index-Value Pairs
Intuition

We can also represent elements of a sparse vector as a list of <index, value> pairs. We use two pointers to iterate through the two vectors to calculate the dot product.

Algorithm

Complexity Analysis

Let nn be the length of the input array and LL and L_{2}L 
2
​	
  be the number of non-zero elements for the two vectors.

Time complexity: O(n)O(n) for creating the <index, value> pair for non-zero values; O(L+L_{2})O(L+L 
2
​	
 ) for calculating the dot product.

Space complexity: O(L)O(L) for creating the <index, value> pairs for non-zero values. O(1)O(1) for calculating the dot product.
"""
class SparseVector:
    def __init__(self, nums: List[int]):
        self.pairs = []
        for index, value in enumerate(nums):
            if value != 0:
                self.pairs.append([index, value])

    def dotProduct(self, vec: 'SparseVector') -> int:
        result = 0
        p, q = 0, 0

        while p < len(self.pairs) and q < len(vec.pairs):
            if self.pairs[p][0] == vec.pairs[q][0]:
                result += self.pairs[p][1] * vec.pairs[q][1]
                p += 1
                q += 1
            elif self.pairs[p][0] < vec.pairs[q][0]:
                p += 1
            else:
                q += 1

        return result
