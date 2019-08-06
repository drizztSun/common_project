
# 4 Median of Two Sorted Array

# There are two sorted arrays nums1 and nums2 of size m and n respectively.

# Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

# Example 1:
# nums1 = [1, 3]
# nums2 = [2]

# The median is 2.0

# Example 2:
# nums1 = [1, 2]
# nums2 = [3, 4]

# The median is (2 + 3)/2 = 2.5


class FindMedianSortedArrays:

    def verifyMedian(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        nums1.extend(nums2)
        nums1.sort()
        N = len(nums1)

        if N % 2:
            return nums1[N/2]
        else:
            return (nums1[N/2] + nums1[N/2-1]) / 2.0

    def doit(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        # always make A being the shorter one
        A, B, N1, N2 = nums1, nums2, len(nums1), len(nums2)
        if N1 > N2:
            A, B, N1, N2 = B, A, N2, N1
            
        lo, hi = 0, N1
        # left = right(even) or left = right + 1(odd)
        half = (N1 + N2 + 1) // 2
        
        while lo <= hi:
            # m1 is from 0 ~ N1
            m1 = (lo + hi) // 2
            # because half is greater and equal to N1, m2 will be always valid [0, N2) 
            m2 = half - m1
            
             # if N1 == N2 and m1 == 0, then m2 == N2. but m1 > 0, so m2 will never being N2  
            if m1 > 0 and A[m1-1] > B[m2]:
                hi = m1 - 1
            
            # if N1 == N2 and m1 == N1, then m2 == 0. but m1 < N1, so m2 will never being 0 
            elif m1 < N1 and B[m2-1] > A[m1]:
                lo = m1 + 1
            
            else:
                if m1 == 0:
                    max_left = B[m2-1]
                elif m2 == 0:
                    max_left = A[m1-1]
                else:
                    max_left = max(A[m1-1], B[m2-1])
                
                if (N1 + N2) % 2:
                    return max_left
                
                if m2 == N2:
                    min_right = A[m1]
                elif m1 == N1:
                    min_right = B[m2]
                else:
                    min_right = min(A[m1], B[m2])
            
                return (max_left + min_right) / 2.0

    def doit2(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        A, B, m, n = nums1, nums2, len(nums1), len(nums2)
        if m > n: 
            A, B, m, n = B, A, n, m

        if n == 0: 
            raise ValueError
        
        imin, imax, half_len = 0, m, (m + n + 1) // 2
        
        while imin <= imax:
            i = (imin + imax) // 2
            j = half_len - i
            
            if i < m and B[j-1] > A[i]:
                imin = i+1

            elif i > 0  and A[i-1] > B[j]:
                imax = i-1

            else:
                if i == 0: 
                    max_of_left = B[j-1]
                elif j == 0: 
                    max_of_left = A[i-1]
                else: 
                    max_of_left = max(B[j-1], A[i-1])
                
                if (m+n)%2 == 1:
                    return max_of_left
                
                if i == m: 
                    min_of_right = B[j]
                elif j == n: 
                    min_of_right = A[i]
                else: 
                    min_of_right = min(B[j], A[i])
                
                return (max_of_left + min_of_right)/2.0

    def doit1(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        def median(v1, v2):
            if len(v1) > len(v2):
                return median(v2, v1)

            lo, hi = 0, len(v1) * 2
            N1, N2 = len(v1), len(v2)
            while lo <= hi:
                
                mid1 = (lo + hi) / 2
                mid2 = N1 + N2 - mid1

                L1 = float('-inf') if mid1 == 0 else v1[(mid1-1)/2]
                L2 = float('-inf') if mid2 == 0 else v2[(mid2-1)/2]

                R1 = float('inf') if mid1 == N1 * 2 else v1[mid1/2]
                R2 = float('inf') if mid2 == N2 * 2 else v2[mid2/2]

                if L1 > R2:
                    hi = mid1 - 1
                elif L2 > R1:
                    lo = mid1 + 1
                else:
                    return (max(L1, L2) + min(R1, R2)) / 2.0
                
        return median(nums1, nums2)


if __name__ == "__main__":

    res = FindMedianSortedArrays().doit([1, 3], [2])

    res = FindMedianSortedArrays().doit([1, 2], [3, 4])

    res = FindMedianSortedArrays().doit([1, 3, 5, 7, 9], [0, 2, 4, 6, 8, 10])

    res = FindMedianSortedArrays().doit([1, 3, 5, 7], [2, 4, 6, 8])
        
