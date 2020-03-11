/*
 
 
 # 974. Subarray Sums Divisible by K

 # Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.


 # Example 1:

 # Input: A = [4,5,0,-2,-3,1], K = 5
 # Output: 7
 # Explanation: There are 7 subarrays with a sum divisible by K = 5:
 # [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]


 # Note:

 # 1 <= A.length <= 30000
 # -10000 <= A[i] <= 10000
 # 2 <= K <= 10000
 
 
 */

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

class SubarraysDivByK {
    
public:
    int doit(vector<int>&& A, int K) {

        unordered_map<int, int> buf;
        int total = 0;
        
        for (auto c : A) {
            total += c;
            int r = total % K;
            if (r < 0) {
                r += K;
            }
            if (buf.count(r) == 0)
                buf[r] = 0;
            buf[r] += 1;
        }
        
        int cnt = 0;
        for (auto& c : buf) {
            if (c.first == 0)
                cnt += c.second * (c.second + 1) / 2;
            else
                cnt += c.second * (c.second - 1) / 2;
        }
        
        return cnt;
    }
    
    int doit2(vector<int>&& A, int K) {
        vector<int> buckets(K);
        buckets[0]=1;
        int sum=0,cnt=0;
        
        for(int i = 0; i < A.size(); ++i){
            sum += A[i];
            if(sum < 0)
                sum = K-(-sum)%K;
            else
                sum %= K;
            if(sum == K)
                sum = 0;
            cnt += buckets[sum];
            buckets[sum]++;
        }
        return cnt;
    }
};

void test_974_subarray_sums_division_by_k() {
    
    auto res1 = SubarraysDivByK().doit(vector<int>{4,5,0,-2,-3,1}, 5);
    
    auto res2 = SubarraysDivByK().doit(vector<int>{2,-2,2,-4}, 6);
    
    auto res3 = SubarraysDivByK().doit(vector<int>{-1, 2, 9}, 2);
    
    return;
}
