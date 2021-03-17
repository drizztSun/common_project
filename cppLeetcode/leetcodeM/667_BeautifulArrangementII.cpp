/*
667. Beautiful Arrangement II

Given two integers n and k, you need to construct a list which contains n different positive integers ranging from 1 to n and obeys the following requirement:
Suppose this list is [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.

If there are multiple answers, print any of them.

Example 1:
Input: n = 3, k = 1
Output: [1, 2, 3]
Explanation: The [1, 2, 3] has three different positive integers ranging from 1 to 3, and the [1, 1] has exactly 1 distinct integer: 1.
Example 2:
Input: n = 3, k = 2
Output: [1, 3, 2]
Explanation: The [1, 3, 2] has three different positive integers ranging from 1 to 3, and the [2, 1] has exactly 2 distinct integers: 1 and 2.
Note:
The n and k are in the range 1 <= k < n <= 10^4.

*/
#include <vector>

using std::vector;

class BeautifulArrangement {

public:
    /*
        Approach #2: Construction [Accepted]
        Intuition

        When \text{k = n-1}k = n-1, a valid construction is \text{[1, n, 2, n-1, 3, n-2, ....]}[1, n, 2, n-1, 3, n-2, ....]. 
        One way to see this is, we need to have a difference of \text{n-1}n-1, which means we need \text{1}1 and \text{n}n adjacent; then, we need a difference of \text{n-2}n-2, etc.

        Also, when \text{k = 1}k = 1, a valid construction is \text{[1, 2, 3, ..., n]}[1, 2, 3, ..., n]. So we have a construction when \text{n-k}n-k is tiny, and when it is large. This leads to the idea that we can stitch together these two constructions: we can put \text{[1, 2, ..., n-k-1]}[1, 2, ..., n-k-1] first so that \text{n}n is effectively \text{k+1}k+1, and then finish the construction with the first \text{"k = n-1"}"k = n-1" method.

        For example, when \text{n = 6}n = 6 and \text{k = 3}k = 3, we will construct the array as \text{[1, 2, 3, 6, 4, 5]}[1, 2, 3, 6, 4, 5]. 
        
        This consists of two parts: a construction of \text{[1, 2]}[1, 2] and a construction of \text{[1, 4, 2, 3]}[1, 4, 2, 3] where every element had \text{2}2 added to it (i.e. \text{[3, 6, 4, 5]}[3, 6, 4, 5]).

        Algorithm

        As before, write \text{[1, 2, ..., n-k-1]}[1, 2, ..., n-k-1] first. The remaining \text{k+1}k+1 elements to be written are \text{[n-k, n-k+1, ..., n]}[n-k, n-k+1, ..., n], and we'll write them in alternating head and tail order.

        When we are writing the i^{th}i 
        th
        element from the remaining \text{k+1}k+1, every even ii is going to be chosen from the head, and will have value \text{n-k + i//2}n-k + i//2. Every odd ii is going to be chosen from the tail, and will have value \text{n - i//2}n - i//2.

        **Complexity Analysis**
        Time Complexity: O(n). We are making a list of size \text{n}n.

        Space Complexity: O(n). Our answer has a length equal to \text{n}n.
    */
    vector<int> doit_(int n, int k) {
  
        vector<int> ans(n);
        
        int c = 0;
        for (int v = 1; v < n-k; v++) {
            ans[c++] = v;
        }
        
        for (int i = 0; i <= k; i++) {
            ans[c++] = (i % 2 == 0) ? (n-k + i / 2) : (n - i/2);
        }
        
        return ans;
    }
};