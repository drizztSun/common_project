/*
 
 982. Triples with Bitwise AND Equal To Zero
 
 Given an array of integers A, find the number of triples of indices (i, j, k) such that:

 0 <= i < A.length
 0 <= j < A.length
 0 <= k < A.length
 A[i] & A[j] & A[k] == 0, where & represents the bitwise-AND operator.
  

 Example 1:

 Input: [2,1,3]
 Output: 12
 Explanation: We could choose the following i, j, k triples:
 (i=0, j=0, k=1) : 2 & 2 & 1
 (i=0, j=1, k=0) : 2 & 1 & 2
 (i=0, j=1, k=1) : 2 & 1 & 1
 (i=0, j=1, k=2) : 2 & 1 & 3
 (i=0, j=2, k=1) : 2 & 3 & 1
 (i=1, j=0, k=0) : 1 & 2 & 2
 (i=1, j=0, k=1) : 1 & 2 & 1
 (i=1, j=0, k=2) : 1 & 2 & 3
 (i=1, j=1, k=0) : 1 & 1 & 2
 (i=1, j=2, k=0) : 1 & 3 & 2
 (i=2, j=0, k=1) : 3 & 2 & 1
 (i=2, j=1, k=0) : 3 & 1 & 2
  

 Note:

 1 <= A.length <= 1000
 0 <= A[i] < 2^16
 
 */

#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class CountTriplets {

    

public:


    int doit_hashtable(vector<int>& A) {
        
        int ans = 0;
        unordered_map<int, int> buff;
        
        for (auto a: A)
            for (auto b: A)
                buff[a&b]++;
        
        for (auto a: A) {
            
            int bits = (~a) & 0xffff;
            
            for (int subset = bits; subset > 0; subset = (subset-1) & bits) {
                if (buff.count(subset) > 0) ans += buff[subset];
            }
            
            ans += buff[0];
        }
        
        return ans;
    }
    
    
    int doit3(vector<int>&& A) {
        int ans = 0;
        unordered_map<int,int> hash;
        
        for (auto x: A)
            for(auto y: A) {
                hash[x & y]++;
            }
        
        for (auto c : hash)
            for (auto z: A) {
                if ((c.first & z) == 0)
                    ans += c.second;
            }
        
        return ans;
    }
    
    int doit2(vector<int>&& A) {
        int length = A.size();
        int has[1<<16];
        memset(has,0,sizeof has);
        
         for (int i=0;i<length;i++) {
            for(int j=0;j < length; j++) {
                int idx = A[i] & A[j];
                has[A[i] & A[j]] ++;
            }
        }
         
         int ans =0;
         for(int i=0;i<length;i++) {
             for(int j=0;j<(1<<16);j++) {
                 if((A[i] & j) ==0 ) {
                      ans+= has[j];
                 }
             }
         }
         return ans ;
    }
    

    // key thinking: question is easy by itself
    // but the iteration technique is rare to see!
    // (iterate over subset of bit combos!)
    int doit_hashtable(vector<int>&& A) {
        // note A[i] < 2^16
        int n = A.size();
        vector<int> count(1 << 16, 0);
        
        for(auto a : A)
            for(auto b : A)
                count[a&b]++;
        
        int res = 0;
        for(int i = 0; i < n; i ++){
            int bits = (~A[i]) & 0xffff; // mask of 0-bits of A[i], A[i] is 00011000100, then ~A[i] 11100111011, any bits is subbits of those 1s will be good candidatas.
            // iterate k until it reaches 0,
            // interesting technique is, we & k with bits!
            // since any 1-bit outside of bits will result in non-zero and result!
            // this is essentially iterate over all combinations of 0-bits of A[i]!!
            for(int k = bits; k ; k = (k-1) & bits) // list each k has more 0s in bits, util 0
                res += count[k];
            res += count[0];
        }
    
        return res;
    }
};