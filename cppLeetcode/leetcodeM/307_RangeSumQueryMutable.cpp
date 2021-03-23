/*
307. Range Sum Query - Mutable

Given an array nums and two types of queries where you should update the value of an index in the array, and retrieve the sum of a range in the array.

Implement the NumArray class:

. NumArray(int[] nums) initializes the object with the integer array nums.
. void update(int index, int val) updates the value of nums[index] to be val.
. int sumRange(int left, int right) returns the sum of the subarray nums[left, right] (i.e., nums[left] + nums[left + 1], ..., nums[right]).
 

Example 1:

Input
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
Output
[null, 9, null, 8]

Explanation
NumArray numArray = new NumArray([1, 3, 5]);
numArray.sumRange(0, 2); // return 9 = sum([1,3,5])
numArray.update(1, 2);   // nums = [1,2,5]
numArray.sumRange(0, 2); // return 8 = sum([1,2,5])
 

Constraints:

. 1 <= nums.length <= 3 * 104
. -100 <= nums[i] <= 100
. 0 <= index < nums.length
. -100 <= val <= 100
. 0 <= left <= right < nums.length
. At most 3 * 104 calls will be made to update and sumRange.


*/

#include <vector>

using std::vector;


class NumArray_BIT {

    vector<int> _nums;
    vector<int> bit;

    int getsums(int index) {
        int total = 0;
        while (index > 0) {
            total += bit[index];
            index -= index & (-index);
        }
        return total;
    }

public:

    NumArray_BIT(vector<int>& nums) {

        int n = nums.size();
        _nums = nums;
        bit.resize(n+1, 0);

        for (int i = 0; i < nums.size(); i++) {
            int base = i+1;
            while (base < n+1) {
                bit[base] += nums[i];
                base += base & (-base);
            }
        }
    }
    
    void update(int index, int val) {
        
        int diff = val - _nums[index];
        _nums[index] = val;
        index++;

        while (index < _nums.size()+1) {
            bit[index] += diff;
            index += index & (-index);
        } 
    }
    
    int sumRange(int left, int right) {
        return getsums(right + 1) - getsums(left);
    }
};


/*
    307.Range-Sum-Query-Mutable
    Binary Indexed Tree
    此题用到了一种比较不常见的数据结构 Binary Indexed Tree. 参考(http://www.cnblogs.com/grandyang/p/4985506.html). 总的来说，这种数据结构累加一部分元素，又留着一部分元素，是一种兼顾“查找元素本身”和“查找元素和”的中庸方法。

    这种数据结构的特征是：元素的标号（index）从1开始。第i个元素的变化，之后影响到的依次以此是 i+= (i&-i)。举个列子：
    第1个元素影响到：1,2,4,8,16，...  
    第2个元素影响到：2,4,8,16，...
    第3个元素影响到：3,4,8,16，...
    第4个元素影响到：4,8,16，...   总的来说，一个元素的变化，影响到整个Binary Indexed Tree的节点变化数目是 log(n)，比传统“累加和数组”牵一发动全身的数据结构而言，会优越很多。

    总结一下这种数据结构的初始化方法。nums是原始的数据（数组），tree是Binary Indexed Tree，本质也是一个数组。注意，两者的元素标号都是从1开始，标号为0的元素没有意义。

    for (int i=1; i<nums.size(); i++)
    {
        for (int j=i; j<nums.size(); j+=(j&-j))
        tree[i]+=nums[i];
    }
    相应地，如果想更新nums[i]，则对应的tree的变化

    int update(i,new_val)
    {
        int diff = new_val - nums[i];
        for (int j=i; j<nums.size(); j+=(j&-j))
        tree[j]+=diff;  
        nums[i] = new_val;  
    }
    对于nums前k个元素之和，需要在tree中累加的元素标号依次是 k-=(k&-k)，举个例子：
    nums的前8个元素之和，需要累加的的tree元素：8
    nums的前7个元素之和，需要累加的的tree元素：7,6,4
    nums的前6个元素之和，需要累加的的tree元素：6,4
    nums的前5个元素之和，需要累加的的tree元素：5,4
    由此看来，平均需要在tree里累加的元素和的数目也是log(n)，虽然比不上纯的累加数组，但也算很高效。

        int getSum(int i)
        {
            int res = 0;
            for (int j = i; j > 0; j -= (j&-j)) 
            {
                res += tree[j];
            }
            return res;        
        }
    Segment Tree
    除了Binary Indexed Tree，此题的另外一种解法是采用数据结构“线段树”。线段树的本质是一棵二叉树，每一个节点代表着一个区间。子节点区间都是父节点区间的二分子集。线段树适合的题型有非常鲜明的特点，即一个大区间的问题可以分解为若干小区间来求解并归并。比如一个大区间的sum，等于两个子区间sum的和；再比如，一个大区间的max，等于两个子区间max的最大值。构建线段树的时间复杂度、空间复杂度都是o(2n)，查询、更新（单个元素）是o(logn)，总和性能还不错。

    线段树的模板比较长，常见的操作包括buildTree，modifyTree和queryTree。但思路非常清晰简洁，如果写熟练了，并不比TrieNode模板慢。需要注意的是，在本题里，最底层的子树一定会是start==end，这种结构比较特殊，反而降低了难度。更general的线段树,会涉及到setStatus,getStatus,remove等操作,更难写一些。

    首先，我们来设计线段树的结构。和二叉树类似有左子树和右子树（默认是NULL），但关于自身节点的属性有三个:其中start,end表示了"线段"的起点和终点（在本题中就是数组的index区间,我们这里规定是一个左闭右也闭的区间），这对遍历整颗树非常关键。sum表示了该线段的属性（在本题中用作表示这个区间内元素的和），有点像二叉树里常规的val属性

    class SegmentTree
    {
        SegmentTree* left;
        SegmentTree* right;
        int sum;
        int start,end;
        SegmentTree(int a, int b):start(a),end(b),left(NULL),right(NULL){}
    };
    接下来，我们怎么来构建整棵树？本题中,我们已经有了所有的数据（完整的数组），想构建的是一棵近乎平衡的二叉树，显然用二分的思想不断向下递归即可。注意,本题中的线段区间就代表数组内元素index的区间,也就是说线段树内所有叶子节点的区间长度都是1,这是一类特殊的线段树,也更好些.如果线段区间表示的是值区间,则会更难写一些.

    SegmentTree* buildTree(vector<int>&nums, int a, int b)
    {    
        if (a>b) return NULL; //这个很关键,因为不断地二分过程中会造成这种情况
        node = new SegmentTree(a,b);
        if (a==b)
        {
            node->sum = nums[a];
            return node;
        }    
        node->left = buildTree(a,(a+b)/2);
        node->right = buildTree((a+b)/2+1,b);
        node->sum = node->left->sum + node->right->sum;
        return node;    
    }
    题目中的update,指的是修改这整颗树的某一个叶子节点,注意这个update会前一发动全身,所以它上级的节点的sum都会需要变动.我们怎么写这段程序呢?当然是根据线段的范围作为指引,一路朝叶子节点递归下去,返回的时候再次修改sum.

    void modifyTree(SegmentTree* node, int pos, int val)
    {
        if (pos==node->start && node->start==node->end) //说明找到的是叶子节点
        {
            node->sum = val;
            return;
        }
        int mid = root->start + (root->end-root->start)/2;
        if (pos<=mid)
            modifyTree(root->left,pos,val);
        else
            modifyTree(root->right,pos,val);
        root->sum = root->left->sum+root->right->sum;
    }
    题目中的sumRange,自然就是求区间和,明显也是根据左右子树的线段范围进行递归.

        int queryTree(SegmentTreeNode* root, int a, int b)
        {
            if (root->start==a && root->end==b) 
                return root->sum;
            
            int mid = root->start+(root->end-root->start)/2;
            if (b<=mid)
                return queryTree(root->left, a, b);
            else if (a>mid)
                return queryTree(root->right, a, b);
            else
                return queryTree(root->left,a,mid)+queryTree(root->right,mid+1,b);
        }

*/
  
class NumArray {
public:
    vector<int>bitArr;
    vector<int>nums;

    NumArray(vector<int>& nums) {
        this->nums = nums;
        bitArr.resize(nums.size()+1);
        for (int i=0; i<nums.size(); i++)
            my_update(i, nums[i]);
    }

    void update(int i, int val){
        my_update(i, val-nums[i]);
        nums[i] = val;
    }

    void my_update(int i, int delta) {
        int idx = i+1;
        while (idx<bitArr.size())
        {
            bitArr[idx]+=delta;
            idx+=idx&(-idx);
        }
    }

    int my_query(int idx){
        idx+=1;
        int result = 0;
        while (idx){
            result += bitArr[idx];
            idx-=idx&(-idx);
        }
        return result;
    }

    int sumRange(int i, int j) {
        return my_query(j)-my_query(i-1);
    }
};

class NumArray {
    class SegmentTreeNode
    {
        public:
        SegmentTreeNode* left;
        SegmentTreeNode* right;
        int start, end, sum;
        SegmentTreeNode(int a, int b):start(a),end(b),sum(0),left(NULL),right(NULL){}
    };
    SegmentTreeNode* root;
public:
    NumArray(vector<int> nums) 
    {
        int n=nums.size();
        root = buildTree(nums, 0, n-1);        
    }
    
    void update(int i, int val) 
    {
        modifyTree(root, i, val);
    }
    
    int sumRange(int i, int j) 
    {
        return queryTree(root, i, j);
    }
    
    SegmentTreeNode* buildTree(vector<int>&nums, int a, int b)
    {    
        if (a>b) return NULL; //这个很关键,因为不断地二分过程中会造成这种情况
        SegmentTreeNode* node = new SegmentTreeNode(a,b);
        if (a==b)
        {
            node->sum = nums[a];
            return node;
        }    
        node->left = buildTree(nums,a,(a+b)/2);
        node->right = buildTree(nums,(a+b)/2+1,b);
        node->sum = node->left->sum + node->right->sum;
        return node;    
    }
    
    void modifyTree(SegmentTreeNode* root, int i, int val)
    {
        if (root->start==i && root->end==i)
        {
            root->sum = val;
            return;
        }
        int mid = root->start + (root->end-root->start)/2;
        if (i<=mid)
            modifyTree(root->left,i,val);
        else
            modifyTree(root->right,i,val);
        root->sum = root->left->sum+root->right->sum;
    }
    
    int queryTree(SegmentTreeNode* root, int a, int b)
    {
        if (root->start==a && root->end==b) return root->sum;
        
        int mid = root->start+(root->end-root->start)/2;
        if (b<=mid)
            return queryTree(root->left, a, b);
        else if (a>mid)
            return queryTree(root->right, a, b);
        else
            return queryTree(root->left,a,mid)+queryTree(root->right,mid+1,b);
    }
};

class NumArray {
    
    class SegTree
    {
        public:
        int begin,end, status;
        SegTree* left;
        SegTree* right;
        SegTree(int a, int b, int s)
        {
            begin = a;
            end = b;
            status = s;
            left = NULL;
            right = NULL;
        }
        
        void remove(SegTree* &node)
        {
            if (!node) return;
            remove(node->left);
            remove(node->right);
            delete node;
            node = NULL;
        }
        
        
        int setStatus(int a, int b, int s)
        {
            if (begin>=b || end<=a)            // 1. [a,b]与这个区间不相交，返回原先的状态
                return status;                        
            if (a<=begin && end<=b)            // 2. [a,b]包括了整个区间，将该区间抹平
            {
                remove(left);
                remove(right);
                return status = s;
            }         
            if (!left)                         // 3. [a,b]与该区间相交，需考虑其子树
            {
                int mid = (end-begin)/2+begin;
                left = new SegTree(begin,mid,status);
                right = new SegTree(mid,end,status);
            }            
            int leftStatus = left->setStatus(a,b,s);
            int rightStatus = right->setStatus(a,b,s);
            return status = leftStatus + rightStatus;
        }
                
        int getStatus(int a, int b)
        {
            if (begin>=b || end<=a)            // 1. [a,b]与这个区间不相交，返回一个不影响结果的状态
                return 0;            
            if (a<=begin && end<=b)            // 2. [a,b]包括了整个区间，返回该区间的状态
                return status;                        
            if (!left)                         // 3. [a,b]与该区间相交，但又没有子树，返回整个区间状态
                return status;
            int mid = (end-begin)/2+begin;      // 4. [a,b]与该区间相交，需要考虑其子树
            int leftStatus = left->getStatus(a,b);
            int rightStatus = right->getStatus(a,b);
            return leftStatus + rightStatus;            
        }
            
};
    
    
public:
    SegTree* root;
        
    NumArray(vector<int> nums) 
    {
        root = new SegTree(0,nums.size(),0);        
        for (int i=0; i<nums.size(); i++)
            root->setStatus(i, i+1, nums[i]);
    }
    
    void update(int i, int val) 
    {
        root->setStatus(i,i+1,val);
    }
    
    int sumRange(int i, int j) 
    {
        return root->getStatus(i,j+1);
    }
};