/*
166. Fraction to Recurring Decimal

Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

If multiple answers are possible, return any of them.

It is guaranteed that the length of the answer string is less than 104 for all the given inputs.

 

Example 1:

Input: numerator = 1, denominator = 2
Output: "0.5"
Example 2:

Input: numerator = 2, denominator = 1
Output: "2"
Example 3:

Input: numerator = 2, denominator = 3
Output: "0.(6)"
Example 4:

Input: numerator = 4, denominator = 333
Output: "0.(012)"
Example 5:

Input: numerator = 1, denominator = 5
Output: "0.2"
 

Constraints:

-2^31 <= numerator, denominator <= 2^31 - 1
denominator != 0
*/
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;


class FractionToDecimal {


    /*
        166.Fraction-to-Recurring-Decimal
        注意的几个细节：

        被除数为0；
        被除数或除数为负数；
        遇到INT_MIN时的溢出;
        整除的情况。
        需要一个set记录每次的余数t。如果某次的余数已经在集合中，则说明有循环。

        同时需要一个Map来记录每次的余数与对应的小数位置，当发现循环的起始位置时，便于插入‘(’。

                while (t!=0 && Set.find(t)==Set.end())
                {
                    Set.insert(t);
                    Map[t]=result.size();            
                    result.push_back((t*10/B)+'0');
                    t=t*10%B;
                }
                
                if (t==0) return result; //整除：就直接输出
                
                int pos=Map[t]; // 非整除：找到循环体开始的位置
                result.insert(result.begin()+pos,'(');
                result.push_back(')'); 
    */
    string fractionToDecimal(int numerator, int denominator) 
    {
        long A = numerator;
        long B = denominator;
        
        if (A==0) return "0";
        
        int sign = 1;
        if (A<0)
        {
            sign *= -1;
            A = abs(A);
        }
        if (B<0)
        {
            sign *= -1;
            B = abs(B);
        }
        
        string ret;
        if (sign==-1) ret = "-";
        
        ret += std::to_string(A/B);
        
        if (A%B==0) 
            return ret;
        else 
            ret+=".";
        
        long C = A%B;
        
        unordered_map<int,int> Map;
        
        while (C!=0 && Map.find(C)==Map.end())
        {
            Map[C] = ret.size();
            ret.push_back('0'+C*10/B);
            C = C*10%B;
        }
        
        if (C==0) return ret;
        
        ret.insert(ret.begin()+Map[C], '(');
        ret.push_back(')');
        
        return ret;
    }
};