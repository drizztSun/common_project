/*
525. Contiguous Array

Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.

*/

#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;



class ContiguousArray {

    /*
        525.Contiguous-Array
        建立累加和sum，遍历所有元素，遇到1加1，遇到0减1. 如果两个位置的累加和相等，说明中间的元素和是0，即有相同数目的0和1.

        构造unordered_map<int,int>Map记录每个累加和sum出现的位置。注意，因为求的是最大长度，只需要存储第一次出现sum数值的位置即可。另外，需要考虑子串的首位置可以是0，故设置Map[0]=-1.

                int result=0;
                for (int i=0; i<nums.size(); i++)
                {
                    sum+=(nums[i]==1?1:-1);
                    if (Map.find(sum)==Map.end())
                        Map[sum]=i;
                    else
                        result = max(result, i-Map[sum]);
                }
    */
    int findMaxLength(vector<int>& nums) 
    {
        int sum=0;
        unordered_map<int,int>Map;
        Map[0]=-1;
        
        int result=0;
        for (int i=0; i<nums.size(); i++)
        {
            sum+=(nums[i]==1?1:-1);
            if (Map.find(sum)==Map.end())
                Map[sum]=i;
            else
            {
                result = std::max(result, i-Map[sum]);
            }
        }
        
        return result;
    }
};