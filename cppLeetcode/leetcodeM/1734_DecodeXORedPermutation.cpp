/*
1720. Decode XORed Array

There is a hidden integer array arr that consists of n non-negative integers.

It was encoded into another integer array encoded of length n - 1, such that encoded[i] = arr[i] XOR arr[i + 1]. For example, if arr = [1,0,2,1], then encoded = [1,2,3].

You are given the encoded array. You are also given an integer first, that is the first element of arr, i.e. arr[0].

Return the original array arr. It can be proved that the answer exists and is unique.

 

Example 1:

Input: encoded = [1,2,3], first = 1
Output: [1,0,2,1]
Explanation: If arr = [1,0,2,1], then first = 1 and encoded = [1 XOR 0, 0 XOR 2, 2 XOR 1] = [1,2,3]
Example 2:

Input: encoded = [6,2,7,3], first = 4
Output: [4,2,0,7,4]
 

Constraints:

2 <= n <= 10^4
encoded.length == n - 1
0 <= encoded[i] <= 10^5
0 <= first <= 10^5
*/


class DecodeXORArray {
public:
    vector<int> decode(vector<int>& encoded, int first) {

        vector<int> res(encoded.size()+1);
        res[0] = first;
        
        for (int i = 0; i < encoded.size(); i++) {
            res[i+1] = res[i] ^ encoded[i];
        }
        
        return res;
    }
};


/*
1734. Decode XORed Permutation

There is a hidden integer array arr that consists of n non-negative integers.

It was encoded into another integer array encoded of length n - 1, such that encoded[i] = arr[i] XOR arr[i + 1]. For example, if arr = [1,0,2,1], then encoded = [1,2,3].

You are given the encoded array. You are also given an integer first, that is the first element of arr, i.e. arr[0].

Return the original array arr. It can be proved that the answer exists and is unique.



Example 1:

Input: encoded = [1,2,3], first = 1
Output: [1,0,2,1]
Explanation: If arr = [1,0,2,1], then first = 1 and encoded = [1 XOR 0, 0 XOR 2, 2 XOR 1] = [1,2,3]
Example 2:

Input: encoded = [6,2,7,3], first = 4
Output: [4,2,0,7,4]


Constraints:

2 <= n <= 104
encoded.length == n - 1
0 <= encoded[i] <= 10^5
0 <= first <= 10^5

*/
#include <vector>

using std::vector;


class DecodeXORPermutation {

    /*
        1734.Decode-XORed-Permutation
        我们知道，XOR的最常用的一个性质就是x^x=0，我们需要尽量使用这个性质。但是我们发现如果把encode里面的元素全部XOR起来，大多数元素都会被消除，得到的只是头尾值nums[0]^nums[n-1].

        这时候我们注意到题目中说n是个奇数，这个条件很奇怪。仔细分析了一下，发现我们如果间隔着取encode里面的元素再XOR起来，就得到nohead = nums[1]^numx[2]^...^nums[n-1]，只缺少了nums[0]而已.
        这时候我们果断想到全局的XOR Sum其实是已知的（因为题目说的是1到n的permutation）。将nohead与XORSum再亦或一下，就得到了nums[0]。于是nums[1]就可以从encode[0]^nums[0]得到，其余的nums[i]也就迎刃而解。
    */
    vector<int> doit_(vector<int>& encoded) {

        int n = encoded.size()+1;
        int sum = 0;
        for (int i=1; i<=n; i++)
            sum ^= i;
                
        int nohead = 0;
        for (int i=1; i<encoded.size(); i+=2)
            nohead ^= encoded[i];
            
        int head = sum^nohead;

        vector<int>ret(n);        
        ret[0] = head;        
        for (int i=1; i<n; i++)
            ret[i] = encoded[i-1] ^ ret[i-1];
        
        return ret;
    }

public:

    /*
        Intuition
        If the first element is determined,
        the whole array can be decoded.
        1720. Decode XORed Array

        But if we enumerate the first element,
        the overall complexity will be O(n^2),
        which will be TLE.


        Explanation
        We make good use of the condition "n is odd" as follow
        a1,(a2,a3),(a4,a5).....,
        making the decoded into pairs.
        a2^a3 = A[1]
        a4^a5 = A[3]
        a6^a7 = A[5]
        ...
        so we can have the result of a2^a3^a4...^an.
        And a1,a2,a3... is a permuatation of 1,2,3,4..n

        so we can have
        a1 = 1^2^3...^n^a2^a2^a3...^an

        Then we can deduct the whole decoded array.


        Complexity
        Time O(n)
        Space O(n)
    */

    vector<int> doit_(vector<int>& encoded) {
        
        int a1 = 0;
        int n = encoded.size() + 1;
        
        for (int i = 1; i <= n; i++)
            a1 ^= i;

        for (int i = 1; i < n; i += 2) {
            a1 ^= encoded[i];
        }

        vector<int> res(n);
        res[0] = a1;
        for (int i = 1; i < n; i++)
            res[i] = res[i-1] ^ encoded[i-1];

        return res;
    }

    vector<int> doit_1(vector<int>& A) {
        int n = A.size() + 1, a = 0;
        for (int i = 0; i <= n; ++i) {
            a ^= i;
            if (i < n && i % 2 == 1) {
                a ^= A[i];
            }
        }
        vector<int> res = {a};
        for (int a: A) {
            res.push_back(res.back() ^ a);
        }
        return res;
    }
};