"""
60. Permutation Sequence

The set [1,2,3,...,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note:

Given n will be between 1 and 9 inclusive.
Given k will be between 1 and n! inclusive.
Example 1:

Input: n = 3, k = 3
Output: "213"
Example 2:

Input: n = 4, k = 9
Output: "2314"

"""

"""
For n = 4, k = 9

We use factorial(n) n! to resolve this issue. The total result has n!, here is 4! ways. 
The first one has 4 ways, 1, 2, 3, 4. once we pick the first one like 1, then the possible starting with 1 will be (n-1)!, 3!.

so we need to know (1! .. (n-1)!), [1, 2, 6] then we use k! / m!, m(n-1 => 1) to locate the block or we say the first number of each level.
fact = [1, 1, 2, 6]
nums = [1, 2, 3, 4]
k = 9, idx = k / 3!, k -= idx * fact[3] so index = 1, first = 2, the rest is [1,3, 4]
k = 3, idx = k / 2!, k -= idx * fact[2] so index = 1, first = 3, the rest is [1, 4]
k = 1, idx = k / 1!, k -= idx * fact[1] so index = 1, first = 4, the rest is [1]
k = 0, idx = k / 1!, k -= idx * fact[0], so index = 0, first = 1, the rest is []  


1 2 3 4
1 2 4 3
1 3 2 4
1 3 4 2
1 4 2 3
1 4 3 2

2 ...
2 ...
2 ...
2 ...
2 ...
2 ...

3 ...
3 ...
3 ...
3 ...
3 ...
3 ...

4 ...
4 ...
4 ...
4 ...
4 ...
4 ...

"""
class GetPermutation:

    def doit(self, n: int, k: int):
        factorials, nums = [1], ['1']
        for i in range(1, n):
            # generate factorial system bases 0!, 1!, ..., (n - 1)!
            factorials.append(factorials[i - 1] * i)
            # generate nums 1, 2, ..., n
            nums.append(str(i + 1))

        # fit k in the interval 0 ... (n! - 1)
        k -= 1

        # compute factorial representation of k
        output = []
        for i in range(n - 1, -1, -1):
            idx = k // factorials[i]
            k -= idx * factorials[i]

            output.append(nums[idx])
            del nums[idx]

        return ''.join(output)

    def doit_(self, n: int, k: int) -> str:

        fact, nums = [1], ["1"]
        for i in range(1, n):
            fact.append(fact[-1] * i)
            nums.append(str(i + 1))

        k -= 1
        output = []
        for b in range(n - 1, -1, -1):
            idx = k // fact[b]
            k -= idx * fact[b]
            output.append(nums.pop(idx))

        return ''.join(output)


if __name__ == '__main__':

    GetPermutation().doit(n = 3, k = 3)

    GetPermutation().doit(n = 4, k = 9)
