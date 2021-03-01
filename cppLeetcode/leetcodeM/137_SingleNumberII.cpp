/*
136. Single Number

Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

Follow up: Could you implement a solution with a linear runtime complexity and without using extra memory?

 

Example 1:

Input: nums = [2,2,1]
Output: 1
Example 2:

Input: nums = [4,1,2,1,2]
Output: 4
Example 3:

Input: nums = [1]
Output: 1
 

Constraints:

1 <= nums.length <= 3 * 10^4
-3 * 10^4 <= nums[i] <= 3 * 10^4
Each element in the array appears twice except for one element which appears only once.

*/
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::unordered_set;
using std::unordered_map;
using std::vector;

class SingleNumber {

    /*
        136.Single-Number
        巧妙应用“亦或”操作。

        a^a=0

        a^b=1

        A^B^B=A (该操作具有交换律commutative.)

        0^A=A (所以初值设为0)
    */
    int doit_(vector<int>& nums) 
    {
        int result=0;
        for (int i=0; i<nums.size(); i++)
            result^=nums[i];
        
        return result;    
    }

public:

    int doit_hashtable(vector<int>& nums) {
        int res = 0;
        unordered_set<int> buff;
        for (auto c: nums) {
            if (buff.count(c) > 0)
                buff.erase(c);
            else
                buff.insert(c);
        }

        return *buff.begin();
    }


    int doit_(vector<int>& nums) {
        
        int res = 0;
        for (auto c : nums) res ^= c;
        return res;
    }
};



/*

137. Single Number II

Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.

 

Example 1:

Input: nums = [2,2,3,2]
Output: 3
Example 2:

Input: nums = [0,1,0,1,0,1,99]
Output: 99
 

Constraints:

1 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
Each element in nums appears exactly three times except for one element which appears once.
 

Follow up: Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

*/


class SingleNumberII {

public:

    /*
        137.Single-Number-II
        此题容易受到136.Single-Number的影响，总觉得应该用到“亦或”操作的性质。但事实上，此题的解法和^操作的关系并不大。

        1) 此题的突破点在于，细分到所有N个数的每个二进制位，都会有N-1个bit重复出现了3次，而有另一个bit出现了1次（这个bit就对应着那个single number）。
        如果把该二进制位上所有数的bit都相加起来，那么对3除的余数一定就是那个与众不同的bit。就这样，我们可以确定这个single number的每一位的bit，然后重构出对应的二进制数来。

        实现上可以设计一个vector<int>bits(32)来累加每个二进制位的bit的总和。
        
        2) 当然还有更省空间的方法。因为我们实际上只需要计算各个二进制位上bit之和除以3的余数，总共只有三种可能0,1,2.于是可以设计两个int32的计数器count1,count2. 
        其中count1[i]和count2[i]用来记录第i个二进制位上的bit之和，即00,01,11这三种情况。single number的每一个二进制位可以通过最终的count1[i]和count2[i]重构出来。
    */
    int doit_(vector<int>& nums)
    {
        int count1 = 0, count2 = 0;
        for (auto x: nums)
        {
            int count1_new = 0, count2_new = 0;
            for (int i=0; i<32; i++)
            {
                int hi = (count1>>i)&1;
                int low = (count2>>i)&1;
                int sum = (hi*2+low+((x>>i)&1))%3;
                count1_new |= ((sum/2)<<i);
                count2_new |= ((sum%2)<<i);
            }       
            count1 = count1_new, count2 = count2_new;
        }

        int ret = 0;
        for (int i=0; i<32; i++)
        {
            ret += ((count2>>i)&1)<<i;
        }
        return ret;
    }

    int doit_hashtable(vector<int>& nums) 
    {
        vector<int>bits(32,0);
        
        for (int i=0; i<nums.size(); i++)
        {
            int k=nums[i];
            for (int j=0; j<32; j++)
            {
                bits[j]+=((k>>j)&1);
            }            
        }
        
        int result=0;
        for (int j=0; j<32; j++)
        {
            if (bits[j]%3!=0)
                result+= 1<<j;
        }
        
        return result;
    }
    
    int doit_(vector<int>& nums) {
        
        int seen_once = 0, seen_twice = 0;
        
        for (auto c: nums) {
            
            seen_once = ~seen_twice & (seen_once ^ c);
            seen_twice = ~seen_once & (seen_twice ^ c);
        }
        
        return seen_once;
    }

    int doit_hashtable(vector<int>& nums) {

        unordered_map<int, int> buff;

        for (auto c: nums) {
            if (buff[c] == 2) {
                buff.erase(c);
                continue;
            }
            buff[c]++;
        }

        return buff.begin()->first;
    }
};


/*
260. Single Number III

Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice. 
Find the two elements that appear only once. You can return the answer in any order.

Follow up: Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

 

Example 1:

Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.
Example 2:

Input: nums = [-1,0]
Output: [-1,0]
Example 3:

Input: nums = [0,1]
Output: [1,0]
 

Constraints:

2 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
Each integer in nums will appear twice, only two integers will appear once.

*/

class SingleNumberIII {

public:

    vector<int> doit_hashtable(vector<int>& nums) {
        
        unordered_set<int> buff;

        for (auto c: nums)
            if (buff.count(c) > 0)
                buff.erase(c);
            else
                buff.insert(c);
        
        vector<int> ans;
        for (auto c: buff) {
            ans.push_back(c);
        }
        return ans;
    }

    vector<int> doit_(vector<int>& nums) {
        // difference between two numbers (x and y) which were seen only once
        int bitmask = 0;
        for (int num : nums) bitmask ^= num;

        // rightmost 1-bit diff between x and y
        int diff = bitmask & (-bitmask);

        int x = 0;
        // bitmask which will contain only x
        for (int num : nums) if (num & diff) x ^= num;

        return {x, bitmask^x};
    }
}