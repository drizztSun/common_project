/*
391. Perfect Rectangle

Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.

Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).


Example 1:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [3,2,4,4],
  [1,3,2,4],
  [2,3,3,4]
]

Return true. All 5 rectangles together form an exact cover of a rectangular region.
 

 

Example 2:

rectangles = [
  [1,1,2,3],
  [1,3,2,4],
  [3,1,4,2],
  [3,2,4,4]
]

Return false. Because there is a gap between the two rectangular regions.
 

 

Example 3:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [3,2,4,4]
]

Return false. Because there is a gap in the top center.
 

 

Example 4:

rectangles = [
  [1,1,3,3],
  [3,1,4,2],
  [1,3,2,4],
  [2,2,4,4]
]

Return false. Because two of the rectangles overlap with each other.
 

Accepted
28,057
Submissions
90,525

*/
#include <vector>
#include <set>

using std::set;
using std::vector;

class PerfectRectangle {
public:
    /*
        Reequirement:
        1. Exact 4 corners (unmatched points)
        2. sum(area) = area of 4-corner enclosed area.

        Use a hashtable to store all unmatech points

        Time complexity: O(n)
        Space complexity: O(n)
    */
    bool doit_(vector<vector<int>>& rectangles) {
        
        set<std::pair<int, int>> corners;
        int area = 0;
        for (const auto& rect : rectangles) {
            
            std::pair<int, int> p1{rect[0], rect[1]};
            std::pair<int, int> p2{rect[2], rect[1]};
            std::pair<int, int> p3{rect[0], rect[3]};
            std::pair<int, int> p4{rect[2], rect[3]};
            
            for (const auto& p: {p1, p2, p3, p4}) {
                auto res = corners.insert(p);
                if (!res.second)
                    corners.erase(res.first);
            }
            
            area += (rect[2] - rect[0]) * (rect[3] - rect[1]);
        }
        
        // Only 4 corners should be left, all internal points should be appeard 2 0r 4 times, then we already removed them.
        if (corners.size() != 4) return false;
        
        const auto& p1 = *begin(corners);
        const auto& p3 = *rbegin(corners);
        // verify area is the same or not.
        return area == (p3.first - p1.first) * (p3.second - p1.second);
    }
};