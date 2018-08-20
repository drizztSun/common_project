


# 388. Longest Absolute File Path

# Suppose we abstract our file system by a string in the following manner:

# The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

# dir
#    subdir1
#    subdir2
#        file.ext
# The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.

# The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

# dir
#    subdir1
#        file1.ext
#        subsubdir1
#    subdir2
#        subsubdir2
#            file2.ext
# The directory dir contains two sub-directories subdir1 and subdir2.
# subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1.
# subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

# We are interested in finding the longest (number of characters) absolute path to a file within our file system.
# For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext",
# and its length is 32 (not including the double quotes).

# Given a string representing the file system in the above format, return the length of the longest absolute path to file in the abstracted file system.
# If there is no file in the system, return 0.


class lengthLongestPath(object):

    def doit(self, input):
        """
        :type input: str
        :rtype: int
        """
        path = {0:0}
        res, depth = 0, 0

        for lines in input.splitlines():
            
            name = lines.lstrip('\	')
            depth = len(lines) - len(name)

            if '.' in name:
                res = max(res, path[depth] + len(name))
            else:
                path[depth+1] = path[depth] + len(name) + 1

        return res


    def doit1(self, input):
        """
        :type input: str
        :rtype: int
        """
        if input.count('.') == 0:
            return 0

        lenStack, maxV, res = [], 0, 0
        nl, tab = '\n', '\t'
        
        i = input.find(nl, 0)
        f1 = len(input) if i == -1 else i
        lenStack.append(f1)
        maxV += f1
        res = maxV

        while 0 < i < len(input):

            level = 0
            s = i+1
            e = input.find(nl, s)
            
            while input[s] == tab:
                level += 1
                s += 1

            path = input[s:e] if e != -1 else input[s:]

            if path.count('.') == 0:
                if level < len(lenStack):
                    while len(lenStack) > level:
                        maxV -= lenStack.pop()

                lenStack.append(len(path))
                maxV += len(path)

            else:
                res = max(res, maxV + len(lenStack) + len(path))

            i = e

        return res
            
        



if __name__=="__main__":


    res = lengthLongestPath().doit("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext")
    
    res = lengthLongestPath().doit("dir\n    file.txt")

    res = lengthLongestPath().doit("file.ext")

    pass