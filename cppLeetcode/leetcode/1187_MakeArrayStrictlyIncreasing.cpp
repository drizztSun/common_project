/*
 1187. Make Array Strictly Increasing
 
 Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.

 In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].

 If there is no way to make arr1 strictly increasing, return -1.

  

 Example 1:

 Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
 Output: 1
 Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
 Example 2:

 Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
 Output: 2
 Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6, 7].
 Example 3:

 Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
 Output: -1
 Explanation: You can't make arr1 strictly increasing.
  

 Constraints:

 1 <= arr1.length, arr2.length <= 2000
 0 <= arr1[i], arr2[i] <= 10^9

 
 
 
 */
#include <stdlib.h>
#include <vector>
#include <algorithm>

using std::vector;


class MakeStrictIncreaingArray {
    
public:
    
    /*
     
     DP : SImilar to 801. Minimum swaps to make sequences increasing. Unlike 801, we need to track a[i] = b[j]
     
     Elements in b can be use arbitrary times, we can remove duplicates and sort it.
     
     Swap[i][j] := min cost to make a[0~i] valid by a[i] <= b[j]
     keep[i] := min cost to make a[0~i] valid by keeping a[i]
     
     Init:
     keep[0] = 0 # a[0] is always valid, no cost
     swap[0][*] = 1 # 1 op to assign b[j] to a[0]
     
     
     a[0......i-1][a[i-1] / b[i]]
     a[0..i-1] are already increasing.
     
     Try all pairs (a[i], b[i])
     
     case 1 : a[i] > a[i-1], keep[i] = keep[i-1]
     case 2 : b[j] > a[i-1], swap[i][j] = keep[i-1]+1
     case 3 : a[i] > b[j], keep[i] = min(swap[i-1][k]), k <= j, so all b[k] < b[j] > a[i] O(1).
     case 4: swap[i][j] = min(swap[i-1][k] + 1), k < j
     
     Ans: min(min(swap[m-1]), keep[m-1]))
     
     Time complexity: O(m*n)
     Space complexity: O(m*n) -> O(m + n)
     */
    
    int doit_dp(vector<int>& a, vector<int>& b) {
        
        constexpr int kMod = 1e9 + 7;
        int m = a.size();
        
        // Sort arr2 and make
        sort(begin(b), end(b));
        b.resize(unique(begin(b), end(b)) - begin(b));
        int n = b.size();
        
        
        // min steps to make a[0~i] valid by keeping a[i]
        vector<int> keep(m, kMod);
        // no cost to keep first elements
        keep[0] = 0;
        
        // Swap[i][j] := min steps to make a[0~i] valid by a[i] = b[j]
        vector<vector<int>> swap(m, vector<int>(n, kMod));
        
        // Init to swap[0] to 1 since swapping a[0] with b[j] cost 1
        fill(begin(swap[0]), end(swap[0]), 1);
        
        for (int i = 1; i < m; i++) {
            
            int min_keep = kMod, min_swap = kMod;
            
            for (int j = 0; j < n; j++) {
                
                // for case 4
                if (j > 0) min_swap = std::min(min_swap, swap[i-1][j-1] +  1);
                
                // for case 3
                if (a[i] > b[j]) min_keep = std::min(min_keep, swap[i-1][j]);
                
                // case 1
                if (a[i] > a[i-1]) keep[i] = keep[i-1];
                    
                // case 2
                if (b[j] > a[i-1]) swap[i][j] = keep[i-1] + 1;

                swap[i][j] = std::min(swap[i][j], min_swap);
                keep[i] = std::min(keep[i], min_keep);
            }
            
        }
        
        int s = *min_element(begin(swap.back()), end(swap.back()));
        int k = keep.back();
        
        int ans = std::min(s, k);
        
        return ans >= kMod ? -1 : ans;
    }
    
    int makeArrayIncreasing(vector<int>& a, vector<int>& c) {
        
        constexpr int kInf = 1e9;
        int m = a.size();
        // Sort b and make it only containing unique numbers.
        sort(begin(c), end(c));
        vector<int> b;
        for (int i = 0; i < c.size(); ++i) {
          if (!b.empty() && c[i] == b.back()) continue;
          b.push_back(c[i]);
        }
        int n = b.size();
        
        // min steps to make a[0~i] valid by keeping a[i]
        vector<int> keep(m, kInf);
        keep[0] = 0;
        // swap[i][j] := min steps to make a[0~i] valid by a[i] = b[j]
        vector<int> swap(n, 1);
        
        for (int i = 1; i < m; ++i) {
            
          int min_keep = kInf;
          int min_swap = kInf;
          vector<int> temp(n, kInf);
            
          for (int j = 0; j < n; ++j) {
              
            if (j > 0) min_swap = std::min(min_swap, swap[j - 1] + 1);
            if (a[i] > b[j]) min_keep = std::min(min_keep, swap[j]);
              
            if (a[i] > a[i - 1]) keep[i] = keep[i - 1];
            if (b[j] > a[i - 1]) temp[j] = keep[i - 1] + 1;
              
            temp[j] = std::min(temp[j], min_swap);
            keep[i] = std::min(keep[i], min_keep);
              
          }
          temp.swap(swap);
        }
        
        int s = *min_element(begin(swap), end(swap));
        int k = keep.back();
        int ans = std::min(s, k);
        return ans >= kInf ? -1 : ans;
    }
};
