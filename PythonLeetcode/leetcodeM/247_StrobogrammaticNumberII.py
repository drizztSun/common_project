"""
247. Strobogrammatic Number II

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

Example:

Input:  n = 2
Output: ["11","69","88","96"]

"""



class StrobogrammaticII:

    def doit_(self, n: int) -> list:

        base = {'1':'1', '6':'9', '9':'6', '8':'8', '0':'0'}

        def search(s):
            
            if s == 0:
                return ['']
            
            if s == 1:
                return ['0', '1','8']

            
            tmp = search(s-2)
            res = []
            
            for k, v in base.items():
                if s == n and k == '0':
                    continue;
                for c in tmp:
                    res.append(k + c + v)
            return res

        return search(n)