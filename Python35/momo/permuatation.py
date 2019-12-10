


def permute(nums):
    if len(nums) == 1:
        return [nums]

    res = []
    for i in range(len(nums)):
        
        # nums[i] + 
        # permute(nums[:i] + nums[i+1:])
        for c in permute(nums[:i] + nums[i+1:]):
            res.append( [nums[i]] + c)

    return res    


    

if __name__ == "__main__":

    nums = [1, 2, 3, 4, 5, 6, 7, 8, 9]

    print(permute(nums))

    pass