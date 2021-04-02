/*
179. Largest Number

Given a list of non-negative integers nums, arrange them such that they form the largest number.

Note: The result may be very large, so you need to return a string instead of an integer.

 

Example 1:

Input: nums = [10,2]
Output: "210"
Example 2:

Input: nums = [3,30,34,5,9]
Output: "9534330"
Example 3:

Input: nums = [1]
Output: "1"
Example 4:

Input: nums = [10]
Output: "10"
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 10^9

*/
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;


class LargestNumber {

    /*
            179.Largest-Number
        
        本题的本质是一个非常有用的知识点：给你一个字符串数组，如何排序拼接这些字符串实现字典序最大？方法是设计一个巧妙的排序函数：

        static bool cmp(string a, string b)
        {
            string c=a+b;
            string d=b+a;
            return stoll(c)>stoll(d);
        }

        sort(Nums.begin(),Nums.end(),cmp);
        将以此排序的字符串拼接起来，就是字典序最大的！

        证明：

        传递性
        我们试图证明如果s3>s2，且s2>s1，那么就一定共有s3>s1. 因为只有具备传递性的大小比较，才能将所有的字符串的唯一排序。
        我们令s3、s2、s1的长度对应的10的幂分别是n3、n2、n1（比如说1000,100,10），那么就有

        s3 > s2 => s3s2 > s2s3 => s3*n2+s2 > s2*n3+s3 => s3(n2-1) > s2(n3-1)
        s2 > s1 => s2s1 > s1s2 => s2*n1+s1 > s1*n2+s2 => s2(n1-1) > s1(n2-1)
        因为所有的都是非负数，所以有

        s3s2(n2-1)(n1-1) > s2s1(n3-1)(n2-1)
        如果s2!=0，那么得到s3(n1-1)>s1(n3-1) => s3n1+s1 > s1n3+s3，即 s3>s1
        如果s2==0，那么s1==0，必然有 s3>s1

        算法的正确性
        对于任意一个乱序的字符串数组，我们都可以通过交换一对相邻的逆序对来实现“冒泡”排序。比如
        s3s1s2s4
        s3s1s4s2
        s3s4s1s2
        s4s3s1s2
        s4s3s2s1
        在每一步中，只有一对相邻的字符串做了交换，每次交换的过程中都是将较大的si移动到较小的sj的前面，即由...sjsi....变成了...sisj....。显然我们发现这一步变化是将整体的字符串的字典序变大的。
        于是我们推断出每一步变化都是将这个字符串的字典序变大。也就是说，任意一个乱序拼接的字符串，都不如按照排序函数得到顺序拼接的字符串大。
    */
    static bool cmp(string&a, string&b)
    {
        return (a+b)>(b+a);
    }

    string largestNumber(vector<int>& nums) 
    {
        vector<string>strs;
        for (int i=0; i<nums.size(); i++)
            strs.push_back(std::to_string(nums[i]));

        std::sort(strs.begin(), strs.end(), cmp);

        string result;
        for (int i=0; i<strs.size(); i++)
            result+=strs[i];

        int i=0;
        while (result[i]=='0') i++;
        if (i==result.size())
            return "0";
        else
            return result.substr(i);
            
        return result;
    }

public:



    /*
        Approach #1 Sorting via Custom Comparator [Accepted]
        Intuition

        To construct the largest number, we want to ensure that the most significant digits are occupied by the largest digits.

        Algorithm

        First, we convert each integer to a string. Then, we sort the array of strings.

        While it might be tempting to simply sort the numbers in descending order, this causes problems for sets of numbers with the same leading digit. For example, sorting the problem example in descending order would produce the number 95343039534303, while the correct answer can be achieved by transposing the 33 and the 3030. Therefore, for each pairwise comparison during the sort, we compare the numbers achieved by concatenating the pair in both orders. We can prove that this sorts into the proper order as follows:

        Assume that (without loss of generality), for some pair of integers aa and bb, our comparator dictates that aa should precede bb in sorted order. This means that a\frown b > b\frown aa⌢b>b⌢a (where \frown⌢ represents concatenation). For the sort to produce an incorrect ordering, there must be some cc for which bb precedes cc and cc precedes aa. This is a contradiction because a\frown b > b\frown aa⌢b>b⌢a and b\frown c > c\frown bb⌢c>c⌢b implies a\frown c > c\frown aa⌢c>c⌢a. In other words, our custom comparator preserves transitivity, so the sort is correct.

        Once the array is sorted, the most "signficant" number will be at the front. There is a minor edge case that comes up when the array consists of only zeroes, so if the most significant number is 00, we can simply return 00. Otherwise, we build a string out of the sorted array and return it.


        Complexity Analysis

        Time complexity : \mathcal{O}(nlgn)O(nlgn)

        Although we are doing extra work in our comparator, it is only by a constant factor. Therefore, the overall runtime is dominated by the complexity of sort, which is \mathcal{O}(nlgn)O(nlgn) in Python and Java.

        Space complexity : \mathcal{O}(n)O(n)

        Here, we allocate \mathcal{O}(n)O(n) additional space to store the copy of nums. Although we could do that work in place (if we decide that it is okay to modify nums), we must allocate \mathcal{O}(n)O(n) space for the final return string. Therefore, the overall memory footprint is linear in the length of nums.        
    */
    string largestNumber(vector<int>& nums) {
        // Get input integers as strings.
        int N = nums.size();
        vector<string> strnums(N);
        
        for(int i = 0; i < nums.size(); i++) 
            strnums[i] = std::to_string(nums[i]);
        
        // Sort strings according to custom comparator.
        std::sort(begin(strnums), end(strnums), [](const auto& a, const auto& b) {
           return a+b > b+a; 
        });
        
        // If, after being sorted, the largest number is `0`, the entire number
        // is zero.
        if (strnums[0] == "0") return "0";
        
        string ans;
        // Build largest number from sorted array.
        for (auto c: strnums)
            ans += c;
        
        return ans;
    }
};