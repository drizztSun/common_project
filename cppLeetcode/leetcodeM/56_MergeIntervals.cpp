/*
 
 56. Merge Intervals
 
 
 Given a collection of intervals, merge all overlapping intervals.

 Example 1:

 Input: [[1,3],[2,6],[8,10],[15,18]]
 Output: [[1,6],[8,10],[15,18]]
 Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
 
 Example 2:

 Input: [[1,4],[4,5]]
 Output: [[1,5]]
 Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
 
 */


#include <vector>
using std::vector;

#include <algorithm>

class MergeIntervals {
    
public:
    
    /*
     
     Approach 2: Sorting
     Intuition

     If we sort the intervals by their start value, then each set of intervals that can be merged will appear as a contiguous "run" in the sorted list.

     Algorithm

     First, we sort the list as described. Then, we insert the first interval into our merged list and continue considering each interval in turn as follows: If the current interval begins after the previous interval ends, then they do not overlap and we can append the current interval to merged. Otherwise, they do overlap, and we merge them by updating the end of the previous interval if it is less than the end of the current interval.

     A simple proof by contradiction shows that this algorithm always produces the correct answer. First, suppose that the algorithm at some point fails to merge two intervals that should be merged. This would imply that there exists some triple of indices ii, jj, and kk in a list of intervals \text{ints}ints such that i < j < ki<j<k and (\text{ints[i]}ints[i], \text{ints[k]}ints[k]) can be merged, but neither (\text{ints[i]}ints[i], \text{ints[j]}ints[j]) nor (\text{ints[j]}ints[j], \text{ints[k]}ints[k]) can be merged. From this scenario follow several inequalities:

     \begin{aligned} \text{ints[i].end} < \text{ints[j].start} \\ \text{ints[j].end} < \text{ints[k].start} \\ \text{ints[i].end} \geq \text{ints[k].start} \\ \end{aligned}
     ints[i].end<ints[j].start
     ints[j].end<ints[k].start
     ints[i].end≥ints[k].start
     ​    
      

     We can chain these inequalities (along with the following inequality, implied by the well-formedness of the intervals: \text{ints[j].start} \leq \text{ints[j].end}ints[j].start≤ints[j].end) to demonstrate a contradiction:

     \begin{aligned} \text{ints[i].end} < \text{ints[j].start} \leq \text{ints[j].end} < \text{ints[k].start} \\ \text{ints[i].end} \geq \text{ints[k].start} \end{aligned}
     ints[i].end<ints[j].start≤ints[j].end<ints[k].start
     ints[i].end≥ints[k].start
     ​    
      

     Therefore, all mergeable intervals must occur in a contiguous run of the sorted list.
    
    */
    
    vector<vector<int>> doit(vector<vector<int>>&& intervals) {
        
        std::sort(intervals.begin(), intervals.end(), [](auto& a, auto&b)-> bool {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });
        
        vector<vector<int>> ans;
        
        for (auto& c : intervals) {
            
            if (ans.empty()) {
                ans.push_back(c);
                continue;
            }
            
            auto& back = ans.back();
            if (c[0] > back[1]) {
                ans.push_back(c);
            } else if (c[0] <= back[1] && c[1] > back[1]) {
                back[1] = c[1];
            }
            
        }
        
        return ans;
    }
};


void test_56_merge_intervals() {
    
    
    auto res1 = MergeIntervals().doit(vector<vector<int>>{{1, 3}, {2, 6}, {8, 10}, {15, 18}});
    
    auto res2 = MergeIntervals().doit(vector<vector<int>>{{1, 4}, {4, 5}});
    
    auto res3 = MergeIntervals().doit(vector<vector<int>>{{1, 4}, {1, 5}});
    
    return;
}
