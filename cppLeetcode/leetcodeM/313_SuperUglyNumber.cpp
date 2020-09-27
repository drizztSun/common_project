/*
 313. Super Ugly Number
 
 Write a program to find the nth super ugly number.

 Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

 Example:

 Input: n = 12, primes = [2,7,13,19]
 Output: 32
 Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
              super ugly numbers given primes = [2,7,13,19] of size 4.
 Note:

 1 is a super ugly number for any given primes.
 The given numbers in primes are in ascending order.
 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
 The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
 */

#include <stdio.h>
#include <queue>
#include <vector>

using std::vector;
using std::priority_queue;
using std::pair;

class NthSuperUglyNumber {
    
public:
    
    int doit_heap(int n, vector<int>& primes) {
        
        vector<int> uglyNums{1};
        priority_queue<pair<int, pair<int, int>>> heap;
        for (auto c : primes) {
            heap.push(std::make_pair(-c, std::make_pair(c, 1)));
        }
        
        for (auto i = 1; i < n; i++) {
            
            auto cur = heap.top();
            auto num = cur.first, base = cur.second.first, index = cur.second.second;
            heap.pop();
            
            uglyNums.push_back(-num);
            heap.push(std::make_pair(-uglyNums[index] * base, std::make_pair(base, index+1)));
            
            while (!heap.empty() && heap.top().first == num) {
                auto cur = heap.top();
                auto num = cur.first, base = cur.second.first, index = cur.second.second;
                heap.pop();
                heap.push(std::make_pair(-uglyNums[index] * base, std::make_pair(base, index+1)));
            }
        }
        
        return uglyNums.back();
    }
    
    int doit_array(int n, vector<int>& A) {
        
        int k = A.size(), t = 1;
        int u[n], d[k], v[k];
        
        for(int i = 0; i < k; ++i)
            d[i] = 0, v[i] = A[i];
        
        for (int i = 0; i < n; ++i)
        {
            u[i] = t;
            t = INT_MAX;
            for (int j = 0; j < k; ++j)
            {
                if (v[j] == u[i])
                    v[j] = u[++d[j]] * A[j];
                
                if(v[j] < t)
                    t = v[j];
            }
        }
        return u[n - 1];
    }
    
};

