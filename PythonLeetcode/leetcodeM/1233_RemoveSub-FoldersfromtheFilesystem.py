# 1233. Remove Sub-Folders from the Filesystem

# Given a list of folders, remove all sub-folders in those folders and return in any order the folders after removing.

# If a folder[i] is located within another folder[j], it is called a sub-folder of it.

# The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters.
# For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.


# Example 1:

# Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
# Output: ["/a","/c/d","/c/f"]
# Explanation: Folders "/a/b/" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.

# Example 2:

# Input: folder = ["/a","/a/b/c","/a/b/d"]
# Output: ["/a"]
# Explanation: Folders "/a/b/c" and "/a/b/d/" will be removed because they are subfolders of "/a".

# Example 3:

# Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
# Output: ["/a/b/c","/a/b/ca","/a/b/d"]


# Constraints:

# 1 <= folder.length <= 4 * 10^4
# 2 <= folder[i].length <= 100
# folder[i] contains only lowercase letters and '/'
# folder[i] always starts with character '/'
# Each folder name is unique.

class RemoveSubfolders:

    def doit(self, folder):

        folder.sort(key=lambda x: x.count('/'))
        ans = set()

        for c in folder:
            group = c.split('/')
            parentfolder = ''
            existed = False
            for s in group[1:]:
                parentfolder += '/' + s
                if parentfolder in ans:
                    existed = True
                    break

            if not existed:
                ans.add(c)

        return list(ans)

    def doit(self, folder):

        def IsSubfolder(path, direct):
            return path.startswith(direct) and len(path.split('/')) > len(direct.split('/'))

        ans = []
        folder.sort()
        for c in folder:
            if not ans or not IsSubfolder(c, ans[-1]):
                ans.append(c)

        return ans

    def doit_hashtable(self, folder: List[str]) -> List[str]:
        ans  = []
        folder.sort()
        for f in folder:
            if not ans or not f.startswith(ans[-1]+ "/"):
                ans.append(f)
        return ans


if __name__ == '__main__':

    res = RemoveSubfolders().doit(
        folder=["/a", "/a/b", "/c/d", "/c/d/e", "/c/f"])  # ["/a","/c/d","/c/f"]

    res = RemoveSubfolders().doit(folder=["/a", "/a/b/c", "/a/b/d"])  # ["/a"]

    # ["/a/b/c","/a/b/ca","/a/b/d"]
    res = RemoveSubfolders().doit(folder=["/a/b/c", "/a/b/ca", "/a/b/d"])

    pass
