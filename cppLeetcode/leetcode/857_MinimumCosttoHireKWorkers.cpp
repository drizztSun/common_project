/*
 857. Minimum Cost to Hire K Workers
 

 There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].

 Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, we must pay them according to the following rules:

 Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
 Every worker in the paid group must be paid at least their minimum wage expectation.
 Return the least amount of money needed to form a paid group satisfying the above conditions.

  

 Example 1:

 Input: quality = [10,20,5], wage = [70,50,30], K = 2
 Output: 105.00000
 Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.
 Example 2:

 Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
 Output: 30.66667
 Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately.
 
 */
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::priority_queue;

class MincostToHireWorkers {
public:
    double doit_heap(vector<int>&& quality, vector<int>&& wage, int K) {
  
        vector<std::pair<double, int>> workers;
        auto N = quality.size();
        for (auto i = 0; i < N; i++) {
            workers.push_back({double(wage[i])/double(quality[i]), i});
        };
        
        std::sort(workers.begin(), workers.end(), [](auto& a, auto&b) {
            return a.first < b.first;
        });
        
        priority_queue<int> qu;
        int total_quality = 0;
        for (int i = 0; i < K; i++) {
            qu.push(quality[workers[i].second]);
            total_quality += quality[workers[i].second];
        }
        
        double res = total_quality * workers[K-1].first;
        
        for (auto i = K; i < workers.size(); i++) {
            auto c = workers[i];
            double ratio = c.first;
            int q = quality[c.second];
            total_quality += q - qu.top();
            qu.pop();
            res = std::min(res, total_quality * ratio);
            qu.push(q);
        }
        
        return res;
    }
};

void Test_857_MinimumCosttoHireKWorkers() {
    
    // MincostToHireWorkers().doit_heap(vector<int>{10, 20, 5}, vector<int>{70, 50, 30}, 2);
    
    MincostToHireWorkers().doit_heap(vector<int>{3,1,10,10,1}, vector<int>{4,8,2,2,7}, 3);
}
