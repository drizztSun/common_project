class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


def addTwoNumbers(l1: ListNode, l2: ListNode):
    res = ListNode()
    node = res
    r = 0
    l1s = True
    l2s = True
    while l1 or l2:
        if not l1:
            l1s = False
        if not l2:
            l2s = False
        node.next = ListNode()
        node = node.next
        r, node.val = divmod(l1.val if l1s else 0 + l2.val if l2s else 0 + r, 10)
        l1 = l1.next if l1s else l1
        l2 = l2.next if l2s else l2
    if r == 1:
        res1 = ListNode(1, res)
        return res1
    return res.next


if __name__ == "__main__":
    a = ListNode(2, ListNode(4, ListNode(3, ListNode(1, ListNode(9)))))

    b = ListNode(5, ListNode(6, ListNode(4, None)))

    print(addTwoNumbers(a, b))
