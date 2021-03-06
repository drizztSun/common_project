/*
779. K-th Symbol in Grammar


On the first row, we write a 0. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.

Given row N and index K, return the K-th indexed symbol in row N. (The values of K are 1-indexed.) (1 indexed).

Examples:
Input: N = 1, K = 1
Output: 0

Input: N = 2, K = 1
Output: 0

Input: N = 2, K = 2
Output: 1

Input: N = 4, K = 5
Output: 1

Explanation:
row 1: 0
row 2: 01
row 3: 0110
row 4: 01101001
Note:

N will be an integer in the range [1, 30].
K will be an integer in the range [1, 2^(N-1)].

*/



class KthGrammar {

    /*
        779.K-th-Symbol-in-Grammar
        此题是典型的递归解法。第N行的第K个，取决于第N-1行的第(K+1)/2个。于是依次往上回溯，直至追踪到第N==1行的元素是0.
    */
    
public:

    int doit_search(int N, int K) {

        




    } 


    /*
        if K % 2 == 1, it is the first number in '01' or '10',
        if Kth number is 0, K+1 th is 1.
        if Kth number is 1, K+1 th is 0.
        so it will be different from K + 1.

        If K % 2 == 0, it is the second number in '01' or '10', generated from K/2 th number.
        If Kth number is 0, it is generated from 1.
        If Kth number is 1, it is generated from 0.
    */
    int doit_search(int N, int K) {
        int res = 0;
        while (K > 1) {
            K = K % 2 == 1 ? K + 1 : K / 2;
            res ^= 1;
        }
        return res;
    }

    /*
        Explanation
        First, you can easily find that prefix of every row is exactly the same.
        It not difficult to understand.
        Beacause every 2 * L fisrt letters are generated by the same L fist letters.

        Then, we know that every row is the start part of the same long sequence.
        Moreover K is guaranteed to be an integer in the range[1, 2 ^ (N - 1)].
        So result depends only on value K

        Suppose 2^L < K <= 2^(L + 1).
        2^L is the biggest 2's power smaller than K.
        Kth number is generated from K - 2^L
        Kth number is also different from K - 2^L
        So we toggle K to K - 2^L by subtracting 2^L

        We repeat the process until we toggle K to 1,
        which mean we need to substract K - 1 in total.

        What we should do is transfer K - 1 in binary,
        so that we can easily find how many times we need to toggle.


        Example
        For example K = 8
        we need to substract K - 1 = 7 = 111 in binary.
        So we need to substract 100, 10 and 1, which are 4, 2, 1 in decimal.
        We toggle K from 8 to 4, 2 and finally 1.

        For example K = 9
        we need to substract K - 1 = 8 = 1000 in binary.
        So we need to substract 1000, which is 8 in decimal.
        We toggle K from 9 to 1 directly.


        Conclusion
        we turn this problem to just count 1 bits.
        We can observe that the answer depend on whether the number of 1 bits in binary K - 1 is odd or even.

        Now you may have many ways to solve this problem.
        In Python, bin transform it into binary directly.
        In Java, build-in method Integer.bitCount is ready for use.
        In C++, I use the trick K & (K - 1) to drops the lowest bit.


        Complexity
        Time O(logN)
        Space O(1)


        More
        Here is another idea
        https://leetcode.com/problems/k-th-symbol-in-grammar/discuss/121544/C++JavaPython-Another-Solution
    */
    int kthGrammar(int N, int K) {
        int n;
        for (n = 0, K -= 1; K ; K &= (K - 1)) n++;
        return n & 1;
    }
};