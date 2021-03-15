/*
457. Circular Array Loop

You are playing a game involving a circular array of non-zero integers nums. Each nums[i] denotes the number of indices forward/backward you must move if you are located at index i:

    .   If nums[i] is positive, move nums[i] steps forward, and
    .   If nums[i] is negative, move nums[i] steps backward.
Since the array is circular, you may assume that moving forward from the last element puts you on the first element, and moving backwards from the first element puts you on the last element.

A cycle in the array consists of a sequence of indices seq of length k where:

    .   Following the movement rules above results in the repeating index sequence seq[0] -> seq[1] -> ... -> seq[k - 1] -> seq[0] -> ...
    .   Every nums[seq[j]] is either all positive or all negative.
    .   k > 1
Return true if there is a cycle in nums, or false otherwise.

 

Example 1:

Input: nums = [2,-1,1,2,2]
Output: true
Explanation:
There is a cycle from index 0 -> 2 -> 3 -> 0 -> ...
The cycle's length is 3.
Example 2:

Input: nums = [-1,2]
Output: false
Explanation:
The sequence from index 1 -> 1 -> 1 -> ... is not a cycle because the sequence's length is 1.
By definition the sequence's length must be strictly greater than 1 to be a cycle.
Example 3:

Input: nums = [-2,1,-1,-2,-2]
Output: false
Explanation:
The sequence from index 1 -> 2 -> 1 -> ... is not a cycle because nums[1] is positive, but nums[2] is negative.
Every nums[seq[j]] must be either all positive or all negative.
 

Constraints:

1 <= nums.length <= 5000
-1000 <= nums[i] <= 1000
nums[i] != 0
 

Follow up: Could you solve it in O(n) time complexity and O(1) extra space complexity?

*/


#include <vector>

using std::vector;


class CircularArrayLoop {

    /*
        457.Circular-Array-Loop
        看到题目要求用o(1)的空间判断一个array里是否存在loop，就应该条件反射地想到用快慢指针的方法。这个方法在linked list的数据结构里经常用到，因为链表无法反向遍历或这按index遍历。此题虽然是数组，但由于空间要求的限制，不得不利用链表里的这个技巧。

        此题要注意的细节是，getNext(pos,nums,dir)函数应该在两种情况下返回”错误“的提示。一种情况是该点nums[pos]和设定的遍历方向dir不同，违反题意，那么就直接返回”错误“。另一种情况是，getNext得到的是本身节点（仅对于慢指针）的话，说明这个方向的搜寻陷入了dead end，不能构成一个环。

        有了以上两个报错预判作为while循环的条件，就可以放心地让快慢指针各自前进，直至两者相遇。

                while (getNextTwo(fast,nums,dir)!=-1 and getNext(slow,nums,dir)!=-1):
                        fast,slow = getNextTwo(fast,nums,dir),getNext(slow,nums,dir)
                        if (fast==slow): break
        跳出之后根据(getNextTwo(fast,nums,dir)!=-1 and getNext(slow,nums,dir)!=-1)判断是否真的loop达成。

        如果loop没达成，则让慢指针再跑一遍，从起点到它的dead end一路都标记为0，以后这些元素就不用访问。这额外的一遍访问会增加一倍o(n)的时间，不会改变整体时间的数量级。
    */
    bool circularArrayLoop(vector<int>& nums) 
    {

        auto advanceBy = [&](int step, int j, int dir) 
        {
            int n = nums.size();
            for (int k=0; k<step; k++) 
            {
                j = (j + nums[j] + n) % n;
                j = (j + n) % n;
                if (nums[j] * dir <= 0)
                    return -1;
            }
            return j;
        };

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0) continue; 
            
            int slow = i, fast = i, dir = nums[i];
            do {
                slow = advanceBy(1, slow, dir);
                fast = advanceBy(2, fast, dir);
            } while (slow >= 0 && fast >= 0 && slow != fast);
                
            if (slow >= 0 && fast >= 0 && slow != advanceBy(1, slow, dir)) 
                return true;
            
            slow = i;
            while (advanceBy(1, slow, dir)>=0)
            {
                int tmp = advanceBy(1, slow, dir);
                nums[slow] = 0;
                slow = tmp;
            }
        }
        return false;
    }

public:
    
    bool doit_link(vector<int>& nums) {
        
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            
            if (nums[i] == 0) continue;

            bool positive = nums[i] > 0;
            int step = 0;
            int j = i;

            while (step < n && nums[j] % n != 0 && (nums[j] > 0) == positive) {
                j = (n + (j + nums[j]) % n) % n;
                step++;
            }

            if (step == n) return true;

            j = i;
            while (nums[j] % n != 0 && (nums[j] > 0) == positive) {
                nums[j] = 0;
                j = (n + (j + nums[j]) % n) % n;
            }
        }

        return false;
    }
};