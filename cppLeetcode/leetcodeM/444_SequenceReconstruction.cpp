/*
444. Sequence Reconstruction

Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs. 
The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. 


Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it). 
Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.

 

Example 1:

Input: org = [1,2,3], seqs = [[1,2],[1,3]]
Output: false
Explanation: [1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
Example 2:

Input: org = [1,2,3], seqs = [[1,2]]
Output: false
Explanation: The reconstructed sequence can only be [1,2].
Example 3:

Input: org = [1,2,3], seqs = [[1,2],[1,3],[2,3]]
Output: true
Explanation: The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
Example 4:

Input: org = [4,1,5,2,6,3], seqs = [[5,2,6,3],[4,1,5,2]]
Output: true
 

Constraints:

1 <= n <= 10^4
org is a permutation of {1,2,...,n}.
1 <= segs[i].length <= 10^5
seqs[i][j] fits in a 32-bit signed integer.

*/
#include <vector>
#include <queue>

using std::queue;
using std::vector;

class SequenceReconstruction {

    /*
                444.Sequence-Reconstruction
        本题巧妙地应用了拓扑排序的原理。我们根据seqs可以得到每个节点的入度和（有向的）邻接节点。我们每个回合里，统计当前入度为零的节点，这样的节点必须只有一个。
        如果有若干个，那么他们彼此之间的先后顺序必然是不确定的。此外，这唯一的入度为零的节点（整个图的起点），也必须是org里当前的首元素。如果不满足这两个条件，我们就返回false。

        在满足这两个条件之后，我们就弹出org的首元素，考察它所邻接的节点及其更新后的入度（它们的入度要减一），继续寻找其中入度为零的节点。不断重复直至遍历完所有的拓扑关系。

        当遍历完所有的拓扑关系后，我们要求也恰好遍历完org里面所有的节点。否则返回false。

        此外，seqs里面所有的节点必须是在[1,n]的范围里。
    */
    bool sequenceReconstruction_topsort(vector<int>& org, vector<vector<int>>& seqs) 
    {
        if (seqs.size() == 0)
            return false;
        int n = org.size();
        vector<int>indegree(n+1);
        vector<vector<int>>out(n+1);
        
        for (auto seq: seqs)
            for (int i: seq)
                if (i>n || i<1) return false;
        
        for (auto seq: seqs)
        {            
            for (int i=1; i<seq.size(); i++)
            {                
                out[seq[i-1]].push_back(seq[i]);
                indegree[seq[i]]++;
            }                
        }
        
        queue<int>q;
        for (int i=1; i<=n; i++)
        {
            if (indegree[i]==0)
                q.push(i);
        }
        
        int i = 0;
        while (!q.empty())
        {
            if (q.size()>1)
                return false;
            
            int x = q.front();            
            q.pop();
            if (x!=org[i]) return false;
            i++;
            
            for (int next: out[x])
            {
                indegree[next]--;
                if (indegree[next]==0)
                    q.push(next);
            }
        }
        
        if (i!=org.size()) return false;
        
        return true;        
    }

public:
    
    bool doit_topsort(vector<int>& org, vector<vector<int>>& seqs) {

        int n = org.size();
        vector<int> degree(n+1, 0);
        vector<vector<int>> next(n+1);

        for (auto& c: seqs) {
            
            for (int i = 1; i < c.size(); i++) {
                degree[c[i]]++;
                next[c[i-1]].push_back(c[i]);
            }
        }

        queue<int> qu;
        for(int i = 1; i <= n; i++)
            if (degree[i] == 0) qu.push(i);

        int i = 0;
        while (!qu.empty()) {

            if (qu.size() > 1) return false;

            int cur = qu.front(); qu.pop();

            if (cur != org[i]) return false;
            i++;

            for (auto child: next[cur]) {
                degree[child]--;
                if (degree[child] == 0)
                    qu.push(child);
            }
        }

        return i == org.size();
    }
};