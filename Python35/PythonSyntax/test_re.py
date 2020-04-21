import re

# Metacharacters
# Metacharacters are characters with a special meaning:
# []	A set of characters	"[a-m]"
# \	Signals a special sequence (can also be used to escape special characters)	"\d"
# .	Any character (except newline character)	"he..o"
# ^	Starts with	"^hello"
# $	Ends with	"world$"
# *	Zero or more occurrences	"aix*"
# +	One or more occurrences	"aix+"
# {}	Exactly the specified number of occurrences	"al{2}"
# |	Either or	"falls|stays"
# ()	Capture and group


# Special Sequences
# A special sequence is a \ followed by one of the characters in the list below, and has a special meaning:
# Character	Description	Example	Try it
# \A	Returns a match if the specified characters are at the beginning of the string	"\AThe"
# \b	Returns a match where the specified characters are at the beginning or at the end of a word
# (the "r" in the beginning is making sure that the string is being treated as a "raw string")	r"\bain"
# r"ain\b"
# \B	Returns a match where the specified characters are present, but NOT at the beginning (or at the end) of a word
# (the "r" in the beginning is making sure that the string is being treated as a "raw string")	r"\Bain"
# r"ain\B"
# \d	Returns a match where the string contains digits (numbers from 0-9)	"\d"
# \D	Returns a match where the string DOES NOT contain digits	"\D"
# \s	Returns a match where the string contains a white space character	"\s"
# \S	Returns a match where the string DOES NOT contain a white space character	"\S"
# \w	Returns a match where the string contains any word characters (characters from a to Z, digits from 0-9, and the underscore _ character)	"\w"
# \W	Returns a match where the string DOES NOT contain any word characters	"\W"
# \Z	Returns a match if the specified characters are at the end of the string	"Spain\Z"


# Sets
# A set is a set of characters inside a pair of square brackets [] with a special meaning:
# [arn]	Returns a match where one of the specified characters (a, r, or n) are present
# [a-n]	Returns a match for any lower case character, alphabetically between a and n
# [^arn]	Returns a match for any character EXCEPT a, r, and n
# [0123]	Returns a match where any of the specified digits (0, 1, 2, or 3) are present
# [0-9]	Returns a match for any digit between 0 and 9
# [0-5][0-9]	Returns a match for any two-digit numbers from 00 and 59
# [a-zA-Z]	Returns a match for any character alphabetically between a and z, lower case OR upper case
# [+]	In sets, +, *, ., |, (), $,{} has no special meaning, so [+] means: return a match for any + character in the string


def test_regex():

    # findall()
    # The findall() function returns a list containing all matches.
    x = re.findall("ai", "The rain in Spain") # if no match, it is None
    print(x)


    # search()
    # The search() function searches the string for a match, and returns a Match object if there is a match.
    # If there is more than one match, only the first occurrence of the match will be returned:

    # Match Object returns,
    # A Match Object is an object containing information about the search and the result.
    x = re.search("^The.*Spain$", "The rain in Spain")

    # The Match object has properties and methods used to retrieve information about the search, and the result:
    print(x.span()) # returns a tuple containing the (start-, and end-) positions of the match.

    print(x.string) # returns the string passed into the function

    print(x.group()) # returns the part of the string where there was a match

    x = re.search("\s", "The rain in Spain")
    print(x.span())
    print(x.group())

    # split()
    # The split() function returns a list where the string has been split at each match:
    text = 'The rain in Spain'
    x = re.split("\s", text)
    print(x)

    # Control the number of occurrences by specifying the maxsplit parameter:
    x = re.split("\s", text, 1)
    print(x)

    # sub()
    # The sub() function replaces the matches with the text of your choice:
    x = re.sub("\s", "-", "The rain in Spain")
    print(x)

    # Control the number of replacements by specifying the count parameter
    x = re.sub("\s", "-", "The rain in Spain", 2)
    print(x)




    # Example
    x = re.findall("\d+\.?", "Ubuntu 16.04.6 LTS")
    print(''.join(x))
    pass




if __name__ == '__main__':

    test_regex()