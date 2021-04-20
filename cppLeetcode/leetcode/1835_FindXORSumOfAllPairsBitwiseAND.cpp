/*
1835. Find XOR Sum of All Pairs Bitwise AND

The XOR sum of a list is the bitwise XOR of all its elements. If the list only contains one element, then its XOR sum will be equal to this element.

For example, the XOR sum of [1,2,3,4] is equal to 1 XOR 2 XOR 3 XOR 4 = 4, and the XOR sum of [3] is equal to 3.
You are given two 0-indexed arrays arr1 and arr2 that consist only of non-negative integers.

Consider the list containing the result of arr1[i] AND arr2[j] (bitwise AND) for every (i, j) pair where 0 <= i < arr1.length and 0 <= j < arr2.length.

Return the XOR sum of the aforementioned list.

 

Example 1:

Input: arr1 = [1,2,3], arr2 = [6,5]
Output: 0
Explanation: The list = [1 AND 6, 1 AND 5, 2 AND 6, 2 AND 5, 3 AND 6, 3 AND 5] = [0,1,2,0,2,1].
The XOR sum = 0 XOR 1 XOR 2 XOR 0 XOR 2 XOR 1 = 0.
Example 2:

Input: arr1 = [12], arr2 = [4]
Output: 4
Explanation: The list = [12 AND 4] = [4]. The XOR sum = 4.
 

Constraints:

1 <= arr1.length, arr2.length <= 105
0 <= arr1[i], arr2[j] <= 109
*/

#include <vector>

using std::vector;

class XORSum {

    /*
        1835.Find-XOR-Sum-of-All-Pairs-Bitwise-AND
        因为XOR和AND都是位操作，我们其实可以只关注每个bit的变化。假设第i个bit位上，我们求某个a与所有b1,b2,...bn的配对，即a&b1 ^ a&b2 ^ a&b3 ^ ... a&bn。
        如果a为0，那么答案就是0；如果a为1，那么答案就是b1 ^ b2 ^ b3 ^ ... bn，结果就是数这些bi里面有几个1. 如果有奇数个1，那么答案就是1；如果是偶数个，那么答案就是0.

        对于所有的a，{b1,b2,...,bn}都是共享的，所以将上述的过程重复n遍即可。总的时间复杂度就是o(N)。
    */
    int getXORSum(vector<int>& arr1, vector<int>& arr2) 
    {
        vector<int>ones(32);
        for (auto b: arr2)
        {
            for (int i=0; i<32; i++)
            {
                if ((b>>i)&1)
                    ones[i]++;
            }
        }
        
        int ret = 0;
        for (auto a: arr1)
        {
            int temp = 0;
            for (int i=0; i<32; i++)
            {
                if (((a>>i)&1)==0)
                    continue;
                temp += ((ones[i]%2)<<i);                    
            }
            ret ^= temp;
        }
        return ret;        
    }

public:

    /*
        Intuition
        We all know the distributive property that (a1+a2)*(b1+b2) = a1*b1 + a1*b2 + a2*b1 + a2*b2

        Now focus on each bit,
        for example the last bit of A[i] and B[j],
        and think how it works and affect the result.


        Explanation
        Distributive property is similar for AND and XOR here.
        (a1^a2) & (b1^b2) = (a1&b1) ^ (a1&b2) ^ (a2&b1) ^ (a2&b2)
        (I wasn't aware of this at first either)


        Complexity
        Time O(A + B)
        Space O(1)
    */

    int doit_(vector<int>& A, vector<int>& B) {
        int xora = 0, xorb = 0;
        for (int& a: A)
            xora ^= a;
        for (int& b: B)
            xorb ^= b;
        return xora & xorb;
    }
};