/*
1442. Count Triplets That Can Form Two Arrays of Equal XOR


Given an array of integers arr.

We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).

Let's define a and b as follows:

a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
Note that ^ denotes the bitwise-xor operation.

Return the number of triplets (i, j and k) Where a == b.

 

Example 1:

Input: arr = [2,3,1,6,7]
Output: 4
Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)
Example 2:

Input: arr = [1,1,1,1,1]
Output: 10
Example 3:

Input: arr = [2,3]
Output: 0
Example 4:

Input: arr = [1,3,5,7,9]
Output: 3
Example 5:

Input: arr = [7,11,12,9,5,2,7,17,22]
Output: 8
 

Constraints:

1 <= arr.length <= 300
1 <= arr[i] <= 10^8

*/
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class CountTriplets {

    /*
        1442.Count-Triplets-That-Can-Form-Two-Arrays-of-Equal-XOR
        本题是说，问有多少个相邻的子区间对[i:j]和[j+1:k]，使得这两个子区间的亦或和相等。

        这个问法其实非常巧妙。如果[i:j]和[j+1:k]的亦或和相等，那么这个大区间[i:k]的亦或和就一定等于零。而这个亦或和等于零的区间[i:k]，你从任意位置去分成两部分，这两个子区间的亦或和又肯定是相等的。

        于是这道题等价于，问有多少个区间的亦或和等于0. 对于每一个符合的区间[i:k]，只要令j为i+1到k任意一个位置，都可以满足xor[i:j]==xor[j+1:k]。也就是说，对于符合条件的(i,k)，存在k-i个拆分方法，得到符合条件的(i,j,k)。

        对于求亦或和为0的子区间，就是常见的Hash+Prefix的套路。
    
    */
    int countTriplets(vector<int>& arr) 
    {
        unordered_map<int,vector<int>>Map;
        Map[0].push_back(-1);
        int xorsum = 0;
        int ret = 0;
        for (int k=0; k<arr.size(); k++)
        {
            xorsum ^= arr[k];
            for (int i: Map[xorsum])
                ret += std::max(0, k - i -1);
            Map[xorsum].push_back(k);
        }
        return ret;
    }

public:

    /*
        Solution 1: Brute Force (TLE)
        Brute force all combinations, will TLE.
        Time O(N^4)
        Space O(1)


        Solution 2: Brute Force with prefix
        Calculate all prefix of bitwise-xor operation.
        prefix[0] = 0
        prefix[i] = A[0]^A[1]^...^A[i - 1]
        So that for each (i, j),
        we can get A[i]^A[i+1]^...^A[j] by prefix[j+1]^prefix[i]
        in O(1) time

        Time O(N^3)
        Space O(N)
        Space O(1) if changing the input


        Solution 3: Prefix XOR
        a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
        b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]

        Assume a == b, thus
        a ^ a = b ^ a, thus
        0 = b ^ a, thus
        arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1] ^ arr[j] ^ arr[j + 1] ^ ... ^ arr[k] = 0
        prefix[k+1] = prefix[i]

        We only need to find out how many pair (i, k) of prefix value are equal.
        So we can calculate the prefix array first,
        then brute force count the pair.

        Because we once we determine the pair (i,k),
        j can be any number that i < j <= k,
        so we need to plus k - i - 1 to the result res.

        Time O(N^2)
        Space O(N)
        Space O(1) if changing the input
    */
    int doit_prefix(vector<int>& A) {
        
        A.insert(A.begin(), 0);
        int n = A.size(), res = 0;

        for (int i = 1; i < n; ++i)
            A[i] ^= A[i - 1];
        
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (A[i] == A[j])
                    res += j - i - 1;
        
        return res;
    }

    /*
        Solution 4: Prefix XOR, O(N)
        The problem now is, given an array,
        find out the sum of index distance with A[i] = A[j].
        Let me know if there is a duplicate problem on LeetCode,
        so I can attach a link to help explain.

        Basicly, for the same value in the array,
        we need to count the frequncy and the total value at the same time.

        Time O(N)
        Space O(N)
        Space O(1) if changing the input
    */
    int doit_prefix_1(vector<int>& A) {
        A.insert(A.begin(), 0);
        int n = A.size(), res = 0;

        for (int i = 1; i < n; ++i)
            A[i] ^= A[i - 1];

        unordered_map<int, int> count, total;

        for (int i = 0; i < n; ++i) {
            // There are n A[j {1...n}] == A[i], total is SUM(A[j], j, 1...n), Then we need to calculate i * n - total 
            res += count[A[i]]++ * (i - 1) - total[A[i]];
            total[A[i]] += i;
        }
        return res;
    }

    /*
        Solution 5: Prefix XOR, One Pass
        Time O(N) for one pass
        Space O(N)
    */
    int doit_prefix_2(vector<int>& A) {
        int n = A.size(), res = 0, prefix = 0;
        unordered_map<int, int> count = {{0, 1}}, total;

        for (int i = 0; i < n; ++i) {
            prefix ^= A[i];
            res += count[prefix]++ * i - total[prefix];
            total[prefix] += i + 1;
        }
        return res;
    }
};