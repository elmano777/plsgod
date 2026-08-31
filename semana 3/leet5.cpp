struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    if (!head) return nullptr;
    int size = 0;
    ListNode *sizeC = head;
    while (sizeC) {
      size++;
      sizeC = sizeC->next;
    }
    if (n == size) {
      ListNode *newHead = head->next;
      delete head;
      return newHead;
    }
    ListNode *prev = head;
    for (int i = 0; i < size - n - 1; i++) {
      prev = prev->next;
    }
    ListNode *toDelete = prev->next;
    prev->next = toDelete->next;
    delete toDelete;
    return head;
  }
};
