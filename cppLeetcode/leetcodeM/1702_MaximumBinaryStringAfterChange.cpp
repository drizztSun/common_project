/*
1702. Maximum Binary String After Change

You are given a binary string binary consisting of only 0's or 1's. You can apply each of the following operations any number of times:

Operation 1: If the number contains the substring "00", you can replace it with "10".
For example, "00010" -> "10010"

Operation 2: If the number contains the substring "10", you can replace it with "01".
For example, "00010" -> "00001"

Return the maximum binary string you can obtain after any number of operations. Binary string x is greater than binary string y if x's decimal representation is greater than y's decimal representation.

 

Example 1:

Input: binary = "000110"
Output: "111011"
Explanation: A valid transformation sequence can be:
"000110" -> "000101" 
"000101" -> "100101" 
"100101" -> "110101" 
"110101" -> "110011" 
"110011" -> "111011"
Example 2:

Input: binary = "01"
Output: "01"
Explanation: "01" cannot be transformed any further.
 

Constraints:

1 <= binary.length <= 10^5
binary consist of '0' and '1'.



*/
#include <string>


using std::string;


class MaximumBinaryString {

public:


    /*  
        Explanation
        We don't need touch the starting 1s, they are already good.

        For the rest part,
        we continually take operation 2,
        making the string like 00...00011...11

        Then we continually take operation 1,
        making the string like 11...11011...11.


        Complexity
        Time O(n)
        Space O(n)
    */
    string doit_greeedy(string s) {
        int ones = 0, zeros = 0, n = s.length();
        for (auto& c : s) {
            if (c == '0')
                zeros++;
            else if (zeros == 0)
                ones++;
            c = '1';
        }

        if (ones < n)
            s[ones + zeros - 1] = '0';
        
        return s;
    }

    /*
        1702.Maximum-Binary-String-After-Change
        将字符串最大化的最高效的一步操作，就是将最高位的0变成1.而我们能用的规则就是操作1："00"->"10"。但是这一步需要0后面有个额外的0才能实现。

        那么0后面紧接着的如果是个1怎么办呢？这时候观察操作2，它的本质就是将0往前移动。这说明如果只要字符串的后面还有0，就可以将它提上来凑成两个连续的0，利用规则1，将此时最高位的0变成1.

        more higher '10' to '01' first, than lower '10'. Then it will save '00' => '10' => '01' it will waster 0

        接下来，此时最高位的0就是之前被提上来的0。想要将它也变成1的话，也需要同样的步骤：将字符串后面的0提前，凑成连续的两个0，再把最高位置成1.

        可以想见，如果原先的字符串里有m个0的话，那么从最高位的0开始，连续m-1个位置都会重复上面的操作。最终留下第m个位置上是0，这是整个字符串目前为止仅剩的一个0，我们再也无法做其他操作使其变大了。

        10 => 01. it puts 0 forward, so if 1000010 => 1000001 => 01000001 => 00100001 => 10100001 => 100100001 => 110100001 => 111111011
        final result is only one 0, and all other 1. 0 should be in 
    */
    string doit_greedy(string binary) {
        
        int n = binary.size();
        int m = 0;

        for (auto c: binary)
            if (c == '0') m++;

        if (m <= 1) return binary;


        string ret;
        int i = 0;
        // "111111100010000001111111"
        while (i < binary.size() && binary[i] == '1') {
            ret += '1';
            i++;
        }

        for (int i = 0; i < m-1; i++)
            ret += '1';

        ret += '0';

        while (ret.size() < n)
            ret += '1';

        return ret;
    }
};