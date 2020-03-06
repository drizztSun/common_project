/*
 
 
 # 1007. Minimum Domino Rotations For Equal Row

 # In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.
 # (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

 # We may rotate the i-th domino, so that A[i] and B[i] swap values.

 # Return the minimum number of rotations so that all the values in A are the same, or all the values in B are the same.

 # If it cannot be done, return -1.


 # Example 1:
 # Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
 # Output: 2
 # Explanation:
 # The first figure represents the dominoes as given by A and B: before we do any rotations.
 # If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.

 # Example 2:

 # Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
 # Output: -1
 # Explanation:
 # In this case, it is not possible to rotate the dominoes to make one row of values equal.
 
 
 */

#include <algorithm>
#include <vector>
using std::vector;

class MinDominoRotations {
    
public:
    int doit(vector<int>&& A, vector<int>&& B) {
        
        int acnt[7] = {0}, bcnt[7] = {0};
        int most_value = 0;
        
        for (auto i = 0; i < A.size(); i++) {
            acnt[A[i]]++;
            bcnt[B[i]]++;
        
            if (acnt[most_value] + bcnt[most_value] < acnt[A[i]] + bcnt[A[i]])
                most_value = A[i];
            
            if (acnt[most_value] + bcnt[most_value] < acnt[B[i]] + bcnt[B[i]])
                most_value = B[i];
        }
        
        if (acnt[most_value] + bcnt[most_value] < A.size())
            return -1;
        
        int a = 0, b = 0;
        for (size_t i = 0; i < A.size(); i++) {
            
            if (A[i] != most_value && B[i] != most_value) {
                return -1;
            } else if (A[i] == most_value && B[i] == most_value) {
                continue;
            } else if (A[i] == most_value) {
                a++;
            } else if (B[i] == most_value) {
                b++;
            }
        }
  
        return std::min(a, b);
    }
    
    int doit1(vector<int>&& A, vector<int>&& B) {
        
        int sol = INT_MAX;
        int countA = 0;
        int countB = 0;
        
        for( auto n = 1; n <= 6; ++n )
        {
            countA = 0;
            countB = 0;
            auto i = 0;
            for( ; i < A.size(); ++i )
            {
                if( A[i] != n && B[i] != n )
                    break;
                
                if( A[i] == n && B[i] == n )
                    continue;
                
                if( A[i] == n )
                    ++countA;
                else if( B[i] == n )
                    ++countB;
            }
            
            if( i == A.size() )
            {
                // potential solution
                sol = std::min( sol, std::min(countA, countB) );
            }
        }
        
        return ( sol == INT_MAX ? -1 : sol );
    }
};


void test_1007_minimum_domina_rotation_for_equal_row() {
    
    auto res1 = MinDominoRotations().doit(vector<int>{2,1,2,4,2,2}, vector<int>{5,2,6,2,3,2});
    
    auto res2 = MinDominoRotations().doit(vector<int>{3,5,1,2,3}, vector<int>{3,6,3,3,4});
    
    return;
}
