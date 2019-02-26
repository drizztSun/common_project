
# 976. Largest Perimeter Triangle

#Given an array A of positive lengths, return the largest perimeter of a triangle with non-zero area, formed from 3 of these lengths.

#If it is impossible to form any triangle of non-zero area, return 0.

 

#Example 1:

#Input: [2,1,2]
#Output: 5
#Example 2:

#Input: [1,2,1]
#Output: 0
#Example 3:

#Input: [3,2,3,4]
#Output: 10
#Example 4:

#Input: [3,6,2,3]
#Output: 8
 

#Note:

#3 <= A.length <= 10000
#1 <= A[i] <= 10^6


class LargestPerimeter:


    def doit(self, A: 'List[int]') -> 'int':

        A.sorted(reverse=True)
        
        for i in range(len(A)-2):
            if A[i] < A[i+1] + A[i+2]:
                return A[i] + A[i+1] + A[i+2]
        
        return 0

    def doit2(self, A: 'List[int]') -> int:
        # if len(A)<3:
        #     return 0
        # A.sort(reverse = True)
        # for i in range(len(A)-2):
        #     a = A[i]
        #     b = A[i+1]
        #     c = A[i+2]
        #     if b+c>a:
        #         return a+b+c
        # return 0
        a = max(A)
        A.remove(a)
        b = max(A)
        A.remove(b)
        c = max(A)
        A.remove(c)
        while b+c<=a and A:
            a,b,c = b,c,max(A)
            A.remove(c)
        if b+c>a:
            return a+b+c
        return 0

    def doit3(self, A: 'List[int]') -> 'int':
        import heapq
        BB = [-a for a in A]
        heapq.heapify(BB)
        one = -heapq.heappop(BB)
        two = -heapq.heappop(BB)
        three = -heapq.heappop(BB)
        while BB and (two + three <= one):
            one, two = two, three
            three = -heapq.heappop(BB)
        return (one + two + three) if (two + three > one) else 0

    def doit1(self, A: 'List[int]') -> int:
        
        istriagle = lambda a, b, c: a + b > c and b + c > a and c + a > b
        ans = 0
        
        for i in range(len(A) - 2):
            for j in range(i+1, len(A)-1):
                for z in range(j+1, len(A)):
                    
                    if istriagle(A[i], A[j], A[z]):
                        ans = max(ans, A[i] + A[j] + A[z])
                        
        return ans
        

if __name__ == "__main__":

    res = LargestPerimeter().doit([1, 2, 1])