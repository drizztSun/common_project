
namespace linkedlist{

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* reverse(ListNode* cur) {

    if (cur == nullptr) return nullptr;

    ListNode *prev = nullptr;

    while (cur) {
        ListNode *curnext = cur->next;
        cur->next = prev;
        prev = cur;
        cur = curnext;
    }

    return prev;
}


}

    