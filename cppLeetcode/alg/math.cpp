#include <vector>

using std::vector;

namespace math {

    vector<int> makePrimes(int N)
    {
        vector<bool>prime(N,true);
        vector<int>results;
        for (long i = 2; i < N; i++) 
        { 
            if (prime[i]) 
            { 
                results.push_back(i);
                for (long j = i*i; j < N; j += i)  
                    prime[j] = false;
            } 
        }
        return results;
    }


    bool isPrime(int k)
    {
        if (k==1) return false;
        if (k%2==0) return k==2;
        for (int i=3; i*i<=k; i+=2)
        {
            if (k%i==0) return false;
        }
        return true;
    }
}

