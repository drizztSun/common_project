# 810. Chalkboard XOR Game

# We are given non-negative integers nums[i] which are written on a chalkboard.  
# Alice and Bob take turns erasing exactly one number from the chalkboard, with Alice starting first.  
# If erasing a number causes the bitwise XOR of all the elements of the chalkboard to become 0, then that player loses.  
# (Also, we'll say the bitwise XOR of one element is that element itself, and the bitwise XOR of no elements is 0.)

# Also, if any player starts their turn with the bitwise XOR of all the elements of the chalkboard equal to 0, then that player wins.

# Return True if and only if Alice wins the game, assuming both players play optimally.

# Example:
# Input: nums = [1, 1, 2]
# Output: false
# Explanation: 
# Alice has two choices: erase 1 or erase 2. 
# If she erases 1, the nums array becomes [1, 2]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 2 = 3. 
# Now Bob can remove any element he wants, because Alice will be the one to erase the last element and she will lose. 
# If Alice erases 2 first, now nums becomes [1, 1]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 1 = 0. Alice will lose.

# Notes:

# 1 <= N <= 1000. 
# 0 <= nums[i] <= 2^16.

from functools import reduce
class XORGame:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        def dfs(shoot, arr, turns):
        
            if len(arr) == 1:
                return not turns

            if shoot == 0:
                return turns

            A = set(arr)
            for a in A:
                
                arr.remove(a)
                
                if not dfs(shoot^a, arr, not turns):
                    return False

                arr.append(a)

            return True


        snapshoot = reduce((lambda x, y: x ^ y), nums)

        return dfs(snapshoot, nums, True)


    # Game is very similar to classic Nim Game, so kind of expected solution to be similar -> problem already stated something about xor.

    # N is 1000 so 2^n, n! wont work here. Thinking of something like O(n) -> xor them all maybe?

    # DP probably won't work because the status is untractable, although order of removing number does not matter here.

    # Question states that if player erase a number and is left with xor( all nums) == 0 or zero num then lose.

    # The zero num means if Alice starts with an odd number of array she loses if no any combination of numbers is zero
    # If Alice erases a number and is left off with xor(all nums) = 0 then she loses. -> need to know the new xor!
    # for xor(all nums) = 0, it means some numbers are duplicates (in a form, as [1, 2, 3] is non duplicate, but can be thought of as [1, 1] in a sense)

    # I tried some examples, (really just [1,2,3,4]) and was pretty sure that Alice won't lose as long as she doesn't start with 4, and I thought if any of her move makes the rest of array full of duplicates, then she won't pick that number, and so won't Bob.

    # So any move leaving rest array dups will not happen, unless she started off with odd number of dups, which instatnly turns her to loss, and it happens to be an odd number..!

    # Then I came up with this piece of code:
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        N = len(nums)
        xor = reduce((lambda x, y: x^y), nums)

        return xor == 0 or N % 2 == 0

    #But checking around on discussion board shows obviously if Alice starts with all xor = 0 then she wins..

    #I also thought about sorting the array, removing some dups, but have no further information on how to proceed.

    #Honestly I prolly won't come up with better solutions given the thought process above in a real interview.. =. =


    # Should not be Hard problem
    # The solution can be only 3 lines and really simple.
    # It should be a medium problem.
    # Hard is kind of misleading.

    # Why [1, 2, 3] expect true
    # If xor == 0 at first for Alice, it is considered as Bob lose already!
    # I find this stupid idea just after contest and I think it has no reason.
    # It should complete this condition in the description!
    # Update: @awice confirmed that "It was supposed to be added to the problem description that 
    # having an initial XOR of 0 is a win."

    # Let's discuss it if we add this condition.
    # If xor == 0, Alice win directly.
    # If xor != 0 and length of numbers is even, Alice will win.

    # Beacause:
    # All numbers won't be the same. Otherwise xor will be equal to 0
    # If all numbers are not the same, It means there are at least 2 different numbers.
    # Alice can always erase a number different from current xor.
    # So Alice won't never lose this turn at this situation.

    # If we don't have the condition
    # Just return nums are not all 0 and length of nums is even
    def doit1(self, nums):
        xor = 0
        for c in nums:
            xor ^= c

        return xor == 0 or len(nums) % 2 == 0
        


if __name__ == "__main__":

    res = XORGame().doit([1, 1, 2])

    res = XORGame().doit([0, 0, 0, 1])

    pass
