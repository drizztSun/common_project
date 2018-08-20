import os



# A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

# For example, these are arithmetic sequence:
# 1, 3, 5, 7, 9
# 7, 7, 7, 7
# 3, -1, -5, -9

# The following sequence is not arithmetic.
# 1, 1, 2, 5, 7

# A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.

# A slice (P, Q) of array A is called arithmetic if the sequence:
# A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.

# The function should return the number of arithmetic slices in the array A.

class numberOfArithmeticSlices:


    def doit(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        if len(A) < 3:
            return 0

        current, sum = 0, 0
        for i in range(2, len(A)):
            if A[i] - A[i-1] == A[i-1] - A[i-2]:
                current += 1
            else:
                sum += current * (current + 1) // 2
                current = 0

        return sum + current * (current + 1) // 2
        

    # Brute force
    def doit_BruteForce(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        count = 0
        for i in range(len(A) - 2):
            d = A[i+1] - A[i]
            

    def doit_recur(self, A):
    # def doit(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        def slices_sum(A, i):
            if i < 2:
                return 0

            sum = 0
            if A[i] - A[i-1] == A[i-1] - A[i-2]:
                ap = 1 + slices_sum(A, i - 1)
                sum += ap
            else:
                sum = slices_sum(A, i - 1)

            return sum
        
        return slices_sum(A, len(A)-1)
    

    # This one can get all sub string
    def doit1(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        if len(A) < 3:
            return 0

        diff = [(A[i] - A[i-1]) for i in range(1, len(A))]
        
        last, number, current = diff[0], 0, 0
        sublist = []

        for i in range(1, len(diff)):
            if last != diff[i]:
                if i - current >= 2:            
                    sublist.append((current, i))
                current = i
            last = diff[i]
            if i == len(diff) - 1 and i != current:
                sublist.append((current, i+1))

        res = []
        for c in sublist:
            s, e = c[0], c[1]
            length = e - s + 1
            for step in range(2, length):
                i = 0
                while s + step + i <= e:
                    res.append(A[s + i : s + i + step + 1])
                    i += 1

        return len(res)


    def doit1(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        if len(A) < 3:
            return 0

        diff = [(A[i] - A[i-1]) for i in range(1, len(A))]
        
        last, number, current = diff[0], 0, 0
        sublist = []

        for i in range(1, len(diff)):
            if last != diff[i]:
                if i - current >= 2:            
                    sublist.append(i-current)
                current = i
            last = diff[i]
            if i == len(diff) - 1 and i != current:
                sublist.append(i - current + 1)

        res = 0
        for c in sublist:
            res += (c * (c-1)) // 2

        return res


    def doit2(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        if len(A) < 3: 
            return 0

        prev = A[1]
        prev_diff = prev - A[0]
        count = 0
        num_slices = 0

        for i in A[2:]:
            #print('cur: {}, prev: {}, prev_diff: {}, count: {}, num_slices: {}'.format(i, prev, prev_diff, count, num_slices))
            cur_diff = i - prev
            if cur_diff == prev_diff:
                count += 1
            else:
                prev_diff = cur_diff
                if count > 0:
                    num_slices += ((count*(count+1))//2)
                count = 0
            prev = i

        if count > 0: 
            num_slices += ((count*(count+1))//2)

        return num_slices
        

if __name__=="__main__":



    A = [1, 2, 3, 4]
    res = numberOfArithmeticSlices().doit(A)

    A = [1,2,3,8,9,10]
    res = numberOfArithmeticSlices().doit(A)


    pass
        