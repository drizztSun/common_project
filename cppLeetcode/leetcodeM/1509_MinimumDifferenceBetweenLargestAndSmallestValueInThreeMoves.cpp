/*
1509. Minimum Difference Between Largest and Smallest Value in Three Moves



*/
#include <vector>
#include <algorithm>

using std::vector;

class MinimumDifferenceBetweenLargestAndSmallestValue {


public:

    /*
        Intuition
        If we can do 0 move, return max(A) - min(A)
        If we can do 1 move, return min(the second max(A) - min(A), the max(A) - second min(A))
        and so on.


        Explanation
        We have 4 plans:

        1. kill 3 biggest elements
        2. kill 2 biggest elements + 1 smallest elements
        3. kill 1 biggest elements + 2 smallest elements
        4. kill 3 smallest elements

        Example from @himanshusingh11:

        A = [1,5,6,13,14,15,16,17]
        n = 8

        Case 1: kill 3 biggest elements

        All three biggest elements can be replaced with 14
        [1,5,6,13,14,15,16,17] -> [1,5,6,13,14,14,14,14] == can be written as A[n-4] - A[0] == (14-1 = 13)

        Case 2: kill 2 biggest elements + 1 smallest elements

        [1,5,6,13,14,15,16,17] -> [5,5,6,13,14,15,15,15] == can be written as A[n-3] - A[1] == (15-5 = 10)

        Case 3: kill 1 biggest elements + 2 smallest elements

        [1,5,6,13,14,15,16,17] -> [6,6,6,13,14,15,16,16] == can be written as A[n-2] - A[2] == (16-6 = 10)

        Case 4: kill 3 smallest elements

        [1,5,6,13,14,15,16,17] -> [13,13,13,13,14,15,16,17] == can be written as A[n-1] - A[3] == (17-13 = 4)

        Answer is minimum of all these cases!


        Solution 1: Quick Sort
        I used quick sort to find out the biggest and smallest
        So time and space are O(quick sort)
    */

    int doit_sort(vector<int> A) {
        int n = A.size();
        if (n < 5) return 0;
        std::sort(A.begin(), A.end());
        return std::min({A[n - 1] - A[3], A[n - 2] - A[2], A[n - 3] - A[1], A[n - 4] - A[0]});
    }

    /*
        Solution 2: Partial Sorting
        Changed from @Sklert
        Reference https://en.cppreference.com/w/cpp/algorithm/partial_sort

        Time O(NlogK)
        Space O(logK)
    */
    int minDifference(vector<int>& A) {
        int n = A.size();
        if (n < 5) return 0;

        std::partial_sort(A.begin(), A.begin() + 4, A.end());
        std::nth_element(A.begin() + 4, A.end() - 4, A.end());
        std::sort(A.end() - 4, A.end());
        
        return std::min({A[n - 1] - A[3], A[n - 2] - A[2], A[n - 3] - A[1], A[n - 4] - A[0]});
    }
}