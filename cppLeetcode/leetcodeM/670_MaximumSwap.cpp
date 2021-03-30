/*
670. Maximum Swap

Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.

Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:
Input: 9973
Output: 9973
Explanation: No swap.
Note:
The given number is in the range [0, 10^8]

*/

#include <string>
#include <vector>
#include <algorithm>


using std::string;
using std::vector;


class MaximumSwap {

    /*
        670.Maximum-Swap
        从前往后遍历，排除最前的极大递减序列之外，找到剩下的序列里最大的那个数字（有相同的取靠后的），用它和递减序列之后的第一个元素交换。

        比如986737，我们将它和排序之后的987763比较，发现前两位就是极大递减序列，所有不用管。从第三位开始，找剩下里面的最大值（相同最大值则取靠后的），结果是最后一个数字7。我们将这个7和递减序列之后的6对换，就得到了最终答案987736。
    */
    int maximumSwap(int num) 
    {
        int MAX=0;
        int pos;
        string str = std::to_string(num);
        
        string str2=str;
        sort(str2.begin(),str2.end());
        reverse(str2.begin(),str2.end());
        
        int j=0;
        while (j<str.size() && str[j]==str2[j])
            j++;
        
        if (j==str.size()) return num;
                
        for (int i=j; i<str.size(); i++)
        {
            if (str[i]-'0'>=MAX)
            {
                MAX=str[i]-'0';
                pos=i;
            }
        }
        
        for (int i=j; i<pos; i++)
        {
            if (str[i]-'0'>=MAX)
                continue;
            std::swap(str[i],str[pos]);         
            break;
        }
        
        return stoi(str);
        
        
    }

public:
    
    int doit_greedy(int num) {
        
        vector<int> digits;
        
        while (num) {
            digits.push_back(num % 10);
            num /= 10;
        }
        
        vector<vector<int>> pos(10);
        
        for (int i = digits.size()-1; i >= 0; i--) {
            pos[digits[i]].push_back(i);
        }
        
        bool done = false;
        
        for (int i = digits.size()-1; !done && i >= 0; i--) {
            
            for (int d = 9; d > digits[i]; d--) {
                
                if (!pos[d].empty() && pos[d].back() < i) {
                    std::swap(digits[i], digits[pos[d].back()]);
                    done = true;
                    break;
                }
            }
            
        }
        
        num = 0;
        for (int i = digits.size()-1; i >= 0; i--)
            num = num * 10 + digits[i];
        
        return num;
    }
};