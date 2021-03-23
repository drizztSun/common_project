/*
715. Range Module

A Range Module is a module that tracks ranges of numbers. Your task is to design and implement the following interfaces in an efficient manner.

1. addRange(int left, int right) Adds the half-open interval [left, right), tracking every real number in that interval. 
        Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval [left, right) that are not already tracked.
2. queryRange(int left, int right) Returns true if and only if every real number in the interval [left, right) is currently being tracked.
3. removeRange(int left, int right) Stops tracking every real number currently being tracked in the interval [left, right).

Example 1:
    addRange(10, 20): null
    removeRange(14, 16): null
    queryRange(10, 14): true (Every number in [10, 14) is being tracked)
    queryRange(13, 15): false (Numbers like 14, 14.03, 14.17 in [13, 15) are not being tracked)
    queryRange(16, 17): true (The number 16 in [16, 17) is still being tracked, despite the remove operation)

Note:

A half open interval [left, right) denotes all real numbers left <= x < right.
0 < left < right < 10^9 in all calls to addRange, queryRange, removeRange.
The total number of calls to addRange in a single test case is at most 1000.
The total number of calls to queryRange in a single test case is at most 5000.
The total number of calls to removeRange in a single test case is at most 1000.
Accepted

*/

#include <map>

using std::map;

class RangeModule {


    /*
        715.Range-Module
        解法1：使用有序map
        对于这种interval类型的题目，我们选用ordered_map，将左边界作为key，右边界作为val，则所有的interval都按左边界从小到大排序。

        加入一个interval时，要考虑这么几点：

        新加入的区间是否和左边的某个区间部分重合？是的话，那么左边的那个区间就要拉长、重新赋值其右边界；如果不是，那么left就是一个新的左边界。
        新加入的区间是否和右边的某个区间部分重合？是的话，那么右边的那个区间就要删除它的key，其右边界将作为一个新区间的右边界。
        新加入的区间范围内的任何key都是需要抹去的。
        新建立一个区间。
        代码如下：

        int leftBound = left;
        auto pos1=Map.lower_bound(left);
        if (pos1!=Map.begin() && prev(pos1,1)->second >= left)  //左边界部分重合
            leftBound = prev(pos1,1)->first;
            
        int rightBound = right;
        auto pos2=Map.upper_bound(right);
        if (pos2!=Map.begin() && prev(pos2,1)->first <= right)  //右边界部分重合
            rightBound = max(right, prev(pos2,1)->second);
            
        Map.erase(pos1,pos2) // 删除一个前闭后开的迭代器区间
        Map[leftBound]=rightBound;
        删除一个interval时，要考虑这么几点：

        要删除的区间是否和左边的某个区间部分重合？是的话，那么左边的那个区间就要缩短，重新赋值其右边界。
        要删除的区间是否和右边的某个区间部分重合？是的话，那么右边的那个区间就要缩短，重新定义其左边界。
        要删除的区间范围内的任何key都是需要抹去的。
        代码如下：

        auto pos1=Map.lower_bound(left);
        bool flag1=0;
        if (pos1!=Map.begin() && prev(pos1,1)->second >= left)
        {
            flag1=1;
            temp1=prev(pos1,1)->second;
        }

        auto pos2=Map.lower_bound(right);
        bool flag=0;
        int temp2;
        if (pos2!=Map.begin() && prev(pos2,1)->second > right)
        {
            flag2=1;
            temp2=prev(pos2,1)->second;
        }

        Map.erase(pos1,pos2);
        if (flag1) Map[temp1]=left;
        if (flag2) Map[right]=temp2;
        特别注意，对于迭代器的修改操作，得安排在删除操作之后进行。
    */
    map<int,int>Map;

public:

    RangeModule() 
    {
        Map.clear();
    }
    
    void addRange(int left, int right) 
    {       
        auto pos1 = Map.lower_bound(left);
        int leftboundary=left;
        if (pos1!=Map.begin() && prev(pos1,1)->second>=left)
            leftboundary = prev(pos1,1)->first;
                            
        auto pos2 = Map.upper_bound(right);
        int rightboundary = right;
        if (pos2!=Map.begin())
            rightboundary = std::max(right, prev(pos2,1)->second);
        
        Map.erase(pos1,pos2);
        Map[leftboundary]=rightboundary;
    }
    
    bool queryRange(int left, int right) 
    {
        auto pos = Map.upper_bound(left);
        if (pos==Map.begin())
            return false;
        pos = prev(pos,1);
        return (pos->second>=right);
    }
    
    void removeRange(int left, int right) 
    {
        auto pos1 = Map.lower_bound(left);
        bool flag1=0;
        int temp1;
        if (pos1!=Map.begin() && prev(pos1,1)->second > left)
        {
            temp1 = prev(pos1,1)->first;
            flag1=1;
        }
        
        auto pos2 = Map.lower_bound(right);
        int temp2;
        bool flag2=0;        
        if (pos2!=Map.begin() && prev(pos2,1)->second > right)
        {
            temp2 = prev(pos2,1)->second;
            flag2=1;
        }
        
        Map.erase(pos1,pos2);
        if (flag1) Map[temp1]=left;
        if (flag2) Map[right]=temp2;
    }
};

/*        
    解法2：使用线段树
    此题适合标准的线段树模型和数据结构。从难度上将，本题是基于307和370基础上的更进一步，因为我们需要再设计一个remove的操作。

    在segTree类中，按照常规的操作，需要有如下成员变量

    int begin, end;
    bool status;
    segTree* left;
    setTree* right;
    这个类需要定义三个方法，除了之前我们已经学习实践过的setStatus和getStatus之外，需要一个remove.这个是用来保证线段树在空间上高效的重要操作。

    1. void remove(setTree* & node)
    2. bool setStatus(int a, int b, bool tracking)
    3. bool getStatus(int a, int b)
    首先我们特别关注一下remove。它是用来干什么的呢？我们设想，当我们在一个很大的范围内[a,b)做setStatus操作（比如设置为true)的时候，如果这个这个区间内已经有很多的子树（即说明其中有些区域是true，有些区域是false，这些子区间们可能犬牙交错），那么这些分支其实在这个操作之后都是完全可以“抹平”的。所以我们试图把这些子节点都删除，并把当前节点范围[start,end)内的status整体比标记为true。

            void remove(SegTree* &node)
            {
                if (!node) return;
                remove(node->left);
                remove(node->right);
                delete node;
                node = NULL;
            }
    接下来再看setStatus。线段树模板写熟了之后，就能知道我们总是根据三种情况讨论：1.[a,b]与这个区间完全不相交（一般就是返回） 2.[a,b]包括了整个区间（一般就是整体赋值），3. [a,b]与该区间相交，这种情况下基本都是要再递归处理。

    在这里，第二种情况下，我们需要添加一个remove操作，以保证线段树的空间高效。因为整体抹平的区间后，我们是不需要再有任何子区间的。另外，需要提醒的是，递归操作后，我们还需要及时更新当前区间的status。和之前的线段树的题目不同，我们这里，即使是非底层节点的status也是有意义的，true表示该区间都是tracked，反之就说明没有全部被tracked。这个对于getStatus函数是很有用的信息，这样我们就不用总是递归到最低层节点即可返回结果。

            void setStatus(int a, int b, int s)
            {
                if (begin>=b || end<=a)            // 1. [a,b]与这个区间不相交，返回原先的状态
                    return;                        
                if (a<=begin && end<=b)            // 2. [a,b]包括了整个区间，将该区间抹平
                {
                    remove(left);
                    remove(right);
                    status = s;
                    return;
                }         
                                                    // 3. 其他情况，[a,b]与该区间相交，需考虑其子树。
                if (!left)                          // 没有子树？那就自己建立子树，子树的status从当前节点继承。
                {
                    int mid = (end-begin)/2+begin;
                    left = new SegTree(begin,mid,status);
                    right = new SegTree(mid,end,status);
                }            
                leftStatus = left->setStatus(a,b,s);
                rightStatus = right->setStatus(a,b,s);
                status = left->status && right->status;     //记得更新当前节点的status
                return;
            }
    第三个方法就是getStatus。依然是套路，分三类讨论：1.完全不相交（这里就返回一个无关紧要的true），2.完全包含（这里就返回该节点区间的status），3.部分相交，基本上需要用到递归。当然，这里有个额外的小trick，也就是，如果当前节点已经没有子树了，也可以直接返回它的status。

            int getStatus(int a, int b)
            {
                if (begin>=b || end<=a)            // 1. [a,b]与这个区间不相交，返回一个不影响结果的状态
                    return true;            
                if (a<=begin && end<=b)            // 2. [a,b]包括了整个区间，返回该区间的状态
                    return status;                        
                if (!left)                         // 3. [a,b]与该区间相交，但又没有子树，返回整个区间状态
                    return status;
                int mid = (end-begin)/2+begin;      // 4. [a,b]与该区间相交，需要考虑其子树
                int leftStatus = left->getStatus(a,b);
                int rightStatus = right->getStatus(a,b);
                return leftStatus && rightStatus;            
            }
*/
class RangeModuleSegTree {

    class SegTree
    {
        public:
        int start, end;
        bool status;
        SegTree* left;
        SegTree* right;
        SegTree(int a, int b, bool T):start(a),end(b),status(T),left(NULL),right(NULL){}
        
        void remove(SegTree* &node)
        {
            if (node==NULL) return;
            remove(node->left);
            remove(node->right);
            delete node;
            node = NULL;
            return;
        }
        
        void setStatus(int a, int b, bool T)
        {
            if (a<=start && b>=end) // bottom condition 1: [a,b)>[start,end)
            {
                remove(left);
                remove(right);
                status = T;
                return;
            }
            if (a>=end || b<=start) // bottom condition 2: [a,b) do not intersect with [start,end)
                return;

            int mid = start+(end-start)/2;
            if (left==NULL)         // no children? create them!
            {
                left = new SegTree(start,mid,status);
                right = new SegTree(mid,end,status);
            }
            
            left->setStatus(a,b,T);
            right->setStatus(a,b,T);
            status =left->status && right->status;
        }        
        
        bool getStatus(int a, int b)
        {            
            if (a<=start && b>=end)   // bottom condition 1: [a,b)>[start,end)
                return status;
            
            if (a>=end || b<=start)     // bottom condition 2: [a,b) do not intersect with [start,end)
                return true;
            
            if (left==NULL)
                return status;
            
            int mid = start+(end-start)/2;
            bool L = left->getStatus(a,b);
            bool R = right->getStatus(a,b);
            return L&&R;
        }        
    };
    
public:
    
    SegTree root = SegTree(0,1e9,false);
    
    RangeModuleSegTree() {}
    
    void addRange(int left, int right) 
    {
        root.setStatus(left,right,true);
    }
    
    bool queryRange(int left, int right) 
    {        
        return root.getStatus(left,right);
    }
    
    void removeRange(int left, int right) 
    {
        root.setStatus(left,right,false);
    }
};