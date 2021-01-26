/*
448. Find All Numbers Disappeared in an Array


Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]

*/

/*
448.Find-All-Numbers-Disappeared-in-an-Array
对于这种数列[1,..,N]摆放在index为[1,..,N]的数组，有一种比较常见的巧妙解法，就是index sorting.

我们观察一个i位置上的数，如果nums[i]!=i的话，那么说明这个nums[i]本不应该在这个位置上，于是我们就把它送到它应该待的地方，也就是index为nums[i]的地方，直至这种交换无法继续为止。什么情况下无法继续呢？一种就是nums[i]==i，说明位置i已经放置了应该出现的数；另一种就是nums[nums[i]]==nums[i]，也就是打算安排nums[i]的位置已经有一个合适的数在那里了，我们也无法继续了，说明位置i上注定无法放置期望出现的数。

核心代码如下：

        while (i<nums.size())
        {
            if (nums[i]==i || nums[nums[i]]==nums[i])             
                i++;            
            else            
                swap(nums[i],nums[nums[i]]);            
        }
此题本质上和 442. Find All Duplicates in an Array 一模一样，只不过最终输出的内容是index而不是元素的值。

*/
#include <vector>
#include <algorithm>

using std::vector;

class FindDisappearedNumbers {

public:

    vector<int> doit_(vector<int>& nums) {

        int i = 0;
        while (i < nums.size()) {

            while (nums[i] != i+1 && nums[i] != nums[nums[i]-1]) {
                std::swap(nums[i], nums[nums[i]-1]);
            }
            i++;
        }

        vector<int> ans;
        //std::remove_copy(begin(nums), end(nums), begin(ans), [&](int i) { return nums[i] != i+1;});
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] != i+1) ans.push_back(i+1);
        
        return ans;
    }
    
    vector<int> doit_(vector<int>& nums) {

        int n = nums.size();
        nums.insert(nums.begin(),0);
        for (int i=1; i<=n; i++)
        {
            while (nums[i]!=i && nums[i]<=n && nums[i]!=nums[nums[i]])
                std::swap(nums[i], nums[nums[i]]);
        }

        vector<int>rets;
        for (int i=1; i<=n; i++)
        {
            if (nums[i]!=i)
                rets.push_back(i);
        }
        return rets;
    }
};