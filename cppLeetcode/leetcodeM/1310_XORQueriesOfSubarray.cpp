/*
1310. XOR Queries of a Subarray

Given the array arr of positive integers and the array queries where queries[i] = [Li, Ri], for each query i compute the XOR of elements from Li to Ri (that is, arr[Li] xor arr[Li+1] xor ... xor arr[Ri] ). Return an array containing the result for the given queries.
 

Example 1:

Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
Output: [2,7,14,8] 
Explanation: 
The binary representation of the elements in the array are:
1 = 0001 
3 = 0011 
4 = 0100 
8 = 1000 
The XOR values for queries are:
[0,1] = 1 xor 3 = 2 
[1,2] = 3 xor 4 = 7 
[0,3] = 1 xor 3 xor 4 xor 8 = 14 
[3,3] = 8
Example 2:

Input: arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
Output: [8,0,4,4]
 

Constraints:

1 <= arr.length <= 3 * 10^4
1 <= arr[i] <= 10^9
1 <= queries.length <= 3 * 10^4
queries[i].length == 2
0 <= queries[i][0] <= queries[i][1] < arr.length

*/
#include <vector>

using std::vector;

class xorQueries {

public:

    /*
        Explanation
        In-place calculate the prefix XOR of input A.

        For each query [i, j],
        if i == 0, query result = A[j]
        if i != 0, query result = A[i - 1] ^ A[j]


        Complexity
        Time O(N)
        O(1) extra space
        O(Q) for output
    */
    vector<int> doit_(vector<int>& A, vector<vector<int>>& queries) {
        vector<int> res;
        for (int i = 1; i < A.size(); ++i)
            A[i] ^= A[i - 1];

        for (auto &q: queries)
            res.push_back(q[0] > 0 ? A[q[0] - 1] ^ A[q[1]] : A[q[1]]);
        
        return res;
    }

    vector<int> doit_presum(vector<int>& arr, vector<vector<int>>& queries) {
        
        int n = arr.size();
        vector<int> presumXOR(n+1, 0);
        
        for (int i = 0; i < arr.size(); i++) {
            presumXOR[i+1] = presumXOR[i] ^ arr[i];
        }
        
        vector<int> ans;
        for (const auto& c: queries) {
            ans.push_back(presumXOR[c[1]+1] ^ presumXOR[c[0]]);
        }
        
        return ans;
    }
};