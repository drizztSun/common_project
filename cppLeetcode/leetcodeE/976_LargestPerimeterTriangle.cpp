/*

 976. Largest Perimeter Triangle
 
 Given an array A of positive lengths, return the largest perimeter of a triangle with non-zero area, formed from 3 of these lengths.

 If it is impossible to form any triangle of non-zero area, return 0.

 
 Example 1:

 Input: [2,1,2]
 Output: 5
 
 Example 2:

 Input: [1,2,1]
 Output: 0
 
 Example 3:

 Input: [3,2,3,4]
 Output: 10
 
 Example 4:

 Input: [3,6,2,3]
 Output: 8
 */

#include <vector>
using std::vector;

class LargestPerimeter {
public:
    /*
     Approach 1: Sort
     Intuition

     Without loss of generality, say the sidelengths of the triangle are a \leq b \leq ca≤b≤c.
     The necessary and sufficient condition for these lengths to form a triangle of non-zero area is a + b > ca+b>c.

     Say we knew cc already. There is no reason not to choose the largest possible aa and bb from the array. If a + b > ca+b>c, then it forms a triangle, otherwise it doesn't.

     Algorithm

     This leads to a simple algorithm: Sort the array. For any cc in the array, we choose the largest possible a \leq b \leq ca≤b≤c: these are just the two values adjacent to cc.
     If this forms a triangle, we return the answer.
     */
    int doit(vector<int>&& A) {

        std::sort(A.begin(), A.end());
        
        for (int i = A.size() - 3; i > -1; i--) {
            if (A[i+1] + A[i] > A[i+2])
                return A[i+1] + A[i] + A[i+2];
        }
        
        return 0;
    }
};

void test_976_largest_perimeter_triangle() {
    
    auto res1 = LargestPerimeter().doit(vector<int>{2,1,2});
    
    auto res2 = LargestPerimeter().doit(vector<int>{1,2,1});
    
    auto res3 = LargestPerimeter().doit(vector<int>{3,2,3,4});
    
    auto res4 = LargestPerimeter().doit(vector<int>{3,6,2,3});
    
    auto res5 = LargestPerimeter().doit(vector<int>{8, 4, 4, 4, 3});
    
    return;
}
