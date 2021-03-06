/*
442. Find All Duplicates in an Array


Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]


*/
#include <vector>
#include <unordered_set>
#include <algorithm>

using std::unordered_set;
using std::vector;


class FindAllDuplicatesArray {

    /*
        442.Find-All-Duplicates-in-an-Array
        解法1
        此题和 041.First-Missing-Positive 的解法非常相似。题目的共同点是：数组的元素规定了是从1~N. 这就强烈暗示了，如果试图把正整数1~N顺次放入nums[1]~nums[N]中，那么没有被正确归位的那个元素（即nums[i]!=i）一定有“问题”。

        对于“把正整数1~N顺次放入nums[1]~nums[N]中”的这种特殊的排序任务，有如下典型的时间复杂度o(n)、空间复杂度o(1)的方法：

        遍历所有元素nums[i]，发现如果nums[i]!=i时，说明当前的nums[i]这个数没有被放置在合适的顺序位置。于是交换nums[i]和nums[nums[i]]。这样做的结果是：把nums[i]放到了它应该在的位置（正确归位），同时nums[i]有了新的值，需要再重复判断、交换的过程。这样的步骤持续到 nums[i]==nums[nums[i]]，这样就到了一个死循环，对于i这个位置就不能再做任何操作，于是跳过。

        等到所有元素都遍历结束，那么所有元素就会被“力所能及”地归入了它们应该在的顺序位置。那么此时，对于那些nums[i]!=i的、没有正确归位的元素，在本题的题意下，就是那些重复的元素，可以轻易地挑出来。

        解法2
        还有一种比较花哨的解法。对于数值x，我们如何不通过extra space来记录它是否出现过呢？方法是将nums[x]上的数字变成负数来进行标记，注意我们并不关心nums[x]是多少。只关心nums[x]是负数时表示x曾经出现过，反之表示x还没出现过。

        所以我们依次遍历数组里的每个数字abs(x)，注意我们关心数值时必须看的是abs(x)，因为x的符号可能被encode了其他含义（如上所说）。如果nums[abs[x]]<0，表示abs(x)曾经出现过，加入我们的答案中。反之，说明abs(x)第一次出现，所以我们将nums[abs(x)]标记为负数，以此留下这个标记。
    */
    vector<int> findDuplicates(vector<int>& nums) 
    {
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
                rets.push_back(nums[i]);
        }
        return rets;
    }

    vector<int> findDuplicates(vector<int>& nums) 
    {
        int n = nums.size();
        nums.insert(nums.begin(),0);
        vector<int>results;
        for (int i=1; i<=n; i++)
        {
            if (nums[abs(nums[i])]<0)
                results.push_back(abs(nums[i]));
            else
                nums[abs(nums[i])] *= -1;                                  
        }
        return results;
    }



public:

    vector<int> doit_indexingsort(vector<int>& nums) {
        
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != i+1 && nums[i] != nums[nums[i]-1]) {
                std::swap(nums[i], nums[nums[i]-1]);
            }
        }

        vector<int> ans;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] != i+1) ans.push_back(nums[i]);
        
        return ans;
    }

    /*
        Pop Quiz: Can you do this in a single loop?

        Definitely! Notice that if an element x occurs just once in the array, the value at index abs(x)-1 becomes negative and remains 
        so for all of the iterations that follow.

        Traverse through the array. When we see an element x for the first time, we'll negate the value at index abs(x)-1.
        But, the next time we see an element x, we don't need to negate again! If the value at index abs(x)-1 is already negative, we know that we've seen element x before.
        So, now we are relying on a single negation to mark the visited status of an element. 
        This is similar to what we did in Approach 3, except that we are re-using the array (with some smart negations) instead of a separate set.
    
    */
    vector<int> doit_indexingsort_2(vector<int>& nums) {
        vector<int> ans;

        for (auto num : nums) {
            if (nums[abs(num) - 1] < 0) {  // seen before
                ans.push_back(abs(num));
            }
            nums[abs(num) - 1] *= -1;
        }

        return ans;
    }

        /*
        Approach 4: Mark Visited Elements in the Input Array itself
        Intuition

        All the above approaches have ignored a key piece of information in the problem statement:

        The integers in the input array arr satisfy 1 ≤ arr[i] ≤ n, where n is the size of array. [2]

        This presents us with two key insights:

        All the integers present in the array are positive. i.e. arr[i] > 0 for any valid index i. [3]
        The decrement of any integers present in the array must be an accessible index in the array.
        i.e. for any integer x in the array, x-1 is a valid index, and thus, arr[x-1] is a valid reference to an element in the array. [4]
        Algorithm

        Iterate over the array and for every element x in the array, negate the value at index abs(x)-1. [5]
        The negation operation effectively marks the value abs(x) as seen / visited.
        Pop Quiz: Why do we need to use abs(x), instead of x?

        Iterate over the array again, for every element x in the array:
        If the value at index abs(x)-1 is positive, it must have been negated twice. Thus abs(x) must have appeared twice in the array. We add abs(x) to the result.
        In the above case, when we reach the second occurrence of abs(x), we need to avoid fulfilling this condition again. So, we'll additionally negate the value at index abs(x)-1.
    

    */
    vector<int> doit_element(vector<int>& nums) {
        vector<int> ans;

        for (auto num : nums)
            nums[abs(num) - 1] *= -1;

        for (auto num : nums)
            if (nums[abs(num) - 1] > 0) {
                ans.push_back(abs(num));
                nums[abs(num) - 1] *= -1;
            }

        return ans;
    }


    /*
        Approach 1: Brute Force
        Intuition

        Check for a second occurrence of every element in the rest of the array.

        Algorithm

        When we iterate over the elements of the input array, we can simply look for any other occurrence of the current element in the rest of the array.

        Since an element can only occur once or twice, we don't have to worry about getting duplicates of elements that appear twice:

        Case - I: If an element occurs only once in the array, when you look for it in the rest of the array, you'll find nothing.
        Case - II: If an element occurs twice, you'll find the second occurrence of the element in the rest of the array. 
        When you chance upon the second occurrence in a later iteration, it'd be the same as Case - I (since there are no more occurrences of this element in the rest of the array).

        Complexity Analysis

        Time complexity : \mathcal{O}(n^2)O(n 
        2
        ).

        For each element in the array, we search for another occurrence in the rest of the array. Hence, for the i^{{th}}i 
        th
        element in the array, we might end up looking through all n - in−i remaining elements in the worst case. So, we can end up going through about n^2n 
        2
        elements in the worst case.

        n-1 + n-2 + n-3 + .... + 1 + 0 = \sum_{1}^{n}(n-i) \simeq n^2n−1+n−2+n−3+....+1+0=∑ 
        1
        n
        ​	
        (n−i)≃n 
        2
        

        Space complexity : No extra space required, other than the space for the output list.
    */
    vector<int> doit_bruteforce(vector<int>& nums) {

        vector<int> ans;

        for (int i = 0; i < nums.size(); i++)
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] == nums[i]) {
                    ans.push_back(nums[i]);
                    break;
                }
            }

        return ans;
    }

    /*
        Approach 2: Sort and Compare Adjacent Elements
        Intuition

        After sorting a list of elements, all elements of equivalent value get placed together. Thus, when you sort an array, equivalent elements form contiguous blocks.

        Algorithm

        Sort the array.
        Compare every element with it's neighbors. If an element occurs more than once, it'll be equal to at-least one of it's neighbors.
        To simplify:

        Compare every element with its predecessor.
        Obviously the first element doesn't have a predecessor, so we can skip it.
        Once we've found a match with a predecessor, we can skip the next element entirely!
        Why? Well, if an element matches with its predecessor, it cannot possibly match with its successor as well. Thus, the next iteration (i.e. comparison between the next element and the current element) can be safely skipped.

        Complexity Analysis

        Time complexity : \mathcal{O}(n \log{n}) + \mathcal{O}(n) \simeq \mathcal{O}(n \log{n})O(nlogn)+O(n)≃O(nlogn).

        A performant comparison-based sorting algorithm will run in \mathcal{O}(n \log{n})O(nlogn) time. Note that this can be reduced to \mathcal{O}(n)O(n) using a special sorting algorithm like Radix Sort.

        Traversing the array after sorting takes linear time i.e. \mathcal{O}(n)O(n).

        Space complexity : No extra space required, other than the space for the output list. Sorting can be done in-place.
    */
    vector<int> doit_sort(vector<int>& nums) {
        vector<int> ans;

        std::sort(nums.begin(), nums.end());

        for (int i = 1; i < nums.size(); i++)
            if (nums[i] == nums[i - 1]) {
                ans.push_back(nums[i]);
                i++;        // skip over next element
            }

        return ans;
    }

    /*
    
        Approach 3: Store Seen Elements in a Set / Map
        Intuition

        In Approach 1 we used two loops (one nested within the other) to look for two occurrences of an element. In almost all similar situations, you can usually substitute one of the loops with a set / map. Often, it's a worthy trade-off: for a bit of extra memory, you can reduce the order of your runtime complexity.

        Algorithm

        We store all elements that we've seen till now in a map / set. When we visit an element, we query the map / set to figure out if we've seen this element before.

        Complexity Analysis

        Time complexity : \mathcal{O}(n)O(n) average case. \mathcal{O}(n^2)O(n 
        2
        ) worst case.

        It takes a linear amount of time to iterate through the array.
        Lookups in a hashset are constant time on average, however those can degrade to linear time in the worst case. Note that an alternative is to use tree-based sets, which give logarithmic time lookups always.
        Space complexity : Upto \mathcal{O}(n)O(n) extra space required for the set.

        If you are tight on space, you can significantly reduce your physical space requirements by using bitsets [1] instead of sets. This data-structure requires just one bit per element, so you can be done in just nn bits of data for elements that go up-to nn. Of course, this doesn't reduce your space complexity: bitsets still grow linearly with the range of values that the elements can take.

    */
    vector<int> doit_hashtable(vector<int>& nums) {
        vector<int> ans;
        unordered_set<int> seen;

        for (auto& num : nums) {
            if (seen.count(num) > 0)
                ans.push_back(num);
            else
                seen.insert(num);
        }

        return ans;
    }
};