#include <iostream>
#include <memory>
#include "list_node.h"
using namespace std;

// head, tail
struct range {
  shared_ptr<ListNode<int>> head;
  shared_ptr<ListNode<int>> last;
  shared_ptr<ListNode<int>> tail;
};

range ReverseSublistHelper(shared_ptr<ListNode<int>> head, int start, int finish) {
  if (start > 0) {
    head->next = ReverseSublistHelper(head->next, start - 1, finish).head;
    return {head, nullptr, nullptr};
  }

  if (finish == 0) {
    return {head, head, head->next};
  }

  // otherwise, we have miles to go before we sleep
  // this represents the reverse of the rest of the list, trivially, the 1 element list is already reversed
  auto rest = ReverseSublistHelper(head->next, start, finish - 1);
  // now, we make this list point to our head node, and our head node, point to the element that was pointed to by list
  head->next = rest.tail;
  rest.last->next = head;
  return {rest.head, head, head->next};
}

// using range = pair<shared_ptr<List/Node<int>>, shared_ptr<ListNode<int>>;

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> head, int start,
                                         int finish) {
  return ReverseSublistHelper(head, start, finish).head;
}

// shared_ptr<ListNode<int>>

int test1() {
    auto list = ConvertArrayToLinkedList(vector<int>{1,2,3,4,5});
    auto newList = ReverseSublist(list, 1, 3);
    cout << newList << endl;
}

int main() {

}