/*
 
 992. Subarrays with K Different Integers
 
 
 Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.

 (For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)

 Return the number of good subarrays of A.

  

 Example 1:

 Input: A = [1,2,1,2,3], K = 2
 Output: 7
 Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
 Example 2:

 Input: A = [1,2,1,3,4], K = 3
 Output: 3
 Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
  
 
 */

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

class SubarraysWithKDistinct {
public:
    int doit(vector<int>&& A, int K) {
        
        unordered_map<int, int> long_wnd, short_wnd;
        int left_long = 0;
        int left_short = 0;
        int cnt_long = 0;
        int cnt_short = 0;
        int ans = 0;
        
        for (auto c: A) {
            
            if (long_wnd[c]++ == 0)
                cnt_long++;
            
            if (short_wnd[c]++ == 0)
                cnt_short++;
            
            while (cnt_long > K) {
                if (long_wnd[A[left_long++]]-- == 1)
                    cnt_long--;
            }
            
            while (cnt_short >= K) {
                if (short_wnd[A[left_short++]]-- == 1)
                    cnt_short--;
            }
            
            ans += left_short - left_long;
        }
        
        return ans;
    }
};


void test_992_subarray_with_kdifferent_integer() {
    
    auto res1 = SubarraysWithKDistinct().doit(vector<int>{1,2,1,2,3}, 2);
    
    auto res2 = SubarraysWithKDistinct().doit(vector<int>{1,2,1,3,4}, 3);
    
    return;
}
