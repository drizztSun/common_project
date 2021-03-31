/*
1526. Minimum Number of Increments on Subarrays to Form a Target Array

Given an array of positive integers target and an array initial of same size with all zeros.

Return the minimum number of operations to form a target array from initial if you are allowed to do the following operation:

Choose any subarray from initial and increment each value by one.
The answer is guaranteed to fit within the range of a 32-bit signed integer.
 

Example 1:

Input: target = [1,2,3,2,1]
Output: 3
Explanation: We need at least 3 operations to form the target array from the initial array.
[0,0,0,0,0] increment 1 from index 0 to 4 (inclusive).
[1,1,1,1,1] increment 1 from index 1 to 3 (inclusive).
[1,2,2,2,1] increment 1 at index 2.
[1,2,3,2,1] target array is formed.
Example 2:

Input: target = [3,1,1,2]
Output: 4
Explanation: (initial)[0,0,0,0] -> [1,1,1,1] -> [1,1,1,2] -> [2,1,1,2] -> [3,1,1,2] (target).
Example 3:

Input: target = [3,1,5,4,2]
Output: 7
Explanation: (initial)[0,0,0,0,0] -> [1,1,1,1,1] -> [2,1,1,1,1] -> [3,1,1,1,1] 
                                  -> [3,1,2,2,2] -> [3,1,3,3,2] -> [3,1,4,4,2] -> [3,1,5,4,2] (target).
Example 4:

Input: target = [1,1,1,1]
Output: 1
 

Constraints:

1 <= target.length <= 10^5
1 <= target[i] <= 10^5
*/
#include <vector>
#include <algorithm>

using std::vector;


class MinimumNumberOfIncrements {

    /*
        1526.Minimum-Number-of-Increments-on-Subarrays-to-Form-a-Target-Array
        解法1： 线段树
        直观上说比较容易想到贪心的解决方案。第一步，我们肯定会挑选全局最小的元素target[i]，然后让整个数组都增加target[i]。此后任何操作都不可横跨整个数组。我们会选择递归处理[0:i-1]和[i+1:n-1]这两个区间。
        方法也类似，就是在[0:i-1]这个区间内找到最小的元素target[j]，让这段区间都增加至target[j]，既然我递归处理[0:j-1]和[j+1:i-1]这两个区间...

        所以上述方法的难点在于快速挑选一段区间内的最小元素和它所在的位置。这种数据结构显然合适线段树来处理。我们构建segmentTree的数据结构，提供一个函数[minVal, pos]=queryMin(start,end)来满足需求。递归的代码就是：

        void DFS(int a, int b, int cur)
            {
                if (a>b) return;
                auto x = queryTree(root, a, b);
                int val = x.first;
                int pos = x.second;
                if (val!=cur)
                    ret += (val-cur);
                DFS(a, pos-1, val);
                DFS(pos+1, b, val);            
            }
        解法2： 贪心法
        我们将target数组想象成连绵起伏的山峦。我们在上坡走的时候，每一步肯定都需要做“增加”的操作（相当于垒土造山）。但是在下坡走的时候实际上不需要任何操作，因为任何一个下坡的位置j，都可以找到一个对应的上坡位置i，
        可以认为在i位置通过“增加”操作成就了target[j]。举个例子：1 3 4 2。我们在处理j=3的时候，target[3]可以认为是在i=1的时候，对于区间[1:3]增加1而构造得到的。
        至于taget[1]=3本身，则可以认为是再通过一步对区间[1:2]增加1得到。这两个效果的叠加，等效于在i=1的位置，直接增加2，也就是target[1]相对于target[0]的增量。

        同理，当我们走过“山谷”，重新上坡的时候，又要开始计数“增加”的操作。
    */
    int doit_greedy(vector<int>& target) 
    {
        int ret = 0, curHeight = 0;
        for (int i=0; i<target.size(); i++)
        {
            ret += std::max(0, target[i] - curHeight);
            curHeight = target[i];
        }
        return ret;
    }
    
public:

    int doit_1(vector<int>& target) {

        int pre = 0, res = 0;
        
        for(int t : target) {

            if(t > pre) {
                res += (t - pre);
            }

            pre = t;
        }

        return res;
    }

    int doit_2(vector<int>& target) {
        
        auto minv = min_element(begin(target), end(target));
        int ans = *minv; 

        int prev = ans;
        int index = minv - begin(target);

        while (index >= 0) {
            if (target[index] > prev) 
                ans += target[index] - prev;
            prev = target[index];
            index--;
        }

        index = minv - begin(target);
        while (index < target.size()) {
            if (target[index] > prev)
                ans += target[index] - prev;
            prev = target[index];
            index++;
        }

        return ans;
    }


    class SegTreeNode
    {
        public:
        SegTreeNode* left;
        SegTreeNode* right;
        int start, end;
        int info, pos;               
        SegTreeNode(int a, int b):start(a),end(b),info(0),pos(0),left(NULL),right(NULL){}
    };
    
    void init(SegTreeNode* node, int a, int b)  // init for range [a,b]
    {                        
        if (a==b)
        {
            node->info = target[a];
            node->pos = a;
            return;
        }
        int mid = (a+b)/2;
        if (node->left==NULL)
        {
            node->left = new SegTreeNode(a, mid);
            node->right = new SegTreeNode(mid+1, b);
        }
        init(node->left, a, mid);
        init(node->right, mid+1, b);
                
        if (node->left->info < node->right->info)
        {
            node->info = node->left->info;
            node->pos = node->left->pos;
        }
        else
        {
            node->info = node->right->info;
            node->pos = node->right->pos;
        }
    }
    
    pair<int,int> queryRangeMin(SegTreeNode* node, int a, int b)
    {        
        if (b < node->start || a > node->end )
        {
            return {INT_MAX, a}; // write your own logic
        }
        if (a <= node->start && b>=node->end)
        {
            return {node->info, node->pos};  // write your own logic
        }  
        
        auto L = queryRangeMin(node->left, a, b);
        auto R = queryRangeMin(node->right, a, b);
        
        if (L.first < R.first)
            return L;
        else
            return R;
    }    
    
    SegTreeNode* root;        
    vector<int> target;
    
public:
    int minNumberOperations(vector<int>& target) 
    {
        this->target = target;        
        int n = target.size();
        
        root = new SegTreeNode(0, n-1);
        init(root, 0, n-1);        
        
        return DFS(target, 0, 0, n-1);
    }
    
    int DFS(vector<int>& target, int base, int a, int b)
    {
        if (a>b) return 0;
        if (a==b) return target[a] - base;
                
        auto [val, pos] = queryRangeMin(root, a, b);        
        int sum = val - base;
        sum += DFS(target, val, a, pos-1);
        sum += DFS(target, val, pos+1, b);    
        return sum;
    }
};