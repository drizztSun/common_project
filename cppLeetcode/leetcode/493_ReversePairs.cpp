/*
493. Reverse Pairs

Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].

You need to return the number of important reverse pairs in the given array.

Example1:

Input: [1,3,2,3,1]
Output: 2
Example2:

Input: [2,4,3,5,1]
Output: 3
Note:
1. The length of the given array will not exceed 50,000.
2. All the numbers in the input array are in the range of 32-bit integer.

*/


#include <vector>
#include <algorithm>
#include <functional>

using std::vector;


class ReversePairs {

    /*
        493.Reverse-Pairs
        遇到这种题目，会发现如果这个数组是有序排列的，那么寻找pairs的过程就会方便很多。也就是说确定了i，很容易就能找到满足条件的j；反过来也是。这就强烈提示了需要用分治法（divide and conquer）来做，这是解决这类题型的套路。

        分治法的最常见的应用就是与归并排序相结合。将数组对半划分为左右两部分，两部分各自是有序的；然后将两部分整体归并，在归并的过程中可以利用有序的性质解决一些问题。比如LeetCode的 493,315,327

        另外，两个有序数组的归并排序操作，代码要熟练掌握。
    */
    int ret = 0;
    int temp[50001];
public:
    // divide_conquer
    int reversePairs(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int>sorted = nums;

        std::function<void()> helper = [&](vector<int>& nums, vector<int>& sorted, int a, int b)
        {
            if (a>=b) return;
            int mid = a+(b-a)/2;
            helper(nums, sorted, a, mid);
            helper(nums, sorted, mid+1, b);

            for (int j=mid+1; j<=b; j++)
            {
                auto iter = upper_bound(sorted.begin()+a, sorted.begin()+mid+1, 2*(long)nums[j]);
                ret += sorted.begin()+mid+1 - iter;
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

        helper(nums, sorted, 0, n-1);
        return ret;
    }

public:


    /*
        Approach 4: Modified Merge Sort
        Intuition

        In BIT and BST, we iterate over the array, dividing the array into 3 sections: already visited and hence added to the tree, current node and section to be visited. Another approach could be divide the problem into smaller subproblems, solving them and combining these problems to get the final result - Divide and conquer. We see that the problem has a great resemblance to the merge sort routine. The question is to find the inversions such that \text{nums[i]}>2 * \text{nums[j]}nums[i]>2∗nums[j] and i<ji<j. So, we can easily modify the merge sort to count the inversions as required.

        Mergesort

        Mergesort is a divide-and-conquer based sorting technique that operates in O(n\log n)O(nlogn) time. The basic idea to divide the array into several sub-arrays until each sub-array is single element long and merging these sublists recursively that results in the final sorted array.

        Algorithm

        We define \text{mergesort\_and\_count}mergesort_and_count routine that takes parameters an array say AA and \text{start}start and \text{end}end indices:

        If \text{start}start>=\text{end}end this implies that elements can no longer be broken further and hence we return 0
        Otherwise, set \text{mid}=(\text{start} + \text{end})/2mid=(start+end)/2
        Store countcount by recursively calling \text{mergesort\_and\_count}mergesort_and_count on range \text{[start,mid]}[start,mid] and \text{[mid+1,end]}[mid+1,end] and adding the results. This is the divide step on our routine, breaking it into the 2 ranges, and finding the results for each range separately
        Now, we that we have separately calculated the results for ranges \text{[start,mid]}[start,mid] and \text{[mid+1,end]}[mid+1,end], but we still have to count the elements in \text{[start,mid]}[start,mid] that are greater than 2 * elements in \text{[mid+1,end]}[mid+1,end]. Count all such elements and add the result to \text{count}count
        Finally, \text{merge}merge the array from \text{start}start to \text{end}end
        Make 2 array : LL from elements in range \text{[start,mid]}[start,mid] and RR from elements in range \text{R[mid+1,end]}R[mid+1,end]
        Keep pointers ii and jj to LL and RR respectively both initialized to start to the arrays
        Iterate over kk from \text{start}start to \text{end}end and set \text{A[k]}A[k] to the smaller of \text{L[i]}L[i] or \text{R[j]}R[j] and increment the respective index

        Complexity analysis

        Time complexity: O(nlogn)

        In each step we divide the array into 2 sub-arrays, and hence, the maximum times we need to divide is equal to O(\log n)O(logn)
        Additional O(n)O(n) work needs to be done to count the inversions and to merge the 2 sub-arrays after sorting. Hence total time complexity is O(n\log n)O(nlogn)
        Space complexity: O(n). Additional space for storing LL and RR array
    */
    int doit_mergesort(vector<int>& nums)
    {
        auto merge = [](vector<int>& A, int start, int mid, int end)
        {
            int n1 = (mid - start + 1);
            int n2 = (end - mid);
            vector<int> L(n1), R(n2);

            for (int i = 0; i < n1; i++)
                L[i] = A[start + i];
            for (int j = 0; j < n2; j++)
                R[j] = A[mid + 1 + j];
            int i = 0, j = 0;
            for (int k = start; k <= end; k++) {
                if (j >= n2 || (i < n1 && L[i] <= R[j]))
                    A[k] = L[i++];
                else
                    A[k] = R[j++];
            }
        };

        std::function<int(vector<int>&, int, int)> mergesort_and_count = [&](vector<int>& A, int start, int end)
        {
            if (start >= end) return 0;
            
            int mid = (start + end) / 2;
            int count = mergesort_and_count(A, start, mid) + mergesort_and_count(A, mid + 1, end);
            int j = mid + 1;
            
            for (int i = start; i <= mid; i++) {
                while (j <= end && A[i] > A[j] * 2LL)
                    j++;
                count += j - (mid + 1);
            }
            
            merge(A, start, mid, end);
            return count;
        };

        return mergesort_and_count(nums, 0, nums.size() - 1);
    }

    /*
        Approach 3: BIT
        Intuition

        The problem with BST is that the tree can be skewed hence, making it O(n^2)O(n 
        2
        ) in complexity. So, need a data structure that remains balanced. We could either use a Red-black or AVL tree to make a balanced BST, but the implementation would be an overkill for the solution. We can use BIT (Binary Indexed Tree, also called Fenwick Tree) to ensure that the complexity is O(n\log n)O(nlogn) with only 12-15 lines of code.

        BIT Overview:

        Fenwick Tree or BIT provides a way to represent an array of numbers in an array(can be visualized as tree), allowing prefix/suffix sums to be calculated efficiently(O(\log n)O(logn)). BIT allows to update an element in O(\log n)O(logn) time.

        We recommend having a look at BIT from the following link before getting into details:

        https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
        So, BIT is very useful to accumulate information from front/back and hence, we can use it in the same way we used BST to get the count of elements that are greater than or equal to 2 * \text{nums[i]} + 12∗nums[i]+1 in the existing tree and then adding the current element to the tree.

        Algorithm

        First, lets review the BIT query and update routines of BIT. 
        According to the convention, query routine goes from index to 0, i.e., BIT[i] gives the sum for the range [0,index], and update updates the values from current index to the end of array. 
        
        ***
        But, since, we require to find the numbers greater than the given index, as and when we update an index, we update all the ancestors of the node in the tree, and for search, we go from the node to the end.

        The modified update algorithm is:

        update(BIT, index, val):
        while(index > 0):
            BIT[index] += val
            index -= (index & (-index))

        Herein, we find get the next index using: index -= index & (-index), which is essentially subtracting the rightmost 1 from the index binary representation. 
        We update the previous indices since, if an element is greater than the index

        And the modified query algorithm is:

        query(BIT,index):
        sum=0
        while(index<BIT.size):
            sum+=BIT[index]
            index+=(index&(-index))

        Herein, we find get the next index using: \text{index += index \& (-index)}index += index & (-index). This gives the suffix sum from indexindex to the end.

        So, the main idea is to count the number of elements greater than 2*\text{nums[i]}2∗nums[i] in range [0,i)[0,i) as we iterate from 00 to \text{size-1}size-1. The steps are as follows:

        Create a copy of \text{nums}nums, say \text{nums\_copy}nums_copy ans sort \text{nums\_copy}nums_copy. This array is actually used for creating the Binary indexed tree
        Initialize \text{count}=0count=0 and \text{BIT}BIT array of size \text{size(nums)} + 1size(nums)+1 to store the BIT
        Iterate over ii from 00 to \text{size(nums)}-1size(nums)−1 :
        Search the index of element not less than 2*\text{nums[i]}+12∗nums[i]+1 in \text{nums\_copy}nums_copy array. \text{query}query the obtained index+1 in the \text{BIT}BIT, and add the result to \text{count}count
        Search for the index of element not less than nums[i]nums[i] in \text{nums\_copy}nums_copy. We need to \text{update}update the BIT for this index by 1. 
        This essentially means that 1 is added to this index(or number of elements greater than this index is incremented). The effect of adding 11 to the index is passed to the ancestors as shown in \text{update}update algorithm

        Complexity analysis

        Time complexity: O(nlogn)
        
        In \text{query}query and \text{update}update operations, we see that the loop iterates at most the number of bits in \text{index}index which can be at most nn. Hence, the complexity of both the operations is O(\log n)O(logn)(Number of bits in nn is \log nlogn)
        The in-built operation \text{lower\_bound}lower_bound is binary search hence O(\log n)O(logn)
        We perform the operations for nn elements, hence the total complexity is O(n\log n)O(nlogn)
        
        Space complexity: O(n). Additional space for \text{BITS}BITS array
    */
    void update(vector<int>& BIT, int index, int val)
    {
        while (index > 0) {
            BIT[index] += val;
            index -= index & (-index);
        }
    }

    int query(vector<int>& BIT, int index)
    {
        int sum = 0;
        while (index < BIT.size()) {
            sum += BIT[index];
            index += index & (-index);
        }
        return sum;
    }
    int doit_BIT(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> nums_copy(nums);

        sort(nums_copy.begin(), nums_copy.end());

        vector<int> BITS(n + 1, 0);
        int count = 0;
        for (int i = 0; i < n; i++) {
            count += query(BITS, lower_bound(nums_copy.begin(), nums_copy.end(), 2LL * nums[i] + 1) - nums_copy.begin() + 1);
            update(BITS, lower_bound(nums_copy.begin(), nums_copy.end(), nums[i]) - nums_copy.begin() + 1, 1);
        }
        return count;
    }

    // Wrong to use 
    int doit_BIT(vector<int>& nums) {
        
        int N = nums.size();
        int minv = * min_element(begin(nums), end(nums));
        int maxv = *max_element(begin(nums), end(nums));
        int length = minv >= 0 ? 2 * maxv + 1 : 2 * (maxv - minv) + 1;
        vector<int> BITS(length, 0);

        auto update = [&](int val) {
            val++;
            while (val < BITS.size()) {
                BITS[val]++;
                val += val & (-val);
            }
        };

        auto rangesum = [&](int val) {
            val++;
            int total = 0;
            while (val > 0) {
                total += BITS[val];
                val -= val & (-val);
            }
            return total;
        };

        int ans = 0;
        for (int i = N-1; i >= 0; i--) {
            nums[i] -= minv;
            ans += rangesum(nums[i]-1);
            update(2*nums[i]);
        }

        return ans;
    }
};