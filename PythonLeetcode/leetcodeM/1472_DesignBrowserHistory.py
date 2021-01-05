"""
1472. Design Browser History

You have a browser of one tab where you start on the homepage and you can visit another url, get back in the history number of steps or move forward in the history number of steps.

Implement the BrowserHistory class:

BrowserHistory(string homepage) Initializes the object with the homepage of the browser.
void visit(string url) Visits url from the current page. It clears up all the forward history.
string back(int steps) Move steps back in history. If you can only return x steps in the history and steps > x, you will return only x steps. Return the current url after moving back in history at most steps.
string forward(int steps) Move steps forward in history. If you can only forward x steps in the history and steps > x, you will forward only x steps. Return the current url after forwarding in history at most steps.


Example:

Input:
["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
[["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]
Output:
[null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]

Explanation:
BrowserHistory browserHistory = new BrowserHistory("leetcode.com");
browserHistory.visit("google.com");       // You are in "leetcode.com". Visit "google.com"
browserHistory.visit("facebook.com");     // You are in "google.com". Visit "facebook.com"
browserHistory.visit("youtube.com");      // You are in "facebook.com". Visit "youtube.com"
browserHistory.back(1);                   // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
browserHistory.back(1);                   // You are in "facebook.com", move back to "google.com" return "google.com"
browserHistory.forward(1);                // You are in "google.com", move forward to "facebook.com" return "facebook.com"
browserHistory.visit("linkedin.com");     // You are in "facebook.com". Visit "linkedin.com"
browserHistory.forward(2);                // You are in "linkedin.com", you cannot move forward any steps.
browserHistory.back(2);                   // You are in "linkedin.com", move back two steps to "facebook.com" then to "google.com". return "google.com"
browserHistory.back(7);                   // You are in "google.com", you can move back only one step to "leetcode.com". return "leetcode.com"


Constraints:

1 <= homepage.length <= 20
1 <= url.length <= 20
1 <= steps <= 100
homepage and url consist of  '.' or lower case English letters.
At most 5000 calls will be made to visit, back, and forward.

"""


class BrowserHistory:

    def __init__(self, homepage: str):
        self._url_history = [homepage]
        self._current = 0

    def visit(self, url: str) -> None:
        while self._current != len(self._url_history)-1:
            self._url_history.pop()
        self._url_history.append(url)
        self._current += 1

    def back(self, steps: int) -> str:
        self._current = max(0, self._current - steps)
        return self._url_history[self._current]

    def forward(self, steps: int) -> str:
        self._current = min(len(self._url_history)-1, self._current + steps)
        return self._url_history[self._current]


class ListNode:
    def __init__(self, val):
        self.val = val
        self.prev = None
        self.next = None


class BrowserHistoryII:

    def __init__(self, homepage: str):
        # Two Pointer
        self.idx_to_url = [""] * 5000
        self.p = self.tail = 0
        self.idx_to_url[self.p] = homepage

        # DLL
        # self.root = ListNode(homepage)

    def visit(self, url: str) -> None:
        # Two Pointer
        self.p += 1
        self.idx_to_url[self.p] = url
        self.tail = self.p

        # DLL
        # new_node = ListNode(url)
        # new_node.prev = self.root
        # self.root.next = new_node
        # self.root = self.root.next

    def back(self, steps: int) -> str:
        # Two Pointer
        self.p = max(0, self.p - steps)
        return self.idx_to_url[self.p]

        # DLL
        # while (steps and self.root.prev):
        #     self.root = self.root.prev
        #     steps -= 1
        # return self.root.val

    def forward(self, steps: int) -> str:
        # Two Pointer
        self.p = min(self.tail, self.p + steps)
        return self.idx_to_url[self.p]

        # DLL
        # while (steps and self.root.next):
        #     self.root = self.root.next
        #     steps -= 1
        # return self.root.val


if __name__ == '__main__':

    bh = BrowserHistory("www.leetcode.com")

    bh.visit("www.google.com")
    bh.visit("www.facebook.com")
    bh.visit("www.youtube.com")

    bh.back(1)
    bh.back(1)
    bh.forward(1)

    bh.visit("linkedin.com")
    bh.forward(2)
    bh.back(2)
    bh.back(7)