/*
930. Binary Subarrays With Sum

In an array A of 0s and 1s, how many non-empty subarrays have sum S?

 

Example 1:

Input: A = [1,0,1,0,1], S = 2
Output: 4
Explanation: 
The 4 subarrays are bolded below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
 

Note:

A.length <= 30000
0 <= S <= A.length
A[i] is either 0 or 1.


*/

#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class NumSubarraysWithSum {

    /*
        930.Binary-Subarrays-With-Sum
        此题是考察对Hash+prefix的常见组合。

        我们遍历每一个元素j，考察以j为结尾、满足条件的subarray，这样的起点i可以在哪里？如果满足条件的起点i有多种可能，那么答案就可以累加上这么多数量．

        如何确定i的位置呢？凡是涉及到数组的subarray的和，我们通常会转化为前缀和来处理。即sum[i:j] = prefix[j]-prefix[i-1]。其中sum[i:j]即使S，当我们固定j的时候，prefix[j]也是已知的。
        因此可以知道我们期望的prefix[i-1]是多少，假设为val。所以我们可以用Hash来存储某个所有前缀和val所对应的i的个数。因此我们就有

        ret += Map[prefix[j] - S]
    */
    int numSubarraysWithSum(vector<int>& A, int S) 
    {
        unordered_map<int,int>Map;
        Map[0] = 1;
        int sum = 0, ret = 0;
        for (int i=0; i<A.size(); i++)
        {
            sum += A[i];
            if (Map.find(sum-S)!=Map.end())
                ret+=Map[sum-S];
            Map[sum]+=1;
        }
        return ret;
    }

public:

    int doit_hashtable_presum(vector<int>& A, int S) {
        
        unordered_map<int, int> presums;
        presums.emplace(0, 1);
        int total = 0, ans = 0;

        for (int i = 0; i < A.size(); i++) {

            total += A[i];

            if (presums.count(total - S)) {
                ans += presums[total - S];
            }

            presums[total]++;
        }

        return ans;
    }
};