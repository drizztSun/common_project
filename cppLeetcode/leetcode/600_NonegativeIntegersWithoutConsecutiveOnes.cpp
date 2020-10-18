/*
 600. Non-negative Integers without Consecutive Ones
 
 Given a positive integer n, find the number of non-negative integers less than or equal to n, whose binary representations do NOT contain consecutive ones.

 Example 1:
 Input: 5
 Output: 5
 Explanation:
 Here are the non-negative integers <= 5 with their corresponding binary representations:
 0 : 0
 1 : 1
 2 : 10
 3 : 11
 4 : 100
 5 : 101
 Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule.
 
 
 */
#include <vector>
using std::vector;

class BiggestIntergersWOConsecutiveOnes {
    
public:
    int doit_dp(int num) {
        
        int dp[32];
        dp[0] = 1, dp[1] = 2;
        
        for (int i = 2; i < 31; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        int sum = 0;
        int prebit = 0;
        
        for (int i = 31; i >= 0; i--) {
            // discard bit is 0, because it is consider as 1, it will exceed the num
            if ((num & (1 << i)) != 0) {
                sum += dp[i];
                if (prebit == 1) {
                    // if it is first 11, cal and quit, because the rest number til to num, will have 10011xxx, that has consecutive 11.
                    sum -= 1;
                    break;
                }
                prebit = 1;
            } else
                prebit = 0;
            

        }
        
        return sum + 1;
    }
    
    int do_dp_1(int num) {
        int dp[33][3][2]; // dp[i][012]  first ith binary, 0 <, 1 =,  2 <, first i of num's binary, (0, 1 end with 0 or 1)
        vector<int> bin;
        for (int i = num; i > 0; i /= 2)
            bin.push_back(i % 2);
        
        reverse(bin.begin(), bin.end());
        
        if (num < 2)
            return num + 1;
            
        int ret = 1;
        dp[1][1][1] = 1;
        ret += dp[1][1][1];
        
        
        for (int i = 2; i < bin.size(); i++){
            for(int pre = 0; pre < 3; pre++) {
                for (int last = 0; last < 2; last++) {
                    for (int nex = 0; nex < 2; nex++) {
                        if (last == nex && last == 1)
                            continue;
                        int status;
                        if (pre == 0)
                            status = 0;
                        else if (pre == 1 && bin[i-1] == nex) {
                            status = 1;
                        } else if (pre == 1 && bin[i-1] > nex) {
                            status = 0;
                        } else
                            status = 2;
                        
                        dp[i][status][nex] += dp[i-1][pre][last];
                        
                        if (i != bin.size())
                            ret += dp[i-1][pre][last];
                        else if (status <= 1)
                            ret += dp[i-1][pre][last];
                    }
                }
            }
        }

        return ret;
    }
    
    /*
    If we have n bits, the number of integers without consecutive ones f(n) = f(n - 1) + f (n - 2).
    f(n - 1) is for the case when first bit is zero, and
    f(n - 2) is when then the first bit is one and second bit is zero (as we cannot have consecutive ones):

    f(n) = ì0î f(n - 1) + ì10î f(n - 2).
    These are Fibonacci numbers, and we can have them in a static array for [0Ö31] bits.

    First, we find n, which is the position of the highest set bit in our number.

    Now, if the binary representation of our number starts with ì11î, then all integers will be smaller than our number,
    and we can just return a Fibonacci number for n bits.

    For example, if n == 12 (binary 0b1100), highest bit at the position 4, next bit is set, so the result is 8 (fb[4]).
    If the binary representation of our number starts with ì10î, then all integers with n - 1 bits will be smaller than our number.
    So, we will grab a Fibonacci number for n - 1 bits. Thatís ì0î + f(n - 1) case.
    Plus, we need to add ì10Öî case, so we remove the highest bit from our number and recursively call our function.

    For example, if n == 18 (binary 0b10010), the highest bit at the position 5, next bit is unset,
    so taking 8 (fb[4] for 0x01111) and adding 3 (fb[2] for 0x00010).
    */

    int findInteger(int num) {
        // below are fibonacci number
        static int fb[31] = { 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946,
            17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578 };

        if (num < 3)
            return num;

        for (int bt = 29; bt >= 0; bt--) {
            if (num & 1 << bt)
                return num & (1 << (bt - 1)) ? fb[bt] : fb[bt - 1] + findInteger((num & ~(1 << bt)));
        }
        return 0;
    }
};

void Test_600_WithOutConsecutveOnes() {

    int res = 0;

    res = BiggestIntergersWOConsecutiveOnes().findInteger(5);

    res = BiggestIntergersWOConsecutiveOnes().findInteger(5);

    res = BiggestIntergersWOConsecutiveOnes().findInteger(5);
}
