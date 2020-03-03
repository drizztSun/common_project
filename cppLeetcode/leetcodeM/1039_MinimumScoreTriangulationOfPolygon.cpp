/*
 
 # 1039. Minimum Score Triangulation of Polygon

 # Given N, consider a convex N-sided polygon with vertices labelled A[0], A[i], ..., A[N-1] in clockwise order.

 # Suppose you triangulate the polygon into N-2 triangles.  For each triangle, the value of that triangle is the product of the labels of the vertices, and the total score of the triangulation is the sum of these values over all N-2 triangles in the triangulation.

 # Return the smallest possible total score that you can achieve with some triangulation of the polygon.


 # Example 1:

 # Input: [1,2,3]
 # Output: 6
 # Explanation: The polygon is already triangulated, and the score of the only triangle is 6.

 # Example 2:


 # Input: [3,7,4,5]
 # Output: 144
 # Explanation: There are two triangulations, with possible scores: 3*7*5 + 4*5*7 = 245, or 3*4*5 + 3*4*7 = 144.  The minimum score is 144.

 # Example 3:

 # Input: [1,3,1,4,1,5]
 # Output: 13
 # Explanation: The minimum score triangulation has score 1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13.
 
 */

/*
   /*
    https://leetcode.com/problems/minimum-score-triangulation-of-polygon/submissions/
    
    The idea is to  take each pair of vertices possible and then with those fixed, find
    a vertex in between such that the polygon on left and right side of it are of min score.
    
*/

#include <vector>

using std::vector;

class MinScoreTriangulation {
    
public:
    
    int doit(vector<int>&& A) {
        
        const size_t N = A.size();
        vector<vector<int>> dp(N, vector<int>(N, 0));
        
        for (int i = 2; i < N; i++) {
            
            for (int j = i - 2; j >= 0; j--) {
                    
                for (int k = j+1; k < i; k++) {
                    
                    int cur = A[i] * A[k] * A[j];
                    
                    dp[j][i] = std::min(dp[j][i] == 0 ? INT_MAX : dp[j][i], dp[j][k] + cur + dp[k][i]);
                }
            }
        }
        
        return dp[0][N-1];
    }
    
    int doit1(vector<int>&& arr) {
        if(arr.empty())
            return 0;
        
        const int N = arr.size();
        // dp(i, j): min triangulation score of polygon with vertices
        // starting from i..j and there is an edge between i and j
        vector<vector<int> > dp(N, vector<int>(N, 0));
        
        // start swiping each vertex using index 'i' and use the index
        // 'j' to keep the other end fixed, this i and j edge will then be evaluated
        // with every other vertex in between them by making a triangle with it and checking
        // the score of left and right side of remaining polygon.
        // first vertex
        for(int i = 2; i < N; i++) {
            // second vertex
            for(int j = i - 2; j >= 0; j--) {
                // pick the third vertex in between the endpoints
                for(int k = j + 1; k < i; k++) {
                    int curr_area = arr[i] * arr[k] * arr[j];
                    dp[j][i] = std::min(dp[j][i] == 0 ? INT_MAX : dp[j][i],
                                   dp[j][k] + curr_area + dp[k][i]);
                }
            }
        }
        return dp[0][N-1];
    }
};


void test_1039_Minimum_Score_Triangulation_of_Polygon() {
    
    auto res1 = MinScoreTriangulation().doit(vector<int>{1, 2, 3});

    auto res2 = MinScoreTriangulation().doit(vector<int>{3,7,4,5});
    
    auto re3 = MinScoreTriangulation().doit(vector<int>{1,3,1,4,1,5});
    
    return;
}
