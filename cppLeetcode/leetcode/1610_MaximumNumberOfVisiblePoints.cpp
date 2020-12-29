/*
1610. Maximum Number of Visible Points


You are given an array points, an integer angle, and your location, where location = [posx, posy] and points[i] = [xi, yi] both denote integral coordinates on the X-Y plane.

Initially, you are facing directly east from your position. You cannot move from your position, but you can rotate. In other words, posx and posy cannot be changed. 
Your field of view in degrees is represented by angle, determining how wide you can see from any given view direction. Let d be the amount in degrees that you rotate counterclockwise. 
Then, your field of view is the inclusive range of angles [d - angle/2, d + angle/2].


You can see some set of points if, for each point, the angle formed by the point, your position, and the immediate east direction from your position is in your field of view.

There can be multiple points at one coordinate. There may be points at your location, and you can always see these points regardless of your rotation. Points do not obstruct your vision to other points.

Return the maximum number of points you can see.

 

Example 1:


Input: points = [[2,1],[2,2],[3,3]], angle = 90, location = [1,1]
Output: 3
Explanation: The shaded region represents your field of view. All points can be made visible in your field of view, including [3,3] even though [2,2] is in front and in the same line of sight.
Example 2:

Input: points = [[2,1],[2,2],[3,4],[1,1]], angle = 90, location = [1,1]
Output: 4
Explanation: All points can be made visible in your field of view, including the one at your location.
Example 3:


Input: points = [[1,0],[2,1]], angle = 13, location = [1,1] 
Output: 1
Explanation: You can only see one of the two points, as shown above.
 

Constraints:

1 <= points.length <= 105
points[i].length == 2
location.length == 2
0 <= angle < 360
0 <= posx, posy, xi, yi <= 109
*/
#include <vector>
#include <algorithm>

using std::vector;


class MaximumNumberOfVisiblePoints {

public:

    /*
        SOlution: Sliding Window

        1. Transform the coordinate system, treat location[0], location[1] as origijn.
        2. Compute the angle of each point w.r.t tp new origin, angle is (-pi, +pi)
        3. Sort all the angles
        4. Maintain a window [l, r] s.t. angle =[r] - angle[l] <= FOV

        Note:
        1. If there are points at the new origin, they are all visiable.

        2. Duplicate the angle with +2pi to hanfle turn-around case

        Time complexity: O(nlogn)
        Space complexity: O(n)
    */

    int doit_(vector<vector<int>>& points, int angle, vector<int>& location) {
        
        int at_origin = 0;
        vector<double> ps;
        // double M_PI = 3.14;

        for (const auto& p: points) {
            if (p[0] == location[0] && p[1] == location[1])
                at_origin++;
            else
                ps.push_back(atan2(p[1] - location[1], p[0] - location[0]));
        }

        std::sort(begin(ps), end(ps));

        const int n = ps.size();
        for (int i = 0; i < n; i++)
            ps.push_back(ps[i] + 2.0 * M_PI); // duplicate the array. because silding window needs to cover section IV and section I

        int l = 0;
        int ans = 0;
        double fov = angle * M_PI / 180.0;

        for (int r = 0; r < ps.size(); ++r) {
            while (ps[r] - ps[l] > fov) ++l;
            ans = std::max(ans, r - l + 1);
        }

        return ans + at_origin;
    }
};