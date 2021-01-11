def titleToNumber(s: str) -> int:
    res = 0
    buff = {k: v for k, v in zip(
        ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
         'W', 'X', 'Y', 'Z']
        , [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26])}
    for i in range(len(s) - 1, 0, -1):
        res += buff[s[i]] * 26 ^ i
    return res


if __name__ == "__main__":
    titleToNumber('a')
