/*
34. Find First and Last Position of Element in Sorted Array

Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

Follow up: Could you write an algorithm with O(log n) runtime complexity?

 

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
Example 3:

Input: nums = [], target = 0
Output: [-1,-1]
 

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums is a non-decreasing array.
-109 <= target <= 109

*/
#include <vector>
#include <algorithm>

using std::vector;

class RangeInSortedArray {

    /*
            034.Search-for-a-Range
        寻找下界函数lower_bound()
        auto pos=lower_bound(MyVector.begin(), MyVector.end(), val) ;	
        函数lower_bound()在first和last中的前闭后开区间进行二分查找，返回大于或等于val的第一个元素位置。如果所有元素都小于val，则返回last的位置. 自定义比较函数：

        static bool cmp(long long a, long long b)  
        {         
        return (a<=b);         
        }    
        pos=lower_bound(q.begin(),q.end(),val,cmp);
        分析：将val看做自定义比较函数中的b，满足条件的a都会摆在b的前面，然后返回值就是b的位置。
        例如：如果a<=b，则所有小于等于val的数都会放在插入位置之前，即插入的位置是第一个大于val的地方；
        同理，如果a<b，则所有小于val的数都会放在插入位置之前，即插入的位置是第一个大于等于val的地方。

        寻找上界函数upper_bound()
        auto pos=upper_bound(MyVector.begin(), MyVector.end(), val) ;	
        函数upper_bound()在first和last中的前闭后开区间进行二分查找，返回指向第一个比参数大的元素，故有可能是MyVector.end()。 自定义比较函数：

        static bool cmp(long long a, long long b)  
        {         
        return (a<=b);
        }    
        pos=lower_bound(q.begin(),q.end(),val,cmp);
        分析：将val看做自定义比较函数中的a，满足条件的b都会摆在a的前面，然后返回值依然是b的位置。
        例如：如果a<b，则插入的位置必定大于val（即第一个大于val的元素地址）；
        同理，如果a<=b，则插入的位置必定大于等于val（即第一个大于等于val的元素地址）

        二分搜索法    
        常规的二分搜索，但是要注意选择好合适的框架。如果等号的情况不容易判断，那就从大于或小于的情况下手。

        对于下确界，可以分析出应该这么判断：

        if (nums[mid]<target)
        left = mid+1; // 不等于target的mid元素都可以排除
        else
        right = mid;
        于是，对于这种框架，显然二分方法用 mid = left+(right-left)/2;

        同理：对于上确界

        mid = left + (right-left)/2 +1;
        if (nums[mid]>target)
        right = mid-1; // 不等于target的mid元素都可以排除
        else
        left = mid;
    */


   static bool cmp1(int a, int b)
    {
        return a<b;
    }
    static bool cmp2(int a, int b)
    {
        return a<b;
    }    
public:
    vector<int> searchRange(vector<int>& nums, int target) 
    {
        vector<int>results;
        
        auto pos1 = lower_bound(nums.begin(),nums.end(),target,cmp1);
        if (pos1!=nums.end() && *pos1==target) 
            results.push_back(pos1-nums.begin());
        else
            results.push_back(-1);
            
        auto pos2 = upper_bound(nums.begin(),nums.end(),target,cmp2);
        
        if (pos2-nums.begin()-1>=0 && *(pos2-1)==target) 
            results.push_back(pos2-nums.begin()-1);
        else
            results.push_back(-1);            
        
        return results;
    }


    vector<int> searchRange(vector<int>& nums, int target) 
    {
        vector<int>results;
        
        if (nums.size()==0)
        {
            results.push_back(-1);
            results.push_back(-1);
            return results;
        }
        
        int left=0;
        int right=nums.size()-1;
        int mid;
        while (left<right)
        {
            mid = left+(right-left)/2;
            if (nums[mid]<target)
                left = mid+1;
            else
                right = mid;
        }
        if (nums[left]==target)
            results.push_back(left);
        else
            results.push_back(-1);
            
        left=0;
        right=nums.size()-1;
        mid;
        while (left<right)
        {
            mid = left+(right-left)/2+1;
            if (nums[mid]>target)
                right = mid-1;
            else
                left = mid;
        }
        if (nums[left]==target)
            results.push_back(left);
        else
            results.push_back(-1);      
            
        return results;   
    }

public:
    
    vector<int> doit_binary_search(vector<int>& nums, int target) {
        
        // returns leftmost (or rightmost) index at which `target` should be
        // inserted in sorted array `nums` via binary search.
        auto search = [&](bool left ) {
            
            int l = 0, r = nums.size();
            
            while (l < r) {
                
                int mid = (l + r) / 2;
                
                if (nums[mid] > target || left  && nums[mid] == target) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
                
            }
            
            return l;
        };

        int left = search(true), right = search(false);

        // assert that `leftIdx` is within the array bounds and that `target`
        // is actually in `nums`.        
        if (left == nums.size() || nums[left] != target || right == 0 || nums[right - 1] != target) return {-1, -1};
        
        return {left, right-1};
    }
};