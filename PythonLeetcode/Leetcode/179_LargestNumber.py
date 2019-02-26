# 179. Largest Number

#Given a list of non negative integers, arrange them such that they form the largest number.

#Example 1:

#Input: [10,2]
#Output: "210"
#Example 2:

#Input: [3,30,34,5,9]
#Output: "9534330"
#Note: The result may be very large, so you need to return a string instead of an integer.

# The main idea is to compare two str(str1+str2 and str2 + str1), and using built-in function sorted to sort list, 
#and then produce the result string, but the speed is slow, i guess that sorting step consume much time. Can somebody modify the code to speeding up

class LargestNumber:
    def doit(self, nums: 'List[int]') -> 'str':
        import functools
        
        def compare(x, y):
            return 1 if str(x) + str(y) < str(y) + str(x) else -1

        nums = [str(r) for r in sorted(nums, key=functools.cmp_to_key(compare))]
        
        ans = ''.join(nums)
        
        return '0' if ans.startswith('0') else ans

    def doit1(self, nums: 'List[int]') -> 'str':
        return str(int(''.join(sorted(map(str, nums), key = lambda _:_ * 9, reverse = True))))


    def doit2(self, nums: 'List[int]') -> 'str':

        compare = lambda x, y: x + y > y + x

        numstr = [str(c) for c in nums]

        def partition(l, h):
            
            j = l+1
            for i in range(l+1, h+1):

                if compare(numstr[i], numstr[l]):
                    numstr[i], numstr[j] = numstr[j], numstr[i]
                    j += 1
            numstr[l], numstr[j-1] = numstr[j-1], numstr[l]

            return j-1

        def quicksort(l, h):
            if l >= h:
                return

            m = partition(l, h)
            quicksort(l, m-1)
            quicksort(m+1, h)

        quicksort(0, len(numstr) - 1)
        return '0' if numstr[0].startswith('0') else ''.join(numstr)



class LargerNumKey(str):
    def __lt__(x, y):
        return x+y > y+x
    
class Solution:
    def largestNumber(self, nums: 'List[int]') -> 'str':
        input_str=list(map(str,nums))

        input_str.sort(key=LargerNumKey)

        while len(input_str)>1 and input_str[0]=='0':
            input_str.pop(0)

        return ''.join(map(str,input_str))
        


if __name__ == "__main__":

    LargestNumber().doit2([10, 2])

    LargestNumber().doit2([3, 30, 35, 5, 9])