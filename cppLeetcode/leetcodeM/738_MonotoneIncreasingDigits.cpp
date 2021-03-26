/*
738. Monotone Increasing Digits

Given a non-negative integer N, find the largest number that is less than or equal to N with monotone increasing digits.

(Recall that an integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.)

Example 1:
Input: N = 10
Output: 9
Example 2:
Input: N = 1234
Output: 1234
Example 3:
Input: N = 332
Output: 299
Note: N is an integer in the range [0, 10^9].

*/
#include <vector>

using std::vector;


class MonotoneIncreasingDigits {

public:
    
    int doit_greedy(int N) {
        
        int t = N;
        vector<int> digits;

        do {
            digits.push_back(t % 10);
            t /= 10;
        } while (t > 0);

        std::reverse(begin(digits), end(digits));
        int pre = 0;
        bool done = false;

        for (int i = 0; !done && i < digits.size() - 1; i++) {

            if (digits[pre] != digits[i])
                pre = i;

            if (digits[i] > digits[i + 1]) {
                digits[pre] -= 1;
                done = true;
            }
        }

        int num = 0;
        for (int i = 0; i < digits.size(); i++) {
            num = (done && i > pre ? 9 : digits[i]) + 10 * num;
        }

        return num;
    }
};