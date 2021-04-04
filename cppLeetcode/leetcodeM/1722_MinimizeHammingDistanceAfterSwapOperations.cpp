/*
1722. Minimize Hamming Distance After Swap Operations



You are given two integer arrays, source and target, both of length n. 

You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. 

Note that you can swap elements at a specific pair of indices multiple times and in any order.

The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. 

Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).

Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.

 

Example 1:

Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
Output: 1
Explanation: source can be transformed the following way:
- Swap indices 0 and 1: source = [2,1,3,4]
- Swap indices 2 and 3: source = [2,1,4,3]
The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
Example 2:

Input: source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
Output: 2
Explanation: There are no allowed swaps.
The Hamming distance of source and target is 2 as they differ in 2 positions: index 1 and index 2.
Example 3:

Input: source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
Output: 0
 

Constraints:

n == source.length == target.length

1 <= n <= 10^5
1 <= source[i], target[i] <= 10^5
0 <= allowedSwaps.length <= 10^5

allowedSwaps[i].length == 2
0 <= ai, bi <= n - 1
ai != bi


*/
#include <vector>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <set>

using std::multiset;
using std::unordered_map;
using std::vector;

class MinimumHammingDistance {

public:

    /*
        1722.Minimize-Hamming-Distance-After-Swap-Operations
        我们将所有互相连接的allowedSwap的位置都union起来，这些位置上的数字其实都是可以任意重新排列的。我们只需要将source里这些位置上的元素集合，与target里这些位置上的元素集合进行比较，数一下有多少不同元素，就是Hamming distances.
    */
    vector<int>Father;
    int FindFather(int x)
    {
        if (Father[x]!=x)
            Father[x] = FindFather(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y) Father[y] = x;
        else Father[x] = y;
    }    

public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) 
    {
        int n = source.size();
        Father.resize(n);
        for (int i=0; i<n; i++)
            Father[i] = i;
        
        for (auto pair: allowedSwaps)
        {
            int a = pair[0];
            int b = pair[1];
            if (FindFather(a)!=FindFather(b))
                Union(a,b);
        }
        
        unordered_map<int,vector<int>>Map;
        for (int i=0; i<n; i++)
            Map[FindFather(i)].push_back(i);
        
        int count = 0;
        for (auto x: Map)
        {
            multiset<int>Set;
            for (auto i: x.second)
                Set.insert(source[i]);
            for (auto i: x.second)
            {
                if (Set.find(target[i])!=Set.end())
                    Set.erase(Set.lower_bound(target[i]));
            }
            count += Set.size();
        }
        return count;                
    }

    
    int doit_disjoint(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        
        int n = source.size();
        vector<int> father(n);
        std::iota(begin(father), end(father), 0);

        auto find = [&](int id) {
            while (id != father[id]) {
                father[id] = father[father[id]];
                id = father[id];
            }
            return id;
        };

        auto merge = [&](int x, int y) {
            int px = find(x), py = find(y);
            if (px == py)
                return;

            if (px < py)
                father[py] = px;
            else
                father[px] = py;
        };

        for (auto& c : allowedSwaps) {
            merge(c[0], c[1]);
        }

        unordered_map<int, vector<int>> groups;
        for (int i = 0; i < n; i++) {
            groups[find(i)].push_back(i);
        }

        int ans = 0;
        for (auto x: groups) {

            multiset<int> group;
            for (auto c : x.second)
                group.insert(source[c]);

            for (auto i : x.second) {
                if (group.find(target[i]) != group.end()) {
                    // only remove one, not all
                    group.erase(group.lower_bound(target[i]));
                }
            }
            
            ans += group.size();
        }

        return ans;
    }
};