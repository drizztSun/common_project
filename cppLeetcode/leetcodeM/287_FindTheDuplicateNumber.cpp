/*
287. Find the Duplicate Number


Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

 

Example 1:

Input: nums = [1,3,4,2,2]
Output: 2
Example 2:

Input: nums = [3,1,3,4,2]
Output: 3
Example 3:

Input: nums = [1,1]
Output: 1
Example 4:

Input: nums = [1,1,2]
Output: 1
 

Constraints:

2 <= n <= 3 * 104
nums.length == n + 1
1 <= nums[i] <= n
All the integers in nums appear only once except for precisely one integer which appears two or more times.
 

Follow up:

How can we prove that at least one duplicate number must exist in nums?
Can you solve the problem without modifying the array nums?
Can you solve the problem using only constant, O(1) extra space?
Can you solve the problem with runtime complexity less than O(n2)?


*/
#include <vector>
#include <unordered_set>
#include <algorithm>

using std::unordered_set;
using std::vector;


class FindDuplicate {

public:

    /*
        Indexing sort 
        O(n), O(1)
    */
    int doit_indexing_sort(vector<int>& nums) {

        for (int i = 0; i < nums.size(); i++) {

            while (nums[i] != i + 1 && nums[i] != nums[nums[i]-1]) {
                std::swap(nums[i], nums[nums[i] - 1]);
            }

            if (nums[i] != i+1) return nums[i];
        }
    }
    /*
        Approach 1: Sorting
        Intuition

        If the numbers are sorted, then any duplicate numbers will be adjacent in the sorted array.

        Algorithm

        Given the intuition, the algorithm follows fairly simply. First, we sort the array, and then we compare each element to the previous element. 
        Because there is exactly one duplicated element in the array, we know that the array is of at least length 2, and we can return the duplicate element as soon as we find it.

        Complexity Analysis

        Time complexity : O(nlgn)

        The sort invocation costs O(nlgn) time in Python and Java, so it dominates the subsequent linear scan.

        Space complexity : O(1) or O(n)

        Here, we sort nums in place, so the memory footprint is constant. If we cannot modify the input array, then we must allocate linear space for a copy of nums and sort that instead.
    */
    int doit_sort(vector<int>& nums) {
        
        std::sort(begin(nums), end(nums));

        for (int i = 0; i < nums.size()-1; i++) {
            if (nums[i] == nums[i+1])
                return nums[i];
        }
        return -1;
    }

    int doit_hashtable(vector<int>& nums) {
        unordered_set<int> buff;
        for (auto c: nums) {
            if (buff.find(c) != buff.end())
                return c;

            buff.insert(c);
        }

        return -1;
    }

    /*
        Approach 3: Floyd's Tortoise and Hare (Cycle Detection)
        Intuition

        The idea is to reduce the problem to Linked List Cycle II:

        Given a linked list, return the node where the cycle begins.

        First of all, where does the cycle come from? Let's use the function f(x) = nums[x] to construct the sequence: x, nums[x], nums[nums[x]], nums[nums[nums[x]]], ....

        Each new element in the sequence is an element in nums at the index of the previous element.

        If one starts from x = nums[0], such a sequence will produce a linked list with a cycle.

        The cycle appears because nums contains duplicates. The duplicate node is a cycle entrance.

        Now the problem is to find the entrance of the cycle.

        Algorithm

        Floyd's algorithm consists of two phases and uses two pointers, usually called tortoise and hare.

        In phase 1, hare = nums[nums[hare]] is twice as fast as tortoise = nums[tortoise]. Since the hare goes fast, it would be the first one who enters the cycle and starts to run around the cycle. 
        At some point, the tortoise enters the cycle as well, and since it's moving slower the hare catches the tortoise up at some intersection point. Now phase 1 is over, and the tortoise has lost.

        Note that the intersection point is not the cycle entrance in the general case.

        pic

        To compute the intersection point, let's note that the hare has traversed twice as many nodes as the tortoise, i.e. 2d(\text{tortoise}) = d(\text{hare})2d(tortoise)=d(hare), that means

        2(F + a) = F + nC + a2(F+a)=F+nC+a, where nn is some integer.

        Hence the coordinate of the intersection point is F + a = n CF+a=nC.

        In phase 2, we give the tortoise a second chance by slowing down the hare, so that it now moves with the speed of tortoise: tortoise = nums[tortoise], hare = nums[hare]. 
        The tortoise is back at the starting position, and the hare starts from the intersection point.

        pic

        Let's show that this time they meet at the cycle entrance after FF steps.

        The tortoise started from zero, so its position after FF steps is FF.

        The hare started at the intersection point F + a = nCF+a=nC, so its position after F steps is nC + FnC+F, that is the same point as FF.

        So the tortoise and the (slowed down) hare will meet at the entrance of the cycle.

        Implementation

        Complexity Analysis

        Time complexity : O(n)

        For detailed analysis, refer to Linked List Cycle II.

        Space complexity : O(1)

        For detailed analysis, refer to Linked List Cycle II.
    */
    int doit_floyd(vector<int>& nums) {

        int slow = nums[0], fast = nums[0];
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        int cur = nums[0];
        while (cur != slow) {
            cur = nums[cur];
            slow = nums[slow];
        }

        return cur;
    }

    /*
        287. Find the Duplicate Number
        解法1：二分法
        本题数的范围是1~n，但是数的个数有n+1个，说明duplicated number至少出现了两次。但是duplicated number也有可能出现的次数更多，它或许会替代了某些missing numbers.但不管怎样，duplicated number的出现次数一定比missing numbers更多。这样，如果k是那个duplicated number的话，我们遍历数组统计小于等于k出现的次数一定是大于k的。

        我们就可以用这个判据去二分搜值。我们猜测一个数k，如果小于等于k出现的次数大于k，那么k有可能是答案，但也有可能比它更小，故right=k. 反之，那么k一定不是答案，我们必须提升答案区间的下限，即left=k+1.

        解法2：indexing sort
        利用indexing sort的方法，我们尝试将n+1个数组元素尽可能地按照“index==value”的方法重新放置在1~n+1这些位置上。放置完之后，必然是有若干个位置的index==val，而有某些index对应的nums[index]!=index，并且这些位置上的数值都是duplicated number。

        解法3：快慢指针
        此题还有一个非常绝妙的算法。将1~N个数放在N+1个位置上，那么val->index将会出现一个一对多的映射，反之，index->val将会有一个多对一的映射。而其余的则是一一映射。于是这些index和val势必会有一部分构成一个环。

        举个例子：2,4,1,3,1 从index到val的映射关系是：1->2, 2->4, {3,5}->1, 4->3，其中1->2->4->3->1就构成了一个环。对于这个环，我们看到多出了一条5->1的切入口。可见，这个环的额外入口就是重复的数字。

        于是此题可以联想到 142. Linked List Cycle II，用快慢指针来确定一个linked list中环的入口。算法是，先用快慢指针做追及（快指针的速度比慢指针快一倍），直到他们相遇的位置；再用一个慢指针从起点开始，和在追及位置的慢指针共同前进。他们再次相遇的地方就是环的入口。
    
    */
    int doit_binary_search(vector<int>& nums) 
    {
        int n = nums.size(), left = 1, right = n-1;        
        
        while (left < right)
        {
            int k = left + (right-left)/2;
            int count=0;
            for (auto x: nums)
                if (x <= k) count++;
            
            if (count > k)
                right = k;
            else
                left = k + 1;
        }        
        return left;        
    }

    int doit_v2(vector<int>& nums) 
    {
        int n = nums.size()-1;
        nums.insert(nums.begin(), 0);
        for (int i=1; i<=n+1; i++)
        {
            while (nums[i]!=i && nums[i]<=n+1 && nums[i]!=nums[nums[i]])
                std::swap(nums[i], nums[nums[i]]);
        }
        for (int i=1; i<=n+1; i++)
        {
            if (nums[i]!=i)
                return nums[i];
        }
        return -1;
    }

    int doit_v3(vector<int>& nums) 
    {
        int slow = nums[0];
        int fast = nums[nums[0]];
        while (slow!=fast)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        fast = 0;
        while (slow!=fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }

};