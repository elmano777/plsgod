struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *rotateRight(ListNode *head, int k) {
    if (!head || head->next == nullptr || k == 0) {
      return head;
    }
    int len = 1;
    ListNode *tail = head;
    while (tail->next) {
      len++;
      tail = tail->next;
    }
    k %= len;
    if (k == 0) {
      return head;
    }
    tail->next = head;
    ListNode *cur = head;
    for (int i = 0; i < len - k - 1; i++) {
      cur = cur->next;
    }
    ListNode *newHead = cur->next;
    cur->next = nullptr;
    return newHead;
  }
};
