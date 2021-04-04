/*

 # 952. Largest Component Size by Common Factor

 # Given a non-empty array of unique positive integers A, consider the following graph:

 # There are A.length nodes, labelled A[0] to A[A.length - 1];
 # There is an edge between A[i] and A[j] if and only if A[i] and A[j] share a common factor greater than 1.
 # Return the size of the largest connected component in the graph.


 # Example 1:

 # Input: [4,6,15,35]
 # Output: 4

 # Example 2:

 # Input: [20,50,9,63]
 # Output: 2

 # Example 3:

 # Input: [2,3,6,7,4,12,21,39]
 # Output: 8

 */

#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using std::vector;
using std::unordered_set;
using std::unordered_map;



class UnionFind {

    vector<int> _parent;
    vector<int> _size;
public:
    UnionFind(int n) {
        _parent.resize(n);
        for (int i = 0; i < _parent.size(); i++)
            _parent[i] = i;
        
        _size.resize(n);
        for (size_t i = 0; i < _size.size(); i++)
            _size[i] = 1;
    }
    
    int Find(int n) {
        while (_parent[n] != n) {
            _parent[n] = _parent[_parent[n]];
            n = _parent[n];
        }
        return n;
    }
    
    void Union(int a, int b) {
        int pa = Find(a), pb = Find(b);
        if (pa == pb)
            return;
            
        if (_size[a] < _size[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        
        _parent[a] = b;
        _size[a] += _size[b];
    }
};

class LargestComponentSize {

    /*
        952.Largest-Component-Size-by-Common-Factor

    此题一眼就能看出是Union Find的解法．任意两个数，只要有质因数相同，就能建立起联系．所以我们将所有的数a,都分解成一系列质因数Pi，将a和Pi都Union起来．最后看所有的数字经过聚类之后，最大的群的数量．

    第一个版本，我们可以将100000以内的所有的质数Pi都找出来，挨个查看是否是a的因数．这比直接求a的所有质因数要快．

            vector<int>primes = makePrimes(100000);
            for (auto p:primes) Root[p] = p;
            for (auto a:A) Root[a] = a;
            
            for (auto a:A)
            {
                for (int p:primes)
                {
                    if (a%p==0 && findRoot(a)!=findRoot(p))
                        Union(a,p);                            
                    if (p>a/2) break;
                }
            }
            
            unordered_map<int,int>Groups;
            for (auto a:A)              
                Groups[findRoot(a)]+=1;
                
            int result = 0;
            for (auto x:Groups)
                result = max(result,x.second);
            return result;
    这个解法能够AC，但是比其他答案要慢得多．原因是100000以内的质数筛检非常费事．怎么改进呢？

    第二个版本，我们只需要求出sqrt(100000)以内的所有质数Pi，这样预处理的规模就小了很多．但是如果继续按照上面的算法，如何保证得到a的所有质因数Pi并建立联系呢？
    其实我们只要将a不断除以它在sqrt(100000)以内的所有质因数，如果仍然大于1，那么剩下的必然是它唯一的一个大于sqrt(100000)的质因数．因为任何数不可能含有两个大于sqrt(100000)的质因数的．

            vector<int>primes = makePrimes(sqrt(100000));        
            for (auto p:primes) Root[p] = p;
            for (auto a:A) Root[a] = a;
            
            for (auto a:A)
            {
                int x = a;
                for (int p:primes)
                {
                    if (x%p==0)
                    {
                        if (findRoot(p)!=findRoot(a))
                            Union(p,a);
                        while (x%p==0) x = x/p;                    
                    }                
                    if (p>x) break;
                }
                
                if (x>1)
                {
                    if (Root.find(x)==Root.end()) Root[x] = x;
                    Union(x,a);
                }
            }
            
            unordered_map<int,int>Groups;
            for (auto a:A)      
                Groups[findRoot(a)]+=1;
                
            int result = 0;
            for (auto x:Groups)
                result = max(result,x.second);
            return result;
    */

    unordered_map<int,int>Root;

public:

    int largestComponentSize_disjoint(vector<int>& A) 
    {            
        vector<int>primes = makePrimes(sqrt(100000));        
        for (auto p:primes) Root[p] = p;
        for (auto a:A) Root[a] = a;
        
        for (auto a:A)
        {
            int x = a;
            for (int p:primes)
            {
                if (x%p==0)
                {
                    if (findRoot(p)!=findRoot(a))
                        Union(p,a);
                    while (x%p==0) x = x/p;                    
                }                
                if (p>x) break;
            }            
            if (x>1)
            {
                if (Root.find(x)==Root.end()) Root[x] = x;
                Union(x,a);
            }
        }
        
        unordered_map<int,int>Groups;
        for (auto a:A)      
            Groups[findRoot(a)]+=1;
            
        int result = 0;
        for (auto x:Groups)
            result = std::max(result,x.second);
        
        return result;
    }
    
    vector<int>makePrimes(int N)
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
    
    int findRoot(int x)
    {
        if (x!=Root[x])
            Root[x] = findRoot(Root[x]);
        return Root[x];
    }
    
    void Union(int x, int y)
    {
        x = Root[x];
        y = Root[y];
        if (x<y) Root[y] = x;
        else Root[x] = y;
    }

public:

    vector<int> get_primes(int n) {
        size_t scope = std::sqrt(n) + 1;
        vector<bool> isprimes(scope, true);
        isprimes[0] = false, isprimes[1] = true;
        vector<int> ans;

        for(int i = 0; i < isprimes.size(); i++) {
            if (isprimes[i])
                for(int s = i * i; s <  isprimes.size(); s += i)
                    isprimes[s] = false;
            if (!isprimes[i])
                ans.push_back(i);
        }

        return ans;
    }
    
    struct DSU{
        
        vector<int> parent_;

        DSU(int n ){
            parent_.resize(n);
            for (int i = 0; i < parent_.size(); i++) 
                parent_[i] = i;
        }    
        
        int Find(int n) {
            while (parent_[n] != n){
                parent_[n] = parent_[parent_[n]];
                n = parent_[n];    
            }
            return parent_[n];
        }
        
        void Union(int a, int b) {
            int pa = Find(a), pb = Find(b);
            parent_[pa] = pb; 
        }
    };

public:

    int doit_disjoint(vector<int>& A) {
        
        int n = *max_element(A.begin(), A.end());
        DSU dsu(n+1);
        
        for (auto x: A) {
            for (int i = 2; i <= std::sqrt(x); i++) {
                if (x % i == 0) {
                    dsu.Union(x, i);
                    dsu.Union(x, x / i);
                }
            }
        }
        
        int res = 1;
        unordered_map<int, int> buf;
        for (auto c : A) {
            buf[dsu.Find(c)] += 1;
            res = std::max(res, buf[dsu.Find(c)]);
        }
        return res;
    }
};

// fatest solution
class LargestComponentSizeI {
    int find(int root[], int x) {
        if(root[x]!=x) {
            root[x] = find(root, root[x]);
        }
        return root[x];
    }
    
    vector<int> primes;
    
    vector<int> get_factors(int num, bool prime[]) {
        vector<int> factors;
        int num_copy = num;
        for(int j=0; j<primes.size() && primes[j]*primes[j]<=num_copy; j++) {
            int d = primes[j];
            if(num%d!=0) {
                continue;
            }
            while(num%d==0) {
                num/=d;
            }
            factors.push_back(d);
            if(prime[num]) {
                factors.push_back(num);
                return factors;
            }
        }
        return factors;
    }
    
public:
    int largestComponentSize(vector<int>& A) {
        int maxN = *max_element(A.begin(), A.end());
        bool prime[maxN+1];
        memset(prime, 1, sizeof prime);
        prime[1] = 0;
        for(int j=4; j<=maxN; j+=2) {
            prime[j] = 0;
        }
        for(int i=3; i*i<=maxN; i+=2) {
            if(prime[i]==0)
                continue;
            for(int j=i*i; j<=maxN; j+=i) {
                prime[j] = 0;
            }
        }
        primes.push_back(2);
        for(int i=3; i*i<=maxN; i+=2)
            if(prime[i]) primes.push_back(i);
        int root[maxN+1];
        int sz[maxN+1];
        memset(sz, 0, sizeof sz);
        for(int i=1; i<=maxN; i++)
            root[i] = i;
        int max_sz = 0;
        for(auto num: A) {
            if(num==1)
                continue;
            if(prime[num]) {
                int the_root = find(root, num);
                sz[the_root]++;
                if(sz[the_root]>max_sz)
                    max_sz = sz[the_root];
                continue;
            }
            int the_root = INT_MAX;
            vector<int> factors = get_factors(num, prime);
            int fact1 = factors.front();
            for(auto fact2: factors) {
                int r1 = find(root, fact1), r2 = find(root, fact2);
                the_root = std::min(the_root, std::min(r1,r2));
                if(r1==r2)
                    continue;
                if(r1>r2)
                    std::swap(r1, r2);
                root[r2] = r1;
                sz[r1] += sz[r2];
            }
            sz[the_root]++;
            if(sz[the_root]>max_sz)
                max_sz = sz[the_root];
        }
        return max_sz;
    }
};