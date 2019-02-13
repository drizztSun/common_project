# 740. Delete and Earn

# Given an array nums of integers, you can perform operations on the array.

# In each operation, you pick any nums[i] and delete it to earn nums[i] points. 
# After, you must delete every element equal to nums[i] - 1 or nums[i] + 1.

# You start with 0 points. Return the maximum number of points you can earn by applying such operations.

# Example 1:

# Input: nums = [3, 4, 2]
# Output: 6
# Explanation: 
# Delete 4 to earn 4 points, consequently 3 is also deleted.
# Then, delete 2 to earn 2 points. 6 total points are earned.
 

# Example 2:

# Input: nums = [2, 2, 3, 3, 3, 4]
# Output: 9
# Explanation: 
# Delete 3 to earn 3 points, deleting both 2's and the 4.
# Then, delete 3 again to earn 3 points, and 3 again to earn 3 points.
# 9 total points are earned.

class DeleteAndEarn:


# Algorithm

# For each unique value k of nums in increasing order, let's maintain the correct values of avoid and using, 
# which represent the answer if we don't take or take k respectively.

# If the new value k is adjacent to the previously largest value prev, 
# then the answer if we must take k is (the point value of k) + avoid, while the answer if we must not take k is max(avoid, using). 
# Similarly, if k is not adjacent to prev, the answer if we must take k is (the point value of k) + max(avoid, using), and the answer if we must not take k is max(avoid, using).

# At the end, the best answer may or may not use the largest value in nums, so we return max(avoid, using).

# Our demonstrated solutions showcase two different kinds of sorts: a library one, and a radix sort. 
# For each language, the other kind of solution can be done without much difficulty, by using an array (Python) or HashMap (Java) respectively.

# Complexity Analysis

# Time Complexity (Python): O(N \log N)O(NlogN), where NN is the length of nums. We make a single pass through the sorted keys of NN,
# and the complexity is dominated by the sorting step.
# Space Complexity (Python): O(N)O(N), the size of our count.
# Time Complexity (Java): We performed a radix sort instead, so our complexity is O(N+W)O(N+W) where WW is the range of allowable values for nums[i].
# Space Complexity (Java): O(W)O(W), the size of our count.
    # <DP>
    def doit(self, nums: 'List[int]') -> 'int':
        count = collections.Counter(nums)
        prev = None
        avoid = using = 0
        
        for k in sorted(count.keys()):
            
            if k - 1 != prev:
                avoid, using = max(using, avoid), k * count[k] + max(avoid, using)
            else:
                avoid, using = max(using, avoid), k * count[k] + avoid
                
            prev = k
            
        return max(avoid, using)
            

    def tls(self, nums: 'List[int]') -> 'int':
        
        data = {}
        for c in nums:
            data[c] = data.get(c, 0) + c
            
        keys = sorted(data.keys())
        buff = {}
        
        def search(keys) :
            
            if tuple(keys) in buff:
                return buff[tuple(keys)]
            
            ans = 0
            for i in range(len(keys)):

                s, e = i, i+1
                if i-1 >= 0 and keys[i-1] == keys[i] - 1:
                    s = i-1
                if i + 1 < len(keys) and keys[i+1] == keys[i] + 1:
                    e = i +2

                ans = max(ans, data[keys[i]] + search(keys[:s] + keys[e:]))

            buff[tuple(keys)] = ans    
            return ans
        
        return search(keys)