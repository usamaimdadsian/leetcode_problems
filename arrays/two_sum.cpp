#include <iostream>
#include <vector>

using namespace std;

/* Given an array of integers nums and an integer target, return indices of the
two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not
use the same element twice.
*/

vector<int> two_sum(vector<int> arr, int target) {
  for (int i = 0; i < arr.size() - 1; i++) {
    for (int j = i + 1; j < arr.size(); j++) {
      if (arr[i] + arr[j] == target)
        return vector<int>{i, j};
    }
  }
  return vector<int>{};
}

vector<int> two_sum_v1(vector<int> nums, int target) {
  vector<int> checked_items;
  for (int i = 0; i < nums.size(); i++) {
    int temp = target - nums[i];
    for (int j = 0; j < checked_items.size(); j++) {
      if (temp == checked_items[j])
        return vector<int>{i, j};
      checked_items.push_back(nums[i]);
    }
  }
  return vector<int>{};
}

void test(vector<int> arr, int target) {
  // vector<int> indices = two_sum(arr, target);
  vector<int> indices = two_sum_v1(arr, target);

  for (int i : indices) {
    cout << i;
  }
  cout << "\n";
}

int main() {
  vector<int> nums1 = {2, 7, 11, 5};
  int target1 = 9;

  vector<int> nums2 = {3, 2, 4};
  int target2 = 6;

  vector<int> nums3 = {3, 3};
  int target3 = 6;

  test(nums1, target1);
  test(nums2, target2);
  test(nums3, target3);

  return 0;
}
