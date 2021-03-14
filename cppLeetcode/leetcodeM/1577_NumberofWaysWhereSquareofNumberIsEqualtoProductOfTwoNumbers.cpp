/*
1577. Number of Ways Where Square of Number Is Equal to Product of Two Numbers


Given two arrays of integers nums1 and nums2, return the number of triplets formed (type 1 and type 2) under the following rules:

Type 1: Triplet (i, j, k) if nums1[i]^2 == nums2[j] * nums2[k] where 0 <= i < nums1.length and 0 <= j < k < nums2.length.
Type 2: Triplet (i, j, k) if nums2[i]^2 == nums1[j] * nums1[k] where 0 <= i < nums2.length and 0 <= j < k < nums1.length.
 

Example 1:

Input: nums1 = [7,4], nums2 = [5,2,8,9]
Output: 1
Explanation: Type 1: (1,1,2), nums1[1]^2 = nums2[1] * nums2[2]. (4^2 = 2 * 8). 
Example 2:

Input: nums1 = [1,1], nums2 = [1,1,1]
Output: 9
Explanation: All Triplets are valid, because 1^2 = 1 * 1.
Type 1: (0,0,1), (0,0,2), (0,1,2), (1,0,1), (1,0,2), (1,1,2).  nums1[i]^2 = nums2[j] * nums2[k].
Type 2: (0,0,1), (1,0,1), (2,0,1). nums2[i]^2 = nums1[j] * nums1[k].
Example 3:

Input: nums1 = [7,7,8,3], nums2 = [1,2,9,7]
Output: 2
Explanation: There are 2 valid triplets.
Type 1: (3,0,2).  nums1[3]^2 = nums2[0] * nums2[2].
Type 2: (3,0,1).  nums2[3]^2 = nums1[0] * nums1[1].
Example 4:

Input: nums1 = [4,7,9,11,23], nums2 = [3,5,1024,12,18]
Output: 0
Explanation: There are no valid triplets.
 

Constraints:

1 <= nums1.length, nums2.length <= 1000
1 <= nums1[i], nums2[i] <= 10^5
*/

#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>

using std::unordered_map;
using std::vector;



class NumTriplets {

    /*
        1577.Number-of-Ways-Where-Square-of-Number-Is-Equal-to-Product-of-Two-Numbers
        解法1：Hash
        这个方法更容易实现。我们查看数组A中的每个元素a。然后遍历数组B中的元素i，同时维护一个hash表来统计B[i]之前的B数组元素的频率。

        如果a*a/B[i]存在hash表中存在并且有k个，这就意味着有k组triplet满足条件{a, B[i], a*a/B[i]}，加入ret的统计中。注意每查看完B[i]，要把B[i]也加入hash表中。

        解法1：Two Pointer
        如果这两个数组都排过序，那么有不需要额外空间的双指针方法。看似和two sum基本一致，但是实现起来更为麻烦。

        我们知道，如果a*a < B[i]*B[j]，那么下一步是i++；如果a*a > B[i]*B[j]，那么下一步是j--；但如果a*a==B[i]*B[j]，下一步该指针移动？不应该是i++, j--。正解是：

        如果B[i]==B[j]，那么[i:j]区间内的k个相同的数，任意取两个都可以放入triplet，所以ret+=k*(k-1)/2，然后就可以退出了。
        否则的话，我们需要检查有x个与B[i]相同的数，y个与B[j]相同的数，所以ret+=x*y。然后需要把i指针右移到下一个不同的数（移动x个位置），j指针左移到下一个不同的数（移动y个位置）。
    
    */
    int doit_hashtable(vector<int>& nums1, vector<int>& nums2) 
    {
        int ret = 0;

        std::function<int(vector<int>&, vector<int>&)> helper = [](vector<int>& nums1, vector<int>& nums2)
        {
            int ret = 0;                
            for (long x: nums1)
            {
                unordered_map<int,int>Map;
                for (int i=0; i<nums2.size(); i++)
                {
                    if (x*x%nums2[i]==0)
                    {
                        ret += Map[x*x/nums2[i]];
                    }
                    Map[nums2[i]]+=1;
                }
            }
            return ret;
        };

        ret += helper(nums1, nums2);
        ret += helper(nums2, nums1);
        return ret;
    }

    int numTriplets(vector<int>& nums1, vector<int>& nums2) 
    {
        int ret = 0;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        std::function<int(vector<int>&, vector<int>&)> helper = [](vector<int>& nums1, vector<int>& nums2)
        {
            int ret = 0;
            int n = nums2.size();
            for (long x: nums1)
            {
                int i = 0, j = n-1;
                while (i<j)
                {                
                    if (x*x==(long)nums2[i]*(long)nums2[j])
                    {
                        if (nums2[i]==nums2[j])
                        {
                            int t = j-i+1;
                            ret += t*(t-1)/2;
                            break;
                        }
                        else
                        {
                            int i0 = i; int j0=j;
                            while (i+1<n && nums2[i+1]==nums2[i])
                                i++;
                            while (j-1<n && nums2[j-1]==nums2[j])
                                j--;
                            ret += abs(i-i0+1)*abs(j0-j+1);
                            i++;
                            j--;                        
                        }
                    }                    
                    else if (x*x<(long)nums2[i]*(long)nums2[j])
                        j--;
                    else
                        i++;
                }
            }
            return ret;
        };

        ret += helper(nums1,nums2);
        ret += helper(nums2,nums1);
        return ret;
    }

public:

    /*
        Solution 1.
        Type 1 and Type 2 are symmetrical so we can define a function count(A, B) which returns the count of the Type 1 triples. The answer is count(A, B) + count(B, A).

        For count(A, B), we can use a unordered_map<int, int> m to store the frequency of the numbers in B. Then for each number a in A, the target value is a * a. We traverse the map m to count the triplets.

        For each entry (b, cnt) in m:

        If target is not divisible by b or target / b is not in m, there is no triplets, skip.
        If target / b == b, we need to pick 2 out of cnt numbers so we can add cnt * (cnt - 1) triplets to the answer.
        Otherwise, we can add cnt * m[target / b] triplets to the answer.
        Since we count the the pairs in B twice, we need to divide the answer by 2 before returning.
    */
    int doit_hashtable(vector<int>& nums1, vector<int>& nums2) {

        std::function<int(vector<int>&, vector<int>&)> count = [](vector<int> &A, vector<int> &B) {
            int ans = 0;
            unordered_map<int, int> m;
            for (int n : B) m[n]++;
            
            for (int a : A) {
                long target = (long)a * a;
            
                for (auto &[b, cnt] : m) {
                    if (target % b || m.count(target / b) == 0) continue;
                    
                    if (target / b == b) 
                        ans += cnt * (cnt - 1);
                    else 
                        ans += cnt * m[target / b];
                }
            }
            return ans / 2;
        };

        return count(nums1, nums2) + count(nums2, nums1);
    }
};