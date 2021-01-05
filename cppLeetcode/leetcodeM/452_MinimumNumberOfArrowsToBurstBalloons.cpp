/*
452. Minimum Number of Arrows to Burst Balloons

There are some spherical balloons spread in two-dimensional space. For each balloon, provided input is the start and end coordinates of the horizontal diameter. 
Since it's horizontal, y-coordinates don't matter, and hence the x-coordinates of start and end of the diameter suffice. The start is always smaller than the end.

An arrow can be shot up exactly vertically from different points along the x-axis. A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend. 
There is no limit to the number of arrows that can be shot. An arrow once shot keeps traveling up infinitely.

Given an array points where points[i] = [xstart, xend], return the minimum number of arrows that must be shot to burst all balloons.

 

Example 1:

Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).
Example 2:

Input: points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4
Example 3:

Input: points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2
Example 4:

Input: points = [[1,2]]
Output: 1
Example 5:

Input: points = [[2,3],[2,3]]
Output: 1
 

Constraints:

0 <= points.length <= 104
points[i].length == 2
-231 <= xstart < xend <= 231 - 1


*/
#include <vector>
#include <algorithm>


using std::vector;

class MinimumNumberArrows {

public:

    /*

    Approach 1: Greedy

    Greedy algorithms

    Greedy problems usually look like "Find minimum number of something to do something" or "Find maximum number of something to fit in some conditions", and typically propose an unsorted input.

    The idea of greedy algorithm is to pick the locally optimal move at each step, that will lead to the globally optimal solution.

    The standard solution has \mathcal{O}(N \log N)O(NlogN) time complexity and consists of two parts:

    Figure out how to sort the input data (\mathcal{O}(N \log N)O(NlogN) time). That could be done directly by a sorting or indirectly by a heap usage. Typically sort is better than the heap usage because of gain in space.

    Parse the sorted input to have a solution (\mathcal{O}(N)O(N) time).

    Please notice that in case of well-sorted input one doesn't need the first part and the greedy solution could have \mathcal{O}(N)O(N) time complexity, here is an example.

    How to prove that your greedy algorithm provides globally optimal solution?

    Usually you could use the proof by contradiction.

    Intuition

    Let's consider the following combinations of the balloons.

    Algorithm

    Now the algorithm is straightforward :

    Sort the balloons by end coordinate x_end.

    Initiate the end coordinate of a balloon which ends first : first_end = points[0][1].

    Initiate number of arrows: arrows = 1.

    Iterate over all balloons:

    If the balloon starts after first_end:

    Increase the number of arrows by one.

    Set first_end to be equal to the end of the current balloon.

    Return arrows.

    Implementation

    */

    int doit_greedy(vector<vector<int>>& points) {

        if (points.size() < 2) return points.size();
        
        std::sort(begin(points), end(points), [](const auto& a, const auto& b){
           return a[1] < b[1]; 
        });
        
        int endTime = INT_MIN, keep = 0;
        
        for (const auto& c : points) {
            if (c[0] > endTime) {
                endTime = c[1];
                keep++;
            }
        }
        return keep;
    }
};