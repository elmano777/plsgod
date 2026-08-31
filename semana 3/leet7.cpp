struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *reverseBetween(ListNode *head, int left, int right) {
    if (!head || !head->next || left == right) {
      return head;
    }

    ListNode dummy(0, head);
    ListNode *prevL = &dummy;

    for (int i = 0; i < left - 1; i++) {
      prevL = prevL->next;
    }

    ListNode *curr = prevL->next;
    ListNode *prev = nullptr;

    for (int i = 0; i < right - left + 1; i++) {
      ListNode *next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }

    prevL->next->next = curr;
    prevL->next = prev;

    return dummy.next;
  }
};
