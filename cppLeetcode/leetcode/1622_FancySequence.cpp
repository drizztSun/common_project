/*
1622. Fancy Sequence

Write an API that generates fancy sequences using the append, addAll, and multAll operations.

Implement the Fancy class:

    . Fancy() Initializes the object with an empty sequence.
    . void append(val) Appends an integer val to the end of the sequence.
    . void addAll(inc) Increments all existing values in the sequence by an integer inc.
    . void multAll(m) Multiplies all existing values in the sequence by an integer m.
    . int getIndex(idx) Gets the current value at index idx (0-indexed) of the sequence modulo 109 + 7. If the index is greater or equal than the length of the sequence, return -1.
 

Example 1:

Input
["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
[[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
Output
[null, null, null, null, null, 10, null, null, null, 26, 34, 20]

Explanation
Fancy fancy = new Fancy();
fancy.append(2);   // fancy sequence: [2]
fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
fancy.append(7);   // fancy sequence: [5, 7]
fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
fancy.getIndex(0); // return 10
fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
fancy.append(10);  // fancy sequence: [13, 17, 10]
fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
fancy.getIndex(0); // return 26
fancy.getIndex(1); // return 34
fancy.getIndex(2); // return 20
 

Constraints:

1 <= val, inc, m <= 100
0 <= idx <= 10^5
At most 10^5 calls total will be made to append, addAll, multAll, and getIndex.

*/

#include <vector>
#include <map>

using std::map;
using std::vector;


/*
    1622.Fancy-Sequence
    我们想象一个这样的序列

    0 1 2 3 4 5  6  7 8 9 ...
    *     + ** +
    a     b cd e
    此时我们如果想getIdx(0)的话，除了取出nums[0]之外，还必须经过一系列的乘法和加法操作(((((num[0]*a)+b)*c)*d)+e)...，当然，最终我们肯定可以将其化简为nums[0]*mul+add.

    此时我们如果想getIdx(1)的话，其实处理方法和nums[0]是一模一样的，所以我们可以直接用nums[1]*mul+add.

    此时我们如果想getIdx(2)的话，情况就不一样了，不能用nums[2]*mul+add了，因为我们实际需要计算的是(((((num[2])+b)*c)*d)+e)...。那么我们还需要再重新把这一票算符再走一遍吗？可否直接利用之前化简得到的mul和add呢？其实是可以的。
    当我们在存nums[2]的时候，不存原始的数值，而是存入的是val = nums[2]/a的话，那么我们当我们调取getIdx(2)时，就可以使用val*mul+add这个表达式，因为它本质算的是(((((num[2]/a*a)+b)*c)*d)+e)...，恰好就是我们想要的结果。

    所以我们发现了一个规律，如果当前的化简算子是{mul,add}的时候，我们想要append一个新的数字nums[i]时，我们不直接append原始的数值，我们append一个虚拟的数值val用来“抵消”这对算子的影响，即使得nums[i] = val*mul+add。
    这样我们调用getIdx(i)的时候，仍然apply当前的化简算子{mul,add}得到val*mul+add，恰好就还原了真实的nums[i]。即使此后的{mul,add}可能会更新为{mul',add'}，但是val只是抵消了i之前的运算符的效果，
    并不会影响i之后的运算的作用，所以当再次调用getIdx(i)的时候，就可以放心地将{mul',add'}用在val上然后输出答案。

    接下来的一个关键问题，我们试图得到这个“抵消”后的val时，发现nums[i] = val*mul+add并不能保证得到一个整数的val= (nums[i]-add) / mul，如果存储的是小数的话，此后的误差会越来越大。
    另外一个更重要的问题是，mul会随着时间的推移有可能非常大直至越界。而如果为了避免mul越界而对其做了%M的操作的话，那么上面val的计算方法得到的结果就是错误的。因为(a/b)%M != a / (b%M)

    怎么办呢？事实上，我们并不需要存一个真实的val，我们只要存一个与val关于M同余的值就行了，我们记做val'。因为val'与val（关于M）同余，那么val'*mul+add就会与val*mul+add同余，也就是和最终的答案同余。而题目要求输出的就只是将答案对M取模的结果。

    想求(nums[i]-add) / mul关于M的同余，不能用“(nums[i]-add)关于M的同余”去除以“mul关于M的同余”，因为除法不满足 (a/b)%M = (a%M) / (b%M) 。正确的答案是 (nums[i]-add) * inv(mul)。其中inv(mul)称之为mul的逆元。满足如下关系的a和b称之为逆元：

    x / a ≡ x * b (mod M)
    写作b=inv(a)。存在a的逆元的充要条件是a与M互质。

    有了以上的知识，我们求val时，不要计算val= (nums[i]-add) / mul，而是计算val= (nums[i]-add) * inv(mul) % M。有人会疑问，前者是个小数，后者是个整数，怎么可能相等呢？确实不是相等的，而是同余的。注意查看之前的表达式，有了逆元的概念，同余并不依赖于x/a是否为整数。
    也就是说，允许小数val与某个整数val'同余，这样当我们同时乘以某个数k时，val*k依然与val'*k同余，而此时前者可能已经是个整数了。

    关于逆元的解法inv(a)，请参见这里的笔记。
*/

class Fancy {

    using LL = long long;
    LL M = 1e9+7;

    LL add, mul;
    vector<LL>nums;
    
    LL quickPow(int x, int y) 
    {
        int ret = 1;
        int cur = x;
        while (y) 
        {
            if (y & 1) 
            {
                ret = (long long)ret * cur % M;
            }
            cur = (long long)cur * cur % M;
            y >>= 1;
        }
        return ret;
    }
    
    LL inv(int x) 
    {
        return quickPow(x, M - 2);
    }
    
public:
    Fancy() {
        mul = 1;
        add = 0;
    }
    
    void append(int val) 
    {
        /*
            before append(val)

            {mul, add}

            append val, s.t val * mul + add = nums[i]

            {mul', add}
            getIdx(i) => val*mul' + add'


            append: val = (nums[i]-add) / mul
            val' = (nums[i]-add) * inv(mul)
            
            val' % M == val % M
            val' % M == val * k % M

            inverse element
            x / a = x * b (mod M)   <=> a and M hu zhi shu
            b = inv(a), a = inv(b)

            一般地，我们说如果a和b满足这样的性质：

            x / a ≡ x * b (mod M)
            从形式上来看，b好像就与1/a（在同余的意义上）等价，所以我们称b就是a的逆元，记做 b = inv(a)（反之也成立）。
            对于a而言，存在逆元的充要条件是a与M互质。当然，我们做题时M一般都已经是质数。

            逆元的计算方法
            方法1：快速幂法
            根据费马小定理，我们有

            inv(a) ≡ a ^ (M-2)  (mod M)
            显然，我们需要利用快速幂来计算这个数。

            方法2：线性求逆元
            如果我们想求1,2,3...N 每个数的逆元：

            const ll N = 1e6+7, M = 998244353;
            ll inv[N];
            int i;
            for(inv[1]=1, i=2; i<N; ++i)
                inv[i] = (M - M/i) * inv[M % i] % M
            逆元的一些性质
            逆元的计算有如下的性质：

            x1/y1 + x2/y2 ≡ x1 * y1^-1 + x2 * y2^-1 (mod M)
            x1/y1/y2 ≡ x1 * y1^-1 * y2^-1 (mod M)
        */
        val = (val-add+M) % M;
        val = (val * inv(mul)) % M;
        nums.push_back(val);
    }
    
    void addAll(int inc) 
    {
        add = (add + inc) % M;
    }
    
    void multAll(int m) 
    {
        mul = (mul*m) % M;
        add = (add*m) % M;
    }
    
    int getIndex(int idx) 
    {
        if (idx >= nums.size())
            return -1;
        return (nums[idx]*mul % M + add) % M;
    }
};




class Fancy {

    int M = 1e9 + 7;
    vector<int> v;
    int64_t T[4] = {1, 0, 0, 1}; // transformation matrix
    
public:
    Fancy() {}
    
    static int powmod(int64_t x, int p) {
        int64_t res = 1;
        while(p > 0) {
            if (p & 1)
                res = (res * x) % M;
            p >>= 1;
            x = (x * x) % M;
        }
        return res;
    }
    
    void append(int value) {
        // insert T^-1 * v
        
        //int det = ((T[0] * T[3])%M - (T[1]*T[2])%M) % M;
        //int det = T[0];
        
        // x <- det^-1 * (t3 * v - t1) = (t3 * v - 1) * det^(M-2) because M is prime
        //int x = ( (T[3] * value) % M - T[1]) * powmod(det, M-2) % M;
        int x = ( value % M - T[1]) * powmod(T[0], M-2) % M;
        
        v.push_back(x);
    }
    
    void addAll(int inc) {
        // T =  | 1 inc | T
        //      | 0  1  | 
        
        //T[0] = (T[0] + T[2] * inc) % M;
        //T[1] = (T[1] + T[3] * inc) % M;
        T[1] = (T[1] + inc) % M;
    }
    
    void multAll(int m) {
        // T = | m 0 | T
        //     | 0 1 |
        
        T[0] = (T[0] * m) % M;
        T[1] = (T[1] * m) % M;
    }
    
    int getIndex(int idx) {
        // T | v[i] |
        //   |  1   |
        
        if (idx >= v.size()) return -1;
        int r = (T[0] * v[idx] + T[1]) % M;
        if (r < 0) r += M;
        return r;
    }
};


/*
    Explanation
    Count the prefix sum add of addAll
    Count the prefix mul mul of mulAll

    Complexity
    Time O(1) for all
    Space O(N)
*/
class Fancy {

    using LL = long long;
    int hMod = 1e9 + 7;
    vector<LL> _nums;
    vector<LL> _mul, _add;

public:
    
    Fancy() {
        _mul.push_back(1);
        _add.push_back(0);
    }
    
    void append(int val) {
        _nums.push_back(val);
        _mul.push_back(_mul.back());
        _add.push_back(_add.back());
    }
    
    void addAll(int inc) {
        _add.back() += inc;
    }
    
    void multAll(int m) {
        _add.back() = (_add.back() * m) % hMod;
        _mul.back() = (_mul.back() * m) % hMod;
    }
    
    int getIndex(int idx) {
        if (idx >= _nums.size()) return -1;

        LL m = _mul.back() * pow(_mul[idx], hMod - 2);
        LL inc = _add.back() - _add[idx] * m;
        return (_nums[idx] * m + inc) % hMod; 
    }
};