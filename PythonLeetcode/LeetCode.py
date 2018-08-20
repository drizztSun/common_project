#/user/bin/env Python

import os
import sys
import pdb
import logging
import types

import decimal
import random
import cmath
import array
import operator

import math

import collections

from operator import add, mul
from functools import partial

# Leetcode 1 two sum
class twoSum(object):
    def doit(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        result = []
        i = 0
        while i < len(nums) :
            j = 0
            while  j < len(nums) :
                if nums[i] + nums[j] == target and j != i:
                    if i not in result:
                        result.append(i)
                    if j not in result:
                        result.append(j)
                j += 1
                    
            i += 1;
        
        return result 

    # O(n)
    def doit2(self, nums, target):
        mapArr, i = dict(), 0
        while i < len(nums):
            remainder = target - nums[i]
            if mapArr.has_key(remainder) :
                return [i, mapArr[remainder]]

            mapArr[nums[i]] = i
            i += 1

        return []

    def doit3(self, nums, target):
        res, start, end = [], 0, len(nums) - 1
        mapArr = {}
        while start <= end:
            mapArr[nums[start]] = start
            start += 1

        start = 0
        while start < end:
            sum = nums[start] + nums[end]
            if sum == target:
                res.append(start)
                res.append(end)
                break
            elif sum > target:
                end -= 1
            else:
                start += 1
        return res 
        
# leetcode 15. 3Sum
class threeSum(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        res, i, numsDict = [], 0, {}

        nums.sort()
        i = 0
        while i < len(nums) - 2:
            target = 0 - nums[i]
            
            start, end  = i + 1, len(nums) - 1
            while start < end:
                sum = nums[start] + nums[end]
                if sum == target:
                    res.append([nums[i], nums[start], nums[end]])
                    
                    st = nums[start]
                    while start < end and nums[start] == st:
                        start += 1

                    ed = nums[end]
                    while start < end and nums[end] == ed:
                        end -= 1

                elif sum > target:
                    end  -= 1
                else :
                    start += 1

            while i + 1 < len(nums) and nums[i] == nums[i+1]:
                i += 1

            i += 1

        return res

    def doit2(self, nums):
        res = []
        nums.sort()
        for i in xrange(len(nums)-2):
            if i > 0 and nums[i] == nums[i-1]:
                continue
            l, r = i+1, len(nums)-1
            while l < r:
                s = nums[i] + nums[l] + nums[r]
                if s < 0:
                   l += 1
                if s > 0:
                    r -= 1
                else:
                    res.append([nums[i], nums[l], nums[r]])
                    while l < r and nums[l] == nums[l + 1]:
                        l += 1
                    while l < r and nums[r] == nums[r - 1]:
                        r += 1
                    l += 1; r += 1
        return res

# leetcode 18. 4Sum
class fourSum(object):
    def doit(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        i, length, result = 0, len(nums), []
        nums.sort()

        while i < length - 2:

            j = i + 1
            while j < length - 2:

                start, end = j + 1, length - 1

                while start < end:
                    sum = nums[i] + nums[j] + nums[start] + nums[end]
                    if sum > target:
                        while start < end and nums[end] == nums[end - 1]:
                            end -= 1
                        end -= 1
                    elif sum < target:
                        while start < end and nums[start + 1] == nums[start]:
                            start += 1
                        start += 1
                    else:
                        result.append([nums[i], nums[j], nums[start], nums[end]])
                        
                        while start < end and nums[start + 1] == nums[start]:
                            start += 1
                        
                        while start < end and nums[end] == nums[end - 1]:
                            end -= 1

                        start += 1; end-=1

                while j < length - 2 and nums[j] == nums[j + 1]:
                    j += 1
                j += 1

            while i < length - 2 and nums[i] == nums[i + 1]:
                i += 1
            i += 1
    
        return result 

    def doit2(self, nums, target):        
        def findNsum(nums, target, N, result, results):
            if len(nums) < N or N < 2 or target < nums[0]*N or target > nums[-1]*N:  # early termination
                return
            if N == 2: # two pointers solve sorted 2-sum problem
                l,r = 0,len(nums)-1
                while l < r:
                    s = nums[l] + nums[r]
                    if s == target:
                        results.append(result + [nums[l], nums[r]])
                        l += 1
                        while l < r and nums[l] == nums[l-1]:
                            l += 1
                    elif s < target:
                        l += 1
                    else:
                        r -= 1
            else: # recursively reduce N
                for i in range(len(nums)-N+1):
                    if i == 0 or (i > 0 and nums[i-1] != nums[i]):
                        findNsum(nums[i+1:], target-nums[i], N-1, result+[nums[i]], results)
    
        results = []
        findNsum(sorted(nums), target, 4, [], results)
        return results       

# Leetcode 16. 3Sum Closest
class threeSumClosest(object):
    def doit2(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        closestValue = 10000
        nums.sort()
        def findClosestNumber(num, target, N, res):
            if len(num) < N:
                return

            if N == 0:
                if abs(closestValue - target) > abs(res - target):
                    closestValue = res
                return

            i = 0
            while i < len(num):
                if i == 0 or (i > 0 and num[i - 1] != num[i]):
                    findClosestNumber(nums[i+1:], target, N - 1, res + num[i])
                i += 1

        findClosestNumber(nums, target, 3, res)
        return closestValue

    def doit(self, nums, target):
        i, length, closestValue = 0, len(nums), 10000
        nums.sort()
        while i < length - 2:
            
            start, end = i + 1, length - 1
            while start < end:
                sum = nums[i] + nums[start] + nums[end]
                if abs(closestValue - target) > abs(sum - target) :
                    closestValue = sum
                
                if sum == target:
                    return target
                elif sum > target:
                    end -= 1
                else:
                    start += 1
           
            while i < length -2 and nums[i] == nums[i + 1]:
                i += 1
            i += 1

        return closestValue
            

# Leetcode 454. 4Sum II
class fourSumCount(object):
    def doit(self, A, B, C, D):
        """
        :type A: List[int]
        :type B: List[int]
        :type C: List[int]
        :type D: List[int]
        :rtype: int
        """



# leetcode 2 AddTwoNumber
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

class addTwoNumbers(object):

    @staticmethod
    def doit(l1, l2):        
        result = ListNode(0)
        v = result
        accum = 0

        while True :            
            num = 0
            if l1 != None :
                num += l1.val
                l1 = l1.next
            
            if l2 != None :
                num += l2.val
                l2 = l2.next

            num += accum
            accum = 0            

            if num >= 10 :
                num -= 10
                accum = 1

            v.next = ListNode(num)
            v = v.next

            if l1 is None and l2 is None and accum == 0:
                break

        v = result
        result = result.next
        v.next = None
 
        return result

# Leetcode 3. Longest Substring Without Repeating Characters
class lengthOfLongestSubstring(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        return self.way3(s)

    def way3(self, s):
        start = maxLength = 0
        usedChar = {}
        min, max = 0, 0
        
        for i in range(len(s)):
            if s[i] in usedChar and start <= usedChar[s[i]]:
                start = usedChar[s[i]] + 1
            else:
                if i - start + 1 > maxLength: 
                    maxLength = i - start + 1
                    min = start
                    max = i

            usedChar[s[i]] = i

        return s[min : max + 1]
 
    def way2(self, s):
        w, i = len(s), 0
        if w == 0: 
            return 0
        
        Matrix = [0 for x in range(w)]
        while i < w:
            Matrix[i] = 1
            i += 1    
 
        d = 1
        max, imax, imin = 1, 0, 0

        while d < w:
            i, done = 0, True
            while i < w and i + d < w:
              if Matrix[i]> 0 :
                a, f = 0, s[i + d]
                
                while a + i < i + d and s[a + i] != f:
                    a += 1
 
                if a + i == i + d:
                    Matrix[i] +=  1
                    if Matrix[i] > max:
                        max = Matrix[i]
                        imax = i + d
                        imin = i
                        done = False
                else :
                    Matrix[i] = 0
              i += 1
            if done:
                break
            d += 1

        return s[imin : imax + 1]            
        
    # it seems 2D array to be so hard to create
    def way1(self, s):
        w, i = len(s), 0
        if w == 0: return 0

        Matrix = [[0 for x in range(w)] for y in range(w)]
        while i < w:
            Matrix[i][i] = 1
            i += 1    
    
        d = 1
        max, imax, imin = 1, 0, 0

        while d < w:
            i, done = 0, True
            while i < w and i + d < w:
              if Matrix[i][i + d - 1] > 0 :
                a, f = 0, s[i + d]
                
                while a + i < i + d and s[a + i] != f:
                    a += 1
 
                if a + i == i + d:
                    Matrix[i][i + d] = Matrix[i][i + d - 1] + 1
                    if Matrix[i][i + d] > max:
                        max = Matrix[i][i + d]
                        imax = i + d
                        imin = i
                        done = False
                else :
                    Matrix[i][i + d] = 0
              i += 1
            if done:
                break
            d += 1

        return s[imin : imax + 1]


#  Leetcode 8 atoi 
class myAtoi(object):
    @staticmethod
    def doit(str):
        """
        :type str: str
        :rtype: int
        """
        i = 0 
        sign = 1
        while i < len(str) and str[i] == ' ' :
            i += 1
        if i == len(str) :
            return 0
        
        if str[i] == '-' or str[i] == '+':
            sign = 1 - 2 * (str[i] == '-') 
            i += 1
        
        base = 0
        while i < len(str) and str[i] >= '0' and str[i] <= '9' :
            num = int(str[i]) - int('0')
            if base > sys.maxint / 10 or base == sys.maxint / 10 and num > 7:
                if sign == 1 :
                    return sys.maxint
                else :
                    return -sys.maxint - 1
            base = num + base * 10
            i += 1

        base = sign * base
        
        return base
      
      
        
# LeetCode 4 Median of two sorted array
class findMedianSortedArrays(object):
    @staticmethod
    def doit(nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        n, m = len(nums1), len(nums2)
        if n > m :
            n, m, nums1, nums2 = m, n, nums2, nums1
        
        if n == 0:
            raise ValueError

        imin, imax, half_len = 0, n, (m + n + 1) /2 
        
        while imin <= imax :
            i = (imin + imax) / 2
            j = half_len - i

            if i < n and nums1[i] < nums2[j - 1] :
                # i is too small
                imin = i + 1

            elif i > 0 and nums1[i - 1] > nums2[j] :
                # i is too big
                imax = i - 1

            else :
                # i is perfect
                if i == 0 : 
                    max_of_left = nums2[j - 1]

                elif j == 0 :
                    max_of_left = nums1[i - 1]

                else :
                    max_of_left = max(nums1[i -1], nums2[j - 1])
            
                if (m + n) % 2 == 1 :
                    return max_of_left

                if i == n :
                    min_of_right = nums2[j]

                elif j == m :
                    min_of_right = nums1[i]

                else :
                    min_of_right = min(nums1[i], nums2[j])

                return (max_of_left + min_of_right) / 2.0
                                      
# Leetcode 22. Generate Parentheses
class generateParenthesis(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        collect, str, max = [], '', 0 
        self.recur(collect, str, n, n, max)
        return collect


    def correctAnswer(self, str):
        max, i, length = 0, 0, len(str)
        while max >= 0 and i < length:
            if str[i] == '(':
                max += 1
            else:
                max -= 1

            i += 1
        
        return i == length and max == 0

    def recur(self, collect, str, a, b, max):

        if max < 0:
            return False
        
        if a == 0 and b == 0 and self.correctAnswer(str) :
            collect.append(str)
            return True
        
        if a > 0:
            str += '('
            self.recur(collect, str, a - 1, b, max + 1)
            str = str[0 : len(str) - 1]

        if b > 0:
            str += ')'
            self.recur(collect, str, a, b - 1, max - 1)   
            str = str[0 : len(str) - 1]
        


    def way1(self, n):
        a, b, max, col, result = n, -n, 0, [], []
        max, a = 1, a - 1
        col.append('(')
        
        while True:
            
            if a > 0:
                a -= 1
                max += 1
                col.append('(')
            elif b > 0:
                b += 1
                max -= 1
                col.append(')')

            if a == 0 and b == 0 and max == 0:
                result.append(col[:])
                

# Leetcode 25. Reverse Nodes in k-Group
class reverseKGroup(object):
    def doit(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        result, Fir = ListNode(1000), head
        tail = result

        while Fir != None:
    
            i, pt = 0, Fir
            while i < k and pt != None:
                pt = pt.next
                i += 1

            if i == k:
                i, pt = 0, Fir
                while i < k:
                    b = tail.next
                    c = pt.next
                    tail.next = pt
                    pt.next = b
                    pt = c                                        
                    i += 1
                tail = Fir
            else:
                tail.next = Fir

            Fir = pt
            
        result = result.next
        return result



class rotate(object):
    def doit(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """
        n = len(matrix)
        mid, rem, odd = n / 2, n % 2, False
            
        i = 0
        while i < mid:
            j = 0
            x, y = i, i
            x1, y1 = n - i - 1, n - (i + j) - 1
            end = n - i - 1 - i
            while j < end:
                a = matrix[x][y + j]
                matrix[x][y + j] = matrix[x1 - j][y]
                matrix[x1 - j][y] = matrix[x1][y1 - j]
                matrix[x1][y1 - j] = matrix[x + j][y1]
                matrix[x + j][y1] = a
                j += 1
            i += 1
           
            
        
# Leetcode 27 Remove Element
class removeElement(object):
    @staticmethod
    def doit(nums, val):
        """
        :type nums: List[int]
        :type val: int
        :rtype: int
        """    
        i, j = len(nums) - 1, len(nums) - 1
        while i >= 0:
            if nums[i] == val:
                nums[i] = nums[j]
                nums[j] = val
                j -= 1
            i -= 1
        
        return  j + 1

# Leetcode 29. Divide Two Integers
class divide(object):
    def doit(self, dividend, divisor):
        """
        :type dividend: int
        :type divisor: int
        :rtype: int
        """     
        positive = (dividend < 0) is (divisor < 0)
        dividend, divisor = abs(dividend), abs(divisor)
        res = 0
        while dividend >= divisor:
            i, temp = 1, divisor  
            while dividend >= temp:
                dividend -= temp
                res += i
                i <<= 1
                temp <<= 1

        if not positive:
            res = -res

        return min(max(-2147483648, res), 2147483647)


# Leetcode 35. Search Insert Position
class searchInsert(object):
    def doit(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        res, start, end, mid = 0, 0, len(nums), len(nums)/2

        while start < end:
            if nums[mid] < target:
                start = mid + 1
                res = start
            elif nums[mid] > target:
                end = mid
                res = end
            else :
                res = mid
                break

            mid = (start + end) / 2

        return res


# Leetcode 283 Move Zeroes
class moveZeroes(object):
    @staticmethod
    def doit(nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        i, j, listlen = 0, 0, len(nums) 
        while i < listlen:
            if nums[i] == 0 :
                while j < listlen and nums[j] == 0 :
                    j += 1  

                if j == listlen :
                    break
                else :                
                   nums[i] = nums[j]
                   nums[j] = 0
            i += 1
            j += 1

        return nums
            
# Leetcode 7 Reverse Integer
class reverse(object):
    @staticmethod
    def doit(x):
        """
        :type x: int
        :rtype: int
        """
        base, sign = 0, 1
        if x < 0 :
            sign = -1
            x = x * sign

        while x > 0 :
            num = x % 10
            if base > sys.maxint / 10 or base == sys.maxint / 10 and num > 7 :
                return 0
            base = base * 10 + num
            x = x / 10
        
        return sign * base
            
# Leetcode 21 Merge Two Sorted Lists
# Definition for singly-linked list.
class ListNode(object):
     def __init__(self, x):
         self.val = x
         self.next = None

class mergeTwoLists(object):
    @staticmethod
    def doit(l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        result = ListNode(0)
        iter = result

        while l1 != None or l2 != None:
            val = 0
            if l1 != None and l2 != None:
                if l1.val < l2.val :
                    val = l1.val
                    l1 = l1.next
                else :
                    val = l2.val
                    l2 = l2.next
            elif l1 == None :
                val = l2.val
                l2 = l2.next
            elif l2 == None:
                val = l1.val
                l1 = l1.next
                    
            iter.next = ListNode(val)
            iter = iter.next               
        
        result = result.next        

        return result             

# Leetcode 23. Merge k Sorted Lists
class mergeKLists(object):
    @staticmethod
    def doit(lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        size, result, done = len(lists), [], False
        while not done :
            val, e, done = -sys.maxint, None, True
            for e in lists:
                if e == None :
                    continue
                
                val = min(val, e.val)
                done = False
                e = e.next
                
            if not done:
                result.append(val)

        return result
    
    @staticmethod
    def doit1(lists):
        index, i, sum, num = [0] * len(lists), 0, 0, 0
        result, v = ListNode(0), result
                
        for e in lists:
            sum += len(e)
        
        while i < sum :
            num, min, pos = 0, sys.maxint, 0
            while num < len(lists) :
                if index[num] < len(lists[num]) and min > lists[num][index[num]]:
                    min = lists[num][index[num]]
                    pos = num       
                num += 1
            index[pos] += 1

            result.next = ListNode(min)
            result = result.next
            i += 1

        return v.next


# Leetcode 88 Merge Sorted Array
class mergeSortedArray(object):
    @staticmethod
    def doit(nums1, m, nums2, n):
        """
        :type nums1: List[int]
        :type m: int
        :type nums2: List[int]
        :type n: int
        :rtype: void Do not return anything, modify nums1 in-place instead.
        """
        #nums1.extend(nums2)
        s1, s2, e1 = m - 1, n - 1, m - 1
        
        while s1 >= 0 or s2 >= 0 :
            val = 0
            if s1 >= 0 and s2 >= 0:
                if nums1[s1] > nums2[s2]:
                    val = nums1[s1]
                    s1 -= 1
                else :
                    val = nums2[s2]
                    s2 -= 1
            elif s1 < 0 :
                    val = nums2[s2]
                    s2 -= 1
            elif s2 < 0 :               
                    val = nums1[s1]
                    s1 -= 1
            else :
                raise ValueError
            
            nums1[e1] = val
            e1 -= 1
            

# Leetcode 32. Longest Valid Parentheses
class longestValidParentheses(object):
    @staticmethod
    def doit(str):
        """
        :type s: str
        :rtype: int
        """
        s, e = 0, len(str) - 1
        while s < len(str) and str[s] == ')' :
            s += 1 
        
        while e >= 0 and str[e] == '(' :
            e -= 1

        if e < s :
            return 0
    
        i, pos, max_len, maxS, maxE = s + 1, 1, 0, 0, 0
        stack = []
        stack.append(s)
        while i <= e:
            if str[i] == '(':
                stack.append(i)
                pos += 1
            else :
                if pos > 0 and str[stack[pos - 1]] == '(':
                    stack.pop()
                    pos -= 1
                else :
                    stack.append(i)
                    pos += 1
            i += 1
        #
        longest, b = -1, e + 1
        if len(stack) == 0 :
            longest = e - s + 1
        else :
            while len(stack) != 0:
                a = stack.pop()
                longest = max(longest, b - a -1)
                b = a
            longest = max(longest, a - s)
        return  longest 

# Leetcode 24. Swap Nodes in Pairs
class swapPairs(object):
    @staticmethod
    def doit(head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        result, done, V1, V2 = ListNode(0), False, head, None

        while not done :
            if V1 == None:
                done = True
                continue
            else :
                V2 = V1.next
                
            



# Leetcode 26. Remove Duplicates from Sorted Array
class removeDuplicates(object):
    @staticmethod
    def doit(nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) < 2:
            return

        current, removablePos, removalNum = 1, 1, nums[0]
        while current < len(nums) :
            if nums[current] != removalNum :
                removalNum = nums[current]
                nums[removablePos] = nums[current]
                removablePos += 1
            current += 1

        del nums[removablePos:]


# Leetcode 33. Search in Rotated Sorted Array
class search(object):
    @staticmethod
    def doit(nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        min, max = 0, len(nums) - 1
        while min < max:
            mid = (max + min) / 2
            if nums[mid] > nums[max] :
                min = mid + 1
            else :
                max = mid
        #
        low, high, n, delta = 0, len(nums) - 1, len(nums), max
        while low <= high:
            med = (low + high) / 2
            realmid = (med + delta) % n
            if nums[realmid] == target :
                return realmid
            elif nums[realmid] > target:
                high = med - 1
            else :
                low = med + 1
                
        return -1

# Leetcode 44. Wildcard Matching (Hard)
class isMatch(object):
    
    @staticmethod
    def resolve(s, p):
        #return isMatch.doit3(s, p) > 1
        #return isMatch.doit4(s, p, 0, 0) > 1
        #return isMatch.doit2(s, p)
        return isMatch.doitDP2(s, p)

    @staticmethod
    def doit(s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        if s is "" and p == '':
            return True

        if p is "":
            return False

        done = False
        if p[0] == '*' :
            i, length = 0, len(s)
            while i <= length and not done:
                done = isMatch.doit(s[i:], p[1:])
                i += 1
        elif p[0] == '?' and s != '':
            done = isMatch.doit(s[1:], p[1:])
        elif p[0] != '?' and p[0] != '*':
            if s != '' and p[0] == s[0] :
                done = isMatch.doit(s[1:], p[1:])
            else :
                return False

        return done

    @staticmethod 
    def doit4(s, p, si, pi):
        if si == len(s) and pi == len(p) : return 2
        if si == len(s) and p[pi] != '*': return 0
        if pi == len(p) : return 1

        done = 1
        if p[pi] == '*':
            if pi + 1 < len(p) and p[pi + 1] == '*':
                return isMatch.doit4(s, p, si, pi + 1)
        
            i = 0
            while i <= len(s) - si:
                done = isMatch.doit4(s, p, si + i, pi + 1)
                if done == 2 or done == 0:
                    return done
                i += 1

        if p[pi] == '?' or s[si] == p[pi]:
            return isMatch.doit4(s, p, si+1, pi+1)

        return 1

    @staticmethod
    def doit3(s, p):
        # 0: reach the end of s but unmatched
        # 1: unmatched without reaching the end of s
        # 2: matched
        if len(s) == 0 and len(p) == 0: return 2
        if len(s) == 0 and p[0] != '*': return 0
        if len(p) == 0 : return 1

        done = 1
        # *
        if p[0] == '*':
            #skip duplicate *
            if len(p) > 1 and p[1] == '*' :
               return isMatch.doit3(s, p[1:])
            # use * to match 0 - n charactor
            i = 0
            while i <= len(s):
                done = isMatch.doit3(s[i:], p[1:])
                if done == 2 or done == 0:
                    return done
                i += 1

        # ? and Alphabelta
        if p[0] == '?' or s[0] == p[0] :
            done = isMatch.doit3(s[1:], p[1:])
    
        return done

    @staticmethod
    def doitDP2(s, p):
        m = len(s)
        n = len(p)

        if n == 0 and m == 0:
            return True
        if n == 0 and m != 0:
            return False
        if p.count('*') == len(p):
            return True            
        if len(p) - p.count('*') > m:
            return False

        dp = [True] + [False]*m
        for cp in p:
            if cp != '*':
                for i in xrange(m, 0, -1): # m, m-1, .. 1
                    dp[i] = dp[i-1] and (cp=='?' or s[i-1] == cp)
            else:
                for i in xrange(1, m+1):
                    dp[i] = dp[i] or dp[i-1]
            dp[0] = dp[0] and cp=='*'
    
        return dp[m]

    @staticmethod
    # DP
    def doitDP(s, p):
        length = len(s)
        if len(p) - p.count('*') > length:
            return False
        dp = [True] + [False]*length
        for i in p:
            if i != '*':
                for n in reversed(range(length)):
                    dp[n+1] = dp[n] and (i == s[n] or i == '?')
            else:
                for n in range(1, length+1):
                    dp[n] = dp[n-1] or dp[n]
            dp[0] = dp[0] and i == '*'
        return dp[-1]

    @staticmethod
    # non-recursion way
    def doit2(s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        s_cur, p_cur, match, sStar, pStar = 0, 0, 0, -1, -1
        while s_cur < len(s) and p_cur < len(p):
            
            if p[p_cur] == '*':
                sStar = s_cur
                pStar = p_cur
                sStar -= 1

            else:
                if  s[s_cur] != p[p_cur] and p[p_cur] != '?':
                    if sStar >= 0:
                        sStar += 1   
                        s_cur = sStar
                        p_cur = pStar
                    else :
                       return False
 
            s_cur += 1
            p_cur += 1

        while p_cur < len(p) and p[p_cur] == '*':
            p_cur += 1               
        
        return p_cur == len(p) and s_cur == len(s)       

# Leetcode 31 Next Permutation
class nextPermutation(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        pass
        
# Leetcode 34. Search for a Range        
class searchRange(object):
    def doit(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        i, length, start, end = 0, len(nums), -1, -1
    
        while i < length:
            
            if nums[i] == target:
                if start == -1:
                    start = i
                    end = i
                else:
                    end = i
            i += 1
                
        return [start, end]
        
        
# Leetcoe 46. Permutations
class permute(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        return self.recursiveWay(nums)

    def recursiveWay(self, nums):
        # define inner
        result = []
        def innerlogic(r, c, n):
            if n == 0:
                result.append(c[:])
                return
            
            i = 0
            n -= 1
            while i < len(r):
                c.append(r[i])
                b = r[0:i] + r[i+1:]
                innerlogic(b, c, n)
                c.pop()
                i += 1
         
        
        c = []
        length = len(nums)
        innerlogic(nums, c, length)
        return result

        
# Leetcode 47. Permutations II
class permuteUnique(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        return self.recurWay(nums)
     
    def recurWay(self, nums):
        
        def innerfunc(nums, i, j, res):
            if i == j - 1:
                res.append(nums)
                return
        
            k = i
            while k < j:
                if i != k and nums[i] == nums[k]:
                    k += 1
                    continue
                a = nums[i]
                nums[i] = nums[k]
                nums[k] = a
                
                innerfunc(nums[:], i + 1, j, res)
                k += 1
                   
        nums.sort()
        res = []
        innerfunc(nums[:], 0, len(nums), res)
        return res   

    #return self.recursiveWay(nums)
    def recursiveWay(self, nums):
        # define inner
        nums.sort()
        result = []
        def innerlogic(r, c, n):
            if n == 0:
                result.append(c[:])
                return
            
            i, k = 0, 0
            n -= 1
            while i < len(r) and k < len(r):
                if i != k and r[i] == r[k]:
                    continue
                i = k
                c.append(r[i])
                b = r[0:i] + r[i+1:]
                innerlogic(b, c, n)
                c.pop()
                k += 1
                i += 1
        
        c = []
        length = len(nums)
        innerlogic(nums, c, length)
        return result          

# Leetcode 54. Spiral Matrix
class spiralOrder(object):
    def doit(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        m = len(matrix)
        if m == 0:
            return []
            
        result, n = [], len(matrix[0])
        rowBen, rowEnd, colBen, colEnd = 0, m-1, 0, n-1

        while rowBen <= rowEnd and colBen <= colEnd:
            j = colBen
            while j <= colEnd:
                result.append(matrix[rowBen][j])
                j += 1    
            rowBen += 1

            i = rowBen
            while i <= rowEnd:
                result.append(matrix[i][colEnd])
                i += 1
            colEnd -= 1

            if rowBen <= rowEnd :
                j = colEnd
                while j >= colBen:
                    result.append(matrix[rowEnd][j])
                    j -= 1
                rowEnd -= 1
            
            if colBen <= colEnd:
                i = rowEnd
                while i >= rowBen:
                    result.append(matrix[i][colBen])
                    i -= 1
                colBen += 1

        return result

# Leetcode 45. Jump Game II
class jump(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) < 2:
            return 0
        i, currentMax, nextMax, level = 0, 0, 0, 0
        while currentMax - i + 1 > 0:
            level += 1
            while i <= currentMax:
                nextMax = max(nextMax, nums[i] + i)
                if nextMax >= len(nums) - 1:
                    return level
                i += 1
            currentMax = nextMax
        return level
            

    #return self.recurrenceWay(nums)
    def recurrenceWay(self, nums):
        self.minVal = sys.maxint
        def iter(nums, cur, buf):
            if cur >= len(nums) - 1:
                if len(buf) < self.minVal:
                    self.minVal = len(buf)
                return
            if len(buf) > self.minVal:
                return

            jumpStep = nums[cur]
            buf.append(cur)
            while jumpStep > 0:
                iter(nums, cur + jumpStep, buf)
                jumpStep -= 1
            buf.pop()
        
        iter(nums, 0, [])

        return min(len(nums) - 1, self.minVal)
                 
# Leetcode 55. Jump Game        
class canJump(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        i, reach, n = 0, 0, len(nums)
        while i < n and i <= reach:
            reach = max(i + nums[i], reach)
            i += 1
        return i >= n
            

            
        
# Leetcode 58. Length of Last Word
class lengthOfLastWord(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        length, i = 0, 0
        
        while i < len(s):
            if s[i] != ' ':
                length += 1
            elif i + 1 < len(s) and s[i + 1] != ' ':
                length = 0
            
            i += 1
            
        return length


# Leetcode 57. Insert Interval
class insert(object):
    def doit(self, intervals, newInterval):
        """
        :type intervals: List[Interval]
        :type newInterval: Interval
        :rtype: List[Interval]
        """
        

# Leetcode 59. Spiral Matrix II
class generateMatrix(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: List[List[int]]
        """
        matrix = [[0 for x in range(n)] for y in range(n)]
        num, end = 1, n*n
        rowBen, rowEnd, colBen, colEnd = 0, n-1, 0, n-1 

        while num <= end and rowBen <= rowEnd and colBen <= colEnd:
            
            i = colBen
            while i <= colEnd:
                matrix[rowBen][i] = num
                num += 1                     
                i += 1
            rowBen += 1

            j = rowBen
            while j <= rowEnd:
                matrix[j][colEnd] = num
                num += 1
                j += 1
            colEnd -= 1

            if colBen <= colEnd:
                i = colEnd
                while i >= colBen:
                    matrix[rowEnd][i] = num 
                    num += 1
                    i -= 1
                rowEnd -= 1

            if rowBen <= rowEnd:
                j = rowEnd
                while j >= rowBen:
                    matrix[j][colBen] = num
                    num += 1
                    j -= 1
                colBen += 1

        
        return matrix
        
        
# 64. Minimum Path Sum
#Given a m x n grid filled with non-negative numbers, find a path from top 
#left to bottom right which minimizes the sum of all numbers along its path.            
class minPathSum(object):
    def doit(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        if not grid or not len(grid) or not len(grid[0]): 
            return 0
        
        if len(grid) == 1 or len(grid[0]) == 1:
            return grid[0][0]
        
        m, n = len(grid), len(grid[0])
        D = [[0 for x in range(n)] for y in range(m)]

        i, j, D[0][0] = 1, 1, grid[0][0]
        while i < m:
            D[i][0] = D[i-1][0] + grid[i][0]
            i += 1
        while j < n:
            D[0][j] = D[0][j-1] + grid[0][j]
            j += 1

        i, j = 1, 1
        while i < m:
            j = 1
            while j < n:
                D[i][j] = min(D[i-1][j], D[i][j-1]) + grid[i][j]
                j += 1
            i+= 1
        
        return D[m-1][n-1]

    # in-place method
    def doit2(self, grid):
        m = len(grid)
        if m == 0:
            return 0
        n = len(grid[0])
        
        for i in range(1,n):
            grid[0][i] += grid[0][i-1]
            
        for i in range(1, m):
            grid[i][0] += grid[i-1][0]
        
        for i in range(1, m):
            for j in range(1, n):
                grid[i][j] += min(grid[i-1][j], grid[i][j-1])
        
        return grid[-1][-1]

# 78. Subsets
# Given a set of distinct integers, nums, return all possible subsets.
class subsets(object):
   
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        def dfs(nums, index, path, res):
            res.append(path)
            for i in xrange(index, len(nums)):
                dfs(nums, i+1, path+[nums[i]], res)
        
        rv = []
        dfs(nums, 0, [], rv)
        return rv

    def doit1(self, nums):
        res = [[]]
        for num in sorted(nums):
            res += [items + [num] for items in res]
        return res
                
# 90. Subsets II
# Given a collection of integers that might contain duplicates, nums, return all possible subsets.        
class subsetsWithDup(object):
    def doit1(self, nums):
        """
        :type: nums: List[int]
        :rtype: List[List[int]]
        """
        def dfs(nums, index, path, rv):
            rv.append(path)
            last = None
            for i in xrange(index, len(nums)):
                if last != nums[i]:
                    dfs(nums, i+1, path+[nums[i]], rv)
                last = nums[i]

        rv = []    
        dfs(sorted(nums), 0, [], rv)
        return rv

    def doit2(self, nums):
        """
        :type: nums: List[int]
        :rtype: List[List[int]]
        """
        res = []
        nums.sort()
        res.append([])
        begin = 0
        for i in range(len(nums)):
            if i == 0 or nums[i] != nums[i-1]:
                begin = len(res)
            size = len(res)
            # print "from size - begin:",(size - begin)," to size:",size
            for j in range(size - begin, size):
                # cur = res[j]
                # cur.append(nums[i])
                # print "cur:", cur, " nums[i]",nums[i]
                res.append(res[j] + [nums[i]])
        return res


    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        res, last, temp = [[]], None, [[]]
        for num in sorted(nums):
            if num == last :
                temp = [[num] + target for target in temp]
            else :
                temp = [[num] + target for target in res]

            res += temp
            last = num
        return res
            
        
# Leetcode 81. Search in Rotated Sorted Array II
# duplicates are allowed
class searchII(object):
    @staticmethod
    def doit(nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: bool
        """
        lo, hi = 0, len(nums) - 1
        while lo < hi :
            mid = (lo + hi) / 2
            if nums[mid] == target:
                return True
            
            if nums[mid] > nums[hi] :
                if target >= nums[lo] and target < nums[mid] :
                    hi = mid
                else :
                    lo = mid + 1
            elif nums[mid] < nums[hi] :
                if target > nums[mid] and target <= nums[hi] :
                    lo = mid + 1
                else :
                    hi = mid
            else :
                hi -= 1

        return lo < len(nums) and nums[lo] == target
                
                 
                
    @staticmethod
    def doit2(nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: bool
        """
        i, max, pos = 0, -sys.maxint, -1
        while i < len(nums):
            if max <= nums[i] :
                max = nums[i]
                pos = i

            if max > nums[i]:
                break
            i += 1

        #
        low, high, n = 0, len(nums) - 1, len(nums)
        delta = n - pos -1
        while low <= high:
            med = (low + high) / 2
            realmid = med - delta
            if realmid < 0:
                realmid += n
            if nums[realmid] == target :
                return True
            elif nums[realmid] > target:
                high = med - 1
            else :
                low = med + 1
                
        return False

# Leetcode 70. Climbing Stairs
class climbStairs(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        step = [0 for x in range(n + 1)]
        step[0] = 1
        step[1] = 1
        
        i = 2
        while i <= n:
            step[i] = step[i - 1] + step[i - 2]
            i += 1
            
        return step[n]


# Leetcode 11. Container With Most Water
class maxArea(object):
    def doit(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        start, end, maxValue = 0, len(height)-1, 0
        while start < end:
            val = (end - start) * min(height[end], height[start])
            maxValue = max(val, maxValue)

            if height[start] > height[end]:
                end += 1
            else:
                start += 1

        return maxValue 


# 215. Kth Largest Element in an Array
class findKthLargest(object):
    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        A, B, k = nums[0], 0, k - 1
        min, max = 0, len(nums)
        while True:
            A, i, j = nums[min], min, min
            while i < max:
                if nums[i] > A:
                    j += 1
                    a = nums[j]
                    nums[j] = nums[i]
                    nums[i] = a
                i += 1
            
            if j != min :
                a = nums[j]
                nums[j] = nums[min]
                nums[min] = a 
            
            if k == j:
                B = nums[k]
                break
            elif k > j :
                min = j + 1
            else:
                max = j

        return B   


# Leetcode 278. First Bad Version
class firstBadVersion(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        start, end, mid = 1, n, n/2
        
        while start + 1 < end:
            while not self.isBadVersion(mid) and start + 1 < end:
                start = mid
                mid = (start + end) / 2


            while self.isBadVersion(mid) and start + 1 < end:
                end = mid
                mid = (start + end) / 2

        res = end
        if self.isBadVersion(start):
            res = start

        return res

    def isBadVersion(self, version):
        return version >= 1

# Leetcode 414. Third Maximum Number
class thirdMax(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) == 1:
            return nums[0]
        
        M, i, jmin = [-sys.maxint, -sys.maxint, -sys.maxint], 0, 0
        while i < len(nums):
            if nums[i] not in M and nums[i] > M[jmin]:
                M[jmin] = nums[i]
                
                j, val, jmin = 1, M[0], 0
                while j < 3:
                    if val > M[j]:
                        val = M[j]
                        jmin = j
                    j += 1
            i += 1 
        
        if M[jmin] == -sys.maxint:
            return max(M[0], M[1], M[2])

        return M[jmin]        



# Leetcode 520. Detect Capital
class detectCapitalUse(object):
    def doit(self, word):
        """
        :type word: str
        :rtype: bool
        """
        i, result, cap = 0, True, True
        if word[i].isupper():
            i = 1
            while i < len(word) and i + 1 < len(word) :
                if not (word[i].isupper()) == word[i + 1].isupper():
                    result = False
                    break
                i += 1
        else:
            while i < len(word):
                if word[i].isupper():
                    result = False
                    break
                i += 1     

        return result

# Leetcode 62 Unique Paths
class uniquePaths(object):
    def doit(self, m, n):
        """
        :type m: int
        :type n: int
        :rtype: int
        """
        matrix = [[0 for x in range(n)] for y in range(m)]
        i, j, matrix[m-1][n-1], d = m-1, n-1, 1, 1
        
        while d <= m + n - 2:
            if d < n:
                j, i = n-1 - d, m-1
            else:
                j, i = 0, m-1 - (d - n + 1) 

            #while j <= n-1 and i <= m-1:
            while j <= n-1 and i >= 0:
                if i < m-1 and j < n-1:
                    matrix[i][j] = matrix[i + 1][j] + matrix[i][j + 1]
                else :
                    if j == n-1:
                        matrix[i][j] = matrix[i + 1][j]
                    if i == m-1:
                        matrix[i][j] = matrix[i][j + 1]

                i -= 1
                j += 1
            d += 1
        
        return matrix[0][0]


# Leetcode 63. Unique Paths II
class uniquePathsWithObstacles(object):
    def doit(self, obstacleGrid):
        """
        :type obstacleGrid: List[List[int]]
        :rtype: int
        """
        matrix = obstacleGrid
        m, n = len(matrix), len(matrix[0])
        
        i, j = 0, 0
        while i < m:
            j = 0
            while j < n:
                if matrix[i][j] == 1:
                    matrix[i][j] = -1
                j += 1
            i += 1

        if matrix[0][0] == -1 or matrix[m-1][n-1] == -1:
            return 0

        matrix[m-1][n-1], d = 1, 1

        while d <= m + n - 2:
            if d < n:
                j, i = n-1 - d, m-1
            else:
                j, i = 0, m-1 - (d - n + 1) 

            while j <= n-1 and i >= 0:
                if matrix[i][j] == -1:
                    i -= 1
                    j += 1
                    continue

                if i < m-1 and j < n-1:
                    matrix[i][j] = matrix[i + 1][j] + matrix[i][j + 1]
                    if matrix[i+1][j] == -1:
                        matrix[i][j] += 1
                    if matrix[i][j + 1] == -1:
                        matrix[i][j] += 1
                else :
                    if j == n-1:
                        matrix[i][j] = matrix[i + 1][j]
                    if i == m-1:
                        matrix[i][j] = matrix[i][j + 1]

                i -= 1
                j += 1
            d += 1
        
        return matrix[0][0]


# Leetcode 304. Range Sum Query 2D - Immutable
class NumMatrix(object):

    def __init__(self, matrix):
        """
        :type matrix: List[List[int]]
        """
        self._m = len(matrix)
        if self._m == 0:
            self._n = 0
            return
        else :
            self._n = len(matrix[0])
        self._mRec = [[0 for x in range(self._n)] for y in range(self._m)]

        j, self._mRec[0][0], m, n = 1, matrix[0][0], self._m, self._n
        while j < n: 
            self._mRec[0][j] = matrix[0][j] + self._mRec[0][j - 1]
            j += 1

        i = 1
        while i < m:
            j = 0
            sum = 0
            while j < n:
                sum += matrix[i][j]
                self._mRec[i][j] = sum + self._mRec[i - 1][j]
                j += 1
            i += 1        

    def sumRegion(self, row1, col1, row2, col2):
        """
        :type row1: int
        :type col1: int
        :type row2: int
        :type col2: int
        :rtype: int
        """
        if row2 >= self._m and col2 >= self._n:
            return 0

        S3, S2, S1 = 0, 0, 0
        
        if row1 != 0:
            S2 = self._mRec[row1-1][col2]
        if col1 != 0:
            S3 = self._mRec[row2][col1-1]
        if row1 != 0 and col1 != 0:
            S1 = self._mRec[row1-1][col1-1]   

        return self._mRec[row2][col2] - S3 - S2 + S1


# Leetcode 303. Range Sum Query - Immutable
class NumArray(object):

    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        self._m = len(nums)
        self._mNums = [0 for x in range(self._m + 1)]
        self._mNums[0] = 0
        i = 1
        while i <= self._m:
            self._mNums[i] = self._mNums[i-1] + nums[i-1]
            i += 1
        

    def sumRange(self, i, j):
        """
        :type i: int
        :type j: int
        :rtype: int
        """
        if i > j or j >= self._m:
            return 0

        return self._mNums[j+1] - self._mNums[i]

# Leetcode 240. Search a 2D Matrix II
class searchMatrixII(object):
    def doit(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: bool
        """
        if len(matrix) < 1 or len(matrix[0]) < 1:
            return False

        m, n = len(matrix), len(matrix[0])
        row, col = 0, n - 1
        while row < m and col >= 0:
            if matrix[row][col] < target:
                row += 1
            elif matrix[row][col] > target:
                col -= 1
            else:
                return True

        return False
        
        
    
        

# Leetcode 74. Search a 2D Matrix
class searchMatrix(object):
    def doit(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: bool
        """
        m, n = len(matrix), 0
        if m == 0:
            return False
        n = len(matrix[0])
        if n == 0:
            return False

        # get line
        start, end, mid = 0, m, m / 2
        while start < end:
            if matrix[mid][0] < target:
                start = mid + 1
            elif matrix[mid][0] > target:
                end = mid
            else:
                return True
            mid = (start + end) / 2

        # search line
        line = end - 1
        start, end, mid = 0, n, n / 2
        while start < end:
            if matrix[line][mid] < target:
                start = mid + 1
            elif matrix[line][mid] > target:
                end = mid
            else:
                return True
            mid = (start + end) / 2

        return False

    def doit2(self, matrix, target):
        m, n = len(matrix), len(matrix[0])
        start, end = 0, m * n - 1
        mid = (start + end) / 2
        
        while start < end:
            x, y = mid / n, mid % n
            if matrix[x][y] < target:
                start = mid + 1
            elif matrix[x][y] > target:
                end = mid
            else:
                return True
   
            mid = (start + end) / 2
        
        return matrix[mid/n][mid%n] == target
        
        

        

# Leetcode 82. Remove Duplicates from Sorted List II
class deleteDuplicatesII(object):
    def doit(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        result = ListNode(1000)
        tail, pt = result, head

        while pt != None:
            if pt.next == None or pt.next.val != pt.val:
                tail.next = pt
                tail = pt
                pt = pt.next
                continue

            s = pt
            while pt.next != None and s.val == pt.next.val:
                pt = pt.next
            pt = pt.next

        tail.next = None
        return result.next        

# Leetcode 83. Remove Duplicates from Sorted List
class deleteDuplicates(object):
    def doit(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        if head is None:
            return None
 
        val, pt, tail = head.val, head, head
        while pt != None:
            if val != pt.val:
                tail.next = pt
                val = pt.val
                tail = pt
            pt = pt.next
        tail.next = None

        return head
        

# Leetcode 56. Merge Intervals 
class Interval(object):
     def __init__(self, s=0, e=0):
         self.start = s
         self.end = e

class mergeIntervals(object):
    def doit(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[Interval]
        """
        if len(intervals) == 0:
            return []
        sortedIntervals = sorted(intervals, key=lambda Interval:Interval.start)
        result, i, cur = [], 0, Interval(sortedIntervals[0].start, sortedIntervals[0].end)
        while i < len(sortedIntervals):
            if cur.end < sortedIntervals[i].start:
                result.append(cur)
                cur = Interval(sortedIntervals[i].start, sortedIntervals[i].end)
            else:
                if cur.end < sortedIntervals[i].end:
                    cur.end = sortedIntervals[i].end
            i += 1

        result.append(cur)
        return result

# Leetcode 57. Insert Interval
class insertInIntervals(object):
    def doit(self, intervals, newInterval):
        """
        :type intervals: List[Interval]
        :type newInterval: Interval
        :rtype: List[Interval]
        """
        res = []
        if len(intervals) == 0:
            res.append(newInterval)
            return res
    
        i = 0
        while i < len(intervals) and intervals[i].end < newInterval.start:
            res.append(intervals[i])
            i += 1

        while i < len(intervals) and intervals[i].start <= newInterval.end:
            newInterval.end = max(intervals[i].end, newInterval.end)
            newInterval.start = min(intervals[i].start, newInterval.start)
            i += 1
        res.append(newInterval)

        while i < len(intervals):
            res.append(intervals[i])
            i += 1  

        return res

# Leetcode 43. Multiply Strings
class multiply(object):
    def doit(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        product = [0] * (len(num1) + len(num2))
        pos = len(product) - 1

        for n1 in reversed(num1):
            tempos = pos
            for n2 in reversed(num2):
                product[tempos] += int(n1) * int(n2)
                product[tempos - 1] += product[tempos] / 10
                product[tempos] = product[tempos] % 10
                tempos -= 1
            pos -= 1
    
        pt = 0
        while pt < len(product) - 1 and product[pt] == 0:
            pt += 1

        return ''.join(map(str, product[pt:]))

# Leetcode 415. Add Strings
class addStrings(object):
    def doit(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        result = [0] * (max(len(num1), len(num2)) + 1)
        pt1, pt2, temppos = len(num1) - 1, len(num2) - 1, len(result) - 1
        while temppos >= 0 and (pt1 >= 0 or pt2 >= 0):
            a, b = 0, 0
            if pt1 >= 0:
                a = int(num1[pt1])
                pt1 -= 1
            if pt2 >= 0:
                b = int(num2[pt2])
                pt2 -= 1

            result[temppos] += a + b
            result[temppos - 1] = result[temppos] / 10
            result[temppos] = result[temppos] % 10
            
            temppos -= 1

        pt = 0
        while pt < len(result) - 1 and result[pt] == 0:
            pt += 1
            
        return ''.join(map(str, result[pt:]))

# Leetcode 67. Add Binary
class addBinary(object):
    def doit(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: str
        """
        result, pt1, pt2, c = '', len(a)-1, len(b)-1, 0
        while pt1 >= 0 or pt2 >= 0:
            num1, num2 = 0, 0
            if pt1 >= 0:
                num1 = int(a[pt1])
            if pt2 >= 0:
                num2 = int(b[pt2])

            s = c + num1 + num2
            c = s / 2
            result = str(s % 2) + result

            pt1 -= 1
            pt2 -= 1
             
        if c != 0:
            result = str(c) + result

        return result

# Leetcode 66. Plus One
class plusOne(object):
    def doit(self, digits):
        """
        :type digits: List[int]
        :rtype: List[int]
        """
        result, n, i = [0] * (len(digits) + 1), len(digits), len(digits) - 1
        result[n] = 1
        while i >= 0 and n >= 0:
            result[n] += int(digits[i])
            result[n - 1] = result[n] / 10
            result[n] = result[n] % 10
            n -= 1
            i -= 1
        if result[0] == 0:
            result.pop(0)

        return result
        
# Leetcode 77. Combinations
class combine(object):
    def doit(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[List[int]]
        """
        def recur(num, k, arr):
            if k == 0:
                result.append(arr[:])
                return
            
            if k > len(num):
                return

            for i, element in enumerate(num):
                arr.append(num[i])
                recur(num[i+1:], k - 1, arr)
                arr.pop()
            
        result = []
        arr = []
        number = [x+1 for x in range(n)]
        recur(number, k, arr)
        return result

# Leetcode 85. Maximal Rectangle
class maximalRectangle(object):
    def doit(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
                






# Leetcode 39. Combination Sum        
class combinationSum(object):
    def doit(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        def recur(candidates, target, accu):
            if target == 0:
                result.append(accu[:])
                return

            if len(candidates) == 0:
                return    

            i = 0
            num = candidates[0]
            while target - num * i >= 0:
                recur(candidates[1:], target - num*i, accu[:])
                accu.append(num)
                i += 1
                
        
        result = []
        accu = []
        recur(candidates, target, accu)
        return result



# Leetcode 38. Count and Say
class countAndSay(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: str
        """
        temp, i = '1', 1
        while i < n:
            j, length, tempStr, cur = 0, len(temp), '', '1'
            while j < length:
                amount = 1
                while j + 1 < length and temp[j] == temp[j+1] :
                    j += 1
                    amount += 1

                tempStr += str(amount) + temp[j]
                j += 1
            temp = tempStr
            i += 1
        
        return temp

# Leetcode 40. Combination Sum II
class combinationSum2(object):
    def doit(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        if len(candidates) == 0:
            return []

        i, length, result = 0, len(candidates), []
        candidates.sort()

        def recurAccumulate(nums, i, target, accum, result):
            if target == 0:
                result.append(accum[:])
                return
        
            if i == len(nums) or nums[i] > target:
                return 

            j = i + 1
            while j < len(nums) and nums[j] == nums[i]:
                j += 1

            iNum, a, temp = j - i, 0, len(accum)
            while a <= iNum and target - a * nums[i] >= 0:
                recurAccumulate(nums, j, target - a * nums[i], accum, result)
                a += 1
                accum.append(nums[i])

            while len(accum) != temp:
                accum.pop();
            return

        recurAccumulate(candidates, 0, target, [], result)
        return result
            


                
# Leetcode 307. Range Sum Query - Mutable

# Leetcode 188. Best Time to Buy and Sell Stock IV


# Leetcode 42. Trapping Rain Water
class trap(object):
    def doit(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        leftmaxVal, mv, i = [0 for x in range(len(height))], 0, 0
        while i < len(height):
            leftmaxVal[i] = mv
            mv = max(mv, height[i])
            i += 1
        
        rightmaxVal, mv, i = [0 for x in range(len(height))], 0, len(height)-1
        while i >= 0:
            rightmaxVal[i] = mv
            mv = max(mv, height[i])
            i -= 1

        contained, i = 0, 0
        while i < len(height):
            if min(leftmaxVal[i], rightmaxVal[i]) > height[i]:
                contained += min(leftmaxVal[i], rightmaxVal[i]) - height[i]
            i += 1
       
        return contained
        
# Leetcode 407. Trapping Rain Water II
class trapRainWater(object):
    def doit(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        m, n = len(heightMap), len(heightMap[0])
        leftMV, i, j, maxV = [[0 for x in range(n)] for y in range(m)], 0, 0, 0
        while i < m:
           j, maxV = 0, 0
           while j < n:
              leftMV[i][j] = maxV
              maxV = max(heightMap[i][j], maxV)  
              j += 1
           i += 1
        
        rightMV, i, j, maxV = [[0 for x in range(n)] for y in range(m)], 0, 0, 0
        while i < m:
           j, maxV = n - 1, 0
           while j >= 0:
              rightMV[i][j] = maxV
              maxV = max(heightMap[i][j], maxV)
              j -= 1
           i += 1 

        topMV, i, j, maxV = [[0 for x in range(n)] for y in range(m)], 0, 0, 0
        while j < n:
            i, maxV = 0, 0
            while i < m:
                topMV[i][j] = maxV
                maxV = max(heightMap[i][j], maxV)
                i += 1
            j += 1         
                
        bottomMV, i, j, maxV = [[0 for x in range(n)] for y in range(m)], 0, 0, 0
        while j < n:
            i, maxV = m - 1, 0
            while i >= 0:
                bottomMV[i][j] = maxV
                maxV = max(heightMap[i][j], maxV)
                i -= 1
            j += 1  


        # Calculate
        contained, i, j = 0, 0, 0
        while i < m:
            j = 0
            while j < n:
                minV = min(min(leftMV[i][j], rightMV[i][j]), min(topMV[i][j], bottomMV[i][j]))
                if minV > heightMap[i][j]:
                    contained += minV - heightMap[i][j]
                j += 1
            i += 1

        return contained

# Leetcode 61. Rotate List
class rotateRight(object):
    def doit(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        if head == None:
            return head
            
        pHead, pTail, len = head, head, 1
        while pTail.next != None:
            len += 1
            pTail = pTail.next

        pTail.next, i = head, 0
        k %= len
        while i < len-k-1:
           pHead = pHead.next
           i += 1
        
        res = pHead.next
        pHead.next = None
        return res
        

# Leetcode 189. Rotate Array
class rotate(object):
    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        k %= len(nums)
        temp, i = [0 for x in range(k)], len(nums) - k

        while i < len(nums):
            
            i += 1
        
# Leetcode 51. N-Queens
class solveNQueens(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        def checkPos(position, k):
            i, pos, res = 0, position[k], 1
            while i <= k - 1:
                if abs(position[i] - pos) == abs(i - k) or position[i] == pos:
                    res = 0
                i += 1

            if k == len(position) - 1 and res == 1:
                res = 2

            return res
        
        position, result = [-1 for x in range(n)], []
        k = 0
        while k >= 0:

            while position[k] < n - 1:
                position[k] += 1
                res = checkPos(position, k)
                if res == 1:
                    k += 1
                    continue
                elif res == 2:
                    temp, j = [], 0
                    while j < n:
                        queen = ['.']*n
                        queen[position[j]] = 'Q'
                        temp.append(''.join(map(str, queen[:])))
                        j += 1
                    result.append(temp)
                    break
                else:
                    continue

            position[k] = -1
            k -= 1

        return result
                
# Leetcode 50. Pow(x, n)        
class myPow(object):
    def doit(self, x, n):
        """
        :type x: float
        :type n: int
        :rtype: float
        """
        m = abs(n)
        temp, res = x, 1
        while m != 0:
            if m % 2 == 1:
                res *= temp
            temp *= temp

            m /= 2

        return res if n > 0 else 1/res 
          
# Leetcode 69. Sqrt(x)
class mySqrt(object):
    def doit(self, x):
        """
        :type x: int
        :rtype: int
        """        
        if x == 0:
            return 0
        
        left, right = 0, x
        while left <= right:
            mid = (left + right) / 2
            if mid * mid <= x < (mid+1) * (mid+1):
                return mid
            elif x < mid * mid:
                right = mid
            else:
                left = mid + 1
              
         
# Leetcode 372. Super Pow
# One knowledge: ab % k = (a%k)(b%k)%k
# Since the power here is an array, we'd better handle it digit by digit.
# One observation:
# a^1234567 % k = (a^1234560 % k) * (a^7 % k) % k = (a^123456 % k)^10 % k * (a^7 % k) % k
# Looks complicated? Let me put it other way:
# Suppose f(a, b) calculates a^b % k; Then translate above formula to using f :
# f(a,1234567) = f(a, 1234560) * f(a, 7) % k = f(f(a, 123456),10) * f(a,7)%k;
# Implementation of this idea:
class superPow(object):
    def doit(self, a, b):
        """
        :type a: int
        :type b: List[int]
        :rtype: int
        """
        base = 1337
        def powmod(a, b):
            a %= base
            i, result = 0, 1
            while i < b:
               result =  (result * a) % base
               i += 1
            return result

        def PowByK(a, b, k):
            if k < 0:
                return 1
            
            return (powmod(PowByK(a, b, k-1), 10) * powmod(a, b[k])) % base

        return PowByK(a, b, len(b) - 1)

    def doit2(self, a, b):
        def finishMod(a):
            listA = [a%1337]
            x=a
            for i in range(1,1338):
                x=(x*a)%1337
                listA.append(x)
            return listA

        q=finishMod(a)

        def findOrder(listA):
            for i in range(1,1338):
                if listA[i]==listA[0]:
                    return i
            return 0

        w=findOrder(q)
        if(w==0):
            w=1338
        e= int(''.join(map(str, b)))
        r= e%w
        return q[r-1]


# Leetcode 49. Group Anagrams
class groupAnagrams(object):
    def doit(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        """
        codeLt, i, result = [], 0, []
        while i < len(strs):
            code, j, word = {}, 0, strs[i]
            while j < len(word):
                if code.has_key(word[j]):
                    code[word[j]] += 1
                else:
                    code[word[j]] = 0
                j += 1
            
            j = 0
            while j < len(codeLt):
                if codeLt[j] == code:
                    break
                j += 1
            if j == len(codeLt):
                codeLt.append(code)
                result.append([word])
            else:
                result[j].append(word)
            i += 1

        return result

    def doit2(self, strs):
        dic = {}
        for item in sorted(strs):
            sortedItem = ''.join(sorted(item))
            dic[sortedItem] = dic.get(sortedItem, []) + [item]
        return dic.values()
        
# Leetcode 242. Valid Anagram        
class isAnagram(object):
    def doit(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        def makeCode(word):
            code, j= {}, 0
            while j < len(word):
                if code.has_key(word[j]):
                    code[word[j]] += 1
                else:
                    code[word[j]] = 0
                j += 1
            return code
        return makeCode(s) == makeCode(t)

# Leetcode 91. Decode Ways
#'A' -> 1
#'B' -> 2
#...
#'Z' -> 26
class numDecodings(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        if not s:
            return 0

        D = [0] * (len(s) + 1)
        D[0], D[1] = 1, 0 if s[0] == '0' else 1
        i = 2
        while i < len(D):
            first, second = s[i-1], s[i-2 : i]
            if '1' <= first <= '9':
                D[i] += D[i-1]
            if '10' <= second <= '26':
                D[i] += D[i-2]

            i += 1
        return D[len(s)]
              

    def doit1(self, s):
        """
        :type s: str
        :rtype: int
        """
        if not s or s[0] == '0':
            return 0

        r1, r2 = 1, 1 # s[i-1], s[r-2]
        i = 0
        while i < len(s):
            if s[i] == '0':
                r1 = 0
            
            if s[i-1] == '1' or s[i-1] == '2' and s[i] < '7':
                r1 = r1 + r2
                r2 = r1 - r2
            else :
                r2 = r1
            i += 1

        return r1

    def doit3(self, s):
        n = len(s)
        if n == 0 or s[0] == '0':
            return 0
        if n == 1:
            return 1
        memo = [0] * (n + 1)
        memo[n] = 1
        memo[n-1] = 1 if s[n-1] != '0' else 0
        for i in range(n-2, -1, -1):
            if s[i] == '0':
                continue
            else:
                memo[i] = memo[i+1] + memo [i+2] if s[i:i+2] <= '26' else memo[i+1]
        return memo[0]
            

# 79. Word Search
class existWord(object):
    def doit(self, board, word):
        """
        :type board: List[List[str]]
        :type word: str
        :rtype: bool
        """
        #def findWord(board, x, y):
        #    m, n = len(board), len(board[0])
        #    i, num, pos = 1, len(word), [1 for x in range()]

        #    while i < len(num):
                
        #        while pos[i] <= 4:
        #            x1, y1 = x, y
        #            if pos[i] in (1,3):
        #                x += 1 if pos[i] == 1 else -1
        #            if pos[i] in (2,4):
        #                y += 1 if pos[i] == 2 else -1

        #            if 0 <= x < m and 0 <= y < n and board[x][y] == word[i]:
        #                i += 1
        #                continue
        #            else :
        #                pos[i] += 1
        #                x, y = x1, y1

        #        if pos[i] > 4:
        #            if pos[i] in (1,3):
        #                x -= 1 if pos[i] == 1 else -1
        #            if pos[i] in (2,4):
        #                y -= 1 if pos[i] == 2 else -1

        #            pos[i] = 0

        m, n = len(board), len(board[0])

        def findword(x, y, i):
            if not (0<=x<m) or not (0<=y<n) or i >= len(word) or board[x][y] != word[i]:
                return False
            
            if i == len(word)-1:
                return True

            t, board[x][y] = board[x][y], '0'
            result = findword(x+1, y, i+1) or findword(x-1, y, i+1) or findword(x, y+1, i+1) or findword(x, y-1, i+1)
            
            if not result:
                board[x][y] = t

            return result
            
        for x in xrange(0, m):
            for y in xrange(0, n):
                if board[x][y] == word[0] and findword(x, y, 0):
                    return True
        return False
                    

# 86. Partition List        
#Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
#You should preserve the original relative order of the nodes in each of the two partitions.            
class partition(object):
    def doit(self, head, x):
        """
        :type head: ListNode
        :type x: int
        :rtype: ListNode
        """
        result = ListNode(0)
        result.next = head
        st, it, last = result, head, result
        
        while it :
            if it.val < x:
                next = it.next
                if it != st.next:
                    st.next, it.next, last.next = it, st.next, next
                it, st = next, st.next
                continue

            last, it = it, it.next
        return result.next
            
# 80. Remove Duplicates from Sorted Array II
class removeDuplicatesII(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i = 0
        for n in nums:
            if i < 2 or n > nums[i-2]:
                nums[i] = n
                i += 1
                
        return i

    def doit(self, nums, k=2):
        if len(nums) <= k:
            return len(nums)

        i, j, cnt = 1, 1, 1
        while j < len(nums):
            if nums[j] != nums[j-1]:
                cnt = 1
                nums[i] = nums[j]
                i += 1
            else:
                if cnt < k:
                    cnt += 1
                    nums[i] = nums[j]
                    i += 1
            j += 1

        return i
                    
                


# Leetcode 20. Valid Parentheses        
class isValidParentheses(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: bool
        """
        def isPair(a, b):
            return a == '(' and b == ')' or a == '[' and b == ']' or a == '{' and b == '}'

        result, length = [], 0
        for x in s:
            length = len(result)
            if length > 0 and isPair(result[length - 1], x):
                result.pop()
                continue

            if x in ['}', ']', ')']:
                return False
            
            result.append(x)

        return len(result) == 0
            
# Leetcode 301. Remove Invalid Parentheses
class removeInvalidParentheses(object):
    def doit2(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        leftBuf, i, length, invalideBuf, result = [], 0, len(s), [], s
        while i < length:
            if s[i] == '(':
                leftBuf.append(i)
            else:
                if s[i] == ')' and len(leftBuf) == 0:
                    invalideBuf.append(i)
                else:
                    leftBuf.pop()
            i += 1
        
        for x in invalideBuf:
            leftBuf.append(x)

        
        for x in reversed(leftBuf):
            result = result[:x] + result[x+1:]

        return result

    def doit(self, s):
        def removeParentheses(s, start, end, result, par):
           i, stack = start, 0
           while i < len(s):
                if s[i] == par[1]:
                    stack -= 1
                elif s[i] == par[0]:
                    stack += 1
        
                if stack >= 0:
                    i += 1
                    continue

                j = end
                while j <= i:
                    if s[j] == par[1] and (j == end or s[j - 1] != par[1]):
                        removeParentheses(s[:j] + s[j+1:], i, j, result, par)
                    j += 1
                return
                
           reversedStr = s[::-1]
           if par[0] == '(':
                removeParentheses(reversedStr, 0, 0, result, [')', '('])
           else :
                result.append(reversedStr)

        result, par = [], ['(', ')']
        removeParentheses(s, 0, 0, result, par)
        return result
        
# Leetcode 100. Same Tree
class isSameTree(object):
    def doit(self, p, q):
        """
        :type p: TreeNode
        :type q: TreeNode
        :rtype: bool
        """
        def isSame(a, b):
            if a == None and b == None:
                return True
    
            if a == None or b == None or a.val != b.val:
                return False

            return isSame(a.left, b.left) and isSame(a.right, b.right)
        
        return isSame(p, q)

    def doit2(self, p, q):
        st_p, st_q = [], []
        if p : st_p.append(p)
        if q : st_q.append(q)

        while len(st_p) != 0 and len(st_q) != 0:
            a = st_p.pop()
            b = st_q.pop()
            if a.val != b.val:
                return False
        
            if a.left : st_p.append(a.left)
            if b.left : st_q.append(b.left)

            if len(st_p) != len(st_q) :
                return False

            if a.right : st_p.append(a.right)
            if b.right : st_q.append(b.right)

            if len(st_p) != len(st_q) :
                return False

        return len(st_p) == len(st_q)
                    
                
            
# Leetcode 104. Maximum Depth of Binary Tree
class maxDepth(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def TreeDep(rt) :
            if rt == None:
                return 0

            return max(TreeDep(rt.left), TreeDep(rt.right)) + 1

        return TreeDep(root)
            
    def doit2(self, root):
        pass
        

        
# Leetcode 95. Unique Binary Search Trees II
class generateTrees(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: List[TreeNode]
        """
        def makeTree(nums):
            if len(nums) == 0:
                return []
            if len(nums) == 1:
                return [TreeNode(nums[0])]

            i, result= 0, [];
            while i < len(nums):
                left = makeTree(nums[:i])
                right = makeTree(nums[i+1:])
                if len(left) == 0: left.append(None)
                if len(right) == 0: right.append(None)
                j = 0
                while j < len(left):
                    k = 0
                    while k < len(right):
                        a = TreeNode(nums[i])
                        a.left = left[j]
                        a.right = right[k]
                        result.append(a)
                        k += 1
                    j += 1
                i += 1

            return result
        
        numbers = [x + 1 for x in range(n)]
        return makeTree(numbers)

    # DP
    def doit3(self, n):
        
        def geneTree(start, end, matrix):
            if start > end:
                return None
            if start == end:
                return [TreeNode(start)]

            if matrix[start][end] != 0:
                return matrix[start][end]

            i, result = start, []
            while i <= end:
                left = geneTree(start, i-1)
                right = geneTree(i + 1, end)
            
                for l in left:
                    for r in right:
                        a = TreeNode(nums[i])
                        a.left = l
                        a.right = r
                        result.append(a)
                i += 1
            
            matrix[start][end] = result
            return result
           
        matrix = [[0 for x in range(n)] for y in range(n)]
        return geneTree(1, n, matrix)
        

    def doit2(self, n) :
        if n == 0:
            return [[]]
        return self.dfs(1, n+1)
        
    def dfs(self, start, end):
        if start == end:
            return None
        result = []
        for i in xrange(start, end):
            for l in self.dfs(start, i) or [None]:
                for r in self.dfs(i+1, end) or [None]:
                    node = TreeNode(i)
                    node.left, node.right  = l, r
                    result.append(node)
        return result
    


# Leetocde 96. Unique Binary Search Trees II
class numTrees(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        numbers = [x + 1 for x in range(n)]
        
        def numberofBST(arr, mapRes):
            if len(arr) == 0 or len(arr) == 1:
                return 1

            if len(arr) == 2:
                return 2

            if mapRes.has_key(len(arr)):
                return mapRes[len(arr)]

            amount = 0
            i = 0
            while i < len(arr):
                amount += numberofBST(arr[:i], mapRes) * numberofBST(arr[i+1:], mapRes)
                i += 1

            mapRes[len(arr)] = amount
            return amount

        return numberofBST(numbers, {})

    def doit2(self, n):
        result, i = [1 for x in range(n+1)], 2
        while i <= n:
            amount, j = 0, 0
            while j < i:
                amount += result[j] * result[i - j - 1]
                j += 1
            result[i] = amount
            i += 1

        return result[n]
            
        
# Leetcode 89. Gray Code
class grayCode(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        result = []
        result.append(0)

        for i in range(n):
            j = len(result) - 1
            base = 2 ** i
            while j >= 0:
                result.append(result[j] + base)
                # result.append(result[j] | 1<<i )
                j -= 1

        return result
            
    # G(i) = i ^ (i / 2)
    def doit2(self, n):
        i, result = 0, []
        while i < 1 << n:
            result.append(i ^ i >> 1)
        return result
        
        


# Leetcode 53. Maximum Subarray
class maxSubArray(object):
    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """ 
        A, i, maxVal = [0 for x in range(len(nums))], 0, -2147483647
        while i < len(nums):
            j = 0
            while j + i < len(nums):
                A[j] += nums[j + i]
                maxVal = max(A[j], maxVal)
                j += 1
            i += 1

        return maxVal

    def doit(self, nums):
        i, maxEnd, maxVal = 0, 0, -2147483647
        while i < len(nums):
            maxEnd = max(maxEnd + nums[i], nums[i])
            maxVal = max(maxVal, maxEnd)
            i += 1
        return maxVal

    def doit3(self, nums):
        i, istart, start, end, maxEnd, maxVal = 0, 0, 0, 0, 0, -2147483647
        while i < len(nums):
            if maxEnd + nums[i] < nums[i]:
                maxEnd = nums[i]
                istart = i
            else:
                maxEnd += nums[i]

            if maxVal < maxEnd :
                maxVal = maxEnd
                end = i
                start = istart
            i += 1

        return maxVal
        
        
# Leetcode 60. Permutation Sequence
class getPermutation(object):
    def doit2(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        def iterNumber(x, temp, n, k, res):
            if n == 0:
                res.append(temp)
                return len(res) != k

            i = 0
            while i < len(x):
               if iterNumber(x[:i] + x[i+1:], temp + str(x[i]), n - 1, k, res) == False:
                    return False
               i += 1

            return True
            
        x, res = [x + 1 for x in range(n)], []
        iterNumber(x, "", n, k, res)
        return res[k-1]

    def doit(self, n, k):
        factorial, i, accum = [1 for x in range(n+1)], 1, 1
        numbers = [x+1 for x in range(n)]
        while i < n+1:
            accum *= i
            factorial[i] = accum
            i += 1 

        j, res, k = n - 1, "", k -1
        while j >= 0:
           temp = k / factorial[j]
           k -= temp * factorial[j]
           j -= 1
           res += str(numbers[temp])
           numbers.pop(temp)

        return res

# Leetcode 31. Next Permutation
class nextPermutation(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        def swap(nums, i, j):
            temp = nums[i]
            nums[i] = nums[j]
            nums[j] = temp

        def reverseSort(nums, start, end):
            if start > end:
                return
            i = start
            while i <= (start + end) / 2:
                swap(nums, i, start + end -i)
                i += 1
        
        i = len(nums) - 1
        while i > 0:
            if nums[i-1] < nums[i]:
                break
            i -= 1

        if i == 0:
            reverseSort(nums, 0, len(nums)-1)
        else:
            j = len(nums)-1
            while j >= i:
                if nums[j] > nums[i-1]:
                    swap(nums, j, i-1)
                    break
                j -= 1
            
            reverseSort(nums, i, len(nums)-1)
           
        return
    
    def doit2(self, nums):
        for i in range(len(nums)-1)[::-1]:
            target = nums[i]
            replace = None
            replace_index = None
            for j in range(len(nums[i + 1:])):
                num = nums[i + 1 + j]
                if num > target and (not replace or num < replace):
                    replace = num
                    replace_index = j + i + 1
            if replace:
                nums[replace_index] = target
                nums[i] = replace
                nums[i+1:] = sorted(nums[i+1:])
                return
        nums.sort()

    def doit3(self, nums):
        if not nums or len(nums) == 1:
            return
        ## 1) find the largest k, such that a[k] < a[k+1]
        k, j = 0, 0
        N = len(nums)
        for k in xrange(N-2, -1, -1):
            if nums[k]<nums[k+1]:
                break
            if k == 0:
                nums.reverse()
                #nums = nums[::-1]
                #nums.sort()
                return
        ## 2) find the largest j (j > k), such that a[j] > a[k]
        for j in xrange(N-1, k, -1):
            if nums[j] > nums[k]:
                break
        ## 3) swap k, j
        nums[k], nums[j] = nums[j], nums[k]
        ## 4) reverse nums from k+1 to N-1
        nums[k+1:] = nums[N-1:k:-1]
        return
       
# Leetcode 98. Validate Binary Search Tree
class isValidBST(object):
    def doit2(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        def iterCheck(node, minVal, maxVal):
            if node == None:
                return True

            if node.val >= maxVal or node.val <= minVal:
                return False
            
            return iterCheck(node.left, minVal, node.val) and iterCheck(node.right, node.val, maxVal)

        return iterCheck(root, -sys.maxsize, sys.maxsize)

    def doit(self, root):
        def preorder(root, res):
            if not root:
                return
            preorder(root.left, res)
            res.append(root.val)
            preorder(root.right, res)
            

        res = []
        preorder(root, res)
        for i in xrange(1, len(res)):
            if res[i] <= res[i - 1]:
                return False
        return True







# Leetcode 92. Reverse Linked List II
class reverseBetween(object):
    def doit(self, head, m, n):
        """
        :type head: ListNode
        :type m: int
        :type n: int
        :rtype: ListNode
        """
        preHead = ListNode(1000)
        pt, preHead.next, i, = preHead, head, 1
        while pt and i < m:
            pt = pt.next
            i += 1

        pStart, pEnd = pt.next, pt
        while pStart and i < n:
            p = pStart.next
            pStart.next = p.next
            p.next = pEnd.next 
            pEnd.next = p
            i += 1

        return preHead.next

    
# Leetcode 206. Reverse Linked List
class reverseList(object):
    def doit(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        result = ListNode(1000)
        result.next, pt = head, head
        
        while pt and pt.next:
            next = pt.next
            pt.next = next.next
            result.next, next.next = next, result.next

        return result.next
        

# Leetcode 93. Restore IP Addresses
class restoreIpAddresses(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        def isValid(s):
            if len(s) > 3 or len(s) == 0 or s[0] == '0' and len(s) > 1 or int(s) > 255:
                return False
            return True
 
        length, res = len(s), []
        i = 1
        while i < 4 and i < length - 2:
            j = i + 1
            while j < i + 4 and j < length -1 :
                k = j + 1
                while k < j + 4 and k < length:
                    if isValid(s[:i]) and isValid(s[i:j]) and isValid(s[j:k]) and isValid(s[k:]):
                        res.append(s[:i] + '.' + s[i:j] + '.' + s[j:k] + '.' + s[k:])
                    k += 1
                j += 1
            i += 1

        return res

#Leetcode 17. Letter Combinations of a Phone Number
class letterCombinations(object):
    def doit(self, digits):
        """
        :type digits: str
        :rtype: List[str]
        """
        DigitalMap = {'2':'abc', '3':'def', '4':'ghi', '5':'jkl', '6':'mno', '7':'pqrs', '8':'tuv', '9':'wxyz'}
        length, i, temp, result, tempResult = len(digits), 0, [-1 for x in range(len(digits))], [], ['' for x in range(len(digits))]

        while i < length and i >= 0:

            while temp[i] < len(DigitalMap[digits[i]]) - 1:
                temp[i] += 1
                tempResult[i] = DigitalMap[digits[i]][temp[i]]
                if i == length - 1:
                    result.append(''.join(map(str, tempResult[:])))
                    continue
                i += 1

            temp[i] = -1
            tempResult[i] = ''
            i -= 1

        return result


# Leetcode 28. Implement strStr()
class strStr(object):
    def doit(self, haystack, needle):
        """
        :type haystack: str
        :type needle: str
        :rtype: int
        """
        if len(needle) == 0:
            return 0

        index, length, i = 0, len(haystack), 0
        next = self.makeKmp(needle)

        while index < length:
            if haystack[index] == needle[i]:
                i += 1
                index += 1

            if i == len(needle):
                return index - i
            
            if index < length and haystack[index] != needle[i]:
                if i > 0: 
                    i = next[i - 1]
                else:
                    index += 1
                
        return -1

    def makeKmp(self, needle) :
        next, prefixlen, j = [0 for x in range(len(needle))], 0, 1

        while j < len(next) :
            if needle[prefixlen] == needle[j]:
                prefixlen += 1
                next[j] = prefixlen
                j += 1
            else:
               if prefixlen > 0:
                  prefixlen = next[prefixlen - 1]
               else:
                  next[j] = 0
                  j += 1

        return next
        
        

#Leetcode 6. ZigZag Conversion
class convert(object):
    def doit(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """ 
        content, rowArray, length, i = list(s), ['' for x in range(numRows)], len(s), 0
        
        while i < length:
            index = 0
            while index < numRows and i < length:
                rowArray[index] += content[i]
                index += 1
                i += 1

            index = numRows - 2
            while index >= 1 and i < length:
                rowArray[index] += content[i]
                index -= 1
                i += 1

        return ''.join(map(str, rowArray[:]))

    def doit(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """
        if numRows == 1 or len(s) == 1 or len(s) <= numRows:
            return s
        
        n = len(s)
        res = ''
        for i in range(numRows):
            if i == 0 or i == numRows - 1:
                res += s[i::2*(numRows - 1)]
                continue
            m = i
            res += s[m]
            #print '1st: ', res
            while m + 2*(numRows -1 -i) < n:
                res +=s [m+2*(numRows - 1 - i)]
                m += 2*(numRows -1 - i)
                #print '2nd: ', res
                if m + 2*i < n:
                    res += s[m+2*i]
                    m += 2*i
                    #print '3rd: ', res
                else:
                    break
        return res
        
        # rules
        """
        0: 0      7       13     2*(numRows -1)
        1: 1    6 8    12 14     2*(numRows -1 -i) -> 2*i ->...
        2: 2  5   9  11   15     2*(numRows -1 -i) -> 2*i ->...
        3: 3      10      16     2*(numRows -1)
        """
                        
        
# Leetcode 41. First Missing Positive
class firstMissingPositive(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i, length = 0, len(nums)
        while i < length:
            while 0 < nums[i] <= length and nums[nums[i]-1] != nums[i]:
                nums[nums[i] - 1], nums[i] = nums[i], nums[nums[i] - 1] 
            i += 1
        
        i = 0
        while i < length and nums[i] == i + 1:
            i += 1

        return i + 1


# Leetcode 268. Missing Number
class missingNumber(object):
    # O(n)
    def doit(self, nums):
        n = len(nums)
        return n*(n+1)/2 - sum(nums)

    def doit2(self, nums):
        return reduce(operator.xor, range(0, len(nums) + 1) + nums)

    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """ 
        i, length = 0, len(nums)
        while i < length:
            while 0 <= nums[i] < length and nums[i] != i:
                a = nums[nums[i]]
                nums[nums[i]] = nums[i]
                nums[i] = a
            i += 1

        i = 0
        while i < length and nums[i] == i:
            i += 1

        return i 


# Leetcode 136. Single Number
class singleNumber(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # ^ is exchangble
        i, result = 0, 0
        while i < len(nums):
            result ^= nums[i]
            i += 1

        return result

# Leetcode 137. Single Number II
class singleNumberII(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        ones, twos = 0, 0
        for i in nums:
            ones = (ones ^ i) & ~twos
            twos = (twos ^ i) & ~ones
            
        return ones
        


# Leetcode 287. Find the Duplicate Number
class findDuplicate(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        i = 0
        while i + 1 < len(nums):
            if nums[i+1] == nums[i]:
                return nums[i]
            i += 1
            
        return nums[i]

    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums)<2: return nums[0:1]
        slow, fast = nums[0], nums[nums[0]]
        while slow != fast:
            slow = nums[slow]
            fast = nums[nums[fast]]
        slow = 0
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]
        return slow


# Leetcode 36. Valid Sudoku
class isValidSudoku(object):
    def doit(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        if len(board) == 0:
            return False

        # Check row and col
        i = 0
        while i < 9:
            j = 0
            row, col = [0 for x in range(10)], [0 for x in range(10)]
            while j < 9:
                if board[i][j] != '.':
                    if row[int(board[i][j])] == 1:
                        return False
                    row[int(board[i][j])] += 1

                if board[j][i] != '.':
                    if col[int(board[j][i])] == 1:
                        return False
                    col[int(board[j][i])] += 1
                j += 1
            i += 1
        
        # Check small 9
        i = 0
        while i < 9:
            j = 0
            while j < 9:
                content = [0 for x in range(10)]
                a = 0
                while a < 3:
                   b = 0 
                   while b < 3:
                       if board[i+a][j+b] == '.':
                           b += 1
                           continue
                       if content[int(board[i+a][j+b])] == 1:
                           return False
                       content[int(board[i+a][j+b])]  += 1
                       b += 1
                   a += 1
                j += 3
            i += 3

        return True


# Leetcode 131. Palindrome Partitioning
class partitionPalindrome(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: List[List[str]]
        """
        def isPalindrome(s, start, end):
            while start < end:
                if s[start] != s[end]:
                    return False
                start += 1
                end -= 1

            return True


        def dfs(s, start, output, result):
            if start == len(s) :
                result.append(output[:])
                return

            i = start
            while i < len(s):
                if isPalindrome(s, start, i):
                    output.append(s[start:i+1])
                    dfs(s, i+1, output, result)
                    output.pop()
                i += 1

        result = []
        dfs(s, 0, [], result)
        return result
        
# Leetcode 132. Palindrome Partitioning II
class minCutPalindrome(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        if len(s) == 0:
            return 0

        D = [len(s) - x for x in range(len(s) + 1)]
        p = [[False for x in range(len(s))] for y in range(len(s))]

        i = len(s) - 1
        while i >= 0:
            j = i
            while j < len(s):
                if s[i] == s[j] and (j - i < 2 or p[i+1][j-1]):
                    p[i][j] =  True                
                    D[i] = min(1 + D[j + 1], D[i]) 
                j += 1
            i -= 1

        return D[0] - 1

    def doit2(self, s):
        n = len(s)
        pal = [[False for col in range(n)] for row in range(n)]
        d = [n-1 for i in range(n)]
        
        for i in range(n-1, -1, -1):
            d[i] = n-i-1
            for j in range(i, n):
                if s[i] == s[j] and (j-i<=2 or pal[i+1][j-1]):
                    pal[i][j] = True
                    if j==n-1:
                        d[i] = 0
                    elif d[j+1] + 1 <d[i]:
                        d[i] = d[j+1]+1
        return d[0]

        
 
# Leetcode 125. Valid Palindrome
class isValidPalindrome(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: bool
        """
        s = s.lower()
        start, end = 0, len(s) - 1
        while start < end:
            while start < end and not (s[start].isalpha() or s[start].isdigit()):
                start += 1

            while end > start and not (s[end].isalpha() or s[end].isdigit()):
                end -= 1

            if end < start:
                break

            if s[start] != s[end]:
                return False

            start += 1
            end -= 1

        return True

# Leetcode 133 Clone Graph
# Definition for a undirected graph node
class UndirectedGraphNode:
     def __init__(self, x):
         self.label = x
         self.neighbors = []

class cloneGraph:
    # @param node, a undirected graph node
    # @return a undirected graph node
    def doit(self, node):
        if not node:
            return None
        
        dict, queue, labels = {}, [node], set()
        dict[node.label] = UndirectedGraphNode(node.label)
        labels.add(node.label)
        
        while queue:
            t = queue.pop(0) 
    
            for i in t.neighbors:
               if i.label not in labels:
                   queue.append(i)
                   labels.add(i.label)
                    
               if i.label not in dict: 
                   dict[i.label] = UndirectedGraphNode(i.label)
                    
               dict[t.label].neighbors.append(dict[i.label])
        
        return dict[node.label]

    def doit3(self, node):
        if not node:
            return None
        
        cloned_node = UndirectedGraphNode(node.label)
        queue, map = collections.deque([node]), {}
        map[node] = cloned_node
        
        while queue:
            cur = queue.popleft()
            for neighbor in cur.neighbors:
                if neighbor not in map:
                    copy = UndirectedGraphNode(neighbor.label)
                    map[neighbor] = copy
                    map[cur].neighbors.append(copy)
                    queue.append(neighbor)
                else:
                    map[cur].neighbors.append(map[neighbor])
        return cloned_node


    def doit2(self, node):
        if not node:
            return None

        def cloneGraph(node, map):
            
            if node.label in map:
                return map[node.label]

            map[node.label] = UndirectedGraphNode(node.label)

            for num in node.neighbors:
                a = cloneGraph(num, map)
                map[node.label].neighbors.append(a)                

            return map[node.label]

        return cloneGraph(node, {})

    def serializeGraph(self, node):
        if not node:
            return node

        nodes, dict, res = [node], set(), []
            
        while nodes:
            t = nodes.pop(0)
            if t.label not in labels:
                labels.add(t.label)
            temp += t.label
            for i in t.neighbors:
                if i not in labels:
                    nodes.append(i)
                temp += ',' + i.label

                res.append(temp)
        return '#'.join(res)


        
            
# Leetcode 145. Binary Tree Postorder Traversal                   
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class postorderTraversal(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        def searchTree(node):
            if not node:
                return []

            return searchTree(node.left) + searchTree(node.right) + [node.val]

        return searchTree(root)

        #self.ans = []
        #def post(root):
        #    if root is None:
        #        return []
        #    post(root.left)
        #    post(root.right)
        #    self.ans.append(root.val)
        #post(root)
        #return self.ans


    def doit1(self, root):

        if not root:
            return []
        
        node, leftNode, rightNode, res = root, [], [root], []

        while leftNode or rightNode:
            
            while rightNode:
                A = rightNode.pop()
                if A.left:
                    leftNode.append(A.left)
                if A.right:
                    rightNode.append(A.right)

                res.append(A.val)

            if leftNode:    
                rightNode.append(leftNode.pop())

        res.reverse()
        return res

    def doit3(self, root):
        self.answer = []
        def traversal(node):
            if node.left is not None:
                traversal(node.left)
            if node.right is not None:
                traversal(node.right)
            self.answer.append(node.val)
        if root is not None:
            traversal(root)
        return self.answer
                
        
        
# Leetcode 128. Longest Consecutive Sequence                     
class longestConsecutive(object):
    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        D, best = set(nums), 0
        for x in D:
            if x-1 not in D:
                y = x + 1
                while y in D:
                    y += 1

                best = max(best, y - x)                    

        return best

    def doit(self, nums):
        nums = list(set(nums))
        nums.sort()
        longest = 0
        current = 0
        for i in range(len(nums)):
            if i >= 1 and nums[i] == 1+nums[i-1]:
                current += 1
            else:
                current = 1
            longest = max(longest, current)
        return longest
    
                
    
            
        




# Leetcode 130. Surrounded Regions
class SurroundedRegions(object):
    def doit(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        if not board:
            return
        
        m, n = len(board), len(board[0])
        save = [ij for k in range(m+n) for ij in ((0,k), (m-1,k),(k,0), (k,n-1))]
        while save:
            i, j = save.pop()
            if 0<=i<m and 0<=j<n and board[i][j] == 'O':
                board[i][j] = 'S'
                save += (i-1,j), (i+1,j), (i,j+1), (i,j-1)

        board[:] = [['XO' [c=='S']  for c in row] for row in board]


# Leetcode 134. Gas Station
class canCompleteCircuit(object):
    def doit(self, gas, cost):
        """
        :type gas: List[int]
        :type cost: List[int]
        :rtype: int
        """
        start, end = len(gas)-1, 0
        sum = gas[start] - cost[start]
        while start > end:
            if sum >= 0:
                sum += gas[end] - cost[end]
                end += 1

            else:
                start -= 1
                sum ++ gas[start] - gas[end]

        return start if sum >= 0 else -1 
        

    def doit2(self, gas, cost):
        if len(gas) == 0 or len(gas) != len(cost):
            return 0

        status = map(operator.sub, gas, cost)

        for i, st in enumerate(status):
            j, amount = 0, 0
            if status[i] < 0:
                continue
            while j < len(status):
                index = j+i if index > len(status) else j+i - len(status)
                amount += status[index]
                if amout < 0:
                    break;
                j += 1
            
            if j == len(status) and amount >=0:
                return j

        return -1
            
        
        
        
# Leetcode 234. Palindrome Linked List
class isPalindromeList(object):
    def doit(self, head):
        """
        :type head: ListNode
        :rtype: bool
        """
        def reverseList(head):
            pass
            pre, next = None, None
            while head:
                next = head.next
                head.next = pre
                pre = head
                head = next
        
            return pre

        holder = ListNode(100)
        holder.next, slow, fast, odd = head, holder, holder, False
        while fast.next != None:
            fast = fast.next
            if fast.next:
                fast = fast.next
            else:
                odd = True
                break

            slow = slow.next
        
        Part1st, Part2nd = head, slow.next
        if odd:
            Part2nd = Part2nd.next

        Part2nd = reverseList(Part2nd)
    
        while Part2nd:
            if Part1st.val != Part2nd.val:
                return False
            Part1st = Part1st.next
            Part2nd = Part2nd.next

        return True 
        
            
# Leetcode 214. Shortest Palindrome
class shortestPalindrome(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        reversed_s = s[::-1]
        l = s + '#' + reversed_s

        prefixlen, i, P = 0, 1, [0 for x in range(len(l))]
        while i < len(l):
            if l[prefixlen] == l[i]:
                prefixlen += 1
                P[i] = prefixlen
                i += 1
            else:
                if prefixlen ==  0:
                    i += 1
                else:
                    while prefixlen > 0 and l[prefixlen] != l[i]:
                        prefixlen = P[prefixlen - 1]
            
        return reversed_s[:len(reversed_s) - P[len(P)-1]] + s


# Leetcode 564. Find the Closest Palindrome
class nearestPalindromic(object):
    def doit(self, n):
        """
        :type n: str
        :rtype: str
        """
        start, end, length = 0, len(n) - 1, len(n)
        while start < end:
            pass
            start += 1
            end -= 1




# Leetcode 409. Longest Palindrome        
class longestPalindrome(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        i, strMap, count = 0, {}, 0
        while i < len(s):
            if strMap.has_key(s[i]):
                del strMap[s[i]]
                count += 1
            else:
                strMap[s[i]] = i

            i += 1

        if len(strMap) == 0:
            return count * 2
        else:
            return count * 2 + 1

    def doit2(self, s):
        odds = sum(v & 1 for v in collections.Counter(s).values())
        return len(s) - odds + bool(odds)
        

# Leetfcode 141. Linked List Cycle
class hasCycle(object):
    def doit(self, head):
        """
        :type head: ListNode
        :rtype: bool
        """
        ref = ListNode(100) 
        slow, fast, ref.next = ref, ref, head
        
        while fast:

            slow = slow.next
            fast = fast.next
            if fast is None:
                return False
            else :
                fast = fast.next

            if slow == fast:
                return True
       
        return False

        
# Leetcode 142. Linked List Cycle II
class detectCycle(object):
    def doit(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        slow, fast = head, head
        while fast:
            slow = slow.next
            fast = fast.next
            if fast == None:
                return None
            else:
                fast = fast.next
            
            if slow == fast:
                break
        if fast == None:
            return False
    
        slow = head
        while slow != fast:
            slow = slow.next
            fast = fast.next

        return slow
        
# Leetcode 445. Add Two Numbers II
class addTwoNumbersLink(object):
    def doit(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        l1Stack, l2Stack = [], []
        while l1:
            l1Stack.append(l1.val)
            l1 = l1.next
        while l2:
            l2Stack.append(l2.val)
            l2 = l2.next

        prev, head, accum = None, None, 0
        while l1Stack or l2Stack:
            a, b = 0, 0
            if l1Stack:
                a = l1Stack.pop()
            if l2Stack:
                b = l2Stack.pop()

            val = (a + b + accum) % 10
            accum = (a + b + accum) / 10

            head = ListNode(val)
            head.next = prev
            prev = head

        if accum == 1:
            head = ListNode(accum)
            head.next = prev
           
        return head

    def doit2(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        stk1, stk2 = [], []
        while l1:
            stk1.append(l1.val)
            l1 = l1.next
        while l2:
            stk2.append(l2.val)
            l2 = l2.next

        prev, head = None, None
        sum = 0
        while stk1 or stk2:
            sum /= 10
            if stk1:
                sum += stk1.pop()
            if stk2:
                sum += stk2.pop()
            
            head = ListNode(sum % 10)
            head.next = prev
            prev = head

        if sum >= 10:
            head = ListNode(sum / 10)
            head.next = prev

        return head   


# 75. Sort Colors
# Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
class sortColors(object):
    
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        i, zero, second = 0, 0, len(nums)-1
        while i <= second:
            while nums[i] == 2 and i < second:
                nums[i], nums[second] = nums[second], nums[i]
                second -= 1
            
            while nums[i] == 0 and i > zero:
                nums[i], nums[zero] = nums[zero], nums[i]
                zero += 1
        
            i += 1
        

    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        i = 0
        while i < len(nums) and nums[i] == 0:
            i += 1
        s = i
        e = len(nums)-1
        while e >= 0 and nums[e] == 2:
            e -= 1

        if s >= e:
            return

        while i <= e:
            if nums[i] == 0:
                if s != i:
                    nums[s], nums[i] = nums[i], nums[s]
                    s += 1
                else :
                    s = i = i + 1
            elif nums[i] == 2:
                nums[e], nums[i] = nums[i], nums[e]
                e -= 1
            else :
                i += 1       
        

# Leetcode  148. Sort List
class sortList(object):
    def doit2(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        def kCup(start, end):
            if start == end:
                return
            
            head, kval, kpt = start, start.val, None
            
            while start.next and start.next != end:
               if start.next.val < kval:
                  nextI = start.next
                  a = nextI.next
                  kpt.next, nextI.next = nextI, kpt.next
                  kpt = kpt.next
                  start.next = a

               start = start.next
            
               
            newhead = head.next
            head.next, kpt.next = kpt.next, head
            
            s1 = kCup(newhead, kpt.next)
            s2 = kCup(kpt.next , end)

            return newhead
        
        result = ListNode(0)
        result.next = head 
        kCup(result, None)
        return result.next

    # merge sort
    def doit(self, head):
        def merge(l1, l2):
            result = ListNode(100)
            p = result

            while l1 and l2:
                if l1.val < l2.val:
                    p.next = l1
                    l1 = l1.next
                else:
                    p.next = l2
                    l2 = l2.next
                p = p.next

            if l1:
                p.next = l1
            if l2:
                p.next = l2
            
            return result.next
        
        def mergeSort(head):
            if head == None or head.next == None:
                return head

            slow, fast, prev = head, head, None
            while fast:
                prev = slow
                slow = slow.next
                fast = fast.next
                if fast:
                   fast = fast.next
        
            prev.next = None
            s1 = mergeSort(head)
            s2 = mergeSort(slow)

            return merge(s1, s2)
      
        return mergeSort(head)


# Leetcode 147. Insertion Sort List
class insertionSortList(object):
    def doit(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        if head == None or head.next == None:
            return head
        
        st = ListNode(100)
        first, st.next, head.next = head.next, head, None
        while first:
            next = first.next
            pt, pre = st.next, st
            while pt:
                if pt.val > first.val:
                    pre.next, first.next = first, pre.next
                    break
                pre = pt
                pt = pt.next
                
            if pt == None :
                pre.next, first.next = first, None

            first = next

        return st.next

    def doit2(self, head):
        if head == None or head.next == None:
            return head

        helper = ListNode(200)
        pre, cur, helper.next = helper, head, head
        while cur != None:
            next = cur.next
            while pre.next != None and pre.next.val < cur.val:
                pre = pre.next
            
            if pre.next != cur:
                pre.next, cur.next = cur, pre.next
            pre = helper
            cur = next

        return helper.next

    # Best Solution
    def doit3(self, head):
        if not head:
            return None
            
        p = dummy = ListNode(0)
        cur = dummy.next = head
        while cur and cur.next:
            val = cur.next.val
            if cur.val < val:
                cur = cur.next
                continue
            if p.next.val > val:
                p = dummy
            while p.next.val < val:
                p = p.next
            new = cur.next
            cur.next = cur.next.next
            new.next = p.next
            p.next = new
        return dummy.next
        

# Leetcode 30. Substring with Concatenation of All Words
class findSubstring(object):
    def doit(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        pass
                 
# Leetcode 234. Palindrome Linked List
class isPalindrome(object):
    def doit(self, head):
        """
        :type head: ListNode
        :rtype: bool
        """
        pass
       

# Leetcode 101. Symmetric Tree
class isTreeSymmetric(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        def check(rootA, rootB):
            if rootA == rootB == None:
                return True

            if rootA == None or rootB == None or rootA.val != rootB.val:
                return False

            return check(rootA.right, rootB.left) and check(rootA.left, rootB.right)
        if root == None:
            return True

        return check(root.left, root.right)

# Leetode 102. Binary Tree Level Order Traversal
class levelOrderTree(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        if not root:
            return []
        buff, result = [root], []
        while buff:
            temp, level = [], []
            for x in buff:
                if x.right:
                    temp.append(x.right)
                if x.left:
                  temp.append(x.left)

            while buff:
                level.append(buff.pop().val)

            result.append(level)
            buff = temp

        return result

    def doit2(self, root):
        if not root:
            return []
        res , level = [],[root]
        
        while level:
            res.append([node.val for node in level])
            
            temp = []
            
            for node in level:
                temp.extend([node.left,node.right])
            
            level = [node for node in temp if node]
            
            
        return res


# Leetcode 103. Binary Tree Zigzag Level Order Traversal
class zigzagLevelOrderTree(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        if not root:
            return []

        buff, result, leftToRight = [root], [], False
        while buff:
            result.append([node.val for node in buff if node])

            temp = []

            for node in reversed(buff):
                if leftToRight:
                    temp.extend([node.left, node.right])
                else:
                    temp.extend([node.right, node.left])

            leftToRight = ~leftToRight
            buff = [node for node in temp if node]
            

        return result

    def doit2(self, root):
        if root == None:
            return []

        statck = [(root, 0)]
        ind = 0
        rtn = []
        tmpl = []
        while statck != []:
            node, i = statck.pop(0)
            if i == ind:
                tmpl.append(node.val)
            else:
                rtn.append(tmpl)
                ind = i
                tmpl = [node.val]
            if node.left:
                statck.append((node.left, i + 1))
            if node.right:
                statck.append((node.right, i + 1))
        rtn.append(tmpl)
        for i in range(len(rtn)):
            if i % 2 == 1:
                rtn[i] = list(reversed(rtn[i]))
        return rtn
        
            

# Leetcode 105. Construct Binary Tree from Preorder and Inorder Traversal
class buildTreeWithPreorderAndInorder(object):
    def doit(self, preorder, inorder):
        """
        :type preorder: List[int]
        :type inorder: List[int]
        :rtype: TreeNode
        """
        def buildTree(preorder, inorder):
            if len(preorder) == 0:
                return None

            i, root, val = 0, TreeNode(preorder[0]), preorder[0]
            if len(preorder) == 1:
                return root

            while i < len(inorder):
                if inorder[i] == val:
                    break
                i += 1

            root.left = buildTree(preorder[1:i+1], inorder[0:i])
            root.right = buildTree(preorder[i+1:], inorder[i+1:])

            return root

        return buildTree(preorder, inorder)

    def doit2(self, preorder, inorder):
        """
        :type preorder: List[int]
        :type inorder: List[int]
        :rtype: TreeNode
        """
        l = len(preorder)
        if l==0:
            return None
            
        root = TreeNode(preorder[0])
        index = 0
        stack = [root]
        
        for i in xrange(1,l):
            node = stack[-1]
            if node.val != inorder[index]:
                node.left = TreeNode(preorder[i])
                node = node.left
                stack.append(node)
            else:
                while len(stack)!=0 and stack[-1].val==inorder[index]:
                    node = stack.pop()
                    index += 1
                node.right = TreeNode(preorder[i])
                node = node.right
                stack.append(node)
                
        return root
            
            
# Leetcode 106. Construct Binary Tree from Inorder and Postorder Traversal
class buildTreeWithInorderAndPostorder(object):
    def doit(self, inorder, postorder):
        """
        :type inorder: List[int]
        :type postorder: List[int]
        :rtype: TreeNode
        """
        def buildTree(inorder, postorder):
            if not inorder:
                return None

            val = postorder[len(postorder)-1]
            i, root = 0, TreeNode(val)
            if len(inorder) == 1:
                return root

            while i < len(inorder):
                if inorder[i] == val:
                    break
                i += 1

            root.left = buildTree(inorder[0:i], postorder[0:i])
            root.right = buildTree(inorder[i+1:], postorder[i:len(postorder)-1])

            return root

        return buildTree(inorder, postorder)


    def doit2(self, inorder, postorder):
        """
        :type inorder: List[int]
        :type postorder: List[int]
        :rtype: TreeNode
        """
        if not inorder:
            return None

        root = TreeNode(inorder[-1])
        

        


# Leetcode  107. Binary Tree Level Order Traversal II        
class levelOrderBottom(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """
        def buildLevel(nodeList, result):
            if not nodeList:
                return

            temp = []
            for node in nodeList:
                if node and node.left:
                    temp.append(node.left)
                if node and node.right:
                    temp.append(node.right)
            
            buildLevel(temp, result)

            temp = [node.val for node in nodeList if node]
            if temp:
                result.append(temp)

            return
            
        nodelist, result = [root], []
        buildLevel(nodelist, result)
        return result


        
# Leetcode 108. Convert Sorted Array to Binary Search Tree        
class sortedArrayToBST(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: TreeNode
        """
        def buildTree(nums):
            if not nums:
                return None
            
            if len(nums) == 1:
                return TreeNode(nums[0])


            mid = len(nums) / 2
            root = TreeNode(nums[mid])
            root.left = buildTree(nums[0:mid])
            root.right = buildTree(nums[mid+1:])

            return root

        return buildTree(nums)

# Leetcode 109. Convert Sorted List to Binary Search Tree
class sortedListToBST(object):
    def doit(self, head):
        """
        :type head: ListNode
        :rtype: TreeNode
        """ 
        def buildTree(start, end, node):
            if start > end or not node:
                return None

            mid = (start + end) / 2
            treeleft = buildTree(start, mid-1, node)

            cur = TreeNode(node.val)
            cur.left = treeleft
            node = node.left

            cur.right = buildTree(mid + 1, end, node)
            
            return cur

        size, cur = 0, head
        while cur:
            size += 1
            cur = cur.next

        return buildTree(0, size-1, head)


# Leetcode 110. Balanced Binary Tree
class isBalancedTree(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        def dfsHeight(root):
            if not root:
                return 0

            leftHeight = dfeHeight(root.left)
            if leftHeight == -1:
                return -1

            rightHeight = dfsHeight(root.right)
            if rightHeight == -1:
                return -1


            if abs(leftHeight - rightHeight) > 1 :
                return -1

            return max(leftHeight, maxHeight) + 1


        return dfsHeight(root) != -1


# Leetcode 111. Minimum Depth of Binary Tree
class minDepthTree(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def dfsDepth(node):
            if not node:
                return 0

            if not node.left:
                return dfsDepth(node.right)

            if not node.right:
                return dfsDepth(node.left)

            return min(dfsDepth(node.left), dfsDepth(node.right)) + 1


        return dfsDepth(root)


# Leetcode 112. Path Sum
class hasPathSum(object):
    def doit(self, root, sum):
        """
        :type root: TreeNode
        :type sum: int
        :rtype: bool
        """
        def calcDepth(node, sum):
            if not node:
                return False

            if sum - node.val == 0 and not node.right and not node.left:
                return True

            return calcDepth(node.right, sum - node.val) or calcDepth(node.left, sum - node.val)
        

        return calcDepth(root, sum)


# Leetcode 113. Path Sum II
class pathSum(object):
    def doit(self, root, sum):
        """
        :type root: TreeNode
        :type sum: int
        :rtype: List[List[int]]
        """
        def buildPath(node, sum, buff, result):
            if not node :
                return

            buff.append(node.val)
            if sum - node.val == 0 and not node.right and not node.left:
                result.append(buff[:])
                buff.pop()
                return

            sum -= node.val

            buildPath(node.left, sum, buff, result)

            buildPath(node.right, sum, buff, result)

            buff.pop()

        result = []
        buildPath(root, sum, [], result)                        
        return result


# Leetcode 114. Flatten Binary Tree to Linked List
class flatten(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """
        if not root:
            return root

        self.prev = root
        self.doit(root.left)
        temp = root.right
        root.right = root.left
        root.left = None
        self.prev.right = temp
        self.doit(temp)

    def doit2(self, root):
        buff, node = [], root
        while node:
            while node and (node.left or node.right):
                if not node.left and node.right:
                    node = node.right
                    continue

                if node.right:
                    buff.append(node.right)

                node.right, node.left = node.left, None
                node = node.right

            if buff:
                temp = buff.pop()
                node.right = temp

            node = node.right

        return root


# Leetcode 116. Populating Next Right Pointers in Each Node
class connectToNextRight:
    # @param root, a tree link node
    # @return nothing
    def doit(self, root):
        if not root:
            return None

        buff = [root]
        while buff:
            temp = []
            for x in buff:
                temp.extend([x.left, x.right])

            i = 0
            while i < len(buff) - 1:
                buff[i].next = buff[i+1]
                i += 1

            buff = [x for x in temp if x]

    def doit2(self, root):
        while root and root.left:
            next = root.left
            while root:
                root.left.next = root.right
                root.right.next = root.next and root.next.left
                root = root.next
            root = next


# Leetcode 117. Populating Next Right Pointers in Each Node II                
class TreeLinkNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        self.next = None

class connectToNextRightII:
    # @param root, a tree link node
    # @return nothing
    def doit(self, root):
        current = root
        while current:
            head, pre = None, None
            while current:
                if current.left:
                    if not pre:
                        head = current.left
                    else:
                        pre.next = current.left
                    pre = current.left

                if current.right:
                    if not pre:
                        head = current.right
                    else:
                        pre.next = current.right
                    pre = current.right

                current = current.next

            current = head


# Leetcode 118. Pascal's Triangle
class generatePascalTriangle(object):
    def doit(self, numRows):
        """
        :type numRows: int
        :rtype: List[List[int]]
        """
        if numRows == 0:
            return []

        i, result = 1, [[1]]
        while i < numRows:
            temp, j = [0 for x in range(i+1)], 0
            while j < len(temp):
               if j - 1 >= 0:
                    temp[j] += result[i-1][j-1]
               if j < len(result[i-1]):
                    temp[j] += result[i-1][j]  
               j += 1
            result.append(temp[:])
            i += 1

        return result

    # explanation: Any row can be constructed using the offset sum of the previous row. Example:
    #     1 3 3 1 0 
    #  +  0 1 3 3 1
    #  =  1 4 6 4 1
    def generate(self, numRows):
        res = [[1]]
        for i in range(1, numRows):
            res += [map(lambda x, y: x+y, res[-1] + [0], [0] + res[-1])]
        return res[:numRows]


# Leetcode 119. Pascal's Triangle II
class getRowOfPascalTriangle(object):
    def doit(self, rowIndex):
        """
        :type rowIndex: int
        :rtype: List[int]
        """
        i, res = 0, [1]
        while i < rowIndex:
            res = map(lambda x, y: x+y, res + [0], [0] + res)
            i += 1

        return res

# leetcode 120. Triangle
class minimumTotalOfTriangle(object):
    def doit2(self, triangle):
        """
        :type triangle: List[List[int]]
        :rtype: int
        """
        def buildPath(triangle, row, line, sum):
            if row >= len(triangle) or line >= len(triangle[row]):
                return sys.maxint

            if row == len(triangle)-1:
                sum += triangle[row][line]
                return sum

            sum += triangle[row][line]
            return min( buildPath(triangle, row + 1, line, sum), 
                        buildPath(triangle, row + 1, line + 1, sum))

        return buildPath(triangle, 0, 0, 0)

    def doit(self, tri):
        DP = [sys.maxint for x in range(len(tri[-1]))]
        i, DP[0] = 1, tri[0][0]

        while i < len(tri):
            temp, j = DP[:], 1
            temp[0] += tri[i][0]
            while j < len(tri[i]): 
                temp[j] = min(DP[j-1], DP[j]) + tri[i][j]
                j += 1
            DP = temp[:]
            i += 1

        minVal = DP[0]
        for x in DP:
            if minVal > x:
                minVal = x

        return minVal


# Leetcode 129. Sum Root to Leaf Numbers        
class sumNumbersTree(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def iterateTree(node, num, sum):
            if not node:
                return

            num = num * 10 + node.val
            if not node.left and not node.right:
                sum.append(num)
                return            

            iterateTree(node.left, num, sum)

            iterateTree(node.right, num, sum)
        
        #
        total = []
        iterateTree(root, 0, total)
        return sum(total)

    def doit2(self, root):
        if not root:
            return 0
        stack, res = [(root, root.val)], 0
        while stack:
            node, value = stack.pop()
            if node:
                if not node.left and not node.right:
                    res += value
                if node.right:
                    stack.append((node.right, value*10+node.right.val))
                if node.left:
                    stack.append((node.left, value*10+node.left.val))
        return res        
                


# Leetcode 121. Best Time to Buy and Sell Stock
class maxProfitOfStock(object):
    def doit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        n = len(prices)
        if n < 2:
            return 0
        
        diffArray=[0 for i in range(n-1)]
        current_sum, max_sum = 0, 0
        
        for i in range(n-1):
            diffArray[i]=prices[i+1]-prices[i]
            
        for i in range(n-1):
            current_sum +=diffArray[i]
            if current_sum > max_sum:
                max_sum = current_sum
            if current_sum < 0:
                current_sum = 0

        return max_sum
        
    def doit2(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """  
        minVal, i, res = sys.maxint, 0, 0
        while i < len(prices):
            if minVal > princes[i]:
                minVal = prices[i]

            if prices[i] - minVal > res:
                res = prices[i] - minVal

            i += 1

        return res
            
# Leetcode 122. Best Time to Buy and Sell Stock II
class maxProfitOfStockII(object):
    def doit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        i, diff, sum = 1, 0, 0
        while i < len(prices):
            diff = prices[i] - prices[i-1]
            if diff > 0:
                sum += diff
            i += 1

        return sum

    def doit2(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        total = 0
        num_prices = len(prices)
        for price_idx in xrange(num_prices - 1):
            if prices[price_idx + 1] > prices[price_idx]:
                total += prices[price_idx + 1] - prices[price_idx]

        return total

# Leetcode 123. Best Time to Buy and Sell Stock III
class maxProfitOfStockIII(object):
    def doit2(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        if not prices:
            return 0

        leftSidePrices, rightSidePrices = [], []
        i, minVal, maxVal = 0, sys.maxint, -sys.maxint
        while i < len(prices):
            if minVal > prices[i]:
                minVal = prices[i]

            if maxVal < prices[i] - minVal:
                maxVal = prices[i] - minVal
            leftSidePrices.append(maxVal)
            i += 1

        i, maxP, maxVal = len(prices)-1, -sys.maxint, -sys.maxint
        while i >= 0:
            if maxVal < prices[i]:
                maxVal = prices[i]

            if maxP < maxVal - prices[i]:
                maxP =  maxVal - prices[i]

            rightSidePrices = [maxP] + rightSidePrices
            i -= 1

        i, sum = 0, rightSidePrices[0]
        while i < len(prices) - 1:
            if sum < leftSidePrices[i] + rightSidePrices[i+1]:
                sum = leftSidePrices[i] + rightSidePrices[i+1]
            i += 1

        return sum

    def doit3(self, prices):
        hold1, hold2 = -sys.maxint, -sys.maxint
        release1, release2 = 0, 0
        
        for num in prices:
            release2 = max(release2, hold2 + num)
            hold2 = max(hold2, release1 - num)
            release1 = max(release1, hold1+num)
            hold1 = max(hold1, -num)

        return release2

    def doit(self, prices):
        k = 2
        D = [[0] * len(prices)] * (k+1)
        i , maxPro = 1, 0

        while i < k:
            j,  tmpMax = 1, D[i-1][0] - prices[0]
            while j < len(prices):
                # f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) { jj in range of [0, ii-1] }
                D[i][j] = max(D[i][j-1], prices[j] + tmpMax)
                # max value of max(f[k-1, jj] - prices[jj])
                tmpMax = max(tmpMax, D[i-1][j] - prices[j])
                # max value
                maxPro = max(D[i][j], maxPro)
                j += 1
            i += 1

        return maxPro

            
# Leetcode 257. Binary Tree Paths
class binaryTreePaths(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[str]
        """
        pass
        

        
# Leetcode 437. Path Sum III
class pathSum(object):
    def doit(self, root, sum):
        """
        :type root: TreeNode
        :type sum: int
        :rtype: int
        """ 
        pass                           
            


# Leetcode 150. Evaluate Reverse Polish Notation
class evalRPN(object):
    def doit(self, tokens):
        """
        :type tokens: List[str]
        :rtype: int
        """
        stack = []
        
# Leetcode 143. Reorder List
class reorderList(object):

    def doit(self, head):
        L1 = ListNode(100)
        L1.next, Mid, fast = head, L1, head
        while fast :
           fast = fast.next
           if not fast:
              Mid = Mid.next
              break
           fast = fast.next
           Mid = Mid.next

        sec, Mid.next, L2 = Mid.next, None, ListNode(200)
        while sec:
            s = sec.next
            sec.next, L2.next = L2.next, sec
            sec = s

        fir, sec = head, L2.next
        while fir and sec:
            f, s = fir.next, sec.next
            fir.next, sec.next = sec, fir.next
            sec, fir = s, f  

        L1.next = None
        return head

    def doit2(self, head):
        if head is None or head.next is None:
            return
            
        pfast = head; pslow = head
        
        while pfast.next and pfast.next.next:
            pfast = pfast.next.next
            pslow = pslow.next
        pfast = pslow.next
        pslow.next = None
        
        pnext = pfast.next
        pfast.next = None
        while pnext:
            q = pnext.next
            pnext.next = pfast
            pfast = pnext
            pnext = q
            
        tail = head
        while pfast:
            pnext = pfast.next
            pfast.next = tail.next
            tail.next = pfast
            tail = tail.next.next
            pfast = pnext


# Definition for singly-linked list with a random pointer.
class RandomListNode(object):
     def __init__(self, x):
         self.label = x
         self.next = None
         self.random = None

# Leetcode 138. Copy List with Random Pointer
class copyRandomList(object):

    def doit(self, head):
        """
        :type head: RandomListNode
        :rtype: RandomListNode
        """
        pt, next = head, None
        while pt:
            next = pt.next
            copy = RandomListNode(pt.label)
            pt.next, copy.next = copy, next
            pt = next

        pt = head
        while pt:
            if pt.random:
                pt.next.random = pt.random.next
            pt = pt.next.next

        NewList, pt = head.next, head
        while pt:
            next1, next2 = pt.next, pt.next.next
            if not next2:
                pt.next, next1.next = None, None
                break
            pt.next, next1.next = next2, next2.next
            pt = next2
                
        return NewList

    def doit2(self, head):
        #The algorithm is composed of the follow three steps which are also 3 iteration rounds.
        #
        #Iterate the original list and duplicate each node. The duplicate
        #of each node follows its original immediately.

        #Iterate the new list and assign the random pointer for each
        #duplicated node.

        #Restore the original list and extract the duplicated nodes.
        # make copy of each node
        p = head
        while p != None:
            p_next = p.next
            
            copy = RandomListNode(p.label)
            # append copy of p right next to p 
            p.next = copy
            copy.next = p_next
            
            # move to next node 
            p = p_next
          
        # assign random pointers for the copy nodes 
        p = head
        while p != None:
            if p.random != None:
                # p.next is a copy of p and p.random.next is a copy of p.random
                # since p's random is p.random, p.next.random is p.random.next
                p.next.random = p.random.next
                
            # move to next original node. p.next is p's copy node and 
            # p.next.next is p's next original node 
            p = p.next.next
            
        # restore original node list and extract copy node list 
        aux_head = RandomListNode(0)
        p_copy = aux_head
        p = head 
        while p != None:            
            # extract p's copy node and append it to extracted list 
            p_copy.next = p.next
            p_copy = p_copy.next
            
            # skip p's copy node to restore orignial list 
            p.next = p.next.next 
            # move to next original node 
            p = p.next
            
        return aux_head.next


# Leetcode 139. Word Break
class wordBreak(object):
    # DP solution
    def doit(self, s, wordDict):
        DP = [False] * len(s)

        for i in range(len(s)):
            for w in wordDict:
                if w == s[i-len(w)+1 : i+1] and (DP[i-len(w)] or i - len(w) == -1):
                    DP[i] = True

        return DP[-1]
         
        
    # recusion solution
    def doit2(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
        """    
        def checkWordInDict(s, wordDict, res):
            rtv = False
            for each in wordDict:
                if each == s[0:len(each)]:
                    if len(s[len(each):]) == 0 or checkWordInDict(s[len(each):], wordDict, res):
                        rtv = True
                        break

            return rtv
            
        result = []
        return checkWordInDict(s, wordDict, result)

# Leetcode 140. Word Break II
class wordBreakII(object):
    def doit(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: List[str]
        """
        None
        

# Leetcode 150. Evaluate Reverse Polish Notation            
class evalRPN(object):
    def doit(self, tokens):
        """
        :type tokens: List[str]
        :rtype: int
        """
        stack, i = [], 0
        while i < len(tokens):

            if tokens[i] in ('+', '-', '*', '/'):
                a1, a2, res = stack.pop(), stack.pop(), 0
                if tokens[i] == '+':
                    res = a1 + a2
                elif tokens[i] == '-':
                    res = a2 - a1
                elif tokens[i] == '*':
                    res = a1 * a2
                elif tokens[i] == '/':
                    res = int(float(a2) / a1)
                stack.append(res)
            else:
                stack.append(int(tokens[i]))
            i += 1
            
        return stack.pop()

# Leetcode 124. Binary Tree Maximum Path Sum
class maxPathSum(object):
   def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def maxPath(node):
            if not node :
                return -sys.maxint, -sys.maxint

            l, maxl = maxPath(node.left)
            r, maxr = maxPath(node.right)

            T = max(node.val, node.val + max(l, r))
            return T, max(T, l + r + node.val, max(l, r), max(maxr, maxl))
        
        return  max(maxPath(root))

   def doit2(self, node):
        """
        :type root: TreeNode
        :rtype: int
        """
        def max_path(self, node):
            if node == None:
                return 0, -9999999

            max_path_from_left, max_path_in_left = self.max_path(node.left)
            max_path_from_right, max_path_in_right = self.max_path(node.right)

            max_path_from_current = max(\
                max_path_from_left + node.val,\
                node.val, \
                max_path_from_right + node.val)

            max_path = max(max_path_in_left, max_path_in_right, \
                      max_path_from_left + node.val + max_path_from_right, \
                      max_path_from_current)
            return max_path_from_current, max_path

        _, max_path = self.max_path(root)
        return max_path
                        
# Leetcode 126. Word Ladder II
class findLadders(object):
    # better way
    def doit2(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: List[List[str]]
        """
        if endWord not in wordList:
            return []
        
        def construct_paths(source, dest, tree):
            if source == dest: 
                return [[source]]
            return [[source] + path for succ in tree[source]
                                    for path in construct_paths(succ, dest, tree)]

        def add_path(tree, word, neigh, is_forw):
            if is_forw: tree[word]  += neigh,
            else:       tree[neigh] += word,

        def bfs_level(this_lev, oth_lev, tree, is_forw, words_set):
            if not this_lev: return False
            if len(this_lev) > len(oth_lev):
                return bfs_level(oth_lev, this_lev, tree, not is_forw, words_set)
            for word in (this_lev | oth_lev):
                words_set.discard(word)
            next_lev, done = set(), False
            while this_lev:
                word = this_lev.pop()
                for c in string.ascii_lowercase:
                    for index in range(len(word)):
                        neigh = word[:index] + c + word[index+1:]
                        if neigh in oth_lev:
                            done = True
                            add_path(tree, word, neigh, is_forw)
                        if not done and neigh in words_set:
                            next_lev.add(neigh)
                            add_path(tree, word, neigh, is_forw)
            return done or bfs_level(next_lev, oth_lev, tree, is_forw, words_set)
                            
        tree, path, paths = collections.defaultdict(list), [beginWord], []
        bfs_level(set([beginWord]), set([endWord]), tree, True, set(wordList))

        return construct_paths(beginWord, endWord, tree)

    def doit(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: List[List[str]]
        """
        nodeNeighbors, distance, solution = dict(), dict(), []

        def bfs(start, end, wl, nodeNeighbors, distance):
            for item in wl:
                nodeNeighbors[item] = []

            queue, distance[start], found, temp = [start], 0, False, []
            while not found and queue:
                for item in queue:
                    curDistance = distance[item]
                    wl.discard(item)
                    neighbor = getNeighbor(item, wl)

                    for j in neighbor:
                        nodeNeighbors[item].append(j)

                        if j not in distance:
                            distance[j] = curDistance + 1
                            if j == end:
                                found = True
                            else:
                                temp.append(j)
                queue = temp

            return queue
                    
        def getNeighbor(node, wl):
            rv = []
            i = 0
            while i < len(node):
                for j in 'abcdefghijklmnopqrstuvwxyz':
                    temp = node[:i] + j + node[i+1:]
                    if temp != node and temp in wl:
                        rv.append(temp)
                i += 1        
            return rv

        def dfs(start, end, nodeNeighbors, distance, rv, solution):
            rv.append(start)
        
            if end == start:
                solution.append(rv[:])
            else:
                for item in nodeNeighbors[start]:
                    if distance[item] == distance[start] + 1:
                        dfs(item, end, nodeNeighbors, distance, rv, solution)
            rv.pop()


        wl = set(wordList)
        if beginWord not in wl:
            wl.add(beginWord)

        if endWord not in wl:
            return []
        
        bfs(beginWord, endWord, wl, nodeNeighbors, distance)
        dfs(beginWord, endWord, nodeNeighbors, distance, [], solution)
        
        return solution
        
        

# Leetcode 127. Word Ladder
class ladderLength(object):
    def doit(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        wl = set(wordList)
        if endWord in wl:
            wl.remove(endWord)
        else :
            return 0

        if beginWord in wl:
            wl.remove(beginWord)

        ladder = 2
        preWord, nextWord = set([beginWord]), set([endWord])
        while preWord and nextWord:
            if len(preWord) < len(nextWord):
                preWord, nextWord = nextWord, preWord
        
            temp = set()
            for t in nextWord:
                # iter word
                i = 0
                while i < len(t):
                    for j in 'abcdefghijklmnopqrstuvwxyz':
                        word = t[:i] + j + t[i+1:]
                        if word in preWord:
                            return ladder
                        if word in wl:
                           temp.add(word)
                           wl.remove(word)
                    i+= 1
            nextWord, temp = temp, nextWord
            ladder += 1

        return 0
       
                
#130. Surrounded Regions
class solveContaining(object):
    def doit(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        n, half, i = len(board), len(board)/2, 0

        #while i < half:
        #    xe, ye = n - i, n - i
        #    while xe < :
                
        #    i += 1 

        
        
#151 Reverse Words in a String
class reverseWords(object):
    def doit(self, s):
        i, res, tempt, lastWord = 0, '', '', ''
        while i < len(s):
            if s[i] != ' ':
                tempt += s[i]
            else :
                if tempt:
                    res = s[i] + tempt + res
                    tempt,  lastWord = '', ' '
                #else :
                #    if lastWord != ' ' and res:
                #        res = s[i] + res
            i += 1

        return res

#152 Maximum Product Subarray
class maxProduct(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        maxherepre, minherepre, maxcur, i = nums[0], nums[0], nums[0], 0

        while i < len(nums):
            maxhere = max(max(maxherepre * nums[i], minherepre * nums[i]), nums[i])
            minhere = min(min(maxherepre * nums[i], minherepre * nums[i]), nums[i])
            maxcur = max(maxhere, maxcur)
            maxherepre = maxhere
            minherepre = minhere
            i += 1

        return maxcur

    def doit3(self, nums):
        i, r, maxV, minV = 1, nums[0], nums[0], nums[0]

        while i < len(nums):
            if nums[i] < 0:
                maxV, minV = minV, maxV

            maxV = max(maxV * nums[i], nums[i])
            minV = min(minV * nums[i], nums[i])

            r = max(maxV, r)
            i += 1
        return r
 

    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        D, i, maxV, s, step = [1] * len(nums), 0, -1000, 0, 0 

        while i < len(nums):
            j = 0
            while j < len(nums):
                if j + i < len(nums):
                    D[j] = D[j] * nums[j+i]
                    if D[j] > maxV:
                        maxV, s, step = D[j], j, i
                j += 1
            i += 1

        return maxV
        
# 71 Simplify Path
# Given an absolute path for a file (Unix-style), simplify it.
# For example,
# path = "/home/", => "/home"
# path = "/a/./b/../../c/", => "/c"
class simplifyPath(object):
    def doit(self, path):
        places = [p for p in path.split("/") if p!="." and p!=""]
        stack = []
        for p in places:
            if p == "..":
                if len(stack) > 0:
                    stack.pop()
            else:
                stack.append(p)
        return "/" + "/".join(stack)

    def doit(self, path):
        segement, temp = [], path.split('/')
        for i in temp:
            if i == '.':
                continue
            elif i == '..':
                segement and segement.pop()
            elif i == '':
                continue
            else:
                segement.append(i)

        return '/' + '/'.join(segement)
        #rv = ''
        #for i in segement:
        #    rv += '/' + i 
        
        #return '/' if not rv else rv

    def doit1(self, path):
        """
        :type path: str
        :rtype: str
        """
        segment, temp = [], ""
        
        for i in path:
            if i == '/':
                if temp == '..':
                    segment and segment.pop()
                elif temp == '.':
                    temp = ''
                elif temp:
                    segment.append(temp)
                    temp = ''
                continue
            temp += i

        if temp:
            segment.append(temp)
        rv = '/'
        for item in segment:
            rv += '/' + item

        return rv
        
                       
#153. Find Minimum in Rotated Sorted Array
class findMin153(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i = 0
        while i < len(nums) - 1:
            if nums[i] > nums[i+1]:
                break
            i += 1

        if i == len(nums) - 1:
            return nums[0]
            
        return nums[i + 1]                

#154. Find Minimum in Rotated Sorted Array II
class findMin154(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i, minVal = 0, nums[0]
        while i < len(nums) - 1:
            if nums[i] > nums[i+1] and nums[i+1] < minVal:
                minVal = nums[i+1]
            i += 1
         
        return minVal

#155. Min Stack
class MinStack(object):

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.g = []

    def push(self, x):
        """
        :type x: int
        :rtype: void
        """
        curMin = self.getMin()
        if curMin == None or x < curMin:
            curMin = x
        self.g.append((x, curMin))
        

    def pop(self):
        """
        :rtype: void
        """
        if not self.g :
            return None
        return self.g.pop()[0]
        

    def top(self):
        """
        :rtype: int
        """
        if not self.g :
            return None
        return self.g[len(self.g)-1][0]

    def getMin(self):
        """
        :rtype: int
        """
        if not self.g :
            return None
        return self.g[len(self.g)-1][1]
        



# 160. Intersection of Two Linked Lists
# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class getIntersectionNode(object):

    def doit(self, headA, headB):
        if headA is None or headB is None:
            return None
        pa, pb = headA, headB
        
        while pa is not pb:
            pa = headB if pa is None else pa.next
            pb = headA if pb is None else pb.next

        return pa

    def doit2(self, headA, headB):
        """
        :type head1, head1: ListNode
        :rtype: ListNode
        """
        step1, step2, hA, hB = 0, 0, headA, headB
        while hA.next:
            hA = hA.next
            step1 += 1

        while hB.next:
            hB = hB.next
            step2 += 1

        if hA != hB:
            return None

        hmax, hmin = headA, headB
        if step2 > step1:
            hmax, hmin = hB, hA
        else:
            hmax, hmin = hA, hB

        i = 0
        while i < abs(step2 - step1):
            hmax = hmax.next
            i += 1

        while hmax and hmin:
            if hmax == hmin:
                break
            hmax = hmax.next
            hmin = hmin.next
            
        return hmax
         
            

#162. Find Peak Element
class findPeakElement(object):
    # O(logN)
    # num[i] ≠ num[i+1]
    #If num[i-1] < num[i] > num[i+1], then num[i] is peak
    #If num[i-1] < num[i] < num[i+1], then num[i+1...n-1] must contains a peak
    #If num[i-1] > num[i] > num[i+1], then num[0...i-1] must contains a peak
    #If num[i-1] > num[i] < num[i+1], then both sides have peak
    def doit(self, nums):
        def checkPeak(nums, s, e):
            if s == e:
                return s
            elif s + 1 == e:
                return s if nums[s] > nums[e] else e 

            mid = (s + e) / 2
            if nums[mid-1] < nums[mid] > nums[mid+1] :
                return mid
            elif nums[mid-1] < nums[mid] < nums[mid+1]:
                return checkPeak(nums, mid+1, e)
            elif nums[mid-1] > nums[mid] > nums[mid+1]:
                return checkPeak(nums, s, mid)
            elif nums[mid-1] > nums[mid] < nums[mid+1]:
                s = checkPeak(nums, s, mid)
                if s:
                    s = checkPeak(nums, mid, e)
                return s
            else:
                return None

        return checkPeak(nums, 0, len(nums) - 1) 

    # O(n)
    def doit2(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i, peak, ispeak = 0, 0, True
        while i < len(nums) - 1:
            if nums[i] > nums[i+1] and ispeak:
                return i

            ispeak = True if nums[i+1] > nums[i] else False
            i += 1

        return i if ispeak else None        


##164. Maximum Gap
#class Solution(object):
#    def maximumGap(self, nums):
#        """
#        :type nums: List[int]
#        :rtype: int
#        """
#        if len(nums) < 2:
#            return 0

#        None

#165. Compare Version Numbers
class compareVersion(object):
    def doit(self, version1, version2):
        """
        :type version1: str
        :type version2: str
        :rtype: int
        """ 
        ver1, ver2 = (map(int, v.split('.')) for v in (version1, version2))
        d = len(ver2) - len(ver1)
        return cmp(ver1 + [0]*d, ver2 + [0]*-d)
        


#167. Two Sum II - Input array is sorted
class twoSumSorted(object):
    def doit2(self, numbers, target):
        s, e = 0, len(numbers) - 1
        while s < e:
            if numbers[s] + numbers[e] == target:
                return [s+1, e+1]
            elif numbers[s] + numbers[e] > target:
                e = (s+e)/2
            else:
                s += 1

        return [0, 0]        

    def doit(self, numbers, target):
        """
        :type numbers: List[int]
        :type target: int
        :rtype: List[int]
        """
        s, e = 0, len(numbers)-1
        while s < e:
            mid = s + (e-s)/2
            if numbers[mid] == target:
                break
            elif numbers[mid] > target:
                e = mid - 1
            else:
                s = mid + 1
        s, e = 0, min(s, e)


        s, e = 0, len(numbers) - 1
        while s < e:
            if numbers[s] + numbers[e] == target:
                return [s+1, e+1]
            elif numbers[s] + numbers[e] > target:
                e -= 1
            else:
                s += 1

        return [0, 0]


# Leetcode 237. Delete Node in a Linked List
class deleteNode(object):
    def doit(self, node):
        """
        :type node: ListNode
        :rtype: void Do not return anything, modify node in-place instead.
        """
        node.val = node.next.val
        node.next = node.next.next
        
        
    
        
#168. Excel Sheet Column Title
    #1 -> A
    #2 -> B
    #3 -> C
    #...
    #26 -> Z
    #27 -> AA
    #28 -> AB 
class convertToTitle(object):
    def doit(self, num):
        """
        :type n: int
        :rtype: str
        """
        capitals, res = [chr(x) for x in range(ord('A'), ord('Z')+1)], []

        while num != 0:
            res.append(capitals[(num-1)%26])
            num = (num-1) // 26

        res.reverse()
        return ''.join(res)
            

# 171. Excel Sheet Column Number
class titleToNumber(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        i, number, base = 0, 0, ord('A')-1
        while i < len(s):
            num = ord(s[i]) - base
            number = number * 26 + num
            i +=1

        return number
            
            
# 169. Majority Element                
class majorityElement(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        x, i, count = nums[0], 1, 1
        while i < len(nums):
            if count == 0:
                x = nums[i]
                count += 1
            elif nums[i] == x:
                count += 1
            else:
                count -= 1
            i += 1
        return x

#229. Majority Element II
class majorityElementII(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        candidate1, candidate2, count1, count2 = 0, 1, 1, 1
        for n in nums:
            if n == candidate1:
                count1 += 1
            elif n == candidate2: 
                count2 += 1
            elif count1 == 0:
                candidate1, count1 = n, 1
            elif count2 == 0:
                candidate2, count2 = n, 1
            else:
                count1, count2 = count1-1, count2-1

        return [n for n in (candidate1, candidate2) if nums.count(n) > len(nums)//3] 
                
                       
# 172. Factorial Trailing Zeroes
class trailingZeroes(object):
    def doit2(self, n):
        return 0 if n == 0 else n / 5 + self.doit2(n / 5)

    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """ 
        if n == 0 : 
            return 0
        
        accu = []
        while n:
            accu.append(n % 10)
            n /= 10
        
        i, base = 1, 2
        res = 1 if accu[0] >= 5 else 0
        
        while i < len(accu):
            res += accu[i] * base
            base = base * 10 + 1
            i += 1
        
        return res

    def doit3(self, n):
        i, amount = 5, 0
        while i <= n:
            j = i
            while j % 5 == 0:
                amount += 1
                j = j // 5 
            i += 1

        return amount

        
#173. Binary Search Tree Iterator        
#Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
#Calling next() will return the next smallest number in the BST.
#Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None        
class BSTIterator(object):
    def __init__(self, root):
        """
        :type root: TreeNode
        """
        self.stack = []
        self.pushAll(root)

    def pushAll(self, n):
        while n:
            self.stack.append(n)
            n = n.left

    def hasNext(self):
        """
        :rtype: bool
        """
        return len(self.stack) > 0
        

    def next(self):
        """
        :rtype: int
        """
        a = self.stack.pop()        
        self.pushAll(a.right)        

        return a.val




# 189. Rotate Array
#Rotate an array of n elements to the right by k steps.
#For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].
class rotateI(object):
    def doit(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        b, i = nums[len(nums)-k:], len(nums)-k-1
        while i >= 0:
            nums[i + k] = nums[i]
            i -= 1 
        i = 0
        while i < k:
            nums[i] = b[i]
            i += 1

#190. Reverse Bits
#Reverse bits of a given 32 bits unsigned integer.
#For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).
class reverseBits:
    # @param n, an integer
    # @return an integer
    def doit(self, n):
        res = n >> 16 | n << 16
        res = ((res & 0xff00ff00) >> 8) | ((res & 0x00ff00ff) << 8)
        res = ((res & 0xf0f0f0f0) >> 4) | ((res & 0x0f0f0f0f) << 4)
        res = ((res & 0xcccccccc) >> 2) | ((res & 0xcccccccc) << 2)
        return res


# 198. House Robber
#You are a professional robber planning to rob houses along a street. 
#Each house has a certain amount of money stashed, the only constraint stopping you from robbing 
#each of them is that adjacent houses have security system connected and 
#it will automatically contact the police if two adjacent houses were broken into on the same night.

#Given a list of non-negative integers representing the amount of money of each house, determine
# the maximum amount of money you can rob tonight without alerting the police.
class rob(object):
    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        
        


# 199. Binary Tree Right Side View
#Given a binary tree, imagine yourself standing on the right side of it,
#return the values of the nodes you can see ordered from top to bottom.
class rightSideView(object):
    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        rsv, s, dep, iterArray = [], root, 0, [] 
        while s:
            if dep >= len(rsv):
                rsv.append(s.val)
            
            if s.right or s.left:
                dep += 1
                if s.right :
                    iterArray.append((s, dep))
                    s = s.right
                else:
                    s = s.left
            else :
                # search left
                s = None
                while iterArray:
                    last = iterArray.pop()
                    if last[0].left:
                        s, dep = last[0].left, last[1]
                        break
                    dep = last[1]
            return rsv

        def doit2(self, root):
            rsv = []
            def search(node, depth):
                if not node:
                    return

                if depth == len(rsv):
                    rsv.append(node.val)

                search(node.right, depth + 1)
                search(node.left, depth + 1)
                

            search(root, 0)
            return rsv

        # Width iteration
        def doit3(self, root):
            if not root:
                return []
            results = []
            queue = [root]
            while(len(queue)):
                results.append(queue[-1].val)
                count = len(queue)
                while(count>0):
                    node = queue.pop(0)
                    if node.left:
                        queue.append(node.left)
                    if node.right:
                        queue.append(node.right)
                    count -= 1
            return results

        def doit4(self, root):
            view = []
            if root:
                level = [root]
                while level:
                    view += level[-1].val
                    view = [kid for node in level for kid in (node.left, node.right) if kid]
            return view
        

# 389. Find the Difference
class findTheDifference(object):
    def doit(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        #return chr(reduce(operator.xor, map(ord, s + t)))
        #return list(collections.Counter(t) - collections.Counter(s))[0]
        pass
        

    def doit3(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        c, i = 0, 0
        while i < len(s):
            c ^= ord(s[i])
            i += 1

        i = 0
        while i < len(t):
            c ^= ord(t[i])
            i += 1

        return chr(c)
        

    def doit2(self, t, s):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        i, D = 0, {}
        while i < len(t):
            if D.has_key(t[i]):
                D[t[i]] += 1
            else:
                D[t[i]] = 1
            i += 1

        i, res = 0, ''
        while i < len(s):
            if not D.has_key(s[i]) or D[s[i]] == 0:
                 res += s[i]
            else:
                D[s[i]] -= 1

            i += 1

        return res


# 146. LRU Cache
class LRUCache(object):

    def __init__(self, capacity):
        """
        :type capacity: int
        """
        

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """            
        
# 187. Repeated DNA Sequences
class findRepeatedDnaSequences(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        t, i, D, rv = 0, 0, {}, []
        while i < 9:
            t = t << 3 | ord(s[i]) & 7
            i += 1

        while i < len(s):
            t = t << 3 & 0x3FFFFFFF | ord(s[i]) & 7
            if t not in D:
                D[t] = 0
            D[t] += 1
            if D[t] == 2:
                rv.append(s[i-9:i+1])
            i += 1

        return rv

    def doit2(self, s):
        if not s or  len(s) <= 10: 
            return []

        st = set([])
        res_set = set([])

        for i in xrange(len(s)):
            pattern = s[i:i+10]
            if pattern in st:
                if pattern not in res_set:
                    res_set.add(pattern)
            else:
                st.add(pattern)

        return list(res_set)
            
                
# 202. Happy Number
class isHappyNumber(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: bool
        """
        D = set()
        while n != 1 and n not in D:
            D.add(n)
            temp = 0
            while n != 0:
                temp += (n%10)**2
                n //=10
            n = temp
            
        return n == 1

# 258. Add Digits
class addDigits(object):
    def doit(self, num):
        """
        :type num: int
        :rtype: int
        """
        while num > 10:
            temp = 0
            while num :
                temp += num%10
                num //= 10

            num = temp

        return num

    def doit2(self, num):
        """
        :type num: int
        :rtype: int
        """
        return 1 + (num-1)%9

# 260. Single Number III
class singleNumberIII(object):
    def doit1(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        D = {}
        for i in nums:
            if D.has_key(i):
                D.pop(i)
            else:
                D[i] = 1

        return D.keys()

    def doit(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        xorAll = 0
        for n in nums:
            xorAll ^= n

        l = 0
        while xorAll & 1 == 0:
            l += 1
            xorAll >>= 1

        bit = 1 << l
        xor1 = 0
        xor2 = 0

        for n in nums:
            if n & bit == 0:
                xor1 ^= n
            else:
                xor2 ^= n
        return [xor1, xor2]
                    
                


# 203. Remove Linked List Elements
# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None
class removeElements(object):
    def doit(self, head, val):
        """
        :type head: ListNode
        :type val: int
        :rtype: ListNode
        """
        result = ListNode(200)
        result.next = head
        bt, pt = result, head
        
        while pt:
            while pt and pt.val == val:
                pt = pt.next
            
            bt.next = pt
            
            if not pt:
                continue
            
            bt, pt = pt, pt.next    

        return result.next


# 204. Count Primes
class countPrimes(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        pass

# 205. Isomorphic Strings
class isIsomorphic(object):
    def doit(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        if len(s) != len(t):
            return False
           
        dicS, dicT = {}, {}
        for i in range(len(s)):
            a = dicS.get(s[i])
            b = dicT.get(t[i])

            if not a and not b:
                dicS[s[i]] = t[i]
                dicT[t[i]] = s[i]
            elif a != t[i] or b != s[i]:
                return False

        return True
        

# 191. Number of 1 Bits
class hammingWeight(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        amount = 0
        while n != 0:
            if n % 2 == 1:
                amount += 1
            n = n >> 1
        return amount

    def doit2(self, n):
        dist = 0
        while n:
            n &= n-1
            dist += 1
        return dist

# 201. Bitwise AND of Numbers Range
class rangeBitwiseAnd(object):
    def doit(self, m, n):
        """
        :type m: int
        :type n: int
        :rtype: int
        """
        if m == 0:
            return 0

        factor = 1
        while m != n:
            m >>= 1
            n >>= 1
        
            factor <<= 1
        return m * factor


# 204. Count Primes
class countPrimes(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        Primes = [True] * (n+1)
        Primes[0] = Primes[1] = False

        i = 1
        while i < int(n**0.5)+1:
            if Primes[i]:
                j = i * i
                while j < n:
                    Primes[j] = False
                    j += i
            i += 1
        
        return sum(Primes)


    def doit2(self, n):
        if n <= 1:
            return 0

        primes = [True] * n
        primes[0], primes[1] = False, False
        for i in xrange(2, int(n**0.5) + 1):
            if primes[i]:
                primes[i*i:n:i] = [False] * int(math.ceil((n-i*i)/float(i)))
                
        return sum(primes)

# 231. Power of Two
class isPowerOfTwo(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: bool
        """
        return n > 0 and n & (n-1) == 0
    
    def doit2(self, n):
        amount = 0
        while n and amount < 2:
            amount += n & 1
            n = n >> 1
        return amount == 1

    def doit3(self, n):
        amount = 0
        while n != 0 and amount < 2:
            if n % 2 == 1:
                amount += 1
            n = n >> 1
        return 0 < amount < 2
        

# 326. Power of Three
class isPowerOfThree(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: bool
        """
        while n != 1 and n > 0:
            if n % 3 != 0:
                return False
            n //= 3
        return n == 1

    def doit1(self, n):
        return  n > 0 and 3**19 % n == 0
        #if n <= 0:
        #    return False
        #max_int = 3**19
        #return (max_int % n == 0)

    def doit3(self, n):
        if n == 0:
            return False

        while n % 3 == 0:
            n //= 3

        return n == 1

# 342. Power of Four
class isPowerOfFour(object):
    def doit(self, num):
        """
        :type num: int
        :rtype: bool
        """
        while n != 1 and n > 0:
            if n % 4 != 0:
                return False
            n = n >> 2

        return n == 1

    def doit2(self, num):
        if n == 0:
            return False

        while n % 4 == 0:
            n //= 4

        return n == 1

    def doit3(self, num):
        # 01010101010101010101010101010101 
        # 1431655765
        # num & (num-1) is 2**n
        # num & 0x55555555 is 4 ** n of all possible
        return num != 0 and num &(num-1) == 0 and (num & 1431655765) != 0

    def doit4(self, num):
        return ((num-1)&num)==0 and (num-1)%3==0;



# 257. Binary Tree Paths
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class binaryTreePaths(object):
    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: List[str]
        """
        def searchBTree(node, path, rv):
            if not node.left and not node.right:
                rv.append(path[:])
                return

            if node.left:
                path.append(str(node.left.val))
                searchBTree(node.left, path, rv)
                path.pop()

            if node.right:
                path.append(str(node.right.val))
                searchBTree(node.right, path, rv)
                path.pop()

        temp = []
        if root:        
            searchBTree(root, [str(root.val)], temp)

        rv = []
        for path in temp:
            rv.append("->".join(path))
            
        return rv

    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[str]
        """
 
        def searchBinaryTree(node, path, rv):
            if not node.left and not node.right:
                rv.append(path + str(node.val))
                return
            path += str(node.val) + '->'
                
            if node.left:
                searchBinaryTree(node.left, path, rv)
            if node.right:
                searchBinaryTree(node.right, path, rv)

        rv = []
        if root:
            searchBinaryTree(root, "", rv)
        return rv
            
    def doit2(self, root):
        """
        :type root: TreeNode
        :rtype: List[str]
        """
        if not root:
            return []
        if not root.left and not root.right:
            return [str(root.val)]
        res = []
        for kid in (root.left, root.right):
            if kid:
                for s in self.binaryTreePaths(kid):
                    res.append(str(root.val)+"->"+s)
        return res
            
# 273. Integer to English Words            
class numberToWords(object):
    def doit(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num == 0:
            return "Zero"
        
        Dict = {0:'', 1:'One', 2:"Two", 3:'Three', 4:'Four', 5:'Five', 6:'Six', 7:'Seven',
                8:'Eight', 9:'Nine', 10:'Ten', 11:'Eleven', 12:'Twelve', 13:'Thirteen',
                14:'Fourteen', 15:'Fifteen', 16:'Sixteen', 17:'Seventeen', 18:'Eighteen',
                19: 'Nineteen', 20:'Twenty', 30:'Thirty', 40:'Forty', 50:'Fifty', 60:'Sixty',
                70: 'Seventy', 80:'Eighty', 90:'Ninety', 100:'One Hundred', 200: 'Two Hundred', 
                300: 'Three Hundred', 400:'Four Hundred', 500: 'Five Hundred', 600: 'Six Hundred',
                700: 'Seven Hundred', 800: 'Eight Hundred', 900: 'Nine Hundred'}

        Level = ['', "Thousand", "Million", 'Billion']
        base, res, i = 1000, [], 0
            
        while num:
            remainder = num % base
            if remainder == 0:
                num //= base
                i += 1
                continue

            hundred = remainder - remainder % 100
            tens = remainder % 100
            section = []
            if Dict[hundred]:
                section.append(Dict[hundred])
            
            if  0 < tens <= 20:
                section.append(Dict[tens])
            else: 
                if Dict[tens-tens%10]:
                    section.append(Dict[tens-tens%10])
                if Dict[tens%10]:
                    section.append(Dict[tens%10])
   
            if i > 0:
                section.append(Level[i])

            res.append(' '.join(section))

            num //= base
            i += 1
                
        return ' '.join(reversed(res))

    def doit2(self, num):
        top19 = 'One Two Three Four Five Six Seven Eight Nine Ten Eleven Twelve Thirteen Fourteen Fifteen\
        Sixteen Seventeen Eighteen Nineteen'.split()
        tens = 'Twenty Thirty Forty Fifty Sixty Seventy Eighty Ninety'.split()
        
        def words(n):
            if n < 20:
                return top19[n-1:n]
            if n < 100:
                return [tens[n/10 -2]] + words(n%10)
            if n < 1000:
                return [top19[n/100 - 1]] + [ 'Hundred' ] + words(n%100)
  
            for p,w in enumerate(('Thousand', 'Million', 'Billion'),1):
                if n < 1000**(p+1):
                    return words(n/1000**p) + [w] + words(n%1000**p)

        return ' '.join(words(num)) or 'Zero'


# 274. H-Index
class hIndex(object):
    def doit(self, citations):
        """
        :type citations: List[int]
        :rtype: int
        """
        pass

# 279. Perfect Squares
class numSquares(object):
    # O(n) Static DP
    def doit(self, n):
        """
        :type n: int
        :rtype: int
        """
        D = [0]
        while len(D) <= n:
            M, i = len(D), 1
            cntPerfectNum = M
            while i ** 2 <= M:
                cntPerfectNum = min(cntPerfectNum, D[M - i**2] + 1)
                i += 1
            D.append(cntPerfectNum)

        return D[n]

    # Legendre's three-square theorem
    # O(1)
    def doit2(self, n):
        """
        :type n: int
        :rtype: int
        """
        def is_square(n):
            a = int(math.sqrt(n))
            return a * a == n

        if is_square(n):
            return 1

        # Legendre's three-square theorem
        # n = 4**a (8b + 7)
        while n & 3 == 0:
            n >>= 2
        if n & 7 == 7:
            return 4

        sqrt_n = int(math.sqrt(n))
        for i in range(1, sqrt_n + 1):
            if is_square(n - i**2):
                return 2

        return 3
        
    # DP 
    def doit1(self, n):
        if n <=0:
            return 0

        D, M = [sys.maxint] * (n+1), 1
        D[0] = 0
        while M < n:
            for i in range(1, int(math.sqrt(m)) + 1):
                D[M] = min(D[M], D[m - i**2] + 1)
            M += 1

        return D[n]

    # BFS
    def doit3(self, n):
        D = [0] * (n+1)
        M = [x**2 for x in range(1, int(math.sqrt(n))+1) if x **2 <= n]

        if M[-1] == n:
            return 1

        i = 1
        while i**2 <= n:
            D[i**2 - 1] = 1
            i += 1

        searchQ, cntPerfectSquare = collections.deque(M[:]), 1
        while searchQ:
            
            cntPerfectSquare += 1
            i, size = 0, len(searchQ)
            for i in range(size):
                tmp = searchQ[0]

                for j in M:
                    if tmp + j == n:
                        return cntPerfectSquare

                    elif tmp + j < n and D[tmp+j-1] == 0:
                        D[tmp+j-1] = cntPerfectSquare
                        searchQ.append(tmp + j)
                    elif tmp+j > n:
                        break

                searchQ.popleft()
            

        return 0

    # BSF
    def doit4(self, n):
        """
        :type n: int
        :rtype: int
        """
        M, cnt = [x**2 for x in range(1, int(math.sqrt(n))+1) if x **2 <= n], 1
        if n in M:
            return cnt

        maxV, SearchQ = 0, M[:] 
        while maxV <= n:
              tmp = []
              cnt += 1
              for i in SearchQ:
                    for num in M:
                        if i + num == n:
                            return cnt
                        elif i + num < n:
                            tmp.append(i+num)
                        else:
                            break

              SearchQ = tmp

        return 0
                
#224. Basic Calculator
class calculate(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        i, sign, num = 0, [1, 1], 0
        while i < len(s):
            c = s[i]
            if c.isdigit():
                start = i
                while i < len(s) and s[i].isdigit():
                    i+=1
                num += sign.pop()*int(s[start:i])
                continue
            elif c in "+-(":
                sign += sign[-1]*(1, -1)[c=='-'],
            elif c == ')':
                sign.pop()

            i += 1

        return num


# 227. Basic Calculator II
class calculateII(object):

    def doit(self, s):
        """
        :type s: str
        :rtype: int
        """
        i, stack, sign, num = 0, [], '+', 0
        while i < len(s):
            c = s[i]
            if c.isdigit():
               num = num * 10 + int(c)
                
            if i == len(s)-1 or c in '+-*/':
                if sign == '+':
                    stack.append(num)
                elif sign == '-':
                    stack.append(-num)
                elif sign == '*':
                    stack.append(stack.pop() * num)
                elif sign == '/':
                    div = stack.pop()
                    if div >= 0:
                        stack.append(int(math.floor(div/num)))
                    else:
                        stack.append(-int(math.floor(-div/num)))

                sign, num = c, 0
            i += 1
        return sum(stack)


    def doit2(self, s):
        """
        :type s: str
        :rtype: int
        """
        if len(s) == 1:
            return int(s[0])

        i, nums, sign = 0, [], []
        while i < len(s):
            c = s[i]
            if c.isdigit():
                start = i
                while i < len(s) and s[i].isdigit():
                    i += 1
                num = int(s[start:i])
                if len(sign) > 0 and sign[-1] in (2, 3):
                    nums[-1] = nums[-1] * num if sign[-1] == 2 else int(math.floor(nums[-1] // num))
                    sign.pop()
                else:
                    nums.append(num)
                continue
            elif c in "+-*/":
                if c in ('+', '-'):
                    sign.append(1 if c == '+' else -1)
                else :
                    sign.append(2 if c == '*' else 3)
            i += 1

        i, res = 0, nums[0]
        while i < len(nums)-1:
            res += nums[i+1] * sign[i]
            i += 1

        return res
        




# 282. Expression Add Operators
class addOperators(object):
    def doit(self, num, target):
        """
        :type num: str
        :type target: int
        :rtype: List[str]
        """
        def calculate(res, num, psn, path, last, cur, target):
            if psn == len(num):
                if cur == target:
                    res.append(path)
                return 
            
            for i in range(1, len(num) - psn + 1):
                tmp = num[psn:psn+i]
                a = int(tmp)
                if len(tmp) > 1 and tmp[0] == '0':
                    continue
                if path:
                    calculate(res, num, psn+i, path+'+'+tmp, a, cur + a, target)

                    calculate(res, num, psn+i, path+'-'+tmp, -a, cur - a, target) 

                    calculate(res, num, psn+i, path+'*'+tmp, last * a, (cur-last) + last * a, target)
                else:
                    calculate(res, num, psn+i, tmp, a, a, target)

            return

        res= []
        calculate(res, num, 0, "", 0,  0, target)
        return res



        
# 290. Word Pattern
class wordPattern(object):
    def doit(self, pattern, str):
        """
        :type pattern: str
        :type str: str
        :rtype: bool
        """
        M = str.split()
        D, RD = dict(), dict()
        if len(M) != len(pattern):
            return False

        for i, index in enumerate(pattern):
            if not D.has_key(index):
                D[index] = M[i]
            else:
                if D[index] != M[i]:
                    return False
                
            if not RD.has_key(M[i]):
                RD[M[i]]=index
            else:
                if RD[M[i]] != index:
                    return False
                    
        return True       
        
    def doit1(self, pattern, str):
        """
        :type pattern: str
        :type str: str
        :rtype: bool
        """
        p2w = {}
        w2p = {}
        s = str.strip().split()
        if len(s) != len(pattern):
            return False

        for i in range(len(s)):
            word = s[i]
            p = pattern[i]
            p2w[p] = p2w.get(p, word)
            w2p[word] = w2p.get(word, p)
            if p != w2p[word] or word != p2w[p]:
                return False
        return True

# 72. Edit Distance
class minDistance(object):
    def doit1(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        def compare(word1, s1, word2, s2, changed):
            if s1 == len(word1) and s2 == len(word2):
                return changed

            if s1 == len(word1) or s2 == len(word2):
                changed += (len(word2) - s2) if s1 == len(word1) else (len(word1) - s1) 
                return changed 

            res = 0
            if word1[s1] == word2[s2]:
                res = compare(word1, s1+1, word2, s2+1, changed)
            else:
                res = min(compare(word1, s1+1, word2, s2+1, changed+1), # replace
                          compare(word1, s1+1, word2, s2, changed+1), # delete
                          compare(word1, s1, word2, s2+1, changed+1)) # insert

            return res

        return compare(word1, 0, word2, 0, 0)

    def doit(slef, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        if len(word1) < len(word2):
            word1, word2 = word2, word1

        D = [x for x in range(len(word1)+1)]
        DL = D[:]

        for i in range(1, len(word2)+1):
            D[0] = i
            for j in range(1, len(word1)+1):

                if word2[i-1] == word1[j-1]:
                    D[j] = DL[j-1]
                else:
                    D[j] = min(DL[j], D[j-1], DL[j-1]) + 1

            DL = D[:]

        return D[len(word1)]
                        
        
# 73. Set Matrix Zeroes
class setZeroes(object):
    def doit(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """
        m, n = len(matrix), len(matrix[0])

        D = [(x, y) for x in range(len(matrix)) for y in range(len(matrix[0])) if matrix[x][y] ==0 ]
        
        xset, yset = set(), set()
        for i in D:
            if i[0] not in xset:
                matrix[i[0]] = [0] * n
                xset.add(i[0])

            if i[1] not in yset:
                for x in range(m):
                    matrix[x][i[1]] = 0 
                yset.add(i[1])

    def doit1(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """
        cord=[]

        for i in xrange(len(matrix)):
            for j in xrange(len(matrix[0])):
                if not matrix[i][j]:
                    cord.append((i,j))

        for each in cord:
            r=each[0]
            c=each[1]
            for j in xrange(len(matrix[r])):
                matrix[r][j]=0
            for i in xrange(len(matrix)):
                matrix[i][c]=0




# 76. Minimum Window Substring
class minWindow(object):
    def doit(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        if not s or not t:
            return ""

        have, nums = [False for x in range(128)], [0 for x in range(128)]
        for c in t:
            have[ord(c)] = True
            nums[ord(c)] += 1

        i, j = -1, 0
        minLen, iMin, count = sys.maxint, 0, len(t)
        
        while i < len(s) and j < len(s):
             if count:
                
                c = ord(s[i])
                i += 1
                nums[c] -= 1
                if have[c] and nums[c] >= 0:
                    count -= 1
             else:
                if minLen > i - j + 1:
                    minLen = i - j + 1
                    iMin = j

                c = ord(s[j])
                nums[c] += 1
                if have[c] and nums[c] > 0:
                    count += 1

                j += 1

        return "" if minLen == sys.maxint else s[iMin: iMin + minLen]


#292. Nim Game
class canWinNim(object):
    def doit(self, n):
        """
        :type n: int
        :rtype: bool
        """
        pass        

# Main function
if __name__ == '__main__':

   res = 1



   res = minWindow().doit("ADOBECODEBANC", "ABC")

   res = minDistance().doit("abcd", "abcde")

   a = [[0,0,0,5],[4,3,1,4],[0,1,1,4],[1,2,1,3],[0,0,1,1]]
   setZeroes().doit(a)

   res = fullJustify().doit([""], 2)

   res = isNumber().doit("0")

   res = isNumber().doit(" 0.1")

   res = isNumber().doit("abc")

   res = isNumber().doit("1 ")

   res = isNumber().doit("1 a")

   res = isNumber().doit("2e10")


   res = calculate().doit("1+1")

   res = calculate().doit("2-1+2")

   res = calculateII().doit("  30")

   res = calculateII().doit("14-3/2")

   res = calculateII().doit("0-2147483647")

   res = calculate().doit("(1+(4+5+2)-3)+(6+8)")

   res = addOperators().doit("123", 6)

   res = addOperators().doit("999999999", 80)

   res = addOperators().doit("123", 6)

   res = numSquares().doit3(8)

   res = numberToWords().doit2(18)

   res = numberToWords().doit(123)

   res = numberToWords().doit(12345)

   res = singleNumberIII().doit([1, 2, 1, 3, 2, 5])

   res = nthUglyNumber().doit(7)
    
   res = isHappyNumber().doit(2)

   res = findRepeatedDnaSequences().doit("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT")

   res = longestConsecutive().doit([100,4,200,1,3,2])
   res = longestConsecutive().doit([0,-1])

   a = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
   res = SurroundedRegions().doit(a)

   res = canCompleteCircuit().doit([4], [5])

   a = TreeNode(-1)
   a.right = TreeNode(9)
   a.right.left, a.right.right = TreeNode(-6), TreeNode(3)
   a.right.right.right = TreeNode(-1) 
   res = maxPathSum().doit(a)

   a = TreeNode(-2)
   a.left = TreeNode(6)
   a.left.left, a.left.right = TreeNode(0), TreeNode(-6)

   res = maxPathSum().doit(a)

   a = TreeNode(1)
   a.left, a.right = TreeNode(2), TreeNode(3)

   res = maxPathSum().doit(a)

   res = ladderLength().doit("hit", "cog", ["hot","dot","dog","lot","log","cog"])

   res = ladderLength().doit("hit", "cog", ["hot","dot","dog","lot","log"])


   res = findLadders().doit("hit", "cog", ["hot","dot","dog","lot","log","cog"])



   a = ListNode(1)
   a.next = ListNode(2)
   a.next.next = ListNode(4)
   a.next.next.next = ListNode(3)
   a.next.next.next.next = ListNode(5)

   res = partition().doit(a, 4)

   
   a = [["a","b"], ["c","d"]]
   res = existWord().doit(a, "abcd")

   a = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']]
   res = existWord().doit(a, "ABCCED")
   res = existWord().doit(a, "SEE")
   res = existWord().doit(a, "ABCB")

   a = "/a/./b/../../c/"
   res = simplifyPath().doit(a)
   
   a = [1, 0]
   res = sortColors().doit(a)
   #a = [0,1,2,0,1,2,0,2,1,2,0,1,2]
   a = [0,2,1,2,0,0,1,2,1,1,1,0,2,1,2,1,1,1,1,2,1,0,0,0,1,2,2,0,2,1,0,0,1,2,2,1,2,1,0,0,0,0,2,0,2,1,2,1,1,1,1,0,1,2,0,0,0,0,0,0,2,1,1,0,0,1,1,0,0,0,0,1,1,2,2,0,2,1,1,1,2,0,1,1,1,0,2,1,1,2,2,0,1,0,0,1,0,2,2,1,2,1,2,0,0]
   res = sortColors().doit(a)

   res = numDecodings().doit("11")
   res = numDecodings().doit("10")
   res = numDecodings().doit("4757562545844617494555774581341211511296816786586787755257741178599337186486723247528324612117156948")
    

   res = subsets().doit([1,2,3,4])
   res = subsetsWithDup().doit([1,2,2])

   res = minPathSum().doit([[1,2,5],[3,2,1]])
   res = minPathSum().doit([[9,1,4,8]])

   a = TreeNode(1)
   a.left = TreeNode(2)
   res = rightSideView().doit(a)

   a = TreeNode(1)
   a.left, a.right = TreeNode(2), TreeNode(3)
   a.left.left = TreeNode(4)
    
   res = rightSideView().doit(a)

   res = findTheDifference().doit('abcd', 'abcde')

   a = [1,2,3,4,5,6,7]
   res = rotateI().doit(a, 3)

   res = trailingZeroes().doit2(30)
   res = trailingZeroes().doit(30)

   res = trailingZeroes().doit2(100)
   res = trailingZeroes().doit(100)

   res = trailingZeroes().doit2(1000)
   res = trailingZeroes().doit(1000)

   

   res = majorityElementII().doit([6,6,6,7,7])
    

   res = convertToTitle().doit(26)
   res = convertToTitle().doit(27)

   res = twoSumSorted().doit([2,3,4], 6)
   res = twoSumSorted().doit([-1, 0], -1)
   res = twoSumSorted().doit([0,0,3,4], 0)

   res = compareVersion().doit("2.4", "2.4.1.2")
    
   a = ListNode(1)
   res = getIntersectionNode().doit2(a, a)

   res = maxProduct().doit([2,3,-2,4])

   res = maxProduct().doit3([-2,-3,7])

   res = maxProduct().doit3([-5,2,4,1,-2,2,-6,3,-1,-1,-1,-2,-3,5,1,-3,-4,2,-4,6,-1,5,-6,1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,1,1,1,-1,1,1,-1,-1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,-1,1,1,1,1,-1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,-1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,1,1,-1,-1,1,-1,-1,1,-1,1,1,1,1,1,-1,1,1,1,1,-1,1,1,-1,-1,1,-1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,-1,-1,-1,1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,1,1,1,-1,1,1,1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,1,1,1,-1,1,1,-1,1,1,-1,1,1,-1,-1,-1,1,-1,1,1,-1,1,1,1,1,-1,-1,-1,1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,1,1,1,1,-1,1,1,1,-1,-1,-1,-1,1,-1,-1,1,1,1,-1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,-1,-1,1,-1,1,1,1,1,-1,1,1,1,-1,-1,-1,-1,1,-1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,1,1,1,-1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,1,1,1,1,1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,1,1,1,-1,1,1,1,-1,-1,-1,1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,1,1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,1,1,1,1,1,-1,1,1,1,-1,-1,1,1,1,1,1,-1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,1,-1,1,1,1,1,1,1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,1,1,1,-1,-1,-1,1,1,1,1,1,-1,-1,-1,1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,1,1,1,1,1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,1,1,-1,1,1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,1,1,1,1,-1,1,-1,1,1,1,1,-1,-1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,1,1,1,-1,1,-1,1,-1,-1,1,1,1,1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,1,1,1,1,1,-1,1,-1,1,1,1,1,-1,-1,-1,1,1,1,1,-1,-1,1,1,1,1,1,-1,1,1,1,-1,1,1,1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,1,1,-1,1,1,1,1,-1,-1,1,1,1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,1,1,-1,-1,1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,-1,1,1,1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,1,1,1,-1,-1,1,1,1,1,-1,1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,1,-1,1,1,1,1,1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,1,1,1,1,1,-1,1,-1,1,1,1,-1,1,1,1,-1,1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,1,1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,1,1,1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,1,1,1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,1,1,-1,1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,1,1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,1,-1,1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,1,-1,1,1,1,1,1,-1,1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,1,1,1,-1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,-1,1,1,1,1,1,1,1,1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,-1,-1,1,1,1,1,-1,1,1,1,1,1,1,1,1,1,1,1,-1,1,-1,-1,1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,-1,1,1,1,-1,1,-1,-1,-1,1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,1,1,1,1,-1,1,-1,1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,-1,1,1,-1,-1,-1,1,1,1,1,1,-1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,1,1,1,1,1,1,1,-1,-1,1,-1,-1,1,1,1,-1,1,1,-1,1,1,1,1,-1,1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,1,1,1,1,1,1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,-1,-1,1,1,1,1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,-1,1,-1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,-1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,1,1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,1,-1,1,1,-1,1,-1,1,-1,1,1,1,1,-1,1,1,1,-1,1,1,1,1,1,-1,1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,1,1,-1,1,1,1,-1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,-1,1,1,1,1,-1,1,-1,1,1,1,1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,1,1,1,-1,-1,-1,1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,-1,1,1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,-1,1,1,1,1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,1,-1,1,1,-1,1,1,1,1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,1,1,1,1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,-1,1,1,1,-1,1,1,1,1,1,-1,-1,1,-1,1,-1,1,1,1,-1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,-1,1,-1,1,-1,1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,1,1,1,1,1,-1,-1,1,-1,1,-1,-1,1,1,-1,1,1,1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,1,1,1,-1,-1,-1,1,1,-1,1,1,1,1,1,1,1,1,-1,1,-1,-1,1,1,1,1,-1,-1,-1,1,1,-1,1,1,-1,1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,1,1,-1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,1,1,1,1,-1,-1,1,-1,1,1,-1,-1,1,1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,1,1,-1,1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,1,1,-1,1,-1,-1,1,-1,1,1,-1,1,1,1,1,1,-1,1,-1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,1,1,1,1,1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,1,1,1,1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,-1,1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,1,-1,1,1,1,1,-1,1,-1,1,-1,-1,-1,1,1,1,1,1,-1,1,1,1,1,1,1,-1,1,1,1,1,-1,1,1,-1,1,-1,1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,1,1,1,1,1,-1,1,-1,1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,1,1,1,1,1,-1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,1,1,-1,-1,-1,1,-1,1,1,1,-1,1,1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,1,1,1,1,1,-1,1,1,1,1,1,1,1,-1,1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,-1,-1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,1,1,-1,1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,1,-1,1,-1,1,1,1,1,1,-1,1,1,1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,1,1,1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,1,1,-1,1,-1,-1,-1,-1,1,-1,1,-1,1,1,1,1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,1,-1,-1,1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,1,1,1,-1,1,1,-1,1,-1,-1,1,1,-1,1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,1,-1,1,1,1,-1,1,1,-1,1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,1,1,-1,1,-1,1,1,1,1,1,1,1,-1,-1,-1,1,1,-1,1,1,-1,1,1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,-1,1,1,1,1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,1,1,1,1,1,-1,1,1,-1,1,1,-1,1,1,1,1,1,1,-1,1,1,1,-1,-1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,1,1,-1,1,1,1,1,-1,1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,-1,-1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,1,-1,1,1,1,1,1,1,-1,1,1,-1,1,1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,1,1,1,1,1,1,-1,1,1,1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,-1,1,1,-1,-1,1,1,1,1,-1,1,1,-1,1,-1,1,-1,-1,1,1,1,-1,1,1,-1,1,1,1,1,1,-1,1,1,-1,-1,1,1,1,-1,-1,1,1,-1,1,1,-1,1,1,1,1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,-1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,1,1,1,1,1,1,1,-1,-1,1,-1,1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,1,1,1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,1,1,1,1,1,-1,-1,1,1,-1,-1,1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,1,1,-1,-1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,1,1,-1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,1,1,1,-1,-1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,1,1,-1,1,-1,1,1,1,1,1,1,-1,1,-1,1,-1,1,1,-1,1,-1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,1,-1,1,-1,1,1,-1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,1,1,1,1,1,-1,1,-1,1,-1,1,1,1,-1,1,1,-1,1,-1,1,1,1,1,1,1,1,1,1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,1,-1,1,1,1,1,1,1,1,1,1,1,-1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,1,1,1,1,-1,-1,1,1,-1,1,1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,1,-1,-1,1,1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,1,-1,1,1,1,1,-1,-1,-1,1,1,1,1,-1,1,1,-1,1,-1,1,1,-1,1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,-1,1,1,1,1,1,1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,1,1,-1,1,-1,1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,1,1,1,1,1,1,-1,-1,1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,1,1,1,1,-1,1,-1,-1,1,1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,1,1,1,-1,1,-1,-1,1,1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,1,1,-1,1,1,-1,1,-1,-1,1,1,1,1,1,1,1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,1,1,-1,-1,1,1,1,1,-1,1,-1,1,1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,-1,1,1,1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,1,1,-1,1,1,1,1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,1,-1,-1,1,1,1,1,-1,-1,-1,-1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,1,1,1,1,1,1,-1,-1,1,-1,1,1,-1,1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,1,1,1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,1,-1,1,-1,1,1,1,1,-1,-1,1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,-1,1,-1,1,-1,1,-1,-1,1,1,1,-1,1,-1,1,1,1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,1,1,1,1,1,-1,-1,1,1,1,-1,-1,1,1,-1,1,1,1,1,1,-1,1,-1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,1,1,1,1,1,-1,1,-1,1,1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,1,-1,1,1,1,1,1,1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,-1,-1,1,-1,1,-1,-1,1,1,1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,1,1,1,1,1,1,1,1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,1,1,1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,1,1,1,1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,1,1,-1,1,1,-1,1,-1,1,-1,-1,1,1,1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,1,1,1,1,1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,1,1,1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1,-1,1,1,1,-1,1,-1,1,1,1,1,-1,1,1,1,-1,-1,1,1,1,-1,-1,1,1,1,1,-1,-1,-1,1,1,-1,1,1,1,1,1,1,-1,1,-1,1,1,-1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,1,1,1,1,-1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,1,1,1,-1,1,1,-1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,1,1,1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,-1,-1,1,1,1,-1,1,1,-1,1,1,1,1,1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,1,1,1,-1,1,1,1,1,1,1,1,-1,1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,-1,-1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,1,1,1,1,-1,1,-1,1,1,1,-1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,1,1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,1,1,-1,1,-1,1,1,-1,1,1,1,-1,-1,1,1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,-1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,1,1,1,1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,-1,1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,1,1,1,1,1,1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,1,1,-1,1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,1,-1,1,1,1,1,-1,1,1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,1,1,1,1,1,1,1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,1,1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,1,-1,1,1,1,1,1,1,1,-1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,1,1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,-1,1,1,1,-1,1,1,-1,-1,-1,1,-1,1,1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,1,1,1,1,-1,1,-1,-1,1,-1,1,1,1,1,1,1,1,1,1,1,1,-1,1,1,1,-1,1,-1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,1,-1,1,1,1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,1,1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,1,1,1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,1,1,1,-1,-1,-1,-1,1,1,-1,1,1,1,1,-1,1,-1,1,1,1,-1,-1,1,1,-1,-1,1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,1,1,1,-1,1,1,1,1,-1,-1,-1,1,1,1,-1,-1,1,1,1,1,-1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,1,1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,-1,1,1,-1,1,1,1,1,1,1,1,-1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,1,1,1,1,1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,1,1,1,-1,1,-1,-1,-1,1,-1,1,1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,1,1,1,-1,-1,-1,1,1,1,1,1,1,1,1,-1,1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,-1,-1,1,1,1,-1,1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,1,-1,1,1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,1,1,1,1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,-1,1,-1,1,1,1,-1,-1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,-1,1,-1,1,-1,1,1,-1,1,1,1,-1,-1,1,1,1,1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,1,1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,1,1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,1,1,1,-1,1,1,1,1,1,1,-1,1,1,-1,1,1,1,1,-1,1,1,-1,1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,-1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,1,1,-1,1,1,-1,1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,1,1,1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,1,-1,1,-1,1,1,1,1,1,-1,-1,1,1,1,1,1,1,-1,1,1,1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,1,1,1,-1,1,1,1,1,1,-1,-1,1,1,1,1,-1,1,1,1,1,-1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,1,-1,1,1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,1,1,1,-1,1,-1,1,1,-1,1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,1,-1,-1,-1,1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,1,1,-1,-1,1,1,1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,1,1,-1,1,1,-1,1,1,-1,1,-1,1,1,-1,-1,1,1,1,1,1,-1,-1,1,1,1,1,1,-1,1,-1,-1,1,-1,1,-1,1,1,1,1,-1,-1,1,1,-1,1,1,1,1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,1,1,1,1,1,1,1,1,1,-1,1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,-1,1,1,1,1,-1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,1,1,-1,1,1,1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,1,1,1,-1,-1,-1,1,1,-1,1,1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,1,1,1,-1,1,1,-1,-1,1,1,1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,1,1,1,1,-1,1,1,-1,1,-1,-1,1,1,1,1,-1,1,1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,1,1,1,1,-1,1,1,-1,-1,-1,-1,-1,1,1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,1,1,1,-1,1,1,1,-1,1,-1,-1,1,1,1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,1,1,-1,-1,1,1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,-1,1,-1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,1,-1,1,-1,1,1,-1,-1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,1,1,1,1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,-1,1,1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,-1,-1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,-1,1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,1,1,1,1,1,1,1,-1,-1,1,1,1,1,1,1,1,-1,-1,1,-1,1,-1,-1,1,1,1,1,1,-1,1,-1,-1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,-1,1,1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,1,1,1,1,-1,-1,1,1,1,-1,1,1,1,1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,1,1,1,1,1,1,-1,1,-1,-1,1,1,1,-1,-1,1,1,-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,1,-1,1,-1,1,1,1,1,-1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,1,1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,1,-1,1,1,1,1,1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,-1,1,1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,1,1,1,-1,-1,1,1,1,-1,1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,1,-1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,1,1,-1,1,-1,1,1,1,1,-1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,1,-1,-1,1,1,1,1,1,1,1,1,1,-1,1,1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,1,1,1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,1,1,-1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,1,1,-1,-1,1,-1,1,1,1,-1,1,1,1,1,-1,-1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,1,1,1,1,-1,-1,1,1,1,1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,1,1,1,1,-1,1,-1,1,-1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,-1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,-1,1,1,-1,-1,-1,1,-1,1,1,1,-1,1,1,1,1,1,1,-1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,1,1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,-1,1,1,-1,-1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,1,1,1,-1,-1,1,1,-1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,1,1,1,-1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,1,1,-1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,1,1,1,-1,-1,1,1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,-1,-1,1,1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,1,1,1,1,1,-1,1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,1,-1,1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,1,1,-1,-1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,1,1,1,1,1,1,1,-1,1,1,-1,-1,1,1,-1,1,1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,-1,-1,1,1,1,1,-1,1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,-1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,1,1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,1,1,1,-1,1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,1,1,1,-1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,1,1,1,1,1,1,-1,-1,-1,1,-1,1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,-1,1,1,1,1,-1,1,1,1,1,1,1,1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,1,1,-1,1,-1,1,1,1,-1,1,-1,-1,1,1,1,1,1,-1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,1,1,-1,1,1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,1,1,-1,1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,1,1,1,1,1,-1,1,1,1,1,-1,1,-1,1,1,1,1,1,1,1,-1,-1,1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,1,1,-1,1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,1,1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,1,1,1,-1,1,1,-1,-1,-1,1,-1,1,1,-1,-1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,-1,1,1,1,1,-1,1,-1,1,1,1,1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,-1,1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,-1,1,1,1,1,-1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,1,1,-1,1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,-1,-1,1,1,1,1,-1,1,1,1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,1,-1,1,-1,1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,-1,-1,1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,1,1,-1,1,1,-1,-1,1,-1,1,1,1,1,1,-1,-1,1,-1,1,-1,1,1,1,-1,1,-1,1,1,-1,-1,1,-1,-1,1,1,1,1,1,1,-1,1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,1,1,-1,-1,1,1,1,1,1,-1,-1,1,1,1,1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,-1,1,1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,1,1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,1,1,1,-1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,-1,1,-1,1,1,1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,1,1,-1,1,1,1,1,1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,1,1,-1,1,1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,-1,1,-1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,1,-1,-1,1,1,-1,1,1,1,-1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,1,1,1,1,1,1,1,-1,-1,-1,1,-1,1,1,1,1,-1,1,1,-1,1,1,1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,1,1,1,1,1,1,1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,-1,-1,-1,1,-1,1,1,1,1,1,1,1,1,1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,-1,1,1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,1,1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,-1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,1,-1,1,-1,1,-1,1,1,-1,1,1,1,1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,1,1,-1,1,1,1,1,1,-1,1,1,1,1,-1,-1,1,-1,1,-1,-1,1,1,1,1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,-1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,-1,1,-1,1,1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,1,-1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,1,1,1,1,-1,-1,-1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,1,1,-1,1,1,1,1,-1,-1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,1,1,-1,1,1,-1,1,-1,-1,1,-1,1,1,1,-1,1,-1,1,1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,1,1,1,1,1,1,-1,-1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,1,1,1,1,-1,1,1,-1,1,-1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,1,1,-1,1,-1,1,1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,1,1,-1,1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,1,-1,1,1,1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,-1,1,-1,-1,1,1,1,-1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,-1,1,1,-1,-1,-1,-1,1,-1,1,1,1,1,1,-1,-1,-1,1,1,1,1,1,1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,1,1,-1,-1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,1,1,1,-1,-1,1,1,1,-1,-1,1,1,1,1,1,-1,-1,1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,1,1,-1,1,1,1,-1,-1,1,1,-1,1,1,1,-1,-1,1,1,-1,1,1,1,-1,-1,1,1,-1,-1,1,1,1,-1,1,-1,1,1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,1,1,1,1,1,1,1,1,-1,1,-1,1,1,-1,1,1,-1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,1,1,1,1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,1,1,-1,1,1,1,1,1,1,-1,1,-1,1,1,1,-1,1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,1,1,1,-1,-1,-1,1,1,1,1,1,1,1,-1,1,1,1,-1,1,-1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,-1,-1,-1,1,1,1,1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,1,1,1,1,1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,1,1,1,1,1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,-1,-1,-1,1,1,1,1,1,1,1,-1,1,-1,1,-1,1,1,1,-1,1,1,1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,-1,1,-1,1,1,1,-1,-1,1,1,1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,1,-1,1,-1,-1,1,1,1,-1,-1,1,1,1,-1,-1,1,-1,1,1,-1,1,1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,1,1,-1,-1,1,1,1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,-1,-1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,1,1,1,1,1,-1,-1,-1,1,1,1,1,-1,-1,1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,1,1,1,1,-1,1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,1,1,1,-1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,-1,1,1,1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,-1,-1,1,1,1,1,-1,1,1,-1,1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,1,1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,1,1,1,-1,1,-1,1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1])

   res = ladderLength().doit("hit", "cog", ["hot","dot","dog","lot","log","cog"])

   a = RandomListNode(-1)
   a.next = RandomListNode(-1)

   res = copyRandomList().doit(a)


   res = wordBreak().doit("leetcode", ["leet", "code"])
   res = wordBreak().doit("cars", ["car", "rs", "ca"])
   res = wordBreak().doit("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"])

   a = ListNode(1)
   a.next = ListNode(2)
   a.next.next = ListNode(3)
   #a.next.next.next = ListNode(4)
   res = reorderList().doit(a)

   res = evalRPN().doit(["10","6","9","3","+","-11","*","/","*","17","+","5","+"])

   res = reverseWords().doit("  ")

   res = maxProfitOfStockIII().doit([1,2,4])

   res = maxProfitOfStockIII().doit([10000,9999,9998,9997,9996,9995,9994,9993,9992,9991,9990,9989,9988,9987,9986,9985,9984,9983,9982,9981,9980,9979,9978,9977,9976,9975,9974,9973,9972,9971,9970,9969,9968,9967,9966,9965,9964,9963,9962,9961,9960,9959,9958,9957,9956,9955,9954,9953,9952,9951,9950,9949,9948,9947,9946,9945,9944,9943,9942,9941,9940,9939,9938,9937,9936,9935,9934,9933,9932,9931,9930,9929,9928,9927,9926,9925,9924,9923,9922,9921,9920,9919,9918,9917,9916,9915,9914,9913,9912,9911,9910,9909,9908,9907,9906,9905,9904,9903,9902,9901,9900,9899,9898,9897,9896,9895,9894,9893,9892,9891,9890,9889,9888,9887,9886,9885,9884,9883,9882,9881,9880,9879,9878,9877,9876,9875,9874,9873,9872,9871,9870,9869,9868,9867,9866,9865,9864,9863,9862,9861,9860,9859,9858,9857,9856,9855,9854,9853,9852,9851,9850,9849,9848,9847,9846,9845,9844,9843,9842,9841,9840,9839,9838,9837,9836,9835,9834,9833,9832,9831,9830,9829,9828,9827,9826,9825,9824,9823,9822,9821,9820,9819,9818,9817,9816,9815,9814,9813,9812,9811,9810,9809,9808,9807,9806,9805,9804,9803,9802,9801,9800,9799,9798,9797,9796,9795,9794,9793,9792,9791,9790,9789,9788,9787,9786,9785,9784,9783,9782,9781,9780,9779,9778,9777,9776,9775,9774,9773,9772,9771,9770,9769,9768,9767,9766,9765,9764,9763,9762,9761,9760,9759,9758,9757,9756,9755,9754,9753,9752,9751,9750,9749,9748,9747,9746,9745,9744,9743,9742,9741,9740,9739,9738,9737,9736,9735,9734,9733,9732,9731,9730,9729,9728,9727,9726,9725,9724,9723,9722,9721,9720,9719,9718,9717,9716,9715,9714,9713,9712,9711,9710,9709,9708,9707,9706,9705,9704,9703,9702,9701,9700,9699,9698,9697,9696,9695,9694,9693,9692,9691,9690,9689,9688,9687,9686,9685,9684,9683,9682,9681,9680,9679,9678,9677,9676,9675,9674,9673,9672,9671,9670,9669,9668,9667,9666,9665,9664,9663,9662,9661,9660,9659,9658,9657,9656,9655,9654,9653,9652,9651,9650,9649,9648,9647,9646,9645,9644,9643,9642,9641,9640,9639,9638,9637,9636,9635,9634,9633,9632,9631,9630,9629,9628,9627,9626,9625,9624,9623,9622,9621,9620,9619,9618,9617,9616,9615,9614,9613,9612,9611,9610,9609,9608,9607,9606,9605,9604,9603,9602,9601,9600,9599,9598,9597,9596,9595,9594,9593,9592,9591,9590,9589,9588,9587,9586,9585,9584,9583,9582,9581,9580,9579,9578,9577,9576,9575,9574,9573,9572,9571,9570,9569,9568,9567,9566,9565,9564,9563,9562,9561,9560,9559,9558,9557,9556,9555,9554,9553,9552,9551,9550,9549,9548,9547,9546,9545,9544,9543,9542,9541,9540,9539,9538,9537,9536,9535,9534,9533,9532,9531,9530,9529,9528,9527,9526,9525,9524,9523,9522,9521,9520,9519,9518,9517,9516,9515,9514,9513,9512,9511,9510,9509,9508,9507,9506,9505,9504,9503,9502,9501,9500,9499,9498,9497,9496,9495,9494,9493,9492,9491,9490,9489,9488,9487,9486,9485,9484,9483,9482,9481,9480,9479,9478,9477,9476,9475,9474,9473,9472,9471,9470,9469,9468,9467,9466,9465,9464,9463,9462,9461,9460,9459,9458,9457,9456,9455,9454,9453,9452,9451,9450,9449,9448,9447,9446,9445,9444,9443,9442,9441,9440,9439,9438,9437,9436,9435,9434,9433,9432,9431,9430,9429,9428,9427,9426,9425,9424,9423,9422,9421,9420,9419,9418,9417,9416,9415,9414,9413,9412,9411,9410,9409,9408,9407,9406,9405,9404,9403,9402,9401,9400,9399,9398,9397,9396,9395,9394,9393,9392,9391,9390,9389,9388,9387,9386,9385,9384,9383,9382,9381,9380,9379,9378,9377,9376,9375,9374,9373,9372,9371,9370,9369,9368,9367,9366,9365,9364,9363,9362,9361,9360,9359,9358,9357,9356,9355,9354,9353,9352,9351,9350,9349,9348,9347,9346,9345,9344,9343,9342,9341,9340,9339,9338,9337,9336,9335,9334,9333,9332,9331,9330,9329,9328,9327,9326,9325,9324,9323,9322,9321,9320,9319,9318,9317,9316,9315,9314,9313,9312,9311,9310,9309,9308,9307,9306,9305,9304,9303,9302,9301,9300,9299,9298,9297,9296,9295,9294,9293,9292,9291,9290,9289,9288,9287,9286,9285,9284,9283,9282,9281,9280,9279,9278,9277,9276,9275,9274,9273,9272,9271,9270,9269,9268,9267,9266,9265,9264,9263,9262,9261,9260,9259,9258,9257,9256,9255,9254,9253,9252,9251,9250,9249,9248,9247,9246,9245,9244,9243,9242,9241,9240,9239,9238,9237,9236,9235,9234,9233,9232,9231,9230,9229,9228,9227,9226,9225,9224,9223,9222,9221,9220,9219,9218,9217,9216,9215,9214,9213,9212,9211,9210,9209,9208,9207,9206,9205,9204,9203,9202,9201,9200,9199,9198,9197,9196,9195,9194,9193,9192,9191,9190,9189,9188,9187,9186,9185,9184,9183,9182,9181,9180,9179,9178,9177,9176,9175,9174,9173,9172,9171,9170,9169,9168,9167,9166,9165,9164,9163,9162,9161,9160,9159,9158,9157,9156,9155,9154,9153,9152,9151,9150,9149,9148,9147,9146,9145,9144,9143,9142,9141,9140,9139,9138,9137,9136,9135,9134,9133,9132,9131,9130,9129,9128,9127,9126,9125,9124,9123,9122,9121,9120,9119,9118,9117,9116,9115,9114,9113,9112,9111,9110,9109,9108,9107,9106,9105,9104,9103,9102,9101,9100,9099,9098,9097,9096,9095,9094,9093,9092,9091,9090,9089,9088,9087,9086,9085,9084,9083,9082,9081,9080,9079,9078,9077,9076,9075,9074,9073,9072,9071,9070,9069,9068,9067,9066,9065,9064,9063,9062,9061,9060,9059,9058,9057,9056,9055,9054,9053,9052,9051,9050,9049,9048,9047,9046,9045,9044,9043,9042,9041,9040,9039,9038,9037,9036,9035,9034,9033,9032,9031,9030,9029,9028,9027,9026,9025,9024,9023,9022,9021,9020,9019,9018,9017,9016,9015,9014,9013,9012,9011,9010,9009,9008,9007,9006,9005,9004,9003,9002,9001,9000,8999,8998,8997,8996,8995,8994,8993,8992,8991,8990,8989,8988,8987,8986,8985,8984,8983,8982,8981,8980,8979,8978,8977,8976,8975,8974,8973,8972,8971,8970,8969,8968,8967,8966,8965,8964,8963,8962,8961,8960,8959,8958,8957,8956,8955,8954,8953,8952,8951,8950,8949,8948,8947,8946,8945,8944,8943,8942,8941,8940,8939,8938,8937,8936,8935,8934,8933,8932,8931,8930,8929,8928,8927,8926,8925,8924,8923,8922,8921,8920,8919,8918,8917,8916,8915,8914,8913,8912,8911,8910,8909,8908,8907,8906,8905,8904,8903,8902,8901,8900,8899,8898,8897,8896,8895,8894,8893,8892,8891,8890,8889,8888,8887,8886,8885,8884,8883,8882,8881,8880,8879,8878,8877,8876,8875,8874,8873,8872,8871,8870,8869,8868,8867,8866,8865,8864,8863,8862,8861,8860,8859,8858,8857,8856,8855,8854,8853,8852,8851,8850,8849,8848,8847,8846,8845,8844,8843,8842,8841,8840,8839,8838,8837,8836,8835,8834,8833,8832,8831,8830,8829,8828,8827,8826,8825,8824,8823,8822,8821,8820,8819,8818,8817,8816,8815,8814,8813,8812,8811,8810,8809,8808,8807,8806,8805,8804,8803,8802,8801,8800,8799,8798,8797,8796,8795,8794,8793,8792,8791,8790,8789,8788,8787,8786,8785,8784,8783,8782,8781,8780,8779,8778,8777,8776,8775,8774,8773,8772,8771,8770,8769,8768,8767,8766,8765,8764,8763,8762,8761,8760,8759,8758,8757,8756,8755,8754,8753,8752,8751,8750,8749,8748,8747,8746,8745,8744,8743,8742,8741,8740,8739,8738,8737,8736,8735,8734,8733,8732,8731,8730,8729,8728,8727,8726,8725,8724,8723,8722,8721,8720,8719,8718,8717,8716,8715,8714,8713,8712,8711,8710,8709,8708,8707,8706,8705,8704,8703,8702,8701,8700,8699,8698,8697,8696,8695,8694,8693,8692,8691,8690,8689,8688,8687,8686,8685,8684,8683,8682,8681,8680,8679,8678,8677,8676,8675,8674,8673,8672,8671,8670,8669,8668,8667,8666,8665,8664,8663,8662,8661,8660,8659,8658,8657,8656,8655,8654,8653,8652,8651,8650,8649,8648,8647,8646,8645,8644,8643,8642,8641,8640,8639,8638,8637,8636,8635,8634,8633,8632,8631,8630,8629,8628,8627,8626,8625,8624,8623,8622,8621,8620,8619,8618,8617,8616,8615,8614,8613,8612,8611,8610,8609,8608,8607,8606,8605,8604,8603,8602,8601,8600,8599,8598,8597,8596,8595,8594,8593,8592,8591,8590,8589,8588,8587,8586,8585,8584,8583,8582,8581,8580,8579,8578,8577,8576,8575,8574,8573,8572,8571,8570,8569,8568,8567,8566,8565,8564,8563,8562,8561,8560,8559,8558,8557,8556,8555,8554,8553,8552,8551,8550,8549,8548,8547,8546,8545,8544,8543,8542,8541,8540,8539,8538,8537,8536,8535,8534,8533,8532,8531,8530,8529,8528,8527,8526,8525,8524,8523,8522,8521,8520,8519,8518,8517,8516,8515,8514,8513,8512,8511,8510,8509,8508,8507,8506,8505,8504,8503,8502,8501,8500,8499,8498,8497,8496,8495,8494,8493,8492,8491,8490,8489,8488,8487,8486,8485,8484,8483,8482,8481,8480,8479,8478,8477,8476,8475,8474,8473,8472,8471,8470,8469,8468,8467,8466,8465,8464,8463,8462,8461,8460,8459,8458,8457,8456,8455,8454,8453,8452,8451,8450,8449,8448,8447,8446,8445,8444,8443,8442,8441,8440,8439,8438,8437,8436,8435,8434,8433,8432,8431,8430,8429,8428,8427,8426,8425,8424,8423,8422,8421,8420,8419,8418,8417,8416,8415,8414,8413,8412,8411,8410,8409,8408,8407,8406,8405,8404,8403,8402,8401,8400,8399,8398,8397,8396,8395,8394,8393,8392,8391,8390,8389,8388,8387,8386,8385,8384,8383,8382,8381,8380,8379,8378,8377,8376,8375,8374,8373,8372,8371,8370,8369,8368,8367,8366,8365,8364,8363,8362,8361,8360,8359,8358,8357,8356,8355,8354,8353,8352,8351,8350,8349,8348,8347,8346,8345,8344,8343,8342,8341,8340,8339,8338,8337,8336,8335,8334,8333,8332,8331,8330,8329,8328,8327,8326,8325,8324,8323,8322,8321,8320,8319,8318,8317,8316,8315,8314,8313,8312,8311,8310,8309,8308,8307,8306,8305,8304,8303,8302,8301,8300,8299,8298,8297,8296,8295,8294,8293,8292,8291,8290,8289,8288,8287,8286,8285,8284,8283,8282,8281,8280,8279,8278,8277,8276,8275,8274,8273,8272,8271,8270,8269,8268,8267,8266,8265,8264,8263,8262,8261,8260,8259,8258,8257,8256,8255,8254,8253,8252,8251,8250,8249,8248,8247,8246,8245,8244,8243,8242,8241,8240,8239,8238,8237,8236,8235,8234,8233,8232,8231,8230,8229,8228,8227,8226,8225,8224,8223,8222,8221,8220,8219,8218,8217,8216,8215,8214,8213,8212,8211,8210,8209,8208,8207,8206,8205,8204,8203,8202,8201,8200,8199,8198,8197,8196,8195,8194,8193,8192,8191,8190,8189,8188,8187,8186,8185,8184,8183,8182,8181,8180,8179,8178,8177,8176,8175,8174,8173,8172,8171,8170,8169,8168,8167,8166,8165,8164,8163,8162,8161,8160,8159,8158,8157,8156,8155,8154,8153,8152,8151,8150,8149,8148,8147,8146,8145,8144,8143,8142,8141,8140,8139,8138,8137,8136,8135,8134,8133,8132,8131,8130,8129,8128,8127,8126,8125,8124,8123,8122,8121,8120,8119,8118,8117,8116,8115,8114,8113,8112,8111,8110,8109,8108,8107,8106,8105,8104,8103,8102,8101,8100,8099,8098,8097,8096,8095,8094,8093,8092,8091,8090,8089,8088,8087,8086,8085,8084,8083,8082,8081,8080,8079,8078,8077,8076,8075,8074,8073,8072,8071,8070,8069,8068,8067,8066,8065,8064,8063,8062,8061,8060,8059,8058,8057,8056,8055,8054,8053,8052,8051,8050,8049,8048,8047,8046,8045,8044,8043,8042,8041,8040,8039,8038,8037,8036,8035,8034,8033,8032,8031,8030,8029,8028,8027,8026,8025,8024,8023,8022,8021,8020,8019,8018,8017,8016,8015,8014,8013,8012,8011,8010,8009,8008,8007,8006,8005,8004,8003,8002,8001,8000,7999,7998,7997,7996,7995,7994,7993,7992,7991,7990,7989,7988,7987,7986,7985,7984,7983,7982,7981,7980,7979,7978,7977,7976,7975,7974,7973,7972,7971,7970,7969,7968,7967,7966,7965,7964,7963,7962,7961,7960,7959,7958,7957,7956,7955,7954,7953,7952,7951,7950,7949,7948,7947,7946,7945,7944,7943,7942,7941,7940,7939,7938,7937,7936,7935,7934,7933,7932,7931,7930,7929,7928,7927,7926,7925,7924,7923,7922,7921,7920,7919,7918,7917,7916,7915,7914,7913,7912,7911,7910,7909,7908,7907,7906,7905,7904,7903,7902,7901,7900,7899,7898,7897,7896,7895,7894,7893,7892,7891,7890,7889,7888,7887,7886,7885,7884,7883,7882,7881,7880,7879,7878,7877,7876,7875,7874,7873,7872,7871,7870,7869,7868,7867,7866,7865,7864,7863,7862,7861,7860,7859,7858,7857,7856,7855,7854,7853,7852,7851,7850,7849,7848,7847,7846,7845,7844,7843,7842,7841,7840,7839,7838,7837,7836,7835,7834,7833,7832,7831,7830,7829,7828,7827,7826,7825,7824,7823,7822,7821,7820,7819,7818,7817,7816,7815,7814,7813,7812,7811,7810,7809,7808,7807,7806,7805,7804,7803,7802,7801,7800,7799,7798,7797,7796,7795,7794,7793,7792,7791,7790,7789,7788,7787,7786,7785,7784,7783,7782,7781,7780,7779,7778,7777,7776,7775,7774,7773,7772,7771,7770,7769,7768,7767,7766,7765,7764,7763,7762,7761,7760,7759,7758,7757,7756,7755,7754,7753,7752,7751,7750,7749,7748,7747,7746,7745,7744,7743,7742,7741,7740,7739,7738,7737,7736,7735,7734,7733,7732,7731,7730,7729,7728,7727,7726,7725,7724,7723,7722,7721,7720,7719,7718,7717,7716,7715,7714,7713,7712,7711,7710,7709,7708,7707,7706,7705,7704,7703,7702,7701,7700,7699,7698,7697,7696,7695,7694,7693,7692,7691,7690,7689,7688,7687,7686,7685,7684,7683,7682,7681,7680,7679,7678,7677,7676,7675,7674,7673,7672,7671,7670,7669,7668,7667,7666,7665,7664,7663,7662,7661,7660,7659,7658,7657,7656,7655,7654,7653,7652,7651,7650,7649,7648,7647,7646,7645,7644,7643,7642,7641,7640,7639,7638,7637,7636,7635,7634,7633,7632,7631,7630,7629,7628,7627,7626,7625,7624,7623,7622,7621,7620,7619,7618,7617,7616,7615,7614,7613,7612,7611,7610,7609,7608,7607,7606,7605,7604,7603,7602,7601,7600,7599,7598,7597,7596,7595,7594,7593,7592,7591,7590,7589,7588,7587,7586,7585,7584,7583,7582,7581,7580,7579,7578,7577,7576,7575,7574,7573,7572,7571,7570,7569,7568,7567,7566,7565,7564,7563,7562,7561,7560,7559,7558,7557,7556,7555,7554,7553,7552,7551,7550,7549,7548,7547,7546,7545,7544,7543,7542,7541,7540,7539,7538,7537,7536,7535,7534,7533,7532,7531,7530,7529,7528,7527,7526,7525,7524,7523,7522,7521,7520,7519,7518,7517,7516,7515,7514,7513,7512,7511,7510,7509,7508,7507,7506,7505,7504,7503,7502,7501,7500,7499,7498,7497,7496,7495,7494,7493,7492,7491,7490,7489,7488,7487,7486,7485,7484,7483,7482,7481,7480,7479,7478,7477,7476,7475,7474,7473,7472,7471,7470,7469,7468,7467,7466,7465,7464,7463,7462,7461,7460,7459,7458,7457,7456,7455,7454,7453,7452,7451,7450,7449,7448,7447,7446,7445,7444,7443,7442,7441,7440,7439,7438,7437,7436,7435,7434,7433,7432,7431,7430,7429,7428,7427,7426,7425,7424,7423,7422,7421,7420,7419,7418,7417,7416,7415,7414,7413,7412,7411,7410,7409,7408,7407,7406,7405,7404,7403,7402,7401,7400,7399,7398,7397,7396,7395,7394,7393,7392,7391,7390,7389,7388,7387,7386,7385,7384,7383,7382,7381,7380,7379,7378,7377,7376,7375,7374,7373,7372,7371,7370,7369,7368,7367,7366,7365,7364,7363,7362,7361,7360,7359,7358,7357,7356,7355,7354,7353,7352,7351,7350,7349,7348,7347,7346,7345,7344,7343,7342,7341,7340,7339,7338,7337,7336,7335,7334,7333,7332,7331,7330,7329,7328,7327,7326,7325,7324,7323,7322,7321,7320,7319,7318,7317,7316,7315,7314,7313,7312,7311,7310,7309,7308,7307,7306,7305,7304,7303,7302,7301,7300,7299,7298,7297,7296,7295,7294,7293,7292,7291,7290,7289,7288,7287,7286,7285,7284,7283,7282,7281,7280,7279,7278,7277,7276,7275,7274,7273,7272,7271,7270,7269,7268,7267,7266,7265,7264,7263,7262,7261,7260,7259,7258,7257,7256,7255,7254,7253,7252,7251,7250,7249,7248,7247,7246,7245,7244,7243,7242,7241,7240,7239,7238,7237,7236,7235,7234,7233,7232,7231,7230,7229,7228,7227,7226,7225,7224,7223,7222,7221,7220,7219,7218,7217,7216,7215,7214,7213,7212,7211,7210,7209,7208,7207,7206,7205,7204,7203,7202,7201,7200,7199,7198,7197,7196,7195,7194,7193,7192,7191,7190,7189,7188,7187,7186,7185,7184,7183,7182,7181,7180,7179,7178,7177,7176,7175,7174,7173,7172,7171,7170,7169,7168,7167,7166,7165,7164,7163,7162,7161,7160,7159,7158,7157,7156,7155,7154,7153,7152,7151,7150,7149,7148,7147,7146,7145,7144,7143,7142,7141,7140,7139,7138,7137,7136,7135,7134,7133,7132,7131,7130,7129,7128,7127,7126,7125,7124,7123,7122,7121,7120,7119,7118,7117,7116,7115,7114,7113,7112,7111,7110,7109,7108,7107,7106,7105,7104,7103,7102,7101,7100,7099,7098,7097,7096,7095,7094,7093,7092,7091,7090,7089,7088,7087,7086,7085,7084,7083,7082,7081,7080,7079,7078,7077,7076,7075,7074,7073,7072,7071,7070,7069,7068,7067,7066,7065,7064,7063,7062,7061,7060,7059,7058,7057,7056,7055,7054,7053,7052,7051,7050,7049,7048,7047,7046,7045,7044,7043,7042,7041,7040,7039,7038,7037,7036,7035,7034,7033,7032,7031,7030,7029,7028,7027,7026,7025,7024,7023,7022,7021,7020,7019,7018,7017,7016,7015,7014,7013,7012,7011,7010,7009,7008,7007,7006,7005,7004,7003,7002,7001,7000,6999,6998,6997,6996,6995,6994,6993,6992,6991,6990,6989,6988,6987,6986,6985,6984,6983,6982,6981,6980,6979,6978,6977,6976,6975,6974,6973,6972,6971,6970,6969,6968,6967,6966,6965,6964,6963,6962,6961,6960,6959,6958,6957,6956,6955,6954,6953,6952,6951,6950,6949,6948,6947,6946,6945,6944,6943,6942,6941,6940,6939,6938,6937,6936,6935,6934,6933,6932,6931,6930,6929,6928,6927,6926,6925,6924,6923,6922,6921,6920,6919,6918,6917,6916,6915,6914,6913,6912,6911,6910,6909,6908,6907,6906,6905,6904,6903,6902,6901,6900,6899,6898,6897,6896,6895,6894,6893,6892,6891,6890,6889,6888,6887,6886,6885,6884,6883,6882,6881,6880,6879,6878,6877,6876,6875,6874,6873,6872,6871,6870,6869,6868,6867,6866,6865,6864,6863,6862,6861,6860,6859,6858,6857,6856,6855,6854,6853,6852,6851,6850,6849,6848,6847,6846,6845,6844,6843,6842,6841,6840,6839,6838,6837,6836,6835,6834,6833,6832,6831,6830,6829,6828,6827,6826,6825,6824,6823,6822,6821,6820,6819,6818,6817,6816,6815,6814,6813,6812,6811,6810,6809,6808,6807,6806,6805,6804,6803,6802,6801,6800,6799,6798,6797,6796,6795,6794,6793,6792,6791,6790,6789,6788,6787,6786,6785,6784,6783,6782,6781,6780,6779,6778,6777,6776,6775,6774,6773,6772,6771,6770,6769,6768,6767,6766,6765,6764,6763,6762,6761,6760,6759,6758,6757,6756,6755,6754,6753,6752,6751,6750,6749,6748,6747,6746,6745,6744,6743,6742,6741,6740,6739,6738,6737,6736,6735,6734,6733,6732,6731,6730,6729,6728,6727,6726,6725,6724,6723,6722,6721,6720,6719,6718,6717,6716,6715,6714,6713,6712,6711,6710,6709,6708,6707,6706,6705,6704,6703,6702,6701,6700,6699,6698,6697,6696,6695,6694,6693,6692,6691,6690,6689,6688,6687,6686,6685,6684,6683,6682,6681,6680,6679,6678,6677,6676,6675,6674,6673,6672,6671,6670,6669,6668,6667,6666,6665,6664,6663,6662,6661,6660,6659,6658,6657,6656,6655,6654,6653,6652,6651,6650,6649,6648,6647,6646,6645,6644,6643,6642,6641,6640,6639,6638,6637,6636,6635,6634,6633,6632,6631,6630,6629,6628,6627,6626,6625,6624,6623,6622,6621,6620,6619,6618,6617,6616,6615,6614,6613,6612,6611,6610,6609,6608,6607,6606,6605,6604,6603,6602,6601,6600,6599,6598,6597,6596,6595,6594,6593,6592,6591,6590,6589,6588,6587,6586,6585,6584,6583,6582,6581,6580,6579,6578,6577,6576,6575,6574,6573,6572,6571,6570,6569,6568,6567,6566,6565,6564,6563,6562,6561,6560,6559,6558,6557,6556,6555,6554,6553,6552,6551,6550,6549,6548,6547,6546,6545,6544,6543,6542,6541,6540,6539,6538,6537,6536,6535,6534,6533,6532,6531,6530,6529,6528,6527,6526,6525,6524,6523,6522,6521,6520,6519,6518,6517,6516,6515,6514,6513,6512,6511,6510,6509,6508,6507,6506,6505,6504,6503,6502,6501,6500,6499,6498,6497,6496,6495,6494,6493,6492,6491,6490,6489,6488,6487,6486,6485,6484,6483,6482,6481,6480,6479,6478,6477,6476,6475,6474,6473,6472,6471,6470,6469,6468,6467,6466,6465,6464,6463,6462,6461,6460,6459,6458,6457,6456,6455,6454,6453,6452,6451,6450,6449,6448,6447,6446,6445,6444,6443,6442,6441,6440,6439,6438,6437,6436,6435,6434,6433,6432,6431,6430,6429,6428,6427,6426,6425,6424,6423,6422,6421,6420,6419,6418,6417,6416,6415,6414,6413,6412,6411,6410,6409,6408,6407,6406,6405,6404,6403,6402,6401,6400,6399,6398,6397,6396,6395,6394,6393,6392,6391,6390,6389,6388,6387,6386,6385,6384,6383,6382,6381,6380,6379,6378,6377,6376,6375,6374,6373,6372,6371,6370,6369,6368,6367,6366,6365,6364,6363,6362,6361,6360,6359,6358,6357,6356,6355,6354,6353,6352,6351,6350,6349,6348,6347,6346,6345,6344,6343,6342,6341,6340,6339,6338,6337,6336,6335,6334,6333,6332,6331,6330,6329,6328,6327,6326,6325,6324,6323,6322,6321,6320,6319,6318,6317,6316,6315,6314,6313,6312,6311,6310,6309,6308,6307,6306,6305,6304,6303,6302,6301,6300,6299,6298,6297,6296,6295,6294,6293,6292,6291,6290,6289,6288,6287,6286,6285,6284,6283,6282,6281,6280,6279,6278,6277,6276,6275,6274,6273,6272,6271,6270,6269,6268,6267,6266,6265,6264,6263,6262,6261,6260,6259,6258,6257,6256,6255,6254,6253,6252,6251,6250,6249,6248,6247,6246,6245,6244,6243,6242,6241,6240,6239,6238,6237,6236,6235,6234,6233,6232,6231,6230,6229,6228,6227,6226,6225,6224,6223,6222,6221,6220,6219,6218,6217,6216,6215,6214,6213,6212,6211,6210,6209,6208,6207,6206,6205,6204,6203,6202,6201,6200,6199,6198,6197,6196,6195,6194,6193,6192,6191,6190,6189,6188,6187,6186,6185,6184,6183,6182,6181,6180,6179,6178,6177,6176,6175,6174,6173,6172,6171,6170,6169,6168,6167,6166,6165,6164,6163,6162,6161,6160,6159,6158,6157,6156,6155,6154,6153,6152,6151,6150,6149,6148,6147,6146,6145,6144,6143,6142,6141,6140,6139,6138,6137,6136,6135,6134,6133,6132,6131,6130,6129,6128,6127,6126,6125,6124,6123,6122,6121,6120,6119,6118,6117,6116,6115,6114,6113,6112,6111,6110,6109,6108,6107,6106,6105,6104,6103,6102,6101,6100,6099,6098,6097,6096,6095,6094,6093,6092,6091,6090,6089,6088,6087,6086,6085,6084,6083,6082,6081,6080,6079,6078,6077,6076,6075,6074,6073,6072,6071,6070,6069,6068,6067,6066,6065,6064,6063,6062,6061,6060,6059,6058,6057,6056,6055,6054,6053,6052,6051,6050,6049,6048,6047,6046,6045,6044,6043,6042,6041,6040,6039,6038,6037,6036,6035,6034,6033,6032,6031,6030,6029,6028,6027,6026,6025,6024,6023,6022,6021,6020,6019,6018,6017,6016,6015,6014,6013,6012,6011,6010,6009,6008,6007,6006,6005,6004,6003,6002,6001,6000,5999,5998,5997,5996,5995,5994,5993,5992,5991,5990,5989,5988,5987,5986,5985,5984,5983,5982,5981,5980,5979,5978,5977,5976,5975,5974,5973,5972,5971,5970,5969,5968,5967,5966,5965,5964,5963,5962,5961,5960,5959,5958,5957,5956,5955,5954,5953,5952,5951,5950,5949,5948,5947,5946,5945,5944,5943,5942,5941,5940,5939,5938,5937,5936,5935,5934,5933,5932,5931,5930,5929,5928,5927,5926,5925,5924,5923,5922,5921,5920,5919,5918,5917,5916,5915,5914,5913,5912,5911,5910,5909,5908,5907,5906,5905,5904,5903,5902,5901,5900,5899,5898,5897,5896,5895,5894,5893,5892,5891,5890,5889,5888,5887,5886,5885,5884,5883,5882,5881,5880,5879,5878,5877,5876,5875,5874,5873,5872,5871,5870,5869,5868,5867,5866,5865,5864,5863,5862,5861,5860,5859,5858,5857,5856,5855,5854,5853,5852,5851,5850,5849,5848,5847,5846,5845,5844,5843,5842,5841,5840,5839,5838,5837,5836,5835,5834,5833,5832,5831,5830,5829,5828,5827,5826,5825,5824,5823,5822,5821,5820,5819,5818,5817,5816,5815,5814,5813,5812,5811,5810,5809,5808,5807,5806,5805,5804,5803,5802,5801,5800,5799,5798,5797,5796,5795,5794,5793,5792,5791,5790,5789,5788,5787,5786,5785,5784,5783,5782,5781,5780,5779,5778,5777,5776,5775,5774,5773,5772,5771,5770,5769,5768,5767,5766,5765,5764,5763,5762,5761,5760,5759,5758,5757,5756,5755,5754,5753,5752,5751,5750,5749,5748,5747,5746,5745,5744,5743,5742,5741,5740,5739,5738,5737,5736,5735,5734,5733,5732,5731,5730,5729,5728,5727,5726,5725,5724,5723,5722,5721,5720,5719,5718,5717,5716,5715,5714,5713,5712,5711,5710,5709,5708,5707,5706,5705,5704,5703,5702,5701,5700,5699,5698,5697,5696,5695,5694,5693,5692,5691,5690,5689,5688,5687,5686,5685,5684,5683,5682,5681,5680,5679,5678,5677,5676,5675,5674,5673,5672,5671,5670,5669,5668,5667,5666,5665,5664,5663,5662,5661,5660,5659,5658,5657,5656,5655,5654,5653,5652,5651,5650,5649,5648,5647,5646,5645,5644,5643,5642,5641,5640,5639,5638,5637,5636,5635,5634,5633,5632,5631,5630,5629,5628,5627,5626,5625,5624,5623,5622,5621,5620,5619,5618,5617,5616,5615,5614,5613,5612,5611,5610,5609,5608,5607,5606,5605,5604,5603,5602,5601,5600,5599,5598,5597,5596,5595,5594,5593,5592,5591,5590,5589,5588,5587,5586,5585,5584,5583,5582,5581,5580,5579,5578,5577,5576,5575,5574,5573,5572,5571,5570,5569,5568,5567,5566,5565,5564,5563,5562,5561,5560,5559,5558,5557,5556,5555,5554,5553,5552,5551,5550,5549,5548,5547,5546,5545,5544,5543,5542,5541,5540,5539,5538,5537,5536,5535,5534,5533,5532,5531,5530,5529,5528,5527,5526,5525,5524,5523,5522,5521,5520,5519,5518,5517,5516,5515,5514,5513,5512,5511,5510,5509,5508,5507,5506,5505,5504,5503,5502,5501,5500,5499,5498,5497,5496,5495,5494,5493,5492,5491,5490,5489,5488,5487,5486,5485,5484,5483,5482,5481,5480,5479,5478,5477,5476,5475,5474,5473,5472,5471,5470,5469,5468,5467,5466,5465,5464,5463,5462,5461,5460,5459,5458,5457,5456,5455,5454,5453,5452,5451,5450,5449,5448,5447,5446,5445,5444,5443,5442,5441,5440,5439,5438,5437,5436,5435,5434,5433,5432,5431,5430,5429,5428,5427,5426,5425,5424,5423,5422,5421,5420,5419,5418,5417,5416,5415,5414,5413,5412,5411,5410,5409,5408,5407,5406,5405,5404,5403,5402,5401,5400,5399,5398,5397,5396,5395,5394,5393,5392,5391,5390,5389,5388,5387,5386,5385,5384,5383,5382,5381,5380,5379,5378,5377,5376,5375,5374,5373,5372,5371,5370,5369,5368,5367,5366,5365,5364,5363,5362,5361,5360,5359,5358,5357,5356,5355,5354,5353,5352,5351,5350,5349,5348,5347,5346,5345,5344,5343,5342,5341,5340,5339,5338,5337,5336,5335,5334,5333,5332,5331,5330,5329,5328,5327,5326,5325,5324,5323,5322,5321,5320,5319,5318,5317,5316,5315,5314,5313,5312,5311,5310,5309,5308,5307,5306,5305,5304,5303,5302,5301,5300,5299,5298,5297,5296,5295,5294,5293,5292,5291,5290,5289,5288,5287,5286,5285,5284,5283,5282,5281,5280,5279,5278,5277,5276,5275,5274,5273,5272,5271,5270,5269,5268,5267,5266,5265,5264,5263,5262,5261,5260,5259,5258,5257,5256,5255,5254,5253,5252,5251,5250,5249,5248,5247,5246,5245,5244,5243,5242,5241,5240,5239,5238,5237,5236,5235,5234,5233,5232,5231,5230,5229,5228,5227,5226,5225,5224,5223,5222,5221,5220,5219,5218,5217,5216,5215,5214,5213,5212,5211,5210,5209,5208,5207,5206,5205,5204,5203,5202,5201,5200,5199,5198,5197,5196,5195,5194,5193,5192,5191,5190,5189,5188,5187,5186,5185,5184,5183,5182,5181,5180,5179,5178,5177,5176,5175,5174,5173,5172,5171,5170,5169,5168,5167,5166,5165,5164,5163,5162,5161,5160,5159,5158,5157,5156,5155,5154,5153,5152,5151,5150,5149,5148,5147,5146,5145,5144,5143,5142,5141,5140,5139,5138,5137,5136,5135,5134,5133,5132,5131,5130,5129,5128,5127,5126,5125,5124,5123,5122,5121,5120,5119,5118,5117,5116,5115,5114,5113,5112,5111,5110,5109,5108,5107,5106,5105,5104,5103,5102,5101,5100,5099,5098,5097,5096,5095,5094,5093,5092,5091,5090,5089,5088,5087,5086,5085,5084,5083,5082,5081,5080,5079,5078,5077,5076,5075,5074,5073,5072,5071,5070,5069,5068,5067,5066,5065,5064,5063,5062,5061,5060,5059,5058,5057,5056,5055,5054,5053,5052,5051,5050,5049,5048,5047,5046,5045,5044,5043,5042,5041,5040,5039,5038,5037,5036,5035,5034,5033,5032,5031,5030,5029,5028,5027,5026,5025,5024,5023,5022,5021,5020,5019,5018,5017,5016,5015,5014,5013,5012,5011,5010,5009,5008,5007,5006,5005,5004,5003,5002,5001,5000,4999,4998,4997,4996,4995,4994,4993,4992,4991,4990,4989,4988,4987,4986,4985,4984,4983,4982,4981,4980,4979,4978,4977,4976,4975,4974,4973,4972,4971,4970,4969,4968,4967,4966,4965,4964,4963,4962,4961,4960,4959,4958,4957,4956,4955,4954,4953,4952,4951,4950,4949,4948,4947,4946,4945,4944,4943,4942,4941,4940,4939,4938,4937,4936,4935,4934,4933,4932,4931,4930,4929,4928,4927,4926,4925,4924,4923,4922,4921,4920,4919,4918,4917,4916,4915,4914,4913,4912,4911,4910,4909,4908,4907,4906,4905,4904,4903,4902,4901,4900,4899,4898,4897,4896,4895,4894,4893,4892,4891,4890,4889,4888,4887,4886,4885,4884,4883,4882,4881,4880,4879,4878,4877,4876,4875,4874,4873,4872,4871,4870,4869,4868,4867,4866,4865,4864,4863,4862,4861,4860,4859,4858,4857,4856,4855,4854,4853,4852,4851,4850,4849,4848,4847,4846,4845,4844,4843,4842,4841,4840,4839,4838,4837,4836,4835,4834,4833,4832,4831,4830,4829,4828,4827,4826,4825,4824,4823,4822,4821,4820,4819,4818,4817,4816,4815,4814,4813,4812,4811,4810,4809,4808,4807,4806,4805,4804,4803,4802,4801,4800,4799,4798,4797,4796,4795,4794,4793,4792,4791,4790,4789,4788,4787,4786,4785,4784,4783,4782,4781,4780,4779,4778,4777,4776,4775,4774,4773,4772,4771,4770,4769,4768,4767,4766,4765,4764,4763,4762,4761,4760,4759,4758,4757,4756,4755,4754,4753,4752,4751,4750,4749,4748,4747,4746,4745,4744,4743,4742,4741,4740,4739,4738,4737,4736,4735,4734,4733,4732,4731,4730,4729,4728,4727,4726,4725,4724,4723,4722,4721,4720,4719,4718,4717,4716,4715,4714,4713,4712,4711,4710,4709,4708,4707,4706,4705,4704,4703,4702,4701,4700,4699,4698,4697,4696,4695,4694,4693,4692,4691,4690,4689,4688,4687,4686,4685,4684,4683,4682,4681,4680,4679,4678,4677,4676,4675,4674,4673,4672,4671,4670,4669,4668,4667,4666,4665,4664,4663,4662,4661,4660,4659,4658,4657,4656,4655,4654,4653,4652,4651,4650,4649,4648,4647,4646,4645,4644,4643,4642,4641,4640,4639,4638,4637,4636,4635,4634,4633,4632,4631,4630,4629,4628,4627,4626,4625,4624,4623,4622,4621,4620,4619,4618,4617,4616,4615,4614,4613,4612,4611,4610,4609,4608,4607,4606,4605,4604,4603,4602,4601,4600,4599,4598,4597,4596,4595,4594,4593,4592,4591,4590,4589,4588,4587,4586,4585,4584,4583,4582,4581,4580,4579,4578,4577,4576,4575,4574,4573,4572,4571,4570,4569,4568,4567,4566,4565,4564,4563,4562,4561,4560,4559,4558,4557,4556,4555,4554,4553,4552,4551,4550,4549,4548,4547,4546,4545,4544,4543,4542,4541,4540,4539,4538,4537,4536,4535,4534,4533,4532,4531,4530,4529,4528,4527,4526,4525,4524,4523,4522,4521,4520,4519,4518,4517,4516,4515,4514,4513,4512,4511,4510,4509,4508,4507,4506,4505,4504,4503,4502,4501,4500,4499,4498,4497,4496,4495,4494,4493,4492,4491,4490,4489,4488,4487,4486,4485,4484,4483,4482,4481,4480,4479,4478,4477,4476,4475,4474,4473,4472,4471,4470,4469,4468,4467,4466,4465,4464,4463,4462,4461,4460,4459,4458,4457,4456,4455,4454,4453,4452,4451,4450,4449,4448,4447,4446,4445,4444,4443,4442,4441,4440,4439,4438,4437,4436,4435,4434,4433,4432,4431,4430,4429,4428,4427,4426,4425,4424,4423,4422,4421,4420,4419,4418,4417,4416,4415,4414,4413,4412,4411,4410,4409,4408,4407,4406,4405,4404,4403,4402,4401,4400,4399,4398,4397,4396,4395,4394,4393,4392,4391,4390,4389,4388,4387,4386,4385,4384,4383,4382,4381,4380,4379,4378,4377,4376,4375,4374,4373,4372,4371,4370,4369,4368,4367,4366,4365,4364,4363,4362,4361,4360,4359,4358,4357,4356,4355,4354,4353,4352,4351,4350,4349,4348,4347,4346,4345,4344,4343,4342,4341,4340,4339,4338,4337,4336,4335,4334,4333,4332,4331,4330,4329,4328,4327,4326,4325,4324,4323,4322,4321,4320,4319,4318,4317,4316,4315,4314,4313,4312,4311,4310,4309,4308,4307,4306,4305,4304,4303,4302,4301,4300,4299,4298,4297,4296,4295,4294,4293,4292,4291,4290,4289,4288,4287,4286,4285,4284,4283,4282,4281,4280,4279,4278,4277,4276,4275,4274,4273,4272,4271,4270,4269,4268,4267,4266,4265,4264,4263,4262,4261,4260,4259,4258,4257,4256,4255,4254,4253,4252,4251,4250,4249,4248,4247,4246,4245,4244,4243,4242,4241,4240,4239,4238,4237,4236,4235,4234,4233,4232,4231,4230,4229,4228,4227,4226,4225,4224,4223,4222,4221,4220,4219,4218,4217,4216,4215,4214,4213,4212,4211,4210,4209,4208,4207,4206,4205,4204,4203,4202,4201,4200,4199,4198,4197,4196,4195,4194,4193,4192,4191,4190,4189,4188,4187,4186,4185,4184,4183,4182,4181,4180,4179,4178,4177,4176,4175,4174,4173,4172,4171,4170,4169,4168,4167,4166,4165,4164,4163,4162,4161,4160,4159,4158,4157,4156,4155,4154,4153,4152,4151,4150,4149,4148,4147,4146,4145,4144,4143,4142,4141,4140,4139,4138,4137,4136,4135,4134,4133,4132,4131,4130,4129,4128,4127,4126,4125,4124,4123,4122,4121,4120,4119,4118,4117,4116,4115,4114,4113,4112,4111,4110,4109,4108,4107,4106,4105,4104,4103,4102,4101,4100,4099,4098,4097,4096,4095,4094,4093,4092,4091,4090,4089,4088,4087,4086,4085,4084,4083,4082,4081,4080,4079,4078,4077,4076,4075,4074,4073,4072,4071,4070,4069,4068,4067,4066,4065,4064,4063,4062,4061,4060,4059,4058,4057,4056,4055,4054,4053,4052,4051,4050,4049,4048,4047,4046,4045,4044,4043,4042,4041,4040,4039,4038,4037,4036,4035,4034,4033,4032,4031,4030,4029,4028,4027,4026,4025,4024,4023,4022,4021,4020,4019,4018,4017,4016,4015,4014,4013,4012,4011,4010,4009,4008,4007,4006,4005,4004,4003,4002,4001,4000,3999,3998,3997,3996,3995,3994,3993,3992,3991,3990,3989,3988,3987,3986,3985,3984,3983,3982,3981,3980,3979,3978,3977,3976,3975,3974,3973,3972,3971,3970,3969,3968,3967,3966,3965,3964,3963,3962,3961,3960,3959,3958,3957,3956,3955,3954,3953,3952,3951,3950,3949,3948,3947,3946,3945,3944,3943,3942,3941,3940,3939,3938,3937,3936,3935,3934,3933,3932,3931,3930,3929,3928,3927,3926,3925,3924,3923,3922,3921,3920,3919,3918,3917,3916,3915,3914,3913,3912,3911,3910,3909,3908,3907,3906,3905,3904,3903,3902,3901,3900,3899,3898,3897,3896,3895,3894,3893,3892,3891,3890,3889,3888,3887,3886,3885,3884,3883,3882,3881,3880,3879,3878,3877,3876,3875,3874,3873,3872,3871,3870,3869,3868,3867,3866,3865,3864,3863,3862,3861,3860,3859,3858,3857,3856,3855,3854,3853,3852,3851,3850,3849,3848,3847,3846,3845,3844,3843,3842,3841,3840,3839,3838,3837,3836,3835,3834,3833,3832,3831,3830,3829,3828,3827,3826,3825,3824,3823,3822,3821,3820,3819,3818,3817,3816,3815,3814,3813,3812,3811,3810,3809,3808,3807,3806,3805,3804,3803,3802,3801,3800,3799,3798,3797,3796,3795,3794,3793,3792,3791,3790,3789,3788,3787,3786,3785,3784,3783,3782,3781,3780,3779,3778,3777,3776,3775,3774,3773,3772,3771,3770,3769,3768,3767,3766,3765,3764,3763,3762,3761,3760,3759,3758,3757,3756,3755,3754,3753,3752,3751,3750,3749,3748,3747,3746,3745,3744,3743,3742,3741,3740,3739,3738,3737,3736,3735,3734,3733,3732,3731,3730,3729,3728,3727,3726,3725,3724,3723,3722,3721,3720,3719,3718,3717,3716,3715,3714,3713,3712,3711,3710,3709,3708,3707,3706,3705,3704,3703,3702,3701,3700,3699,3698,3697,3696,3695,3694,3693,3692,3691,3690,3689,3688,3687,3686,3685,3684,3683,3682,3681,3680,3679,3678,3677,3676,3675,3674,3673,3672,3671,3670,3669,3668,3667,3666,3665,3664,3663,3662,3661,3660,3659,3658,3657,3656,3655,3654,3653,3652,3651,3650,3649,3648,3647,3646,3645,3644,3643,3642,3641,3640,3639,3638,3637,3636,3635,3634,3633,3632,3631,3630,3629,3628,3627,3626,3625,3624,3623,3622,3621,3620,3619,3618,3617,3616,3615,3614,3613,3612,3611,3610,3609,3608,3607,3606,3605,3604,3603,3602,3601,3600,3599,3598,3597,3596,3595,3594,3593,3592,3591,3590,3589,3588,3587,3586,3585,3584,3583,3582,3581,3580,3579,3578,3577,3576,3575,3574,3573,3572,3571,3570,3569,3568,3567,3566,3565,3564,3563,3562,3561,3560,3559,3558,3557,3556,3555,3554,3553,3552,3551,3550,3549,3548,3547,3546,3545,3544,3543,3542,3541,3540,3539,3538,3537,3536,3535,3534,3533,3532,3531,3530,3529,3528,3527,3526,3525,3524,3523,3522,3521,3520,3519,3518,3517,3516,3515,3514,3513,3512,3511,3510,3509,3508,3507,3506,3505,3504,3503,3502,3501,3500,3499,3498,3497,3496,3495,3494,3493,3492,3491,3490,3489,3488,3487,3486,3485,3484,3483,3482,3481,3480,3479,3478,3477,3476,3475,3474,3473,3472,3471,3470,3469,3468,3467,3466,3465,3464,3463,3462,3461,3460,3459,3458,3457,3456,3455,3454,3453,3452,3451,3450,3449,3448,3447,3446,3445,3444,3443,3442,3441,3440,3439,3438,3437,3436,3435,3434,3433,3432,3431,3430,3429,3428,3427,3426,3425,3424,3423,3422,3421,3420,3419,3418,3417,3416,3415,3414,3413,3412,3411,3410,3409,3408,3407,3406,3405,3404,3403,3402,3401,3400,3399,3398,3397,3396,3395,3394,3393,3392,3391,3390,3389,3388,3387,3386,3385,3384,3383,3382,3381,3380,3379,3378,3377,3376,3375,3374,3373,3372,3371,3370,3369,3368,3367,3366,3365,3364,3363,3362,3361,3360,3359,3358,3357,3356,3355,3354,3353,3352,3351,3350,3349,3348,3347,3346,3345,3344,3343,3342,3341,3340,3339,3338,3337,3336,3335,3334,3333,3332,3331,3330,3329,3328,3327,3326,3325,3324,3323,3322,3321,3320,3319,3318,3317,3316,3315,3314,3313,3312,3311,3310,3309,3308,3307,3306,3305,3304,3303,3302,3301,3300,3299,3298,3297,3296,3295,3294,3293,3292,3291,3290,3289,3288,3287,3286,3285,3284,3283,3282,3281,3280,3279,3278,3277,3276,3275,3274,3273,3272,3271,3270,3269,3268,3267,3266,3265,3264,3263,3262,3261,3260,3259,3258,3257,3256,3255,3254,3253,3252,3251,3250,3249,3248,3247,3246,3245,3244,3243,3242,3241,3240,3239,3238,3237,3236,3235,3234,3233,3232,3231,3230,3229,3228,3227,3226,3225,3224,3223,3222,3221,3220,3219,3218,3217,3216,3215,3214,3213,3212,3211,3210,3209,3208,3207,3206,3205,3204,3203,3202,3201,3200,3199,3198,3197,3196,3195,3194,3193,3192,3191,3190,3189,3188,3187,3186,3185,3184,3183,3182,3181,3180,3179,3178,3177,3176,3175,3174,3173,3172,3171,3170,3169,3168,3167,3166,3165,3164,3163,3162,3161,3160,3159,3158,3157,3156,3155,3154,3153,3152,3151,3150,3149,3148,3147,3146,3145,3144,3143,3142,3141,3140,3139,3138,3137,3136,3135,3134,3133,3132,3131,3130,3129,3128,3127,3126,3125,3124,3123,3122,3121,3120,3119,3118,3117,3116,3115,3114,3113,3112,3111,3110,3109,3108,3107,3106,3105,3104,3103,3102,3101,3100,3099,3098,3097,3096,3095,3094,3093,3092,3091,3090,3089,3088,3087,3086,3085,3084,3083,3082,3081,3080,3079,3078,3077,3076,3075,3074,3073,3072,3071,3070,3069,3068,3067,3066,3065,3064,3063,3062,3061,3060,3059,3058,3057,3056,3055,3054,3053,3052,3051,3050,3049,3048,3047,3046,3045,3044,3043,3042,3041,3040,3039,3038,3037,3036,3035,3034,3033,3032,3031,3030,3029,3028,3027,3026,3025,3024,3023,3022,3021,3020,3019,3018,3017,3016,3015,3014,3013,3012,3011,3010,3009,3008,3007,3006,3005,3004,3003,3002,3001,3000,2999,2998,2997,2996,2995,2994,2993,2992,2991,2990,2989,2988,2987,2986,2985,2984,2983,2982,2981,2980,2979,2978,2977,2976,2975,2974,2973,2972,2971,2970,2969,2968,2967,2966,2965,2964,2963,2962,2961,2960,2959,2958,2957,2956,2955,2954,2953,2952,2951,2950,2949,2948,2947,2946,2945,2944,2943,2942,2941,2940,2939,2938,2937,2936,2935,2934,2933,2932,2931,2930,2929,2928,2927,2926,2925,2924,2923,2922,2921,2920,2919,2918,2917,2916,2915,2914,2913,2912,2911,2910,2909,2908,2907,2906,2905,2904,2903,2902,2901,2900,2899,2898,2897,2896,2895,2894,2893,2892,2891,2890,2889,2888,2887,2886,2885,2884,2883,2882,2881,2880,2879,2878,2877,2876,2875,2874,2873,2872,2871,2870,2869,2868,2867,2866,2865,2864,2863,2862,2861,2860,2859,2858,2857,2856,2855,2854,2853,2852,2851,2850,2849,2848,2847,2846,2845,2844,2843,2842,2841,2840,2839,2838,2837,2836,2835,2834,2833,2832,2831,2830,2829,2828,2827,2826,2825,2824,2823,2822,2821,2820,2819,2818,2817,2816,2815,2814,2813,2812,2811,2810,2809,2808,2807,2806,2805,2804,2803,2802,2801,2800,2799,2798,2797,2796,2795,2794,2793,2792,2791,2790,2789,2788,2787,2786,2785,2784,2783,2782,2781,2780,2779,2778,2777,2776,2775,2774,2773,2772,2771,2770,2769,2768,2767,2766,2765,2764,2763,2762,2761,2760,2759,2758,2757,2756,2755,2754,2753,2752,2751,2750,2749,2748,2747,2746,2745,2744,2743,2742,2741,2740,2739,2738,2737,2736,2735,2734,2733,2732,2731,2730,2729,2728,2727,2726,2725,2724,2723,2722,2721,2720,2719,2718,2717,2716,2715,2714,2713,2712,2711,2710,2709,2708,2707,2706,2705,2704,2703,2702,2701,2700,2699,2698,2697,2696,2695,2694,2693,2692,2691,2690,2689,2688,2687,2686,2685,2684,2683,2682,2681,2680,2679,2678,2677,2676,2675,2674,2673,2672,2671,2670,2669,2668,2667,2666,2665,2664,2663,2662,2661,2660,2659,2658,2657,2656,2655,2654,2653,2652,2651,2650,2649,2648,2647,2646,2645,2644,2643,2642,2641,2640,2639,2638,2637,2636,2635,2634,2633,2632,2631,2630,2629,2628,2627,2626,2625,2624,2623,2622,2621,2620,2619,2618,2617,2616,2615,2614,2613,2612,2611,2610,2609,2608,2607,2606,2605,2604,2603,2602,2601,2600,2599,2598,2597,2596,2595,2594,2593,2592,2591,2590,2589,2588,2587,2586,2585,2584,2583,2582,2581,2580,2579,2578,2577,2576,2575,2574,2573,2572,2571,2570,2569,2568,2567,2566,2565,2564,2563,2562,2561,2560,2559,2558,2557,2556,2555,2554,2553,2552,2551,2550,2549,2548,2547,2546,2545,2544,2543,2542,2541,2540,2539,2538,2537,2536,2535,2534,2533,2532,2531,2530,2529,2528,2527,2526,2525,2524,2523,2522,2521,2520,2519,2518,2517,2516,2515,2514,2513,2512,2511,2510,2509,2508,2507,2506,2505,2504,2503,2502,2501,2500,2499,2498,2497,2496,2495,2494,2493,2492,2491,2490,2489,2488,2487,2486,2485,2484,2483,2482,2481,2480,2479,2478,2477,2476,2475,2474,2473,2472,2471,2470,2469,2468,2467,2466,2465,2464,2463,2462,2461,2460,2459,2458,2457,2456,2455,2454,2453,2452,2451,2450,2449,2448,2447,2446,2445,2444,2443,2442,2441,2440,2439,2438,2437,2436,2435,2434,2433,2432,2431,2430,2429,2428,2427,2426,2425,2424,2423,2422,2421,2420,2419,2418,2417,2416,2415,2414,2413,2412,2411,2410,2409,2408,2407,2406,2405,2404,2403,2402,2401,2400,2399,2398,2397,2396,2395,2394,2393,2392,2391,2390,2389,2388,2387,2386,2385,2384,2383,2382,2381,2380,2379,2378,2377,2376,2375,2374,2373,2372,2371,2370,2369,2368,2367,2366,2365,2364,2363,2362,2361,2360,2359,2358,2357,2356,2355,2354,2353,2352,2351,2350,2349,2348,2347,2346,2345,2344,2343,2342,2341,2340,2339,2338,2337,2336,2335,2334,2333,2332,2331,2330,2329,2328,2327,2326,2325,2324,2323,2322,2321,2320,2319,2318,2317,2316,2315,2314,2313,2312,2311,2310,2309,2308,2307,2306,2305,2304,2303,2302,2301,2300,2299,2298,2297,2296,2295,2294,2293,2292,2291,2290,2289,2288,2287,2286,2285,2284,2283,2282,2281,2280,2279,2278,2277,2276,2275,2274,2273,2272,2271,2270,2269,2268,2267,2266,2265,2264,2263,2262,2261,2260,2259,2258,2257,2256,2255,2254,2253,2252,2251,2250,2249,2248,2247,2246,2245,2244,2243,2242,2241,2240,2239,2238,2237,2236,2235,2234,2233,2232,2231,2230,2229,2228,2227,2226,2225,2224,2223,2222,2221,2220,2219,2218,2217,2216,2215,2214,2213,2212,2211,2210,2209,2208,2207,2206,2205,2204,2203,2202,2201,2200,2199,2198,2197,2196,2195,2194,2193,2192,2191,2190,2189,2188,2187,2186,2185,2184,2183,2182,2181,2180,2179,2178,2177,2176,2175,2174,2173,2172,2171,2170,2169,2168,2167,2166,2165,2164,2163,2162,2161,2160,2159,2158,2157,2156,2155,2154,2153,2152,2151,2150,2149,2148,2147,2146,2145,2144,2143,2142,2141,2140,2139,2138,2137,2136,2135,2134,2133,2132,2131,2130,2129,2128,2127,2126,2125,2124,2123,2122,2121,2120,2119,2118,2117,2116,2115,2114,2113,2112,2111,2110,2109,2108,2107,2106,2105,2104,2103,2102,2101,2100,2099,2098,2097,2096,2095,2094,2093,2092,2091,2090,2089,2088,2087,2086,2085,2084,2083,2082,2081,2080,2079,2078,2077,2076,2075,2074,2073,2072,2071,2070,2069,2068,2067,2066,2065,2064,2063,2062,2061,2060,2059,2058,2057,2056,2055,2054,2053,2052,2051,2050,2049,2048,2047,2046,2045,2044,2043,2042,2041,2040,2039,2038,2037,2036,2035,2034,2033,2032,2031,2030,2029,2028,2027,2026,2025,2024,2023,2022,2021,2020,2019,2018,2017,2016,2015,2014,2013,2012,2011,2010,2009,2008,2007,2006,2005,2004,2003,2002,2001,2000,1999,1998,1997,1996,1995,1994,1993,1992,1991,1990,1989,1988,1987,1986,1985,1984,1983,1982,1981,1980,1979,1978,1977,1976,1975,1974,1973,1972,1971,1970,1969,1968,1967,1966,1965,1964,1963,1962,1961,1960,1959,1958,1957,1956,1955,1954,1953,1952,1951,1950,1949,1948,1947,1946,1945,1944,1943,1942,1941,1940,1939,1938,1937,1936,1935,1934,1933,1932,1931,1930,1929,1928,1927,1926,1925,1924,1923,1922,1921,1920,1919,1918,1917,1916,1915,1914,1913,1912,1911,1910,1909,1908,1907,1906,1905,1904,1903,1902,1901,1900,1899,1898,1897,1896,1895,1894,1893,1892,1891,1890,1889,1888,1887,1886,1885,1884,1883,1882,1881,1880,1879,1878,1877,1876,1875,1874,1873,1872,1871,1870,1869,1868,1867,1866,1865,1864,1863,1862,1861,1860,1859,1858,1857,1856,1855,1854,1853,1852,1851,1850,1849,1848,1847,1846,1845,1844,1843,1842,1841,1840,1839,1838,1837,1836,1835,1834,1833,1832,1831,1830,1829,1828,1827,1826,1825,1824,1823,1822,1821,1820,1819,1818,1817,1816,1815,1814,1813,1812,1811,1810,1809,1808,1807,1806,1805,1804,1803,1802,1801,1800,1799,1798,1797,1796,1795,1794,1793,1792,1791,1790,1789,1788,1787,1786,1785,1784,1783,1782,1781,1780,1779,1778,1777,1776,1775,1774,1773,1772,1771,1770,1769,1768,1767,1766,1765,1764,1763,1762,1761,1760,1759,1758,1757,1756,1755,1754,1753,1752,1751,1750,1749,1748,1747,1746,1745,1744,1743,1742,1741,1740,1739,1738,1737,1736,1735,1734,1733,1732,1731,1730,1729,1728,1727,1726,1725,1724,1723,1722,1721,1720,1719,1718,1717,1716,1715,1714,1713,1712,1711,1710,1709,1708,1707,1706,1705,1704,1703,1702,1701,1700,1699,1698,1697,1696,1695,1694,1693,1692,1691,1690,1689,1688,1687,1686,1685,1684,1683,1682,1681,1680,1679,1678,1677,1676,1675,1674,1673,1672,1671,1670,1669,1668,1667,1666,1665,1664,1663,1662,1661,1660,1659,1658,1657,1656,1655,1654,1653,1652,1651,1650,1649,1648,1647,1646,1645,1644,1643,1642,1641,1640,1639,1638,1637,1636,1635,1634,1633,1632,1631,1630,1629,1628,1627,1626,1625,1624,1623,1622,1621,1620,1619,1618,1617,1616,1615,1614,1613,1612,1611,1610,1609,1608,1607,1606,1605,1604,1603,1602,1601,1600,1599,1598,1597,1596,1595,1594,1593,1592,1591,1590,1589,1588,1587,1586,1585,1584,1583,1582,1581,1580,1579,1578,1577,1576,1575,1574,1573,1572,1571,1570,1569,1568,1567,1566,1565,1564,1563,1562,1561,1560,1559,1558,1557,1556,1555,1554,1553,1552,1551,1550,1549,1548,1547,1546,1545,1544,1543,1542,1541,1540,1539,1538,1537,1536,1535,1534,1533,1532,1531,1530,1529,1528,1527,1526,1525,1524,1523,1522,1521,1520,1519,1518,1517,1516,1515,1514,1513,1512,1511,1510,1509,1508,1507,1506,1505,1504,1503,1502,1501,1500,1499,1498,1497,1496,1495,1494,1493,1492,1491,1490,1489,1488,1487,1486,1485,1484,1483,1482,1481,1480,1479,1478,1477,1476,1475,1474,1473,1472,1471,1470,1469,1468,1467,1466,1465,1464,1463,1462,1461,1460,1459,1458,1457,1456,1455,1454,1453,1452,1451,1450,1449,1448,1447,1446,1445,1444,1443,1442,1441,1440,1439,1438,1437,1436,1435,1434,1433,1432,1431,1430,1429,1428,1427,1426,1425,1424,1423,1422,1421,1420,1419,1418,1417,1416,1415,1414,1413,1412,1411,1410,1409,1408,1407,1406,1405,1404,1403,1402,1401,1400,1399,1398,1397,1396,1395,1394,1393,1392,1391,1390,1389,1388,1387,1386,1385,1384,1383,1382,1381,1380,1379,1378,1377,1376,1375,1374,1373,1372,1371,1370,1369,1368,1367,1366,1365,1364,1363,1362,1361,1360,1359,1358,1357,1356,1355,1354,1353,1352,1351,1350,1349,1348,1347,1346,1345,1344,1343,1342,1341,1340,1339,1338,1337,1336,1335,1334,1333,1332,1331,1330,1329,1328,1327,1326,1325,1324,1323,1322,1321,1320,1319,1318,1317,1316,1315,1314,1313,1312,1311,1310,1309,1308,1307,1306,1305,1304,1303,1302,1301,1300,1299,1298,1297,1296,1295,1294,1293,1292,1291,1290,1289,1288,1287,1286,1285,1284,1283,1282,1281,1280,1279,1278,1277,1276,1275,1274,1273,1272,1271,1270,1269,1268,1267,1266,1265,1264,1263,1262,1261,1260,1259,1258,1257,1256,1255,1254,1253,1252,1251,1250,1249,1248,1247,1246,1245,1244,1243,1242,1241,1240,1239,1238,1237,1236,1235,1234,1233,1232,1231,1230,1229,1228,1227,1226,1225,1224,1223,1222,1221,1220,1219,1218,1217,1216,1215,1214,1213,1212,1211,1210,1209,1208,1207,1206,1205,1204,1203,1202,1201,1200,1199,1198,1197,1196,1195,1194,1193,1192,1191,1190,1189,1188,1187,1186,1185,1184,1183,1182,1181,1180,1179,1178,1177,1176,1175,1174,1173,1172,1171,1170,1169,1168,1167,1166,1165,1164,1163,1162,1161,1160,1159,1158,1157,1156,1155,1154,1153,1152,1151,1150,1149,1148,1147,1146,1145,1144,1143,1142,1141,1140,1139,1138,1137,1136,1135,1134,1133,1132,1131,1130,1129,1128,1127,1126,1125,1124,1123,1122,1121,1120,1119,1118,1117,1116,1115,1114,1113,1112,1111,1110,1109,1108,1107,1106,1105,1104,1103,1102,1101,1100,1099,1098,1097,1096,1095,1094,1093,1092,1091,1090,1089,1088,1087,1086,1085,1084,1083,1082,1081,1080,1079,1078,1077,1076,1075,1074,1073,1072,1071,1070,1069,1068,1067,1066,1065,1064,1063,1062,1061,1060,1059,1058,1057,1056,1055,1054,1053,1052,1051,1050,1049,1048,1047,1046,1045,1044,1043,1042,1041,1040,1039,1038,1037,1036,1035,1034,1033,1032,1031,1030,1029,1028,1027,1026,1025,1024,1023,1022,1021,1020,1019,1018,1017,1016,1015,1014,1013,1012,1011,1010,1009,1008,1007,1006,1005,1004,1003,1002,1001,1000,999,998,997,996,995,994,993,992,991,990,989,988,987,986,985,984,983,982,981,980,979,978,977,976,975,974,973,972,971,970,969,968,967,966,965,964,963,962,961,960,959,958,957,956,955,954,953,952,951,950,949,948,947,946,945,944,943,942,941,940,939,938,937,936,935,934,933,932,931,930,929,928,927,926,925,924,923,922,921,920,919,918,917,916,915,914,913,912,911,910,909,908,907,906,905,904,903,902,901,900,899,898,897,896,895,894,893,892,891,890,889,888,887,886,885,884,883,882,881,880,879,878,877,876,875,874,873,872,871,870,869,868,867,866,865,864,863,862,861,860,859,858,857,856,855,854,853,852,851,850,849,848,847,846,845,844,843,842,841,840,839,838,837,836,835,834,833,832,831,830,829,828,827,826,825,824,823,822,821,820,819,818,817,816,815,814,813,812,811,810,809,808,807,806,805,804,803,802,801,800,799,798,797,796,795,794,793,792,791,790,789,788,787,786,785,784,783,782,781,780,779,778,777,776,775,774,773,772,771,770,769,768,767,766,765,764,763,762,761,760,759,758,757,756,755,754,753,752,751,750,749,748,747,746,745,744,743,742,741,740,739,738,737,736,735,734,733,732,731,730,729,728,727,726,725,724,723,722,721,720,719,718,717,716,715,714,713,712,711,710,709,708,707,706,705,704,703,702,701,700,699,698,697,696,695,694,693,692,691,690,689,688,687,686,685,684,683,682,681,680,679,678,677,676,675,674,673,672,671,670,669,668,667,666,665,664,663,662,661,660,659,658,657,656,655,654,653,652,651,650,649,648,647,646,645,644,643,642,641,640,639,638,637,636,635,634,633,632,631,630,629,628,627,626,625,624,623,622,621,620,619,618,617,616,615,614,613,612,611,610,609,608,607,606,605,604,603,602,601,600,599,598,597,596,595,594,593,592,591,590,589,588,587,586,585,584,583,582,581,580,579,578,577,576,575,574,573,572,571,570,569,568,567,566,565,564,563,562,561,560,559,558,557,556,555,554,553,552,551,550,549,548,547,546,545,544,543,542,541,540,539,541,540,542,539,538,537,536,535,534,533,532,531,530,529,528,527,526,525,524,523,522,521,520,519,518,517,516,515,514,513,512,511,510,509,508,507,506,505,504,503,502,501,500,499,498,497,496,495,494,493,492,491,490,489,488,487,486,485,484,483,482,481,480,479,478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,463,462,461,460,459,458,457,456,455,454,453,452,451,450,449,448,447,446,445,444,443,442,441,440,439,438,437,436,435,434,433,432,431,430,429,428,427,426,425,424,423,422,421,420,419,418,417,416,415,414,413,412,411,410,409,408,407,406,405,404,403,402,401,400,399,398,397,396,395,394,393,392,391,390,389,388,387,386,385,384,383,382,381,380,379,378,377,376,375,374,373,372,371,370,369,368,367,366,365,364,363,362,361,360,359,358,357,356,355,354,353,352,351,350,349,348,347,346,345,344,343,342,341,340,339,338,337,336,335,334,333,332,331,330,329,328,327,326,325,324,323,322,321,320,319,318,317,316,315,314,313,312,311,310,309,308,307,306,305,304,303,302,301,300,299,298,297,296,295,294,293,292,291,290,289,288,287,286,285,284,283,282,281,280,279,278,277,276,275,274,273,272,271,270,269,268,267,266,265,264,263,262,261,260,259,258,257,256,255,254,253,252,251,250,249,248,247,246,245,244,243,242,241,240,239,238,237,236,235,234,233,232,231,230,229,228,227,226,225,224,223,222,221,220,219,218,217,216,215,214,213,212,211,210,209,208,207,206,205,204,203,202,201,200,199,198,197,196,195,194,193,192,191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172,171,170,169,168,167,166,165,164,163,162,161,160,159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144,143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]) 

   res = minimumTotalOfTriangle().doit2([[-1], [-2, -3]])
   res = minimumTotalOfTriangle().doit2([[-1], [2, 3], [1, -1, -3]])

   a = [[46],[43,61],[10,-16,3],[-26,41,36,-72],[-28,-76,-22,26,51],[56,-53,38,67,86,-45],[58,53,47,-52,-54,-95,56],[-54,-93,58,68,26,-4,-45,86],[75,28,27,12,33,98,35,87,1],[-13,20,25,-98,-13,11,-44,-77,-59,-97],[-53,-14,83,80,31,89,38,-1,15,-88,53],[-22,86,-41,-94,-25,68,-96,87,55,-18,-49,-25],[-93,-48,39,17,8,61,57,-13,-92,-79,-29,87,51],[-63,3,-72,29,-9,57,-93,-46,-84,88,29,83,69,-7],[15,-49,43,90,-43,94,29,50,-21,-33,-16,43,-26,4,90],[-61,-67,-96,18,-63,32,-91,93,16,-61,86,4,67,46,-27,-63],[-38,0,79,-48,56,51,80,-17,-70,-53,67,49,-3,-52,39,12,-43],[43,-93,-7,-48,91,-13,44,-69,-27,-74,74,95,-25,-88,-43,75,90,8],[8,41,-35,91,48,-12,35,-3,62,59,-86,-49,-83,56,-42,-14,84,-74,72],[6,-44,-78,31,-92,-82,-94,-81,-49,57,85,36,-34,4,77,-66,-71,-34,45,25],[-95,4,15,-45,-3,-52,-11,83,-67,15,32,38,47,54,-54,54,48,-72,72,75,85],[35,11,-72,-61,-11,-62,-33,31,82,68,35,-37,-16,66,37,31,-44,20,40,47,-71,-45],[-6,59,0,-51,7,5,97,-40,-10,32,70,-6,47,-41,31,-86,89,-10,59,1,29,-57,-32],[-34,73,0,62,-9,-53,91,45,17,50,-54,65,-65,50,40,-6,-83,-28,-59,-13,-80,0,94,-90],[-34,-39,68,67,89,-89,-88,-67,61,-12,71,-48,11,62,73,-72,-10,95,70,1,45,10,71,38,58],[-88,-98,54,-12,95,64,31,-44,9,-25,-77,20,-14,-45,-42,73,-74,-14,-16,65,-41,-12,-68,-45,-42,32],[76,44,-20,-8,3,-32,-7,-66,56,-11,97,-36,21,7,38,43,-96,-76,74,-62,73,-99,0,-66,42,58,21],[73,89,56,-18,43,0,61,-65,79,-71,27,-86,61,92,87,-98,-9,-29,39,-89,-49,39,85,-12,12,62,87,45],[4,23,-56,-46,12,99,35,-45,-24,-27,-34,-44,1,70,-54,-60,39,-67,-59,-70,-19,57,-59,31,-4,-97,96,85,64],[83,7,-55,-17,50,-2,72,49,-67,-96,-74,5,-30,-42,82,-60,3,98,78,12,-83,85,92,73,-97,24,-54,-95,20,-69],[45,-20,38,89,63,-12,-36,35,-85,-27,38,-83,77,84,-26,36,-99,53,12,56,-35,5,41,-42,-22,43,58,0,24,-45,31],[-31,34,-31,-65,-26,33,-2,85,24,70,1,40,24,-15,90,-63,-14,20,48,-81,85,-47,59,-80,7,-21,54,-92,-97,-91,15,-52],[19,60,-18,93,-30,79,55,94,49,-44,11,-27,18,-21,9,80,98,-65,98,60,-36,34,56,71,-87,10,55,-85,-5,-53,-38,-85,-93],[43,84,-47,-1,39,-53,-52,72,35,-3,-10,-86,82,-30,88,-83,-55,49,-19,78,5,-71,90,92,60,81,-13,-93,-80,1,89,39,-38,-81],[-62,-98,-57,-38,73,77,58,-60,67,40,-14,55,34,30,-19,91,-15,63,-80,-25,55,79,-67,-81,62,-71,-3,28,67,58,46,81,59,88,-57],[9,42,77,48,9,-6,-89,-58,-72,40,22,-81,-98,-15,-85,-24,-83,70,-15,-64,32,13,32,-63,-20,-10,60,-62,-73,48,-20,12,-9,-43,-62,76],[51,-52,-82,55,65,40,74,66,-98,88,-80,-81,59,4,-46,-32,94,62,5,-49,-48,-35,-11,-45,89,68,67,-43,-97,-95,-66,53,-71,-49,-15,93,67],[-41,37,69,-75,56,87,83,-63,-82,-49,-69,79,32,-18,-92,73,70,-37,63,15,-93,-80,17,87,-70,-53,-84,-42,32,86,-75,67,23,70,91,-44,34,51],[-8,51,79,23,7,11,81,-8,-38,28,31,-75,-57,37,-79,37,24,-72,60,16,-15,-31,-21,9,-63,-98,-43,-72,-43,90,79,49,19,58,-51,-74,-54,-93,-6],[7,34,-75,8,76,61,6,-10,-38,33,-49,55,-82,19,-66,3,32,-87,59,60,-31,27,16,94,-54,-49,-80,-52,-27,-74,42,80,59,66,-35,13,5,70,-97,43],[-20,-70,-25,-26,26,9,77,-42,21,13,94,66,-83,10,61,-38,37,57,-13,-89,83,-71,67,19,71,-91,-68,-47,79,-88,73,-41,-82,-52,33,43,56,-13,-98,-46,76],[72,-79,93,-17,58,-68,96,-8,18,-93,-25,23,50,71,-28,59,-97,1,15,90,-26,50,85,22,-17,28,-45,46,6,-14,0,-21,6,-30,38,-59,1,34,32,96,18,84],[-4,-32,55,67,-73,34,-54,18,2,19,-31,-13,-82,28,-85,-27,-25,-2,35,51,53,-59,-79,-9,-42,21,-98,66,-6,19,27,90,64,-18,34,67,93,79,-14,-5,-24,54,81],[-7,-18,72,42,33,-30,-23,-16,-77,-6,4,-10,28,-97,-8,-5,-4,-89,-78,-14,74,-19,97,42,-26,76,-72,68,-48,58,49,45,-60,-2,-36,73,68,41,-43,67,-65,38,-42,63],[40,49,-65,-64,36,-67,-1,-12,13,-4,-70,86,-51,-66,31,1,91,-43,-77,-69,55,-14,80,23,-96,-85,-33,-84,52,24,55,-8,-50,89,4,63,-78,79,-49,12,-25,-43,-25,24,-10],[-93,-98,-42,-37,-76,-35,-82,-14,-54,17,-10,-40,84,5,88,8,-40,-20,35,-74,60,-2,-76,40,48,35,91,-95,-89,-8,-29,93,-7,28,-44,-7,69,-26,79,91,67,-54,-72,51,27,-84],[-63,63,-28,71,65,-67,-54,88,49,93,1,40,74,-12,-90,-55,-19,2,49,13,72,-5,86,28,-13,31,73,14,-18,-23,30,18,-60,78,-34,-95,-89,11,69,36,4,-30,-23,-45,34,-14,-1],[-85,64,-75,28,13,20,-9,-59,83,-78,90,-3,-19,-33,-96,98,-17,59,-35,-36,69,75,-89,-17,-43,-43,36,11,91,98,87,82,62,88,-13,-24,-15,55,-7,-32,53,-16,42,-66,27,22,-67,87],[-19,-26,-49,-72,-51,-39,10,-18,18,-54,93,-14,-56,57,-32,82,45,55,-65,-69,-13,28,-25,-60,88,-83,-26,-8,16,6,-21,96,56,7,-99,81,67,10,-36,-38,32,-66,24,75,90,69,35,12,24],[69,19,-89,-26,71,-50,-61,87,0,31,-20,82,-90,-46,38,16,-46,20,-39,64,60,-1,-4,93,-99,-51,60,69,83,-51,-7,29,68,-20,80,39,6,-81,3,-93,49,60,65,36,-86,4,-71,-33,-99,-34],[-69,60,42,4,30,42,52,-10,11,12,15,80,-82,-17,-40,97,98,42,-83,-21,25,42,-61,-9,-45,-48,71,-16,18,71,26,26,31,-32,-93,-39,-90,35,27,20,-53,-58,0,-36,2,36,-61,-23,-44,-45,55],[80,73,93,-52,-71,-78,-81,12,17,66,-85,-80,-3,-17,-74,34,-8,60,-62,-87,83,-20,-11,-76,58,-74,-38,-65,-19,16,90,-62,-33,60,-37,-5,82,-42,83,-24,-75,97,-5,-2,-20,20,-67,72,-43,-30,61,-60],[26,-50,-37,-16,-25,25,19,32,-82,-14,70,-16,-54,-90,78,-95,-33,61,-20,-9,36,51,66,-84,-29,75,64,27,-55,25,43,48,52,-93,-91,-96,31,27,36,48,-87,-17,-90,-64,-8,87,-83,35,26,-3,-96,-38,-75],[69,-46,-27,44,95,76,65,20,20,13,-51,26,22,-47,-66,-74,88,58,-84,-52,67,-49,39,55,-33,-49,-42,40,-46,-4,42,-77,49,-85,66,44,90,32,-58,10,-78,-10,-87,20,42,-54,23,7,-95,38,54,48,65,-30],[3,-91,21,37,26,51,-67,-32,74,82,-18,17,3,-51,-74,44,36,-52,-88,25,44,30,48,-33,-62,29,81,68,-23,46,-61,80,32,36,17,-42,-13,27,2,-62,9,60,55,88,-91,80,10,21,-95,21,-53,26,-72,94,92],[-35,23,74,-89,99,-3,-74,56,-71,38,-49,-37,-75,77,64,-60,-37,24,71,-49,10,28,37,-69,33,-65,-46,-64,-37,-52,-95,4,70,78,14,47,-47,39,3,-42,-46,30,-2,-21,7,-38,-5,69,63,-34,97,-50,93,11,-20,3],[46,11,15,-91,58,20,-11,6,-25,-96,-47,27,19,32,62,73,-37,-40,-71,69,21,0,16,-39,65,-10,10,35,-99,67,-84,46,-22,30,31,-87,-50,-79,18,25,-99,47,-71,-4,-20,90,-31,42,-50,-26,-12,48,73,80,-91,15,-30],[-4,-72,-29,-60,-57,93,-6,72,25,6,99,22,-98,24,22,48,52,-82,-95,20,-36,46,69,14,-88,17,-35,91,3,56,-61,75,83,9,91,-97,-21,-15,52,80,67,51,-21,45,-48,-99,-29,80,95,-25,0,-64,98,-30,26,86,63,90],[77,-57,24,-84,-82,7,1,85,10,57,-30,-38,37,-85,89,-83,36,-59,93,-93,-79,65,-41,-2,77,-43,44,4,-57,7,-29,96,50,94,89,44,-21,-10,7,88,-76,53,-73,61,67,92,54,-19,-90,24,-13,-70,-10,22,4,-33,55,-52,47],[97,55,-81,71,-18,89,60,-97,-32,-73,9,-67,-49,-37,-64,88,-93,-72,42,-13,-63,-57,51,-56,32,-27,47,76,-71,72,0,-97,4,18,50,85,-15,10,64,52,14,-49,62,64,-10,97,29,-4,-97,-29,60,-61,-10,-12,-41,-77,60,83,75,65],[55,-25,45,-41,70,-5,-79,-45,82,61,83,-4,-88,45,-63,1,20,65,74,22,-87,34,37,2,98,96,1,58,56,-24,1,11,28,-77,46,-2,17,43,29,-24,4,12,71,16,-65,-92,93,54,72,67,-24,61,-22,-87,-36,-24,85,64,-88,41,-82],[-11,-71,45,11,51,-80,-95,-6,25,-19,75,-63,-71,-32,-52,-86,-39,-98,62,-94,-46,24,-40,-33,87,13,-71,28,1,70,22,89,75,-56,-23,27,-37,-42,97,87,15,72,-98,44,-60,-51,57,-22,-72,-4,-17,-19,-80,19,24,83,-68,53,-11,32,0,-89],[-2,-25,-45,74,78,-6,-90,53,-41,24,25,-40,-32,42,-15,-98,-80,12,-2,-21,70,17,97,-6,-22,-70,-53,66,38,46,53,-63,98,-92,87,53,-21,96,6,37,21,-68,73,65,50,-42,67,69,47,-58,-52,-6,35,-55,87,-87,-49,-88,55,89,57,9,-97],[32,-7,89,-14,71,86,91,-15,-16,99,-42,-51,49,-7,-84,-5,-83,-66,42,10,69,64,-26,81,-85,-15,14,-96,-80,-77,-94,51,-8,72,-86,-36,58,82,25,-58,81,83,-33,8,-47,-40,-97,-31,-7,22,55,-38,-14,-71,-79,0,14,34,-19,33,33,-37,-39,-75],[-65,-25,-12,92,-43,-86,-89,-85,73,-45,-1,-74,14,2,-29,-93,-99,-74,-54,-14,-46,-34,85,44,99,-57,-23,32,6,38,56,40,89,-78,10,-54,-88,-3,-63,61,51,36,86,-35,-85,-66,-28,-85,-41,17,0,-11,59,-38,-66,35,-18,-13,-33,87,-75,99,27,-86,97],[-86,-64,85,11,-27,46,-38,85,9,27,99,42,75,90,77,-31,-33,-33,-95,5,-23,39,86,63,82,73,65,58,-22,55,56,-9,91,18,78,-59,-35,-59,-97,73,44,-98,-7,-4,68,-30,41,-65,13,45,39,89,-16,26,53,-57,-24,18,-99,53,-50,33,-78,-82,-48,99],[-65,-7,-83,-63,-34,60,-85,58,-67,82,-94,73,-83,18,-5,33,8,55,-64,-62,97,11,32,75,-58,81,8,-60,99,36,-84,-66,-71,-67,-52,-5,69,-38,-70,-97,-55,-88,52,-62,30,-75,47,-85,79,82,-48,54,-29,83,29,-11,41,-63,28,17,73,43,51,-98,52,75,-27],[22,-63,-20,1,-42,-9,-70,-4,-79,-46,-80,-65,-66,-97,-37,87,-50,-77,16,38,64,29,-57,-19,-21,62,-91,-42,15,83,7,-86,97,86,14,-45,-22,43,27,-25,74,47,-13,-92,26,49,71,75,49,-36,-10,13,69,32,70,-51,-6,79,6,-91,39,-87,-78,36,76,12,68,-69],[-67,-5,-18,-93,-81,68,90,44,-5,61,-4,-56,-98,85,33,70,17,3,-81,-88,-41,1,96,75,-9,95,-12,-56,-16,-44,-26,16,51,55,-1,46,1,-11,-9,72,-73,86,-84,-95,49,25,75,-34,-95,70,-46,-36,-28,-49,-84,39,-54,3,82,29,59,-67,-77,-13,87,21,-90,-35,87],[0,-63,90,-36,-71,95,-87,53,47,-22,58,17,9,98,65,59,90,4,81,-7,-37,-13,-71,-5,-14,-8,-40,84,2,1,71,78,38,38,-58,43,10,-69,-26,-43,-14,-68,74,94,-93,39,30,96,-79,11,-34,-17,74,-28,55,-39,63,91,-55,-58,-8,92,-79,-93,30,-61,50,-82,-30,-76],[-26,32,-68,-75,26,-85,64,-44,87,61,43,-47,-79,-6,24,52,54,-35,43,98,-17,-87,90,3,-81,-2,19,45,15,65,45,65,-3,76,90,99,67,31,-68,54,-31,51,84,-11,-55,-15,-58,99,49,61,74,-90,73,42,12,69,-83,-92,-9,31,72,-63,-27,-54,-87,-37,-55,80,70,-47,11],[-61,-96,-5,5,-51,80,23,-75,6,-16,98,15,-65,40,-95,80,56,-88,-29,-36,61,7,37,-93,-3,76,-71,-46,24,-19,64,39,-38,-63,-56,10,-83,66,11,-1,-72,9,91,-61,-73,95,95,82,83,-34,-76,21,50,37,5,-53,-10,10,0,-86,90,-59,30,-71,-23,73,15,-7,17,-74,69,21],[35,60,59,61,32,54,20,-8,96,43,90,46,-20,-5,69,47,-95,-31,60,71,10,-10,-99,86,-59,15,-43,57,41,-97,-45,-47,39,90,-86,-29,44,33,39,17,-46,29,-36,33,-76,-90,-43,-95,-21,-82,76,65,-16,53,28,1,-55,61,-65,85,63,-11,-62,2,-21,-72,49,99,61,-11,17,91,94],[57,1,95,66,58,99,-78,75,52,86,-64,-18,-8,37,27,-47,71,12,93,-62,27,-5,16,54,-78,16,-8,-13,-90,-17,-19,43,84,-47,9,19,-70,8,-29,81,-6,6,-36,62,-80,90,-84,68,-21,-91,-94,82,-20,21,37,-22,-86,-94,64,-77,-34,-77,65,-73,-25,-48,45,-19,59,-84,-37,-70,-2,3],[92,18,-30,84,-14,25,92,-32,8,-51,88,-78,27,-97,-73,-9,-98,-8,-10,44,-5,42,95,-60,-77,31,-45,-38,60,30,41,29,-52,-89,13,10,13,5,54,-79,54,42,-58,-42,21,-55,25,0,14,-84,-56,-91,34,-61,-51,33,69,-20,95,6,-90,36,-64,-66,24,48,20,-63,-69,-26,-43,61,93,-25,-81],[-9,19,43,90,-90,35,-66,-81,-31,-51,-33,-97,94,23,74,-22,10,-13,13,20,-89,-62,-59,-76,-32,-9,-43,-94,-39,31,-76,52,-72,44,42,-63,-21,53,-45,25,-98,-2,4,73,98,-22,-49,8,64,40,-72,52,77,-55,75,-77,36,-67,-72,96,63,-71,48,67,72,-32,-95,-72,-79,-64,52,98,11,-44,71,9],[10,98,-83,-25,38,-79,-73,-7,-34,78,15,78,-89,19,74,51,47,0,18,19,44,-1,24,41,35,-24,39,-77,9,-12,31,-81,-37,47,-30,-98,67,-27,-29,-90,-48,85,87,-38,4,62,-87,-71,-61,8,47,59,-93,-29,0,18,24,-84,40,-67,3,-29,-72,43,94,-25,21,39,47,91,48,75,76,13,-85,-43,-48],[-96,-15,-10,11,-90,-74,-5,-43,25,-87,80,40,30,89,-79,77,94,63,49,-31,-16,-35,92,-25,-87,45,-72,2,59,-16,53,39,69,-80,-72,55,-55,22,-88,69,11,92,-13,-82,58,7,95,52,-53,21,97,30,85,90,81,74,35,-91,-23,-29,-31,-70,86,-85,-50,-86,69,-6,12,81,-59,-99,73,27,-82,8,-89,89],[-39,-43,10,-42,63,-5,-75,21,-30,36,6,46,83,74,75,70,89,-98,83,58,-27,-4,39,13,-4,-11,-83,-10,97,-73,-20,-65,-40,89,-31,99,-15,-6,20,54,-70,-74,-23,-86,99,-48,60,65,-69,43,24,3,-84,-60,-84,-12,6,-91,78,3,-65,-42,14,-29,-76,82,-30,8,-47,89,-61,-40,91,15,-50,90,44,-90,33],[51,52,-43,-46,45,-27,-54,-67,78,-46,87,-42,-35,-55,71,35,-54,54,81,53,-93,47,69,-34,38,-39,15,5,81,1,-62,32,-46,-29,85,75,44,-69,-92,22,-39,95,80,25,-83,51,-63,-38,-18,94,92,-34,41,38,8,-21,98,-99,61,80,1,98,12,31,-53,-25,6,90,5,14,-11,43,-14,-31,-32,-21,97,-18,41,-44],[-24,10,21,-82,-52,-93,-27,-54,-93,-89,-97,7,86,-8,-61,-67,66,44,-77,-52,-65,-12,90,-3,57,-64,76,31,17,-6,86,69,-96,-15,63,-49,-9,-86,-27,-26,-76,-47,80,-90,44,95,-81,10,17,-82,34,51,6,25,-51,-60,60,-98,70,-46,-5,33,99,-2,94,63,25,-38,76,74,35,76,-96,-7,63,47,-12,81,-66,-95,99],[68,33,5,-30,58,44,-93,59,-9,-63,-69,-99,-64,28,95,75,-70,-66,28,80,46,5,84,-61,-32,31,3,-51,42,8,-52,-13,-82,29,56,75,-50,62,11,40,98,41,18,-89,-54,-10,86,-48,23,14,-68,-31,95,-84,-16,-37,24,87,-11,-34,-28,13,52,-11,-57,8,-59,-8,-53,28,-90,-78,-31,27,-68,-9,93,94,42,16,-14,73],[62,-19,89,-54,44,-10,-67,-67,55,4,45,-16,69,64,68,-90,-66,-85,14,-80,-87,59,23,-79,-50,16,-84,91,-91,1,42,70,58,8,-83,2,97,-74,11,29,30,-66,-87,-24,97,80,-37,-92,71,76,-73,83,36,49,80,85,-58,95,54,-49,-27,-4,-79,-68,80,-86,10,77,-60,98,-17,46,-68,-5,-78,-94,-48,-16,-86,-77,-62,-83,82],[73,43,62,35,84,58,-34,-65,-92,38,-67,-84,18,-54,3,-28,-15,1,54,-69,32,-51,-70,14,0,-10,4,-1,27,21,-19,-23,-59,-56,-87,-75,78,-45,-63,62,93,-31,78,11,14,-42,83,76,58,14,-93,-33,63,-87,80,-60,3,-15,39,-93,82,96,-16,99,-60,-27,-76,94,27,-63,57,20,5,12,-91,96,69,91,72,4,-18,55,70,-78],[68,50,-38,-52,-88,77,-46,70,73,37,69,90,-90,70,61,37,-93,18,-43,-11,-93,-35,-15,52,-67,-66,-44,-8,88,-74,13,56,53,74,80,64,28,-65,35,-21,71,-19,-54,58,-49,-93,-5,-65,2,28,23,8,70,84,-62,79,-82,-7,-29,82,19,84,16,-28,35,-4,-87,-59,30,24,19,-21,-94,41,-63,-67,47,8,-56,-74,-64,43,34,82,27],[48,62,21,-59,-90,-19,59,70,96,-92,-17,-8,97,0,99,21,95,-22,3,36,14,36,-40,98,79,-14,-66,23,96,93,-73,44,32,25,84,41,-94,21,-11,-98,5,48,-30,2,-52,-31,-76,-57,23,26,78,-86,-61,-62,-88,95,23,-77,-5,-4,-84,21,-60,47,-54,-75,-35,-72,22,53,-94,-73,1,-24,29,25,21,52,67,-78,-45,22,-65,-29,60,-76],[-34,-40,-54,60,33,-39,-19,72,-92,4,73,-51,8,-5,-97,14,22,-20,89,-49,-94,-13,79,49,8,-66,-28,20,4,-91,43,69,-55,88,6,77,-74,87,27,-90,-32,0,-42,75,95,-63,-11,17,-6,-45,67,-24,19,46,-75,-96,56,-27,23,-39,-19,-57,-93,3,-92,13,-43,-67,-23,83,-81,21,-16,-23,-27,-21,-10,39,72,83,70,39,-41,-11,-38,-39,-30],[94,33,92,-68,91,-87,-61,-6,-80,28,27,-70,81,11,-52,-21,94,24,51,-50,91,-10,-78,74,-62,37,-89,26,75,-29,95,69,80,65,-98,71,77,-83,-58,73,44,69,-97,2,-20,-49,80,-49,51,8,0,42,75,-2,17,-87,-65,4,15,-90,74,11,78,54,-47,56,3,-93,72,21,79,-7,-10,82,94,46,-90,51,73,60,-63,-50,3,-88,47,96,-76,58],[0,38,67,-49,-74,23,81,-22,-21,-16,-39,-71,82,-59,21,-51,99,-7,72,-91,-79,45,45,-43,95,-52,-32,19,-79,-32,-22,-3,-93,-78,47,-91,44,29,-36,-99,89,24,-94,71,41,26,-79,40,95,92,25,93,14,-29,-50,-14,-5,-5,-94,16,62,-40,89,45,-19,14,54,-97,-80,-82,79,-91,18,84,57,-40,10,54,76,-17,23,2,-24,-86,49,2,0,-56,96],[-18,36,36,41,26,-19,98,-60,-88,-99,-41,-94,79,-56,24,63,77,60,-49,8,36,10,-69,-85,62,-55,63,-36,21,-92,-62,-97,20,73,20,-54,-46,-5,-38,-57,-27,-3,-52,-71,18,48,69,-5,8,-80,-96,-78,6,-89,-64,-32,-45,76,31,52,60,68,31,-20,41,-49,3,72,23,64,91,95,-61,-61,-76,56,87,92,-49,-28,88,-69,-7,-6,-58,6,61,-4,-41,-30],[-74,-81,-85,56,-2,33,84,-99,5,7,42,-27,-21,80,11,2,13,-25,-28,63,24,-40,94,93,31,-64,-1,-31,8,57,38,33,52,30,-10,-49,-37,-26,-72,44,57,46,-83,-64,3,27,14,-84,79,85,79,3,-77,50,-4,53,62,72,-78,-30,6,37,80,-41,-33,-53,-14,29,-3,-10,-50,-46,-63,-34,-34,39,69,79,55,48,65,11,-72,87,-39,24,17,99,-27,15,-54],[55,-48,-74,-86,-5,-51,-24,-99,45,66,-50,75,79,15,-59,18,-38,-79,-50,-90,62,60,-62,49,97,38,-34,96,87,57,-80,42,-90,-55,33,-19,-29,85,-41,-84,51,8,91,7,-99,-91,-74,-38,-71,-25,-52,90,-87,-38,16,86,76,58,60,63,16,79,-17,2,-99,92,59,-29,77,-82,-36,6,3,-45,-87,3,-60,-85,41,-54,-10,65,-87,-21,-72,29,-35,-96,-36,-75,44,56],[-96,-96,-65,81,95,94,-48,49,-88,15,-45,14,46,-32,93,86,-41,11,-68,25,-23,-56,-96,4,49,-54,-16,90,-30,-95,46,-49,-92,81,-68,79,75,-40,29,63,75,83,-45,-2,-72,-52,-16,-13,59,-8,-88,-87,13,92,-7,-38,-62,76,-48,-16,58,75,34,42,33,42,22,8,-97,-72,-52,54,87,2,-48,92,50,36,-44,-14,-95,-56,-2,17,-64,90,79,-50,43,-92,34,-22,59],[-55,-79,-8,87,19,76,66,23,-75,20,10,26,71,-21,-47,7,34,15,-11,78,-87,-94,90,79,61,-59,0,46,51,77,5,95,74,97,59,-7,73,25,-84,74,-55,3,-22,-83,81,7,0,-7,-77,88,-29,-88,94,-62,68,32,-22,-32,-22,-94,-78,83,-98,96,57,60,-34,7,-14,-41,-18,30,61,36,23,19,-57,-76,-88,-35,88,-41,-23,82,-3,-55,15,51,-11,69,57,10,52,58],[6,9,-5,72,-83,57,-69,-25,-35,68,-89,87,-13,-47,87,-24,-5,76,34,48,35,-69,92,-73,82,-42,96,39,67,25,-26,-49,-65,45,99,-72,3,-70,-21,44,74,-34,31,-62,18,-4,13,89,-28,-52,37,-93,-22,6,-89,-40,63,-93,75,8,31,-74,58,42,48,57,46,-49,63,-98,71,37,-33,2,74,62,97,-12,51,-54,35,-11,-70,89,94,-60,-73,58,-77,-98,-57,53,-95,-99,-27],[52,57,95,79,-3,97,50,-66,-36,-71,84,-74,-96,-28,77,-51,83,-57,-22,73,-63,-6,99,71,16,77,-86,-53,81,90,-4,10,24,-9,-11,-79,-35,-84,-69,29,-55,-84,31,-52,-36,-15,-27,-52,27,28,97,41,-78,96,12,15,50,3,61,9,-7,-66,-81,-82,24,-15,-62,66,0,-31,-5,21,-16,-97,68,24,-35,-58,71,91,69,68,32,67,41,-78,-18,-8,24,-80,77,-83,-47,95,-66,54],[-43,-28,20,57,17,91,-22,77,70,-76,1,-65,-58,-27,-96,87,-82,35,54,36,56,-86,-95,-20,-90,81,-26,-60,53,7,93,-89,55,-10,67,-51,-42,-78,-74,-72,-78,27,-60,-37,76,-57,-50,70,54,81,6,11,71,-13,67,80,-32,-59,-80,-78,25,89,-68,-20,-44,75,29,-10,73,31,-5,95,-65,34,-42,-89,76,-15,58,30,-57,-59,-82,-86,28,62,70,72,79,67,70,4,33,-98,61,66,53],[-33,-44,27,74,50,-1,-90,-16,56,96,-63,-82,54,44,-40,95,38,-50,0,0,97,-28,-43,64,-57,60,-26,-79,-2,-60,51,41,-4,-22,16,-54,53,25,7,9,21,20,4,-47,-59,40,-75,79,67,24,-44,64,72,12,5,91,-50,78,89,47,-81,40,-11,-9,94,81,13,47,6,-80,-67,-96,17,36,-44,57,-46,-20,13,-79,80,69,84,53,-19,-34,21,7,-56,10,-45,-61,-50,20,29,-79,-22,-80],[67,83,-61,-99,63,32,13,-80,-10,43,-24,-97,63,-43,48,24,86,-70,89,7,36,-89,-82,67,-74,-56,-36,32,-58,41,51,-91,1,66,85,-35,-1,-24,-39,65,-81,36,67,59,92,16,-40,78,22,-73,-14,-65,-63,-20,79,-38,0,-80,70,18,61,21,27,-61,-12,-11,3,86,41,63,51,37,-23,-5,-27,-31,87,32,-52,-14,58,10,-2,71,66,-23,-66,-57,-4,-96,61,-66,2,-35,-50,89,30,29,52],[-51,-30,-20,85,46,74,-65,-85,39,66,-61,-75,25,25,22,-4,-32,75,6,11,-51,-13,-51,-41,88,-10,8,54,-80,-62,6,-55,7,85,-93,-70,36,-59,-56,-25,-92,-40,-23,9,84,75,81,-70,51,-12,17,99,51,65,-42,16,-68,43,-53,-72,80,52,-27,-36,14,-21,-7,-73,20,13,-21,4,72,55,-87,34,7,93,40,-42,-42,-43,-66,85,98,-31,1,-70,-88,47,-43,68,-24,6,-68,66,85,1,70,-18],[90,-51,85,63,80,74,-26,-13,44,-86,22,-97,-53,55,64,-55,-76,-57,-26,-65,66,7,79,-80,-86,-89,85,75,-12,55,-66,-21,80,95,-81,37,69,-31,-75,13,-18,23,-8,5,-22,-66,49,-21,-24,99,-10,-58,6,-30,-39,-4,-20,-76,-52,45,55,-19,-99,36,-24,-81,-50,-55,-13,-26,35,45,73,-96,-50,-48,-63,75,30,-11,74,-80,31,-43,-11,68,30,46,91,77,-32,47,-41,-32,-40,11,-14,9,33,49,60],[-32,-29,33,-52,20,61,-38,-28,-32,50,-54,-12,-42,-21,53,-73,-91,-24,-82,63,20,41,-78,87,77,9,-50,-13,-58,98,-76,-14,-31,56,34,65,-5,95,-63,62,22,-41,-73,80,38,57,-93,23,-67,-99,-14,53,42,-16,17,-4,93,67,82,-65,42,82,21,-88,16,-68,53,-89,-96,67,72,25,-74,99,-18,40,33,-12,-36,65,-34,49,-5,84,-89,-87,-20,-96,56,-60,-85,-2,-78,35,-14,37,43,-83,47,46,83,-3],[-51,85,-27,30,26,-94,95,89,47,-39,15,-80,-78,2,-91,1,5,64,40,-3,-61,62,-91,2,-24,52,18,-76,-25,1,-3,23,-14,69,-69,88,51,-74,54,-2,-37,-53,-6,-16,48,2,84,-69,-34,2,27,-18,-59,35,83,16,-36,1,16,39,78,-87,-38,-59,58,-31,-70,-14,-6,83,84,33,-70,-45,93,55,57,55,85,-77,-43,12,4,-3,-76,-36,-87,-12,64,29,-73,42,18,-35,60,-23,34,89,39,-95,49,0,15],[56,55,8,11,12,-37,-4,11,-4,84,92,92,-92,-44,82,-28,-79,-12,-2,39,82,40,-1,-64,-49,-35,75,-68,-85,-25,46,70,-70,-68,-19,41,-6,53,-47,90,37,-55,59,21,0,18,93,-3,82,-32,-63,65,84,12,-99,-65,77,52,-33,68,-72,89,15,-43,-79,72,75,-8,25,-72,-41,-61,-51,94,36,48,13,29,-77,-28,74,-41,-63,35,47,-85,70,1,66,-86,-31,70,79,83,-72,-99,55,-97,-8,-43,-93,50,-5,-45],[21,-91,79,-66,37,78,-17,-12,-86,-4,-76,61,10,70,-38,-46,60,8,-99,39,-32,-72,39,-76,-93,-92,-43,89,34,29,-79,-44,37,77,-34,-49,55,48,39,69,-55,39,7,31,9,45,61,-31,-47,62,84,21,66,24,21,73,8,77,39,-80,-17,60,-25,-80,14,17,-29,-54,-34,86,-85,10,25,-2,-82,-89,-56,79,-44,-27,41,-60,70,7,40,-9,-43,-51,-54,73,-32,28,10,19,25,-76,-64,95,-31,-22,81,-39,87,-17,58],[82,-7,78,61,48,-71,-21,64,98,62,5,-33,96,53,-11,69,97,93,-21,-7,18,2,28,-10,47,-93,-52,-92,70,30,43,52,99,-2,-10,24,26,45,-11,25,8,93,68,4,23,-43,-27,-3,-50,28,89,68,-93,-6,-42,53,0,-17,38,-52,-87,-19,76,89,55,-56,13,-18,88,-98,83,-4,71,51,76,-29,-92,-74,67,-66,53,33,-98,59,-72,-63,-10,4,19,-72,51,8,8,5,-3,-60,48,87,21,13,88,4,86,37,-68,62],[-92,-61,65,75,-27,18,-15,-49,-45,12,-36,44,-83,59,71,44,-55,-44,-51,41,-5,73,28,-83,-13,-6,-3,-27,-69,29,-88,-85,44,76,66,93,-28,-48,-55,26,63,-15,-30,56,-55,-59,1,-11,-27,49,-93,44,0,12,60,86,-94,-65,-64,-87,40,-53,-73,-16,-99,93,-22,-28,-78,-1,97,84,60,-56,41,-95,-39,-81,-30,33,44,-46,-23,-56,65,-85,-93,70,-74,-58,59,65,-34,85,-74,-57,55,-20,14,53,55,-12,38,16,31,-44,-3],[91,-26,67,1,-82,97,77,-61,62,68,-55,9,93,-36,-32,35,6,-70,61,48,62,-59,-61,15,96,26,-70,-11,-66,-15,85,-98,35,29,2,30,26,-44,45,-12,-98,89,96,71,-70,-36,7,12,-29,-55,-63,-67,-38,-25,47,-65,77,77,23,87,-61,9,88,51,-62,-33,-19,64,23,-97,-71,24,68,-74,-5,98,-34,78,10,36,-77,47,45,-15,98,-7,19,53,-30,-80,40,-15,28,29,-64,42,95,-7,-17,-5,-5,-11,95,-36,-9,-32,-61,56],[-54,25,-30,-54,-51,-85,7,-75,-16,-74,77,30,-78,17,-84,26,-77,-49,-31,95,21,28,-33,-84,-83,-37,-44,7,7,-29,-59,52,96,-13,74,-78,-22,-19,-54,62,-16,-77,-31,5,17,-16,-68,16,12,-23,-12,-67,81,55,-75,98,94,-42,-18,1,28,22,-70,24,85,81,46,-36,-38,68,-97,45,91,-29,-72,-15,32,-41,77,-56,12,-34,-24,-7,97,-23,-32,91,34,50,-31,-37,-51,-25,63,-65,-44,-14,-25,18,-45,-23,-60,-77,24,-33,-16,-44,2],[-39,-1,-86,26,51,-16,23,-71,51,-9,39,1,59,-98,50,-65,42,84,-33,-72,-64,84,-41,12,-98,-19,-87,-32,41,-31,70,-97,67,60,28,-4,-56,-71,1,95,19,-60,-27,-44,-81,-77,-33,60,83,33,64,-81,-5,-76,7,-4,-19,20,40,-77,88,10,-75,32,-52,29,-95,-32,34,5,-37,-46,22,36,-14,40,35,52,-23,-4,-15,-59,14,56,-59,98,-48,22,18,92,21,-17,-21,45,91,3,-49,73,71,85,-22,-66,-84,76,46,1,16,-41,-70,69],[54,-9,-89,-55,-52,-49,-57,-24,49,37,-55,-30,96,24,91,65,-73,-57,38,74,-95,92,85,96,69,31,-26,-15,66,3,-45,20,93,-58,65,-59,-31,-92,-6,-81,22,38,-35,18,-38,-43,-17,-34,-24,-79,-83,-20,90,-98,-47,59,10,26,-79,-24,-71,-48,96,-78,-7,38,-60,62,22,33,57,-56,-52,-78,62,10,-45,-78,52,30,-80,68,86,-90,47,-61,68,-43,64,88,32,69,-59,5,68,10,-57,84,-51,65,-6,82,-91,41,81,47,-72,-64,46,79,43],[65,25,29,51,-28,45,19,5,-14,-16,-63,-44,1,19,-99,88,61,84,-63,3,-22,96,-11,-81,77,-64,-53,-87,81,-97,55,23,4,-38,-26,52,-93,69,-43,-31,-69,-29,24,8,89,1,-4,27,-15,10,-69,39,6,19,58,-17,31,81,-28,-10,83,-72,89,-12,-34,-36,-83,-28,-90,-26,40,-60,21,-58,25,10,19,-79,-86,-95,30,-56,43,-87,39,-22,-28,-52,-41,44,37,-80,48,3,-16,-86,43,0,-38,53,50,78,69,-29,96,-6,57,16,-8,71,20,98],[91,-60,-88,31,18,-17,55,53,-96,-31,72,51,71,-67,41,15,33,-97,-55,-17,58,-86,31,54,-15,-12,-30,76,-41,66,74,-49,-93,62,58,1,-77,13,-69,-74,81,80,54,52,-87,-28,-56,45,-25,-12,-94,-90,-21,36,63,63,-99,-66,16,-40,99,-33,-13,82,-93,-55,-40,-71,57,-9,-69,15,-29,84,-56,-17,-43,-12,-94,8,52,87,17,-69,0,-43,70,0,-10,-37,36,-33,7,-77,-74,13,-33,-14,41,-99,53,48,15,-76,33,36,-17,66,-76,-35,-49,75,-48],[44,83,28,-99,30,-71,-32,93,41,11,0,64,13,-87,-92,75,30,-91,28,-22,0,51,87,-64,-88,30,-64,-24,80,88,28,1,71,-67,-21,-22,-62,23,-29,79,-66,47,43,23,36,50,-1,-34,35,-73,21,-87,55,-15,-52,66,-84,-16,-58,72,-51,46,-26,-80,79,29,-3,-83,-48,45,72,-38,-8,15,84,-94,-57,-17,-52,54,10,68,66,-35,-46,-85,-69,-54,-25,-51,-82,23,95,-32,19,51,73,92,44,-75,14,17,-14,83,-68,-52,88,-49,30,-64,-94,-83,81,71],[-42,-88,62,-35,-43,-86,14,-49,36,-14,19,-68,-63,-8,-98,80,-6,15,-3,56,-2,6,-96,-14,33,11,-1,38,27,-20,-13,62,-9,-74,-73,47,-60,40,97,52,-97,-7,84,-61,62,85,96,-44,0,-30,88,75,52,92,-39,-14,-20,59,-99,-93,-84,-13,68,6,13,72,-70,52,-11,-95,4,-8,-3,-35,7,-64,-50,-20,-32,27,50,-43,2,2,-74,39,64,5,-24,65,-12,-9,-48,-43,74,41,-94,-96,-30,-6,84,51,85,-41,-84,-30,-6,-57,49,62,46,-24,95,-75,55],[-79,63,19,25,-61,-16,-87,7,13,-54,-42,-69,-49,-39,1,22,-77,-71,-16,-19,-79,53,74,-37,-20,13,85,55,8,-90,10,5,50,-93,-93,65,-10,-80,-28,79,-58,29,-89,-30,67,-12,68,89,-7,-48,-53,13,82,97,53,-38,11,38,93,95,25,-19,-22,-25,-13,-16,-60,53,-20,-11,33,22,-82,20,68,61,84,36,27,-23,87,73,89,46,71,42,-92,-41,-42,-98,-69,82,-18,8,-43,45,69,-27,-2,-51,61,-69,47,56,27,15,17,11,-72,-78,87,-84,71,77,61,42],[-4,46,77,53,24,85,12,82,-7,45,27,-61,-81,-75,-12,56,-67,-65,12,59,27,-93,-29,54,-72,-42,46,75,-88,8,18,8,-69,-28,-62,54,-43,27,13,27,-28,-60,65,-10,-59,-70,-76,-27,-35,35,-67,91,18,3,45,22,37,-8,-2,49,76,92,-66,83,-36,-52,14,-2,74,-73,-98,-53,-57,43,13,-17,73,36,56,-62,-51,65,-94,66,-32,27,-34,81,95,63,30,48,55,40,31,95,65,-78,-30,39,-52,-29,62,-10,-85,-47,50,87,65,-17,-98,-86,-52,-93,57,15,10],[99,-27,6,62,80,-46,-6,20,62,-11,-15,83,59,-98,-91,-70,40,-25,-79,92,-75,-92,58,7,85,48,31,68,-18,-77,-21,-19,-4,61,-57,-24,91,13,72,53,-97,-42,14,61,-64,22,67,75,73,65,68,75,49,3,-41,35,-49,90,3,10,-87,81,90,8,42,-89,60,11,23,33,-36,2,67,54,-60,-97,-47,84,54,-73,49,22,-98,-2,-98,-40,-90,-70,-73,13,39,-60,-29,6,24,90,16,-15,1,-83,-82,41,-5,84,-4,35,63,48,19,17,51,-32,-83,29,42,-82,66,52],[-53,92,-58,85,-91,-11,-31,33,-44,84,-82,33,77,-88,-25,-27,95,47,84,58,-28,3,-25,-99,47,-9,29,-34,-14,-5,94,32,-12,-87,-5,-4,2,63,-94,34,24,99,-32,-21,-89,19,28,82,-34,12,17,14,-85,69,14,38,-63,-56,-96,22,38,98,-68,-97,-89,26,-24,-11,-34,-19,-76,66,-19,-9,-55,-32,-90,72,-49,-48,-16,67,65,-25,13,-20,89,50,0,93,-28,-85,68,3,-82,55,-94,-7,-78,-29,50,-78,-85,-92,-11,-41,-24,-2,-91,3,26,-8,-30,-32,44,60,24,33,10],[-76,3,81,-61,-52,-38,-67,80,-56,25,78,-8,-48,99,6,-40,-12,64,12,62,72,-85,-12,-58,-16,32,62,-56,-43,-28,30,-20,52,-11,18,76,50,50,56,70,-48,11,-38,-19,10,44,40,74,9,-48,36,-42,-34,-99,-24,26,33,-85,47,89,-13,-46,-54,-84,42,64,91,-31,-9,25,-60,20,-64,-22,-99,46,-77,17,20,8,45,-66,42,87,-66,-81,-10,43,-90,-86,9,-4,-32,55,-12,-90,-4,-20,-21,86,-95,-5,-17,-60,72,-40,62,71,76,-40,-21,21,-30,-78,-15,-20,-83,75,-76,-74],[88,32,-1,-44,-13,63,-57,82,-57,21,46,-53,92,-94,-36,64,-34,-97,36,-58,-61,91,40,8,89,-75,65,-94,76,88,-91,65,-3,-16,97,61,-53,-60,20,-33,37,-34,-10,29,-51,30,-29,14,33,83,55,48,74,-28,-66,64,-26,98,46,-50,86,31,-85,-40,91,-87,-79,-84,-71,41,-18,66,83,71,-5,-68,2,65,45,-88,48,-22,36,0,49,69,-59,-77,44,86,-27,7,-5,-36,67,-37,-47,87,-22,-18,5,36,-52,-11,-15,42,20,63,-15,-57,74,-67,20,-13,9,-31,-66,49,-31,77,36],[18,-15,-92,81,-48,-30,-65,-84,25,16,21,-39,40,-90,45,-41,6,8,43,48,-41,53,-55,23,-38,-9,56,-88,59,33,24,-23,-82,31,-42,-54,77,-31,-38,2,61,82,40,1,91,-15,60,-26,70,-20,-77,-94,-67,-33,28,-28,57,-16,-17,-7,-82,-93,46,-88,14,81,-42,-32,-50,-4,47,88,-22,-13,-11,-54,48,-74,19,18,-17,18,1,15,62,-71,63,-4,-10,-54,89,-16,-71,35,-5,19,16,29,87,43,-75,34,31,-21,97,96,24,45,99,-56,-59,-18,38,41,73,0,46,37,96,-64,82,62],[-4,88,-3,68,7,90,-3,-29,33,-1,81,-59,77,78,-63,-21,24,-87,22,64,-6,-40,-18,-32,37,-72,81,33,-59,40,-5,36,28,68,4,-87,35,78,-17,-55,-23,-35,-15,-69,-57,-1,9,43,11,-92,-16,82,-55,65,-73,81,70,-92,-9,87,47,62,23,-24,7,-95,-12,-57,82,47,-13,-64,88,49,-34,-91,-75,52,51,12,59,-64,-6,-96,77,20,61,24,27,-71,11,-25,90,-65,27,-2,-61,91,17,97,38,80,-67,4,6,-2,12,30,-73,-37,-57,86,-25,13,66,-70,-66,28,53,37,33,-35,88],[24,-24,15,98,14,-17,15,11,98,-28,20,2,78,94,-86,8,-78,-47,27,-92,28,-59,50,57,-49,-45,10,64,88,51,53,12,-73,-55,-13,40,28,-98,-72,26,-27,47,-95,-72,42,-82,36,40,-30,-60,47,74,-43,-3,31,-16,29,-81,-51,17,69,78,-94,96,-77,-8,13,27,-7,18,-47,42,-58,-66,70,60,-49,-17,0,-2,-1,-76,-28,33,-2,80,-83,-73,98,-58,43,44,-80,48,40,-57,-83,-69,46,-14,25,99,-95,66,-90,51,27,-39,-66,-96,35,10,-72,-93,-80,2,86,-64,28,61,-45,-52,6,-26],[72,-77,-7,88,-70,-60,-26,54,-84,-22,21,-75,-70,-75,-38,-60,-95,96,26,-91,80,45,10,43,58,-62,-18,-87,-15,87,-37,-66,86,33,-78,-83,72,-28,47,64,50,-32,65,56,-31,-95,72,-49,-99,-1,-41,57,-56,69,1,78,-93,82,90,-31,46,-46,2,9,86,1,25,35,72,-27,-24,-1,17,-59,-68,63,-55,-95,-86,-77,-20,-28,79,0,-82,-43,-21,-75,-84,-31,-30,38,-1,48,-52,-38,-74,49,73,75,98,-51,-26,16,-33,-17,-44,11,-13,-54,33,43,17,-10,-57,35,23,21,36,16,67,82,-69,-34,30],[-45,5,33,-95,-45,8,-97,4,58,-5,70,-59,27,-42,4,72,68,-53,-33,-42,-10,78,57,-89,14,-50,54,-27,-19,97,-97,35,2,12,16,56,-80,-4,-63,78,90,-93,-81,18,-35,23,-33,-90,69,33,-33,-64,11,-99,-76,-75,-72,77,-26,-15,74,-46,-80,-24,65,13,-90,85,-91,-54,63,98,-70,81,-7,-29,-19,60,-20,-72,-7,23,-37,-95,0,-14,-94,27,-59,-20,-88,-85,33,-91,-32,-2,21,-46,-40,6,-24,-77,4,5,81,74,52,-61,11,-91,-34,80,8,6,61,-91,68,67,12,-91,-76,1,-76,33,-14,-32],[-92,-93,21,-32,12,96,-33,92,-21,-52,43,-69,-13,-46,-83,29,-88,24,-65,72,9,-96,16,-78,88,39,-1,88,-51,84,-44,-66,90,76,-22,-21,73,44,-52,-48,69,68,-41,-67,98,-25,61,-90,99,73,82,8,53,-2,6,41,-85,-95,30,-37,88,62,-4,55,39,73,-89,-11,-5,-64,40,-36,-96,75,-27,-98,-49,-66,88,-73,83,70,34,36,-32,-82,-45,-18,-78,84,22,87,46,94,19,-38,45,30,50,-60,42,-33,-20,45,-57,52,23,-7,62,11,19,46,-42,-70,-18,3,-76,13,61,-77,-3,-17,-90,-79,-45,28,-41],[99,-65,-90,-84,76,-47,-28,-2,-5,-76,98,87,85,-14,-17,8,44,-10,90,-53,13,-20,-92,35,77,-32,21,74,-1,-50,-90,-2,-39,-81,-10,-85,-51,61,-11,43,61,-36,8,46,50,67,-45,-29,-43,-78,-6,70,1,-22,5,-45,22,-73,-94,-79,-47,-84,-5,-10,-89,84,-19,-41,22,47,79,-17,-89,-13,-70,60,-46,-39,-92,-12,-41,1,-42,36,56,39,68,-22,42,50,-1,71,65,93,-61,53,55,19,88,-23,-34,44,60,-46,-69,66,90,-38,-96,98,49,-38,-24,83,74,-68,22,42,10,-58,-7,85,-87,-65,55,-49,64,10],[47,30,87,89,-26,24,-57,5,-33,-66,43,-30,-68,-8,8,-16,-25,-18,16,73,-98,-97,-85,-6,87,-95,5,42,-68,-30,-70,78,99,93,45,-27,17,87,54,83,-79,-26,-70,-71,65,37,-10,-83,-81,-94,67,-80,84,81,-10,71,62,95,-10,94,-58,-4,49,-59,-11,-6,-10,82,-18,-78,42,-21,-5,71,-15,-62,8,74,-69,27,56,97,23,40,56,-86,-12,18,85,54,-11,-73,-49,-61,-56,16,32,10,-1,90,31,-59,-53,-96,-87,8,-82,20,-18,-52,-76,-85,-77,47,54,78,37,-81,-27,22,72,62,25,99,-99,68,16,9,-45],[-85,0,86,-45,23,66,-56,-69,83,41,-11,-92,64,3,-70,-12,-66,84,-98,-71,-42,0,-99,96,-75,-99,96,69,-7,5,-75,7,81,87,38,-19,53,82,11,13,23,76,-3,-36,-44,4,52,-34,-12,53,-6,22,-46,-5,18,-45,-28,-9,-75,64,73,-51,-52,54,-64,85,-87,65,44,0,-45,-56,-23,51,8,9,-45,-63,75,20,66,-31,-58,96,40,37,-48,-88,-72,-47,52,-99,-22,76,32,13,62,44,-45,-17,-56,9,4,-3,-63,88,-93,-8,-98,58,88,67,-73,-93,41,67,43,69,55,71,-78,-15,48,-1,-39,-20,88,99,-99,-80],[-40,-78,5,63,18,41,51,1,-90,52,-64,97,-4,-37,-95,-86,-93,47,82,38,-5,80,-77,-56,-44,-16,0,-56,-40,1,-60,19,22,44,-18,-83,-14,-90,-5,-5,38,30,-30,-65,69,-26,-52,75,97,-92,14,-30,87,13,-10,-56,73,89,-36,-66,-33,-19,52,88,-75,-88,82,-13,-79,-46,59,59,83,-71,70,53,-21,94,5,-47,-98,95,22,66,9,-88,86,-18,78,-50,15,-55,30,-32,-89,32,-44,69,-81,-24,-77,77,-88,-94,82,81,35,-62,53,-59,-9,31,-64,89,-3,21,78,-17,-96,56,10,18,77,-83,62,64,48,-82,33,44,-29],[55,-2,-18,38,-42,-59,-50,-5,93,-10,85,24,3,52,98,-76,30,-42,-96,-37,44,-1,-83,61,-39,81,-14,-44,-9,-93,3,-53,5,84,61,62,-98,-89,-66,94,-22,96,-4,57,48,-29,57,-22,5,61,17,-50,-40,33,-89,-3,-9,-27,29,82,-20,-68,-94,61,93,66,0,94,53,33,66,-92,29,-61,64,-46,-14,22,31,90,-40,-75,-60,19,58,-73,92,-74,0,22,-92,56,53,-87,-6,23,78,93,18,9,3,-39,16,-90,-1,-42,-37,61,56,71,51,-84,95,91,11,30,94,3,56,-6,-75,63,-73,55,76,20,-22,31,-10,72,-83,70],[-67,33,79,8,67,-58,-31,23,-87,97,15,-91,88,-97,15,82,5,-29,-46,7,-88,-43,-61,64,54,-7,-28,-79,-34,-11,90,-25,98,69,60,42,-88,-94,-35,-99,-97,56,85,67,58,1,27,-60,48,57,46,59,90,61,0,44,-45,72,65,-3,-62,55,71,-64,2,8,77,13,-9,-81,-10,-30,74,-24,-85,9,76,41,48,24,-25,-28,-39,-35,-67,60,86,-13,32,51,83,69,-17,32,81,84,-83,35,-26,7,53,64,54,4,-60,68,89,92,-14,38,-7,60,-90,53,-98,-81,-9,87,6,-77,15,-34,69,98,97,27,59,91,-37,-66,-2,92,74],[-48,-26,90,96,-37,82,-18,-99,-25,-81,86,-94,-79,-94,-4,84,-12,-5,-23,53,-59,-25,28,68,-89,19,-92,-79,93,99,94,-77,-27,84,-81,13,43,-22,-10,95,-4,-46,-99,-7,-64,-27,-22,23,67,54,-47,85,-94,57,53,-84,-47,37,-86,-76,36,-92,-77,86,69,-59,-1,-11,-5,65,-16,91,-81,-39,-16,-46,33,38,76,-22,-31,-93,-37,-49,40,92,-56,93,29,-43,-83,-58,-59,-61,-72,-90,-44,3,-1,28,-31,59,19,-36,-79,79,18,30,-5,-29,-92,63,-23,-53,91,-82,-84,-65,87,44,-9,80,63,31,95,67,18,-72,-29,93,55,16,52,-49],[79,72,-69,-3,-20,2,45,-36,-58,98,11,-67,92,3,-33,79,-75,34,36,87,-57,31,54,37,59,-98,30,-9,17,-41,42,-26,-68,72,47,-12,-49,-8,51,-8,-9,-61,25,-17,42,68,-60,66,-20,75,53,-1,7,7,-64,-57,9,42,33,-97,-99,-25,-24,-91,-76,-99,-4,-26,-8,-52,66,59,-14,-32,-80,-72,-87,-41,70,-8,-66,23,67,17,-92,-97,36,-7,21,-30,-5,22,21,48,30,45,25,-96,95,-83,-49,38,53,13,82,72,18,95,-92,-12,-36,-59,88,-68,35,72,-89,-29,-35,32,17,36,-69,-61,-39,60,60,85,63,32,79,90,-29,32,4],[-70,-19,98,-75,-12,-14,-34,5,-26,-3,-60,-77,-16,-12,-13,-84,-95,-99,-54,-80,-39,83,56,-53,23,-11,-74,-9,36,34,94,65,-85,92,67,2,-45,-67,-93,6,6,-76,28,89,11,92,82,-8,92,-72,-11,-47,87,-55,-24,-12,33,1,78,-31,-88,72,-88,-74,41,78,27,72,-89,11,-22,16,34,-93,5,-55,98,-36,13,67,-31,-98,-80,-44,-76,-4,43,56,73,21,-97,85,-30,-86,87,87,91,15,60,78,-74,-62,-6,36,-79,75,57,95,-60,-30,62,8,-51,59,40,-28,-68,-39,-72,81,58,-93,66,-71,96,31,92,64,-54,52,42,-52,67,-87,83,64],[88,40,37,-95,86,-24,-11,-65,-65,-71,6,-57,-11,11,-75,-52,-6,90,-47,-9,-2,-78,-45,43,74,97,67,18,86,27,-41,74,-33,95,55,-69,-51,-56,-35,-40,-50,48,3,15,-64,27,39,29,-6,91,96,92,-86,-71,35,64,-97,-20,-41,88,-93,-6,63,-49,-33,-5,-19,15,39,22,74,65,-30,-23,-20,-18,-96,-80,88,-25,87,84,-33,77,-87,78,18,-85,-42,53,-96,-35,-52,43,-8,14,-62,72,-94,53,-29,79,-5,18,-66,75,99,-86,71,87,-12,35,49,54,-10,61,33,-92,53,67,61,33,-91,85,-47,0,-24,-10,-51,-19,-79,20,-63,-8,-62,-53,-56],[-86,-39,-85,-98,25,27,50,-20,-83,-12,89,-99,-82,33,38,50,42,23,-97,-81,98,-30,-32,-44,-33,64,-30,58,78,16,79,91,76,93,92,-21,-3,19,58,13,84,24,14,-98,-43,-48,29,75,52,8,94,27,54,-61,83,97,-97,-47,33,80,45,12,71,22,5,41,-99,79,-63,35,-8,-79,-64,82,99,-31,-88,5,-55,63,-87,-61,-10,44,-46,-50,41,-44,-21,-26,-87,-75,85,60,23,-32,1,0,-53,38,-65,15,35,-53,-25,11,15,-14,-84,59,-51,-94,74,15,49,-72,42,-33,-40,-79,18,-28,-78,3,-67,44,47,10,-56,70,-75,-45,-14,37,1,60,-52,93],[-54,-36,52,-29,-54,4,62,94,31,-19,-62,68,2,55,-83,0,-41,-74,-55,82,36,-35,53,37,-3,-84,-26,74,75,22,67,97,62,-3,-55,-92,-99,83,78,8,-35,-84,-47,43,71,-30,-57,-93,-5,-36,65,-69,29,18,45,-74,33,-81,99,-15,17,44,-18,-21,-59,3,-37,-82,-13,-59,2,51,-66,55,-29,81,-75,13,87,19,77,29,27,-17,-52,-51,-15,57,-33,-39,-57,61,-95,1,-83,-55,-95,-20,-61,-32,-3,41,95,30,-27,-34,11,-26,78,-25,69,32,-95,-4,91,-71,21,-24,85,88,37,-72,26,18,6,42,40,10,98,78,77,-27,-4,72,-97,45,-85,-9,-81],[69,42,88,2,23,-39,-30,51,82,23,37,47,-63,41,-27,54,-53,91,-6,33,67,-50,-13,-60,45,-64,-81,-9,-50,9,-14,-80,-71,-26,-2,51,35,67,3,17,-33,-83,-59,3,34,13,-42,58,-19,51,-9,-52,77,55,-13,23,90,6,90,-59,91,-24,-63,-80,27,34,48,-38,-22,-72,55,45,-56,95,-52,54,-15,-18,12,65,-89,80,-86,87,12,-23,10,2,82,-23,19,51,30,32,47,-43,-34,-5,-5,21,22,-73,-34,42,-78,-10,-3,-17,72,85,-52,82,65,-62,69,-23,15,-43,56,-26,10,-48,-75,-60,84,72,-27,-73,-33,67,47,89,93,89,8,91,-20,-95,-26,-71],[90,-1,-89,32,36,56,86,-49,-87,19,25,0,70,26,39,31,-2,-87,58,42,56,5,8,27,-5,-84,-5,51,-79,69,79,87,-55,89,-4,57,45,-18,-91,35,-99,10,-65,48,-87,50,-21,11,39,-63,-47,-4,19,37,99,90,52,-6,41,49,-60,20,36,-16,9,-67,-58,-69,-9,-73,42,-8,13,53,-83,25,4,-28,-87,-57,9,-58,15,-95,78,14,94,31,85,35,-20,-75,-45,-83,-14,40,-74,27,47,16,30,-33,84,-57,-80,-99,44,0,-27,57,20,58,98,-88,39,77,26,33,-15,-12,-55,64,12,-24,57,97,92,59,1,39,-24,-92,82,-63,-50,-97,-62,71,-21,-13,5],[98,-78,3,-89,60,-43,13,-30,18,-99,14,-17,-11,66,-83,-36,58,76,64,-26,-71,72,-43,-35,98,-64,-21,46,14,65,-49,-10,63,31,-23,23,64,89,69,-17,66,-17,42,-68,-51,35,-5,83,11,-63,-42,16,85,-9,81,60,26,-40,7,-83,-97,34,6,65,-35,82,-34,-93,48,-65,-11,-9,-5,-92,0,20,42,94,4,-69,-92,38,46,92,-71,4,53,54,64,-63,47,43,70,-69,8,-87,89,50,-81,38,85,-16,-94,-43,-9,5,76,-90,-23,-20,-60,-39,-82,63,-46,-77,-33,83,76,-92,96,1,50,43,31,-64,55,20,85,50,-65,47,-89,-59,-96,-22,22,80,-12,75,-63,4],[-63,-68,-33,-33,-46,11,-73,-92,18,-77,8,-54,42,-61,-19,-2,58,-57,-75,93,90,-64,-89,93,13,9,50,77,-38,87,-18,-2,-81,25,41,-28,-87,67,-21,31,66,63,53,8,-98,-66,82,37,-24,84,30,-57,-80,17,-63,9,-97,86,-13,-36,50,45,38,68,-53,-21,-82,-40,-77,-27,67,65,-63,20,-49,-62,53,-67,51,-94,93,-42,-51,89,74,-38,-1,77,-52,62,-82,98,7,56,43,53,-88,60,-87,-65,-66,79,76,-30,-1,-73,-16,-71,-63,-64,-88,-70,-7,-40,-80,-55,21,18,98,45,-43,-84,20,63,48,-36,-7,60,-99,-17,94,-89,-38,70,-43,38,74,41,43,-89,53,54,-60],[-77,90,-64,-56,-12,30,-81,-66,86,-65,30,26,82,93,-80,19,71,2,13,81,40,-39,-61,-45,-65,56,98,-78,-14,29,-62,-15,20,-26,6,-92,80,24,-82,67,35,48,-30,-5,18,-11,-86,-11,67,4,-29,-15,64,-14,39,75,-81,14,73,4,-56,-89,65,40,-39,-29,24,-58,95,42,85,30,-33,-68,-75,84,-2,-61,-49,-35,42,21,26,-17,83,-34,-65,-98,79,-92,-18,99,94,-53,16,-44,18,-59,-26,13,59,-64,-57,-74,-33,-55,-90,64,-17,-40,-93,-98,57,32,-16,17,97,-5,-5,54,2,76,30,-4,-76,-53,28,41,-13,-98,-69,-54,-63,-50,-52,-19,-6,-66,-55,53,-29,-49,31,-95],[60,91,22,57,-14,-83,-12,87,70,-81,-39,93,-35,88,11,28,90,18,50,-96,67,97,-16,-61,-92,6,68,-22,33,0,-17,-7,-9,81,-72,54,97,15,41,44,10,78,37,51,67,-75,-44,34,42,-94,14,-13,79,98,25,87,-19,-30,-35,-86,69,24,-16,-62,5,11,91,-20,-97,9,-76,-10,-12,38,-59,-68,62,-3,65,-18,-21,-21,45,-41,-46,-53,-77,34,16,-36,25,-14,88,85,0,-30,-4,-9,49,-25,76,50,64,-36,-12,82,-5,-73,-44,-63,-15,34,16,-70,69,46,-24,68,-42,92,-67,82,-45,97,44,54,-33,-60,-78,93,-9,97,43,-44,-61,-92,-62,33,-66,-7,70,-4,-96,-37,25],[73,-91,-98,41,-34,70,50,-75,-75,47,68,55,-85,84,76,-92,-24,50,27,31,88,34,45,-1,44,-85,-31,-60,94,31,42,44,16,20,-14,82,-10,-87,-93,-9,60,52,-77,51,36,75,35,-88,25,-38,19,-9,95,-59,89,16,-68,-65,33,-73,42,-25,70,-42,71,-67,-83,-62,-54,-99,28,82,52,50,33,-12,2,-32,-23,-73,29,72,-6,1,-86,-17,93,-55,17,26,-29,-41,77,-58,17,48,-49,33,85,-4,10,-10,-22,-38,-83,-89,50,18,-45,-96,22,83,75,-84,-39,88,-1,-45,-89,92,57,-42,-48,35,-24,45,-40,27,-45,-54,-77,65,35,-22,-73,29,-12,53,-53,43,33,45,3,9,61,41],[-26,-40,95,-16,-71,29,42,-20,-36,-82,-98,24,21,-43,46,44,98,-42,-78,-75,86,-14,55,-66,-94,-12,78,-14,73,16,-73,-52,52,98,31,81,27,-50,-62,91,-55,-60,-8,65,-4,-62,-14,-6,-5,-16,-5,-18,70,-73,-8,52,15,-53,-62,-35,63,-36,12,-8,-61,-79,-27,66,-53,11,34,-9,50,-74,-66,-77,-60,-4,-7,34,80,64,92,27,91,-39,-21,-17,-15,-6,47,-75,34,-63,16,73,-43,66,16,3,-23,-50,71,-96,-48,81,-97,-9,-23,-28,-98,-66,-64,71,37,-96,-68,-83,-37,-7,10,-89,17,-56,-76,-66,93,-20,99,9,59,-47,58,30,-67,86,-12,-65,-46,65,6,-67,75,18,-96,13,22],[-88,6,84,5,92,71,-78,-87,94,-68,-93,-26,-69,-8,-66,-40,-72,40,-8,-86,-71,26,-32,70,-91,0,45,27,-20,-65,-51,-9,17,-67,72,9,81,71,22,75,-97,5,-73,-66,96,-63,-7,-76,53,85,-85,81,-12,-18,28,-3,58,-49,-76,-85,-15,-28,-18,-97,-19,-45,-12,-61,-74,-90,91,-72,-9,-82,-62,-12,-69,8,-12,60,-30,2,42,57,60,-53,-69,-5,-3,-46,9,59,2,68,38,60,99,-74,98,-75,-87,89,-71,-20,83,-56,67,90,28,-67,51,97,34,-30,31,-28,16,39,66,90,92,-47,26,-28,-79,-36,-68,-80,-34,-93,-79,-45,73,-74,35,56,-31,-21,24,73,11,-25,70,-77,21,-21,-6,-86],[-82,-40,-96,86,-11,29,-42,9,69,-34,28,-64,-50,25,-33,-77,51,-98,55,96,-42,-21,70,45,30,17,67,-72,72,-62,-58,89,-25,-78,53,63,28,-89,-27,-3,-46,77,9,-20,-20,76,2,-69,54,-66,-96,-88,-10,73,57,96,-32,1,-75,-60,39,-57,-70,-86,-36,82,76,91,69,-74,-34,99,80,74,-21,-40,50,57,-10,5,68,-30,-7,-42,-56,-50,-69,11,28,-45,50,-33,-26,56,-20,38,15,-67,6,-38,-41,71,-62,-84,46,17,-25,-27,-49,41,54,-81,-89,-52,-47,-46,-26,-16,41,-98,15,-31,-55,89,-98,1,4,17,34,-90,55,69,58,92,84,4,-14,-41,53,14,76,8,9,86,32,62,-82,82,-77],[35,61,37,-96,-94,3,-94,7,-93,-1,-82,93,-69,63,51,-77,47,-45,9,82,84,99,58,-8,8,21,-99,-30,38,83,-31,-26,21,-93,-46,26,-14,-64,-90,-7,11,-96,-14,41,66,-63,64,-10,-32,-50,-51,-48,-51,83,21,33,5,-2,-96,-80,-19,-28,-7,78,-45,24,5,41,59,-9,-89,-29,-28,-4,-88,-85,9,52,5,76,78,30,-95,-96,14,2,37,95,-99,17,91,-42,65,-38,-63,97,85,18,38,44,-91,25,-85,-43,-79,-96,-28,6,32,53,-18,11,-17,-37,-9,73,65,-72,45,42,44,37,99,-13,98,-64,-16,83,30,98,4,16,23,-4,72,43,-1,-56,-51,-92,96,7,18,-43,46,-90,-70,-12,-86,52],[-70,35,-11,-93,-78,-13,-58,5,-53,72,3,50,-35,-74,-54,-63,45,21,-19,70,29,-46,-46,-76,10,76,-67,17,-35,-76,-31,-29,58,34,-23,79,97,19,-39,-56,-32,40,70,32,42,-83,45,-36,14,-74,-89,-57,-43,-36,-56,43,-83,-24,-40,-19,-24,5,52,-66,-61,-71,89,-87,24,-50,-44,68,89,-73,-23,8,-80,99,71,10,-98,81,53,-42,-55,96,-98,-61,-51,-62,19,25,20,-52,35,58,-46,25,71,54,51,-96,0,18,-93,76,-74,-97,75,97,13,77,78,-34,-88,-99,-61,89,-61,-36,-72,34,65,47,59,-22,-18,-87,-97,-70,66,30,-66,-34,-52,-83,-80,-26,-80,71,-52,32,25,-74,74,37,-97,89,26,-59,-70],[30,52,95,-23,11,-27,36,23,-48,65,-34,58,75,9,-93,69,28,-43,88,-24,4,-3,78,6,-52,15,9,-86,-82,26,-57,25,-22,-85,78,88,-13,14,-12,15,-43,54,-26,-91,-37,-43,77,67,13,42,-80,93,-61,97,-1,-14,-11,84,-1,-16,11,19,-91,88,33,86,54,97,-22,-58,12,34,72,62,42,-65,95,-3,78,-15,-61,98,-22,-22,72,54,40,-38,15,-83,45,-74,12,53,91,-55,16,45,-58,93,63,31,4,36,-7,-76,47,-34,20,26,50,58,1,-94,-87,-27,59,30,11,-26,23,-44,-23,-65,-91,-32,-21,2,89,-2,-5,29,-71,76,-35,-2,99,-87,63,-4,15,14,-69,92,19,-79,-58,-45,27,53,5,-50],[-91,81,-39,94,-74,39,-4,91,-86,67,21,-58,20,85,40,-4,74,-20,91,-34,70,99,-65,-11,-80,-23,20,46,-93,-74,72,-85,83,-67,85,86,48,-42,77,62,-74,-25,80,45,-39,-3,-58,-88,77,-90,-45,47,-91,-11,-86,-95,42,10,27,48,35,-1,40,-4,8,25,-18,-43,83,-41,95,85,34,75,7,71,-27,48,59,-73,35,90,73,20,-43,63,2,98,-26,-71,47,85,5,-13,-19,-87,88,62,-54,71,98,-82,56,9,70,-36,-43,-57,88,92,-54,0,83,-81,-79,-60,59,22,-85,-67,27,38,94,-68,-98,-24,-78,90,-85,-56,61,89,-38,-5,-25,-68,35,8,-49,23,1,-4,-76,-39,-9,-79,-23,-50,19,-32,-41,-54,-93],[-69,-45,-92,6,-24,97,-3,-4,36,-36,57,-69,38,65,65,-53,-84,-35,24,11,-35,61,79,-15,-85,-94,80,-18,-58,-73,-35,-28,-42,-27,54,10,-53,-49,-94,59,-9,63,66,-93,5,8,-47,21,73,53,-91,-85,-9,64,-23,5,70,-43,63,-88,-40,-71,-40,17,-22,-86,-73,24,-59,-90,-16,32,49,-50,38,-46,58,67,51,8,-3,37,22,64,1,98,-31,-29,-44,-91,-41,-8,-63,18,-90,14,8,-87,-84,49,98,-24,-42,47,25,72,-98,-40,39,29,67,-87,-34,-33,76,67,-35,-78,-85,-3,-70,-26,89,-56,68,75,34,-23,64,26,-97,63,-98,-40,-13,4,-68,-35,63,47,94,8,36,-40,74,12,-73,-84,10,-58,-10,16,-8,-21],[59,-40,-69,-29,13,71,96,15,11,75,74,98,-21,82,-37,-58,29,-43,26,-35,17,0,53,20,-7,-37,38,82,79,-70,-62,15,-33,-55,62,79,-84,36,-5,27,11,-31,2,89,-48,64,-92,57,-78,34,99,15,-89,52,-88,3,92,50,-38,48,56,-24,-37,-77,20,-97,-97,13,38,-26,-83,-51,19,18,-85,47,-18,-78,5,-20,55,4,71,66,-67,83,-54,-75,10,-15,49,-34,60,89,-11,-42,91,-32,70,29,41,86,54,-40,-19,68,-92,39,89,-11,-80,22,69,67,-12,-98,50,10,-96,-63,94,52,3,32,41,91,89,9,-64,36,-62,76,-1,68,-87,79,36,-80,18,3,8,14,-75,-23,-41,-11,-44,85,75,-64,-77,47,64,25,-21],[-17,-7,-32,91,28,80,-93,-19,-21,74,-7,-42,-12,13,52,67,97,-56,91,-48,2,-43,-16,-13,-68,19,9,78,-17,-66,-66,65,26,-22,34,-69,-42,40,11,36,14,-95,70,78,-6,0,45,-32,43,13,-4,-55,69,79,31,78,-2,-82,33,58,-72,67,0,31,-55,-66,61,3,73,-50,-84,-35,-69,63,-80,24,-37,65,68,-94,-22,-35,-73,-75,-79,34,-97,19,51,35,-46,79,-21,30,-13,24,64,-52,-96,14,-3,95,55,27,58,75,-72,97,17,73,-97,71,-62,-94,95,-42,40,74,53,-32,-13,83,-76,65,14,10,-34,-22,35,-54,68,-91,-58,24,13,76,-24,40,74,92,13,53,63,27,59,36,62,-24,10,-8,20,73,-24,44,16,89],[-69,81,-56,65,-72,-88,51,-54,12,-36,98,87,-96,72,56,-6,3,20,97,-38,-67,59,14,19,-48,-66,-7,27,54,-91,-7,85,66,36,27,70,24,-45,-84,-86,18,-85,-99,-1,63,57,92,-34,-46,66,4,-14,26,-82,-95,54,-48,-26,-42,82,-18,50,44,-74,-37,-51,95,63,3,-88,76,-78,-97,54,20,65,-12,-11,-91,41,-45,12,-96,57,30,84,11,58,-41,45,40,17,-5,-38,42,34,10,38,-2,-87,26,-26,-89,5,-72,7,-30,15,72,-45,-67,-95,67,-87,61,-26,74,-50,-68,-67,94,48,26,-33,86,-54,-99,-4,60,-2,-14,-14,49,-27,90,76,80,-63,-31,52,-8,-22,56,-64,-32,-5,9,-58,21,40,-26,-8,-35,76,58,-48,98],[59,24,58,-43,-90,-79,-94,-17,87,59,-60,-75,-95,68,-7,-41,25,28,26,96,-63,67,17,53,-82,-91,94,94,44,-77,69,3,47,28,36,33,48,19,-84,36,-45,-68,37,-41,-99,-70,17,2,34,-56,-2,47,87,91,0,-94,76,-29,76,-3,-6,45,99,-59,-27,13,50,98,-68,43,11,-14,74,-52,21,74,-46,-85,-24,64,-65,50,11,-77,18,87,-95,-28,-42,80,68,28,2,45,45,52,-42,-4,50,-34,-61,-62,28,89,-15,-51,64,15,-60,-83,-44,-25,44,66,-26,-61,30,-22,10,64,-42,-44,-7,59,-99,-85,11,-42,-13,-62,23,25,-25,-72,-8,36,-24,-67,-72,-8,-74,-17,66,69,-74,-60,-91,55,17,-5,20,51,50,89,-12,50,-96,75],[84,-32,-86,-16,69,-35,11,-39,-98,63,-7,-71,-44,19,-11,98,-35,14,-61,-50,-30,32,45,66,-16,-5,55,71,-77,35,46,-93,-97,36,-9,72,-98,78,-90,79,42,3,84,74,98,-27,72,-37,87,87,13,-66,20,-42,99,80,29,31,28,51,-57,-49,35,-77,87,-74,94,65,80,-96,44,22,-17,5,-27,-19,78,-54,44,42,-67,-66,52,29,-9,28,9,96,-41,-63,48,-22,-12,-40,0,-25,-38,-29,-83,-58,-48,60,41,34,-58,-86,92,96,-64,36,38,-31,46,-33,97,-63,94,7,-90,-70,20,34,8,-92,93,-92,-41,-45,-21,-25,-3,7,-88,-62,-59,-46,-72,-67,-50,-36,45,65,32,-9,-91,6,4,-96,89,14,-67,10,-52,17,-6,-58,2,53,-4],[80,-95,69,-36,-83,-93,4,-53,-65,14,-27,-2,-41,-62,-93,50,-53,-11,-69,-73,-21,44,-64,65,69,53,-41,-89,-45,88,-17,-88,93,-47,-25,-90,-64,78,-67,-53,-8,5,21,28,20,27,-45,66,-83,-15,69,-28,-93,-95,-86,75,57,-28,62,-88,-62,-55,99,-69,-26,-26,-83,10,-70,-51,56,-2,53,-45,-74,-50,81,-20,-84,74,42,61,-77,48,66,-64,23,23,-15,-15,12,22,29,11,52,80,62,45,-33,91,70,-77,-11,0,-46,15,50,-64,71,65,86,13,27,-90,-39,-30,-78,60,69,6,-55,-19,-72,51,69,56,31,31,1,97,22,-29,96,-89,71,-49,2,21,-37,-49,-37,-74,63,66,-65,-98,-64,-66,61,-94,39,-93,-37,67,34,-68,23,-35,39,-98],[-61,-39,-51,-88,-51,-80,-61,27,17,1,77,57,27,41,0,38,19,36,71,-20,18,-12,-37,57,-45,96,66,54,-62,5,32,-47,43,81,-35,91,77,3,-5,-28,81,-27,-71,-15,90,28,-77,9,-59,71,88,35,-41,-48,-30,-10,-75,-64,-79,-37,17,53,15,-40,11,56,-72,-35,-40,23,36,-59,95,41,2,85,-53,24,-6,-13,-28,-41,99,7,-13,-31,73,-11,-19,71,28,97,1,-80,-42,-88,76,-15,-24,-87,84,89,-70,79,30,31,41,76,-68,-88,-59,4,-52,-60,87,34,-15,38,99,65,9,27,62,-90,47,96,-79,23,-41,-27,35,-57,-38,64,99,69,-5,40,45,26,29,62,-93,76,-98,71,-13,-37,9,-13,-72,-82,-86,67,-73,60,63,-76,-40,-78,-27],[94,-58,12,35,-59,-19,-70,57,-97,33,-14,65,16,-61,43,-13,3,83,95,89,-89,89,79,54,-84,17,18,-84,76,16,-34,48,57,77,-17,74,-65,-10,9,-63,99,94,78,15,-89,-1,-97,13,-18,74,-21,-31,64,-42,-76,56,51,18,49,28,-66,-85,-24,68,91,35,42,-74,-98,-49,-61,-99,-77,94,16,-90,-30,-5,-1,51,-54,77,96,86,-88,-80,43,63,37,-31,-32,48,-17,43,16,-49,-45,-65,-47,-43,-37,-9,-43,-38,-38,49,-29,31,-79,69,-41,-33,23,-44,-47,34,-48,72,-26,66,-59,41,14,0,-39,-93,50,16,-82,-97,49,-20,-29,-94,18,9,32,88,-82,52,34,-24,95,-66,8,-51,68,60,-79,-81,26,-61,60,-83,38,-79,-77,-34,13,-60,-55,-38],[-3,-8,-32,-85,-98,76,80,-81,28,-9,-29,24,25,79,49,-30,16,46,-12,-81,84,-52,-65,0,-54,-66,42,58,-50,86,-79,23,-44,-35,38,-66,-59,-5,-71,45,85,-1,-31,10,-45,94,56,70,41,-55,65,2,-31,99,78,14,-90,20,-50,-63,-16,-30,59,39,11,-3,72,51,68,-99,-27,54,-1,19,-59,31,13,97,1,-46,-81,-33,33,-36,-57,11,55,-70,-91,-95,-34,-8,-49,-75,-69,61,-1,-97,-11,-33,79,61,97,-45,-20,-61,85,70,-87,-36,-99,-92,7,33,-29,49,-78,-74,55,-70,-93,-79,21,-43,-77,28,94,21,7,-17,64,-14,-78,62,40,-22,77,3,-52,66,66,-74,73,-27,58,-56,98,56,-53,54,85,-47,51,-17,-13,73,-89,-19,-6,17,41,-41,-97],[39,97,20,-83,74,99,-58,40,65,-33,-10,-85,-98,10,89,58,56,43,43,86,-28,-73,-27,-55,-86,30,16,31,-29,74,10,86,48,-93,-96,-1,-94,-78,-84,70,-12,5,61,-34,-85,51,-76,48,-29,44,34,42,47,83,87,60,-10,3,-9,38,-46,-98,24,78,-92,27,-23,-86,25,-8,60,89,73,22,-44,87,-50,-21,12,20,99,-77,-37,46,-94,-73,7,-27,6,74,-89,36,52,34,14,60,-61,90,50,63,-41,-13,53,-91,85,-91,95,-65,-36,-15,32,-59,7,71,86,-10,97,-7,62,-20,-55,72,-84,96,6,29,33,44,-4,-40,-15,31,47,-62,39,9,-77,11,44,-37,95,-24,3,-20,-53,-33,69,-79,36,8,0,80,-43,15,77,62,-79,10,-16,16,70,45,-76,-6],[59,62,-97,81,-27,23,-79,-54,98,1,25,-78,67,-6,-81,3,78,-5,-16,-65,86,-62,73,-93,47,-66,-1,-6,78,22,87,37,-16,90,-5,34,13,-7,79,-11,93,4,-13,37,74,-17,-60,29,77,0,63,64,14,13,47,-61,47,-53,32,2,68,20,-60,-70,-13,11,40,76,80,19,-35,73,99,29,-13,50,-88,4,-21,65,80,-58,29,-5,54,-23,33,-22,0,-35,80,-55,61,96,-26,-52,-16,90,-98,-35,9,-57,-85,-15,71,2,-65,59,-94,13,25,85,31,-46,-43,-14,7,89,63,-93,-68,20,-48,92,16,2,-82,-99,-7,-81,-35,78,-39,-21,-36,-90,57,-25,68,39,88,-30,2,19,1,58,81,-92,48,22,91,79,-58,-80,48,35,21,65,35,90,60,76,46,98,-68],[86,84,66,-39,52,5,-51,99,-93,45,0,65,3,7,-10,-75,-25,-31,-56,-6,93,55,92,36,-33,59,-4,-57,5,-29,-49,-9,-45,-83,52,84,-1,77,83,5,-1,-17,-53,-97,66,36,-96,-81,81,-76,12,75,78,-19,11,-55,-59,83,-36,45,-68,-8,-86,-14,-15,65,-53,83,19,-93,-11,-81,-11,12,97,-67,-51,-99,-72,-70,-98,39,81,79,97,-8,-98,-62,-47,-58,59,-16,33,72,46,-81,14,93,-98,-66,99,-33,-71,-34,79,-74,-25,-72,-97,2,-66,-96,-82,-84,60,-85,-16,61,-71,13,-97,65,96,13,14,20,31,-94,-10,32,-84,-34,76,-56,8,55,-54,82,59,-52,-39,69,-71,-21,61,65,-30,-54,26,-24,58,5,-82,32,94,8,-71,25,13,18,-65,28,83,-89,48,-31],[42,93,-49,-22,-81,-11,-76,-76,44,85,88,90,-69,-9,-34,65,95,-40,-26,67,68,2,-8,-42,96,3,86,57,13,11,-74,-68,5,-47,-14,0,41,10,23,-15,-5,11,-24,2,-98,18,-56,73,55,18,40,23,96,-67,57,93,35,20,27,-74,-68,52,-66,36,-95,-3,-87,46,-93,35,-92,-22,-54,-17,79,-76,78,99,96,33,17,14,-67,-9,23,89,-39,-65,10,87,-40,41,16,-29,-46,20,67,-34,-57,50,77,-49,-72,-77,10,83,-54,-12,82,-81,-79,-23,32,-70,44,-45,-80,-95,-10,6,68,26,-53,-16,73,-23,-96,40,19,-76,-33,-4,-26,-6,-5,83,-46,17,-51,-63,35,-54,-10,-55,-24,-66,-1,-28,-62,65,77,82,-8,-99,-34,-58,-23,-54,82,95,-31,-74,-32,19,20,62,-20],[50,-21,28,86,90,50,-24,-65,-74,9,11,-3,23,-24,-26,5,44,-49,47,86,27,93,45,-1,-61,47,43,58,-56,5,-85,94,60,42,80,51,-31,-66,62,-5,19,-27,68,-57,26,-80,24,-53,-30,-28,-90,74,-58,31,-50,-20,-21,93,-85,22,-25,-71,16,-64,47,-26,63,-83,-16,25,-12,-97,75,-44,-55,-22,-48,69,1,22,-82,11,-27,-41,-81,22,38,-3,-8,53,96,67,58,-11,79,6,39,42,22,-77,-56,-90,-74,95,-58,-53,-27,-6,92,74,92,-90,-38,-58,-32,-20,40,83,54,-67,13,50,99,-29,-84,55,76,55,-3,-25,77,17,-39,79,13,3,-73,62,73,-81,13,42,-71,51,83,-27,-68,23,-44,62,32,68,-11,31,-83,4,-14,92,-64,59,-32,-86,-46,28,92,66,-92,95],[5,80,-85,95,-1,-57,46,-18,-8,77,82,48,16,14,-7,-95,-77,9,9,-15,-21,44,-78,23,34,-25,-72,4,-82,-64,-1,22,92,13,17,-31,32,-59,50,-75,94,9,49,11,-76,-81,15,-54,28,-99,30,83,45,28,6,-44,-97,10,59,-80,45,-64,19,15,25,-87,83,-42,-47,10,-41,-52,-80,84,58,-80,-97,-50,-35,7,-49,71,-10,72,0,72,-72,-21,-17,64,-1,-95,99,-82,-4,24,-70,-21,58,-40,66,-83,7,62,77,-58,81,80,-9,-77,-13,18,70,54,-10,-53,26,18,26,-91,-18,-75,90,-42,-81,-14,81,-75,42,40,-16,8,33,67,-53,11,-91,-72,-32,-23,-73,54,94,96,-15,-15,-56,-88,79,69,96,-62,70,86,-5,65,-27,-47,89,91,69,-26,-1,3,-82,45,90,-73,49],[-42,3,75,-88,-26,71,-26,35,91,-15,14,37,-42,51,-16,-78,-77,-51,-29,-24,-84,-38,-55,-34,37,24,-17,-41,14,9,84,71,88,59,60,-60,7,-66,74,-24,-5,-11,-87,29,-83,-3,50,-83,22,97,-8,37,-41,13,-97,72,-85,-14,-69,28,71,-85,-23,37,50,-86,76,-65,-53,50,10,18,-84,-1,-76,-90,72,51,-74,-5,48,-6,-91,84,-93,-88,56,-79,-26,64,26,-55,55,-97,58,6,92,34,40,-84,-38,-73,33,-46,25,33,-37,-2,-16,-12,92,-67,81,-99,-83,65,88,49,62,-38,13,-12,-16,-54,-33,-81,51,-41,53,-32,-26,91,-6,83,-55,-81,17,8,-7,-99,72,-38,-90,54,-60,-97,19,-72,52,-19,-33,-58,46,27,-13,-87,45,-62,-51,-25,-18,22,-34,52,-17,-12,48,99,72,-59],[76,44,3,86,-2,42,88,93,46,17,-25,-87,59,97,16,-54,86,-61,-39,-65,13,42,34,56,-28,-83,-56,-80,92,-84,-40,45,59,62,31,-65,-19,-3,-72,-72,-86,-21,-83,72,-24,10,95,-37,48,-67,-26,-39,51,-92,-83,-77,-99,-63,-58,69,-71,2,15,65,-59,-77,99,22,19,-96,26,10,-17,42,-41,35,-71,-46,74,76,-14,-51,-62,-62,-67,-69,-63,-66,-55,-21,79,-27,80,-6,-62,-79,17,-86,19,-87,-82,-55,22,-23,64,81,88,92,-88,63,69,-25,88,83,-11,97,-86,25,-92,-65,-96,87,8,60,-19,45,81,74,36,-23,87,53,22,-14,-70,-37,-56,-82,-45,-44,57,-99,7,22,60,72,20,51,-3,27,85,-22,14,-7,-62,72,-84,95,46,51,-27,33,-19,71,96,-13,-66,-60,-19,-35,-5],[-61,-57,78,60,-97,50,-43,30,-75,84,16,2,-2,85,16,-30,-99,12,93,28,61,3,-91,9,-1,-5,19,39,76,60,-89,91,79,89,28,59,16,85,-11,40,69,-95,-81,-56,67,35,-9,67,-76,-16,-27,61,86,-19,-30,-14,53,65,-98,6,25,-88,-3,5,77,-75,-36,-6,86,52,-89,55,34,-70,76,1,64,-33,-55,64,27,17,25,13,75,71,75,5,36,53,-89,-39,42,-16,42,19,8,-94,89,-5,35,-99,-73,-54,-93,-97,23,70,-54,44,11,72,-61,-64,-14,90,83,-62,-5,19,91,-18,56,33,65,-1,-71,-27,-19,-81,44,92,95,48,-85,-98,50,37,48,96,-41,-64,68,-3,-52,-69,-13,-69,-54,81,26,-86,-37,-18,46,-95,57,51,-23,-84,46,98,84,41,46,99,19,-27,13,-56,-31,71],[-21,-85,-55,26,-78,31,56,-33,-11,-18,-43,28,41,79,32,-25,31,86,-33,-23,84,-48,95,7,-72,-9,79,17,35,-74,-34,90,-83,10,17,-85,-58,-50,-18,7,9,15,-64,-73,-5,44,1,-74,30,68,-21,-9,96,-49,97,-76,42,54,17,-46,79,82,-79,72,-7,37,86,11,64,-55,94,-50,60,-70,-24,-45,74,53,-20,-19,-2,35,72,-6,86,69,-6,5,23,88,58,-21,70,55,-49,-60,-30,-62,27,-66,-41,22,-17,-81,51,35,-27,2,-35,29,83,63,-58,55,-66,-72,1,5,9,-98,-7,-56,-20,-60,98,8,-20,-32,22,-93,1,80,28,60,99,-43,-28,-51,35,37,55,-5,-23,73,-73,10,-99,28,91,-14,29,-16,29,85,24,27,-7,80,95,91,86,-27,72,-8,-89,48,25,-18,73,-63,95,5,32],[-28,-22,58,59,-45,-37,50,40,68,-88,-31,54,12,73,-76,-8,45,-84,-45,-82,87,23,-95,12,-52,-36,-15,-15,-41,90,93,8,-55,51,-33,0,91,93,-83,59,-95,-14,-10,16,-64,14,84,80,6,-60,74,-30,62,79,81,87,-80,-57,-51,-22,-90,-58,62,-45,69,-71,31,60,99,47,-3,-96,-90,86,-3,-55,-23,-19,-98,82,20,76,-48,-40,32,-67,-76,51,-47,-51,-94,-38,-10,68,-7,-64,73,-76,73,72,48,-30,76,57,-67,-27,79,10,30,80,-8,-72,56,21,-13,-35,30,-13,-84,82,35,-78,-78,-98,89,14,-63,39,15,86,12,-37,-67,-35,96,-34,14,75,75,-56,56,-56,-29,-11,64,34,31,-5,-79,46,-46,32,44,-25,33,10,66,47,-50,-42,33,38,20,66,-97,-7,-91,16,-31,60,36,-98,-96,-92],[-33,45,18,97,-83,39,21,-30,-52,-35,22,81,52,-35,28,78,22,-62,16,-58,80,18,11,88,-89,79,48,46,57,29,53,-75,-49,-51,98,-33,87,-4,13,-88,38,-88,92,-10,-24,-3,-32,97,35,83,-84,15,-22,27,-19,-12,6,-71,-66,-59,34,64,-58,84,-87,-60,-49,76,13,41,87,-49,52,57,17,-71,-46,84,-97,65,44,-81,-19,98,45,61,-14,-72,66,-4,-55,1,-63,-14,-15,-51,3,13,-98,-84,-46,89,-57,82,23,59,87,76,43,90,42,-36,85,99,-38,30,37,24,34,-20,96,79,80,-66,-35,-57,-18,44,32,-39,59,85,-73,-98,44,49,37,32,2,-43,-1,-79,20,-16,96,58,-86,33,-41,24,90,-44,-20,47,-11,22,89,47,-34,21,-92,-97,-17,-66,80,-95,59,18,36,-38,74,-65,-18,-5,18],[-21,-70,8,88,-11,-91,55,21,-11,3,-90,-89,-8,33,-24,90,18,-22,-50,28,-64,-46,-12,53,66,26,27,-99,-92,98,-5,-37,-94,79,-71,-29,88,83,91,-46,-14,77,-36,55,-13,16,22,-95,71,71,33,-93,-97,97,59,68,23,-37,46,7,-38,-59,70,-33,97,75,37,62,58,5,-84,-78,-41,-44,53,45,71,-25,50,42,-77,-17,48,-75,-20,-16,93,-97,47,39,9,85,56,-44,-48,30,-69,65,-8,66,-53,-16,64,5,39,17,-50,11,91,99,-47,-86,-41,78,-84,15,-38,-91,-6,85,24,-96,70,-43,-64,98,87,-56,63,-44,86,86,40,50,-9,-44,-33,41,66,-65,17,96,-75,76,51,-60,-32,-87,-75,62,75,25,65,45,82,77,44,46,97,-16,78,83,-29,-5,33,61,51,76,-21,17,-89,73,-10,-87,49,-59],[-48,-83,-69,-23,55,-94,78,20,50,37,-25,-6,-17,-28,78,-61,-44,-51,33,65,86,-39,42,-57,55,29,-84,-55,41,41,-14,93,34,-7,-53,-10,-2,-75,86,-75,62,-39,19,-78,10,-26,-63,65,-1,70,7,-38,-92,-51,4,62,55,19,-92,-4,-63,-30,-34,71,62,-11,-39,-63,-9,-53,-39,-70,-15,56,-72,94,-93,-35,36,-18,-88,-57,44,-81,-31,-75,58,-99,21,65,-27,57,-88,16,5,50,-95,65,86,-28,89,-76,-22,-26,57,6,-55,63,47,80,-77,35,99,66,30,-55,67,-12,-55,-12,-70,18,-77,-59,-66,27,90,-85,-30,53,-36,-41,54,41,9,11,-76,53,-49,47,10,-27,-18,-14,-84,89,31,60,-23,52,-75,7,-53,-53,24,-20,74,-8,-28,-79,-55,12,-21,98,-70,87,-14,-46,17,14,77,-96,63,-63,-11,56,-74],[96,16,-21,49,40,85,72,87,-13,-47,38,78,1,35,-77,89,-86,98,-81,77,-39,-51,-29,74,-73,-26,38,-37,39,-6,-35,36,86,43,-38,26,6,-66,-10,92,-37,-95,70,40,39,69,29,29,44,48,-17,-94,96,53,79,99,-73,-6,-61,43,64,3,-21,50,-76,17,-46,29,27,20,21,67,2,-32,7,-82,-63,-86,47,81,38,-70,63,11,83,19,11,86,-86,49,29,54,-70,84,-18,-47,-22,12,81,82,-68,-21,49,10,23,-67,28,36,-54,-25,-6,83,-19,-43,-5,-59,76,82,-95,66,8,10,20,37,-5,78,89,49,-10,47,31,-1,-97,-20,-91,25,-10,13,-38,35,64,55,-4,-54,89,67,-37,65,49,-33,31,-43,77,-72,71,-51,83,60,74,-50,-15,6,48,-36,62,34,89,-48,-53,-72,64,88,59,-63,-66,48,-96,-27],[-10,52,40,-79,85,-6,-74,56,19,85,-6,-7,-65,55,75,60,-81,15,-29,84,66,-6,-88,7,-18,71,43,-8,-4,46,65,86,-25,-18,83,-62,52,85,70,-29,70,-36,40,82,95,16,42,-85,-69,-87,98,73,-17,87,-42,65,58,-99,-43,-69,24,-78,-83,98,-20,-99,-87,-68,85,83,2,33,-76,-80,15,-80,12,-43,-89,42,-54,85,-8,28,72,49,-30,7,27,27,38,-49,25,54,-74,82,54,-61,-86,17,-78,-7,-50,-78,12,64,-59,-76,97,-72,42,-57,-86,-89,47,85,60,94,-7,-13,-2,-69,14,99,61,39,81,16,77,95,-90,75,-35,-41,97,53,-77,-85,53,96,-57,-5,-84,-67,-18,62,-82,-58,33,-13,5,-69,-6,95,-69,-44,35,-88,48,12,83,57,-35,-75,-84,-61,77,-85,-47,30,-89,-28,-98,-74,-19,-16,64,-1,2],[-2,62,84,5,-43,79,35,12,14,24,-63,-96,-16,93,-32,9,-91,6,-14,99,35,-83,-90,84,94,-65,-35,-22,75,40,80,-27,3,41,78,36,20,-10,-75,-65,-86,-39,-85,-2,-46,-41,83,-61,64,-31,-62,-24,-38,-76,-40,-43,-42,25,11,-90,-58,-32,-40,44,-91,-62,-43,29,4,-19,40,-5,18,54,69,71,-87,52,86,53,-79,-76,-71,-40,-53,-34,16,-19,67,-73,-9,-91,-28,50,30,-20,64,86,-91,-32,-55,48,39,62,-21,8,11,-9,-40,-3,-79,-19,21,-73,40,44,-8,-67,-74,-64,-64,-7,-79,7,-80,50,87,83,14,72,-72,35,-2,67,-26,76,-25,84,-55,35,-18,-35,92,79,-9,9,0,59,18,25,94,53,94,-84,-39,-86,42,-75,73,-67,96,-98,67,-6,45,-58,-52,96,-97,-8,31,-39,33,0,-60,-98,85,40,37,3],[-58,9,-43,-63,1,-6,-73,-57,18,-99,-47,-9,78,-80,62,23,-62,-90,19,-82,-22,-72,-22,87,4,18,88,-10,-65,26,92,-47,-88,-74,-34,12,19,-7,31,-86,-30,83,5,-52,80,-33,70,94,-47,-34,-88,30,-30,-10,17,74,84,-17,-59,-81,85,-67,-29,96,-41,14,8,54,-93,-61,68,-24,99,-50,0,79,-7,-53,73,45,12,62,-48,82,-48,68,33,-64,-72,73,-69,-87,82,-22,85,-59,91,-7,72,74,9,17,-73,-15,66,26,-36,-41,72,-86,-96,-15,52,-45,-56,-96,99,53,-84,-72,26,-77,-83,8,-22,-97,26,-31,-28,-25,-79,57,91,-53,-58,57,73,-18,-84,22,-27,95,83,-75,-73,-73,-94,-97,56,-79,-93,-18,-79,-76,67,-2,-97,-30,66,-26,44,63,-68,12,-89,-50,-31,60,32,-39,-18,-95,-67,-34,-71,-41,-31,-66,-62,-74,-68],[-55,-16,-48,-32,-72,49,-53,-3,-8,20,-82,-44,28,6,-57,78,74,-97,-13,-88,-39,-9,-79,26,-4,-21,72,30,-6,97,38,38,-19,89,82,-14,15,-71,82,-93,25,77,-61,-69,-17,-42,85,-65,-40,-28,-77,-2,62,-56,-76,-65,-1,95,64,92,69,2,30,-72,-32,-11,13,82,17,-28,66,-80,-51,81,-50,9,-60,-65,20,-24,-17,42,73,-78,85,74,-44,-38,46,-79,-46,16,-1,61,20,44,-50,-67,3,67,4,-54,63,30,-72,-87,-84,-56,-76,35,19,6,-46,-30,27,-83,-56,82,-22,89,79,8,-18,-44,-31,-98,99,19,-89,-21,-37,-8,25,-74,-78,29,-85,-86,72,-62,48,-32,43,78,37,-30,94,57,-71,-28,24,-91,80,82,-36,-51,84,-37,44,71,41,83,-37,-57,85,-16,71,99,-26,20,-63,-78,88,56,-99,2,-74,71,-40,-45,-56,60],[-37,-99,42,3,-74,3,42,70,-25,-40,30,37,3,16,98,-49,15,-28,71,29,-29,36,-15,-52,-62,-12,-81,-26,42,-38,-66,81,-61,76,-39,-35,-21,-97,-88,30,-38,41,-32,64,-66,-57,-84,49,14,63,-45,84,-1,39,-68,36,-73,-72,87,45,-34,-79,3,5,73,63,69,-70,65,80,59,-95,-2,-96,68,32,-54,60,-42,37,23,12,21,98,-72,30,35,-45,34,22,76,99,19,-20,4,-7,-80,-50,22,62,-93,-42,66,5,-38,11,-86,-16,-51,-29,-79,48,59,19,47,86,-74,-41,-82,59,80,94,58,-24,-49,-60,68,-30,-11,-33,-91,-4,2,74,-99,40,-37,-86,-76,11,-39,-78,-41,-80,40,82,-94,65,-59,-76,24,97,94,-41,-26,-55,-2,-81,-9,87,-37,0,-17,64,-26,-40,-19,13,-50,4,-76,-13,2,-40,6,-58,-58,-12,83,-17,11,7,-43],[5,43,30,26,-59,26,-82,-95,88,17,-36,29,67,0,86,-42,49,-33,-19,-64,69,17,18,-89,59,-93,94,-81,-6,-22,-25,76,-79,82,2,-61,-15,-4,-80,-27,89,-16,78,34,83,64,91,10,-92,-28,22,76,66,-59,87,25,-76,58,20,17,-64,71,-30,-66,30,72,-51,-85,-55,-32,-36,-65,28,-81,68,12,59,36,-78,67,84,20,43,50,60,30,-25,83,-12,71,-22,1,20,47,11,-50,-4,36,-35,41,80,28,52,9,24,-3,97,-17,-67,95,-50,-83,15,93,67,-24,0,-81,-64,65,90,13,-34,-13,-62,53,36,33,-11,-99,-49,-31,6,-97,54,-70,-1,51,12,31,46,39,25,-38,32,-8,14,-68,-13,26,96,-46,-60,-61,40,-46,68,-23,86,-66,-46,-62,-20,59,-83,-66,65,-7,62,-45,-76,8,93,25,46,2,-83,-63,33,4,63,7,57,79],[22,-25,-67,-9,51,-81,24,-95,-67,-96,41,-73,-85,-17,19,76,37,19,-39,7,-55,84,-91,-62,-79,42,18,83,-74,-47,62,47,27,71,-62,-22,67,39,-41,99,19,99,-97,10,-40,21,-14,96,-82,24,-19,-38,8,-11,-24,28,-92,94,-11,-67,-53,-72,57,50,99,94,-72,66,10,-37,42,-70,-37,45,39,22,-57,-97,-5,-63,3,75,-25,-89,-58,51,15,-51,22,80,-41,45,-91,-84,-5,84,86,-1,27,-3,61,-31,3,-99,90,-81,22,-89,97,94,-53,0,46,22,-13,87,-27,79,-86,71,59,-28,16,44,-36,-89,5,-50,9,-68,46,-53,1,-74,-52,-32,-78,46,-22,-81,40,2,-4,-36,-76,82,-49,-27,61,-59,-56,-2,12,59,-81,52,46,24,-97,-68,55,25,-22,-67,51,25,1,72,-28,78,67,88,-43,-37,-48,-20,-54,-20,29,83,20,72,-19,-90,8],[-23,61,-69,-99,40,-38,55,-34,17,88,93,-58,-34,42,-10,-79,9,-44,-22,72,7,57,94,63,-13,54,-39,-64,-87,-30,21,-11,-92,51,-11,25,-86,-79,90,7,85,60,48,-49,2,-84,-28,87,-29,49,36,54,-17,30,18,46,-38,78,82,-26,-75,3,62,-91,-69,-49,33,-79,-29,0,27,-43,-40,-47,-16,38,-32,55,26,15,-19,-38,-31,41,69,86,-13,-69,41,-54,-19,65,25,-57,51,56,-7,-16,76,40,84,4,73,-79,33,-42,59,-99,89,-15,15,-29,23,60,-88,-31,47,-25,-24,-35,21,56,-92,-54,98,58,78,-32,-58,55,85,-97,-64,58,-76,68,92,82,45,82,-56,-63,-70,43,96,-82,-87,20,-31,-35,85,89,-78,92,-87,96,50,90,-58,68,45,-73,48,57,61,71,25,31,30,-53,-10,73,-17,-4,-7,-20,13,-18,99,81,47,84,48,45,53,60],[18,-20,27,59,-51,-50,62,96,-93,1,44,9,-68,-26,55,-2,-76,-61,93,-7,-5,-17,75,-6,-59,22,-44,65,-33,85,25,61,-34,-70,21,-9,-21,-40,-36,-38,60,-92,70,68,-42,3,-57,-42,18,-64,50,-87,-5,25,-17,36,-76,38,1,-33,24,-96,-71,66,-90,26,-43,-12,85,20,26,23,4,-26,-32,38,76,11,72,-29,23,22,-17,95,-75,65,8,-52,-19,85,15,81,65,20,47,74,-54,80,-61,-92,-23,65,30,57,-61,75,-5,91,-14,-33,-38,85,65,44,80,89,-14,-35,-85,43,-49,6,24,-84,-74,-52,90,-52,-95,-94,-45,-19,70,85,-62,-91,60,9,99,-77,52,-39,84,-5,81,42,-39,-32,-93,-25,87,-66,57,12,-50,82,36,-83,-93,41,-78,-38,98,92,-53,-63,77,83,22,54,82,-48,-85,66,46,73,8,-93,-82,-8,-41,-95,25,-84,-7,51,75],[-70,67,81,47,66,-57,45,35,-34,58,-11,-74,-19,-57,-92,32,-65,51,-45,-92,-64,-39,-98,27,19,-94,-70,12,-24,80,-13,5,25,-55,-48,-9,-35,73,-97,30,32,-9,33,89,34,40,21,45,-32,75,52,4,-87,30,-92,9,35,-63,-79,-89,94,-16,-8,19,5,20,86,69,-6,65,-23,-97,-44,-90,91,66,26,12,11,94,-36,-60,-25,-47,69,-18,61,-18,-4,58,-31,-10,-58,61,85,47,-42,48,-7,51,13,69,53,68,55,44,12,-18,-67,99,-47,-27,-60,4,3,85,85,-36,-33,-42,-77,36,47,-59,-26,9,64,31,-43,-65,-40,69,-96,89,15,36,11,-96,-82,20,-97,-53,93,-81,50,-4,-95,12,36,-52,70,35,60,-6,53,-66,-96,-6,65,-63,28,-98,83,32,90,-25,-32,1,-22,-38,-78,-20,-15,91,-24,-88,-36,-20,23,99,4,-30,12,-35,64,-35,-2,44],[58,-60,80,-13,-82,63,95,-91,-62,-60,-14,-8,-22,-16,49,62,-25,-75,73,15,-19,-27,-8,84,43,-96,-51,-16,-32,24,-72,-97,40,84,-11,58,25,-39,66,39,0,-71,-68,77,13,80,16,87,81,-34,-20,-38,39,71,-54,-18,74,-28,65,-81,95,69,-79,35,53,-13,-30,-22,24,-64,94,-75,-35,-74,78,54,82,-5,18,63,60,97,-98,-24,68,-53,57,19,-5,-1,37,-10,-32,35,-97,98,-78,-28,-47,45,-15,-53,46,26,-28,2,-20,-69,73,97,70,10,95,71,86,40,-81,20,-40,-10,-80,96,80,-36,31,59,-38,29,-92,15,-48,-31,38,97,94,87,-24,-49,-82,-51,-51,88,59,-79,59,45,60,54,-58,96,-55,-39,93,-98,2,1,37,40,-92,44,-45,-41,90,70,-67,84,57,9,-87,74,57,-39,39,-7,-42,-1,-85,94,-70,-43,91,-26,-6,61,-48,95,-38,88,36],[-54,10,67,4,0,37,37,-39,-6,-77,-27,-54,56,10,84,-73,44,-17,-59,16,-10,-3,7,40,68,-55,92,63,6,57,-24,29,-56,-56,-67,20,57,46,58,-48,68,-92,-3,2,-5,-19,28,-61,41,45,54,-69,-57,-62,47,-89,-18,39,50,65,-26,-73,-6,-6,-53,3,-85,-96,-50,72,-45,94,56,28,-27,-49,86,-99,-33,4,46,97,11,65,-64,-42,52,-6,74,-21,-41,-75,5,29,18,51,-67,32,55,-18,-19,86,-47,-62,-8,26,-35,-45,26,31,58,-51,29,-54,90,41,3,42,-65,-46,-78,-29,-22,3,76,96,-45,-91,5,86,-33,86,49,20,-99,-82,-77,-35,-28,48,73,-93,74,-21,-48,64,96,55,-16,-92,-91,-18,-45,-36,84,-68,-40,-84,-60,64,78,-16,27,28,80,27,45,-97,69,94,27,19,-99,1,74,-47,-57,70,84,26,77,69,-92,-90,-67,68,-59,-8,84,-43],[-66,62,40,60,-33,20,-35,-87,22,-89,83,-50,29,83,27,-20,-64,46,-50,-80,-28,-96,66,-44,-87,98,-75,-47,-32,85,-13,1,47,-73,-62,-85,24,2,-96,-77,-11,86,-51,94,46,76,-26,82,22,23,78,71,4,44,-96,16,20,-95,46,87,66,-67,-35,14,-64,2,5,36,81,-15,59,-30,-52,-92,-58,93,60,15,52,-40,-61,8,-92,19,-71,87,-65,48,92,57,12,58,66,76,-51,-97,-44,30,38,-86,91,-26,-40,-61,-18,1,-90,-81,-83,61,-22,-68,-54,-38,50,-48,-50,61,76,-58,-4,-11,76,-38,-58,-97,-59,-26,32,56,-13,24,-70,24,39,-12,-75,48,7,-59,-13,61,-51,32,-76,75,60,-27,37,37,-9,-67,-97,-33,-29,-56,-54,-11,-5,78,-55,58,-21,-49,-18,-82,39,7,66,-77,24,-70,83,50,38,83,25,-1,-44,-38,-64,46,-29,-62,90,19,-42,-64,-92,52,90],[-71,11,-31,-21,69,-36,94,-24,-93,-83,77,-64,77,27,73,60,-48,-28,93,-9,-16,16,38,21,6,-66,79,19,-59,8,9,-54,95,55,25,65,-81,19,-59,-75,13,94,-63,-10,21,-90,-73,50,-41,-80,-82,42,36,55,-59,-81,66,96,37,-93,4,-53,-47,0,78,54,-35,96,-50,-18,97,62,-23,-66,-71,74,-80,-44,1,-45,-48,-5,74,87,-49,-85,83,-83,-89,20,99,-9,43,-71,67,21,82,-68,-6,-67,-9,-32,71,44,1,-99,-5,-2,-67,73,52,-16,-32,26,-51,18,17,-68,11,27,51,-12,95,-28,-7,62,92,-24,71,-36,-15,-38,31,-44,82,-90,-67,-23,7,-35,-50,-64,26,18,62,74,-87,-44,-94,1,83,33,65,55,-95,-42,17,74,10,-35,-85,94,3,45,-72,-15,31,-63,39,-62,-21,88,-26,-95,-17,-87,78,-27,-32,60,73,-72,-30,15,59,-25,72,-46,-74,-17,18,-60],[-46,-78,61,-42,-17,-7,-5,-78,7,50,87,57,54,-30,46,9,19,91,-31,-31,-81,38,83,55,89,33,-91,91,-84,26,-92,-54,24,69,4,-92,-61,75,-71,22,25,-84,-20,-21,-37,-97,64,58,93,-67,-72,89,47,-89,44,37,43,52,28,35,-22,36,81,79,-18,-38,86,-3,-86,91,-81,15,84,-25,70,-76,-22,34,81,-29,66,-91,-40,13,96,-96,-73,16,32,32,-71,-89,-32,86,66,26,-75,52,-77,-62,43,-59,52,4,-7,22,27,70,-44,9,-59,98,-6,-22,-12,-33,-42,15,83,90,-53,88,77,-9,74,43,-83,98,-28,-84,-87,91,-67,64,-4,25,-37,-77,-5,-5,8,13,-7,-97,67,80,-54,-75,-28,-94,91,-5,93,68,85,67,-12,78,42,59,93,54,51,-96,-5,-76,28,34,-54,-99,-71,31,-10,-2,10,-66,-21,55,-42,27,61,-73,-77,54,71,-92,-1,-40,63,-82,95,56,49],[46,59,-56,69,-35,55,92,-35,83,23,31,-18,-67,64,37,64,98,-36,25,-75,-14,-20,96,-29,55,-67,-66,72,-72,66,21,51,3,42,-3,67,-3,-34,-91,-43,88,39,15,97,-20,-48,39,-22,-7,-36,-20,55,20,-47,-74,-25,-38,-64,-52,-11,-97,45,-83,5,-13,14,-51,60,79,-43,-82,45,72,9,19,-48,61,-42,6,-69,22,62,62,-81,91,88,-6,-47,-99,18,19,-97,-60,35,-16,27,-51,32,-13,-94,88,-19,27,37,90,-54,65,28,4,-28,35,-97,-89,-3,97,-97,-38,-9,-45,-37,85,73,-58,-74,-14,26,29,11,-65,92,16,-76,-49,-57,37,-59,-34,3,45,46,51,-20,25,61,53,22,40,-84,90,95,-45,75,45,-4,77,-69,98,6,42,-66,-24,-65,-66,26,-45,70,66,20,-50,-12,-34,-99,44,67,39,-3,-11,-21,-11,-21,-49,20,-68,96,-83,-91,-96,91,-8,22,-98,67,57,-65],[-7,-88,82,-64,8,-91,23,50,-90,-56,17,25,40,82,-96,-93,-38,-45,26,-7,-72,19,-22,-69,-12,69,53,-11,13,-13,1,-94,-2,-17,-59,82,-9,40,9,-23,83,-74,78,1,84,82,7,-54,-86,-90,15,-59,29,93,-52,-83,39,-99,-18,-47,-13,82,-42,61,-58,-24,20,10,92,-71,86,76,-69,42,-46,-84,24,60,-62,14,46,53,54,-25,23,78,-32,-38,79,50,14,-57,9,49,-95,51,-98,1,-39,93,30,-76,69,60,65,-77,52,-34,59,90,79,6,20,10,57,-57,-11,-97,4,-55,29,95,-13,-62,44,-32,65,45,69,-74,15,-1,-50,-15,-64,91,-16,65,-42,-79,55,-63,26,-25,24,-40,17,-87,-61,97,-66,67,92,20,82,13,88,47,-65,34,73,50,-67,99,-88,-55,90,-28,-90,-52,-8,41,-38,94,92,85,-45,-14,74,-7,-16,-92,-62,-47,4,96,43,-31,43,77,-97,-7,4,-65,-31],[-8,-43,-63,64,-57,-39,-44,84,22,-49,53,-16,-18,-60,-65,51,0,-81,88,29,23,61,-28,91,-18,-73,94,51,7,-94,-79,99,-61,-66,63,-18,-6,-81,-57,93,-31,95,-46,50,-88,-11,2,11,-16,-33,-82,-93,-71,-11,75,-13,-8,46,-62,99,28,-42,98,67,-9,61,-74,62,56,-32,55,-97,-60,-91,29,-48,-26,-69,39,58,-25,56,41,-20,-77,16,66,-9,-61,-96,-10,67,-61,-35,34,6,-97,59,-32,59,-96,-77,61,-57,-91,-10,-29,-18,-2,87,-60,49,20,81,-94,42,-26,71,-89,13,51,0,-20,66,65,90,-27,44,49,17,3,29,40,-59,71,25,8,-80,-93,82,-93,-53,8,26,-95,13,-54,-22,-39,-44,90,-88,32,-30,78,-26,-40,-72,-81,85,44,-2,14,-39,16,-37,85,-99,-18,92,59,-35,-84,-33,67,-80,56,89,-26,-83,-78,-35,-72,54,11,82,-95,71,86,99,33,31,-25,-75,68,67]]
   res = minimumTotalOfTriangle().doit(a)

   res = getRowOfPascalTriangle().doit(3)

   res = generatePascalTriangle().doit(2)

   root = TreeLinkNode(1)
   root.left = TreeLinkNode(2)
   res = connectToNextRightII().doit(root)

   root = TreeNode(3)
   root.left = TreeNode(1)
   root.right = TreeNode(4)
   root.left.right = TreeNode(2)
   res = flatten().doit2(root)

   res = hasPathSum().doit(TreeNode(1), 1)

   a = ListNode(1)
   a.next = ListNode(1)
   res = insertionSortList().doit2(a)


   res = hasCycle().doit(None)

   res = longestPalindrome().doit("abccccdd")

   res = palindromePairs().doit(["a",""])

   res = palindromePairs().doit(["abcd","dcba","lls","s","sssll"])

   #res = shortestPalindrome().doit("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")

   res = shortestPalindrome().doit("aacecaaa")

   res = isPalindromeList().doit(ListNode(100))

   a = ListNode(1)
   a.next = ListNode(2)
   a.next.next = ListNode(2)
   a.next.next.next = ListNode(1)
   res = isPalindromeList().doit(a)

   res = isValidPalindrome().doit("A man, a plan, a canal: Panama")

   res = minCutPalindrome().doit("aab")

   res = isValidSudoku().doit([".87654321","2........","3........","4........","5........","6........","7........","8........","9........"])


   res = missingNumber().doit([1, 0])
   res = missingNumber().doit([0, 1, 3])

   res = firstMissingPositive().doit([1,2,0])
   res = firstMissingPositive().doit([3,4,-1,1])

   res = countAndSay().doit(6)

   res = combinationSum2().doit([10, 1, 2, 7, 6, 1, 5], 8)


   res = strStr().doit("ababcaababcaabc", "ababcaabc")
   res = strStr().doit("aabaaabaaac", "aabaaac")
   res = strStr().doit("mississippi", "issipi")
   res = strStr().doit("ABABDABACDABABCABAB", "ABABCABAB")

   res = letterCombinations().doit("23")

   res = restoreIpAddresses().doit("25525511135")

   res = ListNode(3)
   res.next = ListNode(5)
   reverseBetween().doit(res, 1, 2)

   res = TreeNode(2)
   res.left= TreeNode(3)
   res.right = TreeNode(1)
   recoverTree().doit(res)


   res = TreeNode(1)
   res.left = TreeNode(2)
   res.right = TreeNode(3)
   recoverTree().doit(res)

   res = [1,2,4,3]
   nextPermutation().doit(res)
   res = [1]
   nextPermutation().doit(res)
    
   res = getPermutation().doit(3, 4)
   res = getPermutation().doit(9, 171669)
   res = getPermutation().doit(1, 1)
   
   
   res = maxSubArray().doit3([-2,1,-3,4,-1,2,1,-5,4])

   res = grayCode().doit(2)
   res = generateTrees().doit(0)
   res = generateTrees().doit(3)

   res = numTrees().doit(3)
   res = numTrees().doit2(12)
   res = numTrees().doit(19)

   res = removeInvalidParentheses().doit("x(")

   res = removeInvalidParentheses().doit("()())()")

   res = isValidParentheses().doit('()')

   res = threeSumClosest().doit([-1, 2, 1, -4], 1)

   res = fourSum().doit([1, 0, -1, 0, -2, 2], 0)
   
   res = threeSum().doit([-1, 0, 1, 2, -1, -4])

   res = groupAnagrams().doit(["eat", "tea", "tan", "ate", "nat", "bat"])

   res = solveNQueens().doit(4)

   res = superPow().doit(2, [3])

   res = superPow().doit(2, [1,0])

   res = mySqrt().doit(1)

   res = myPow().doit(2, 6)

   res = myPow().doit(34.00515, -3)

   res = trapRainWater().doit([[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]) 

   res = trapRainWater().doit([[12,13,1,12],[13,4,13,12],[13,8,10,12],[12,13,12,12],[13,13,13,13]])

   res = trap().doit([2,0,2])

   res = addBinary().doit('111', '11')

   res = addStrings().doit('123', '912')

   res = combinationSum().doit([2,3,6,7], 7)
   
   res = combine().doit(4, 2)

   res = multiply().doit('3', '123')

   a = [Interval(1,4), Interval(0, 4)]
   m = mergeIntervals().doit(a)

   m = searchMatrix().doit([[1]], 1)
   m = searchMatrix().doit2([[1]], 1)
   m = searchMatrix().doit2([[1,3,5,7],[10,11,16,20],[23,30,34,50]], 3)
   m = searchMatrix().doit([[1,3,5,7],[10,11,16,20],[23,30,34,50]], 3)

   a = ListNode(1)
   a.next = ListNode(1)
   a.next.next = ListNode(2)
   m = deleteDuplicatesII().doit(a)

   a = ListNode(1)
   a.next = ListNode(1)
   a.next.next = ListNode(2)
   a.next.next.next = ListNode(2)
   m = deleteDuplicatesII().doit(a)

   m = NumArray([-2,0,3,-5,2,-1])
   n = m.sumRange(0,2)
   n = m.sumRange(2,5)
   n = m.sumRange(0,5)     

   m = NumMatrix([[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]])
   n = m.sumRegion(2,1,4,3)
   n = m.sumRegion(1,1,2,2)
   n = m.sumRegion(1,2,2,4)

   m = [[0,0,0],
        [0,1,0],
        [0,0,0]]
   n = uniquePathsWithObstacles().doit(m)
   n = uniquePathsWithObstacles().doit([[1]])
   
   n = uniquePaths().doit(4, 3)


   n = jump().doit([0])
   n = jump().doit([2,1])
   n = jump().doit([2,3,1,1,4])
   n = jump().doit([2,1])
   n = jump().doit([6,2,6,1,7,9,3,5,3,7,2,8,9,4,7,7,2,2,8,4,6,6,1,3])
   n = jump().doit([8,2,4,4,4,9,5,2,5,8,8,0,8,6,9,1,1,6,3,5,1,2,6,6,0,4,8,6,0,3,2,8,7,6,5,1,7,0,3,4,8,3,5,9,0,4,0,1,0,5,9,2,0,7,0,2,1,0,8,2,5,1,2,3,9,7,4,7,0,0,1,8,5,6,7,5,1,9,9,3,5,0,7,5])
    
   n = canJump().doit([0])
   n = canJump().doit([1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1])
   n = canJump().doit([2,0,6,9,8,4,5,0,8,9,1,2,9,6,8,8,0,6,3,1,2,2,1,2,6,5,3,1,2,2,6,4,2,4,3,0,0,0,3,8,2,4,0,1,2,0,1,4,6,5,8,0,7,9,3,4,6,6,5,8,9,3,4,3,7,0,4,9,0,9,8,4,3,0,7,7,1,9,1,9,4,9,0,1,9,5,7,7,1,5,8,2,8,2,6,8,2,2,7,5,1,7,9,6])
   n = canJump().doit([2,3,1,1,4])
   n = canJump().doit([3,2,1,0,4])
   
   n = searchInsert().doit([1,3,5,6], 5)
   n = searchInsert().doit([1,3,5,6], 2)
   n = searchInsert().doit([1,3,5,6], 7)    
   n = searchInsert().doit([1,3,5,6], 0)

   n = firstBadVersion().doit(1)
   
   n = firstBadVersion().doit(3)

   m = [3,2,2,3]
   removeElement().doit(m, 3)

   m = generateMatrix().doit(3) 
    
   m = [[1,2,3],
        [4,5,6],
        [7,8,9]]
   n = spiralOrder().doit(m)

   m = [[1],[2],[3],[4],[5],[6],[7],[8],[9],[10]]
   n = spiralOrder().doit(m)


   m = [[1]]
   ref = rotate().doit(m)
   m = [[1, 2],[3, 4]]
   ref = rotate().doit(m)
   m = [[1,2,3],
        [4,5,6],
        [7,8,9]]
   
   ref = rotate().doit(m)

   m = [[1,2,3,4],
        [5,6,7,8],
        [9,10,11,12],
        [13,14,15,16]]

   ref = rotate().doit(m)

   ref = ListNode(1)
   ref.next = ListNode(2)

   result = reverseKGroup().doit(ref, 1)

   result = reverseKGroup().doit(ListNode(1), 2)

   result = reverseKGroup().doit(ListNode(1), 2)

   rescollect = generateParenthesis().doit(3)

   res = detectCapitalUse().doit("FlaG")
   res = detectCapitalUse().doit("mL")
   res = detectCapitalUse().doit("Lm")

   
   max = lengthOfLongestSubstring().doit("abcabcbbc")

   max = lengthOfLongestSubstring().doit("bbb")    

   max = lengthOfLongestSubstring().doit("pwwkew")

   max = lengthOfLongestSubstring().doit("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ abcdefghijklmnopqrstuvwxyzABCD")
        

   result = permute().doit([1,2,3])

   result = permuteUnique().doit([1,2,1])
   result = permuteUnique().doit([1,1,2])
    
   done = findKthLargest().doit([3,2,1,5,6,4], 2)

   done = findKthLargest().doit([3,2,1,4], 2)

   num = thirdMax().doit([3,2,1])

   num = thirdMax().doit([2,2,3,1])

   num = thirdMax().doit([1,2,2,5,3,5])

   res = addTwoNumbers.doit(ListNode(5), ListNode(5))


   number = myAtoi.doit("2147483648")
    
   number = myAtoi.doit("-2147483648")

   number = findMedianSortedArrays.doit([1,2], [3,4])

   number = findMedianSortedArrays.doit([1, 2, 4, 5, 6], [3, 7])

   listRes = moveZeroes.doit([0,1,0,3,12])

   listRes = moveZeroes.doit([1,0])

   num = reverse.doit(1534236469)

   nums1 = [1, 2, 3, 0, 0, 0]
   nums2 = [4, 5, 6]
   mergeSortedArray.doit(nums1, len(nums1), nums2, len(nums2))

   num = longestValidParentheses.doit("(()")
   num = longestValidParentheses.doit("())")

   #mergeKLists.doit([[1]])

   nums1 = [1,2,2,2,3,3,3,4,5,5,5,6,6,7,8,9]
   removeDuplicates.doit(nums1)

   num = search.doit([4,5,6,7,8,9,1,2,3], 2)

   num = search.doit([1], 1)

   num = search.doit([1, 3], 0)

   num = search.doit([1, 3], 1)

   done = searchII.doit([1, 3], 1)
   
   done = searchII.doit([1, 2, 1], 2)

   done = searchII.doit([2,2,2,0,2,2], 2)

   done = searchII.doit([], 2)


   done = isMatch.resolve("aa", "a") == False

   done = isMatch.resolve("aa", "aa") == True

   done = isMatch.resolve("aa", "*") == True

   done = isMatch.resolve("a", "aa") == False

   done = isMatch.resolve("ho", "ho**") == True

   done = isMatch.resolve("", "*") == True
    
   done = isMatch.resolve("", "?") == False

   

   done = isMatch.resolve("aaabababaaabaababbbaaaabbbbbbabbbbabbbabbaabbababab", "*ab***ba**b*b*aaab*b") == True
   
   done = isMatch.resolve("babaaababaabababbbbbbaabaabbabababbaababbaaabbbaaab", "*bba*a*bbba*aab*b") == True

   done = isMatch.resolve("babaaababaabababbbbbbaabaabbabababbaababbaaabbbaaab", "***bba**a*bbba**aab**b") == True


     
   done = REMMatch().isMatch("aab", 'c*a*b')

   done = REMMatch().isMatch("ab",".*c")

   done = REMMatch().isMatch("a","ab*")

   done = REMMatch().isMatch("aaa","a*a")

   done = REMMatch().isMatch("aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s")

   done = REMMatch().isMatch("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c")


   
   end = 0
