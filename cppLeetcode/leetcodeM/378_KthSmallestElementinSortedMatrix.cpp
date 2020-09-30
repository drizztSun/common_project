#include <stdio.h>
#include <vector>
#include <queue>

using std::vector;
using std::priority_queue;


class KthSmallest {
public:
    int doit_heap(vector<vector<int>>& matrix, int k) {

        std::priority_queue<std::pair<int, std::pair<int, int>>> heap;
        
        auto push = [&](int i, int j) {
            if (i < matrix.size() && j < matrix[0].size())
                heap.push({-matrix[i][j], {i, j}});
        };
        
        push(0, 0);
        int ans = 0;
        while (!heap.empty() && k > 0) {
            
            auto item = heap.top();
            auto c = item.second;
            ans = item.first;
            int x = c.first, y = c.second;
            heap.pop();
            k--;
            
            push(x, y+1);
            
            if (y==0)
                push(x+1, y);
        }
        
        return -ans;
    }
    
    int doit_binary_search(vector<vector<int>>& matrix, int k) {
     
        int size = matrix.size(), l = matrix[0][0], r = matrix[size-1][size-1];
        
        while(l < r) {
           int smaller = 0, m = l+((r-l)>>1);
            
           for(int i = 0; i < size; ++i) {
               smaller += upper_bound(matrix[i].begin(), matrix[i].end(), m)-matrix[i].begin();
           }
            
           smaller < k ? l = m+1 : r = m;
       
         }
         return r;
    }
};
