/*
# 699. Falling Squares

# On an infinite number line (x-axis), we drop given squares in the order they are given.

# The i-th square dropped (positions[i] = (left, side_length)) is a square with the left-most point
# being positions[i][0] and sidelength positions[i][1].

# The square is dropped with the bottom edge parallel to the number line, and from a higher height than
# all currently landed squares. We wait for each square to stick before dropping the next.

# The squares are infinitely sticky on their bottom edge, and will remain fixed to any positive length surface
# they touch (either the number line or another square).
# Squares dropped adjacent to each other will not stick together prematurely.


# Return a list ans of heights. Each height ans[i] represents the current highest height of any square we have dropped,
# after dropping squares represented by positions[0], positions[1], ..., positions[i].

# Example 1:
# Input: [[1, 2], [2, 3], [6, 1]]
# Output: [2, 5, 5]
# Explanation:

# After the first drop of positions[0] = [1, 2]:
# _aa
# _aa
# -------
# The maximum height of any square is 2.


# After the second drop of positions[1] = [2, 3]:
# __aaa
# __aaa
# __aaa
# _aa__
# _aa__
# --------------
# The maximum height of any square is 5.
# The larger square stays on top of the smaller square despite where its center
# of gravity is, because squares are infinitely sticky on their bottom edge.


# After the third drop of positions[1] = [6, 1]:
# __aaa
# __aaa
# __aaa
# _aa
# _aa___a
# --------------
# The maximum height of any square is still 5.

# Thus, we return an answer of [2, 5, 5].


# Example 2:
# Input: [[100, 100], [200, 100]]
# Output: [100, 100]
# Explanation: Adjacent squares don't get stuck prematurely - only their bottom edge can stick to surfaces.

# Note:

# 1 <= positions.length <= 1000.
# 1 <= positions[i][0] <= 10^8.
# 1 <= positions[i][1] <= 10^6.


*/

#include <vector>
#include <map>
#include <algorithm>
using namespace std;



class FallingSquares {

    class SegTree
    {
        public:
        int start,end,status;
        SegTree* left;
        SegTree* right;
        SegTree(int a,int b,int s):start(a),end(b),status(s),left(NULL),right(NULL){}
        
        void remove(SegTree* &node)
        {
            if (node==NULL) return;
            remove(node->left);
            remove(node->right);
            delete node;
            node=NULL;
            return;
        }
        
        void setStatus(int a, int b, int s)
        {
            if (a<=start && b>=end)
            {
                remove(left);
                remove(right);
                status = s;
                return;
            }
            
            if (a>=end || b<=start) return;

            if (left==NULL)
            {
                int mid = (end-start)/2+start;
                left = new SegTree(start,mid,status);
                right = new SegTree(mid,end,status);
            }
            left->setStatus(a,b,s);
            right->setStatus(a,b,s);
            status = max(left->status,right->status);
            return;
        }
        
        int getStatus(int a, int b)
        {
            if (a<=start && b>=end) return status;
            if (a>=end || b<=start) return 0;
            if (left==NULL)
                return status;
            int L = left->getStatus(a,b);
            int R = right->getStatus(a,b);
            return max(L,R);            
        }        
    };
public:
    vector<int> doit_segmenttree(vector<pair<int, int>>& positions) 
    {
        SegTree root = SegTree(0,1e9,0);
        vector<int>result;
        int curMax = 0;
        for (auto p:positions)
        {
            int cur = root.getStatus(p.first,p.first+p.second);
            curMax = max(curMax, cur+p.second);
            root.setStatus(p.first,p.first+p.second, cur+p.second);            
            result.push_back(curMax);                    
        }
        return result;
    }

    /*
        699.Falling-Squares
        解法1：使用Hash容器
        此题考查了对Hash结构（比如说Map和Set）的迭代器的操作。

        设置一个有序hash表，map<int,int>Map，其中的key表示在横轴上某个x的位置，value表示从这个x开始往右直至遇到下一个邻接x位置之间的高度（这个高度在这两个位置之间必须是平整的）。在不断读入positions的过程中，来更新这个Map。

        对于一个新引入的square，我们考察它的左右边界left,right在这个hash表中的位置（找最近邻元素的迭代器）

        auto ptri = Map.lower_bound(left);
        auto ptrj = Map.upper_bound(right);
        注意得到的两个边界迭代器的意义。ptri表示处于left或其靠右的第一个迭代器。ptrj表示在right靠右的第一个迭代器。

        根据题意，处于[ptri,ptrj)的那些hash元素都将被取代（抹平），换成这个新square的信息。这个新square叠加上去后的高度等于这些hash元素的最大值加上新square自身的高度。但是注意，以上对于 ptri->first == left时成立；但是对ptri->first > left时，我们必须把ptri之前的那个元素也考虑上，即 prev(ptri,1)。

        auto ptr= ptri->left==left? ptri:prev(ptri,1);
        int maxH=0;
        while (ptr!=ptrj)
        {
            maxH=max(maxH,ptr->second);
            ptr=next(ptr,1);
        }
        以上得到了新高度。但是如何抹平之前的呢？erase命令可以删除一个前闭后开的迭代器区间。特别强调，不能用for等循环名一边通过迭代器遍历hash、一边删改迭代器。这是会出错的。

        Map.erase(ptri,ptrj)
        接下来要跟新，即在Map里新加入一个区间。显然对于新sqaure的左边界，会引入：

        Map[left]= maxH+h;
        特别注意：对于新sqaure的右边界，同样也可能会引入新生成的边界。比如，当新square比较小，那么Map[right+1]应该是之前 prev(ptrj,1)对应的数值。这个数值必须在对Map做迭代器删改之前保留下来。

        解法2：使用线段树
        相比于 715.Range Module 使用的标准线段树模型，此题只需要对标准模型进行很小的改动即可适用。

        也即是每个线段的status不再是一个二值的状态，而是代表了[begin,end)区间里最大高度。每次处理一个正方形(x,y,d)，首先用getStatus(x,y)得到该区间内的最大高度maxH，然后在该相同的区间内setStatus(x,y,maxH+d)即可。整颗线段树的维护非常直观。

        相比与715，线段树模型的改动之处是：715题的setStatus里，status = left->status && right->status，现在改为 stuats = max(left->status, right->status)即可。      
    */
    vector<int> doit_hashtable(vector<pair<int, int>>& positions) 
    {
        map<int,int>Map;
        
        Map[0]=0;
        Map[INT_MAX]=0;
        
        vector<int>results;
        int cur=0;
        
        for (auto p:positions)
        {
            int left=p.first;
            int right=p.first+p.second-1;
            int h=p.second;
            int maxH=0;
            
            auto ptri = Map.lower_bound(left);
            auto ptrj = Map.upper_bound(right);
            
            int temp = prev(ptrj,1)->second;
            
            auto ptr = ptri->first==left? ptri:prev(ptri,1);
            while (ptr!=ptrj)            
            {
                maxH=max(maxH, ptr->second);
                ptr = next(ptr,1);
            }
            if (ptri!=ptrj)
                Map.erase(ptri,ptrj);
                            
            Map[left] = maxH+h;
            Map[right+1] = temp;            
            cur = max(cur, maxH+h);
            
            results.push_back(cur);    
        }
        
        return results;
    }

    vector<int> doit_hashtable_2(vector<pair<int, int>>& positions) 
    {
        map<int,int>Map;
        Map[0]=0;
        Map[INT_MAX]=0;
        int cur=0;
        vector<int>results;
        
        for (int i=0; i<positions.size(); i++)
        {
            int left=positions[i].first;            
            int len=positions[i].second;
            int right=left+len-1;
            
            auto pos1 = Map.lower_bound(left);
            
            int Hmax=0;
            auto pos=pos1;
            if (pos->first!=left) pos=prev(pos,1);
            while (pos->first <= right)            
            {
                Hmax = max(Hmax, pos->second);
                pos = next(pos,1);
            }
            int rightHeight = prev(pos,1)->second;
            
            Map.erase(pos1,pos);
            Map[left]=Hmax+len;
            Map[right+1]=rightHeight;                
            
            cur = max(cur, Hmax+len);
            results.push_back(cur);
        }
        
        return results;
    }



public:

    /*
        Similar to skyline concept, going from left to right the path is decomposed to consecutive segments, and each segment has a height.
        Each time we drop a new square, then update the level map by erasing & creating some new segments with possibly new height.
        There are at most 2n segments that are created / removed throughout the process,
        and the time complexity for each add/remove operation is O(log(n)).
    */
	vector<int> doit_hashtable(vector<vector<int>>&& positions) {

        vector<int> ret;
        map<int, int> r2h; // right to height, this heigh until this right
        r2h[INT_MAX] = 0;
        int maxh = 0;

        for(auto &position: positions){
            int l=position[0], d=position[1];
            int r = l + d;
            auto iter = r2h.upper_bound(l);  // O(logn) operation for set
            int wh = iter->second;
            if(!r2h.count(l)) 
				r2h[l] = wh;
            
			while(iter->first < r){
                // Erase the interval that will be overlapped. Each interval will be erased at most once.
                iter = r2h.erase(iter);
                wh = max(wh, iter->second);
            }
            // update the height of current interval
            r2h[r] = wh + d;
            maxh = max(maxh, wh+d);
            ret.push_back(maxh);
        }
        return ret;
	}
};