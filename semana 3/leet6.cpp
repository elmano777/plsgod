struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *middleNode(ListNode *head) {
    ListNode *cal = head;
    int size = 0;
    while (cal) {
      size++;
      cal = cal->next;
    }
    if (size % 2 == 0) {
      int steps = size / 2;
      for (int i = 0; i < steps; i++) {
        head = head->next;
      }
    }
    if (size % 2 == 1) {
      int steps = (size + 1) / 2;
      for (int i = 0; i < steps; i++) {
        head = head->next;
      }
    }
    return head;
  }
};
