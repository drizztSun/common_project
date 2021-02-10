"""
1637. Widest Vertical Area Between Two Points Containing No Points

Given n points on a 2D plane where points[i] = [xi, yi], Return the widest vertical area between two points such that no points are inside the area.

A vertical area is an area of fixed-width extending infinitely along the y-axis (i.e., infinite height). The widest vertical area is the one with the maximum width.

Note that points on the edge of a vertical area are not considered included in the area.

 

Example 1:

​
Input: points = [[8,7],[9,9],[7,4],[9,7]]
Output: 1
Explanation: Both the red and the blue area are optimal.
Example 2:

Input: points = [[3,1],[9,0],[1,0],[1,4],[5,3],[8,8]]
Output: 3
 

Constraints:

n == points.length
2 <= n <= 105
points[i].length == 2
0 <= xi, yi <= 109


"""


class MaxWidthOfVerticalArea:
    
    def doit_(self, points: list) -> int:

        points.sort(key=lambda x: x[0])
        max_x = 0 
        for i in range(len(points) - 1):
            max_x = max(max_x, points[i+1][0] - points[i][0])
        return max_x

    def maxWidthOfVerticalArea(self, points: list) -> int:
        # the widest vertical area is simply the widest difference between any
        # consequtive points along the x axis.
        # to resolve the problem we sort the points by their x values
        # and compute the largest difference between any two consqutive points.
        
        def quicksort(arr):
            if len(arr) <= 1:
                return arr
            else:
                pivot = arr[0]
                left = []
                right = []
                rest = arr[1:]
                for i in rest:
                    if i <= pivot:
                        left.append(i)
                    else:
                        right.append(i)
                return quicksort(left)+[pivot]+quicksort(right)
        
        
        def mergeSort(arr):
            if len(arr) == 1:
                return arr
            else:
                mid = int(len(arr) / 2)
                left = arr[:mid]
                right = arr[mid:]
                return merge(mergeSort(left),mergeSort(right))

        def merge(left, right):
            merged = []
            i = 0
            j = 0
            while i < len(right) and j < len(left):
                if right[i] < left[j]:
                    merged.append(right[i])
                    i = i+1
                else:
                    merged.append(left[j])
                    j = j+1
            if i <= len(right)-1:
                merged = merged + right[i:]
            elif j <= len(left)-1:
                merged = merged + left[j:]
            return merged


        
        x = []
        for p in points:
            x.append(p[0])

        sortedPoints = mergeSort(x) # or use quicksort
       
        res = 0
        for i in range(0, len(x)-1):
            if sortedPoints[i+1] - sortedPoints[i] > res:
                res = sortedPoints[i+1] - sortedPoints[i]
        return res