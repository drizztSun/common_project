/*
1362. Closest Divisors


Given an integer num, find the closest two integers in absolute difference whose product equals num + 1 or num + 2.

Return the two integers in any order.

 

Example 1:

Input: num = 8
Output: [3,3]
Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.
Example 2:

Input: num = 123
Output: [5,25]
Example 3:

Input: num = 999
Output: [40,25]
 

Constraints:

1 <= num <= 10^9

*/
#include <vector>
using std::vector;

class CloestDivisor {

public:

    /*
        Explanation
        Iterate a from sqrt(x+2) to 1, and check:
        if (x + 1) % a == 0, we directly return the pair [a, (x + 1) / a].
        if (x + 2) % a == 0, we directly return the pair [a, (x + 2) / a].
        The first valid pair we meet will have be the closet pair.
        
        Complexity
        Time O(sqrtX), Space O(1)
    */

    vector<int> closestDivisors(int x) {
    
        for (int a = sqrt(x + 2); a > 0; --a) {
            if ((x + 1) % a == 0)
                return {a, (x + 1) / a};
            if ((x + 2) % a == 0)
                return {a, (x + 2) / a};
        }
        return {};
    }
}