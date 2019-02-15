# 842. Split Array into Fibonacci Sequence

# Given a string S of digits, such as S = "123456579", we can split it into a Fibonacci-like sequence [123, 456, 579].

# Formally, a Fibonacci-like sequence is a list F of non-negative integers such that:

# 0 <= F[i] <= 2^31 - 1, (that is, each integer fits a 32-bit signed integer type);
# F.length >= 3;
# and F[i] + F[i+1] = F[i+2] for all 0 <= i < F.length - 2.
# Also, note that when splitting the string into pieces, each piece must not have extra leading zeroes, 
# except if the piece is the number 0 itself.

# Return any Fibonacci-like sequence split from S, or return [] if it cannot be done.

# Example 1:

# Input: "123456579"
# Output: [123,456,579]
# Example 2:

# Input: "11235813"
# Output: [1,1,2,3,5,8,13]
# Example 3:

# Input: "112358130"
# Output: []
# Explanation: The task is impossible.
# Example 4:

# Input: "0123"
# Output: []
# Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
# Example 5:

# Input: "1101111"
# Output: [110, 1, 111]
# Explanation: The output [11, 0, 11, 11] would also be accepted.
# Note:

# 1 <= S.length <= 200
# S contains only digits.


class SplitIntoFibonacci:


# Approach #1: Brute Force [Accepted]
# Intuition

# The first two elements of the array uniquely determine the rest of the sequence.

# Algorithm

# For each of the first two elements, assuming they have no leading zero, let's iterate through the rest of the string. 
# At each stage, we expect a number less than or equal to 2^31 - 1 that starts with the sum of the two previous numbers.

    def doit(self, S):

        for i in range(min(10, len(S))):
            
            x = S[:i+1]
            if x != '0' and x.startswith('0'):
                break
                
            for j in range(i+1, min(i+10, len(S))):
                
                y = S[i+1:j+1]
                if y != '0' and y.startswith('0'):
                    break
                    
                Fib = [int(x), int(y)]
                
                k = j+1
                while k < len(S):
                    nxt = Fib[-1] + Fib[-2]
                    nxtS = str(nxt)
                    
                    if nxt < 2**31 - 1 and S[k:].startswith(nxtS):
                        k += len(nxtS)
                        Fib.append(nxt)
                        continue
                    
                    else:
                        break
                else:
                    if len(Fib) > 2:
                        return Fib
                    
        return []


    def doit2(self, S: 'str') -> 'List[int]':
       
        res, i, L = [], 0, 1

        # not_found = set()
    
        while i + L <= len(S):

            while L < len(S) / 2 and i + L <= len(S):

                if L > 1 and S[i] == '0':
                    break

                c = int(S[i:i+L])
                if len(res) < 2 or c == res[-1] + res[-2]:
                    i += L
                    res.append(c)
                    if len(res) > 2 and i == len(S):
                        return res

                    L = 1
                    continue
                else:
                    if c > res[-1] + res[-2]:
                        #not_found.add(tuple(res))                        
                        break
                    else:
                        L += 1

            if len(res) > 0:
                c = res.pop()
                L = len(str(c))
                i -= L
            L += 1

            # 
            if not res and L > len(S) / 2:
                break
                
        return res


if __name__ == "__main__":

    res = SplitIntoFibonacci().doit("1101111")

    res = SplitIntoFibonacci().doit("123456579")

    res = SplitIntoFibonacci().doit("112358130")

    res = SplitIntoFibonacci().doit("0123")

    res = SplitIntoFibonacci().doit("0000")

    res = SplitIntoFibonacci().doit("539834657215398346785398346991079669377161950407626991734534318677529701785098211336528511")

    res = [-1, -1, -1, -1]


    
                                        

                    

                    
        
        