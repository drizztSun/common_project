/*
1569. Number of Ways to Reorder Array to Get Same BST

Given an array nums that represents a permutation of integers from 1 to n. We are going to construct a binary search tree (BST) by inserting the elements of nums in order into an initially empty BST. 
Find the number of different ways to reorder nums so that the constructed BST is identical to that formed from the original array nums.

For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left child, and 3 as a right child. The array [2,3,1] also yields the same BST but [3,2,1] yields a different BST.

Return the number of ways to reorder nums such that the BST formed is identical to the original BST formed from nums.

Since the answer may be very large, return it modulo 10^9 + 7.

 

Example 1:



Input: nums = [2,1,3]
Output: 1
Explanation: We can reorder nums to be [2,3,1] which will yield the same BST. There are no other ways to reorder nums which will yield the same BST.
Example 2:



Input: nums = [3,4,5,1,2]
Output: 5
Explanation: The following 5 arrays will yield the same BST: 
[3,1,2,4,5]
[3,1,4,2,5]
[3,1,4,5,2]
[3,4,1,2,5]
[3,4,1,5,2]
Example 3:



Input: nums = [1,2,3]
Output: 0
Explanation: There are no other orderings of nums that will yield the same BST.
Example 4:



Input: nums = [3,1,2,5,4,6]
Output: 19
Example 5:

Input: nums = [9,4,2,1,3,6,5,7,8,14,11,10,12,13,16,15,17,18]
Output: 216212978
Explanation: The number of ways to reorder nums to get the same BST is 3216212999. Taking this number modulo 10^9 + 7 gives 216212978.
 

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= nums.length
All integers in nums are distinct.

*/
#include <vector>
#include <functional>

using std::vector;

class ReorderBSTWays {

    /*
        1569.Number-of-Ways-to-Reorder-Array-to-Get-Same-BST
        首先我们要搞清楚一件事情，为什么原题条件所给的一个序列能对应一棵BST？而为什么那棵BST又可以对应其他很多的序列？

        第一步要知道，条件所给的一个序列，能构造出唯一的一棵BST。怎么做？比较基础的办法就是逐个点地加上去。第一个点是根节点。第二点放在根节点左边还是右边，取决于它与根节点的相对大小。
        
        第三个节点放在哪里？其实只要从根节点出发，每一步做比较，比根大就往右边走，比根小就往左边走，直到遇到一个空节点的位置就放置在哪里。从这个过程可以知道，这个序列对应了一棵确定的BST。

        第二步要知道，给定了一棵BST，为什么可以有多种序列？我们仔细研究这个序列生成的本质，其实是因为“左右子树节点的向下生成允许交错并行”。

        举个第二个样例：

            3
            1   4
            2   5
        对于根节点而言，它的左子树只能有一种序列[1,2]，它的右子树只能有一种序列[4,5]。但是对于整棵树而言的序列，除了根节点3必须放在第一个，序列的剩下部分只需要满足[1,2]与[4,5]的相对顺序不变即可。也就是

        [3,1,2,4,5]
        [3,1,4,2,5]
        [3,1,4,5,2]
        [3,4,1,2,5]
        [3,4,1,5,2]
        [3,4,5,1,2]
        我们看出，[1,2]和[4,5]的任意次序的交叠(interleave)都是可以的。这样总共产生了6种。

        这6种如何计算出来？我们可以更一般地设计两个序列，第一个长度是m，第二个长度是n，求“保持各自相对顺序的任意交叠”序列有多少个？这其实是一个高中组合数学的中等题。我们在总共m+n个位置中，只要选择出其中m个位置填上第一个序列，那么其他一切都能确定下来：这m个位置如何填充必须依照序列一的顺序；剩下的n个位置自然就是给第二个序列，并且他们如何填充必须依照序列二的顺序。所以我们只需要做的就是从m+n个位置中挑选m个，也就是C(m+n,n)。

        解决了这个问题，我们就可以知道对任意一棵树，如何计算它的序列的个数。我们可以先递归处理它的子树，计算它的左子树有L种序列，它的右子树有R种序列，那么每一对左右序列，我们又可以产生C(m+n,n)种交叠序列（也就是这棵树本身的序列）。所以答案就是LRC(m+n,n)，其中m是左子树序列的长度（也就是左子树的节点总数），n是右子树序列的长度（也就是右子树的节点总数）。

        可见，本题的大框架就是一个递归。从底层节点算起，不断给上层节点提供数据。

        边界条件是叶子节点，序列数必然是1.

        另外，本题需要计算大组合数以及算它对大质数的模。我们这里抛开逆元的用法，采用一个更容易理解的算法。利用组合数的递推公式:C(m+n,n) = C(m+n-1,n) + C(m+n-1,n-1)。这样可以将大组合数分解为小组合数，直至边界条件是C(x,1) = x, C(x,0) = 1。对于加法的分拆，(a+b)%M = a% + b%M是可以放心使用的。
            
    */
    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    
    long M = 1e9+7;
    long comb[1001][1001];

    long getComb(long m, long n)
    {
        if (comb[m][n]!=-1)
            return comb[m][n];
        if (n==0) return 1;
        if (n==1) return m;        
        if (n>m-n) return getComb(m, m-n);
        long a = getComb(m-1, n-1);        
        long b = getComb(m-1, n);
        comb[m][n] = (a+b)%M;
        return comb[m][n];
    }
    
public:
    int numOfWays(vector<int>& nums) 
    {
        for (int i=0; i<=1000; i++)
            for (int j=0; j<=1000; j++)
                comb[i][j] = -1;
        
        TreeNode* root = new TreeNode(nums[0]);
        for (int i=1; i<nums.size(); i++)        
            insertNode(root, nums[i]);
                    
        long num, val;
        dfs(root, num, val);
        return val-1;
    }

    void insertNode(TreeNode* root, int val)
    {
        if (val < root->val)
        {
            if (root->left==NULL)
                root->left = new TreeNode(val);
            else
                insertNode(root->left, val);
        }
        else
        {
            if (root->right==NULL)
                root->right = new TreeNode(val);
            else
                insertNode(root->right, val);
        }
    }
    
    void dfs(TreeNode* node, long& num, long& val)
    {
        if (node->left==NULL && node->right==NULL)
        {
            num = 1;
            val = 1;
            return;
        }
        
        long leftNum = 0, leftVal = 1;
        long rightNum = 0, rightVal = 1;
        if (node->left)
            dfs(node->left, leftNum, leftVal);
        if (node->right)
            dfs(node->right, rightNum, rightVal);
        
        num = leftNum+rightNum+1;
        val = ((getComb(leftNum+rightNum, leftNum) * leftVal) % M * rightVal) % M;
        return;        
    }


public:

    /*
    First, we can bot change the root, otherwise we will get different trees.

    Second, nodes in the left < root, nodes in the rigth subtree > root. 

    l = [x in nums if x < nums[0]]
    r = [x in nums if x > nums[0]]

    Interleaving l and r will get the same tree.
    And there are C(|l| + |r|m |l|) ways.

    Do it recursively for l and r

    Total ways = C(|l| + |r|, |l|) * ways(l) * ways(r)
    ans = total_watys(nums) - 1

    for [4, 2, 1, 3, 6, 5]

    coulod be :
    [4, 2, 3, 1, 6, 5]
    [4, 2, 3, 6, 5, 1]...

    Sequence for 2, 1, and 3, 6, 5, would be changed.

    For a given root (first element of the array), we can split the array into left children (nums[i] < nums[0]) and 
    right children (nums[i] > nums[0]). Assuming there are l nodes for the left and r nodes for the right. 

    We have C(l + r, l) different ways to insert l elements into a (l + r) sized array. 
    Within node l / r nodes, we have ways(left) / ways(right) different ways to re-arrange those nodes. So the total # of ways is:

    C(l + r, l) * ways(l) * ways(r)
    Don’t forget to minus one for the final answer.

    Time complexity: O(n^2)
    Space complexity: O(n^2)


    Time complexity: (0(nlogn)) -> O(n^2)
    Space complexity: O(nlog(n)) -> O(n^2)
    */
    int doit(vector<int>& nums) {

        const int n = nums.size();
        const int hMod = 1e9 + 7;

        vector<vector<int>> cnk(n+1, vector<int>(n+1, 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++)
                cnk[i][j] = (cnk[i-1][j] + cnk[i-1][i-1]) % hMod;
        }

        std::function<int(vector<int>&)> search = [&](vector<int>& nums) {
            const int m = nums.size();
            if (m <= 2) return 1;

            vector<int> left, right;
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] < nums[0])
                    left.push_back(nums[i]);
                else
                    right.push_back(nums[i]);
            }

            long ans = cnk[m-1][left.size()];
            ans = (ans * search(left)) % hMod;
            ans = (ans * search(right)) % hMod;
            return static_cast<int>(ans);
        };

        return search(nums) - 1;
    }
};