/*
769. Max Chunks To Make Sorted

Given an array arr that is a permutation of [0, 1, ..., arr.length - 1], we split the array into some number of "chunks" (partitions), and individually sort each chunk.  
After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

Example 1:

Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.
Example 2:

Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.
Note:

arr will have length in range [1, 10].
arr[i] will be a permutation of [0, 1, ..., arr.length - 1].
*/
#include <vector>

using std::vector;




class MaxChunksToSorted {

public:

    /*
        Approach #1: Brute Force [Accepted]
        Intuition and Algorithm

        Let's try to find the smallest left-most chunk. If the first k elements are [0, 1, ..., k-1], then it can be broken into a chunk, and we have a smaller instance of the same problem.

        We can check whether k+1 elements chosen from [0, 1, ..., n-1] are [0, 1, ..., k] by checking whether the maximum of that choice is k.
    */
    int doit_(vector<int>& arr) {
        
        int N = arr.size();
        int maxv = 0, ans = 0;
        
        for (int i = 0; i < N; i++) {
            
            maxv = std::max(maxv, arr[i]);
            
            if (maxv == i) {
                ans++;
                // maxv--;
            }
            
        }
        
        return ans;
    }
};