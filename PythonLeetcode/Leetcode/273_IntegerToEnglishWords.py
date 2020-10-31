"""
273. Integer to English Words

Convert a non-negative integer num to its English words representation.



Example 1:

Input: num = 123
Output: "One Hundred Twenty Three"
Example 2:

Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"
Example 3:

Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Example 4:

Input: num = 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"


"""


class NumberToWords:

    def doit(self, num: int):

        if num == 0:
            return 'Zero'

        def num_word(n):
            huns = (n - n % 100) // 100
            tens = n % 100 - n % 10
            tenones = n % 100
            ones = n % 10
            res = ''

            if huns:
                res = words[huns] + ' Hundred'

            if tenones in words:
                res += (' ' if res else '') + words[tenones]
            else:
                if tens in words:
                    res += (' ' if res else '') + words[tens]

                if ones in words:
                    res += (' ' if res else '') + words[ones]

            return res

        words = {1: "One", 2: "Two", 3: "Three", 4: "Four", 5: "Five", 6: "Six", 7: "Seven", 8: "Eight", 9: "Nine",
                 10: "Ten",
                 11: "Eleven", 12: "Twelve", 13: "Thirteen", 14: "Fourteen", 15: "Fifteen", 16: "Sixteen",
                 17: "Seventeen", 18: "Eighteen",
                 19: "Nineteen", 20: "Twenty", 30: "Thirty", 40: "Forty", 50: "Fifty", 60: "Sixty", 70: "Seventy",
                 80: "Eighty", 90: "Ninety"}
        base = ["", " Thousand", " Million", " Billion"]
        i, res = 0, []

        while num > 0:
            num, r = divmod(num, 1000)
            tmp = num_word(r)
            if tmp:
                res.append(tmp + base[i])
            i += 1

        return ' '.join(res[::-1])

    def doit_math(self, num):
        """
        :type num: int
        :rtype: str
        """
        top19 = "One Two Three Four Five Six Seven Eight Nine Ten Eleven Twelve Thirteen Fourteen Fifteen Sixteen Seventeen Eighteen Nineteen".split()
        tens = "Twenty Thirty Forty Fifty Sixty Seventy Eighty Ninety".split()

        def word(n):
            if n < 20:
                return top19[n - 1:n]

            if n < 100:
                return [tens[n // 10 - 2]] + word(n % 10)

            if n < 1000:
                return [top19[n // 100 - 1]] + ["Hundred"] + word(n % 100)

            for i, p in enumerate(('Thousand', 'Million', 'Billion'), 1):
                if n < 1000 ** (i + 1):
                    return word(n // 1000 ** i) + [p] + word(n % 1000 ** i)

        return ' '.join(word(num)) or 'Zero'


if __name__ == '__main__':

    NumberToWords().doit(123)

    NumberToWords().doit(12345)

    NumberToWords().doit(1234567)

    NumberToWords().doit(1234567891)