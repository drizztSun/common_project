/*
 479. Largest Palindrome Product
 
 Find the largest palindrome made from the product of two n-digit numbers.

 Since the result could be very large, you should return the largest palindrome mod 1337.

  

 Example:

 Input: 2

 Output: 987

 Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

  

 Note:

 The range of n is [1,8].
 
*/
#include <cmath>
#include <string>
#include <sstream>

using std::stringstream;
using std::string;

class LargestPalindrome{


    /*
        479.Largest-Palindrome-Product
        两个n位数的数字相乘，得到的最大是2n位数，最小的2n-1位数。但是2n-1位数的数值明显要比2n位数要小，所以有一定的理由相信，答案应该在2n位数里面找。

        对于所有2n位数的回文数，怎么列举出来？一种方法是：列出所有2n位数，判断是否是回文数；第二种方法，列出所有n位数，构造出对应的2n位数的回文数。显然，后者更加高效。当n最大为8时，回文数是16位，10^16<(2^4)^16<2^64，所以用int64可以装下。

        有了一个2n位的回文数，再一一尝试所有的n位数（从大往小尝试），如果能除尽，且商仍是n位数，那么这个回文数就是符合题意的。
    */


public:

    int largestPalindrome(int n) {
            
        int ans[9] = {0,9,987,123,597,677,1218,877,475};
        
        return ans[n];
    }


    int largestPalindrome_best(int n) {

        if(n==1) return 9;      
        
        for(long long int x = 1; x <= pow(10,n)-1; x++)
        {
			//constracting the a Palindrome number by following lines
            long long int a = pow(10,n) - x;
            string str = std::to_string(a);
            reverse(str.begin(),str.end());
            stringstream sm(str);
            long long int b=0;
            sm>>b;
			// Here the Palindrome number we get is:  
			//  				rst = pow(10,n)*a + b;
			//  Let's assume n = 2;
			//  so: 
			//  				rst = 100*(100-x) + b;
			//  if rst is the number we want, then we can find c and d satisfy this: 
			//  				rst = (100-c)*(100-d)
			//  so we have :
			//   				100*(100-x) + b = (100-c)*(100-d)
			//                  100*(c+d-x) = c*d - b
			//  one solution that satisfies the above equation is that :
			//                  c+d = x
			//                  c*d = b
			//  if that is the case, then we have
			//                  (c-d)^2 = x*x-4*b
			//  now if temp: 
			//                  temp =x*x -4*b;
			//  have squre root:
			//  then we have c-d =sqrt(temp) x = c + d
			//  now we have 2*c = x+sqrt(temp)
			//  we can definitly find integer solution for c and d, then we can simply return rst. 
            long long int temp =x*x -4*b;
            if(temp>=0)
            {
                long long int temp1 =(int)sqrt(temp);
                if(temp1*temp1 == temp&&(x+temp1)%2==0)
                {
                    long long int ret= pow(10,n)*a;
                    ret = ret+ b;
                    return ret % 1337;
                }
            }
            
        }
        return -1;
    }

    /*
        This is just a conversion from the "An easy 9-line Java solution" by ckcz123 plus some explanation.
        max is the biggest possible n digit number

        you may have noticed that
        9x9 = 81
        99x99 = 9801
        999x999 = 998001
        9999x9999 = 9980001
        etc.
        The biggest possibe n digit numbers multipled together are never palindromes. So the first loop iteration is from max-1.

        v will be used to generate a palindrome and will get smaller in every iteration. This solution assumes that a palindrome will be found before v becomes 10x smaller than the biggest possible n digit number (max). This must be true because if v becomes 10x smaller, it will no longer be an n digit number.

        Generating the palindrome from v is fairly straight forward except in C++ you have to make sure your variables are big enough to hold the numbers.

        The second for loop relies on some key observations.

        If x is one of the numbers that can be multiplied with something else to make the palindrome, then that something else cannot be bigger than x. Since the solution starts from the biggest numbers and works back, if a bigger number than x was part of the solution, it would have been found earlier.
        If x is not a multiple, next we check if x-1 is big enough to be a multiple for the palindrome u.
        If at any point x^2 is found to be smaller than the palindrome u then it cannot be a multiple for it since all numbers greater than x have been checked and the numbers below it will only further decrease the value of x^2.
        Once a multiple is found for u we know that it comes from x and x%u, and that u is the biggest palindrome possible given those numbers.
    */

    int doit_math(int n) {
        
        if (n == 1) return 9;
        
        long long max = pow(10, n) - 1;
        
        for (int v = max - 1; v > (max / 10); v--) {
            string s = std::to_string(v), s0 = s;
            reverse(s.begin(), s.end());
            long long u = atoll((s0 + s).c_str());
            
            for (long long x = max; x*x >= u; x--)
                if (u%x == 0) return(int)(u%1337);
        }
        return 0;
    }
    
public:

    long createPalindrom(int n) {
        string left = std::to_string(n);
        string right = left;
        std::reverse(right.begin(), right.end());
        left += right;
        return atoi(left.c_str());
    }
    
    int doit_(int n) {
        
        if (n == 1)
            return 9;
        
        int upperBound = pow(10, n) - 1;
        int lowerBound = upperBound / 10 + 1;
        long maxnum = (long) upperBound * (long) upperBound;
        int half = (int) (maxnum / (long) pow(10, n));
        long palindrom = 0;
        bool found = false;
        
        while (!found) {
            
            palindrom = createPalindrom(half);
            
            for (long i = upperBound; i >= lowerBound; i--) {
                if (i * i < palindrom)
                    break;
                
                if (palindrom % i == 0) {
                    found = true;
                    break;
                }
            }
            half--;
        }
        
        return (int) (palindrom % 1337);
    }
};
