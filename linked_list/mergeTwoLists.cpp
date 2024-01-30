#include <iostream>
#include <vector>

using namespace std;

/*You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists into one sorted list. The list should be made by splicing
together the nodes of the first two lists.

Return the head of the merged linked list.*/

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *mergeTwoLists_v1(ListNode *list1, ListNode *list2) {
  ListNode *root = nullptr;
  ListNode *curr_node = nullptr;
  while (list1 != nullptr && list2 != nullptr) {
    if (root == nullptr) {
      if (list1->val < list2->val) {
        root = list1;
        list1 = list1->next;
      } else {
        root = list2;
        list2 = list2->next;
      }
      curr_node = root;
      continue;
    }

    if (list1->val < list2->val) {
      curr_node->next = list1;
      list1 = list1->next;
    } else {
      curr_node->next = list2;
      list2 = list2->next;
    }
    curr_node = curr_node->next;
  }
  if (curr_node != nullptr)
    curr_node->next = (list1 == nullptr) ? list2 : list1;

  if (root == nullptr) {
    if (list1 != nullptr)
      root = list1;
    else
      root = list2;
  }
  return root;
}

void insertNode(ListNode *&new_node, ListNode *&prev_node,
                ListNode *&curr_node) {
  prev_node->next = new_node;
  prev_node = new_node;

  new_node = new_node->next;
  prev_node->next = curr_node;
}

ListNode *mergeTwoLists_v2(ListNode *list1, ListNode *list2) {
  ListNode *list3;
  ListNode *list_node = list2;

  if (!list1) {
    return list2;
  }

  if (!list2) {
    return list1;
  }

  if (list1->val < list2->val) {
    list3 = list1;
    list_node = list2;
  } else {
    list3 = list2;
    list_node = list1;
  }

  ListNode *prev_node = list3;
  ListNode *curr_node = prev_node->next;

  while (list_node) {
    if (curr_node) {
      if (list_node->val < curr_node->val) {
        insertNode(list_node, prev_node, curr_node);
      } else if (list_node->val == curr_node->val) {
        prev_node = curr_node;
        curr_node = curr_node->next;

        insertNode(list_node, prev_node, curr_node);
      } else {
        prev_node = curr_node;
        curr_node = curr_node->next;
      }
    } else {
      prev_node->next = list_node;
      break;
    }
  }
  return list3;
}

ListNode *mergeTwoLists_v3(ListNode *list1, ListNode *list2) {
  ListNode *small_node, *big_node;
  // Base case if any of two lists is null they return the other list as answer
  if (!list1) {
    return list2;
  }

  if (!list2) {
    return list1;
  }

  cout << "list1: " << list1->val << " list2: " << list2->val << endl;
  /*
      1. If either of the list1 or lis2 is null return the other one.
      2. detect small and big node from the two of them
      3. send next of small node and big node to the function again
      4. Attach the return of the function to the next of small node
      5. return small node
  */

  //

  /*
      Input: 5     1->2->4
      output: 1->2->4->5

      2. s 1, b 5 - s 2, b 5 - s 4 b 5
      3. (2,5) - (4,5) - (5, null)

      small ->

  */

  if (list1->val < list2->val) {
    small_node = list1;
    big_node = list2;
  } else {
    small_node = list2;
    big_node = list1;
  }

  small_node->next = mergeTwoLists_v3(big_node, small_node->next);

  return small_node;
}

ListNode *createList(vector<int> arr) {
  ListNode *root = nullptr;
  ListNode *curr_node = nullptr;

  if (!arr.empty()) {
    for (int i = 0; i < arr.size(); i++) {
      if (root == nullptr) {
        root = new ListNode(arr[i]);
        curr_node = root;
        continue;
      }

      curr_node->next = new ListNode(arr[i]);
      curr_node = curr_node->next;
    }
  }

  return root;
}

void printList(ListNode *node) {
  while (node != nullptr) {
    cout << " " << node->val << " ";
    node = node->next;
  }
  cout << endl;
}
void printVector(vector<int> arr) {
  if (!arr.empty())
    for (int i = 0; i < arr.size(); i++)
      cout << " " << arr[i];
}

void test(vector<int> &list1, vector<int> &list2,
          ListNode *(*func)(ListNode *, ListNode *)) {
  ListNode *lst_node1 = createList(list1);
  cout << "list1:";
  printVector(list1);

  ListNode *lst_node2 = createList(list2);
  cout << "  list2:";
  printVector(list2);

  // cout << lst_node1 << " Hello g " << lst_node2 << " whaw whaw? ";

  ListNode *mergedList = func(lst_node1, lst_node2);
  cout << "  Result:";
  printList(mergedList);
}

int main() {

  vector<int> list1 = {1, 2, 4};
  vector<int> list2 = {1, 3, 4};
  test(list1, list2, mergeTwoLists_v1);
  test(list1, list2, mergeTwoLists_v2);
  test(list1, list2, mergeTwoLists_v3);

  vector<int> list3;
  vector<int> list4;
  test(list3, list4, mergeTwoLists_v1);
  test(list3, list4, mergeTwoLists_v2);
  test(list3, list4, mergeTwoLists_v3);

  vector<int> list5;
  vector<int> list6 = {0};
  test(list5, list6, mergeTwoLists_v1);
  test(list5, list6, mergeTwoLists_v2);
  test(list5, list6, mergeTwoLists_v3);

  return 0;
}
