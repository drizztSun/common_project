# 793. Preimage Size of Factorial Zeroes Function

# Let f(x) be the number of zeroes at the end of x!. (Recall that x! = 1 * 2 * 3 * ... * x, and by convention, 0! = 1.)

# For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) = 2 because 11! = 39916800 has 2 zeroes at the end. 
# Given K, find how many non-negative integers x have the property that f(x) = K.

# Example 1:
# Input: K = 0
# Output: 5
# Explanation: 0!, 1!, 2!, 3!, and 4! end with K = 0 zeroes.

# Example 2:
# Input: K = 5
# Output: 0
# Explanation: There is no x such that x! ends in K = 5 zeroes.
# Note:

# K will be an integer in the range [0, 10^9].

class PreimageSizeFZF1:

    # <TLE>
    def doit1(self, K):
        """
        :type K: int
        :rtype: int
        """
        i, zeros = 0, 0
        while True:
            
            num = i
            while num > 0 and num % 5 == 0:
                zeros += 1
                num /= 5

            if zeros >= K:
                break

            i += 5

        return 5 if zeros == K else 0



    # Definef(n)=>K, where K is the number of trailing zeroes in n!
    # see https://leetcode.com/problems/factorial-trailing-zeroes/description/
    # Define f-1(K) => n, where n is any value such that f(n) = K, or None if no such n exists
    # Implement using binary search on f
    # Given K, find n = f-1(K)
    # If n==None, the answer is 0
    # otherwise, search up/down from n to find for how many values f(n+d)=K, where d is in [-5,5]

    def doit(self, K):
        """
        :type K: int
        :rtype: int
        """

        def zeros(n):
            res = 0
            while n > 4 :
                n //= 5
                res += n
            return res
        
        def binarySearch(lo, hi):
            
            while lo < hi:
                
                mid = (lo + hi) // 2
            
                n = zeros(mid)

                if n == K:
                    return mid
                elif n > K:
                    hi = mid - 1
                else:
                    lo = mid + 1
            
            if zeros(lo) == K:
                return lo

            if zeros(hi) == K:
                return hi

            return 0

        M = (1 << 63) -1
        n = binarySearch(0, M)

        if not n:
            return 0

        cnt = 1
        for d in (1, -1):
            i = n
            while i + d >= 0 and zeros(i + d) == K:
                cnt += 1
                i += d

        return cnt
       

class PreimageSizeFZF:


#Some basic observations:

# 1. The number of trailing zeros of the factorial x! is given by the minimum of num_2 and num_5, 
# where the former is the total number of factor 2 of integers in the range [1, x], 
# while the latter is the total number of factor 5 of these integers. Since we always have more factors of 2 than 5, 
# the number of trailing zeros of x! will always be num_5.

# 2. num_5 of x! can be computed by summing up the count of integers in the range [1, x] 
# that are integer multiples of 5, 25, 125, ..., 5^k, ..., etc. A simple implementation is as follows:

# 3. Given two non-negative integers x and y, if x <= y, then numOfTrailingZeros(x) <= numOfTrailingZeros(y), 
# which implies numOfTrailingZeros is a non-decreasing function of x.

# Our first binary solution is based on the third observation where we search the range of integers such that the numOfTrailingZeros 
# function is evaluated to K, as shown below.

    def numofTrailingZeros(self, n):
        res = 0
        while n > 0:
            n //= 5
            res += n
        return res

# Binary search solution ONE -- search for x range:

# This solution takes advantage of the last observation mentioned above, 
# where we use binary search to find the largest integers x and y such that numOfTrailingZeros(x) <= K and numOfTrailingZeros(y) <= K-1, respectively. 
# Then the factorial of all integers in the range (y, x] (left exclusive, right inclusive) will have K trailing zeros. 
# Therefore the total number of non-negative integers whose factorials have K trailing zeros will be given by x - y.

# The following is the Java code for this solution, where the time complexity is O((logK)^2) and space complexity is O(1). 
# Note that x! will always have at least x/5 trailing zeros, therefore, if x is the largest integer such that x! has no more than K trailing zeros,
# then we have x <= 5 * (K + 1), which can serve as the upper bound of our binary search.



    def doit(self, K):
        """
        :type K: int
        :rtype: int
        """
        def bs(n):
            l, r = 0, 5 * (n + 1)

            while l <= r:
                m = (l + r) // 2
                
                s = self.numofTrailingZeros(m)
        
                if s <= n:
                    l = m + 1
                else:
                    r = m - 1

            return r

        return bs(K) - bs(K-1)

    def doit1(self, K):
        """
        :type K: int
        :rtype: int
        """
        l, r = 0, 5 * (K + 1)

        while l <= r:
            
            m = (l + r) // 2

            s = self.numofTrailingZeros(m)

            if s == K:
                return 5
            
            if s < K:
                l = m + 1
            else:
                r = m - 1
        
        return 0



# Binary search solution THREE -- search for valid K values:

# As mentioned above, the valid K values will form an ordered list of ranges separated by gaps. We can order them as follows:

# index:      0        1           2      ...       m
# range:    [0, 5)   [6, 11)    [12, 17)  ...  [T_m, T_m + 5)
# gaps:  {}       {5}       {11}          ... 
# If we take all valid ranges and gaps before index m, we know those values will fill up the range [0, T_m), 
# in which there are m * 5 valid values (we have m valid ranges and each range contains 5 elements), and sum(gap_i) invalid values 
# (where gap_i is the number of elements in the i-th gap with 0 <= i <= m, and we define that the i-th gap is immediately preceding the i-th range).

# So we obtain:
# T_m = m * 5 + sum(gap_i)
# Now to compute T_m, we need to evalutae sum(gap_i). To evalutae sum(gap_i), we need to refer to its definition: the number of elements in the i-th gap. 
# We know that a gap is generated whenever x is an integer multiple of 25 and the number of elements in the gap is given by the number of factor 5 in x/5. 
# Therefore the i-th gap corresponds to x_i = i * 25, and sum(gap_i) is equivalent to the total sum of factor 5 of integers in the range [1, 5*m], 
# which by definition is given by numOfTrailingZeros(m * 5). So we arrive at:

# T_m = m * 5 + numOfTrailingZeros(m * 5)

# For the given K, we can do a binary search to find the largest index m such that T_m <= K, then K will be valid if and only if it falls within the m-th range. 
# The following is the code for this solution, with time and space complexities the same as the first solution.


    def doit2(self, K):
        """
        :type K: int
        :rtype: int
        """
        l, r = 0, K/5

        while l <= r:
            
            m = (l + r) // 2
            s = m * 5 + self.numofTrailingZeros(5 * m)

            if s <= K:
                l = m + 1
            else:
                r = m - 1

        return 5 if K < r * 5 + self.numofTrailingZeros(r * 5) + 5 else 0



# Binary search solution FOUR -- search for invalid K values:

# In constrast to the previous solution, this solution tries to directly identify the set containing all the invalid K values and check if the given K value falls into this invalid set. To build the invalid set, we will divide the x values into ranges of the form (0, 5^m] and find the skipped values in the corresponding K ranges (recall that the skipping will happen whenever x is an integer multiple of 25), for example,

# m = 1: the corresponding K range is [0, 1] and no values in this range are skipped, so the invalid set is empty. We will denote it as S1 = {} with length f1 = 0.

# m = 2: the corresponding K range is [0, 6] and we do have one value that is skipped, which is 5. So the invalid set will be S2 = {5} with length f2 = 1.

# m = 3: the corresponding K range is [0, 31] and we have multiple values that are skipped. In this case, the invalid set will be S3 = {5, 11, 17, 23, 29, 30} with length f3 = 6.

# ... and so on

# Note that the invalid set of K values for the x range (0, 5^m] can be constructed from that of (0, 5^(m-1)]. This is because (0, 5^m] can be subdivided into five smaller ranges:

# (0, 5^(m-1)]
# (5^(m-1), 2 * 5^(m-1)]
# (2 * 5^(m-1), 3 * 5^(m-1)]
# (3 * 5^(m-1), 4 * 5^(m-1)]
# (4 * 5^(m-1), 5 * 5^(m-1)]

# All these subranges will contain the same number of skipped K values except for the last one, which produces one additional invalid K value due to an extra factor of 5 at x = 5^m. Let's take m = 3 as an example, where the x range is (0, 125]. The five subranges are (0, 25], (25, 50], (50, 75], (75, 100], (100, 125]. There will be one K value skipped for each of the first four ranges: (0, 25], (25, 50], (50, 75], (75, 100], and two K values skipped for the last range (100, 125] due to the extra factor of 5 at x = 125 (compared to x = 25).

# So in general we have f_m = 5 * f_(m-1) + 1. Now to construct S_m from S_(m-1), we have to find the values skipped in each of the last four subranges. Note that they are not just copies of S_(m-1), but instead, will be S_(m-1) shifted by some value (that is, a new set obtained by shifting the elements in S_(m-1)). The shifting value will be an integer multiple of f_m, so that we have:

# Subranges:                          Skipped values
# (0, 5^(m-1)]                        S_(m-1)
# (5^(m-1), 2 * 5^(m-1)]              S_(m-1) + f_m
# (2 * 5^(m-1), 3 * 5^(m-1)]          S_(m-1) + 2 * f_m
# (3 * 5^(m-1), 4 * 5^(m-1)]          S_(m-1) + 3 * f_m
# (4 * 5^(m-1), 5 * 5^(m-1)]          S_(m-1) + 4 * f_m
# Therefore, S_m can be written in terms of S_(m-1) as:

# S_m = {S_(m-1)} U {S_(m-1) + f_m} U {S_(m-1) + 2 * f_m} U {S_(m-1) + 3 * f_m} U {S_(m-1) + 4 * f_m} U {5*f_m}.

# where U means union operation and the last single element 5 * f_m is due to the extra factor of 5 at x = 5^m.

# Okay, we have obtained the recurrence relations for S_m, but apparently we cannot afford to compute its elements explicitly (which requires exponential space and time). So how do we check if the given K value is in S_m or not?

# Our strategy is simple: first check if K is the single element 5 * f_m. If not, we will take the modulo with respect to f_m and recursively check to see if the remainder is in S_(m-1). We can do this because if an element is in the set S_(m-1) + k * f_m, then the remainder of the element with respect to f_m will be in the set S_(m-1).

# So finally, here is the code for this solution. Note that the given K value does not exceed 10^9 so it makes no sense to test S_m with size greater than that, hence we start with the one with size right below 10^9, which happens to be 305175781. The time complexity is then given by O(logK) and space complexity O(1).


    def doit3(self, K):
        """
        :type K: int
        :rtype: int
        """
        f = 305175781
        while f > 0:
            if 5 * f == K:
                return 0

            K %= f
            f = (f - 1) / 5

        return 5


if __name__ == "__main__":

    res = PreimageSizeFZF().doit(0)

    res = PreimageSizeFZF().doit(5)

    res = PreimageSizeFZF().doit(6)

    res = PreimageSizeFZF().doit(7)
    
    res = PreimageSizeFZF().doit(80502705)
    
    pass