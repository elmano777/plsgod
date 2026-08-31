struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *partition(ListNode *head, int x) {
    ListNode lessDummy(0);
    ListNode greaterDummy(0);
    ListNode *lessTail = &lessDummy;
    ListNode *greaterTail = &greaterDummy;
    ListNode *curr = head;
    while (curr) {
      if (curr->val < x) {
        lessTail->next = curr;
        lessTail = curr;
      } else {
        greaterTail->next = curr;
        greaterTail = curr;
      }
      curr = curr->next;
    }
    greaterTail->next = nullptr;
    lessTail->next = greaterDummy.next;
    return lessDummy.next;
  }
};
