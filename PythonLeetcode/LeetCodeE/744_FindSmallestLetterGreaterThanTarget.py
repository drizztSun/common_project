# 744. Find Smallest Letter Greater Than Target

#Given a list of sorted characters letters containing only lowercase letters, and given a target letter target, find the smallest element in the list that is larger than the given target.

#Letters also wrap around. For example, if the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.

#Examples:
#Input:
#letters = ["c", "f", "j"]
#target = "a"
#Output: "c"

#Input:
#letters = ["c", "f", "j"]
#target = "c"
#Output: "f"

#Input:
#letters = ["c", "f", "j"]
#target = "d"
#Output: "f"

#Input:
#letters = ["c", "f", "j"]
#target = "g"
#Output: "j"

#Input:
#letters = ["c", "f", "j"]
#target = "j"
#Output: "c"

#Input:
#letters = ["c", "f", "j"]
#target = "k"
#Output: "c"


class NextGreatestLetter:
    def doit(self, letters: 'List[str]', target: 'str') -> 'str':
        
        l, h = 0, len(letters)
        ans = 0
        
        while l < h:
            
            mid = (l + h) // 2
            
            if letters[mid] <= target:
                l = mid + 1
            else:
                h = mid
        else:
            ans = l
                
        return letters[ans % len(letters)]
        
        
if __name__ == "__main__":

    res = NextGreatestLetter().doit(["c", "f", "j"], "a")

    res = NextGreatestLetter().doit(["e","e","e","e","e","e","n","n","n","n"], "n")

    res = NextGreatestLetter().doit(["c", "f", "j"], "c")

    res = NextGreatestLetter().doit(["c", "f", "j"], "f") 

    res = NextGreatestLetter().doit(["c", "f", "j"], "j")  