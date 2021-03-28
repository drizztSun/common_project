/*
1803. Count Pairs With XOR in a Range

Given a (0-indexed) integer array nums and two integers low and high, return the number of nice pairs.

A nice pair is a pair (i, j) where 0 <= i < j < nums.length and low <= (nums[i] XOR nums[j]) <= high.

 

Example 1:

Input: nums = [1,4,2,7], low = 2, high = 6
Output: 6
Explanation: All nice pairs (i, j) are as follows:
    - (0, 1): nums[0] XOR nums[1] = 5 
    - (0, 2): nums[0] XOR nums[2] = 3
    - (0, 3): nums[0] XOR nums[3] = 6
    - (1, 2): nums[1] XOR nums[2] = 6
    - (1, 3): nums[1] XOR nums[3] = 3
    - (2, 3): nums[2] XOR nums[3] = 5
Example 2:

Input: nums = [9,8,4,2,1], low = 5, high = 14
Output: 8
Explanation: All nice pairs (i, j) are as follows:
​​​​​    - (0, 2): nums[0] XOR nums[2] = 13
    - (0, 3): nums[0] XOR nums[3] = 11
    - (0, 4): nums[0] XOR nums[4] = 8
    - (1, 2): nums[1] XOR nums[2] = 12
    - (1, 3): nums[1] XOR nums[3] = 10
    - (1, 4): nums[1] XOR nums[4] = 9
    - (2, 3): nums[2] XOR nums[3] = 6
    - (2, 4): nums[2] XOR nums[4] = 5
 

Constraints:

1 <= nums.length <= 2 * 104
1 <= nums[i] <= 2 * 104
1 <= low <= high <= 2 * 104

*/


#include <vector>

using std::vector;


class CountPairsWithXORInRange {

    /*
        1803.Count-Pairs-With-XOR-in-a-Range
        针对一个数组的元素进行XOR操作，一个比较常见的套路就是使用字典树。相似的题目有421.Maximum-XOR-of-Two-Numbers-in-an-Array。如果我们在数组中枚举所有的配对nums[i]和nums[j]，需要o(N^2)的复杂度。
        但是如果我们能根据nums[j]直接找到符合要求的nums[i]，那么会高效很多。关键的操作是利用Trie把所有的元素都集中在了一起。根据nums[j]的特点，我们只需要在字典树里面最多深度搜索32层，即可定位我们期待的nums[i]（如果存在的话）。

        此题的第二个技巧是，我们不同时寻找符合区间[low,high]要求的配对数目。而是先计算XOR小于high+1的配对数目，再减去XOR小于low的配对数目。两者之差就是答案。这样的好处是，我们本质上只需要求解一个问题即可：
        统计XOR小于某个阈值的配对数目；而不用考虑另一个大于等于low的问题。类似思想的题目有992.Subarrays-with-K-Different-Integers.

        为了在统计pairs时不重复计数，我们选定nums[j]时，只在前j-1个元素组成的字典树里寻找与之合适的配对。寻找完之后再将nums[j]添加进字典树中。

        有了以上的基础，我们现在来实现countPairsSmallerThan(int num, int th)，即字典树里有多少元素与num异或之后小于th。

        搜索的关键是在字典树里试图找到一个数（也就是一条根到叶子的路径），其与num异或之后能等于th。这条路径可以帮助我们将字典树分割、并统计能够符合条件的配对元素。

        假设我们从最高位开始，向下走到了第i层，总共考察了i个bit位。并假设这一路走来，在字典树中存在若干个元素的前i-1位，与num的前i-1位异或的结果，等于th的前i-1位。现在令num的第i为是b，th的第i为是c。
        那么我们期望当前所在的字典树的位置（第i层的某个节点），存在一个分支a（即0或者1），满足a^b=c，也就是a=b^c。我们分情况讨论。

        1. 如果a==1, c==1.
        假设从当前节点往下走0分支的话，那么a^b的结果就是与c相反的0。而这个0是比c小的。这就说明如果走0分支下去所有的元素，他们与num的异或的结果：前i-1位与th都相同，但在第i位小于了th的第i位（也就是c）。
        那么必然整个异或的结果就会小于th。所以我们可以直接将0分支下面的元素总数统计进来即可，不必一一遍历到底。
        假设从当前节点往下走1分支的话，那么a^b的结果就是与c相同的1。说明截止到第i位为止，这些字典树的元素与num的异或结果仍然等于th。所以我们就下沉到到i+1层，递归处理。
        
        2. 如果a==1, c==0.
        假设从当前节点往下走0分支的话，那么a^b的结果就是与c相反的1。而这个1是比c大的。这就说明如果走0分支下去所有的元素，他们与num的异或的结果：前i-1位与th都相同，但在第i位大于了th的第i位（也就是c）。
        那么必然整个异或的结果就会大于th。所以我们就果断舍弃该分支的探索。 假设从当前节点往下走1分支的话，那么a^b的结果就是与c相同的1。说明截止到第i位为止，这些字典树的元素与num的异或结果仍然等于th。所以我们就下沉到到i+1层，递归处理。
        类似地：

        3. 如果a==0, c==1.
        假设从当前节点往下走1分支的话，那么a^b的结果就是与c相反的0。而这个0是比c小的。这就说明如果走1分支下去所有的元素，他们与num的异或的结果：前i-1位与th都相同，但在第i位小于了th的第i位（也就是c）。
        那么必然整个异或的结果就会小于th。所以我们可以直接将1分支下面的元素总数统计进来即可，不必一一遍历到底。
        假设从当前节点往下走0分支的话，那么a^b的结果就是与c相同的1。说明截止到第i位为止，这些字典树的元素与num的异或结果仍然等于th。所以我们就下沉到到i+1层，递归处理。
        
        4. 如果a==0, c==0.
        假设从当前节点往下走1分支的话，那么a^b的结果就是与c相反的1。而这个1是比c大的。这就说明如果走1分支下去所有的元素，他们与num的异或的结果：前i-1位与th都相同，但在第i位大于了th的第i位（也就是c）。
        那么必然整个异或的结果就会大于th。所以我们就果断舍弃该分支的探索。 假设从当前节点往下走0分支的话，那么a^b的结果就是与c相同的0。说明截止到第i位为止，这些字典树的元素与num的异或结果仍然等于th。所以我们就下沉到到i+1层，递归处理。
        按照这样的方法，深入32层之后，我们就可以把字典树里所有与num异或小于th的元素数目统计出来了。注意，我们的字典树节点除了常规的next[0]、next[1]之外，还需要一个cnt，来统计该节点下面有多少个数组元素。这个cnt是在往字典树里插入元素时就可以统计得到的。
    */
    struct TrieNode
    {
        TrieNode* next[2];
        int cnt;
        
        TrieNode() { 
            next[0] = next[1] = nullptr;
            cnt=0; 
        }
    };

    

    int countSmallerPairs(vector<int>&nums, int th)
    {
        TrieNode* root = new TrieNode();
        int count = 0;
        for (int num: nums)
        {
            count += countSmallerThan(root, num, th);
            insert(root, num);
        }
        return count;
    }

    int countSmallerThan(TrieNode* root, int num, int th)
    {
        auto node = root;
        int count = 0;
        for (int i=31; i>=0; i--)
        {
            int c = (th>>i)&1;
            int b = (num>>i)&1;
            int a = c ^ b;
            if (a == 1 && c == 1)
            {
                if (node->next[0]) count += node->next[0]->cnt;
                if (node->next[1]) node = node->next[1];
                else break;
            }
            else if (a==1 && c==0)
            {
                if (node->next[1]) node = node->next[1];
                else break;
            }
            else if (a==0 && c==1)
            {
                if (node->next[1]) count += node->next[1]->cnt;
                if (node->next[0]) node = node->next[0];
                else break;
            }
            else if (a==0 && c==0)
            {
                if (node->next[0]) node = node->next[0];
                else break;
            }
        }
        return count;
    }

    void insert(TrieNode* root, int num)
    {
        auto node = root;
        for (int i=31; i>=0; i--)
        {
            if ((num>>i)&1)
            {
                if (node->next[1]==NULL)
                    node->next[1] = new TrieNode();
                node->next[1]->cnt++;
                node = node->next[1];
            }
            else
            {
                if (node->next[0]==NULL)
                    node->next[0] = new TrieNode();
                node->next[0]->cnt++;
                node = node->next[0];
            }
        }
    }

public:
    
    int countPairs(vector<int>& nums, int low, int high) 
    {
        return countSmallerPairs(nums, high+1) - countSmallerPairs(nums, low);
    }
};