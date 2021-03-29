/*
386. Lexicographical Numbers

Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.

 

Example 1:

Input: n = 13
Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
Example 2:

Input: n = 2
Output: [1,2]
 

Constraints:

1 <= n <= 5 * 104
 

Follow up: Could you optimize your solution to use O(n) runtime and O(1) space?

*/

#include <vector>

using std::vector;


class LexicalOrder {

    /*
        386.Lexicographical-Numbers
        研究序列[1,10,11,12,13,2,3,4,5,6,7,8,9]，找出字典序的规律。

        规律1：不考虑上限，元素1后面跟什么元素？10, 100 … 也就是不断乘以10。

        规律2：如果99是上限，那么10后面的元素不能是100了，该怎么办？答案是11，也就是加1，这样个位上的数变大了。如果加1导致进位的话，虽然个位数变0，但十位上的数会变大，总之肯定字典序往后移。
        但此时得到的并不是下一个的目标，因为把其末尾的0去掉会得到字典序相对更前的数。砍掉0之后就可以重复规律1的操作了。

        规律3：如果上限是19，那么19后面的元素就不能是20了，该怎么办？答案是将19除以10，然后再重复规律2（也就是加1），也就是得到2，之后又可以重复规律1了。
    */
    vector<int> lexicalOrder(int n) 
    {
        int current=1;
        vector<int>results(n);
        
        for (int i=0; i<n; i++)
        {
            results[i]=current;
            
            if (current*10<=n)
                current=current*10;
            else
            {
                if (current+1>n) 
                    current=current/10;
                current++;
                while (current % 10==0)
                    current/=10;
            }
        }
        return results;
    }

public:
    
    vector<int> doit_greedy(int n) {
        
        vector<int> res(n);
        int current = 1;
        
        for (int i = 0; i < n; i++) {
            
            res[i] = current;
            
            if (current * 10 <= n) {
                current *= 10;
            } else {
                
                if (current + 1 > n)
                    current /= 10;
                current++;
                
                while (current % 10 == 0)
                    current /= 10;
            }
        }
        
        return res;
    }
};