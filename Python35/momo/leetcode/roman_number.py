
class romanToInt:
    def way(self, s: str) -> int:
        a = 0
        convert = {'I' :1, 'V' :5, 'X' :10, 'L' :50, 'C' :100, 'D' :500, 'M' :1000}
        break_st = False
        for i in range(len(s)):
            if break_st:
                break_st = False
                continue
            if i+1 < len(s) and convert[s[i]] < convert[s[i+1]]:
                    if s[i] == 'I':
                        a += convert[s[i + 1]]-1
                        break_st = True
                    elif s[i] == 'X':
                        a += convert[s[i+1]]-10
                        break_st = True
                    elif s[i] == 'C':
                        a += convert[s[i+1]]-100
                        break_st = True
            else:
                a += convert[s[i]]

        return a

    def way2(self, s):
        ln = 0
        con = {'I' :1, 'V' :5, 'X' :10, 'L' :50, 'C' :100, 'D' :500, 'M' :1000}
        tot = 0
        for i in reversed(s):
            if ln <= con[i]:
                tot += con[i]
            else:
                tot -= con[i]
            ln = con[i]
        return tot

    def way3(self, s):
        lnum = 1001
        rom = {'I' :1, 'V' :5, 'X' :10, 'L' :50, 'C' :100, 'D' :500, 'M' :1000}
        tot = 0
        for i in s:
            tot += rom[i]
            if lnum < rom[i]:
                tot -= 2 * lnum
            lnum = rom[i]
        return tot

if __name__ == '__main__':

    print(romanToInt().way3("III"))
    print(romanToInt().way3("MXXIV"))
    print(romanToInt().way3("MCMXCIV"))#1994


