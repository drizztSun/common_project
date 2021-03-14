/*
 992. Subarrays with K Different Integers
 
 
 Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.

 (For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)

 Return the number of good subarrays of A.

  

 Example 1:

 Input: A = [1,2,1,2,3], K = 2
 Output: 7
 Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
 Example 2:

 Input: A = [1,2,1,3,4], K = 3
 Output: 3
 Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
  

 Note:

 1 <= A.length <= 20000
 1 <= A[i] <= A.length
 1 <= K <= A.length
 
 */

#include <functional>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class SubarraysWithKDistinct {


    /*
        992.Subarrays-with-K-Different-Integers
        
        此题的解法非常巧妙.它代表了一类思想:求关于K的解,是否可以化成求at most K的解减去求at most K-1的解.本题恰好就是用到这个方法.
        我们需要写一个helper函数,计算数组A里面最多含有K个不同数字的subarray的个数.于是最终答案就是helper(K)-helper(K-1).

        对于这个helper函数,标准答案很显然就是用双指针和滑动窗口的方法.遍历右指针,考察对应的最大的滑窗是多少.于是在该右边界固定的条件下,满足题意的subarray的个数就是count+=右指针-左指针+1
    */
    int doit_slidingwindow(vector<int>& A, int K) {

        std::function<int(int)> atMostK = [&](int K)
        {
            unordered_map<int,int> Map;
            int count=0;
            int i = 0;
            
            for (int j=0; j < A.size(); j++)
            {
                Map[A[j]]++;
                
                while (Map.size() > K)
                {
                    Map[A[i]]--;
                    if (Map[A[i]] == 0)
                        Map.erase(A[i]);
                    i++;
                }
                count+= j-i+1;
            }
            return count;
        };

        return atMostK(K) - atMostK(K-1);
    }
    
public:

    /*
        I republished this post.
        The original one is deleded by Leetcode without any notification or information.
        The only reason that, I included my youtube channel link.
        Excusem me, What the HACK!?


        Intuition:
        First you may have feeling of using sliding window.
        Then this idea get stuck in the middle.

        This problem will be a very typical sliding window,
        if it asks the number of subarrays with at most K distinct elements.

        Just need one more step to reach the folloing equation:
        exactly(K) = atMost(K) - atMost(K-1)


        Explanation
        Write/copy a helper function of sliding window,
        to get the number of subarrays with at most K distinct elements.
        Done.

        Complexity:
        Time O(N) for two passes.
        Space O(K) at most K elements in the counter

        Of course, you can merge 2 for loops into one, if you like.
    */
    int subarraysWithKDistinct(vector<int>& A, int K) {

        std::function<int(int)> atMostK = [&](int K) {
            int i = 0, res = 0;
            unordered_map<int, int> count;
            for (int j = 0; j < A.size(); ++j) {
                if (!count[A[j]]++) K--;
                while (K < 0) {
                    if (!--count[A[i]]) K++;
                    i++;
                }
                res += j - i + 1;
            }
            return res;
        };

        return atMostK(K) - atMostK(K - 1);
    }
    
    
    int doit_threepointer(vector<int>& s, int k)
    {
        unordered_map<int, int> left_long, left_short;
        int cnt_long = 0, cnt_short = 0;
        int L = 0, S = 0;
        int ans = 0;
        
        for (int i = 0; i < s.size(); i++) {
            
            int c = s[i];
            
            left_long[c]++;
            left_short[c]++;
            
            if (left_long[c] == 1)
                cnt_long++;
            if (left_short[c] == 1)
                cnt_short++;
            
            while (cnt_long > k) {
                left_long[s[L]]--;
                if (left_long[s[L]] == 0)
                    cnt_long--;
                L++;
            }
            
            while (cnt_short >= k) {
                left_short[s[S]]--;
                if (left_short[s[S]] == 0)
                    cnt_short--;
                S++;
            }
            
            ans += S - L;
        }
        
        return ans;
    }
    

};
