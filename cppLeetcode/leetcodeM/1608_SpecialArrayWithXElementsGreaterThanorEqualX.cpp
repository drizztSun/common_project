/*
1608. Special Array With X Elements Greater Than or Equal X

You are given an array nums of non-negative integers. nums is considered special if there exists a number x such that there are exactly x numbers in nums that are greater than or equal to x.

Notice that x does not have to be an element in nums.

Return x if the array is special, otherwise, return -1. It can be proven that if nums is special, the value for x is unique.

 

Example 1:

Input: nums = [3,5]
Output: 2
Explanation: There are 2 values (3 and 5) that are greater than or equal to 2.
Example 2:

Input: nums = [0,0]
Output: -1
Explanation: No numbers fit the criteria for x.
If x = 0, there should be 0 numbers >= x, but there are 2.
If x = 1, there should be 1 number >= x, but there are 0.
If x = 2, there should be 2 numbers >= x, but there are 0.
x cannot be greater since there are only 2 numbers in nums.
Example 3:

Input: nums = [0,4,3,0,4]
Output: 3
Explanation: There are 3 values that are greater than or equal to 3.
Example 4:

Input: nums = [3,6,7,7,0]
Output: -1
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 1000

*/
#include <vector>
#include <algorithm>

using std::vector;

class SpecialArray {

    /*
            1608.Special-Array-With-X-Elements-Greater-Than-or-Equal-X
        首先我们想一想，为什么该题如果有解，必然是唯一解？假设存在x，满足大于等于x的元素个数是x；另外有一个更大的y，满足大于等于y的元素个数是y。这有什么矛盾呢？矛盾在于，因为x小于y，所以“大于等于x的元素个数”必然多于“大于等于y的元素个数”。然而前者是x，后者是y，前者少于后者，矛盾！

        解法1：二分搜值
        称答案X为数组的“特征值”，那么X的上限就是数组的长度N，因为你不可能有多于N个数字去计数。

        于是我们可以二分搜值X，对于尝试某个特征值x，我们遍历一遍整个数组统计一下大于等于x的个数count。如果count==x，那么就是唯一的答案；如果count>x，那么当前猜测的特征值偏小，使得统计到的数过多，下一次可以猜更大的数；如果count<x，那么当前猜测的特征值偏大，使得统计到的数过少，下一次可以猜更小的数。

        这样的时间复杂度就是 log(N)*N.

        对于有唯一确定解的题目（注意不是有唯一最优解），除了可以沿用我一贯推荐的while(left<=right)模板之外，我们可以用这样的模板：

        while (left<=right)
        {
        mid = ...;
        if (isOK(mid))
            return mid;
        else if (isTooLarge(mid))
            mid = right-1;
        else if (isTooSmall(mid))
            mid = left+1;
        }
        return -1;
        再次强调，上面的模板不适合求最优解（最大/最小）的题目。

        解法2：频率的后缀数组
        考虑到X本身并不大，我们开辟一个数组freq存放每种元素的频次，即freq[i]表示i出现了多少次。特别地，凡是大于等于N的元素，频率都统计在freq[N]里面。

        这样我们从大到小遍历X，遍历的过程中通过累加freq[i]自然而然地就把所有大于等于X的元素的总频次count就统计出来了。只要比较count和X，如果相等就是答案。

        这样的时间复杂度是o(N).
    
    */
    int doit_binary_search(vector<int>& nums) 
    {
        int right = nums.size();
        int left = 1;
        while (left <= right)
        {
            int mid = right-(right-left)/2;
            int count = 0;
            for (auto x: nums)
                if (x>=mid) count++;
            if (count == mid)
                return mid;
            else if (count > mid)
                left = mid+1;
            else
                right = mid-1;
        }
        return -1;
    }

    int doit_index(vector<int>& nums) {
        
        int N = nums.size();
        vector<int>freq(N+1,0);
        for (auto x: nums)
            freq[std::min(x,N)]+=1;

        int count = 0;
        for (int x=N; x>=0; x--) {
            count+=freq[x];                
            if (count == x)
                return x;
        }
        return -1;
    }

public:

    int doit_binary_search(vector<int>& nums) {
        
        std::sort(begin(nums), end(nums));
        std::reverse(begin(nums), end(nums));
        int left = 0, right = nums.front();
        
        while (left <= right) {
        
            int mid = left + (right - left) / 2;
        
            int cnt = 0;
            
            for (auto c : nums) {
                if (c < mid) break;
                cnt++;
            }
            
            if (cnt == mid) return mid;
            
            if (cnt > mid)
                
                left = mid + 1;
            else
                right = mid - 1;
        }
        
        return -1;
    }
};

