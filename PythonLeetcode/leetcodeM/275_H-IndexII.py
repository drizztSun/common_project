"""
275. H-Index II


Given an array of citations sorted in ascending order (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

Example:

Input: citations = [0,1,3,5,6]
Output: 3 
Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had 
             received 0, 1, 3, 5, 6 citations respectively. 
             Since the researcher has 3 papers with at least 3 citations each and the remaining 
             two with no more than 3 citations each, her h-index is 3.
Note:

If there are several possible values for h, the maximum one is taken as the h-index.

Follow up:

This is a follow up problem to H-Index, where citations is now guaranteed to be sorted in ascending order.
Could you solve it in logarithmic time complexity?
"""

class HIndexII:

    """
        Approach 1: Linear search, O(k) time
        Intuition

        Thanks to the fact that the list of citation numbers is sorted in the ascending order, one could solve the problem in a single pass of iteration.

        Let's consider an article whose citation number c is index at i, i.e c = citations[i]. We would know that the number of articles whose citation number is higher than c would be n - i - 1.
        And together with the current article, there are n - i articles that are cited at least c times.

        Given the definition of H-Index, we just need to find the first article at i whose citation number c = citation[i] is greater or equal to n - i, i.e. c >= n - i. As we know that all the articles following i would be cited at least c times, so in total there are n - i articles that are cited at least c times. As a result, according to the definition, the H-Index of the author should be n - i.

        pic

        Following the above intuition, it is straightforward to implement the algorithm. We give some examples in the following.

        Implementation


        Complexity Analysis

        Time complexity : O(N) where N is the length of the input list, since in the worse case we would iterate the entire list.

        Space complexity : O(1), it's a constant space solution.

    """
    def doit_(self, citations):
        """
        :type citations: List[int]
        :rtype: int
        """
        n = len(citations)
        for idx, c in enumerate(citations):
            if c >= n - idx:
                return n - idx
        return 0

    """
        Approach 2: Binary Search, O(log N) time
        Intuition

        Following in the intuition we elaborated in the Approach 1, the problem is actually boiled down to the following task:

        Given a sorted list citations of size n in ascending order, one is asked to find the first number citations[i] which meets the constraint of citations[i] >= n - i.

        With the above formulation of the problem, it becomes clear that one could apply the binary search algorithm to solve the problem. In binary search algorithm, we recursively reduce the searching scope into half, which leads to a more optimal \mathcal{O}(\log N)O(logN) time complexity comparing to the \mathcal{O}(N)O(N) of the linear search.

        pic

        Algorithm

        First we pick a pivot element that is in the middle of the list, i.e. citations[pivot], which would divide the original list into two sublists: citations[0 : pivot - 1] and citations[pivot + 1 : n].

        Then comparing between the values of n - pivot and citations[pivot] element, our binary search algorithm breaks down to the following 3 cases:

        citations[pivot] == n - pivot: We found the desired element !

        citations[pivot] < n - pivot: Since the desired element should be greater or equal to n - pivot, we then further look into the sublist on the right hand side, i.e. citations[pivot + 1 : n].

        citations[pivot] > n - pivot: We should look into the sublist on the left hand side, i.e. citations[0 : pivot-1].

        A minor difference to the typical binary search algorithm, is that in this case we return the value of n - pivot as the result, rather than the value of the desired element.

        Implementation


        Complexity Analysis

        Time complexity : \mathcal{O}(\log N)O(logN) since we apply binary search algorithm here.

        Space complexity : \mathcal{O}(1)O(1), it's a constant space solution.
    """
    def doit_binary_search(self, citations):
        """
        :type citations: List[int]
        :rtype: int
        """
        n = len(citations)
        left, right = 0, n - 1
        while left <= right:
            pivot = left + (right - left) // 2
            if citations[pivot] == n - pivot:
                return n - pivot
            elif citations[pivot] < n - pivot:
                left = pivot + 1
            else:
                right = pivot - 1
        
        return n - left

    def doit_binary_search(self, citations: list) -> int:

        n = len(citations)
        l, r = 0, n-1
        
        while l <= r:
            mid = (l+r) // 2
            
            if citations[mid] >= n - mid:
                r = mid-1
            else:
                l = mid+1
                
        return n - l
        