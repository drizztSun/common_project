/*
 1352. Product of the Last K Numbers
 
 Implement the class ProductOfNumbers that supports two methods:

 1. add(int num)

 Adds the number num to the back of the current list of numbers.
 2. getProduct(int k)

 Returns the product of the last k numbers in the current list.
 You can assume that always the current list has at least k numbers.
 At any time, the product of any contiguous sequence of numbers will fit into a single 32-bit integer without overflowing.

  

 Example:

 Input
 ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
 [[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]

 Output
 [null,null,null,null,null,null,20,40,0,null,32]

 Explanation
 ProductOfNumbers productOfNumbers = new ProductOfNumbers();
 productOfNumbers.add(3);        // [3]
 productOfNumbers.add(0);        // [3,0]
 productOfNumbers.add(2);        // [3,0,2]
 productOfNumbers.add(5);        // [3,0,2,5]
 productOfNumbers.add(4);        // [3,0,2,5,4]
 productOfNumbers.getProduct(2); // return 20. The product of the last 2 numbers is 5 * 4 = 20
 productOfNumbers.getProduct(3); // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40
 productOfNumbers.getProduct(4); // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
 productOfNumbers.add(8);        // [3,0,2,5,4,8]
 productOfNumbers.getProduct(2); // return 32. The product of the last 2 numbers is 4 * 8 = 32
  

 Constraints:

 There will be at most 40000 operations considering both add and getProduct.
 0 <= num <= 100
 1 <= k <= 40000

 
 
 */
#include<vector>

using std::vector;


class ProductOfNumbers {
    
    vector<int> _buf;
    
public:
    
    ProductOfNumbers() {
        _buf.push_back(1);
    }
    
    void add(int num) {
        if (num != 0)
            _buf.push_back(_buf.back() * num);
        else
            _buf.resize(1);
    }
    
    int getProduct(int k) {
        if (k >= _buf.size())
            return 0;
        
        return _buf.back() / _buf[_buf.size() - k - 1];
    }
};

class ProductOfNumbers {
    
    vector<int> _nums;
    int lastzero = -1;
    
public:
    ProductOfNumbers() {
        _nums.push_back(1);
    }
    
    void add(int num) {
        if (num != 0)
            _nums.push_back(num * _nums.back());
        else {
            lastzero = _nums.size();
            _nums.push_back(1);
        }
    }
    
    int getProduct(int k) {
        int l = _nums.size()-k;
        if (l <= lastzero) {
            return 0;
        }

        return _nums.back() / _nums[l-1];
    }
};

/*
1352.Product-of-the-Last-K-Numbers
本题看第一眼就知道解法是构造前缀乘积的数组，令pre[i]表示从nums[1]连续乘到nums[i]的积。假设当前已经有n个元素，那么最后k个元素的乘积就是pre[n]/pre[n-k]。注意本题的约束条件里保证了前缀乘积数组不会溢出。

但是本题就这么简单吗？其实本题需要考察的是当年nums[i]=0的情况。我们发现一旦加入了0，那么会使得当前乃至之后的pre永远都是0，于是在getProduct时的计算公式pre[n]/pre[n-k]的表达式就会有除数为0的风险。那么如何解决这个问题呢？

首先，如果从n往前数的k个数包括了0，那么最终答案就是返回0. 其次，如果这k个数不包括0的话，那么如何保证pre[n]/pre[n-k]一定合法呢？我们可以认为把最近的0之前的数字都忽略掉，将整个pre数组从最近的0之后开始重新计数：也就是当nums[i]==1时，令pre[i]=1。
*/
class ProductOfNumbers {
    
    vector<int>pre;
    int id;
    int lastZero = 0;

public:
    ProductOfNumbers() 
    {
        id = 0;        
        pre.push_back(1);
    }
    
    void add(int num) 
    {   
        id++;     
        if (num!=0)
        {
            pre.push_back(pre.back()*num);
        }
            
        else
        {
            pre.push_back(1);
            lastZero = id;
        }
    }
    
    int getProduct(int k) 
    {
        if (lastZero <= id-k)
            return pre[id]/pre[id-k];
        else
            return 0;
    }
};

class ProductOfNumbers1 {

public:
    
    vector<int> v;
    int last_zero;
    
    ProductOfNumbers1()
    {
        v.clear();
        v.push_back(1);
        last_zero = -1;
    }
    
    void add(int num)
    {
        if(num==0 || v.back()==0)
        {
            if(num == 0)
                last_zero = v.size();
            v.push_back(num);
        }
        else
            v.push_back(v.back()*num);
    }
    
    int getProduct(int k)
    {
        int limit = v.size()-k;
        if(last_zero >= limit)
            return 0;
        
        if(v[limit-1] == 0)
            return v.back();
        
        return v.back()/v[limit-1];
    }
};
