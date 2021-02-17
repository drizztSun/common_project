/*
930. Binary Subarrays With Sum


In an array A of 0s and 1s, how many non-empty subarrays have sum S?

 

Example 1:

Input: A = [1,0,1,0,1], S = 2
Output: 4
Explanation: 
The 4 subarrays are bolded below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
 

Note:

A.length <= 30000
0 <= S <= A.length
A[i] is either 0 or 1.

*/
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class BinarySubarryWithSum {

public:

    /*
        Solution 1: HashMap
        Count the occurrence of all prefix sum.

        I didn't notice that the array contains only 0 and 1,
        so this solution also works if have negatives.

        Space O(N)
        Time O(N)
    */
    int doit_hashtable(vector<int>& A, int S) {
        unordered_map<int, int> c({{0, 1}});
        int psum = 0, res = 0;
        for (int i : A) {
            psum += i;
            res += c[psum - S];
            c[psum]++;
        }
        return res;
    }

    /*
        Solution 2: Sliding Window
        We have done this hundreds time.
        Space O(1)
        Time O(N)

    */
    int numSubarraysWithSum(vector<int>& A, int S) {

        std::function<int(int)> atMost = [&](int S) {
            
            if (S < 0) return 0;
            
            int res = 0, i = 0, n = A.size();

            for (int j = 0; j < n; j++) {
                S -= A[j];
                while (S < 0)
                    S += A[i++];
                res += j - i + 1;
            }
            
            return res;
        }

        return atMost(A, S) - atMost(A, S - 1);
    }


};