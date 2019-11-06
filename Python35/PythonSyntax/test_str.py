
def test_str():

    jwt = 'Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWV9.TJVA95OrM7E2cBab30RMHrHDcEfxjoYZgeFONFh7HgQ'

    jwt = jwt.lstrip().rstrip()

    if jwt.startswith('Bearer '):
        jwt = jwt[6:]
    
    jwt = jwt.lstrip().rstrip()

    print(jwt)

    # upper
    print(" abs upper case ", 'abc'.upper())

    # lower
    print(" ABC lower case ", 'ABC'.lower())

    # capitalize
    print("Captilize \'title\' will be ", 'title'.capitalize())

    # count
    print("cout \'Co\' in coco-cola is ", 'coco-cola'.count('co'))

    # startswith
    print(" \'Rocket\' starts with \'Rock\' is ", 'Rocket'.startswith('Rock'))

    # endwith
    print(" \'Rocket\' ends with \'cket\' is ", 'Rocket'.endswith('cket'))

    # find
    print(" \'Rocket\' finds \'cke\' at ", 'Rocket'.find('cke'))

    # rfind
    print(" \'abc efg abc\' has abc at right side", 'abc efg abc'.rfind('abc'))

    # index
    print(" \'Rocket\' index \'cke\' at ", 'Rocket'.index('cke'))

    # rfind
    print(" \'abc efg abc\' has abc at right side", 'abc efg abc'.index('abc'))

    try:
        print(" if \'Rocket\' has no \'abc\' at ", 'Rocket'.index('abc'))
    except:
        print("index could raise exception")

    # join
    print(" join [\'abc\', \'efg\', \'hji\'] is ", ''.join(['abc', 'efg', 'hji']))

    # lstrip
    print(" lstrip whitespace ", '  lstrip'.lstrip())

    # rstrip
    print("rstrip    whitespacw", 'rstrip   '.rstrip())

    # replace
    print(" \'abcabcabc\' replace \'ab\' with \'ef\' will be ", 'abcabcabc'.replace('ab', 'ef'))

    # split
    print(" \'abc.defg.hijk.lmn\' split is ", 'abc.defg.hijk.lmn'.split('.'))

    # splitlines
    print(" splitlines : \n", "it is line1,\n it is line2,\n    it is line3".splitlines())

    # max
    print("\'aababcabcdabcdeabcdefg\' max is ", max('aababcabcdabcdeabcdefg'))

    # min
    print("\'aababcabcdabcdeabcdefg\' min is ", min('aababcabcdabcdeabcdefg'))

    # isalpha
    print(" \'asjsdfjsdjgjds\' isalpha ", 'asjsdfjsdjgjds'.isalpha())

    # isalnum
    print(" \'aijfsajfhsdh102312903\' isalnum ", 'aijfsajfhsdh102312903'.isalnum())

    # isdigit
    print("\'8127312748\' isdigit ", '8127312748'.isdigit())

    # isupper
    print("\'ABC\' isupper ", 'ABC'.isupper())

    # islower
    print("\'abc\' islower ", 'abc'.islower())

    # isspace
    print("\'   \' isspace ", '   '.isspace())



if __name__ == "__main__":

    test_str()