/*
352. Data Stream as Disjoint Intervals

Given a data stream input of non-negative integers a1, a2, ..., an, ..., summarize the numbers seen so far as a list of disjoint intervals.

For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:

[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]
 

Follow up:

What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?


352.Data-Stream-as-Disjoint-Intervals
方法1
本题需要一种数据结构，能够每扔进一个元素就能自动排序。我们很容易想到priority_queue。但是我们还需要能够便于查找元素，那么priority_queue就没有办法了，它本质是栈，只能一个一个读取。
我们这里采用的是有序集合（ordered set)，不仅能实现自动排序，它的lower_bound函数也很好用，可以log(N)地迅速定位查找。需要注意的是，集合的元素在物理内存上并不是连续的，所以迭代器（可以想象成指针）不能任意移动指定数目，只能通过重载的自增自减操作来实现移动。

本题中，集合的元素是自定义结构Interval，所以需要自己写自动比较排序的函数. 集合的定义和自定义比较函数如下：

struct cmp
{
   bool operator()(Interval a, Interval b)
   {
      return a.start<b.start;
   }
};

set<Interval,cmp>Set;
每当新进一个元素val，我们可以得到 auto it=Set.lower_bound(val) 表示定位到的指针。注意，根据自定义函数cmp，所有start比it->start严格小的区间都在it位置之前。

程序的主体根据这几种情况来分类考虑：

1. val是否已经存在一个区间里。需要把val和it所在区间上下限比较（如果it不是Set.end()的话)；注意，还需要把val和(it--)所代表区间的上下限比较（如果it不是Set.begin()的话）
2. val是否和一个已经存在的区间相邻接。如果 it!=Set.end() && val+1==it->start，那么把原来的it区间删除，加入一个更新了下界的区间。同理，如果it!=Set.begin()那么就可以考察it--，当it->end==val-1，那么把原来的it区间删除，加入一个更新了上界的区间。
3. 如果发现2里面我们操作了两次，说明有两个区间可以再合并。我们再次找到it；如果it!=Set.begin()那么就可以找到it--.把上述两个迭代器对应的元素从集合里删除，取代一个新的加入。
4. 如果发现1-3都没有操作，那么val就可以独立成为一个区间加入。

本题对于Set的迭代器操作要求概念明晰。

1. 知道对于集合，it+=1操作是不合法的，只有it++/it--操作才被合法重载。
2. 集合里的元素只能删除、增加，不可以修改，

方法2
将所有的元素都放在一个有序集合Set里，不着急处理。仅当需要输出区间数组时，根据这堆有序数列即时生成。这样就避免了考虑区间合并等复杂的处理。

根据数列生成区间的方法：遍历这个集合，不断更新start和end。当集合元素a!=end+1时，就可以根据start/end生成一个区间；同时更新 start=a, end=a.

方法3
使用有序的Map，key是左边界，val是右边界。总体思路和方法1差不多，需要完备考虑各种插入的情况。
*/
#include <vector>
#include <set>
#include <map>

using std::map;
using std::set;
using std::vector;

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

struct Interval {
    int start;
    int end;
    Interval(): start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};


class SummaryRangesV1 {
    struct cmp
    {
        bool operator()(Interval a, Interval b)
        {
            return a.start<b.end;
        }
    };
    set<Interval,cmp>Set;
    
public:
    /** Initialize your data structure here. */
    SummaryRangesV1() {
        
    }
    
    void addNum(int val) 
    {
        int flag=0;
        int a,b;
        
        // 空集特殊处理
        if (Set.size()==0)
        {
            Set.insert(Interval(val,val));
            return;
        }
        
        
        // 如果已经存在于已有的区间中，那么什么都不用做
        auto it = Set.lower_bound(Interval(val,val));            
        if (val>=it->start && val<=it->end)
            return;        
        
        if (it!=Set.begin())
        {
            it--;
            if (val>=it->start && val<=it->end)
                return;
        }
            
        // 如果可以与一个区间相接，那么更新那个区间
        it = Set.lower_bound(Interval(val,val));
        if (it!=Set.begin())
        {
            it--;
            if (it->end==val-1)
            {
                a = it->start;
                b = val;
                Set.erase(it);
                Set.insert(Interval(a,b));
                flag=1;
            }
        }
        

        it = Set.lower_bound(Interval(val,val));
        if (it!=Set.end() && it->start==val+1)
        {
            a = val;
            b = it->end;
            Set.erase(it);
            Set.insert(Interval(a,b));
            flag++;
        }
        
        // 如果更新了两个区间，说明这两个区间可以拼接起来。
        if (flag==2)
        {
            it = Set.lower_bound(Interval(val,val));
            if (it!=Set.begin() && it!=Set.end())
            {
                auto it0=it;
                it0--;
                if (it0->end==it->start)
                {
                    a=it0->start;
                    b=it->end;
                    Set.erase(it0);
                    Set.erase(it);
                    Set.insert(Interval(a,b));
                }
            }
        }
        // 没有相邻接的区间可以更新，那么就自己单独作为一个区间
        else if (flag==0)
        {
            Set.insert(Interval(val,val));
        }
        
        
    }
    
    vector<Interval> getIntervals() 
    {
        vector<Interval>results;
        for (auto a:Set)
            results.push_back(a);
        return results;
    }
};


class SummaryRangesV2 {
    set<int>Set;
    
public:
    /** Initialize your data structure here. */
    SummaryRangesV2() {
        
    }
    
    void addNum(int val) 
    {
        Set.insert(val);
    }
    
    vector<Interval> getIntervals() 
    {
        vector<Interval>result;
        int start;
        int end;
        int first=1;

        for (auto a:Set)
        {
            if (first)
            {
                start=a;
                end=a;
                first=0;
                continue;
            }
            
            if (a==end+1)
            {
                end=a;
            }
            else
            {
                Interval newInterval(start,end);
                result.push_back(newInterval);
                start=a;
                end=a;
            }
        }
        
        Interval newInterval(start,end);
        result.push_back(newInterval);        
        
        return result;
    }
};

class SummaryRangesV3 {

public:
    
    map<int,int>Map;
    
    /** Initialize your data structure here. */
    SummaryRangesV3() 
    {
        Map[-2]=-2;
    }
    
    void addNum(int val) 
    {
        auto pos = Map.lower_bound(val);

        if (pos!=Map.end() && pos->first==val) return;                        
        if (prev(pos,1)->second>=val) return;  // if val is already within an interval                                        
        
        if (prev(pos,1)->second==val-1)
            prev(pos,1)->second=val;   // if val is at the right boundary of the previous interval
        else        
            Map[val]=val;               // if val is not connected to the previous interval, create a new one
                
        pos = Map.upper_bound(val);        
        if (pos!=Map.end() && pos->first==prev(pos,1)->second+1) // if the new interval is conneted to the next interval
        {
            prev(pos,1)->second = pos->second;
            Map.erase(pos);
        }         
        
    }
    
    vector<Interval> getIntervals() 
    {
        vector<Interval>results;
        for (auto a:Map)
        {
            if (a.first!=-2)
                results.push_back(Interval(a.first,a.second));
        }
        return results;
    }
};