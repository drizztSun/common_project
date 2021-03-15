/*

447. Number of Boomerangs

You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. 
A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Return the number of boomerangs.

 

Example 1:

Input: points = [[0,0],[1,0],[2,0]]
Output: 2
Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
Example 2:

Input: points = [[1,1],[2,2],[3,3]]
Output: 2
Example 3:

Input: points = [[1,1]]
Output: 0
 

Constraints:

n == points.length
1 <= n <= 500
points[i].length == 2
-104 <= xi, yi <= 104
All the points are unique.

*/
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class NumberOfBoomerangs {

    /*
        447.Number-of-Boomerangs
        固定一个点i，查找其他所有点到该点的距离，存进一个Map。假设到i距离为d的点的数目有n个，说明有n*(n-1)个(i,j,k)配对。

        因为(i,j,k)的次序有关系，遍历其他点的时候，要考察所有点而不是仅仅从i+1开始。
    */
    int numberOfBoomerangs(vector<vector<int>>& points) 
    {
        int result=0;
        for (int i=0; i<points.size(); i++)
        {
            unordered_map<int,int>Map;
            for (int j=0; j<points.size(); j++)
            {
                int dist = (points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) + (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]);
                Map[dist]++;
            }
            for (auto a:Map)
            {
                result+=a.second*(a.second-1);
            }            
        }
        
        return result;
    }
};