"""
588. Design In-Memory File System


Design an in-memory file system to simulate the following functions:

ls: Given a path in string format. If it is a file path, return a list that only contains this file's name.
If it is a directory path, return the list of file and directory names in this directory.
Your output (file and directory names together) should in lexicographic order.

mkdir: Given a directory path that does not exist, you should make a new directory according to the path.
If the middle directories in the path don't exist either, you should create them as well.
This function has void return type.

addContentToFile: Given a file path and file content in string format.
If the file doesn't exist, you need to create that file containing given content.
If the file already exists, you need to append given content to original content. This function has void return type.

readContentFromFile: Given a file path, return its content in string format.



Example:

Input:
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]

Output:
[null,[],null,null,["a"],"hello"]

Explanation:
filesystem


Note:

You can assume all file or directory paths are absolute paths which begin with / and do not end with / except that the path is just "/".
You can assume that all operations will be passed valid parameters and users will not attempt to retrieve file content or list a directory or file that does not exist.
You can assume that all directory names and file names only contain lower-case letters, and same names won't exist in the same directory.



"""
from collections import defaultdict


Trie = lambda: defaultdict(Trie)


class FileSystem(object):

    def __init__(self):
        self.fs = Trie()
        self.fileinfo = defaultdict(str)

    def ls(self, path):
        if path in self.fileinfo:
            return path.split('/')[-1:]

        cur = self.fs
        for token in path.split('/'):
            if token in cur:
                cur = cur[token]
            elif token:
                return []

        return sorted(cur.keys())

    def mkdir(self, path):
        cur = self.fs
        for token in path.split('/'):
            if token: cur = cur[token]

    def addContentToFile(self, filePath, content):
        if filePath not in self.fileinfo:
            self.mkdir(filePath)
        self.fileinfo[filePath] += content

    def readContentFromFile(self, filePath):
        if filePath not in self.fileinfo:
            return ''
        return self.fileinfo[filePath]




class FileSystemII:

    def __init__(self):

        self._root = {}

    def ls(self, path: str) -> list[str]:

        currentPath = self._findpath(path)
        if not currentPath:
            return []

        if isinstance(currentPath, str):
            file = path.split('/')
            return []

        return sorted(currentPath.keys())

    def mkdir(self, path: str) -> None:
        curretPath = self._root
        paths = path[1:].split('/')
        for i, c in enumerate(paths):
            if c not in curretPath:
                curretPath[c] = {}

            if isinstance(curretPath[c], str):
                return

            curretPath = curretPath[c]

    def _findpath(self, path):

        if not path:
            return None

        if path == '/':
            return self._root

        paths = path[1:].split('/')
        currentPath = self._root

        for i in range(len(paths)-1):
            c = paths[i]
            if c not in currentPath:
                return None

            if isinstance(currentPath[c], str):
                return None

            currentPath = currentPath[c]

        return currentPath

    def addContentToFile(self, filePath: str, content: str) -> None:
        if (c := self._findpath(filePath)) is not None:
            file = filePath.split('/')[-1]
            if file not in c:
                c[file] = ''

            if isinstance(c[file], str):
                c[file] += content

    def readContentFromFile(self, filePath: str) -> str:
        content = ''
        if (c := self._findpath(filePath)) is not None:
            file = filePath.split('/')[-1]
            if isinstance(c[file], str):
                content = c[file]
        return content


if __name__ == '__main__':

    fs = FileSystem()

    res = fs.ls('/')

    fs.mkdir('/a/b/c')

    res = fs.ls('/a/b')

    fs.addContentToFile('/a/b/c/d', 'hello')

    content = fs.readContentFromFile('/a/b/c/d')
