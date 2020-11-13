"""

246. Strobogrammatic Number

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.



Example 1:

Input: num = "69"
Output: true
Example 2:

Input: num = "88"
Output: true
Example 3:

Input: num = "962"
Output: false
Example 4:

Input: num = "1"
Output: true

"""


class StrobogrammaticNumber:

    def doit(num):
        i, j = 0, len(num) - 1
        charMap = {'1':'1', '6':'9', '9':'6', '8':'8', '0':'0'}        

        while i <= j:
            if num[i] in charMap and charMap[num[i]] == num[j]:
                i += 1
                j -= 1
            else:
                return False
        return True
            

"""
# 247 Strobogrammatic Number II

# A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
# Find all strobogrammatic numbers that are of length = n.
# For example,
# Given n = 2, return ["11","69","88","96"].

# Hint:
# Try to use recursion and notice that it should recurse with n - 2 instead of n - 1.

"""


class StrobogrammaticNumberII:

    def doit(self, n):
        
        charMap = {'1':'1', '6':'9', '9':'6', '8':'8', '0':'0'}        

        def make(s):
            if s == 0:
                return ['']
            if s == 1:
                return ['1', '8', '0']

            keys = ['1', '6', '9', '8']
            if s < n:
                keys.append('0')

            res = []
            for child in make(s-2):
                for i in keys:
                    res.append(i + child + charMap[i])
                
            return res

        return make(n)

    def doit(self, n):
        
        ans = ['1', '8', '0'] if n % 2 == 1 else []
        n = n//2
        for i in range(n):
            tmp = []
            for word in ans:            
                tmp.append('1' + word + '1')
                tmp.append('6' + word + '9')
                tmp.append('9' + word + '6')
                tmp.append('8' + word + '8')
                if i != n-1:
                    tmp.append('0' + word + '0')
            ans = tmp
    
        return ans


"""

248 Strobogrammatic Number III

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

Example:

Input: low = "50", high = "100"
Output: 3 
Explanation: 69, 88, and 96 are three strobogrammatic numbers.
Note:
Because the range might be a large number, the low and high numbers are represented as string.

"""


class StrobogrammaticNumberIII:

    def doit(self, low, high):
        """
        type : str
        type : str
        rtype : List[str]
        """
        if int(high) < int(low):
            return 0

        dic = {'0': '0', '1': '1', '8': '8', '6': '9', '9': '6'}
        mset = {'0': '0', '1': '1', '8': '8'}
        self.cnt = 0

        def dfs(cur, length):
            if length == len(cur):
                if length != 1 and cur[0] == '0': return
                if (length == len(low) and low > cur) or (length == len(high) and high < cur):
                    return
                self.cnt += 1
                return
            if len(cur) + 2 <= length:
                for add in dic:
                    dfs(add + cur + dic[add], length)

        nl, nh = len(low), len(high)
        if nl == nh:
            if nl % 2 == 0:
                dfs('', nl)
            else:
                for mid in mset:
                    dfs(mid, nl)
        elif nl + 1 == nh:
            if nl % 2 == 0:
                dfs('', nl)
                for mid in mset:
                    dfs(mid, nh)
            else:
                for mid in mset:
                    dfs(mid, nl)
                dfs('', nh)
        else:
            if nl % 2 == 0:
                dfs('', nl)
            else:
                for mid in mset:
                    dfs(mid, nl)

            if nh % 2 == 0:
                dfs('', nh)
            else:
                for mid in mset:
                    dfs(mid, nh)

            for l in xrange(nl + 1, nh):
                half, mid = l // 2, l % 2
                self.cnt += (4 ** (1 if half else 0)) * (5 ** max(half - 1, 0)) * (3 ** mid)
        return self.cnt


    """
    The following solution has been segregated into 3 cases

        Case 1: The difference between the lengths of lowest and highest numbers in the range is >=2
        For example, 98 and 132323 which has a difference of 4 (98 is 2, 132323 is 6)
        I intend to to count the elements of the list which have 3,4,5 digits respectively and add them
        The rest is calculated by the remaining elements left in 2&6 length which are greater and lesser than the limits given.
        Case 2: Difference is 1, Calculating Strobogrammatic Numbers greater than low and lesser than high is enough
        Case 3: low and high are the bounds in a single list, counting numbers between them is enough
    """

    def doit_2(self, low: str, high: str) -> int:
        a = len(low)
        b = len(high)
        sum = 0
        if b - a >= 2:
            for i in range(a + 1, b):
                sum += self.count(i)
            minimum = self.finish(a)
            maximum = self.finish(b)
            sum += self.first(minimum, low) + self.second(maximum, high)

        elif b - a == 1:
            minimum = self.finish(a)
            maximum = self.finish(b)
            sum += self.first(minimum, low) + self.second(maximum, high)

        elif b - a == 0:
            outcome = self.finish(a)
            sum = self.third(outcome, low, high)

        return sum

    # Count how many elements are greater than or equal to the lower number in a given list
    def first(self, list1, low):
        i = 0
        for x in list1:
            if low <= x:
                i += 1
        return i

    # Count how many elements are lesser than or equal to the lower number in a given list
    def second(self, list2, high):
        j = 0
        for y in list2:
            if high >= y:
                j += 1
        return j

        # Count the number of elements in a list given a range
        def third(self, list3, low, high):
            return len(list(x for x in list3 if low <= x <= high))

    # This is Strobogrammatic Number II
    # The below prints/counts the list of Strobogrammatic Numbers that are of length = n
    # prints the list
    def finish(self, n: int) -> List[str]:
        if not n:
            return ['']
        if n == 1:
            return ["0", "1", "8"]
        ret = []
        for x in self.recursion(n):
            if x[0] != '0':
                ret.append(x)
        return ret

    # counts how many in the list
    def count(self, n: int) -> List[str]:
        if not n:
            return ['']
        if n == 1:
            return ["0", "1", "8"]
        ret = []
        for x in self.recursion(n):
            if x[0] != '0':
                ret.append(x)
        return len(ret)

    # recursion is used as per the 2nd question
    def recursion(self, n):
        if n == 1:
            return ["0", "1", "8"]
        if n == 2:
            return ["00", "11", "69", "88", "96"]
        x = self.recursion(n - 2)
        y = self.recursion(2)
        ret = []
        for one in y:
            for two in x:
                ret.append(one[0] + two + one[1])
        return ret

    def doit_1(self, low: str, high: str) -> int:

        def helper(i):
            if i < 0:
                return 0
            elif i < 1:
                return 1
            elif i < 8:
                return 2
            else:
                return 3

        def getCount(self, low, high):
            l = len(low)
            if l == 0:
                return 1
            if l == 1:
                return helper(int(high)) - helper(int(low) - 1)

            ans = 0
            for i, op_i in [('0', '0'), ('1', '1'), ('6', '9'), ('8', '8'), ('9', '6')]:
                if i < low[0] or i > high[0]: # if i less then low or higher then high, no need to do
                    continue

                if i > low[0]:
                    # if i greater then low[0], '3', '2xxx', 'xxx' could be any one from 'candidates', so next low '000'
                    new_low = '0' * (l - 2)
                else:
                    if op_i >= low[-1]:
                        # if op_i bigger than and equal to last one, op_i '6xxx9' and '6xxx7',
                        new_low = low[1:-1]
                    else:
                        # if last one high then op_i '92347' and '9xxx6'
                        if low[1:-1] == '9' * (l - 2):
                            continue # if all 69999, no more
                        else:
                            new_low = str(int(low[1:-1]) + 1) # we don't need lower one, so we add 1

                if i < high[0]:
                    # if i less then high[0], like '1xxxx' and '23456', it means 'xxxx' should be high to '9999'
                    new_high = '9' * (l - 2)
                else:
                    # if i == high[0], like '6xxxx' and '67898'
                    if op_i <= high[-1]:
                        # if last one higher and equal then op_t, '8xxx8', '8xxx9'
                        new_high = high[1:-1]
                    else:
                        # last one higher than '0000', means there is no more.
                        if high[1:-1] == '0' * (l - 2):
                            continue
                        else:
                            new_high = str(int(high[1:-1]) - 1)
                ans += getCount(new_low, new_high)

            return ans

        l1 = len(low)
        l2 = len(high)
        if l1 > l2:
            return 0

        if l1 == l2:
            return getCount(low, high)

        a = getCount(low, '9' * l1)
        b = getCount('1' + '0' * (l2 - 1), high)
        ans = a + b
        for j in range(l1 + 1, l2):
            if j & 1:
                num = 3 * (5 ** ((j - 1) // 2 - 1)) * 4
            else:
                num = 4 * (5 ** (j // 2 - 1))
            ans += num

        return ans


class Solution:
    def strobogrammaticInRange(self, low, high):
        """
        :type low: str
        :type high: str
        :rtype: int
        """
        a = self.below(high)
        b = self.below(low, include=False)
        return a - b if a > b else 0

    # get how many strobogrammatic numbers less than n (include=True for <=n; include=False for <n)
    def below(self, n, include=True):
        res = 0
        for i in range(1, len(n)):  # 长度为1到len(n)-1的范围内，strobogrammatic的数量，可以直接用数学方法获取！
            res += self.math_number(
                i)  # if the length is between 1 and len(n)-1, we calculate its number directly using math!

        l = self.strobogrammatic(len(n))  # for calling the iterative bfs method
        # l = self.strobogrammatic2(len(n)) # for calling the recursive method

        if include:
            l = [num for num in l if (len(num) == 1 or num[0] != '0') and num <= n]  # filtering
        else:
            l = [num for num in l if (len(num) == 1 or num[0] != '0') and num < n]
        return res + len(l)

    # bfs - iterative method
    def strobogrammatic(self, l):
        # return a set of results that with a length=l
        q = collections.deque()
        if l % 2 == 1:
            q.append('0')
            q.append('1')
            q.append('8')
        else:
            q.append('')
        for i in range(l // 2 - 1, -1, -1):
            qsize = len(q)
            for j in range(qsize):
                cand = q.popleft()
                left = ['0', '6', '1', '9', '8']
                right = ['0', '9', '1', '6', '8']
                for k in range(len(left)):
                    if i == 0 and k == 0:
                        continue
                    cand2 = left[k] + cand + right[k]
                    q.append(cand2)
        return list(q)

    # recursive method:
    def strobogrammatic2(self, l):
        res = []
        if l == 1:
            return ['0', '1', '8']
        if l == 2:
            return ['00', '11', '69', '96', '88']
        for s in self.strobogrammatic(l - 2):  # recursive method
            res.append('0' + s + '0')
            res.append('1' + s + '1')
            res.append('6' + s + '9')
            res.append('8' + s + '8')
            res.append('9' + s + '6')
        return res

    # directly calculate number using math method:
    def math_number(self, l):  # l = length of the number
        if l == 0:
            return 0
        # 如果l是偶数，第一个元素有4个可选(1,6,8,9)，其他从1到l//2分别是5个可选(0,1,6,8,9)
        # if l is even, the first element (position 0) has four selections, (1,6,8,9); and other positions from 1 to l//2 each have 5 options (0,1,6,8,9)
        if l % 2 == 0:
            return 4 * (5 ** (l // 2 - 1))
        # 如果l是奇数，middle = 3 (0,1,8); first = 4 (1,6,8,9);
        # if l is odd, the middle position has 3 selections (0,1,8) and the 0-th position has 4 selections (1,6,8,9)
        # other positions (from 1 to l//2-1, l//2-1-1+1=l//2-1 elements) have 5 selections (0,1,6,8,9)
        elif l == 1:
            return 3  # 0, 1, 8 are allowed, thus return 3
        else:
            return 3 * (5 ** (l // 2 - 1)) * 4