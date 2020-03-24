/*
 
 995. Minimum Number of K Consecutive Bit Flips
 
 # In an array A containing only 0s and 1s, a K-bit flip consists of choosing a (contiguous) subarray of length K and
 # simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.

 # Return the minimum number of K-bit flips required so that there is no 0 in the array.  If it is not possible, return -1.


 # Example 1:

 # Input: A = [0,1,0], K = 1
 # Output: 2
 # Explanation: Flip A[0], then flip A[2].

 # Example 2:

 # Input: A = [1,1,0], K = 2
 # Output: -1
 # Explanation: No matter how we flip subarrays of size 2, we can't make the array become [1,1,1].

 # Example 3:

 # Input: A = [0,0,0,1,0,1,1,0], K = 3
 # Output: 3
 # Explanation:
 # Flip A[0],A[1],A[2]: A becomes [1,1,1,1,0,1,1,0]
 # Flip A[4],A[5],A[6]: A becomes [1,1,1,1,1,0,0,0]
 # Flip A[5],A[6],A[7]: A becomes [1,1,1,1,1,1,1,1]

 
 */
#include <vector>
using std::vector;


class MinKBitFlips {
public:
    int doit(vector<int>&& A, int K) {
        int N = A.size();
        vector<int> hint(N, 0);
        int ans = 0, flip = 0;
        
        // When we flip a subarray like A[i], A[i+1], ..., A[i+K-1]
        // we can instead flip our current writing state, and put a hint at
        // position i+K to flip back our writing state.
        
        for (int i = 0; i < A.size(); i++) {
            
            flip ^= hint[i];
            
            if ((flip ^ A[i]) == 0) { // If we must flip the subarray starting here...
                
                ans++; // We're flipping the subarray from A[i] to A[i+K-1]
                
                if (i + K > N) {
                    return -1;  // If we can't flip the entire subarray, its impossible
                }
                
                flip ^= 1;
                
                if (i + K < N) {
                    hint[i + K] ^= 1;
                }
            }
        }
        
        
        return ans;
    }
};


void test_995_minimum_number_of_consecutive_bit_flips() {
    
    auto res1 = MinKBitFlips().doit(vector<int>{0,1,0}, 1);
    
    auto res2 = MinKBitFlips().doit(vector<int>{1,1,0}, 2);
    
    auto res3 = MinKBitFlips().doit(vector<int>{0,0,0,1,0,1,1,0}, 3);

    return;
}
