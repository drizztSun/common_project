/*
556. Next Greater Element III

Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.

Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.

 

Example 1:

Input: n = 12
Output: 21
Example 2:

Input: n = 21
Output: -1
 

Constraints:

1 <= n <= 231 - 1

*/
#include <string>
#include <algorithm>
#include <vector>

using std::vector;
using std::string;

class Solution {

    /*
                556.Next-Greater-Element-III
        首先，从低位到高位找到第一个不满足升序的数字。显然，如果从低位到高位都是升序的话，那么找不到任何可以比这个数字更大的变换了。

        假设找到这样的数字在第n+1位（记做k），那么在1~n这个n个低位数字中找到恰比k大的数字（记做m），交换k和m。于是变换后的第n+1位就这么定下来了（可以分析出这就是最小的改动）。
        剩下来的第1~n位（记得其中有一个是之前调换过来的k），我们让它们按照降序排列即可。
    */

    int nextGreaterElement(int n) 
    {
        if (n==0) return -1;
        
        vector<int>num;
        while (n>0)
        {
            num.push_back(n%10);
            n=n/10;
        }
        
        vector<int>p;
        p.push_back(num[0]);
        int i=1;
        while (i<num.size() && num[i]>=num[i-1])
        {
            p.push_back(num[i]);
            i++;
        }
        if (i==num.size()) return -1; // all the digits are descending
        
        int j=0;
        while (p[j]<=num[i]) j++;
        std::swap(num[i],p[j]);
        
        sort(p.begin(),p.end());
        reverse(p.begin(),p.end());
        
        for (int k=0; k<p.size(); k++)
            num[k]=p[k];
        
        long long result=0;
        for (int i=num.size()-1; i>=0; i--)        
            result = result*10+num[i];
        
        if (result>INT_MAX) 
            return -1;
        else
            return result;                
    }

public:

    int doit_str(int n) {

        string nums = std::to_string(n);
        int sz = nums.length();

        for (int i = sz-1; i > 0; i--) {

            if (nums[i] <= nums[i-1]) continue;

            int cloest = i;
            int j = i;
            while (j < sz) {

                if (nums[j] > nums[i-1] && nums[j] < nums[cloest]) {
                    cloest = j;
                }
                j++;
            }

            std::swap(nums[i-1], nums[cloest]);
            std::sort(begin(nums)+i, end(nums));

            long long res = std::atol(nums.c_str());
            return res > INT_MAX ? -1 : res;
        }

        return -1;
    }
};