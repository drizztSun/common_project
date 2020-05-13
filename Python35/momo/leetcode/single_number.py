from collections import defaultdict
# my solution

class SingleNumberslootion:

    def singleNumber(a) -> int:
        l = {a[j]: 0 for j in range(len(a))}
        for i in range(len(a)):
            l[a[i]] = l[a[i]] + 1
            if l[a[i]] > 1:
                del l[a[i]]
        m = l.keys()
        return list(m)[0]
    '''
    Approach 1: List operation
    Algorithm

    Iterate over all the elements in nums
    If some number in nums is new to array, append it
    If some number is already in the array, remove it
    '''
    def singleNumber1(self, a):
        """
        :type nums: List[int]
        :rtype: int
        """
        a = []
        for i in a:
            if i not in a:
                a.append(i)
            else:
                a.append(i)
        return a.pop()
    '''
    Approach 2: Hash Table
    Algorithm

    We use hash table to avoid the O(n)time required for searching the elements.

    Iterate through all elements in nums and set up key/value pair.
    Return the element which appeared only once.
    '''


    def singleNumber2(self, a) -> int:
        k = defaultdict(int)
        for i in a:
            k[i] += 1
        
        for i in k:
            if k[i] == 1:
                return i
                    
    '''
    Approach 3: Math
    Concept

    2 * (a + b + c) - (a + a + b + b + c) = c2∗(a+b+c)−(a+a+b+b+c)=c
    '''

    def singleNumber3(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        return 2 * sum(set(nums)) - sum(nums)
    '''
    Approach 4: Bit Manipulation
    Concept

    If we take XOR of zero and some bit, it will return that bit
    a \oplus 0 = aa⊕0=a
    If we take XOR of two same bits, it will return 0
    a ⊕ = 0
    a⊕a=0
    a ⊕ b ⊕ a = (a ⊕ a) ⊕ b = 0 ⊕ b = b
    a⊕b⊕a=(a⊕a)⊕b=0⊕b=b
    So we can XOR all bits together to find the unique number.
    '''




    def singleNumber4(self, a):
        """
        :type nums: List[int]
        :rtype: int
        """
        a = 0
        for i in a:
            a ^= i
        return a



if __name__ == '__main__':


   pass