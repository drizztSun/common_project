class Solution:
    # 40ms
    def twoSum(self, a: list , tar: int):
        f = {a[i]:i for i in range(len(a))}
    
        for i in range(len(a)):
            if tar-a[i] in f:
                if f[tar-a[i]] == i:
                    continue
                return i, f[tar-a[i]] 
    # 28ms
    def twoSum2(self, nums: list, target: int) -> list:
        hash = {}
        for i in range(len(nums)):
            compliment = target - nums[i]
            if compliment in hash: return [hash[compliment], i]
            hash[nums[i]] = i

if __name__ == "__main__":

    print(Solution().twoSum([3, 3], 6))