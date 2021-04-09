/*
1814. Count Nice Pairs in an Array


You are given an array nums that consists of non-negative integers. Let us define rev(x) as the reverse of the non-negative integer x. For example, rev(123) = 321, and rev(120) = 21. 
A pair of indices (i, j) is nice if it satisfies all of the following conditions:

    . 0 <= i < j < nums.length
    . nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])

Return the number of nice pairs of indices. Since that number can be too large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [42,11,1,97]
Output: 2
Explanation: The two pairs are:
 - (0,3) : 42 + rev(97) = 42 + 79 = 121, 97 + rev(42) = 97 + 24 = 121.
 - (1,2) : 11 + rev(1) = 11 + 1 = 12, 1 + rev(11) = 1 + 11 = 12.
Example 2:

Input: nums = [13,10,35,24,76]
Output: 4
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109

*/

#include <vector>
#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;
using std::vector;


class CountNicePairs {

    /*
                Explanation
        A[i] + rev(A[j]) == A[j] + rev(A[i])
        A[i] - rev(A[i]) == A[j] - rev(A[j])
        B[i] = A[i] - rev(A[i])

        Then it becomes an easy question that,
        how many pairs in B with B[i] == B[j]


        Complexity
        Time O(nloga)
        Space O(n)
    */
    int countNicePairs(vector<int>& A) {
        int res = 0, mod = 1e9 + 7;
        unordered_map<int, int> count;
        for (int& a : A)
            res = (res + count[a - rev(a)]++) % mod;
        return res;
    }
    int rev(int x) {
        int b = 0;
        while (a > 0) {
            b = b * 10 + (a % 10);
            a /= 10;
        }
        return b;
    }

    /*
        #LeetCode 1814. Count Nice Pairs in an Array
        这题还是不错的，本质上和Two Sum一模一样，只需要把公式变形一下：
        A + rev(B) == B + rev(A) <=>
        A - rev(A) == B - rev(B)
        key = x - rev(x), 用hashtable存freq
        ans += m[key]++
    */
    int doit_hashtable(vector<int>& nums) {
        constexpr int hmod = 1e9+7;
        unordered_map<int, int> m;
        long ans = 0;

        for (int x: nums) {
            string s = std::to_string(x);
            reverse(begin(s), end(s));
            ans += m[x-stoi(s)]++;
        }

        return ans % hmod;
    }


public:
    
    int doit_hashtable(vector<int>& nums) {
        
        auto rev = [](int num) {
            int ans = 0;
            while (num) {
                ans = ans * 10 + num % 10;
                num /= 10;
            }
            return ans;
        };
        
        vector<int> revs;
        int hmod = 1e9+7;
        for (auto c: nums)
            revs.push_back(rev(c));
        
        unordered_map<int, int> buf;
        for (int i = 0; i < nums.size(); i++) {
            buf[nums[i]-revs[i]]++;
        }
        
        long ans = 0;
        for (auto [k, v]: buf) {
            ans = (ans + long(v) * long(v-1) / 2) % hmod; 
        }
        return ans;
    }
};