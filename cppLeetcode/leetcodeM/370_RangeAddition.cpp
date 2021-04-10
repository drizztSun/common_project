/*
370. Range Addition


Assume you have an array of length n initialized with all 0's and are given k update operations.

Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.

Return the modified array after all k operations were executed.

Example:

Input: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
Output: [-2,0,3,5,3]
Explanation:

Initial state:
[0,0,0,0,0]

After applying operation [1,3,2]:
[0,2,2,2,0]

After applying operation [2,4,3]:
[0,2,5,5,3]

After applying operation [0,2,-2]:
[-2,0,3,5,3]


*/


#include <vector>
#include <numeric>

using std::vector;


class ModifiedArray {

    /*
        370.Range-Addition
        解法1：
        此题比较简单的解法是用差分数组diff。diff[i]表示nums[i]比nums[i-1]大多少。这样如果已知nums[i-1]，那么就有diff[i]=nums[i-1]+diff[i]。本题中的三元参数update(i,j,k)恰好就是给出了这样的差分数组的信息：diff[i]+=k, diff[j+1]-=k.

        解法2：
        此题的线段树解法比307更进了一步。307中构造的线段树，是严格的二分到底，即最低层的节点必然有start==end。本题中则不一定，只要[start,end]区间中的状态都是一样的，那么就不会有再往下子树，这样可以节省很多空间。

        本题中，我们将节点的线段定义成一个左闭右开的区间[start,end)，个人觉得后续处理更方便些。状态status表示该区间内的元素的值。注意，在本题的线段树中，只有最底层节点的status才是真正有意义的。
        
        非底层节点，其区间内的值并不一致，所以没有意义，我们需要往下进一步拆分区间来探索。

        这题中，我们尝试将线段树中的常用操作（method）写入线段树的类（SegTree）里面，使得类的封装性更好。注意，本题我们只需要一个setStatus的方法，其他更复杂的线段树可能会需要getStatus和remove等操作。

        我们定义void setStatus(int a, int b, int s)表示往当前的线段树root里面，寻找一段区间[a,b)并将这段区间内的status设置为s。

        以下是模板化的setStatus的写法，分析见注释：

        class SegTree
        {
            ...
            void setStatus(int a, int b, int s)
            {
                    if (a<=start && b>=end && left==NULL)   
                    // 边界情况1：left==NULL表示这是底层节点，并且[a,b)包含了当前节点的整个区间[start,end)，所以可以直接操作这个区间的status
                    {
                        status += s;
                        return;
                    }
                    
                    // 边界情况2：[a,b)和当前节点的整个区间[start,end)完全不相交，没法做任何更新，直接返回
                    if (a>=end || b<=start)         
                        return;
                        
                    // 其他情况，说明我们无法对整个[start,end)做统一的操作，只能考察该节点的子节点。           
                    int mid = start+(end-start)/2;  
                    // 如果没有子节点怎么办？我们先创建子节点，子节点的status继承自父节点的status
                    if (left==NULL)                 
                    {
                        left = new SegTree(start,mid,status);
                        right = new SegTree(mid,end,status);
                    }                               
                    // 现在有了子节点，我们轻轻松松调用递归处理就可以了。
                    left->setStatus(a,b,s);
                    right->setStatus(a,b,s);
            }
        }
        将整棵线段树更新之后，本题求它所代表的所有区间内的每个元素值。我们只要用DFS的方法去遍历，读取所有底层节点的区间的status就行了。
    
    */
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) 
    {
        vector<int>diff(length+1,0);
        for (auto x:updates)
        {
            diff[x[0]]+=x[2];
            diff[x[1]+1]-=x[2];
        }
        vector<int>results;
        int cur = 0;
        for (int i=0; i<length; i++)
        {
            cur+=diff[i];
            results.push_back(cur);
        }
        return results;
    }

public:
    
    class SegTree{
    
    public:
        int start,end,status;
        SegTree* left;
        SegTree* right;
        SegTree(int a, int b, int s):start(a),end(b),status(s),left(NULL),right(NULL){}
        
        void setStatus(int a, int b, int s)
        {
            if (a<=start && b>=end && left==NULL)   // bottom node condition 1;
            {
                status += s;
                return;
            }

            // bottom node condition 2;
            if (a>=end || b<=start) return;
            
            int mid = start+(end-start)/2;  
            if (left==NULL)                 // no children? create them
            {
                left = new SegTree(start,mid,status);
                right = new SegTree(mid,end,status);
            }                               // recursion
            left->setStatus(a,b,s);
            right->setStatus(a,b,s);
        }
    };


    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) 
    {
        SegTree* root = new SegTree(0,length,0);
        for (auto x:updates)        
            root->setStatus(x[0],x[1]+1,x[2]);
        vector<int>results(length);
        DFS(root,results);
        return results;
    }

    void DFS(SegTree* node, vector<int>&results)
    {
        if (node->left!=NULL)
        {
            DFS(node->left,results);
            DFS(node->right,results);
            return;
        }
        for (int i=node->start; i<node->end; i++)
            results[i] = node->status;
    }

public:

    /*
        Approach 1: Naïve Approach
        Algorithm
        The algorithm is trivial. For each update query, we iterate over the required update range and update each element individually.
        Each query of updates is a tuple of 3 integers: start, endstart,end (the start and end indexes for the update range) and valval (the amount by which each array element in this range must be incremented).

        Complexity Analysis

        Time complexity : O(n⋅k) (worst case) where kk is the number of update queries and nn is the length of the array. Each of the kk update operations take up O(n)O(n) time (worst case, when all updates are over the entire range).
        Space complexity : O(1). No extra space required.
    */
    vector<int> doit_bruteforce(int length, vector<vector<int> > updates) {

        vector<int> result(length, 0);

        for (auto& tuple : updates) {
            int start = tuple[0], end = tuple[1], val = tuple[2];

            for (int i = start; i <= end; i++) {
                result[i] += val;
            }
        }

        return result;
    }

    /*
        Approach 2: Range Caching
        Intuition

        There is only one read query on the entire range, and it occurs at the end of all update queries. Additionally, the order of processing update queries is irrelevant.

        Cumulative sums or partial_sum operations apply the effects of past elements to the future elements in the sequence.

        Algorithm

        The algorithm makes use of the above intuition to simply store changes at the borders of the update ranges (instead of processing the entire range). 
        Finally a single post processing operation is carried out over the entire output array.
    */
    vector<int> doit_sweeplines(int length, vector<vector<int>>& updates) {

        vector<int> sweeplines(length + 1, 0);
        
        for (const auto& c: updates) {
            sweeplines[c[0]] += c[2];
            sweeplines[c[1]+1] -= c[2];
        }
        
        vector<int> ans(length);
        int total = 0;

        for (int i = 0; i < length; i++) {
            total += sweeplines[i];
            ans[i] = total;
        }
        
        return ans;
    }

    vector<int> doit_sweeplines(int length, vector<vector<int> > updates)
    {
        vector<int> result(length, 0);

        for (auto& tuple : updates) {
            int start = tuple[0], end = tuple[1], val = tuple[2];

            result[start] += val;
            if (end < length - 1)
                result[end + 1] -= val;
        }

        // partial_sum applies the following operation (by default) for the parameters {x[0], x[n], y[0]}:
        // y[0] = x[0]
        // y[1] = y[0] + x[1]
        // y[2] = y[1] + x[2]
        // ...  ...  ...
        // y[n] = y[n-1] + x[n]

        partial_sum(result.begin(), result.end(), result.begin());

        return result;
    }
};