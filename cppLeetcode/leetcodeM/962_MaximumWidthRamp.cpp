/*
 
 962. Maximum Width Ramp
 
 Given an array A of integers, a ramp is a tuple (i, j) for which i < j and A[i] <= A[j].  The width of such a ramp is j - i.

 Find the maximum width of a ramp in A.  If one doesn't exist, return 0.

  

 Example 1:

 Input: [6,0,8,2,1,5]
 Output: 4
 Explanation:
 The maximum width ramp is achieved at (i, j) = (1, 5): A[1] = 0 and A[5] = 5.
 Example 2:

 Input: [9,8,1,0,1,9,4,0,4,1]
 Output: 7
 Explanation:
 The maximum width ramp is achieved at (i, j) = (2, 9): A[2] = 1 and A[9] = 1.
 
 */

#include <vector>
using std::vector;

class MaxWidthRamp {
public:
    
    int doit(vector<int>&& A) {
        
        vector<std::pair<int, int>> B;
        for (int i = 0; i < A.size(); i++) {
            B.push_back({A[i], i});
        }
        std::sort(B.begin(), B.end(), [](auto& a, auto& b) {
            return a.first < b.first;
        });
        
        int min_index = B.size();
        int res = 0;
        for (auto& c : B) {
            
            res = std::max(res, c.second - min_index);
            min_index = std::min(min_index, c.second);
        }
        
        return res;
    }
    
    /*
     This algorithm uses a vector to record each possible start of the ramp. The interger low is used to record the current lowest value so that we can decide if we are going to put the potential encountering numbers into the vector.
     For every A[i], we compare its value with the numbers in the vector (from its right). And we consequently update the current longest ramp ret.

     Time Complexity : O(n) but O(n^2) in the worst case. (not sure how to describe this, any comment is appreciated)
     Space Complexity : O(1) but O(n) in the worst case.
     */
    int doit1(vector<int>&& A) {
        
        vector<std::pair<int, int>> v;
        v.push_back({A[0], 0});
        int low = A[0];
        int ret = 0;
        
        for (int i = 1; i < A.size(); i++)
        {
            if (A[i] < low)
            {
                low = A[i];
                v.push_back({A[i], i});
                continue;
            }
            
            int len = 0;
            for (int k = v.size()-1; k >= 0; k--)
            {
                if (A[i] >= v[k].first) len = i - v[k].second;
                else break;
            }
            
            ret = std::max(ret, len);
        }
        return ret;
    }
};


void test_962_maxium_width_ramp() {
    
    auto res1 = MaxWidthRamp().doit(vector<int>{6,0,8,2,1,5});
    
    auto res2 = MaxWidthRamp().doit(vector<int>{9,8,1,0,1,9,4,0,4,1});
    
    auto res3 = MaxWidthRamp().doit(vector<int>{3,28,15,1,4,12,6,19,8,15,3,9,6,4,13,12,6,12,10,1,2,1,4,1,4,0,0,1,1,0});
    
    auto res4 = MaxWidthRamp().doit(vector<int>{3,28,15,1,4,12,6,19,8,15,3,9,6,4,13,12,6,12,10,1,2,1,4,1,4,0,0,1,1,0});
    
    return;
}
