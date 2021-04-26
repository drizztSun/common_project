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
#include <set>

using std::set;
using std::multiset;
using std::vector;
using std::priority_queue;
using std::pair;

class NthSuperUglyNumber {
    
public:

    int doit_array_best(int n, vector<int>& A) {
        
        int k = A.size(), t = 1;
        vector<int> u(n), d(k), v(k);
        
        // d is the d[i] number of u, which ith key in A
        // v is the current value, base on u[d[i]] multiplied by A[i]
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


    int doit_heap_(int n, vector<int>& primes) {
        
        vector<int> ans{1};
        // couse the vector<int> so performance is so low.
        priority_queue<vector<int>, vector<vector<int>>, std::greater<>> pq;
        
        for (auto c: primes)
            pq.push({c, c, 1});
        
        while (ans.size() < n) {
            
            auto it = pq.top(); pq.pop();
            
            int num = it[0];
            
            ans.push_back(num);
            
            pq.push({ans[it[2]] * it[1], it[1], it[2]+1});
            
            while (!pq.empty() && pq.top()[0] == num) {
                it = pq.top(); pq.pop();
                pq.push({ans[it[2]] * it[1], it[1], it[2]+1});
            }
        }
        
        return ans.back();
    }

    int doit_heap(int n, vector<int>& primes) {
        
        vector<int> uglyNums{1};
        priority_queue<pair<int, std::pair<int, int>>> heap;

        for (auto c: primes)
            heap.push({-c, {c, 1}});
        
        for (auto i = 1; i < n; i++) {
            
            auto cur = heap.top();
            // bigger number in PQ, base number in primes, index of result buff.
            auto num = cur.first, base = cur.second.first, index = cur.second.second;
            heap.pop();
            
            uglyNums.push_back(-num);
            heap.push({-uglyNums[index] * base, {base, index+1}});
            
            while (!heap.empty() && heap.top().first == num) {
                auto cur = heap.top();
                auto num = cur.first, base = cur.second.first, index = cur.second.second;
                heap.pop();
                heap.push({-uglyNums[index] * base, {base, index+1}});
            }
        }
        
        return uglyNums.back();
    }

    int doit_dp(int n, vector<int>& primes) {
        
        vector<int> cpr(primes.begin(),primes.end());
        vector<int> ind(primes.size(),0);
        vector<long long> dp(n+1);
        dp[0]=1;

        for(int i=1;i<n;i++){
            long long int m=1e18;
            for(auto p:primes){
                m = std::min(m,(long long)p);
            }
            dp[i]=m;
            for(int j=0;j<primes.size();j++){
                if(m==primes[j]){
                    ind[j]++;
                    primes[j]=dp[ind[j]]*cpr[j];
                }
            }
        }
        return dp[n-1];
    }


    /*
        313.Super-Ugly-Number
        本题本质就是find the n-th largest element from k sorted lists. 从1开始，每次从优先队列里弹出当前最小的数，然后分别乘以k个质数再放入队列中。直至弹出n个数为止。

        注意到装入队列的元素可能会是重复的。所以此处用set更方便。
    */
    int doit_heap(int n, vector<int>& primes) 
    {
        set<long> Set={1};
        int count=0;
        long x;

        while (count<n)
        {
            x = *Set.begin();
            Set.erase(x);
            for (int i=0; i<primes.size(); i++)
            {
                if (x*primes[i]<INT_MAX)
                    Set.insert(x*primes[i]);
                else
                    break;
            }
                
            count++;
        }
        return x;
    }
};

