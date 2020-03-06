/*
 
 # 1006. Clumsy Factorial

 # Normally, the factorial of a positive integer n is the product of all positive integers less than or equal to n.
 # For example, factorial(10) = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1.

 # We instead make a clumsy factorial: using the integers in decreasing order, we swap out the multiply operations for a fixed rotation of operations:
 # multiply (*), divide (/), add (+) and subtract (-) in this order.

 # For example, clumsy(10) = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1.
 # However, these operations are still applied using the usual order of operations of arithmetic:
 # we do all multiplication and division steps before any addition or subtraction steps, and multiplication and division steps are processed left to right.

 # Additionally, the division that we use is floor division such that 10 * 9 / 8 equals 11.  This guarantees the result is an integer.

 # Implement the clumsy function as defined above: given an integer N, it returns the clumsy factorial of N.


 # Example 1:

 # Input: 4
 # Output: 7
 # Explanation: 7 = 4 * 3 / 2 + 1

 # Example 2:

 # Input: 10
 # Output: 12
 # Explanation: 12 = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1
 
 
 */


class Clumsy {
    
public:
    
    int doit(int N) {
        
        int rem[4] = {1, 2, 2, -1};
        
        if (N < 3)
            return N;
        
        if (N < 5)
            return N + 3;
        
        return N + rem[N % 4];
    }
    
    int doit1(int N) {
        
        if (N < 3)
            return N;
        
        int ans = N * (N-1) / (N-2);
        int i = N % 4;
        N -= 3;
        
        while (N > 3) {
            ans += N--;
            ans -= N * (N-1) / (N-2);
            N -= 3;
        }
        
        if (i < 3) {
            ans++;
        }
        
        return ans;
    }
    
    int doit2(int N) {
           if (N == 1)
               return 1;
           if (N == 2)
               return 2 * 1;

           int ret = N * (N - 1) / (N - 2);
           N -= 3;
           
           // treat 4 consecutive numbers as one group
           while (N >= 4) {
               ret += N - (N - 1) * (N - 2) / (N - 3);
               N -= 4;
           }

           switch (N) {
           case 1: ret += 1; break;
           case 2: ret += 2 - 1; break;
           case 3: ret += 3 - 2 * 1; break;
           }
           return ret;
       }
};

void test_1006_clumsy_factorial() {
    
    
    auto res1 = Clumsy().doit(4);
    
    auto res2 = Clumsy().doit(10);
}
