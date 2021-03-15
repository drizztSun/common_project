/*
 # 1004. Max Consecutive Ones III

 # Given an array A of 0s and 1s, we may change up to K values from 0 to 1.

 # Return the length of the longest (contiguous) subarray that contains only 1s.


 # Example 1:

 # Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
 # Output: 6
 # Explanation:
 # [1,1,1,0,0,1,1,1,1,1,1]
 # Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.

 # Example 2:

 # Input: A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
 # Output: 10
 # Explanation:
 # [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
 # Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.


 # Note:

 # 1 <= A.length <= 20000
 # 0 <= K <= A.length
 # A[i] is 0 or 1
 
 
 */
#include <algorithm>
#include <vector>
using std::vector;

class LongestOnes {

    /*
        1004.Max-Consecutive-Ones-III
        解法1：DP
        令dp[i][k]表示截止到第i个元素位置，我们行使了k次翻转权利的话，最长的连续1区间的长度。突破口就是第i个元素我们是否进行翻转：

        如果A[i]==1，那么我们不需要翻转，即dp[i][k] = dp[i-1][k]+1
        如果A[i]==0，那么我们需要翻转，即dp[i][k] = dp[i-1][k-1]+1，注意k不能超过题目规定的行使反转权利的上限K。 答案就是dp[x][K]中的最大值。
        以上方法的两层循环的时间复杂度是o(NK)，显然会超时。

        解法2：双指针
        对于任何求subarray的问题，我们通常的做法就是固定左边界，探索右边界。假设我们固定左边界是i，那么要使右边界j最远，需要满足[i,j]最多有K个0。

        此时我们考虑左边界是i+1的情况。如果A[i+1]==1，那么此时[i+1,j]内的需要翻转元素的个数count依然是K，然而右边界j依然不能往右突破。我们只有不停地移动i，直到A[i]==0的时候，
        意味着第i个元素的不被允许翻转，所以区间内的翻转次数count-=1，因此右边界就又可以移动，直到找到下一个A[j]==0为止（此时count再次变为K）。

        所以两个指针都只会朝一个方向移动。这是快慢类型的双指针，时间复杂度就是o(N).
    */
    int longestOnes(vector<int>& A, int K) 
    {
        int n = A.size();
        int count = 0;
        int i = 0;
        int ret = 0;
        for (int j=0; j<n; j++)
        {
            if (A[j]==1)
            {
                ret = std::max(ret, j-i+1);
                continue;
            }
                
            count++;
            while (count>K)
            {
                if (A[i]==0)
                    count--;
                i++;
            }
            ret = std::max(ret, j-i+1);
        }
        return ret;
    }

public:

    /*
        Translation:
        Find the longest subarray with at most K zeros.

        Explanation
        For each A[j], try to find the longest subarray.
        If A[i] ~ A[j] has zeros <= K, we continue to increment j.
        If A[i] ~ A[j] has zeros > K, we increment i (as well as j).
    */
    int doit_slidingwindow(vector<int>& A, int K) {
        int i = 0, j = 0;
        for (; j < A.size(); ++j) {
            if (A[j] == 0) K--;
            if (K < 0 && A[i++] == 0) K++;
        }
        return j - i;
    }

    int doit_slidingwindow_1(vector<int>& A, int K) {
        int left = 0, right = 0;
        int ans = 0;
            
        for (; right < A.size(); right++) {
            
            K -= 1 - A[right];
                
            if (K < 0) {
                K += 1 - A[left];
                left++;
            } else {
                ans = std::max(ans, right - left + 1);
            }
        }
        
        return ans;
    }
    
    int doit(vector<int>&& A, int K) {
        
        int ans = 0;
        int j = 0;
        int ones = 0, zeros = 0;
        
        for (auto i = 0; i <= A.size(); i++) {
        
            if (i < A.size())
                if (A[i] == 1)
                    ones++;
                else
                    zeros++;
            
            while (j < i && zeros > K) {
                if (A[j] == 1)
                    ones--;
                else
                    zeros--;
                j++;
            }
            
            if (zeros <= K)
                ans = std::max(ans, ones + zeros);
        }
        
        return ans;
    }
    
    int doit1(vector<int>&& s, int k) {
        
        int winStart = 0;
        int cnt0 = 0, cnt1 = 0;
        int maxlen = 0;
        int maxcount = 0;
        
        for (int winEnd = 0; winEnd < s.size(); winEnd++) {
            
            if (s[winEnd])
                cnt1++;
            
            maxcount = std::max(maxcount, cnt1);
            while (winEnd-winStart+1 - maxcount > k) {
                if (s[winStart])
                    cnt1--;
                winStart++;
            }
            maxlen = std::max(maxlen, winEnd-winStart+1);
        }
        return maxlen;
    }
};