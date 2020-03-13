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
using std::vector;

#include <unordered_set>
using std::unordered_set;

#include <unordered_map>
using std::unordered_map;

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

public:
    
    int doit(vector<int>&& A) {
        
        vector<int> ps = get_primes(*std::max_element(A.begin(), A.end()));
        vector<vector<int>> B;
        for (auto x : A) {
            
            vector<int> buf;
            for (auto p : ps) {
                if (x % p == 0) {
                    while (x % p == 0) {
                        x /= p;
                    }
                    buf.push_back(p);
                }
            }
            if (x > 1 && buf.empty())
                buf.push_back(x);
            B.push_back(buf);
        }
        
        unordered_set<int> primes;
        for (auto& c : B) {
            for (auto s : c) {
                primes.insert(s);
            }
        }

        
        
        return 0;
    }
    
    
    int doit1(vector<int>&& A) {
        
        auto is_edge = [](int a, int b) -> bool{
            int base = std::min(a, b);
            for (int i = 2; i < std::sqrt(base) + 1; i++) {
                if (a % i == 0 && b % i == 0)
                    return true;
            }
            return std::max(a, b) % std::min(a, b) == 0;
        };
        
        vector<vector<int>> graph(A.size(), vector<int>(A.size(), 0));
        
        for (int i = 0; i < A.size(); i++) {
            
            for (int j = i + 1; j < A.size(); j++) {
                
                if (is_edge(A[i], A[j])) {
                    graph[i][j] = 1;
                    graph[j][i] = 1;
                }
            }
        }
        
        auto search = [&graph](int i) -> int{
            
            return 0;
        };
        
        
        
        return 0;
    }
};


// normal solution

class dsu{

public:
    vector<int> arr;
    dsu(int n):arr(n){
        for(int i=0;i<n;i++){
            arr[i]=i;
        }
    }

    void merge(int a, int b){
        arr[find(arr[a])]=arr[find(arr[b])];
    }

    int find(int x){
        if(arr[x]!=x){
            arr[x]=find(arr[x]);
        }
        return arr[x];
    }
};

class LargestComponentSize1 {

public:
    int doit(vector<int>& A) {
        int n=*max_element(A.begin(),A.end());
        dsu DSU(n+1);
        for(auto x:A){
            int temp=sqrt(x);
            for(int k=2;k<=temp;k++){
                if(x%k==0){
                    DSU.merge(x,k);
                    DSU.merge(x,x/k);
                }
            }
        }
        unordered_map<int,int> m;
        int res=1;
        for(auto v:A){
            m[DSU.find(v)]+=1;
            res = std::max(res,m[DSU.find(v)]);
        }
        return res;
    }
};

// normal solution 2

class DSU1{
    
    vector<int> parent_;
    
public:
    DSU1(int n ){
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


class LargestComponentSizeII {
public:
    int largestComponentSize(vector<int>& A) {
        
        int n = *max_element(A.begin(), A.end());
        DSU1 dsu(n+1);
        
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


void test_952_largest_component_size_by_common_factor() {
    
    auto res1 = LargestComponentSize().doit(vector<int>{4,6,15,35});  // 4
    
    auto res2 = LargestComponentSize().doit(vector<int>{20,50,9,63});  // 2
    
    auto res3 = LargestComponentSize().doit(vector<int>{2,3,6,7,4,12,21,39}); // 8

    return;
}
