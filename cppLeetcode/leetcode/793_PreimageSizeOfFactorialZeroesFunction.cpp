/*
793. Preimage Size of Factorial Zeroes Function

Let f(x) be the number of zeroes at the end of x!. (Recall that x! = 1 * 2 * 3 * ... * x, and by convention, 0! = 1.)

For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) = 2 because 11! = 39916800 has 2 zeroes at the end. Given K, find how many non-negative integers x have the property that f(x) = K.

Example 1:
Input: K = 0
Output: 5
Explanation: 0!, 1!, 2!, 3!, and 4! end with K = 0 zeroes.

Example 2:
Input: K = 5
Output: 0
Explanation: There is no x such that x! ends in K = 5 zeroes.
Note:

K will be an integer in the range [0, 10^9].
*/


class PreimageSizeFZF {

    /*
        793.Preimage-Size-of-Factorial-Zeroes-Function
        此题需要注意，并不是一定存在x使得f(x)=K。比如f(24)=4，但是f(25)=6，因此不存在任何f(x)=5。因此我们可以用二分搜索的方法尝试找到最小的x，满足f(x)==K。如果能找到，那么就直接返回5，这是因为x之后的x+1,x+2,x+3,x+4必定都不含质因数5，而x+5必定会包含新的质因数5从而增加至少一个trailing zero。反之，如果二分搜索找不到，那么就返回0.

        如何写f(x)呢？考虑将x!按顺序每5个分一组，就会有一个因数含有一个5；将x!按顺序每25个分一组，就会有一个因数含有两个5；将x!按顺序每125个分一组，就会有一个因数含有三个5。以此类推，可以知道f(x) = x/5 + x/25 + x/125 + ...

        因为K可以达到1e9，因此由上面的公式可知，二分搜索的上限应该设置为5e9，需要用到long类型。
    */
    int doit_binary_search(int K) 
    {
        long left = 1;
        long right = 5e9;
        
        while (left<right)
        {
            long mid = left+(right-left)/2;
            
            if (countTrailingZeros(mid) < K)
                left = mid+1;
            else if (countTrailingZeros(mid) > K)
                right = mid-1;
            else
                right = mid;
        }
        
        if (left>right) return 0;
        if (left==right && countTrailingZeros(left)==K)
            return 5;
        else
            return 0;
    }
    
    long countTrailingZeros(long x)
    {
        long count = 0;
        for (long i=5; i<=x; i=i*5)
            count += x/i;
        return count;
    }

public:

    /*
        Approach #1: Binary Search [Accepted]
        Intuition and Algorithm

        Let zeta(x) be the number of zeroes at the end of x!. If the prime factorization of x! is (2^a * 5^b * ....), then the number of times that 10 divides this is min(a, b) which is b.

        Thus, zeta(x) is the number of times 5 divides x!, which is equal to [x/5] + [x/5^2] + .....

        Indeed, zeta is a monotone increasing function, so we can binary search for the answer. Our technique follows the same approaches in many other binary search problems.

        We could binary search for both the largest and smallest value x such that zeta(x) = K. However, since zeta(5a-1) < zeta(5a) = zeta(5a+1) = zeta(5a+2) = zeta(5a+3) = zeta(5a+4) < zeta(5a+5), if it is possible for zeta(x) to equal K for some x, then the answer is 5, else the answer is 0.


        Complexity Analysis

        Time Complexity: O(log(k)^2). Our binary search is O(logK), and in each step of that binary search we do O(logK) work to evaluate the function zeta.

        Space Complexity: O(logK), the size of our recursive call stack when calling zeta.
    */
    int doit_binary_search(int K) {

        long long low = K, high = 10*static_cast<long>(K) + 1;

        auto find = [](long x) {

            long cnt = 0;
            while (x/5) {
                cnt += x/5;
                x /= 5;
            }
            return cnt;
        };
        
        while (low < high) {

            long mid = (low + high) / 2;
            long cnt = find(mid);

            if (cnt == K) return 5;

            if (cnt > K)
                high = mid;
            else
                low = mid + 1;
        }

        return 0;
    }
};