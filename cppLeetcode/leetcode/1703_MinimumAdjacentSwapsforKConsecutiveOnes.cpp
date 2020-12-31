/*
1703. Minimum Adjacent Swaps for K Consecutive Ones

You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In one move, you can choose two adjacent indices and swap their values.

Return the minimum number of moves required so that nums has k consecutive 1's.

 

Example 1:

Input: nums = [1,0,0,1,0,1], k = 2
Output: 1
Explanation: In 1 move, nums could be [1,0,0,0,1,1] and have 2 consecutive 1's.
Example 2:

Input: nums = [1,0,0,0,0,0,1,1], k = 3
Output: 5
Explanation: In 5 moves, the leftmost 1 can be shifted right until nums = [0,0,0,0,0,1,1,1].
Example 3:

Input: nums = [1,1,0,1], k = 2
Output: 0
Explanation: nums already has 2 consecutive 1's.
 

Constraints:

1 <= nums.length <= 105
nums[i] is 0 or 1.
1 <= k <= sum(nums)




*/
#include <vector>
#include <algorithm>
using std::vector;

class MinimumAdjacentSwapKConsecutiveOnes {

public:

    /*
    Short Explanation
    Find all index of nums[i] if nums[i] == 1.
    Now the problem changes to find k consecute element in A, that has minimum distance to their median sequence.
    To solve this, we need to use the prefix sum of A, which is B in this solution.

    Complexity
    Time O(n)
    Space O(n)
    */
    int doit_slidingwindows(vector<int>& nums, int k) {

        vector<long> pos;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1)
                pos.push_back(i);
        }

        long n = pos.size(), res = 2e9;
        vector<long> B(1);
        for (int i = 0; i < n; i++) {
            B.push_back(B[i] + pos[i]);
        }

        /*
        B[i + k] - B[k / 2 + i] - B[(k + 1) / 2 + i] + B[i])
        (B[i + k] - B[(k + 1) / 2 + i]) - (B[k / 2 + i] - B[i]);

        example indices (A):
        [0 3 5 6 7 9 10]
        mid = 6
        sum before mid => (6 - 6 - 0) + (6 - 3 - 1) + (6 - 5 - 2) + (6 - 0 - 3)
        => 6 * 4 - (0 + 3 + 5 + 6) - (0 + 1 + 2 + 3)

        sum after mid => (6 - 6 - 0) + (7 - 6 - 1) + (9 - 6 - 2) + (10 - 6 - 3)
        => (6 + 7 + 9 + 10) - 6 * 4 - (0 + 1 + 2 + 3)

        before + after => (6 + 7 + 9 + 10) - (0 + 3 + 5 + 6) - 2 * (1+2+3)
        => A[3]->A[6] - A[0]->A[3] - 2 * (3)(3+1) / 2
        => (B[7] - B[3]) - (B[4] - B[0]) - (k//2)*((k+1)//2)
        */

        for (int i = 0; i < n-k+1; i++) {
            
            // B[i + k] - B[k / 2 + i] - B[(k + 1) / 2 + i] + B[i])
            res = std::min(res, B[i+k] - B[k/2 + i] - B[(k+1)/2 + i] + B[i]);
        }

        res -= (k / 2) * ((k+1/2));
        return res;
    }

    /*
        1703.Minimum-Adjacent-Swaps-for-K-Consecutive-Ones
        首先我们要有这样的意识：想要以最少的操作把k个1靠拢，显然这个k个1必然是在原数组中相邻的（刨除零元素）。所以我们先构造一个新数组p，里面的元素就是原数组中所有1的位置。接下来我们就在数组p中考察所有长度为k的滑窗。在每个滑窗里，我们有k个离散的位置点，我们的任务是研究如何用最少的操作，得到k个连续的位置。

        此时我们会想到一个类似的问题。我们有k个离散点的位置，如何确定一个中心位置x，使得所有k个点离x的距离之和最短？这个问题就是296.Best-Meeting-Point，答案是，“中心”应该选在这k个点的中位数处。此时的总距离total = sum |pi-x|, i=0,1,..,k-1能够最小。

        我们再切回之前所考虑的问题，我们不是把所有的点都移到“中心”位置x，而是把所有的点移到以x为中心的连续k个位置。因此我们最小化的是 sum |pi-x| (for i=0,1,..,k-1) - sum|i-k/2| (for i=0,1,..,k-1) . 我们发现第二项其实是一个常数。所以本题的最优解其实和LC296是一样：最佳的“中心”位置依然是所有点的中位数。

        因此，回到我们最初所考虑的第一个滑窗，对于p[0]~p[k-1]这k个位置的点，我们的目的应该把它们移动到[p[k/2] - k/2, p[k/2]+k/2-1]这个区间。为了计算方便，我们省略掉上一段里面的第二项，只考虑把它们都移动到p[k/2]所需要的操作总数。这个是很容易算的，记做是sum。

        接下来我们看从第一个滑窗到第二个滑窗的变化：原先的k个位置是p[0]~p[k-1]，中心是在p[mid]；滑动之后的k个位置是p[1]~p[k]，中心是在p[mid+1]。

        0  1  2 mid .  . k-1 k
        X  X  X  O  X  X  X
        X  X  X  O  X  X  X
        相应地，操作总数sum的变化有四个部分：

        原先p[0]在滑窗里，贡献了p[mid]-p[0]这么多操作。现在要减去他们。
        原先p[k]不在滑窗里，现在加入了滑窗，需要加上它的贡献p[k]-p[mid+1]
        原先p[1]~p[mid]到中心p[mid]的距离，现在都变成了p[1]~p[mid]到新中心p[mid+1]的距离，每个数到新中心都多出了p[mid+1]-p[mid]，所以我们需要把sum补上(p[mid+1]-p[mid])*(k/2)
        原先p[mid+1]~p[k-1]到中心p[mid]的距离，现在都变成了p[mid+1]~p[k-1]到新中心p[mid+1]的距离，每个数到心中都减少了p[mid+1]-p[mid]，所以我们需要把sum扣除(p[mid+1]-p[mid])*(k-k/2-1)
        可见，我们将第一个滑窗的sum，通过四步o(1)的修正，就可以到第二个滑窗的sum。我们将滑窗走一遍，就可以得到最小的sum。注意，最后的答案是把最小的sum减去常数项 sum|i-k/2|.
    */
   int doit_slidingwindows_2(vector<int>& nums, int k) 
    {
        vector<int>p;
        for (int i=0; i<nums.size(); i++)
            if (nums[i]==1)
                p.push_back(i);
        
        int sum = 0;
        for (int i=0; i<k; i++)
            sum += abs(p[i]-p[k/2]);
        int ret = sum;

        for (int i=0; i+k<p.size(); i++)
        {            
            int mid = i+k/2;
            sum -= abs(p[i]-p[mid]);
            sum += abs(p[mid+1]-p[mid]) * (k/2);
            sum += abs(p[i+k] - p[mid+1]);
            sum -= abs(p[mid+1]-p[mid]) * (k-k/2-1);
            ret = std::min(ret, sum);
        }

        int offset = 0;
        for (int i=0; i<k; i++)
            offset += abs(i-k/2);

        return ret-offset;
    }
};