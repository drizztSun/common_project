"""
677. Map Sum Pairs

Implement the MapSum class:

MapSum() Initializes the MapSum object.
void insert(String key, int val) Inserts the key-val pair into the map.
If the key already existed, the original key-value pair will be overridden to the new one.
int sum(string prefix) Returns the sum of all the pairs' value whose key starts with the prefix.


Example 1:

Input
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
Output
[null, null, 3, null, 5]

Explanation
MapSum mapSum = new MapSum();
mapSum.insert("apple", 3);
mapSum.sum("ap");           // return 3 (apple = 3)
mapSum.insert("app", 2);
mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)


Constraints:

1 <= key.length, prefix.length <= 50
key and prefix consist of only lowercase English letters.
1 <= val <= 1000
At most 50 calls will be made to insert and sum.
"""

"""
Approach #3: Trie [Accepted]
Intuition and Algorithm

Since we are dealing with prefixes, a Trie (prefix tree) is a natural data structure to approach this problem. 
For every node of the trie corresponding to some prefix, we will remember the desired answer (score) and store it at this node. 
As in Approach #2, this involves modifying each node by delta = val - map[key].


Complexity Analysis

Time Complexity: Every insert operation is O(K)O(K), where KK is the length of the key. Every sum operation is O(K)O(K).

Space Complexity: The space used is linear in the size of the total input.
"""


class MapSum:

    class TrieNode(object):
        __slots__ = 'children', 'score'

        def __init__(self):
            self.score = 0
            self.children = {}

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.map = {}
        self._roottrie = MapSum.TrieNode()

    def insert(self, key: str, val: int) -> None:

        delta = val - self.map.get(key, 0)
        self.map[key] = val
        node = self._roottrie
        node.score += delta
        for c in key:
            node = node.children.setdefault(c, MapSum.TrieNode())
            node.score += delta

    def sum(self, prefix: str) -> int:
        node = self._roottrie
        for c in prefix:
            if c not in node.children:
                return 0
            node = node.children[c]
        return node.score

