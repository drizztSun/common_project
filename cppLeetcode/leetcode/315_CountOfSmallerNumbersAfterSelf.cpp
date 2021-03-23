/*
315. Count of Smaller Numbers After Self

You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Example 2:

Input: nums = [-1]
Output: [0]
Example 3:

Input: nums = [-1,-1]
Output: [0,0]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104

*/
#include <algorithm>
#include <vector>
#include <functional>


using std::vector;


class CountSmallerNumber {

    /*
        315.Count-of-Smaller-Numbers-After-Self
        分治法的最常见的应用就是与归并排序相结合。将数组对半划分为左右两部分，两部分各自排序，然后将两部分整体归并，在归并的过程中就可以解决一些问题。比如LeetCode的 493,315,327

        本题中带有鲜明的特征，即求nums[i]右边的所有小于它的数，这暗示了用分治和归并排序的算法。

        在每一轮，序列start~end对半分为两部分，左序列区间从start到mid，右序列区间从mid+1到end。两个部分各自递归调用分治排序的函数后，都变得有序（存放在sortedNums里）。
        此时，对于左序列的任意nums[i]，都可以轻易在有序的右序列中用lower_bound找到可以插入的位置，也就知道了右序列中有多少小于它的数。据此可以更新count[i].

        有人会问，那么在左序列中（从nums[start]到nums[mid]），肯定也有一些数小于nums[i]并且位于它右边呀。为什么不考虑呢？其实这部分在之前对于start~mid区间调用分治排序的函数处理过了。请仔细体会。

        最后注意，本题需要三个数组，nums, sortedNums, count。原来的数据存在nums, 归并排序后的数组存在sortedNums, count[i]对应的是nums[i]的 number of smaller elements to the right.
    */
    vector<int> doit_divide_and_conquer(vector<int>& nums) 
    {        
        int N = nums.size();
        if (N==0) return {};
        
        vector<int>sortedNums = nums;        
        vector<int>counts(N,0);

        std::function<void(int, int)> DivideConque = [&](int start, int end)
        {
            if (start==end) return;
            
            // 如果需要处理的元素有多个，则折半分治处理。注意：分治处理后的sortedNums前后两部分元素都是有序的。
            int mid = start+(end-start)/2;
            DivideConque(start,mid);
            DivideConque(mid+1, end);
            
            // OK，既然现在start~mid和mid+1~end这两段都分别有序，
            // 那么对于start~mid中的任何一个元素，我们都可以轻易地知道在mid+1~end中有多少小于它的数
            for (int i=start; i<=mid; i++)
            {
                int val = nums[i];
                auto pos = lower_bound(sortedNums.begin()+mid+1, sortedNums.begin()+end+1,val);            
                counts[i] += pos-(sortedNums.begin()+mid+1);
            }
            
            // 将两段已经有序的数组段start~mid,mid+1~end合起来排序。
            // 如果写归并排序的code会更快一些。这里就偷懒了，直接用sort函数。        
            std::sort(sortedNums.begin()+start,sortedNums.begin()+end+1);        
        };

        DivideConque(0, nums.size()-1);  // 0表示起点，N-1表示终点
        
        return counts;
    }
    
    vector<int> doit_BIT_best(vector<int>& nums) {
        
        int maxv = *max_element(begin(nums), end(nums));
        int min_val = *min_element(begin(nums), end(nums));
        vector<int> bit(maxv - min_val + 10, 0);
        vector<int> output(nums.size());

        auto get = [&](int index) -> int {
            index++;
            int val=0;
            while(index>=1)
            {
                val+=bit[index];
                index-=index&-index;
            }
            return val;
        };
        
        auto update = [&](int index,int val) {
            index++;
            while(index<bit.size())
            {
                bit[index]+=val;
                index+=index&-index;
            }
        };

        for(int i = nums.size()-1; i >=0; i--)
        {
            // if(min_val<0) nums[i] += (-min_val+1);

            nums[i] += (-min_val+1);

            int count = get(nums[i]-1);
        
            output[i] = count;
            
            update(nums[i],1);
        }

        return output;
    }


public:
    
    // O(n*log^2(n)) => O(n^2) not good
    vector<int> doit_binary_search(vector<int>& nums) {
        
        int n = nums.size();
        vector<int> res(n);
        vector<int> sortedright;

        auto search = [&](int num) {

            int l = 0, r = sortedright.size()-1;

            while (l <= r) {
                int mid = (l + r) / 2;

                if (sortedright[mid] >= num)
                    r = mid - 1;
                else
                    l = mid + 1;
            }

            return l;
        };

        for (int i = nums.size() - 1; i >= 0; i--) {

            int pos = search(nums[i]);

            res[i] = pos;

            sortedright.insert(sortedright.begin() + pos, nums[i]);
        }

        return res;
    }
};