/*
 1354. Construct Target Array With Multiple Sums
 
 
 Given an array of integers target. From a starting array, A consisting of all 1's, you may perform the following procedure :

 let x be the sum of all elements currently in your array.
 choose index i, such that 0 <= i < target.size and set the value of A at index i to x.
 You may repeat this procedure as many times as needed.
 Return True if it is possible to construct the target array from A otherwise return False.

  

 Example 1:

 Input: target = [9,3,5]
 Output: true
 Explanation: Start with [1, 1, 1]
 [1, 1, 1], sum = 3 choose index 1
 [1, 3, 1], sum = 5 choose index 2
 [1, 3, 5], sum = 9 choose index 0
 [9, 3, 5] Done
 Example 2:

 Input: target = [1,1,1,2]
 Output: false
 Explanation: Impossible to create target array from [1,1,1,1].
 Example 3:

 Input: target = [8,5]
 Output: true
  

 Constraints:

 N == target.length
 1 <= target.length <= 5 * 10^4
 1 <= target[i] <= 10^9
 
 
 */
#include <stdio.h>
#include <vector>
#include <queue>

using std::priority_queue;
using std::vector;


class ConstructTargetArray {

public:
    
    /*
     
     1354.Construct-Target-Array-With-Multiple-Sums
     本题的切入点是发现，每个回合得到的x只会越来越大。那么意味着我们在数组里设置的数也会越来越大。那么最后一轮完成构造target的时候，最后一个填入的数一定就是target里面的最大值a，这是一个已知量。那么假设最后一轮里，我们是把b替换成了a，那么b怎么求呢？

     last round:   x x x x x a
     last-1 round: x x x x x b
     根据题意，最后一轮的操作里，a是通过a = x+x+x+x+b得到的，所以b其实就是a-others（其中others=x+x+x+x）。于是我们就可以把a替换成上一轮的b。

     接着我们重复类似的操作，在当前的数组里找到最大的数字a，复原对应的b。直至最终所有的元素都是1或者发现计算出来的b不对劲（即b<=0）. 数据结构上用优先队列最为方便，每轮自动弹出数组里最大的元素。初步的代码如下

     while (pq.top()!=1)
     {
         long long a = pq.top();
         long long others = sum - a;
         pq.pop();

         long long b = a - others;
         if (b<=0) return false;
         
         sum = others + b;
         pq.push(b);
     }

    但是这段代码在处理这个case时遇到了TLE：[1,1000000000]. 我们发现如果依此还原每一步的话，这个数组的变化是：[1,999999999] => [1,999999998] => [1,999999997] => ... 朝最终答案前进的效率非常低。
    究其原因是每次a替换成b的时候，b明显仍然是整个数组里的最大值，如果将b放入优先队列中的话需要额外log(N)的操作来返回当前最大值，并不合算。

    所以处理的手段是：如果我们能预判将a变成b后，重新放回优先队列的话让然是最大值的话，我们就不放入pq。因为我们发现，当a远远大于others时，每次变成b的过程，减去的都是固定不变的others。
    所以这些连续相同的减法，不如直接用除法更高效。所以改动后的代码是：

     while (pq.top()!=1)
     {
         long long a = pq.top();
         long long others = sum - a;
         pq.pop();

         if (others ==0) return false;
         if (a - others <= 0) return false;
         long long b = a % others;
         
         sum = others + b;
         pq.push(b);
     }
    */
    
    bool doit_heap_greedy(vector<int>& target) {
        
        priority_queue<int> qu;
        long long sums = 0;

        for (auto c : target) {
            qu.push(c);
            sums += c;
        }
        
        while (qu.top() != 1) {
            
            // a is maximum number,
            long long a = qu.top();
            qu.pop();
            
            long long others = sums - a;
            /*
                lastround           x x x x x maxv
                lastround - 1       x x x x x b 
            */

            if (others == 0) return false;
            
            // a < others, false b + others = a, b = a - others
            if (a - others <= 0) return false;
            
            // compress multiple times substract to one dividmod ops. like, [1, 1000000] if each time minus 1, that will be huge.
            long long b = a % others; 
            
            sums = others + b;
            qu.push(b);
        }
        
        return true;
    }
};
