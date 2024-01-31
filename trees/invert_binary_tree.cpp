#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*Given the root of a binary tree, invert the tree, and return its root.*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

TreeNode *invertTree_v1(TreeNode *root) {
  TreeNode *tempNode;
  TreeNode *currNode;
  queue<TreeNode *> node_queue;

  if (root == nullptr)
    return root;
  node_queue.push(root);

  while (node_queue.size() > 0) {
    currNode = node_queue.front();

    tempNode = currNode->left;
    currNode->left = currNode->right;
    currNode->right = tempNode;

    if (currNode->left != nullptr)
      node_queue.push(currNode->left);
    if (currNode->right != nullptr)
      node_queue.push(currNode->right);

    node_queue.pop();
  }
  return root;
}

// Takes less memory
TreeNode *invertTree_v2(TreeNode *root) {
  TreeNode *tempNode;
  if (root == nullptr) {
    return nullptr;
  }
  tempNode = invertTree_v2(root->left);
  root->left = invertTree_v2(root->right);
  root->right = tempNode;

  return root;
}

TreeNode *invertTree_v3(TreeNode *root) {
  if (root) {
    TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;
    invertTree_v3(root->left);
    invertTree_v3(root->right);
  }
  return root;
}

TreeNode *createTree(vector<int> arr) {
  TreeNode *root = nullptr;
  TreeNode *new_node = nullptr;
  TreeNode *curr_node = nullptr;
  queue<TreeNode *> leave_nodes;

  while (arr.size() > 0) {
    new_node = new TreeNode(arr[0]);
    if (root == nullptr) {
      root = new_node;
      leave_nodes.push(new_node);
      arr = vector<int>(arr.begin() + 1, arr.end());
      continue;
    }
    curr_node = leave_nodes.front();
    if (curr_node->left == nullptr) {
      curr_node->left = new_node;
    } else if (curr_node->right == nullptr) {
      curr_node->right = new_node;
      leave_nodes.pop();
    }
    leave_nodes.push(new_node);
    arr = vector<int>(arr.begin() + 1, arr.end());
  }
  return root;
}

void printTree(TreeNode *root) {
  queue<TreeNode *> node_queue;
  if (root == nullptr)
    return;
  node_queue.push(root);
  while (node_queue.size() > 0) {
    cout << " " << root->val;

    if (root->left != nullptr)
      node_queue.push(root->left);
    if (root->right != nullptr)
      node_queue.push(root->right);

    node_queue.pop();
    root = node_queue.front();
  }
}

void test(vector<int> arr, TreeNode *(*func)(TreeNode *root)) {
  TreeNode *tree = createTree(arr);
  cout << "Tree: ";
  printTree(tree);

  TreeNode *inv_tree = func(tree);
  cout << " =>> Result: ";
  printTree(inv_tree);

  cout << endl;
}

int main() {
  // Output: [4,7,2,9,6,3,1]
  vector<int> t1 = {4, 2, 7, 1, 3, 6, 9};
  test(t1, invertTree_v1);
  test(t1, invertTree_v2);
  test(t1, invertTree_v3);

  // Output: [2,3,1]
  vector<int> t2 = {2, 1, 3};
  test(t2, invertTree_v1);
  test(t2, invertTree_v2);
  test(t2, invertTree_v3);

  // Output: []
  vector<int> t3;
  test(t3, invertTree_v1);
  test(t3, invertTree_v2);
  test(t3, invertTree_v3);

  return 0;
}
