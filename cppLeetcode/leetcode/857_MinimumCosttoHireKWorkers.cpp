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

    /*
        857.Minimum-Cost-to-Hire-K-Workers
        我们考虑如果将wage[i]/quality[i]作为评价指标来进行排序意味着什么？

        wage[i]/quality[i]最高的那位,意味着最不实惠的工人，它拉高了unitWage，使得其他工人都必须按照这个unitWage乘以各自的quality拿工资．但转念一想，如果我们必须雇佣这个最不实惠的工人的话，那么剩下的工人该如何选择呢？
        显然我们只要选K-1个quality最低的工人，他们可以拉高那个＂最不实惠工人＂的quality比重，从而减少其他工人的quality比重，从而降低总工资．

        我们再考虑，如果选择了wage[i]/quality[i]第二高的那位，那么我们就在接下来的N-2个人里面选择K-1个quality最底的工人即可．

        由此贪心法的最优策略就出来了．实际操作中，我们根据wage[i]/quality[i]从低到高进行处理．
    */
    double doit_sort_heap(vector<int>& quality, vector<int>& wage, int K) 
    {
        vector<std::pair<double,int>> q;

        for (int i = 0; i < quality.size(); i++)
            q.push_back({wage[i]*1.0 / quality[i], quality[i]});
        
        sort(q.begin(), q.end());
        
        int totalQuality = 0;
        double result = INT_MAX;

        priority_queue<int> pq;
        
        for (int i = 0; i < q.size(); i++)
        {
            totalQuality += q[i].second;
            pq.push(q[i].second);
            
            if (pq.size() == K)
            {
                double unitWage = q[i].first;
                result = std::min(result, unitWage * totalQuality);
                totalQuality -= pq.top();
                pq.pop();
            }
        }        
        
        return result;        
    }

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