/*
1345. Jump Game IV


Given an array of integers arr, you are initially positioned at the first index of the array.

In one step you can jump from index i to index:

i + 1 where: i + 1 < arr.length.
i - 1 where: i - 1 >= 0.
j where: arr[i] == arr[j] and i != j.
Return the minimum number of steps to reach the last index of the array.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
Example 2:

Input: arr = [7]
Output: 0
Explanation: Start index is the last index. You don't need to jump.
Example 3:

Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: You can jump directly from index 0 to index 7 which is last index of the array.
Example 4:

Input: arr = [6,1,9]
Output: 2
Example 5:

Input: arr = [11,22,7,7,7,7,7,7,7,22,13]
Output: 3
 

Constraints:

1 <= arr.length <= 5 * 10^4
-10^8 <= arr[i] <= 10^8


*/
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::unordered_set;
using std::unordered_map;
using std::vector;


class JumpGameIV {

public:


    int doit_set(vector<int>& nums) {
        int n = nums.size();
        int result = 0;
        unordered_set<int> set;
        for (int start = 0; start < n; start++) {
            // reset set and current sum for next subarray
            set.clear();
            int currentSum = 0;
            for (int end = start; end < n && (set.find(nums[end]) == set.end());
                 end++) {
                currentSum += nums[end];
                set.insert(nums[end]);
            }
            // update result with maximum sum found so far
            result = std::max(result, currentSum);
        }
        return result;
    }

    /*
        Approach 2: Two Pointer Approach Using Set
        Intuition

        We could optimize Approach 1. Instead of blindly looking for all the subarrays and calculating their sum, we could make use of previous calculations.

        For example, for nums = [4, 2, 3, 5, 4, 1], we found a subarray having unique elements [4, 2, 3, 5] with sum 14 starting at index 0 and ending at 3.

        Now, the end pointer is incremented by 11 and we find that the element at index 4 is 44 which is already present in our current subarray. The subarray is now [4, 2, 3, 5, 4]. Here, instead of breaking the loop and re-initiating our search again from start index 1, we could simply reposition the start index such that there are unique elements in the array. How can we do that?

        The simple way is to increment the start pointer until we find element 4 and fix the start pointer at the index after that. As start is incremented, we are removing each element from our current subarray, hence we must also update the currentSum and set.

        The following figure illustrates the idea.

        img

        Algorithm

        We would maintain 22 pointers, start would point to the beginning and end would point to the end of the current subarray. Both pointers are initialized to 00.

        The end pointer would increment and expand the current subarray until all the array elements are unique. Now, we must use a set as in Approach 1 to check after every increment if the newly added element is unique or not.

        We must also keep track of the sum of elements in the current subarray. Let's use the variable currentSum for that.

        Now, we have to simply iterate over the array nums.

        If the newly added element pointed by index end is not present in set, then it is unique, we must add that element in set and also add it's value to the currentSum.

        Otherwise, we must remove elements from the subarray until the duplicate of the newly added element is removed from the subarray. One way to achieve that is to increment pointer start until the element pointed by pointer end is removed from the map.

        After every increment of the end pointer, if the currentSum is greater than the previous one, update the result.The process would continue until the end pointer has reached the end of array nums.

        Implementation


        Complexity Analysis

        Let nn be the length of array nums.

        Time Complexity: \mathcal{O}(n)O(n) We would iterate over each array element at most twice. First, to add it to the current subarray using the end pointer. Second, to remove it from the subarray using the start pointer. Also, adding/remove elements from the set would take constant time. This gives us time complexity as \mathcal{O}(2n)O(2n) which is roughly \mathcal{O}(n)O(n).

        Space Complexity: \mathcal{O}(n)O(n), as we are using a set to track all the unique elements. In the worst case, if all the array elements are unique, the set would grow up to size nn.

    */
    int maximumUniqueSubarray(vector<int>& nums) {
        int result = 0;
        int currentSum = 0;
        unordered_set<int> set;
        int start = 0;
        for (int end = 0; end < nums.size(); end++) {
            // increment start until subarray has unique elements
            while (set.find(nums[end]) != set.end()) {
                set.erase(nums[start]);
                currentSum -= nums[start];
                start++;
            }
            currentSum += nums[end];
            set.insert(nums[end]);
            // update result with maximum sum found so far
            result = std::max(result, currentSum);
        }
        return result;
    }



    /*
        Approach 3: Two Pointer Approach Using Boolean Array
        Intuition

        In the previous approach, we were using a set data structure to keep track of all the elements in the current subarray. There is little overhead to add and then remove elements from the set. Can we use some data structure where we could just mark or unmark the occurrence of an element instead of actually adding and removing the elements?

        We can use an array of type boolean instead of a set. We know that the maximum value of an array element can be 10^{4}10 
        4
        . So we can use a boolean array of size 10^{4}10 
        4
        and each index would represent the corresponding value in array nums.

        The following figure illustrates how we can store array [4, 6, 8, 1] in array nums.

        img

        Algorithm

        Build a boolean array isPresent to track the elements present in current subarray. If an element ii is added to the current subarray, mark isPresent[i] = true. Similarly, if an element ii, is removed from current subarray, mark isPresent[i] = false.

        Initialize the start and end pointer at 0^{th}0 
        th
        index and set currentSum to 00.

        Now, increment the end pointer by 11 and check if the newly added element is already present in the current subarray or not.

        If the newly added element pointed by index end is marked true in array isPresent, it is unique, add that element in set and also add its value to the currentSum.

        Otherwise, we must remove elements from the subarray until the duplicate of the newly added element is removed from the subarray. One way to achieve that is to increment pointer start until the element pointed by pointer end is removed from the map.

        After every increment of the end pointer, if the currentSum is greater than the previous one, update the result.The process would continue until the end pointer has reached the end of array nums.

        Implementation


        Complexity Analysis

        Let nn be the length of array nums.

        Time Complexity: \mathcal{O}(n)O(n) We would iterate over each array element at most twice. First, to add it to the current subarray using the end pointer. Second, to remove it from the subarray using the start pointer. This gives us time complexity as \mathcal{O}(2n)O(2n) which is roughly \mathcal{O}(n)O(n).

        Space Complexity: \mathcal{O}(1)O(1), as we use constant extra space for fixed size boolean array isPresent.


    */
    int doit_(vector<int>& nums) {
        int result = 0;
        int currentSum = 0;
        bool isPresent[10001]= {0};
        int start = 0;
        for (int end = 0; end < nums.size(); end++) {
            // increment start until subarray has unique elements
            while (isPresent[nums[end]]) {
                isPresent[nums[start]] = false;
                currentSum -= nums[start];
                start++;
            }

            isPresent[nums[end]] = true;
            currentSum += nums[end];
            // update result with maximum sum found so far
            result = std::max(result, currentSum);
        }
        return result;
    }
    /*
        Approach 4: Two Pointer Approach Using Count Map
        Intuition

        This is just another way of implementing the solution. We can also use a count array of type integer to store the frequency of elements in the current subarray. An element is unique if it's frequency is 11.

        We can use a fixed size count array of size 10^{4}10 
        4
        to store the occurrence of an element in the current subarray. If a new element is added to the current subarray, it's count would be incremented. Similarly, if an element is removed from the current subarray, it's count would be decremented.

        As a new element is added to the subarray, we want to check if it's unique or not. We would know this information by checking if it's frequency in count array is 11. If the frequency is greater than 11, we would remove element from the beginning of current subarray until the frequency of the newly added element is exactly 11.

        Algorithm

        Build an integer array countMap to store the frequency of elements in current subarray. Initialize the start and end pointer at 0^{th}0 
        th
        index and set currentSum to 00.

        Increment the end pointer by 11 and update the element's frequency in countMap. Let the newly added element be currentElement, increment countMap[currentElement] by 11.

        If the value of countMap[currentElement] is greater than 11, it is not unique in the current subarray. Remove elements from current subarray by incrementing start pointer until the frequency of currentElement is 11.

        After every increment of the end pointer, if the currentSum is greater than the previous one, update the result.The process would continue until the end pointer has reached the end of array nums.

        Implementation


        Complexity Analysis

        Let nn be the length of array nums.

        Time Complexity: \mathcal{O}(n)O(n) We would iterate over each array element at most twice. First, to add it to the current subarray using the end pointer. Second, to remove it from the subarray using the start pointer. This gives us time complexity as \mathcal{O}(2n)O(2n) which is roughly \mathcal{O}(n)O(n).

        Space Complexity: \mathcal{O}(1)O(1), as we use constant extra space for fixed size integer array countMap.
    
    
    */
    int doit_(vector<int>& nums) {
        vector<int> countMap(10001, 0);
        int start = 0;
        int result = 0;
        int currentSum = 0;
        for (int end = 0; end < nums.size(); end++) {
            int currentElement = nums[end];
            countMap[currentElement]++;
            currentSum += currentElement;
            while (start < end && countMap[currentElement] > 1) {
                countMap[nums[start]]--;
                currentSum -= nums[start];
                start++;
            }
            // update result with maximum sum found so far
            result = std::max(result, currentSum);
        }
        return result;
    }

    /*
        Approach 5: Using Prefix Sum with HashMap
        Intuition

        In all the previous approaches, when we find that the newly added element is not unique in the current subarray, we remove the elements from the beginning of the subarray one by one by incrementing the start pointer by 11 and shrink the subarray until the it contains all the unique elements.

        However, we already know the element that we want to remove from the current subarray.

        For example, if our current subarray is [2, 4, 3, 5] and has all unique elements, when a new element 4 is added to the subarray, we find that the resultant subarray [2, 4, 3, 5, 4] doesn't contain all unique elements. At this point, we are sure that the property of having all unique elements for the current subarray got violated because of the element 4 that was just added.

        Our goal is to somehow remove the old occurrence of 4 from the subarray to restore its property of having all unique elements. How can we do that?

        One way could be that, if we already know that the last index of element 4 in subarray was 11, we could remove that element, by moving the start pointer at index 22. After repositioning the start index, the current subarray would be [3, 5, 4] and contains all unique elements.

        Wait a minute !! Are we missing something?

        How would we now know the sum of all elements in subarray [3, 5, 4]? If we again iterate over each element of the subarray to get the current sum, our optimization would be a waste !!

        There is another idea for that. We can calculate the prefix sum of the array. The prefix sum stores sum of all elements till the current index starting from the 0^{th}0 
        th
        index. Example, the value at position prefixSum[i] would be the sum of all the values in arraynums from 0^{th}0 
        th
        index to i^{th}i 
        th
        index.

        So, in the above example, to get the sum of subarray [3, 5, 4] starting at index 2 and ending at index 4 we could simply calculate prefixSum[4] - prefixSum[1].

        The following figure illustrates the idea for nums = [2, 4, 3, 5, 4, 1].

        img

        Algorithm

        To implement the above idea, we need some data structure that could give us the last index of any element in constant time. We can use a map where the element would be the key and its value would be index when it last appeared in the array nums. Let the map be lastIndexMap.

        Initialize the start and end pointer at 0^{th}0 
        th
        index.

        Now, we must build the prefixSum which would give the sum of any subarray in the array nums. Instead of building it beforehand, we can calculate the prefix sum for every index as we iterate elements at each index.

        Initially, there is no element in the current subarray. We start adding an element to the subarray by incrementing the end pointer by 11 and iterating over nums. currentElement is the element pointed by pointer end.

        Calculate the prefix sum till end index and update in the array prefixSum.

        We have to check if the current subarray starting at index start and ending at index end has all unique elements. We already have a map that maintains the last indexes of all elements in the subarray. Can we reuse the same map?

        We could use this map to know the last index of currentElement. If the last occurrence of currentElement is between the start and end pointer, its last index would be greater than the start index. We can use this trick to determine if the currentElement is unique in the current subarray or not.

        If the last index of current element is greater than start, then update start to the position after last index of currentElement. This could be written as ,

        start = max(start, lastIndexMap.get(currentElement) + 1)
        At every iteration, update the result to track the maximum sum seen so far and return at the end.
        Implementation


        Complexity Analysis

        Let nn be the length of array nums.

        Time Complexity: \mathcal{O}(n)O(n) We iterate over every element only once.

        Space Complexity: \mathcal{O}(n)O(n), as in worst case the size of lastIndexMap would grow upto n. Also, we use an integer array prefixSum of size n.
    */
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> lastIndexMap;
        int prefixSum[n + 1];

        int result = 0, start = 0;
        for (int end = 0; end < n; end++) {
            int currentElement = nums[end];
            prefixSum[end + 1] = prefixSum[end] + currentElement;
            if (lastIndexMap.find(currentElement) != lastIndexMap.end()) {
                start = std::max(start, lastIndexMap.at(currentElement) + 1);
            }
            // update result with maximum sum found so far
            result = std::max(result, prefixSum[end + 1] - prefixSum[start]);
            lastIndexMap[currentElement] = end;
        }
        return result;
    }

    /*
        Approach 6: Using Prefix Sum with Count Array
        Intuition

        We could further improve Approach 5 by using a fixed size integer array to store the last indexes. With this, we can implement the problem in constant space.

        From the problem description, we know that the maximum value of any element in the array nums would be 10^{4}10 
        4
        , hence we could build the array of that size and store the last index of any element in the array.

        Algorithm

        Build an integer array lastIndexes of size 10^{6}10 
        6
        to store the last index of any element in the array. If currentElement is the last added element to the subarray having index end, we would update lastIndexes[currentElement] to i.

        Initially, all the values in the lastIndexes array would be initialized to -1.

        Iterate over each element as in Approach 6 and determine the maximum sum after every iteration. Update result with the maximum sum and return at the end.

        Implementation


        Complexity Analysis

        Let nn be the length of array nums.

        Time Complexity: \mathcal{O}(n)O(n) We iterate over every element only once.

        Space Complexity: \mathcal{O}(n)O(n), as we use constant extra space for fixed size array lastIndexes and linear space for integer array prefixSum of size n.
    */

    int doit_(vector<int>& nums) {

        int n = nums.size();
        vector<int> lastIndexes(10001, -1);
        int prefixSum[n + 1];
        int result = 0, start = 0;

        for (int end = 0; end < n; end++) {
            int currentElement = nums[end];
            prefixSum[end + 1] = prefixSum[end] + currentElement;
            if (lastIndexes[currentElement] != -1) {
                start = std::max(start, lastIndexes[currentElement] + 1);
            }
            // update result with maximum sum found so far
            result = std::max(result, prefixSum[end + 1] - prefixSum[start]);
            // update last index of current element
            lastIndexes[currentElement] = end;
        }

        return result;
    }
};