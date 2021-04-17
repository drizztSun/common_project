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

    /*
        995.Minimum-Number-of-K-Consecutive-Bit-Flips
        本题的最优策略其实很容易想到。我们从前往后依次查看A[i]：如果A[i]是1，那么我们就跳过；如果A[i]是0，那么我们就翻转A[i]，同时需要带着一起翻转A[i+1]~A[i+K-1]。这样一直查下去，看最后K个数是否都是1. 显然我们就有了O(NK)的解法。C++耗时5000多毫秒，竟然也给过了。

        很明显，上述解法的最大弊端是：当A[i]需要翻转时，我们还需要用for循环逐个翻转A[i+1]~A[i+K-1]，效率很差。很容易想到一个简单的改进的方法，用差分数组diff.
        
        差分数组diff[j]记录的是：A[j]经历的翻转次数要比A[j-1]经历的翻转次数多多少？比如说，我们将当前的A[i]翻转了，将会使得A[i+1]~A[i+K-1]整体的翻转次数提升一个，但是之后就又回落下去了。
        
        所以就记录下diff[i+1]+=1, diff[i+K]-=1，这样的话，对任意A[j]经历过的翻转总数是flipNum，那么A[j+1]需要经历的翻转总数就是flipNum+diff[j+1]。

        类似用到差分数组的题目还有：370.Range-Addition
    */
    int minKBitFlips(vector<int>& A, int K) 
    {
        int N = A.size();
        int flipNum=0, result = 0;
        vector<int>diff(N+1,0); 
        // 差分数组diff[i]表示A[i]经历的翻转次数，要比A[i-1]经历的反转次数多多少？
        // 所以 flipNum+diff[i] 表示A[i]真正经历翻转的次数
        
        for (int i=0; i<N; i++)
        {
            flipNum+=diff[i];
            if ((A[i]+flipNum)%2==0 && i+K>N) return -1; 
            if ((A[i]+flipNum)%2==1) continue;            
            result++;
            flipNum++;
            diff[i+K]--;  
            // 如果A[i]需要再反转，说明A[i]~A[i+K-1]这个区间多一次翻转，所以diff[i+K]需要减一
        }
        return result;
    }

public:

    /*
        Approach 1: Greedy + Events
        Intuition

        If the leftmost element is a 0, we must flip the subarray starting at index 0. Similarly, if the leftmost element is a 1, we should not flip the subarray starting at index 0. 
        This proves we can proceed in a greedy manner: after finding out whether we have to flip the first subarray (positions 0 to K-1) or not, we can consider the array with the first element (value 1) removed, and repeat this process.

        We can do better. Every time we flip a subarray A[i], A[i+1], ..., A[i+K-1], we can consider this as two "events", one 'opening event' at position i that marks the start of the subarray, 
        and one 'closing event' at position i+K that marks the end of the subarray. Using these events, we always know how many overlapping flipped subarrays there are: its simply the number of opening events minus the number of closing events.

        Algorithm

        When we flip a subarray, let's call the set of indices we flipped an interval. We'll keep track of flip, the number of overlapping intervals in our current position. 
        We only care about the value of flip modulo 2.

        When we flip an interval starting at i, we create a hint for a closing event at i+K telling us to flip our writing state back.

        Please see the inline comments for more details.


        Complexity Analysis

        Time Complexity: O(N), where NN is length of A.

        Space Complexity: O(N).
    */
    int doit_sweepline(vector<int>&& A, int K) {
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