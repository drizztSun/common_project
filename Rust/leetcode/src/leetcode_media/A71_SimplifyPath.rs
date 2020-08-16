/*

71. Simplify Path
Medium

Add to List

Share
Given an absolute path for a file (Unix-style), simplify it. Or in other words, convert it to the canonical path.

In a UNIX-style file system, a period . refers to the current directory. Furthermore, a double period .. moves the directory up a level.
For more information, see: Absolute path vs relative path in Linux/Unix

Note that the returned canonical path must always begin with a slash /, and there must be only a single slash / between two directory names.
The last directory name (if it exists) must not end with a trailing /. Also, the canonical path must be the shortest string representing the absolute path.

 

Example 1:

Input: "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.
Example 2:

Input: "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.
Example 3:

Input: "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.
Example 4:

Input: "/a/./b/../../c/"
Output: "/c"
Example 5:

Input: "/a/../../b/../c//.//"
Output: "/c"
Example 6:

Input: "/a//b////c/d//././/.."
Output: "/a/b/c"
*/

mod simplify_path {

    pub fn doit(path: String) -> String {

        let mut stack = vec![];

        for c in path.split('/') {
            if c == ".." {
                stack.pop();
            } else if c == "." {
                continue;
            } else if !c.is_empty() {
                stack.push(c);
            }
        }

        format!("/{}", stack.join("/"))
    }

    pub fn doit1(path: String) -> String {

        let mut path: Vec<_> = path.split('/').collect();
        let mut i = 0;

        while i < path.len() {
            match path[i] {
                "" | "." | ".." => {
                    if i != 0 && path[i] == ".." {
                        path.remove(i-1);
                        i -= 1;
                    }
                    
                    path.remove(i);
                    i -= 1;
                },
                _ => {}
            }
            
            i += 1;
        }
        
        format!("/{}", path.join("/"))
    }
}

pub fn test_71_simplify_path() {

    let _res1 = simplify_path::doit("/home/".to_string());

    let _res2 = simplify_path::doit("/../".to_string());

    let _res3 = simplify_path::doit("/home//foo/".to_string());

    let _res4 = simplify_path::doit("/a/./b/../../c/".to_string());
}