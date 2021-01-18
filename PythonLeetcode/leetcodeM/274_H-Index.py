"""
274. H-Index

Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, 
and the other N − h papers have no more than h citations each."

Example:

Input: citations = [3,0,6,1,5]
Output: 3 
Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had 
             received 3, 0, 6, 1, 5 citations respectively. 
             Since the researcher has 3 papers with at least 3 citations each and the remaining 
             two with no more than 3 citations each, her h-index is 3.
Note: If there are several possible values for h, the maximum one is taken as the h-index.


"""


class HIndex:

    """
        Summary
        This article is for intermediate readers. It introduces the following ideas: Comparison Sort and Counting Sort.

        Solution
        Approach #1 (Sorting) [Accepted]
        Intuition

        Think geometrically. Imagine plotting a histogram where the yy-axis represents the number of citations for each paper. After sorting in descending order, hh-index is the length of the largest square in the histogram.

        h-index

        Figure 1. hh-index from a plot of decreasing citations for papers

        Algorithm

        To find such a square length, we first sort the citations array in descending order. After sorting, if \mathrm{citations}[i] \gt icitations[i]>i, then papers 00 to ii all have at least i + 1i+1 citations.

        Thus, to find hh-index, we search for the largest ii (let's call it i'i 
        ′
        ) such that

        \mathrm{citations}[i] \gt icitations[i]>i

        and therefore the hh-index is i' + 1i 
        ′
        +1.


    """

    def doit_sort(self, citations: list) -> int:
        # sort it as ascsending 
        citations.sort()
        
        i = 0
        # 
        while i < len(citations) and citations[len(citations) - i - 1] > i:
            i += 1
            
        return i

    """
        O(n) bucket sort, anything value more then length, will be same into array[length]
    """
    def doit_sort(self, citations: list) -> int:

        # Sort and linear scan: O(log n) time and O(n ) space
        # Save counts
        n = len(citations)
        citation2Freq = [0 for x in range(n+1)] #  [i] will tell us how many papers have i citations

        for cites in citations:
            citation2Freq[min(cites,n)] += 1 
        
        atLeast_i_cites = 0 
        for i in reversed(range(n+1)):
            atLeast_i_cites += citation2Freq[i] 
            if atLeast_i_cites >= i:
                return i 
        
        # count number with more than h citations