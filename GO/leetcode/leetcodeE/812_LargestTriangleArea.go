package leetcodeE

/*
# You have a list of points in the plane. Return the area of the largest triangle that can be formed by any 3 of the points.

# Example:
# Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
# Output: 2
# Explanation: 
# The five points are show in the figure below. The red triangle is the largest.
*/

import (
	"math"
)

func largestTriangleArea(points [][]int) float64 {
    
    ans := 0.0
    
    for i := 0; i < len(points); i++ {
        
        for j := i + 1; j < len(points); j++ {
            
            for k := j + 1; k < len(points); k++ {
                
                aerea := math.Abs(float64(points[i][0] * (points[j][1] - points[k][1]) + 
                                          points[j][0] * (points[k][1] - points[i][1]) + 
                                          points[k][0] * (points[i][1] - points[j][1])))
                
                if ans < aerea {
                    ans = aerea
                }
            }
        }
    }
    
    return ans * 0.5
}