/*
 1649. Create Sorted Array through Instructions
 
 
 Given an integer array instructions, you are asked to create a sorted array from the elements in instructions.
 You start with an empty container nums. For each element from left to right in instructions, insert it into nums.
 The cost of each insertion is the minimum of the following:

  . The number of elements currently in nums that are strictly less than instructions[i].
  . The number of elements currently in nums that are strictly greater than instructions[i].
 For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1)
 (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].

 Return the total cost to insert all elements from instructions into nums. Since the answer may be large, return it modulo 109 + 7



 Example 1:

 Input: instructions = [1,5,6,2]
 Output: 1
 Explanation: Begin with nums = [].
 Insert 1 with cost min(0, 0) = 0, now nums = [1].
 Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
 Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
 Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
 The total cost is 0 + 0 + 0 + 1 = 1.
 Example 2:

 Input: instructions = [1,2,3,6,5,4]
 Output: 3
 Explanation: Begin with nums = [].
 Insert 1 with cost min(0, 0) = 0, now nums = [1].
 Insert 2 with cost min(1, 0) = 0, now nums = [1,2].
 Insert 3 with cost min(2, 0) = 0, now nums = [1,2,3].
 Insert 6 with cost min(3, 0) = 0, now nums = [1,2,3,6].
 Insert 5 with cost min(3, 1) = 1, now nums = [1,2,3,5,6].
 Insert 4 with cost min(3, 2) = 2, now nums = [1,2,3,4,5,6].
 The total cost is 0 + 0 + 0 + 0 + 1 + 2 = 3.
 Example 3:

 Input: instructions = [1,3,3,3,2,4,2,1,2]
 Output: 4
 Explanation: Begin with nums = [].
 Insert 1 with cost min(0, 0) = 0, now nums = [1].
 Insert 3 with cost min(1, 0) = 0, now nums = [1,3].
 Insert 3 with cost min(1, 0) = 0, now nums = [1,3,3].
 Insert 3 with cost min(1, 0) = 0, now nums = [1,3,3,3].
 Insert 2 with cost min(1, 3) = 1, now nums = [1,2,3,3,3].
 Insert 4 with cost min(5, 0) = 0, now nums = [1,2,3,3,3,4].
 Insert 2 with cost min(1, 4) = 1, now nums = [1,2,2,3,3,3,4].
 Insert 1 with cost min(0, 6) = 0, now nums = [1,1,2,2,3,3,3,4].
 Insert 2 with cost min(2, 4) = 2, now nums = [1,1,2,2,2,3,3,3,4].
 The total cost is 0 + 0 + 0 + 0 + 1 + 0 + 1 + 0 + 2 = 4.


 Constraints:

 1 <= instructions.length <= 10^5
 1 <= instructions[i] <= 10^5
 
 
 */
#include <algorithm>
#include <vector>
#include <functional>
#include <set>
#include <unordered_map>

using std::set;
using std::vector;
using std::unordered_map;

class CreateSortedArrayThroughInstructions {

public:

    /*
        Here is problem in thought. If we maintain a sorted array and use lower_bound/upper_bound to check the possible and count the left/right side length;
        but when we insert an element, it still needs to move elements with O(n) compexity.
        If we use O(logn) in MapTree, but MapTree doesn't support to use iter index to count left/right side length.
        so we have to use BIT/Segment Tree, use 
    */
    int doit_BIT(vector<int>& instructions) {
        
        int m = *max_element(begin(instructions), end(instructions)) + 2;
        vector<int> bitbuff(m, 0);
        long long ans = 0;
        int mod = 1e9+7;
        
        auto update = [&](int c, int v = 1) {
            c += 1;
            while (c < m) {
                bitbuff[c] += v;
                c += c & (-c);
            }
        };
        
        auto query = [&](int c) {
            c += 1;
            int res = 0;
            while (c > 0) {
                res += bitbuff[c];
                c -= c & (-c);
            }
            return res;
        };
        
        for (int i = 0; i < instructions.size(); i++) {
            int c = instructions[i];
            int leftCnt = query(c-1);
            int rightCnt = i - query(c);
            ans = (ans + int(std::min(leftCnt, rightCnt))) % mod;
            update(c);
        }
        
        return ans;
    }

    /*
        1649.Create-Sorted-Array-through-Instructions
        解法1：分治法（归并排序）
        遍历这个数组里的每个元素，对于nums[i]，其实我们需要求的其实就是数一下[0,i-1]里有多少个元素严格比它小（或者大）。这不就是Count-of-Smaller-Numbers-Before-Self吗？立马联想到LC315.Count-of-Smaller-Numbers-After-Self，这是一道标准的分治法+归并排序的题。

        所谓的“分治+归并排序”，抽象地说，是对研究原数组的问题，拆分为两个小数组的问题（有点像递归）。但是注意，分别解决完这两个小数组的问题，并不意味着就解决了整个大数组的问题。我们在递归的过程中，将这两个小数组保持有序，然后再归并成一个有序的大数组。
        
        这个归并的过程中，可以额外做些操作来彻底解决这个大数组的问题。

        就本题而言，数组A按照index的先后拆分为两个小数组B和C。我们递归处理，得到B里面每个元素的Count-of-Smaller-Numbers-Before-Self，另外得到C里面每个元素的Count-of-Smaller-Numbers-Before-Self。然后我们再试图求解A问题。
        我们发现，A里面的B部分元素已经不需要再做任何更新了（B的所有smaller numbers before self依然在B里面，而B的问题已经解决了）。但是A里面的C部分元素还没有完全求解，因为B里面也有不少元素是C元素的smaller numbers before self。
        所以如果B是有序的话，那么我们就很容易通过二分法，求得B里面有多少个元素比C[i]小，那么C[i]的最终结果就可以得到进一步的更新。注意，结束之后我们需要将B和C归并起来得到一个有序的A，返回上一层的调用。

        本题OJ对于这种方法的C++解法要求很苛刻，必须全部采用数组（而非vector）才有可能AC。

        解法2：树状数组
        根据数组元素的范围，我们开辟一个计数数组count[100001].如果我们遇到nums[i]，那么就相应的在计数器count[nums[i]]++。于是，对于nums[i]的Count-of-Smaller-Numbers-Before-Self，本质上就是求count数组在区间[1,nums[i]-1]上的和。
        对于一个mutable array，动态地求区间和，那么BIT或者线段树是最合适的数据结构。

        BIT的模板相对更简单一些。简单的说，我们将1-index的原数组nums，做一些变换映射到1-index的新数组bitArray.我们对于nums的单点更新、区间求和，都可以映射成在bitArray上的一些操作。
        BIT提供了两个API，分别是update(i,delta)和querySum(i,j)，前者是用来单点更新nums[i]+=delta，后者是用来求区间nums[i:j]的和。


        解法3：线段树
        我们构造一棵线段树，线段树中的叶子节点代表着instruction里出现过的ordered distinct number，节点的info表示该数字出现的频次。注意，在初始建树的时候，所有节点的info都是零。

        记instruction[i]为x。每一个回合，我们需要分别统计这棵树里小于x的叶子节点个数、大于x的叶子节点个数。但我们不必关心x的数值。我们只需要知道x对应的index，这样我们就是在线段树中查询区间[0,index-1]的叶子节点的总频次（即info的总和）、以及查询区间[index+1,n-1]的叶子节点的info总和。所以我们需要一个方法queryRangeFreq(root,a,b).

        在这个回合结束之后，我们将x加入这棵线段树。注意我们不需要新增节点，我们只是将数值为x的叶子节点的频次加1（事实上就是将第index个元素加1），所以我们需要一个方法updateSingleNode(root, index)。

        因为我们不关心instruction里面每个元素x的具体数值，只关心他们在线段树中的位置。所以我们预处理的时候要做“离散化”，建立x和index的映射关系。
    */

public:

    int doit_divide_and_conquer(vector<int>& nums) 
    {
        int numSmaller[100005];
        int temp[100005];    
        int count[100005];
        int sorted[100005];
        int M = 1e9+7;

        int n = nums.size();
        for (int i=0; i<n; i++)
            sorted[i] = nums[i];

        std::function<void(int, int)> helper = [&](int a, int b) {

            if (a>=b) return;        
            
            int mid = a+(b-a)/2;
            helper(a, mid);
            helper(mid+1, b);
            
            for (int i=mid+1; i<=b; i++)
            {
                auto iter = std::lower_bound(sorted+a, sorted+mid+1, nums[i]);
                numSmaller[i] += iter-(sorted+a);
            }
            
            int i=a, j=mid+1, p = 0;        
            while (i<=mid && j<=b)
            {
                if (sorted[i]<=sorted[j])
                {
                    temp[p] = sorted[i];
                    i++;
                }                
                else
                {
                    temp[p] = sorted[j];
                    j++;
                } 
                p++;
            }
            while (i<=mid)
            {
                temp[p] = sorted[i];
                i++;
                p++;
            }
            while (j<=b)
            {
                temp[p] = sorted[j];
                j++;
                p++;
            }
            for (int i=0; i<b-a+1; i++)
                sorted[a+i] = temp[i];
        };                
                
        helper(0, n-1);

        int ret = 0;
        for (int i=0; i<n; i++)
        {
            // numSmaller[i], number of smaller than nums[i]
            // total is ith elements, and count[nums[i]] elements are equal to nums[i]
            ret += std::min(numSmaller[i], i-count[nums[i]]-numSmaller[i]);
            ret %= M;
            count[nums[i]]++;
        }            
        return ret;
    }

public:

    const int MAX_N = 100000;
    long long bitArr[MAX_N+1];
    long long nums[MAX_N+1];
    long long M = 1e9+7;

    // BIT
    void updateDelta(int i, long long delta) {
        int idx = i;
        while (idx <= MAX_N)
        {
            bitArr[idx]+=delta;
            bitArr[idx] %= M;
            idx+=idx&(-idx);
        }
    }

    long long queryPreSum(int idx){
        long long result = 0;
        while (idx){
            result += bitArr[idx];
            result %= M;
            idx-=idx&(-idx);
        }
        return result;
    }

    long long sumRange(int i, int j) {
        return queryPreSum(j)-queryPreSum(i-1);
    }
    
    int doit_BIT(vector<int>& instructions) 
    {        
        long long ret = 0;
        
        for (auto x:instructions)
        {
            updateDelta(x, 1);
            long long a = sumRange(1, x-1);
            long long b = sumRange(x+1, MAX_N);
            ret += std::min(a,b);
            ret %= M;
        }
        return ret;
        
    }

public:

    class SegTreeNode
    {
        public:
        SegTreeNode* left;
        SegTreeNode* right;
        int start, end;
        int info;        
        SegTreeNode(int a, int b):start(a),end(b),info(0),left(NULL),right(NULL){}
    };
    
    void init(SegTreeNode* node, int a, int b)  // init for range [a,b]
    {                        
        if (a==b)
        {
            node->info = 0;
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
                
        node->info = node->left->info + node->right->info;  // write your own logic
    }
    
    void updateSingleBy(SegTreeNode* node, int id, int val)
    {        
        if (id < node->start || id > node->end ) return;
        if (node->start == node->end)
        {
            node->info += val;
            return;
        }
        updateSingleBy(node->left, id, val);
        updateSingleBy(node->right, id, val);
        node->info = node->left->info + node->right->info;  // write your own logic
    }
    
    int queryRange(SegTreeNode* node, int a, int b)
    {
        if (b < node->start || a > node->end )
        {
            return 0;  // write your own logic
        }
        if (a <= node->start && b>=node->end)
        {
            return node->info;  // write your own logic
        }        
        return queryRange(node->left, a, b) + queryRange(node->right, a, b);  // write your own logic
    }        
    
    long M = 1e9+7;

    int createSortedArray(vector<int>& instructions) 
    {
        set<int>Set(instructions.begin(), instructions.end());
        unordered_map<int,int>num2idx;
        int i = 0;
        for (auto x:Set)
        {
            num2idx[x] = i;
            i++;
        }
        int n = num2idx.size();
                
        SegTreeNode* root = new SegTreeNode(0, n-1);
        init(root, 0, n-1);
        
        long ret = 0;        
        for (auto x: instructions)
        {
            long a = queryRange(root, 0, num2idx[x]-1);
            long b = queryRange(root, num2idx[x]+1, n-1);
            ret += std::min(a,b);
            ret %= M;
            updateSingleBy(root, num2idx[x], 1);
        }
        return ret;        
    }
};