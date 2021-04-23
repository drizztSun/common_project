/*
1073. Adding Two Negabinary Numbers


Given two numbers arr1 and arr2 in base -2, return the result of adding them together.

Each number is given in array format:  as an array of 0s and 1s, from most significant bit to least significant bit.  

For example, arr = [1,1,0,1] represents the number (-2)^3 + (-2)^2 + (-2)^0 = -3.  A number arr in array, format is also guaranteed to have no leading zeros: either arr == [0] or arr[0] == 1.

Return the result of adding arr1 and arr2 in the same format: as an array of 0s and 1s with no leading zeros.

 

Example 1:

Input: arr1 = [1,1,1,1,1], arr2 = [1,0,1]
Output: [1,0,0,0,0]
Explanation: arr1 represents 11, arr2 represents 5, the output represents 16.
Example 2:

Input: arr1 = [0], arr2 = [0]
Output: [0]
Example 3:

Input: arr1 = [0], arr2 = [1]
Output: [1]
 

Constraints:

1 <= arr1.length, arr2.length <= 1000
arr1[i] and arr2[i] are 0 or 1
arr1 and arr2 have no leading zeros

*/
#include <vector>
#include <algorithm>

using std::vector;

class AddTwoNege {

public:

    /*
        Intuition:
        Quite similar to 1017. Convert to Base -2

        Maybe write a base2 addition first?
        Add minus -?
        Done.

        Complexity
        Time O(N), Space O(N)
    */

    vector<int> addBinary(vector<int>& A, vector<int>& B) {
        vector<int> res;
        int carry = 0, i = A.size() - 1, j = B.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            if (i >= 0) carry += A[i--];
            if (j >= 0) carry += B[j--];
            res.push_back(carry & 1);
            carry = (carry >> 1);
        }
        reverse(res.begin(), res.end());
        return res; 
    }

    vector<int> addNegabinary(vector<int>& A, vector<int>& B) {
        vector<int> res;
        int carry = 0, i = A.size() - 1, j = B.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            if (i >= 0) carry += A[i--];
            if (j >= 0) carry += B[j--];
            res.push_back(carry & 1);
            carry = -(carry >> 1);
        }

        while (res.size() > 1 && res.back() == 0)
            res.pop_back();
        reverse(res.begin(), res.end());

        return res;
    }

    /*
        The base algorithm is derived from wikipedia, basically, the majority of bit sum is the same. The main difference is to understand that the sum at each bit location, 
        will be decompose to carry, and the bit at current location. So from the wikipedia chart, for example, when bit sum equals to 2, it should be decomposed to current bit = 0, carry = -1. (because 0 * 2^0 + (-1)*(-2) = 2)

        image

        Therefore, we know that we can mostly perform bit additions, and simply addressing the carry based on the total sum.
    */
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        int carry = 0;
        vector<int> res;
        int p1 = (int)arr1.size() -  1, p2 = (int)arr2.size() -  1;
        while( p1 >=0 || p2 >=0 || carry!= 0) {
           if(p1 >= 0) carry += arr1[p1--];
           if(p2 >= 0) carry += arr2[p2--];
           res.push_back(abs(carry) & 1);
           carry = carry > 1 ? -1 : carry < 0 ? 1 : 0;
        }
        
        while(res.size() > 1 &&res.back() == 0) 
            res.pop_back();
        reverse(res.begin(), res.end());
        return res;
    }
}