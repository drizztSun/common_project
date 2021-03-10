/*
 1157. Online Majority Element In Subarray
 
 Implementing the class MajorityChecker, which has the following API:

 MajorityChecker(int[] arr) constructs an instance of MajorityChecker with the given array arr;
 int query(int left, int right, int threshold) has arguments such that:
 0 <= left <= right < arr.length representing a subarray of arr;
 2 * threshold > right - left + 1, ie. the threshold is always a strict majority of the length of the subarray
 Each query(...) returns the element in arr[left], arr[left+1], ..., arr[right] that occurs at least threshold times, or -1 if no such element exists.

  

 Example:

 MajorityChecker majorityChecker = new MajorityChecker([1,1,2,2,1,1]);
 majorityChecker.query(0,5,4); // returns 1
 majorityChecker.query(0,3,3); // returns -1
 majorityChecker.query(2,3,2); // returns 2
  

 Constraints:

 1 <= arr.length <= 20000
 1 <= arr[i] <= 20000
 For each query, 0 <= left <= right < len(arr)
 For each query, 2 * threshold > right - left + 1
 The number of queries is at most 10000

 
 
 */
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>

using std::set;
using std::unordered_map;
using std::vector;



class MajorityChecker {
    
    unordered_map<int, vector<int>> _num_idx;
    
    vector<int> _order_amount;
    
public:
    
    MajorityChecker(vector<int>& arr) {
        
        set<int> tmp;
        for (int i = 0; i < arr.size(); i++) {
            _num_idx[arr[i]].push_back(i);
            tmp.insert(arr[i]);
        }
        
        vector<int> order(begin(tmp), end(tmp));
        std::sort(begin(order), end(order), [&](auto a, auto b) {
            return _num_idx[a].size() > _num_idx[b].size();
        });
        
        _order_amount.swap(order);
    }
    
    int query(int left, int right, int threshold) {
        
        for (auto c : _order_amount) {
            
            if (_num_idx[c].size() < threshold) return -1;
            
            auto& target = _num_idx[c];
            
            int leftindex = std::lower_bound(begin(target), end(target), left) - begin(target);
            int rightindex = std::upper_bound(begin(target), end(target), right) - begin(target);
            
            if (rightindex - leftindex >= threshold)
                return c;
        }
        
        return -1;
    }
};

/*

    1157.Online-Majority-Element-In-Subarray
    Binary Search
    我的突破口是考虑出现频次最多的元素a，它应该有最大的概率是[left,right]区间内的majority。这个怎么判断呢？显然我们将所有出现a的位置按照从小到大的顺序列出来作为数组p，然后找到left和right能插入的位置。比如，我们找到pos1表示p里面第一个大于等于left的位置，pos2表示p里面最后一个小于等于right的位置。这样，pos2-pos1+1就是在[left,right]区间内a出现的次数。将其与threshold比较就可以判断是否满足题意。

    如果a不合题意，那么数组里剩余元素的总数total就减少了pos2-pos1+1个。如果频率次高的b也不符合题意，那么剩余的total会进一步减少。如果直到剩余的total小于threshold时，说明剩下的元素即使都是同一个，也无法满足题意了，此时就可以直接返回-1.

    Segment Tree
    本题也可以用线段树来实现，来实现高效地对任意区间内的majority元素的查询．

    和传统线段树一样，每个节点代表一个区间，并且不断向下二分，直至区间长度为１位置（叶子节点）．但此题最与众不同的技巧就是，每个节点的status记录的是：该区间内频次最高的元素（记录为val），以及val元素与其他非val元素的频次之差（记录为count).

    这个思想非常ｄｉａｏ，来自Boyer–Moore majority vote algorithm，可以联系169.Majority Element来理解．基本思想就是，如果一个属于majority的元素，与任何一个不属于majority的元素，两者同时消去，那么不影响数组剩下的元素里原本属于majority的元素的地位．

    假设区间d，下面二分了两个子区间d1和d2．如果在d1区间中的majority是val1,因为根据majority的定义，在d1的区间中val1必然必然比其他非val1元素的总个数还要多，记为count1. 同理，在另一个子区间中我们可以定义val2和count2. 显然，我们根据count1和count2的比较，就可以知道val1和val2谁是在区间d上的majority：

    (1) 如果count1>count2，则val1是majority，并且val1在ｄ上比其他元素的总频次还要高出count1-count2，因此记录count=count1-count2.

    (2) 反之说明val2是majority,并且val2在ｄ上比其他元素的总频次还要高出count2-count1,count=count2-count1.

    (3) 如果val1==val2，则更说明val1就是ｄ上的majority，并且它在频次上的优势会更大，变成count=count2+count1.

    (4) 而如果val1!=val2，但是count1==count2，那就是说明在区间ｄ上并没有唯一的majority（记住majority的定义就是大于50%），因此对于该节点我们就置val=0, count=0.

    通过上面递归的思想，我们就可以建立起一棵完全二叉树．每个节点代表的一个区间，并且记录了这个区间里的majority（如果存在的话）的值val，并且val的频次要比非val的频次多count个．

    然后我们处理query(left,right)时，就可以用这棵树的性质，递归处理得到[left,right]区间内的majority元素ｋｅｙ（如果存在的话）．然后再用二分搜索，在数组中元素ｋｅｙ的所出现的iｎｄｅｘ里（从小到大排列）找到left和right的位置，从而计算出ｋｅｙ实际在[left,right]区间内出现的频次，然后与threshold比较确定答案．

    query的具体算法：

    (1) 边界条件：如果节点是空指针，或者[left,right]区间与节点自身的区间完全不相交，则这个节点无法提供任何majority的信息，返回key=0, count=0.

    (2) 边界条件：如果[left,right]区间完全包括了节点自身的区间完全不相交，则这个节点能够提供在自身区间内的majority的信息，即返回node->val和node->count.

    (3) 其他情况（即两个区间只有部分相交，或者节点区间相对于[left,right]而言太大），都只能递归，让更短的子区间去处理．然后根据两个子区间反馈回来的key1,count1和key2,count2，进行合并处理，计算出自身区间内对于[left,right]的贡献．

    举个例子，我们想求[3,5]区间内的majority，但root节点区间是[0,7]，宽度太大，所以自身节点的val和count都不能反应这么一个小区间上的情况．显然只能递归考察左节点[0,3]和右节点[4,7]．就这样左子树一路递归，最终返回到root的其实是下面的节点[3,3]带来的key1和count1；　
    同理右子树一路递归，最终返回到root的其实是下面的节点[4,5]带来的key2和count2．我们此时需要将这两部分归并，仿照上面buildTree的操作，确定root区间内真正应该考察的[3,5]这个子段的majority.
*/

class MajorityChecker {
    
    unordered_map<int,vector<int>>Map;
    vector<std::pair<int,int>>q;

public:
    MajorityChecker(vector<int>& arr) 
    {
        for (int i=0; i<arr.size(); i++)
            Map[arr[i]].push_back(i);
                
        for (auto x: Map)
            q.push_back({x.second.size(), x.first});

        sort(q.begin(),q.end());        
        reverse(q.begin(),q.end());
    }
    
    int query(int left, int right, int threshold) 
    {
        int total = right-left+1;
        for (int i=0; i<q.size(); i++)
        {
            int num = q[i].second;
            int pos1 = lower_bound(Map[num].begin(), Map[num].end(), left) - Map[num].begin();
            int pos2 = upper_bound(Map[num].begin(), Map[num].end(), right) - Map[num].begin() - 1;
            
            if (pos2-pos1+1>=threshold)
                return num;
            else
                total -= pos2-pos1+1;
            if (total < threshold)
                return -1;
        }
        return -1;
    }
};



class MajorityChecker {
    class SegTree
    {
    public:
        SegTree* left;
        SegTree* right;
        int val, count;
        int start,end;        
        SegTree(int a, int b):start(a),end(b),val(0),count(0),left(NULL),right(NULL){}        
    };
    
    vector<int>arr;
    unordered_map<int,vector<int>>Map;

public:
    SegTree* root;
    
    MajorityChecker(vector<int>& arr) 
    {        
        this->arr = arr;
        root = buildTree(0, arr.size()-1);        
        for (int i=0; i<arr.size(); i++)
            Map[arr[i]].push_back(i);
    }
    
    int query(int left, int right, int threshold) 
    {
        int key = 0, val = 0;
        searchTreeMajority(root, left, right, key, val);
        if (key == 0) return -1;
        
        int pos1 = lower_bound(Map[key].begin(), Map[key].end(), left) - Map[key].begin();
        int pos2 = upper_bound(Map[key].begin(), Map[key].end(), right) - Map[key].begin() -1;
        
        if (pos2-pos1+1 >= threshold)
            return key;
        else
            return -1;        
    }
    
    SegTree* buildTree(int a, int b)
    {
        SegTree* node = new SegTree(a,b);
        
        if (a == b)
        {
            node->val = arr[a];
            node->count = 1;
            return node;
        }
        
        int mid = (a+b)/2;
        node->left = buildTree(a, mid);
        node->right = buildTree(mid+1, b);
        
        if (node->left->val==node->right->val)
        {
            node->val = node->left->val;
            node->count = node->left->count + node->right->count;
        }
        else if (node->left->count > node->right->count)
        {
            node->val = node->left->val;
            node->count = node->left->count - node->right->count;
        }
        else
        {
            node->val = node->right->val;
            node->count = node->right->count - node->left->count;
        }
        
        if (node->count==0)
            node->val = 0;
            
        return node;
    }
    
    
    bool searchTreeMajority(SegTree* node, int a, int b, int& key, int& count)
    {
        if (node==NULL || a>b)
            return false;
        
        if (node->start>b || node->end<a)
            return false;
        
        if (a<=node->start && node->end<=b)
        {
            key = node->val;
            count = node->count;
            return key!=0;
        }
        
        int key1, key2, count1, count2;
        int leftCheck = searchTreeMajority(node->left, a, b, key1, count1);
        int rightCheck = searchTreeMajority(node->right, a, b, key2, count2);
        
        if (!leftCheck && !rightCheck)
        {
            key = 0;
            count = 0;
        }
        else if (!leftCheck && rightCheck)
        {
            key = key2;
            count = count2;
        }
        else if (leftCheck && !rightCheck)
        {
            key = key1;
            count = count1;
        }
        else
        {
            if (key1==key2)
            {
                key = key1;
                count = count1+count2;
            }
            else if (count1==count2)
            {
                key = 0;
                count = 0;
            }
            else if (count1>count2)
            {
                key = key1;
                count = count1-count2;
            }
            else
            {
                key = key2;
                count = count2-count1;
            }                
        }
        
        return key!=0;
    }
    
};