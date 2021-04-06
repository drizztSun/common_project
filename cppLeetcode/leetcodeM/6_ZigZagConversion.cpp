/*
6. ZigZag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
 

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
Example 3:

Input: s = "A", numRows = 1
Output: "A"
 

Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000


*/

#include <string>

using std::string;

class ZigZagConversion {

    /*
        006.ZigZag-Conversion
        观察这个数列的周期性。一个周期的元素数目M=numRows*2-2，因此这个数列的周期数目是N=(len(s)-1)/M+1。注意这种根据M计算Ｎ的的技巧。在CUDA编程中，确定block数目的计算和此很相似。

        在每个周期中，第一行是第０个元素，第二行是第１和M-1个元素，第三行是第２和Ｍ-2个元素，直至最后一行是第numRows-1个元素。所以我们只要按行遍历，在每一行中将Ｎ个周期里对应该行的数字都找出来。大致的程序架构是：

        for (int i=0; i<N; i++)
        result+=s[M*i];
        //以上是第0行
        for (int j=1; j<ｎｕｍRows-1; j++)
        ｛
        　　ｆｏｒ (int i=0; i<N; i++)
            {
            result+=s[M*i+j];
            result+=s[M*i+M-j];
            }
        ｝
        //以上是第1到第numRows-2行
        for (int i=0; i<N; i++)
        result+=s[M*i+numRows-1];
        //以上是第numRows-1行
        需要注意的是，以上对s的访问可能会有越界的风险（主要是针对最后一个周期），需要提前判断一下。
            
    */
    string convert(string s, int numRows) 
    {        
        int T=numRows*2-2;
        if (T==0) return s;
        string result;
        
        for (int i=0; i<=T/2; i++)
        {
            int a=i;
            int b=T-a;
            while (a<s.size())
            {
                result+=s[a];
                if (b<s.size() && b!=a && b!=a+T)
                    result+=s[b];
                a+=T;
                b+=T;
            }
        }
        return result;
    }
    
};