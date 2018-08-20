import os

# 68. Text Justification


# Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.
# You should pack your words in a greedy approach; that is, pack as many words as you can in each line. 
# Pad extra spaces ' ' when necessary so that each line has exactly L characters.
# Extra spaces between words should be distributed as evenly as possible. 
# If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
# For the last line of text, it should be left justified and no extra space is inserted between words.

# For example,
# words: ["This", "is", "an", "example", "of", "text", "justification."]
# L: 16.


class fullJustify(object):
    def doit1(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """
        def printWords(words, s, length):
            if len(words) == s:
                return []
            
            lineLen, content = 0, []
            for i in range(s, len(words)):               
                if lineLen + len(words[i]) + (i-s)> length:
                    s = i
                    break
                lineLen += len(words[i])
                content.append(words[i])
            else:
                s = len(words)

            result = ""
            if len(content) == 1:
                result = content[0] + " " * (length - len(content[0]))
            else:
                margin = (length - lineLen) // (len(content) - 1)
                remind = (length - lineLen) % (len(content) - 1)
            
                result += content[0]
                for i in range(1, len(content)):
                    marginContent = " " * (margin if remind <= 0 else margin + 1)
                    result +=  marginContent + content[i]
                    remind -= 1
        
            return [result] + printWords(words, s, length)
            
        return printWords(words, 0, maxWidth)


    def doit(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """
        content, i = [], 0
        while i < len(words):
            # make line content
            s, lineLength, tmp = i, -1, []
            while s < len(words) :
                if lineLength + len(words[s]) + 1 > maxWidth:
                    break
                lineLength += len(words[s]) + 1
                tmp.append(words[s])
                s += 1
            content.append(tmp)
            i = s
        
        result = []
        for i, row in enumerate(content):
            rowContent = ''
            if len(row) == 1:
                rowContent = row[0] + " " * (maxWidth - len(row[0]))
            else:
                margin, remind, lineLen = 1, 0, 0
                if i != len(content)-1:
                    for i in row: 
                        lineLen += len(i)
                    margin = (maxWidth - lineLen) // (len(row) - 1)
                    remind = (maxWidth - lineLen) % (len(row) - 1)

                rowContent += row[0]
                for i in range(1, len(row)):
                    marginContent = " " * (margin if remind <= 0 else margin + 1)
                    rowContent +=  marginContent + row[i]
                    remind -= 1

                if len(rowContent) < maxWidth:
                    rowContent += " " * (maxWidth-len(rowContent))

            result.append(rowContent) 
            
            
        return result

    def doit3(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """
        i, N, result = 0, len(words), []

        while i < N:
            oneLine, j, currWidth, positionNum, spaceNum = [words[i]], i + 1, len(words[i]), 0, maxWidth - len(words[i])

            while j < N and currWidth + 1 + len(words[j]) <= maxWidth:
                oneLine.append(words[j])
                currWidth += 1 + len(words[j])
                spaceNum -= len(words[j])
                positionNum, j = positionNum + 1, j + 1

            i = j
            if j < N and positionNum:
                spaces = [' '*(spaceNum/positionNum + (k < spaceNum % positionNum)) for k in range(positionNum)] + ['']
            else:
                spaces = [' '] * positionNum + [' '* (maxWidth - currWidth)]

            result.append(''.join([s for pair in zip(oneLine, spaces) for s in pair]))

        return result



    def doit4(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """
        ans, cur, length = [], [], 0
        for w in words:
            if length + len(w) + len(cur) > maxWidth:    # len(cur) represent at least 1 space between words
                for i in range(maxWidth - length):
                    cur[ i % (len(cur) - 1 or 1)] += ' '
                ans.append(''.join(cur))
                cur, length = [], 0
                
            cur.append(w)
            length += len(w)
            
        return ans + [' '.join(cur).ljust(maxWidth)]



        length = 0
        for w in words:
            
            if length + len(w) + len(cur) > maxWidth:
                for i in range(maxWidth - length):
                    cur[i%(len(cur) - 1 or 1)] += ' '
                ans.append(''.join(cur))
                cur, length = [], 0
            cur.append(w)
            length += len(w)


if __name__=="__main__":

    res = fullJustify().doit([""], 2)
    
    res = fullJustify().doit(["This", "is", "an", "example", "of", "text", "justification."], 16)

    res = fullJustify().doit1(["a","b","c","d","e"], 1)

    res = fullJustify().doit(["What","must","be","shall","be."], 12)


    pass