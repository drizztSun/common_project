/*
1802. Maximum Value at a Given Index in a Bounded Array

You are given three positive integers n, index and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:

.nums.length == n
.nums[i] is a positive integer where 0 <= i < n.
.abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
.The sum of all the elements of nums does not exceed maxSum.
.nums[index] is maximized.

Return nums[index] of the constructed array.

Note that abs(x) equals x if x >= 0, and -x otherwise.

 

Example 1:

Input: n = 4, index = 2,  maxSum = 6
Output: 2
Explanation: The arrays [1,1,2,1] and [1,2,2,1] satisfy all the conditions. There are no other valid arrays with a larger value at the given index.
Example 2:

Input: n = 6, index = 1,  maxSum = 10
Output: 3
 

Constraints:

1 <= n <= maxSum <= 10^9
0 <= index < n

*/


class MaxValue {

    /*
        1802.Maximum-Value-at-a-Given-Index-in-a-Bounded-Array
        本题很容易想到贪心的策略。既然要使得所用的数字总和不超过maxSum，那我们就省着用。怎么用呢？令index那个位置最高，然后往两边依次递减，每移一个位置就减1。直至递减到1之后，如果还需要再往两边延伸的话，就继续维持1。这个方案是固定index的高度，同时满足所有条件下、数字总和最小的决策。
        反之，如果固定数字总和，那么这个方案就是满足所条件下、index位置最高的决策。

        我们用二分搜值的方法，探索index位置的高度。假设当高度为h时，判断该贪心决策所需要的数字总和是否小于等于maxSum。是的话，那么h可能是解，但还可以往大猜；反之，那么h不是解，且必须往小猜。

        在检验函数中，我们需要考虑两个等差数列。前者从index位置的h，往前逐位递减，直至递减至1或者数组的第一个位置；后者从index位置的h，往后逐位递减，直至递减至1或者数组的最后位置。计算两个等差数列之和。另外注意，等差数列降至1时，如果还有元素需要填充1，那么需要正确计算它们的个数。
    */
    int binary_search(int n, int index, int maxSum) 
    {
        int left = 1, right = maxSum;
        while (left < right)
        {
            int mid = right - (right-left)/2;
            if (count(mid, n, index) <= (long)maxSum)
                left = mid;
            else
                right = mid - 1;
        }
        return left;        
    }
    
    long count(long h, long n, long index)
    {
        long sum = 0;
        if (h > index)
        {
            sum += (h-index + h)*(index+1)/2;
        }
        else
        {
            sum += (1+h)*h/2;
            sum += index+1-h;
        }
        if (h > n-index)
        {
            sum += (h + h-(n-index)+1)*(n-index)/2;
        }
        else
        {
            sum += (h + 1)*h/2;
            sum += (n - (index+h));
        }
        return sum-h;
    }

public:

    /*
        Explanation
        We first do maxSum -= n,
        then all elements needs only to valid A[i] >= 0

        We binary search the final result between left and right,
        where left = 0 and right = maxSum.

        For each test, we check minimum sum if A[index] = a.
        The minimum case would be A[index] is a peak in A.
        It's arithmetic sequence on the left of A[index] with difference is 1.
        It's also arithmetic sequence on the right of A[index] with difference is -1.

        On the left, A[0] = max(a - index, 0),
        On the right, A[n - 1] = max(a - ((n - 1) - index), 0),

        The sum of arithmetic sequence {b, b+1, ....a},
        equals to (a + b) * (a - b + 1) / 2.


        Complexity
        Because O(test) is O(1)
        Time O(log(maxSum))
        Space O(1)


        More Good Binary Search Problems
        Here are some similar binary search problems.
        Also find more explanations.
        Good luck and have fun.

        1802. Maximum Value at a Given Index in a Bounded Array
        1539. Kth Missing Positive Number
        1482. Minimum Number of Days to Make m Bouquets
        1283. Find the Smallest Divisor Given a Threshold
        1231. Divide Chocolate
        1011. Capacity To Ship Packages In N Days
        875. Koko Eating Bananas
        774. Minimize Max Distance to Gas Station
        410. Split Array Largest Sum
    */
    int doit_binary_search(int n, int index, int maxSum) {
        maxSum -= n;
        int left = 0, right = maxSum, mid;

        auto test = [](int n, int index, int a) {
            int b = std::max(a - index, 0);
            long res = long(a + b) * (a - b + 1) / 2;
            b = std::max(a - ((n - 1) - index), 0);
            res += long(a + b) * (a - b + 1) / 2;
            return res - a;
        };
        
        while (left < right) {
            mid = (left + right + 1) / 2;
            if (test(n, index, mid) <= maxSum)
                left = mid;
            else
                right = mid - 1;
        }
        return left + 1;
    }
};