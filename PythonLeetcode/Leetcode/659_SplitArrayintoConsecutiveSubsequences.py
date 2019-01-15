# 659. Split Array into Consecutive Subsequences

# You are given an integer array sorted in ascending order (may contain duplicates), 
# you need to split them into several subsequences, where each subsequences consist of at least 3 consecutive integers.
#  Return whether you can make such a split.

# Example 1:
# Input: [1,2,3,3,4,5]
# Output: True
# Explanation:
# You can split them into two consecutive subsequences : 
# 1, 2, 3
# 3, 4, 5

# Example 2:
# Input: [1,2,3,3,4,4,5,5]
# Output: True
# Explanation:
# You can split them into two consecutive subsequences : 
# 1, 2, 3, 4, 5
# 3, 4, 5
# Example 3:
# Input: [1,2,3,4,4,5]
# Output: False

import collections

class isPossible:


    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        left = collections.Counter(nums)
        end = collections.Counter()

        for num in nums:

            if left[num] == 0:
                continue

            left[num] -= 1

            if end[num-1] > 0:
                end[num - 1] -= 1
                end[num] += 1

            elif left[num+1] and left[num+2]:
                left[num+1] -= 1
                left[num+2] -= 1
                end[num+2] += 1

            else:
                return False
        
        return True


    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        cur = 0
        pre = float('inf')
        
        p1 = p2 = p3 = 0
        c1 = c2 = c3 = 0
        i = j = 0
        n = len(nums)
        
        cnt = 0
        
        while i<n:
            pre = cur
            p1, p2, p3 = c1, c2, c3
            cur = nums[i]
            cnt = 0
            
            while i<n and cur==nums[i]:
                i += 1
                cnt += 1
                        
            if cur!=pre+1:
                if p1!=0 or p2!=0:
                    return False
                c1, c2, c3 = cnt, 0, 0
            else:
                if cnt<p1+p2:
                    return False
                c3 = p2 + min(cnt-p1-p2,p3)
                c2 = p1
                c1 = max(cnt-p1-p2-p3,0)
        
        return (c1==0 and c2==0)


    # TLE:error 
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        buff, i = [], 0
        
        while i < len(nums):
            
            s = -1
            for j in range(len(buff)):
                if buff[j][-1] + 1 == nums[i]:
                    s = j
                    if len(buff[s]) < 3:
                        break
            if s == -1:
                buff.append([nums[i]])
            else:
                buff[s].append(nums[i])

            i += 1
        
        return all([len(s) > 2 for s in buff])