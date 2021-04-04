#include <vector>

using std::vector;

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


