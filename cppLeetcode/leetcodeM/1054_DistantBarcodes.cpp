/*
1054. Distant Barcodes


In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].

Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, and it is guaranteed an answer exists.

 

Example 1:

Input: barcodes = [1,1,1,2,2,2]
Output: [2,1,2,1,2,1]
Example 2:

Input: barcodes = [1,1,1,1,2,2,3,3]
Output: [1,3,1,3,1,2,1,2]
 

Constraints:

1 <= barcodes.length <= 10000
1 <= barcodes[i] <= 10000

*/
#include <vector>
#include <unordered_map>
#include <queue>

using std::priority_queue;
using std::unordered_map;
using std::vector;


class RearrangeBarcodes {

    /*
            054.Distant-Barcodes
            解法1：
            将所有元素按照频次从大到小排列（所以相同的元素都会排在一起）。然后将这些元素先顺次填满reesult所有index为奇数的位置，然后在顺次填满result所有index为偶数的位置。这样就能尽可能地保证相同的元素不会排在一起了。

            解法2：
            套路题：将所有数字按照频次放在一个优先队列里。每次从队列首取出两种不同的数字。频次减一之后再放回。

            与本题类似的题目还有：621.Task Scheduler, 767.Reorganize String, 358. Rearrange String k Distance Apart
    */
    vector<int> doit_(vector<int>& barcodes) 
    {
        unordered_map<int,int>Map;
        for (auto x:barcodes)
            Map[x]+=1;
        
        vector<std::pair<int,int>> p;
        for (auto x: barcodes)
            p.push_back({Map[x], x});

        sort(p.begin(), p.end());
        reverse(p.begin(), p.end());

        int n = barcodes.size();
        vector<int>ret(n);
        int i = 0;
        for (auto x: p)
        {
            ret[i] = x.second;
            i+=2;
            if (i>=n) i = 1;
        }
        return ret;            
    }

    vector<int> doit_heap_1(vector<int>& barcodes) 
    {
        unordered_map<int,int>Map;
        for (auto x:barcodes)
            Map[x]+=1;

        priority_queue<std::pair<int,int>>pq;
        for (auto x: Map)
            pq.push({x.second, x.first});

        vector<int>ret;
        while (!pq.empty())
        {
            if (pq.size()<2 && pq.top().first>1)
                return {};
                        
            vector<std::pair<int,int>>temp;
            int len = pq.size();
            for (int i=0; i < min(2, len); i++)
            {
                ret.push_back(pq.top().second);                
                if (pq.top().first!=1)
                    temp.push_back(pq.top());
                pq.pop();
            }

            for (auto x: temp)
            {
                x.first -= 1;
                pq.push(x);
            }
                
        }

        return ret;
    }

public:

    vector<int> doit_heap(vector<int>& barcodes) {
        
        unordered_map<int, int> cnt;
        for (auto c : barcodes) cnt[c]++;
        
        priority_queue<std::pair<int, int>> pq;
        for (auto it: cnt)
            pq.push({it.second, it.first});
        
        vector<int> ans;
        while (!pq.empty()) {
            
            auto it1 = pq.top(); pq.pop();
            ans.push_back(it1.second);
            
            if (pq.empty()) return ans;
            
            auto it2 = pq.top(); pq.pop();
            ans.push_back(it2.second);
            
            if (it1.first > 1) 
                pq.push({it1.first - 1, it1.second});
            
            if (it2.first > 1)
                pq.push({it2.first - 1, it2.second});
        }
        
        return ans;
    }
};