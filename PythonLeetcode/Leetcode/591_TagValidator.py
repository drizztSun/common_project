


# 591. Tag Validator


# Given a string representing a code snippet, you need to implement a tag validator to parse the code and return whether it is valid.
# A code snippet is valid if all the following rules hold:

# 1. The code must be wrapped in a valid closed tag. Otherwise, the code is invalid.
# 2. A closed tag (not necessarily valid) has exactly the following format : <TAG_NAME>TAG_CONTENT</TAG_NAME>.
#    Among them, <TAG_NAME> is the start tag, and </TAG_NAME> is the end tag. The TAG_NAME in start and end tags should be the same. 
#    A closed tag is valid if and only if the TAG_NAME and TAG_CONTENT are valid.
# 3. A valid TAG_NAME only contain upper-case letters, and has length in range [1,9]. Otherwise, the TAG_NAME is invalid.

# 4. A valid TAG_CONTENT may contain other valid closed tags, cdata and any characters (see note1) EXCEPT unmatched <,
#    unmatched start and end tag, and unmatched or closed tags with invalid TAG_NAME. Otherwise, the TAG_CONTENT is invalid.
# 5. A start tag is unmatched if no end tag exists with the same TAG_NAME, and vice versa. 
#    However, you also need to consider the issue of unbalanced when tags are nested.
# 6. A < is unmatched if you cannot find a subsequent >. And when you find a < or </, all the subsequent characters until the next >
#    should be parsed as TAG_NAME (not necessarily valid).
# 7. The cdata has the following format : <![CDATA[CDATA_CONTENT]]>. 
#    The range of CDATA_CONTENT is defined as the characters between <![CDATA[ and the first subsequent ]]>.
# 8. CDATA_CONTENT may contain any characters. The function of cdata is to forbid the validator to parse CDATA_CONTENT,
#    so even it has some characters that can be parsed as tag (no matter valid or invalid), you should treat it as regular characters.


# Valid Code Examples:
# Input: "<DIV>This is the first line <![CDATA[<div>]]></DIV>"
# Output: True

# Explanation: 

# The code is wrapped in a closed tag : <DIV> and </DIV>. 
# The TAG_NAME is valid, the TAG_CONTENT consists of some characters and cdata. 
# Although CDATA_CONTENT has unmatched start tag with invalid TAG_NAME, it should be considered as plain text, not parsed as tag.
# So TAG_CONTENT is valid, and then the code is valid. Thus return true.


# Input: "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"
# Output: True

# Explanation:
# We first separate the code into : start_tag|tag_content|end_tag.
# start_tag -> "<DIV>"
# end_tag -> "</DIV>"

# tag_content could also be separated into : text1|cdata|text2.
# text1 -> ">>  ![cdata[]] "
# cdata -> "<![CDATA[<div>]>]]>", where the CDATA_CONTENT is "<div>]>"
# text2 -> "]]>>]"

# The reason why start_tag is NOT "<DIV>>>" is because of the rule 6.
# The reason why cdata is NOT "<![CDATA[<div>]>]]>]]>" is because of the rule 7.

# Invalid Code Examples:
# Input: "<A>  <B> </A>   </B>"
# Output: False
# Explanation: Unbalanced. If "<A>" is closed, then "<B>" must be unmatched, and vice versa.

# Input: "<DIV>  div tag is not closed  <DIV>"
# Output: False

# Input: "<DIV>  unmatched <  </DIV>"
# Output: False

# Input: "<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"
# Output: False

# Input: "<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>"
# Output: False

# Input: "<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>"
# Output: False

# Note:
# For simplicity, you could assume the input code (including the any characters mentioned above)
# only contain letters, digits, '<','>','/','!','[',']' and ' '.

import re

class TagValidator:

    def doit2(self, code):
        """
        :type code: str
        :rtype: bool
        """
        if code == 't':
            return False

        code = re.sub(r'<!\[CDATA\[.*?\]\]>', 'c', code)
        prev = None

        while code != prev:
            prev = code
            code = re.sub(r'<([A-Z]{1,9})>[^<]*</\1>', 't', code)

        return code == 't'


    def doit1(self, code):
        """
        :type code: str
        :rtype: bool
        """
        code = re.sub(r'<!\[CDATA\[.*?\]\]>|t', '-', code)
        prev = None
        while code != prev:
            prev = code
            code = re.sub(r'<([A-Z]{1,9})>[^<]*</\1>', 't', code)

        return code == 't'


    def doit(self, code):
        """
        :type code: str
        :rtype: bool
        """

        pattern = re.compile(r"<!\[CDATA\[.*?\]\]>")
        pattern1 = re.compile(r"^<([A-Z]{1,9})>(.*?)</\1>$")
        pattern2 = re.compile(r"<(/?[A-Z]{1,9})>")

        mres = pattern1.findall(code)

        if not len(mres):
            return False;

        code = pattern.sub(r'', code)
        mres = pattern1.findall(code)

        print(mres)
        code = mres[0][1];
        mres = pattern2.findall(code)

        print(mres)
        value_list = []

        for i in mres:
            if i[0] == '/':
                if not value_list or value_list[-1] != i[1:]:
                    return False
                del value_list[-1]
            else:
                value_list.append(i)

        code = pattern2.sub(r'', code)
        print(code)
        if '<' in code or len(value_list):
            return False

        return True

# ###########################
import string


class Token:
    pass


class NodeToken(Token):
    def __init__(self, name):
        self.name = name


class OpenNodeToken(NodeToken):
    def __repr__(self):
        return '(OPEN=%s)' % self.name


class CloseNodeToken(NodeToken):
    def __repr__(self):
        return '(CLOSE=%s)' % self.name


class TextToken(Token):
    def __init__(self, value):
        self.value = value

    def __repr__(self):
        return "(TEXT=%s)" % self.value


class CDataToken(Token):
    def __init__(self, content):
        self.content = content

    def __repr__(self):
        return '(CDATA=%s)' % self.content


def find_tag_end_index(tag):
    if len(tag) < 3:
        raise ValueError('tag too short')

    is_closing_tag = tag[1] == '/'

    if tag[0] != '<':
        raise ValueError('tag does not start with correct character')

    end_bracket_index = tag.find('>')

    if end_bracket_index == -1:
        raise ValueError('tag does not end with correct character')

    name = tag[2:end_bracket_index] if is_closing_tag else tag[1:end_bracket_index]

    if len(name) < 1 or len(name) > 9:
        raise ValueError('tag name too long or too short')

    if not all(ch in string.ascii_uppercase for ch in name):
        raise ValueError('invalid character in tag name')

    return len(name) + 2 if is_closing_tag else len(name) + 1


def find_cdata_end_index(cdata):
    end_string = ']]>'
    end_start = cdata.find(end_string)

    if end_start == -1:
        raise ValueError('cdata end not found')

    return end_start + len(end_string) - 1


def get_tag_info(tag):
    is_closing = tag[1] == '/'
    name = tag[2:-1] if is_closing else tag[1:-1]
    return name, is_closing


def get_next_chunk_tag_token(code):
    end_index = find_tag_end_index(code)

    tag = code[:end_index + 1]
    tag_name, is_closing = get_tag_info(tag)

    if is_closing:
        return CloseNodeToken(tag_name), end_index + 1
    else:
        return OpenNodeToken(tag_name), end_index + 1


def get_next_chunk_text_token(code):
    text = ''
    for ch in code:
        if ch == '<':
            break

        text += ch

    return TextToken(text), len(text)


def get_next_chunk_cdata_token(code):
    end_index = find_cdata_end_index(code)
    content = code[:end_index + 1]
    return CDataToken(content), end_index + 1


def get_next_chunk_token(code):
    if code.startswith('<![CDATA['):
        return get_next_chunk_cdata_token(code)
    elif code[0] == '<':
        return get_next_chunk_tag_token(code)
    else:
        return get_next_chunk_text_token(code)


class Solution:

    def isValid(self, code):
        """
        :type code: str
        :rtype: bool
        """
        tokens = []

        remaining_code = code
        try:
            while remaining_code:
                token, next_index = get_next_chunk_token(remaining_code)
                tokens.append(token)
                remaining_code = remaining_code[next_index:]
        except ValueError as e:
            print(e)
            return False
        finally:
            print(tokens)

        # need opening and closing tag minimum
        if len(tokens) < 2:
            print('not enough tokens')
            return False

        if not isinstance(tokens[0], OpenNodeToken) or not isinstance(tokens[-1], CloseNodeToken):
            print('does not start with open and end with close tag')
            return False

        if tokens[0].name != tokens[-1].name:
            print('root opening and closing nodes do not match')
            return False

        unresolved_open_tokens = []
        for token in tokens:
            if isinstance(token, OpenNodeToken):
                unresolved_open_tokens.append(token)
            elif isinstance(token, CloseNodeToken):
                if not unresolved_open_tokens:
                    print('close tag without open tag')
                    return False
                if unresolved_open_tokens[-1].name != token.name:
                    print('closing tag does not match opening tag')
                    return False

                unresolved_open_tokens.pop()

        if unresolved_open_tokens:
            print('tag is not closed: %s' % unresolved_open_token)
            return False

        return True


class MySolution:
    def isvalid(self, code):
        """
        :type code: str
        :rtype: bool
        """
        def parseTag(src, i):
            j = i
            tag, i = findtag(src, i)
            if not tag:
                return False, j

            res, i = parseContent(src, i)

            e = i + len(tag) + 3
            return (True, e) if src[i: e] == '</' + tag + '>' else (False, j)

        def parseContent(src, i):
            j, res = i, False
            while i < len(src):
                res, i = parseText(src, i)
                if res:
                    continue

                res, i = parseCDData(src, i)
                if  res:
                    continue

                res, i = parseTag(src, i)
                if res:
                    continue

                break

            return True, i

        def parseCDData(src, i):

            s = src.find('<![CDATA[', i)
            if s != i:
                return False, i

            e = src.find(']]>', i)

            return (True, e+3) if e != -1 else (False, i)

        def parseText(src, i):
            j = i
            while i < len(src) and src[i] != '<':
                i += 1

            return j != i, i

        def findtag(src, i):
            if src[i] != '<':
                return "", i

            e = src.find('>', i+1)

            if e == -1 or e - i - 1 > 9 or e - i - 1 < 1:
                return "", e

            s = 1
            while s < e - i and src[i+s].isupper():
                s += 1

            return (src[i+1: e], e+1) if s >= e - i else ("", e)

        # start to check
        return parseTag(code, 0) == (True, len(code))


if __name__ == "__main__":

    res = MySolution().isvalid("<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>")

    res = MySolution().isvalid("<DIV>This is the first line <![CDATA[<div>]]></DIV>")

    # False
    res = MySolution().isvalid("<A>  <B> </A>   </B>")

    res = MySolution().isvalid("<DIV>  div tag is not closed  <DIV>")

    res = MySolution().isvalid("<DIV>  unmatched <  </DIV>")

    res = MySolution().isvalid("<DIV> closed tags with invalid tag name  <b>123</b> </DIV>")

    res = MySolution().isvalid("<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>")

    res = MySolution().isvalid("<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>")

    pass

        



