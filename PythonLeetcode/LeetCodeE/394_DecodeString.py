


# 394. Decode String

# Given an encoded string, return it's decoded string.

# The encoding rule is: k[encoded_string], where the encoded_string inside
# the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

# You may assume that the input string is always valid;
# No extra white spaces, square brackets are well-formed, etc.

# Furthermore, you may assume that the original data does not contain any
# digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

# Examples:

# s = "3[a]2[bc]", return "aaabcbc".
# s = "3[a2[c]]", return "accaccacc".
# s = "2[abc]3[cd]ef", return "abcabccdcdcdef".


class decodeString(object):


    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        stack = [["", 1]]
        num = ''
        
        for c in s:
            if c.isdigit():
                num += c
            elif c == '[':
                stack.append(["", int(num)])
                num = ''
            elif c == ']':
                a = stack.pop()
                stack[-1][0] += a[0] * a[1]
            
            else :
                stack[-1][0] += c
                
        return stack[-1][0]

    def doit(self, s):
        """
        :type s: str
        :rtype: str
        """
        stack = []
        res = ''
        i = 0
        while i < len(s):

            if s[i].isdigit():
                start = i
                while i < len(s) and s[i].isdigit():
                   i += 1
                amount = int(s[start:i])

                i += 1
                b = '' 
                while i < len(s) and not(s[i].isdigit() or s[i] == ']'):
                    b += s[i]
                    i += 1

                if s[i].isdigit() or s[i] == ']':
                    stack.append([amount, b])
                    continue
                
            elif s[i] == ']':

                A = stack.pop()
                a = A[1] * int(A[0])
                if stack:
                    stack[-1][1] += a
                else:
                    res += a

            else:
                if stack:
                    stack[-1][1] += s[i]
                else:
                    res += s[i]

            i += 1

        return res
    


if __name__ == "__main__":

    res = decodeString().doit("")
    
    res = decodeString().doit("abcd")

    res = decodeString().doit("3[a]2[bc]")

    res = decodeString().doit("3[a2[c]]")

    res = decodeString().doit("3[a2[c]ef]")

    res = decodeString().doit("2[abc]3[cd]ef")

    res = decodeString().doit("100[leetcode]")

    pass

