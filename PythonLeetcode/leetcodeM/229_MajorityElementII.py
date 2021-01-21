"""
169. Majority Element

Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-231 <= nums[i] <= 231 - 1
 

Follow-up: Could you solve the problem in linear time and in O(1) space?

"""
class MajorityElement1:

    """
        Approach 2: HashMap
        Intuition

        We know that the majority element occurs more than n//2 times, and a HashMap allows us to count element occurrences efficiently.

        Algorithm

        We can use a HashMap that maps elements to counts in order to count occurrences in linear time by looping over nums. Then, we simply return the key with maximum value.

        Complexity Analysis

        Time complexity : O(n)

        We iterate over nums once and make a constant time HashMap insertion on each iteration. Therefore, the algorithm runs in O(n)O(n) time.

        Space complexity : O(n)
    """
    def doit_(self, nums: list) -> int:
        import collections
        counts = collections.Counter(nums)
        return max(counts.keys(), key=counts.get)


    """
        Approach 3: Sorting
        Intuition

        If the elements are sorted in monotonically increasing (or decreasing) order, the majority element can be found at index \lfloor \dfrac{n}{2} \rfloor⌊ 
        2
        n
        ​	
        ⌋ (and \lfloor \dfrac{n}{2} \rfloor + 1⌊ 
        2
        n
        ​	
        ⌋+1, incidentally, if nn is even).

        Algorithm

        For this algorithm, we simply do exactly what is described: sort nums, and return the element in question. To see why this will always return the majority element (given that the array has one), consider the figure below (the top example is for an odd-length array and the bottom is for an even-length array):
    
        Complexity Analysis

        Time complexity : O(nlgn)

        Sorting the array costs O(nlgn) time in Python and Java, so it dominates the overall runtime.

        Space complexity : O(1) or O(n)

        We sorted nums in place here - if that is not allowed, then we must spend linear additional space on a copy of nums and sort the copy instead.
    
    """
    def doit_sort(self, nums):
        nums.sort()
        return nums[len(nums)//2]

    """
        Approach 5: Divide and Conquer
        Intuition

        If we know the majority element in the left and right halves of an array, we can determine which is the global majority element in linear time.

        Algorithm

        Here, we apply a classical divide & conquer approach that recurses on the left and right halves of an array until an answer can be trivially achieved for a length-1 array. 
        Note that because actually passing copies of subarrays costs time and space, we instead pass lo and hi indices that describe the relevant slice of the overall array. 
        In this case, the majority element for a length-1 slice is trivially its only element, so the recursion stops there. If the current slice is longer than length-1, we must combine the answers for the slice's left and right halves. 
        If they agree on the majority element, then the majority element for the overall slice is obviously the same[1]. 
        If they disagree, only one of them can be "right", so we need to count the occurrences of the left and right majority elements to determine which subslice's answer is globally correct. 
        The overall answer for the array is thus the majority element between indices 0 and nn.
    """
    def doit_divide_and_conquer(self, nums, lo=0, hi=None):
        def majority_element_rec(lo, hi):
            # base case; the only element in an array of size 1 is the majority
            # element.
            if lo == hi:
                return nums[lo]

            # recurse on left and right halves of this slice.
            mid = (hi-lo)//2 + lo
            left = majority_element_rec(lo, mid)
            right = majority_element_rec(mid+1, hi)

            # if the two halves agree on the majority element, return it.
            if left == right:
                return left

            # otherwise, count each element and return the "winner".
            left_count = sum(1 for i in range(lo, hi+1) if nums[i] == left)
            right_count = sum(1 for i in range(lo, hi+1) if nums[i] == right)

            return left if left_count > right_count else right

        return majority_element_rec(0, len(nums)-1)

    """
        Approach 6: Boyer-Moore Voting Algorithm
        Intuition

        If we had some way of counting instances of the majority element as +1+1 and instances of any other element as -1−1, summing them would make it obvious that the majority element is indeed the majority element.

        Algorithm

        Essentially, what Boyer-Moore does is look for a suffix sufsuf of nums where suf[0]suf[0] is the majority element in that suffix. To do this, we maintain a count, which is incremented whenever we see an instance of our current candidate for majority element and decremented whenever we see anything else. Whenever count equals 0, we effectively forget about everything in nums up to the current index and consider the current number as the candidate for majority element. It is not immediately obvious why we can get away with forgetting prefixes of nums - consider the following examples (pipes are inserted to separate runs of nonzero count).

        [7, 7, 5, 7, 5, 1 | 5, 7 | 5, 5, 7, 7 | 7, 7, 7, 7]

        Here, the 7 at index 0 is selected to be the first candidate for majority element. count will eventually reach 0 after index 5 is processed, so the 5 at index 6 will be the next candidate. In this case, 7 is the true majority element, so by disregarding this prefix, we are ignoring an equal number of majority and minority elements - therefore, 7 will still be the majority element in the suffix formed by throwing away the first prefix.

        [7, 7, 5, 7, 5, 1 | 5, 7 | 5, 5, 7, 7 | 5, 5, 5, 5]

        Now, the majority element is 5 (we changed the last run of the array from 7s to 5s), but our first candidate is still 7. In this case, our candidate is not the true majority element, but we still cannot discard more majority elements than minority elements (this would imply that count could reach -1 before we reassign candidate, which is obviously false).

        Therefore, given that it is impossible (in both cases) to discard more majority elements than minority elements, we are safe in discarding the prefix and attempting to recursively solve the majority element problem for the suffix. Eventually, a suffix will be found for which count does not hit 0, and the majority element of that suffix will necessarily be the same as the majority element of the overall array.

        Complexity Analysis

        Time complexity : O(n)O(n)

        Boyer-Moore performs constant work exactly nn times, so the algorithm runs in linear time.

        Space complexity : O(1)O(1)

        Boyer-Moore allocates only constant additional memory.
    """
    def doit_(self, nums):
        count = 0
        candidate = None

        for num in nums:
            if count == 0:
                candidate = num
            count += (1 if num == candidate else -1)

        return candidate


"""
229. Majority Element II


Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Follow-up: Could you solve the problem in linear time and in O(1) space?

 

Example 1:

Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]
Example 3:

Input: nums = [1,2]
Output: [1,2]
 

Constraints:

1 <= nums.length <= 5 * 10^4
-10^9 <= nums[i] <= 10^9

"""


class MajorityElementII:
    
    def doit(self, nums: list) -> list:
        from collections import Counter
        N = len(nums)
        ans = []
        buff = Counter(nums)
        for k, v in buff.items():
            if v > N//3:
                ans.append(k)
        return ans

    """
        Approach 1: Boyer-Moore Voting Algorithm
        Intuition

        To figure out a O(1)O(1) space requirement, we would need to get this simple intuition first. For an array of length n:

        There can be at most one majority element which is more than ⌊n/2⌋ times.
        There can be at most two majority elements which are more than ⌊n/3⌋ times.
        There can be at most three majority elements which are more than ⌊n/4⌋ times.
        and so on.

        Knowing this can help us understand how we can keep track of majority elements which satisfies O(1)O(1) space requirement.

        Let's try to get an intuition for the case where we would like to find a majority element which is more than ⌊n/2⌋ times in an array of length n.

        The idea is to have two variables, one holding a potential candidate for majority element and a counter to keep track of whether to swap a potential candidate or not. Why can we get away with only two variables? Because there can be at most one majority element which is more than ⌊n/2⌋ times. Therefore, having only one variable to hold the only potential candidate and one counter is enough.

        While scanning the array, the counter is incremented if you encounter an element which is exactly same as the potential candidate but decremented otherwise. When the counter reaches zero, the element which will be encountered next will become the potential candidate. Keep doing this procedure while scanning the array. However, when you have exhausted the array, you have to make sure that the element recorded in the potential candidate variable is the majority element by checking whether it occurs more than ⌊n/2⌋ times in the array. In the original Majority Element problem, it is guaranteed that there is a majority element in the array so your implementation can omit the second pass. However, in a general case, you need this second pass since your array can have no majority elements at all!

        The counter is initialized as 0 and the potential candidate as None at the start of the array.

        Current
        1 / 10
        If an element is truly a majority element, it will stick in the potential candidate variable, no matter how it shows up in the array (i.e. all clustered in the beginning of the array, all clustered near the end of the array, or showing up anywhere in the array), after the whole array has been scanned. Of course, while you are scanning the array, the element might be replaced by another element in the process, but the true majority element will definitely remain as the potential candidate in the end.

        Now figuring out the majority elements which show up more than ⌊n/3⌋ times is not that hard anymore. Using the intuition presented in the beginning, we only need four variables: two for holding two potential candidates and two for holding two corresponding counters. Similar to the above case, both candidates are initialized as None in the beginning with their corresponding counters being 0. While going through the array:

        If the current element is equal to one of the potential candidate, the count for that candidate is increased while leaving the count of the other candidate as it is.
        If the counter reaches zero, the candidate associated with that counter will be replaced with the next element if the next element is not equal to the other candidate as well.
        Both counters are decremented only when the current element is different from both candidates.
        Current
        1 / 10
        Implementation


        Complexity Analysis

        Time complexity : O(N) where NN is the size of nums. We first go through nums looking for first and second potential candidates. We then count the number of occurrences for these two potential candidates in nums. Therefore, our runtime is O(N) + O(N) = O(2N) \approx O(N)O(N)+O(N)=O(2N)≈O(N).

        Space complexity : O(1) since we only have four variables for holding two potential candidates and two counters. Even the returning array is at most 2 elements.
    """
    def doit_(self, nums: list):
        if not nums:
            return []
        
        # 1st pass
        count1, count2, candidate1, candidate2 = 0, 0, None, None

        for n in nums:
        
            if candidate1 == n:
                count1 += 1
        
            elif candidate2 == n:
                count2 += 1
        
            elif count1 == 0:
                candidate1 = n
                count1 += 1
        
            elif count2 == 0:
                candidate2 = n
                count2 += 1
        
            else:
                count1 -= 1
                count2 -= 1
        
        # 2nd pass
        result = []
        for c in [candidate1, candidate2]:
            if nums.count(c) > len(nums)//3:
                result.append(c)

        return result
        