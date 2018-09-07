# 473. Matchsticks to Square

# Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has, 
# please find out a way you can make one square by using up all those matchsticks. 
# You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.

# Your input will be several matchsticks the girl has, represented with their stick length. 
# Your output will either be true or false, to represent whether you could make one square using all the matchsticks the little match girl has.

# Example 1:
# Input: [1,1,2,2,2]
# Output: true

# Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.

# Example 2:
# Input: [3,3,3,3,4]
# Output: false

# Explanation: You cannot find a way to form a square with all the matchsticks.

class Makesquare:
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        def stick(nums, i, target, buff):
            if i == len(nums):
                return True

            if (tuple(target), i) in buff:
                return False

            for j in range(4):
                if target[j] - nums[i]>= 0:

                    target[j] -= nums[i]
                    if stick(nums, i + 1, target, buff):
                        return True
                    target[j] += nums[i]

            buff.add((tuple(target), i))

            return False             
           
        if len(nums) < 4:
            return False
     
        if sum(nums) % 4 != 0:
            return False

        nums.sort(reverse = True)

        side = sum(nums) // 4
        target = [side] * 4
        current = 0

        return stick(nums, 0, target, set())



    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        def dfs(index, edge, count, used):
            
            for i in range(index, len(nums)):
                
                if i in used or edge < nums[i]:
                    continue
                    
                if edge - nums[i] > 0 and dfs(i+1, edge - nums[i], count, used | {i}):
                    return True
                
                if edge - nums[i] == 0 and (count and dfs(1, side, count - 1, used | {i})) or not count:
                    return True
                
            return False

        
        total = sum(nums)
        if len(nums) < 4 or total % 4 != 0:
            return False
        
        side = total // 4
        nums.sort(reverse = True)

        if nums[0] > side:
            return False
        
        return nums[0] == side and dfs(1, side, 1, {0}) or dfs(1, side - nums[0], 2, {0}) 



if __name__ == "__main__":

    res = Makesquare().doit([1,1,2,2,2])

    res = Makesquare().doit([3,3,3,3,4])

    res = Makesquare().doit([5,5,5,5,4,4,4,4,3,3,3,3])

    res = Makesquare().doit([5969561,8742425,2513572,3352059,9084275,2194427,1017540,2324577,6810719,8936380,7868365,2755770,9954463,9912280,4713511])

    res = Makesquare().doit([12,8,12,16,20,24,28,32,36,40,44,48,52,56,60])

    res = False
        
