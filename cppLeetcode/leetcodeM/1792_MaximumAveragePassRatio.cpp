/*
1792. Maximum Average Pass Ratio

There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes, where classes[i] = [passi, totali]. 
You know beforehand that in the ith class, there are totali total students, but only passi number of students will pass the exam.

You are also given an integer extraStudents. There are another extraStudents brilliant students that are guaranteed to pass the exam of any class they are assigned to. 
You want to assign each of the extraStudents students to a class in a way that maximizes the average pass ratio across all the classes.

The pass ratio of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. 
The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.

Return the maximum possible average pass ratio after assigning the extraStudents students. Answers within 10-5 of the actual answer will be accepted.

 

Example 1:

Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
Output: 0.78333
Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.
Example 2:

Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
Output: 0.53485
 

Constraints:

1 <= classes.length <= 105
classes[i].length == 2
1 <= passi <= totali <= 105
1 <= extraStudents <= 105

*/
#include <queue>
#include <vector>


using std::vector;
using std::priority_queue;


class MaxAverageRatio {

public:

    /*
        Max heap and always pich the top one with more ave ratio changed.
    */
    double doit_heap(vector<vector<int>>& classes, int extraStudents) {
        
        auto dist = [](double a, double b) -> double {
            return (a+1) / (b+1) - a / b;
        };

        auto cmp = [&](auto a, auto b) {
            return dist(a.first, a.second) < dist(b.first, b.second);
        };

        int ones = 0;
        priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);

        for (auto c : classes) {
            if (c[0] == c[1]) {
                ones++;
                continue;
            }
            pq.emplace(c[0], c[1]);
        }

        
        while (extraStudents-- && !pq.empty()) {
            auto it = pq.top(); pq.pop();
            pq.emplace(it.first+1, it.second+1);
        }

        
        double total = 0;
        while (!pq.empty()) {
            auto c = pq.top(); pq.pop();
            total += double(c.first) / double(c.second);
        }
        
        return (total + ones) / classes.size();
    }
};