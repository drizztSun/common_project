


def match(letters, words):

    m, n = len(letters), len(letters[0])
    res = []

    for i in range(m):
        for j in range(n):
            
            found_word = ''
            pos = []
            for w in words:
                found_word = w
                word_lenght = len(w)
                if j >= word_lenght and letters[i][j - word_lenght + 1 : j+1 : -1] == found_word:
                    pos = [i, j-word_lenght + 1, i, j]
                elif n - j >= word_lenght and letters[i][j : j + word_lenght] == found_word:
                    pos = [i, j, i, j + word_lenght - 1]
                elif i > word_lenght and letters[i - word_lenght + 1 : i + 1 : -1][j] == found_word:
                    pos = [i - word_lenght + 1, j, i, j]
                elif m - i >= word_lenght and  letters[i : i + word_lenght][j] == found_word:
                    pos = [i, j, i + word_lenght,j]
            else:
                pos = []
                found_word = ''

            if found_word:
                res.append((found_word, pos))
                words.remove(found_word)

    for a in res:
        print(a)

def main():

    source = ['DETAILWNRNZI',
                     'GARTRFKIIAIB',
                     'MAWHHSZAGNBV',
                     'TFQQTGCRHLSE',
                     'MCIAODIGTPJQ',
                     'ZOKYVMBERTBO',
                     'PFMARUQAHYUT',
                     'JHOWIAYGHQMX',
                     'UXOHHGIEWBEG',
                     'GCCGUEZSEESZ',
                     'HXPIHFAUICRV',
                     'QPAHOMKDANCA']

    words=set(['SIGH', 'RIGHT', 'WEIGH', 'EIGHT', 'DETAIL', 'HEIGHT', 'SPRAY', 'BRAID', 'BAIT', 'GRAIN', 'SLIGHT', 'THIGH', 'TIGHT', 'RAISIN', 'TRAIT', 'HIGHWAY', 'FRIGHTEN', 'DISMAY', 'FREIGHT', 'SLEIGH'])

    letter_matrix = [[a for a in c] for c in source]

    match(letter_matrix, words)

if __name__ == "__main__":

    main()