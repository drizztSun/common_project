/*
1101. The Earliest Moment When Everyone Become Friends


In a social group, there are N people, with unique integer ids from 0 to N-1.

We have a list of logs, where each logs[i] = [timestamp, id_A, id_B] contains a non-negative integer timestamp, and the ids of two different people.

Each log represents the time in which two different people became friends.  Friendship is symmetric: if A is friends with B, then B is friends with A.

Let's say that person A is acquainted with person B if A is friends with B, or A is a friend of someone acquainted with B.

Return the earliest time for which every person became acquainted with every other person. Return -1 if there is no such earliest time.

 

Example 1:

Input: logs = [[20190101,0,1],[20190104,3,4],[20190107,2,3],[20190211,1,5],[20190224,2,4],[20190301,0,3],[20190312,1,2],[20190322,4,5]], N = 6
Output: 20190301
Explanation: 
The first event occurs at timestamp = 20190101 and after 0 and 1 become friends we have the following friendship groups [0,1], [2], [3], [4], [5].
The second event occurs at timestamp = 20190104 and after 3 and 4 become friends we have the following friendship groups [0,1], [2], [3,4], [5].
The third event occurs at timestamp = 20190107 and after 2 and 3 become friends we have the following friendship groups [0,1], [2,3,4], [5].
The fourth event occurs at timestamp = 20190211 and after 1 and 5 become friends we have the following friendship groups [0,1,5], [2,3,4].
The fifth event occurs at timestamp = 20190224 and as 2 and 4 are already friend anything happens.
The sixth event occurs at timestamp = 20190301 and after 0 and 3 become friends we have that all become friends.
 

Note:

2 <= N <= 100
1 <= logs.length <= 10^4
0 <= logs[i][0] <= 10^9
0 <= logs[i][1], logs[i][2] <= N - 1
It's guaranteed that all timestamps in logs[i][0] are different.
logs are not necessarily ordered by some criteria.
logs[i][1] != logs[i][2]

*/

#include <vector>
#include <algorithm>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class EarliestAcq {

    /*
        1101.The-Earliest-Moment-When-Everyone-Become-Friends
        本题考察的是常规的Union Find的操作．但是一个比较有意思的知识点是，如果快速判定我们已经聚了几个类呢？

        方法是，如果一开始有Ｎ个元素，那就是Ｎ类．每两个不属于同一个类的元素进行union操作，就会少一个类．我们不断聚类的过程中，如果这个类计数器变为了１，那么就说明所有的元素都已经聚为了一类了．这个和 305. Number of Islands II 非常相似．
    */
    unordered_map<int,int>Father;

    int earliestAcq(vector<vector<int>>& logs, int N) 
    {
        sort(logs.begin(),logs.end());
        for (int i=0; i<N; i++)
            Father[i] = i;
        int groups = N;
            
        for (auto log:logs)
        {
            int A = log[1];
            int B = log[2];
            if (findFather(A)!=findFather(B))
            {
                Union(A,B);
                groups--;
            }
            if (groups==1)
                return log[0];
        }
        return -1;
        
    }
    
    int findFather(int x)
    {
        if (Father[x]!=x)
            Father[x] = findFather(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int  y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y) Father[y]=x;
        else Father[x] = y;
    }

public:
    
    int doit_disjoint(vector<vector<int>>& logs, int N) {
        
        std::sort(begin(logs), end(logs));
        
        vector<int> parent(N, -1);
        vector<int> size(N, 1);
        
        for (int i = 0; i < N; i++)
            parent[i] = i;
        
        auto find = [&](int n) {
            
            while (n != parent[n]) {
                parent[n] = parent[parent[n]];
                n = parent[n];
            }
            return n;
        };
        
        auto merge = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            
            if (pa == pb) return;
            
            if (size[pa] > size[pb]) {
                parent[pb] = pa;
                size[pa] += size[pb];
            } else{
                parent[pa] = pb;
                size[pb] += size[pa];
            }
        };
            
            
        for (const auto& c : logs) {
            
            merge(c[1], c[2]);
            
            if (size[find(c[1])] == N) return c[0];
        }
        
        return -1;
    }
};