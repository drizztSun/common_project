/*
668. Kth Smallest Number in Multiplication Table


Nearly every one have used the Multiplication Table. But could you find out the k-th smallest number quickly from the multiplication table?

Given the height m and the length n of a m * n Multiplication Table, and a positive integer k, you need to return the k-th smallest number in this table.

Example 1:
Input: m = 3, n = 3, k = 5
Output: 
Explanation: 
The Multiplication Table:
1	2	3
2	4	6
3	6	9

The 5-th smallest number is 3 (1, 2, 2, 3, 3).
Example 2:
Input: m = 2, n = 3, k = 6
Output: 
Explanation: 
The Multiplication Table:
1	2	3
2	4	6

The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).
Note:
The m and n will be in the range [1, 30000].
The k will be in the range [1, m * n]

*/


class KthSmallestNum {

	/*
				668.Kth-Smallest-Number-in-Multiplication-Table
		此题非常巧妙地用到了二分（值）查找的思想。

		初始状态left=1,right=n*m，每次确定mid之后，计算乘法表里小于等于mid的数目。这只要按照行i=1:m进行遍历就行，count+=min(mid/i,n)。(注意有一个上限n)

		如果得到的count<k，那么显然这个mid太小，不满足条件，需要上调左边界，即left=mid+1；反之，count>=k的话，则说明这个mid可能太大但也可能正好就是答案（例如有很多重复的mid），无法确定，因此可以将其纳入右边界（闭区间），即right=mid，（因为答案不可能比mid更大了）。

		这种二分逼近得到的结果 x 是什么呢？得到的是乘法表里小于等于x的元素个数不少于k的、且最小的那个数字。这其实就是待求的第k个元素。

		但注意有一个问题需要考虑，最终左右指针相遇得到这个数x一定会是出现在乘法表里的吗？表面上看不出来，但答案是肯定的。这是因为满足“乘法表里小于等于x的元素个数不少于k的”，这样的x可能会有很多，但最小的那个一定是出现在乘法表里的。

		PS: 本题本质上和 378. Kth Smallest Element in a Sorted Matrix一模一样。
	*/
	int doit_binary_search(int m, int n, int k) 
    {
        int left=1;
        int right=m*n;
        int mid;
        
        while (left<right)
        {
            mid=left+(right-left)/2;
            
            int count=0;
            for (int i=1; i<=m; i++)
                count+= std::min(mid/i,n);
            if (count<k)
                left=mid+1;
            else
                right=mid;
        }
        
        return left;
    }

public:

	int doit_binary_search(int m, int n, int k) {

        int left = 1, right = m * n;
        
        auto count = [&](int mid) -> int {
        
            int i = m, j = 1;
            int cnt = 0;
            while (i >= 1 && j <= n) {
                
                if (i*j <= mid) {
                    cnt += i;
                    j++;
                } else
                    i--;
            }
            
            return cnt;
        };
        
        while (left < right) {
            
            int mid = left + (right - left) / 2;
            //int count=0;
            //for (int i=1; i<=m; i++)
            //    count+= std::min(mid/i,n);
            
            if (count(mid) < k)
                left = mid + 1;
            else
                right = mid;
        }
        
        return left;
    }

	/*
	
		Approach #3: Binary Search [Accepted]

		Intuition
		As k and m*n are up to 9 * 10^8, linear solutions will not work. This motivates solutions with \loglog complexity, such as binary search.

		Algorithm

		Let's do the binary search for the answer A.

		Say enough(x) is true if and only if there are \text{k}k or more values in the multiplication table that are less than or equal to \text{x}x. Colloquially, enough describes whether \text{x}x is large enough to be the k^{th}k 
		th
		value in the multiplication table.

		Then (for our answer \text{A}A), whenever \text{x ≥ A}, enough(x) is True; and whenever \text{x < A}x < A, enough(x) is False.

		In our binary search, our loop invariant is enough(hi) = True. At the beginning, enough(m*n) = True, and whenever hi is set, it is set to a value that is "enough" (enough(mi) = True). That means hi will be the lowest such value at the end of our binary search.

		This leaves us with the task of counting how many values are less than or equal to \text{x}x. For each of \text{m}m rows, the i^{th}i 
		th
		row looks like \text{[i, 2*i, 3*i, ..., n*i]}[i, 2*i, 3*i, ..., n*i]. The largest possible \text{k*i ≤ x} that could appear is \text{k = x // i}k = x // i. However, if \text{x}x is really big, then perhaps \text{k > n}k > n, so in total there are \text{min(k, n) = min(x // i, n)}min(k, n) = min(x // i, n) values in that row that are less than or equal to \text{x}x.

		After we have the count of how many values in the table are less than or equal to \text{x}x, by the definition of enough(x), we want to know if that count is greater than or equal to \text{k}k.

		Complexity Analysis

		Time Complexity: O(m∗log(m∗n)). Our binary search divides the interval \text{[lo, hi]}[lo, hi] into half at each step. At each step, we call enough which requires O(m)O(m) time.

		Space Complexity: O(1). We only keep integers in memory during our intermediate calculations.
	*/
	int doit_binary_search(int m, int n, int k) {

		int lo = 1, hi = m * n;

		while (lo < hi) {

			int mid = lo + (hi - lo) / 2, num = 0;

			for (int i = 1; i <= m; i++)
				num += std::min(mid / i, n);

			if (num < k)
				lo = mid + 1;
			else
				hi = mid;
		}

		return lo;
	}
};