import os


# leetcode  44. Wildcard Matching
# Implement wildcard pattern matching with support for '?' and '*'.

# '?' Matches any single character.
# '*' Matches any sequence of characters (including the empty sequence).

# The matching should cover the entire input string (not partial).

# The function prototype should be:
# bool isMatch(const char *s, const char *p)

# Some examples:
# isMatch("aa","a") ? false
# isMatch("aa","aa") ? true
# isMatch("aaa","aa") ? false
# isMatch("aa", "*") ? true
# isMatch("aa", "a*") ? true
# isMatch("ab", "?*") ? true
# isMatch("aab", "c*a*b") ? false


class isMatch:

    # Best way so far    
    def doit(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        si, pi =  0, 0
        sstar, pstar = -1, -1
        
        while si < len(s):
            
            if pi < len(p) and (p[pi] == '?' or p[pi] == s[si]):
                pi, si = pi+1, si+1
            
            elif pi < len(p) and p[pi] == '*':
                sstar = si
                pstar = pi
                pi += 1
                
            elif sstar != -1:
                sstar += 1
                si = sstar
                pi = pstar + 1
            
            else:
                return False
            
        while pi < len(p) and p[pi] == '*':
            pi += 1
            
        return pi == len(p)

    # DP good way
    def doit1(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        D = [False for x in range(len(s)+1)]
        D[0] = True

        for i in range(1, len(p) + 1):
            
            if p[i-1] != '*':
                for j in reversed(range(1, len(s)+1)):
                    # when (s[0..i-1], p[0..j-1]) is matched, and (s[i], p[j]) is matched
                    D[j] = D[j-1] and (p[i-1] == s[j-1] or p[i-1] == '?')  
            else:
                for n in range(1, len(s)+1):
                    # D[i,j] = D[i-1, j] or D[i, j-1]
                    D[n] = D[n] or D[n-1]

            D[0] = D[0] and p[i-1] == '*'

        return D[len(s)]


    # slowest way not good
    # TODO: almost get TLE 
    def doit4(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        def search(src, si, tar, ti, buff):

            if (si, ti) in buff:
                return buff[(si, ti)]
    
            if ti == len(tar):
                return si == len(src)
            
            res = False
            if tar[ti] == "*":
                ct = ti + 1
                while ct < len(tar) and tar[ct] == '*':
                    ct += 1

                cur = si
                while not res and cur <= len(src):
                    res = search(src, cur, tar, ct, buff)
                    cur += 1

            if not res and si < len(src) and ti < len(tar) and (src[si] == tar[ti] or tar[ti] == '?'):
                res = search(src, si+1, tar, ti+1, buff)

            buff[(si, ti)] = res
            return res


        return search(s, 0, p, 0, {})


    # TODO:
    def doit2(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        def search(src, si, tar, ti, recurLevel) :
            
            first, curLevel = True, recurLevel
            
            while si < len(src) and ti < len(tar) and (src[si] == tar[ti] or tar[ti] != '?'):
                si += 1
                ti += 1

            if ti == len(tar):
                return si == len(src)

            if tar[ti] == '*':
                while ti < len(tar) and tar[ti] == '*':
                    ti += 1

                if ti == len(tar):
                    return True

                for i in range(si, len(src)):
                    if tar[ti] != '?' and src[i] != tar[ti]:
                        continue 

                    if first:
                        revLevel += 1
                        first = False
        
                    if help(src, i, tar, ti, recurLevel):
                        return True

                    if recurLevel > curLevel + 1:
                        return False

            pass

        return search(s, 0, p, 0)



if __name__=="__main__":


    res = isMatch().doit("abefcdgiescdfimde", "ab*cd?i*de") # True

    res = isMatch().doit("a", "aa") #False

    res = isMatch().doit("", "*") #True

    res = isMatch().doit("aa", "a") #False

    res = isMatch().doit("aa", "aa") #True

    res = isMatch().doit("aaa", "aa") #False
    
    res = isMatch().doit("aa", "*") #True

    res = isMatch().doit("aa", "a*") #True

    res = isMatch().doit("aa", "?*") # True

    res = isMatch().doit("aab", "c*a*b") # False

    

    pass