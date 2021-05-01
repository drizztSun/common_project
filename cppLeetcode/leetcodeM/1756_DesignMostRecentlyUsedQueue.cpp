/*
1756. Design Most Recently Used Queue

Design a queue-like data structure that moves the most recently used element to the end of the queue.

Implement the MRUQueue class:

. MRUQueue(int n) constructs the MRUQueue with n elements: [1,2,3,...,n].
. fetch(int k) moves the kth element (1-indexed) to the end of the queue and returns it.
 

Example 1:

Input:
["MRUQueue", "fetch", "fetch", "fetch", "fetch"]
[[8], [3], [5], [2], [8]]
Output:
[null, 3, 6, 2, 2]

Explanation:
MRUQueue mRUQueue = new MRUQueue(8); // Initializes the queue to [1,2,3,4,5,6,7,8].
mRUQueue.fetch(3); // Moves the 3rd element (3) to the end of the queue to become [1,2,4,5,6,7,8,3] and returns it.
mRUQueue.fetch(5); // Moves the 5th element (6) to the end of the queue to become [1,2,4,5,7,8,3,6] and returns it.
mRUQueue.fetch(2); // Moves the 2nd element (2) to the end of the queue to become [1,4,5,7,8,3,6,2] and returns it.
mRUQueue.fetch(8); // The 8th element (2) is already at the end of the queue so just return it.
 

Constraints:

1 <= n <= 2000
1 <= k <= n
At most 2000 calls will be made to fetch.
 

Follow up: Finding an O(n) algorithm per fetch is a bit easy. Can you find an algorithm with a better complexity for each fetch call?

*/
#include <vector>
#include <list>

using std::list;
using std::vector;

/*
    1756.Design-Most-Recently-Used-Queue
    本题的算法是一种将o(N)复杂度降至o(sqrt(N))的经典方法。

    我们将整个队列用链表来维护。同时，将整个链表虚拟地分为若干个chunk，每一个chunk有恒定的step = sqrt(n)个元素（最后一个chunk除外）。我们另外用数组skip记录每份chunk的第一个元素的指针（迭代器）。

    如果我们要定位第k个元素（注意我们使用0-index更方便），我们可以知道它就在k/step个chunk。然后我们通过该chunk的首元素指针skip[k/step]开始，右移k%step次就可以定位到我们要找的元素。

    接下来我们要维护这个skip数组。因为第k个元素要被抽走，所以通常情况下，从第k/step+1个chunk开始，每个chunk的首元素指针多要往后顺移一位。有个特殊情况是，如果第k个元素本身就是该chunk的首元素，那么我们要从第k/step个chunk就开始移位。即

    int j = (k%step==0) ? k/step: k/step+1;
    for (int i=j; i<skip.size(); i++)
    skip[i] = next(skip[i]);
    特别注意的是我们的操作顺序：我们需要先把第k个元素添加在list的末尾，再做skip的位移，再做第链表中原k个元素的删除。
*/


class MRUQueue {
    list<int>List;
    vector<list<int>::iterator>skip;
    int step;
public:
    MRUQueue(int n) 
    {
        step = sqrt(n+1);
        for (int i=0; i<=n; i++)
        {
            List.push_back(i);
            if (i%step==0)
                skip.push_back(prev(List.end()));            
        }        
    }
    
    int fetch(int k) 
    {        
        int t = k / step;
        auto iter = skip[t];
        for (int i=0; i< k%step; i++)
            iter = next(iter);

        int ret = *iter;
        List.push_back(ret);
        
        int j = (k%step==0)?t:t+1;
        for (int i=j; i<skip.size(); i++)
            skip[i] = next(skip[i]);
        
        List.erase(iter);                
        return ret;
    }
};


class MRUQueue {

public:
    
    MRUQueue(int n) {
        m = sqrt(n);
        for(int i=1;i<=n;i++) push_back(i);
    }
    
    int fetch(int k) {
        for(auto& v:vv){
            if(k > v.size()) {
                k-=v.size();
                continue;
            }
            int x = v[k-1];
            v.erase(v.begin() + k-1);
            push_back(x);
            return x;
        }
        return -1;
    }
    
private:
    void push_back(int x){
        if(!vv.empty() && vv.back().size() < m) 
            vv.back().push_back(x);
        else 
            vv.push_back(vector<int>(1, x));
    }
    
    vector<vector<int>> vv;
    int m;
};