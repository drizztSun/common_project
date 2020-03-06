/*
 
 # 1004. Max Consecutive Ones III

 # Given an array A of 0s and 1s, we may change up to K values from 0 to 1.

 # Return the length of the longest (contiguous) subarray that contains only 1s.


 # Example 1:

 # Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
 # Output: 6
 # Explanation:
 # [1,1,1,0,0,1,1,1,1,1,1]
 # Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.

 # Example 2:

 # Input: A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
 # Output: 10
 # Explanation:
 # [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
 # Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.


 # Note:

 # 1 <= A.length <= 20000
 # 0 <= K <= A.length
 # A[i] is 0 or 1
 
 
 */

#include <vector>
using std::vector;

class LongestOnes {
    
public:
    
    int doit(vector<int>&& A, int K) {
        
        int ans = 0;
        int j = 0;
        int ones = 0, zeros = 0;
        
        for (auto i = 0; i <= A.size(); i++) {
        
            if (i < A.size())
                if (A[i] == 1)
                    ones++;
                else
                    zeros++;
            
            while (j < i and zeros > K) {
                if (A[j] == 1)
                    ones--;
                else
                    zeros--;
                j++;
            }
            
            if (zeros <= K)
                ans = std::max(ans, ones + zeros);
        }
        
        return ans;
    }
    
    int doit1(vector<int>&& s, int k) {
        
        int winStart = 0;
        int cnt0 = 0, cnt1 = 0;
        int maxlen = 0;
        int maxcount = 0;
        
        for (int winEnd = 0; winEnd < s.size(); winEnd++) {
            
            if (s[winEnd])
                cnt1++;
            
            maxcount = std::max(maxcount, cnt1);
            while (winEnd-winStart+1 - maxcount > k) {
                if (s[winStart])
                    cnt1--;
                winStart++;
            }
            maxlen = std::max(maxlen, winEnd-winStart+1);
        }
        return maxlen;
    }
};


void test_1004_max_consecutive_ones_III() {
    
    auto res1 = LongestOnes().doit(vector<int>{1,1,1,0,0,0,1,1,1,1,0}, 2);
    
    auto res2 = LongestOnes().doit(vector<int>{0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, 3);
    
    return;
}
