/*
1231. Divide Chocolate


You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given by the array sweetness.

You want to share the chocolate with your K friends so you start cutting the chocolate bar into K+1 pieces using K cuts, each piece consists of some consecutive chunks.

Being generous, you will eat the piece with the minimum total sweetness and give the other pieces to your friends.

Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.

 

Example 1:

Input: sweetness = [1,2,3,4,5,6,7,8,9], K = 5
Output: 6
Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]
Example 2:

Input: sweetness = [5,6,7,8,9,1,2,3,4], K = 8
Output: 1
Explanation: There is only one way to cut the bar into 9 pieces.
Example 3:

Input: sweetness = [1,2,2,1,2,2,1,2,2], K = 2
Output: 5
Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]
 

Constraints:

0 <= K < sweetness.length <= 10^4
1 <= sweetness[i] <= 10^5

*/

#include <vector>
#include <numeric>

using std::vector;


class DicideChocolate {

    /*
        1231.Divide-Chocolate
        很容易感觉出来，如果 minimum total sweetness 的要求越低，那么就越容易实现。
        极端的例子就是取数组中的最小元素为要求的甜度，那么无论怎么切，每一份的甜度都肯定是大于最小元素值的。反之，如果 minimum total sweetness 的要求越高，那么就越不容易实现。
        于是这就是典型的二分搜值的应用场景。只要猜测一个给定甜度值t，查验在数组中是否至少能拆分出k+1个subarray的和大于t。可以的话，那么可以猜更大的t，反之就猜测更小的t。
    */
    int maximizeSweetness(vector<int>& sweetness, int K) 
    {
        int sum = 0;
        for (auto x: sweetness)
            sum+=x;
        
        int left = 0;
        int right = sum;
        
        while (left<right)
        {
            int mid = left+(right-left+1)/2;
            if (ok(sweetness, mid, K))
                left = mid;
            else
                right = mid-1;
        }
        
        return left;
    }
    
    bool ok(vector<int>& sweetness, int S, int K)
    {
        int sum = 0;
        int count = 0;
        for (int i=0; i<sweetness.size(); i++)
        {
            sum+=sweetness[i];
            if (sum>=S)
            {
                sum = 0;
                count++;
            }
        }
        return count>=K+1;
    }

    /*
        Please reply and upvote now.
        Don't have prime membership.
        Cannot even read and modify my own post later, when it's locked.


        Explanation
        We want to maximize the minimum sweetness.
        Binary search the result between 1 and 10^9.

        Don'e explain binary search too much again and again.
        Please find more related explanation in More.
        Also will explain it more in details on youtube lee215.

        Time O(Nlog(10^9))
        Space O(1)
    */
    int binary_search(vector<int>& A, int K) {
        int left = 1, right = 1e9 / (K + 1);
        while (left < right) {
            int mid = (left + right + 1) / 2;
            int cur = 0, cuts = 0;
            for (int a : A) {
                if ((cur += a) >= mid) {
                    cur = 0;
                    if (++cuts > K) break;
                }
            }
            if (cuts > K)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

public:
    
    int doit_binary_search(vector<int>& sweetness, int K) {

        int left = 0, right = std::accumulate(begin(sweetness), end(sweetness), 0);
        int ans = 0;
        
        while (left < right) {

            int mid = right - (right - left) / 2;
            int total = 0, cnt = 0, minv = INT_MAX;

            for (auto c : sweetness) {
                total += c;
                if (total >= mid) {
                    minv = std::min(minv, total);
                    cnt++;
                    total = 0;
                }
            }
            
            if (cnt >= K+1) {
                ans = std::max(ans, minv);
                left = mid;
            }
            else
                right = mid - 1;

        }
        
        return ans;
    }
};
