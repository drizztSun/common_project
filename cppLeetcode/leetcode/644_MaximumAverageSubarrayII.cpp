/*
643. Maximum Average Subarray I

Given an array consisting of n integers, find the contiguous subarray of given length k that has the maximum average value. And you need to output the maximum average value.

Example 1:

Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation: Maximum average is (12-5-6+50)/4 = 51/4 = 12.75
 

Note:

1 <= k <= n <= 30,000.
Elements of the given array will be in the range [-10,000, 10,000].
*/
#include <vector>

class MaximumAverageSubarrayI {
public:
    double doit_slidingwindow(vector<int>& nums, int k) {
        
        double total = 0.0;
        double res = INT_MIN;
        
        for (int i = 0; i < nums.size(); i++) {
            
            total += nums[i];
            
            if (i > k - 1) total -= nums[i-k];
            
            if (i >= k-1) res = std::max(res, total);
        }
        
        return res / k;
    }
};

/*
644. Maximum Average Subarray II

You are given an integer array nums consisting of n elements, and an integer k.

Find a contiguous subarray whose length is greater than or equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.

 

Example 1:

Input: nums = [1,12,-5,-6,50,3], k = 4
Output: 12.75000
Explanation:
- When the length is 4, averages are [0.5, 12.75, 10.5] and the maximum average is 12.75
- When the length is 5, averages are [10.4, 10.8] and the maximum average is 10.8
- When the length is 6, averages are [9.16667] and the maximum average is 9.16667
The maximum average is when we choose a subarray of length 4 (i.e., the sub array [12, -5, -6, 50]) which has the max average 12.75, so we return 12.75
Note that we do not consider the subarrays of length < 4.
Example 2:

Input: nums = [5], k = 1
Output: 5.00000
 

Constraints:

n == nums.length
1 <= k <= n <= 10^4
-10^4 <= nums[i] <= 10^4

*/


#include <vector>
#include <numeric>

using std::vector;


class MaximumAverageSubarrayII {

public:

    /*
        644.Maximum-Average-Subarray-II
        解法1
        首先最基本o(N^2)的思路要搞清楚。设置两层循环，第一层控制subarray的尾元素位置，第二层控制subarray的首元素位置

        for (int i=k; i<nums.size(); i++)
        for (int j=0; j<=i-k+1; j++)
        {
            考察 nums[j]~nums[i]这个subarray的平均值，更新全局最大。
        }
        可见第二重循环有点大，把所有大于等于K程度的subarray都遍历了一遍。能否利用之前的信息呢？比如，若知道了nums[i-1]的最优解，对于解nums[i]的最优解有什么帮助呢？这种思想很像是DP了。

        我们考虑如果已经找到了nums[i-1]的最优解：即以nums[i-1]为尾元素、长度为len的subarray，是所有这种这种subarray里均值最大的情况。这说明什么？说明处于len长度之前的那些元素是拖后腿的！
        它们会拉低以nums[i-1]为尾元素的subarray的均值，同样也会拉低以nums[i]为尾元素的subarray的均值。所以说，第二重循环我么不需要从0开始找。根据nums[i-1]最优解对应的subarray队首开始找就行了。

        for (int i=k; i<nums.size(); i++)
        {
        for (int j=i-dp[i-1]; j<=i-k+1; j++)
        {
            考察 nums[j]~nums[i]这个subarray的平均值，更新全局最大。
        }
        dp[i] = ...
        }
        解法2
        上述的解法在lintcode中仍然会超时。下面介绍一个非常巧妙的二分搜索法。

        显然二分搜索的上限就是nums里的最大值，下限就是nums里的最小值。我们每次通过low和high确定一个mid，查找nums里是否存在一个子数组是的其平均值大于mid。如果有，那么我们就调高下限至mid；如果没有，我们就降低上限至mid

        但是我们如何知道是否存在一个子数组，其平均值大于mid呢？如果我们将这个数组整体都减去mid，那么任务就等价于找到一个平均值大于零的子数组，也就是是说，找到一个和为正数的子数组。

        如何确认一个数组里有一段子数组的和为正数呢？我们只要遍历一遍前缀和，发现curSum[i]>preMin即说明存在。这里的preMin就是在i之前的最小的前缀和。可见只要o(n)的搜索就可以完成判断。总体的时间长度就是o(NlogK)，其中K是nums最大最小值之差。
    
    */
    double findMaxAverage(vector<int>& nums, int k) 
    {
        
        vector<int>cumSum(nums.size()+1);
        cumSum[0]=0;
        for (int i=1; i<=nums.size(); i++)
            cumSum[i]=cumSum[i-1]+nums[i-1];

        vector<int>dp(nums.size()+1);
        dp[k]=1;               
        double result=(cumSum[k]-cumSum[0])*1.0/k;
        
        for (int i=k+1; i<=nums.size(); i++)
        {
            double maxAvg=INT_MIN;
            
            for (int j=dp[i-1]; j<=i-k+1; j++)
            {
                double avg= (cumSum[i]-cumSum[j-1])*1.0/(i-j+1);
                if (avg>maxAvg)
                {
                    maxAvg=avg;
                    dp[i]=j;
                }
                if (avg>result)
                    result=avg;
                
                // cout<<avg<<endl;
            }
        }
        
        return result;
    }

    double doit_binary_search(vector<int>& nums, int k) 
    {
        double low = INT_MAX, high = INT_MIN;
        for (int i:nums)
        {
            low = std::min((int)low,i);
            high = std::max((int)high,i);
        }

        auto check = [&](double avg, int k)
        {
            int N = nums.size();
            vector<double> prefixSum(N+1,0);
            
            for (int i=1; i<k; i++)
                prefixSum[i] = prefixSum[i-1]+nums[i-1]-avg;

            double preMin = 0;
            
            for (int i=k; i<=N; i++)
            {
                prefixSum[i] = prefixSum[i-1]+nums[i-1]-avg;
                
                if(prefixSum[i] > preMin) 
                    return true;
                preMin = std::min(preMin, prefixSum[i-k+1]);
            }
            return false;
        };
    
        while (high-low>1e-6)
        {
            double mid = (high-low)/2+low;
            
            if (check(mid, k))
                low = mid;
            else
                high = mid;            
        }
        
        return high;
    }

    /*
        Approach #2 Using Binary Search [Accepted]
Algorithm

To understand the idea behind this method, let's look at the following points.

Firstly, we know that the value of the average could lie between the range (min, max)(min,max). Here, minmin and maxmax refer to the minimum and the maximum values out of the given numsnums array. This is because, the average can't be lesser than the minimum value and can't be larger than the maximum value.

But, in this case, we need to find the maximum average of a subarray with atleast kk elements. The idea in this method is to try to approximate(guess) the solution and to try to find if this solution really exists.

If it exists, we can continue trying to approximate the solution even to a further precise value, but choosing a larger number as the next approximation. But, if the initial guess is wrong, and the initial maximum average value(guessed) isn't possible, we need to try with a smaller number as the next approximate.

Now, instead of doing the guesses randomly, we can make use of Binary Search. With minmin and maxmax as the initial numbers to begin with, we can find out the midmid of these two numbers given by (min+max)/2(min+max)/2. Now, we need to find if a subarray with length greater than or equal to kk is possible with an average sum greater than this midmid value.

To determine if this is possible in a single scan, let's look at an observation. Suppose, there exist jj elements, a_1, a_2, a_3..., a_ja 
1
​	
 ,a 
2
​	
 ,a 
3
​	
 ...,a 
j
​	
  in a subarray within numsnums such that their average is greater than midmid. In this case, we can say that

(a_1+a_2+ a_3...+a_j)/j ≥ mid or

(a_1+a_2+ a_3...+a_j) ≥ j*mid or

(a_1-mid) +(a_2-mid)+ (a_3-mid) ...+(a_j-mid) ≥ 0

Thus, we can see that if after subtracting the midmid number from the elements of a subarray with more than k-1k−1 elements, within numsnums, if the sum of elements of this reduced subarray is greater than 0, we can achieve an average value greater than midmid. Thus, in this case, we need to set the midmid as the new minimum element and continue the process.

Otherwise, if this reduced sum is lesser than 0 for all subarrays with greater than or equal to kk elements, we can't achieve midmid as the average. Thus, we need to set midmid as the new maximum element and continue the process.

In order to determine if such a subarray exists in a linear manner, we keep on adding nums[i]-midnums[i]−mid to the sumsum obtained till the i^{th}i 
th
  element while traversing over the numsnums array. If on traversing the first kk elements, the sumsum becomes greater than or equal to 0, we can directly determine that we can increase the average beyond midmid. Otherwise, we continue making additions to sumsum for elements beyond the k^{th}k 
th
  element, making use of the following idea.

If we know the cumulative sum upto indices ii and jj, say sum_isum 
i
​	
  and sum_jsum 
j
​	
  respectively, we can determine the sum of the subarray between these indices(including jj) as sum_j - sum_isum 
j
​	
 −sum 
i
​	
 . In our case, we want this difference between the cumulative sums to be greater than or equal to 0 as discusssed above.

Further, for sum_isum 
i
​	
  as the cumulative sum upto the current(i^{th}i 
th
 ) index, all we need is sum_j - sum_i ≥ 0 such that j - i ≥ k.

To achive this, instead of checking with all possible values of sum_isum 
i
​	
 , we can just consider the minimum cumulative sum upto the index j - kj−k. This is because if the required condition can't be sastisfied with the minimum sum_isum 
i
​	
 , it can never be satisfied with a larger value.

To fulfil this, we make use of a prevprev variable which again stores the cumulative sums but, its current index(for cumulative sum) lies behind the current index for sumsum at an offset of kk units. Thus, by finding the minimum out of prevprev and the last minimum value, we can easily find out the required minimum sum value.

Every time after checking the possiblility with a new midmid value, at the end, we need to settle at some value as the average. But, we can observe that eventually, we'll reach a point, where we'll keep moving near some same value with very small changes. In order to keep our precision in control, we limit this process to 10^-510 
−
 5 precision, by making use of errorerror and continuing the process till errorerror becomes lesser than 0.00001 .
    */
    double findMaxAverage(vector<int>& nums, int k) {
        
        double low = *min_element(begin(nums), end(nums));
        double high = *max_element(begin(nums), end(nums));
        
        auto check = [&](double mid, int k) {
            
            int N = nums.size();
            vector<double> presum(N + 1, 0);
            
            for (int i = 1; i < k; i++) {
                presum[i] = presum[i-1] + nums[i-1] - mid;
            }
            
            double minv = 0;
            
            for (int i = k; i <= N; i++) {
                
                presum[i] = presum[i-1] + nums[i-1] - mid;
                
                if (presum[i] > minv) return true;
                
                minv = std::min(minv, presum[i-k+1]);
            }
            
            return false;
        };
        
        while (high - low >= 1e-6) {
            
            double mid = (high + low) / 2;
            
            if (check(mid, k))
                low = mid;
            else
                high = mid;
        }
        
        return high;
    }
};