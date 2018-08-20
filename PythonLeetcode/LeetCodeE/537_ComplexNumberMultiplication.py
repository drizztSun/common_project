# 537. Complex Number Multiplication

# Given two strings representing two complex numbers.

# You need to return a string representing their multiplication. Note i2 = -1 according to the definition.

# Example 1:
# Input: "1+1i", "1+1i"
# Output: "0+2i"
# Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.

# Example 2:
# Input: "1+-1i", "1+-1i"
# Output: "0+-2i"

# Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
# Note:

# The input strings will not have extra blank.
# The input strings will be given in the form of a+bi, where the integer a and b will both belong to the range of [-100, 100]. 
# And the output should be also in this form.


class ComplexNumberMultiply:
    def doit(self, num1, num2):
        """
        :type a: str
        :type b: str
        :rtype: str
        """
        def divide(s):
            ss = s.split('+')
            return int(ss[0]), int(ss[1][:-1])

        a, b = divide(num1)
        c, d = divide(num2)

        return str(a * c - b * d) + "+" + str(a * d + b * c) + "i"


if __name__ == "__main__":

    res = ComplexNumberMultiply().doit("1+1i", "1+1i")

