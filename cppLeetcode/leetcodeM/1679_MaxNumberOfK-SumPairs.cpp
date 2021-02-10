/*
1679. Max Number of K-Sum Pairs

You are given an integer array nums and an integer k.

In one operation, you can pick two numbers from the array whose sum equals k and remove them from the array.

Return the maximum number of operations you can perform on the array.

 

Example 1:

Input: nums = [1,2,3,4], k = 5
Output: 2
Explanation: Starting with nums = [1,2,3,4]:
- Remove numbers 1 and 4, then nums = [2,3]
- Remove numbers 2 and 3, then nums = []
There are no more pairs that sum up to 5, hence a total of 2 operations.
Example 2:

Input: nums = [3,1,3,4,3], k = 6
Output: 1
Explanation: Starting with nums = [3,1,3,4,3]:
- Remove the first two 3's, then nums = [1,4,3]
There are no more pairs that sum up to 6, hence a total of 1 operation.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= k <= 109

*/
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class MaxOperations {

public:


    /*
        Approach 3: Using Hashmap - Single Pass
        Intuition

        In the previous approach, we iterated over the array twice. In the first pass, we were just building the hashmap. In the second pass, we found a pair for every element. Can we do the same in a single pass?

        For every element current, we must first try to find if it's pair,complement exists in the map. If it does, there is no need to add the current element to the map and we could simply remove the complement element from the map. If the complement element does not exist in the map, we could add the current element to the map.

        In this approach, the hashmap would only hold those array elements for which we have not yet found a suitable pair so far with sum equal to k. As and when the elements are paired up, we remove them from the map.

        Thus, in a single pass, we can build the map as well as find the matching pair of every element. Let's look at the algorithm in detail.

        Algorithm

        Initialize a hashmap map to store the elements that are traversed till now and not paired up with any element so far.

        A variable count would be initialized to 00 and store the total number of pairs we find in the array.

        Iterate over each element in the array nums. For every traversed element current, calculate the complement value with respect to k. complement = k - current. Now check if the complement value exists in the map.

        If the complement value exists in the map, simply remove it from the map. Note that, we would not add the current element in the map here, since it is already paired with complement.
        Otherwise, add the current element to the map, so that it can be paired with some other array element in the future.
        Implementation


        Complexity Analysis

        Time Complexity : O(n), where nn is the length of array nums. We iterate over every element only once. Besides, checking or updating the value of a particular key element in the hashmap takes constant time. This gives us total time complexity as \mathcal{O}(n)O(n).

        Space Complexity: O(n), where nn is the length of array nums. We use an unordered map to store the values of the array with their count of occurrence. In the worst case, if we do not find a complement pair of any current element, we would end up adding all the elements in the map and the maximum size of the map would grow up to nn.
    */
    
    int doit_hahstable_1(vector<int>& nums, int k) {

        unordered_map<int, int> map;
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            int current = nums[i];
            int complement = k - current;
            if (map[complement] > 0) {
                // remove complement from the map
                map[complement] = map[complement] - 1;
                count++;
            } else {
                 // add current element in the map
                map[current] = map[current] + 1;
            }
        }
        return count;
    }

    int doit_hashtable(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        int count = 0;
        // build the hashmap with count of occurence of every element in array
        for (int i = 0; i < nums.size(); i++) {
            map[nums[i]] = map[nums[i]] + 1;
        }

        for (int i = 0; i < nums.size(); i++) {
            int current = nums[i];
            int complement = k - nums[i];

            if (map[current] > 0 && map[complement] > 0) {
                if ((current == complement) && map[current] < 2) 
                    continue;

                map[current] = map[current] - 1;
                map[complement] = map[complement] - 1;
                count++;
            }
        }

        return count;
    }

    /*
        Approach 4: Two Pointer Approach Using Sort
        Intuition

        There is another approach to solve the problem. What if we sort the elements in an array in increasing order? Can we take advantage of this sorted order to find the pairs quickly?

        In sorted array, we know that for every i^{th}i 
        th
        element, the value of (i+1)^{th}(i+1) 
        th
        element would always be greater than or equal it's own value. Similarly, the value of (i-1)^{th}(i−1) 
        th
        element would be less than or equal to its value.

        We can use 22 pointers, the first pointer left, is positioned at 0^{th}0 
        th
        index of the array, and the second pointer right is positioned at n^{th}n 
        th
        index of the array. (where n is the size of array nums). Let's add the values of elements pointed by left and right, given by sum.

        The value of the variable sum can be used to determine where a possible pair could lie,

        If the value of sum is less than the value of k, we know that we want a larger value. We also know that left is pointing to the smallest value in the array, hence we can increment the left pointer by 11 to get a little larger value.

        Similarly, if the value of sum is greater than the value of k, we know that we want a smaller value. We also know that right is pointing to the largest value in the array, hence we can decrement the right pointer by 11 to get a little smaller value.

        Otherwise, the value of sum must be equal to k and we have found one pair of elements pointed by left and right pointers respectively. We can increment the left pointer and decrement right pointer to find the next pair.

        In other words, we could say that, if the left pointer is pointing to the current element, we must adjust the right pointer to point to its complement and vice versa.

        The following example illustrates the idea with nums = [3, 1, 9, 3, 2, 2, 4] and k = 6.

        img

        Let's look at the algorithm in detail.

        Algorithm

        Sort the nums array in increasing i.e ascending order. We can use the built-in sort function.

        Initialize the left pointer to point at the 0^{th}0 
        th
        index and the right pointer to point to the last index of the nums array. We could say that the left pointer points to the smallest element in the array, and the right points to the largest element.

        Add the values of array elements pointed by left and right pointer given by sum.

        If the value of sum is less than k, increment left pointer.
        If the value of sum is greater than k, increment the right pointer.
        Otherwise, we have found one pair with a sum equal to k. Increment left pointer and decrement right pointer so that we can go ahead and find another pair.
        The process would continue until the left pointer is less than the right pointer. Once the left and right pointer cross each other, we know that we have traversed all the elements and cannot find any other pair. Hence, we stop at that point.

        Implementation


        Complexity Analysis

        Time Complexity : \mathcal{O}(n \log n)O(nlogn), where nn is the length of array nums.

        The sort operation on the array takes \mathcal{O}(n \log n)O(nlogn) time.

        Each element is traversed only once, either by the left pointer or by the right pointer, depending on the fact that which pointer reaches that element first. Thus, traversing array takes \mathcal{O}(n)O(n) time.

        This gives us total time complexity as \mathcal{O}(n \log n)O(nlogn) + \mathcal{O}(n)O(n) = \mathcal{O}(n \log n)O(nlogn).

        Space Complexity: \mathcal{O}(1)O(1). We use constant extra space to track the count variable and maintain left,right pointers.

        Space complexity : \mathcal{O}(N)O(N) or \mathcal{O}(\log{N})O(logN)

        The space complexity of the sorting algorithm depends on the implementation of each program language.

        For instance, the std::sort() function in C++ is implemented with the Introsort algorithm whose space complexity is \mathcal{O}(N)O(N).

        In Java, the Arrays.sort() is implemented as a variant of quicksort algorithm whose space complexity is \mathcal{O}(\log{N})O(logN).
    */
    int doit_twopointer(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int count = 0;
        int left = 0;
        int right = nums.size() - 1;
        
        while (left < right) {
            if (nums[left] + nums[right] < k) {
                left++;
            } else if (nums[left] + nums[right] > k) {
                right--;
            } else {
                left++;
                right--;
                count++;
            }
        }
        return count;
    }

};