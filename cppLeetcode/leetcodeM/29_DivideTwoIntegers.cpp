/*
29. Divide Two Integers

Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero, which means losing its fractional part. For example, truncate(8.345) = 8 and truncate(-2.7335) = -2.

Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−2^31, 2^31 − 1]. 

For this problem, assume that your function returns 2^31 − 1 when the division result overflows.

 

Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = truncate(3.33333..) = 3.
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = truncate(-2.33333..) = -2.
Example 3:

Input: dividend = 0, divisor = 1
Output: 0
Example 4:

Input: dividend = 1, divisor = 1
Output: 1
 

Constraints:

-2^31 <= dividend, divisor <= 2^31 - 1
divisor != 0

*/
#include <cmath>
#include <vector>

using std::vector;


class DivideTwoIntegers {

    /*
        029.Divide-Two-Integers
        本题的基本思想就是将divisor不断用左移的方法乘以2来逼近dividend，然后将dividend减去倍乘之后的divisor，再重复这个过程直至被除数小于除数。记录这个过程中divisor“倍乘”的总次数，即为答案。

        核心代码就那么几行 (a为被除数，b为除数）：

                int res=0;
                while (a>=b)
                {
                    c = b;
                    count=1;
                    while ((c<<1)<=a)
                    {
                        c=c<<1;
                        count=count<<1;
                    }
                    res+=count;
                    a = a-c;
                }
        其他需要注意的细节：

        1. 注意可能的负号。提前将被除数和除数取绝对值，符号最后留给商。
        2. 对于整形取绝对值，常设的陷阱就是对于INT_MIN，取反之后就会溢出。为了处理起来简单，把变量统统转换为long long类型。
        3. Overflow的意思就是结果>INT_MAX
    */
    int divide(int dividend, int divisor) 
    {
        if (divisor==0) return INT_MAX;
        if (dividend==0) return 0;
        
        long long a = abs((long long) dividend);
        long long b = abs((long long) divisor);
        long long c;
        long long sum=0;
        
        int sign=1;
        if (divisor<0) sign*=-1;
        if (dividend<0) sign*=-1;
        
        while (a>=b)
        {
            c = b;
            long long count=1;
            while ((c<<1)<=a)
            {
                c=c<<1;
                count=count<<1;
            }
            sum+=count;
            a = a-c;
        }
        
        sum=sum*sign;
        
        if (sum>INT_MAX)
            return INT_MAX;
        else
            return sum;
    }


    int divide(int dividend, int divisor) {
        
        if (divisor == 0) return INT_MAX;
        if (dividend == 0) return 0;
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;
        if (dividend == INT_MIN && divisor == 1) return INT_MIN;
        
        int sig = dividend < 0 == divisor < 0 ? 1 : -1;
        
        long long a = abs((long long) dividend);
        long long b = abs((long long) divisor);

        // if (dividend < 0) dividend = -dividend;
        // if (divisor < 0) divisor = -divisor;

        int total = 0;

        while (a >= b) {

            long c = b;
            long cnt = 1;

            while (a >= c) {

                a -= c;
                total += cnt;    

                c += c;
                cnt += cnt;
            }
        }

        total = sig * total;

        return std::min(std::max(INT_MIN, total), INT_MAX);
    }

    
    int divide(int dividend, int divisor) {
    
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;
        if (dividend == INT_MIN && divisor == 1) return INT_MIN;
        
        
        int sig = dividend < 0 == divisor < 0 ? 1 : -1;
        int a = dividend, b = divisor;
        
        // We converted them to negative instead of positive because the range of valid negative numbers is bigger, and therefore overflows can be cleanly avoided.
        if (a > 0) a = -a;
        if (b > 0) b = -b;

        int total = 0;

        while (a <= b) {

            long c = b;
            long cnt = 1;

            while (a <= c) {

                a -= c;
                total += cnt;    

                c += c;
                cnt += cnt;
            }
        }

        total = sig * total;

        return std::min(std::max(INT_MIN, total), INT_MAX);
        
    }

public:

    /*
        The description note that:
        "Assume we are dealing with an environment,
        which could only store integers within the 32-bit signed integer range: [−2^31, 2^31 − 1]."

        But most of solution use "long" integer.
        So I share my solution here.

        Solution 1
        Only one corner case is -2^31 / 1 and I deal with it at the first line.

        This solution has O(logN^2) time complexity.
    */
    int divide(int A, int B) {
        if (A == INT_MIN && B == -1) return INT_MAX;
        int a = abs(A), b = abs(B), res = 0, x = 0;
        while (a - b >= 0) {
            for (x = 0; a - (b << x << 1) >= 0; x++);
            res += 1 << x;
            a -= b << x;
        }
        return (A > 0) == (B > 0) ? res : -res;
    }

    // Solution 2
    // Another solution is also O(32)
    int divide(int A, int B) {
        if (A == INT_MIN && B == -1) return INT_MAX;
        int a = abs(A), b = abs(B), res = 0;

        for (int x = 31; x >= 0; x--)
            if ((signed)((unsigned)a >> x) - b >= 0)
                res += 1 << x, a -= b << x;
        return (A > 0) == (B > 0) ? res : -res;
    }


    /*
        Approach 1: Repeated Subtraction

        Algorithm

        Remember that we're converting the inputs to negative numbers. This is because we don't want separate code for all the possible combinations of positive/negative divisor and dividend. 
        We converted them to negative instead of positive because the range of valid negative numbers is bigger, and therefore overflows can be cleanly avoided.

        The looping condition is while (dividend - divisor <= 0) because the difference is moving towards zero from the negative side. Therefore, we want to continue while it is still under it. Once it goes over, we know we're done.


        Complexity Analysis

        Let nn be the absolute value of dividenddividend.

        Time Complexity : O(n).

        Consider the worst case where the divisor is 11. For any dividend nn, we'll need to subtract 11 a total of nn times to get to 00. Therefore, the time complexity is O(n)O(n) in the worst case.

        Space Complexity : O(1).

        We only use a fixed number of integer variables, so the space complexity is O(1).

        Seeing as nn can be up to 2^{31}, this algorithm is too slow on the largest test cases. We'll need to do better!
    */
    int divide(int dividend, int divisor) {

        // Special case: overflow.
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        /* We need to convert both numbers to negatives
        * for the reasons explained above.
        * Also, we count the number of negatives signs. */
        int negatives = 2;
        if (dividend > 0) {
            negatives--;
            dividend = -dividend;
        }
        if (divisor > 0) {
            negatives--;
            divisor = -divisor;
        }

        /* Count how many times the divisor has to be added
        * to get the dividend. This is the quotient. */
        int quotient = 0;
        while (dividend - divisor <= 0) {
            dividend -= divisor;
            quotient--;
        }

        /* If there was originally one negative sign, then
        * the quotient remains negative. Otherwise, switch
        * it to positive. */
        if (negatives != 1) {
            return -quotient;
        }
        return quotient;
    }

    /*
        Approach 2: Repeated Exponential Searches
        Intuition

        Linear Search is too slow because at each step, we only subtract one copy of the divisor from the dividend. A better way would be to try and subtract multiple copies of the divisor each time.

        One way of quickly increasing numbers, without using multiplication, is to double them repeatedly. So let's try doubling the divisor until it no longer fits into the dividend.

        Complexity Analysis

        Let nn be the absolute value of dividenddividend.

        Time Complexity : O(log^2(n)).

        We started by performing an exponential search to find the biggest number that fits into the current dividend. This search took O(\log \, n)O(logn) operations.

        After doing this search, we updated the dividend by subtracting the number we found. In the worst case, we were left with a dividend slightly less than half of the previous dividend (if it was more than half, then we couldn't have found the maximum number that fit in by doubling!).

        So how many of these searches did we need to do? Well, with the dividend at least halving after each one, there couldn't have been more than O(\log \, n)O(logn) of them.

        So combined together, in the worst case, we have O(\log \, n)O(logn) searches with each search taking O(\log \, n)O(logn) time. This gives us O((\log \, n) \cdot (\log \, n)) = O(\log^2 \, n)O((logn)⋅(logn))=O(log 
        2
        n) as our total time complexity.

        Space Complexity : O(1).

        Because only a constant number of single-value variables are used, the space complexity is O(1)O(1).
    */  
    int HALF_INT_MIN = -1073741824;

    int divide(int dividend, int divisor) {

        // Special case: overflow.
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        /* We need to convert both numbers to negatives.
        * Also, we count the number of negatives signs. */
        int negatives = 2;
        if (dividend > 0) {
            negatives--;
            dividend = -dividend;
        }
        if (divisor > 0) {
            negatives--;
            divisor = -divisor;
        }

        int quotient = 0;
        /* Once the divisor is bigger than the current dividend,
        * we can't fit any more copies of the divisor into it. */
        while (divisor >= dividend) {
            /* We know it'll fit at least once as divivend >= divisor.
            * Note: We use a negative powerOfTwo as it's possible we might have
            * the case divide(INT_MIN, -1). */
            int powerOfTwo = -1;
            int value = divisor;
            /* Check if double the current value is too big. If not, continue doubling.
            * If it is too big, stop doubling and continue with the next step */
            while (value >= HALF_INT_MIN && value + value >= dividend) {
                value += value;
                powerOfTwo += powerOfTwo;
            }
            // We have been able to subtract divisor another powerOfTwo times.
            quotient += powerOfTwo;
            // Remove value so far so that we can continue the process with remainder.
            dividend -= value;
        }

        /* If there was originally one negative sign, then
        * the quotient remains negative. Otherwise, switch
        * it to positive. */
        if (negatives != 1) {
            quotient = -quotient;
        }
        return quotient;
    }

    /*
        Approach 3: Adding Powers of Two
        Intuition

        In the previous approach, we did repeated exponential searches for the largest value that would fit into the current dividend.
    
            Algorithm

        Again, we work with negative numbers to elegantly avoid overflow issues.

        Hopefully you're getting the hang of the conditionals that have to work with negative, instead of positive, numbers!


        Complexity Analysis

        Let nn be the absolute value of dividenddividend.

        Time Complexity : O(logn).

        We take O(\log \, n)O(logn) time in the first loop to create our list of doubles (and powers of two).

        For the second loop, because there's O(\log \, n)O(logn) items in the list of doubles, it only takes O(\log \, n)O(logn)time for this loop as well.

        Combined, our total time complexity is just O(\log \, n + \log \, n) = O(\log \, n)O(logn+logn)=O(logn).

        Space Complexity : O(\log \, n)O(logn).

        The length of the list of doubles of the divisor is proportional to O(\log \, n)O(logn) so our space complexity is O(\log \, n)O(logn).

        This approach is interesting in that the time complexity is lower than the previous one, but it requires a bit of space. Trading off space for time is very common practice.

        However, as we'll see in the next approach, we can modify the algorithm so that we don't need O(\log \, n)O(logn) space at all!
    */
    int divide(int dividend, int divisor) {

        // Special case: overflow.
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        /* We need to convert both numbers to negatives.
        * Also, we count the number of negatives signs. */
        int negatives = 2;
        if (dividend > 0) {
            negatives--;
            dividend = -dividend;
        }
        if (divisor > 0) {
            negatives--;
            divisor = -divisor;
        }

        std::vector<int> doubles;
        std::vector<int> powersOfTwo;

        /* Nothing too exciting here, we're just making a list of doubles of 1 and
        * the divisor. This is pretty much the same as Approach 2, except we're
        * actually storing the values this time. */
        int powerOfTwo = -1;
        while (divisor >= dividend) {
            doubles.push_back(divisor);
            powersOfTwo.push_back(powerOfTwo);
            // Prevent needless overflows from occurring...
            if (divisor < HALF_INT_MIN) {
                break;
            }
            divisor += divisor;
            powerOfTwo += powerOfTwo;
        }

        int quotient = 0;
        /* Go from largest double to smallest, checking if the current double fits.
        * into the remainder of the dividend */
        for (int i = doubles.size() - 1; i >= 0; i--) {
            if (doubles[i] >= dividend) {
                // If it does fit, add the current powerOfTwo to the quotient.
                quotient += powersOfTwo[i];
                // Update dividend to take into account the bit we've now removed.
                dividend -= doubles[i];
            }
        }

        /* If there was originally one negative sign, then
        * the quotient remains negative. Otherwise, switch
        * it to positive. */
        if (negatives != 1) {
            return -quotient;
        }
        return quotient;
    }

    /*
        Approach 4: Adding Powers of Two with Bit-Shifting
        Intuition

        In Approach 3 we put doubles of the divisor, and powers of two into lists. This was so that we could easily refer back to them.

        However, we don't need to save them—we can simply find the largest double, along with it's corresponding power of two, and then generate the rest by dividing by two repeatedly. 
        But we can't divide by two, that breaks the rules..., you might be thinking. The solution is to use the right-shift bitwise operator!


        Complexity Analysis

        Let nn be the absolute value of dividenddividend.

        Time Complexity : O(logn).

        Same as Approach 3, except instead of looping over a generated array, we simply perform an O(1)O(1) halving operation to get the next values we need.

        Space Complexity : O(1).

        We only use a fixed number of integer variables, so the space complexity is O(1)O(1).
    */
    int divide(int dividend, int divisor) {

        // Special case: overflow.
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        /* We need to convert both numbers to negatives.
        * Also, we count the number of negatives signs. */
        int negatives = 2;
        if (dividend > 0) {
            negatives--;
            dividend = -dividend;
        }
        if (divisor > 0) {
            negatives--;
            divisor = -divisor;
        }

        /* In the first loop, we simply find the largest double of divisor. This is
        * very similar to the start of what we did in Approach 2.
        * The >= is because we're working in negatives. In essence, that
        * piece of code is checking that we're still nearer to 0 than we
        * are to INT_MIN. */
        int highestDouble = divisor;
        int highestPowerOfTwo = -1;
        while (highestDouble >= HALF_INT_MIN && dividend <= highestDouble + highestDouble) {
            highestPowerOfTwo += highestPowerOfTwo;
            highestDouble += highestDouble;
        }

        /* In the second loop, we work out which powers of two fit in, by
        * halving highestDouble and highestPowerOfTwo repeatedly.
        * We can do this using bit shifting so that we don't break the
        * rules of the question :-) */
        int quotient = 0;
        while (dividend <= divisor) {
            if (dividend <= highestDouble) {
                quotient += highestPowerOfTwo;
                dividend -= highestDouble;
            }
            /* We know that these are always even, so no need to worry about the
            * annoying "bit-shift-odd-negative-number" case. */
            highestPowerOfTwo >>= 1;
            highestDouble >>= 1;
        }

        /* If there was originally one negative sign, then
        * the quotient remains negative. Otherwise, switch
        * it to positive. */
        return negatives != 1 ? -quotient : quotient;
    }

    /*
        Approach 5: Binary Long Division
        Intuition

        The previous approaches are all fine for an interview. We provide this approach as an alternate way of thinking about the problem, that some people might relate better to.

        Anyway, another way we could divide two integers is to consider how we do division in math.

        One of the common ways, which you may or may not have learned in school, is called long division.

        Like the previous two approaches, long division works by find a large multiple of the divisor which fits into the dividend. Then it subtracts this from the dividend and repeats the process.

        Complexity Analysis

        Let nn be the absolute value of dividenddividend.

        Time Complexity : O(logn).

        As we loop over the bits of our dividend, performing an O(1)O(1) operation each time, the time complexity is just the number of bits of the dividend: O(\log \, n)O(logn).

        Space Complexity : O(1).

        We only use a fixed number of int variables, so the space complexity is O(1).
    */
    int divide(int dividend, int divisor) {

        // Special cases: overflow.
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        if (dividend == INT_MIN && divisor == 1) {
            return INT_MIN;
        }

        /* We need to convert both numbers to negatives.
        * Also, we count the number of negatives signs. */
        int negatives = 2;
        if (dividend > 0) {
            negatives--;
            dividend = -dividend;
        }
        if (divisor > 0) {
            negatives--;
            divisor = -divisor;
        }

        /* We want to find the largest doubling of the divisor in the negative 32-bit
        * integer range that could fit into the dividend.
        * Note if it would cause an overflow by being less than HALF_INT_MIN,
        * then we just stop as we know double it would not fit into INT_MIN anyway. */
        int maxBit = 0;
        while (divisor >= HALF_INT_MIN && divisor + divisor >= dividend) {
            maxBit += 1;
            divisor += divisor;
        }

        int quotient = 0;
        /* We start from the biggest bit and shift our divisor to the right
        * until we can't shift it any further */
        for (int bit = maxBit; bit >= 0; bit--) {
            /* If the divisor fits into the dividend, then we should set the current
            * bit to 1. We can do this by subtracting a 1 shifted by the appropriate
            * number of bits. */
            if (divisor >= dividend) {
                quotient -= (1 << bit);
                /* Remove the current divisor from the dividend, as we've now
                * considered this part. */
                dividend -= divisor;
            }
            /* Shift the divisor to the right so that it's in the right place
            * for the next positon we're checking at. */
            divisor = (divisor + 1) >> 1;
        }

        /* If there was originally one negative sign, then
        * the quotient remains negative. Otherwise, switch
        * it to positive. */
        if (negatives != 1) {
            quotient = -quotient;
        }
        return quotient;
    }
};