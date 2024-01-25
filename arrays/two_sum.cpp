#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

// https://leetcode.com/problems/two-sum

/* Given an array of integers nums and an integer target, return indices of the
two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not
use the same element twice.
*/

// 48ms 12.5MB leet code
vector<int> two_sum(vector<int> arr, int target) {
  for (int i = 0; i < arr.size() - 1; i++) {
    for (int j = i + 1; j < arr.size(); j++) {
      if (arr[i] + arr[j] == target)
        return vector<int>{i, j};
    }
  }
  return vector<int>{};
}

// 75ms 12.29MB
vector<int> two_sum_v1(vector<int> nums, int target) {
  vector<int> checked_items;
  vector<int> checked_items_indices;

  for (int i = 0; i < nums.size(); i++) {
    for (int j = 0; j < checked_items.size(); j++) {
      if (nums[i] == checked_items[j])
        return vector<int>{i, checked_items_indices[j]};
    }
    int temp = target - nums[i];
    checked_items.push_back(temp);
    checked_items_indices.push_back(i);
  }
  cout << "Nothing found";
  return vector<int>{};
}

// 10ms 13.74MB
vector<int> two_sum_v2(vector<int> nums, int target) {
  map<int, int> num_map = {};
  for (int i = 0; i < nums.size(); i++) {
    int search_ele = target - nums[i];
    if (num_map.find(search_ele) != num_map.end()) {
      return vector<int>{i, num_map[search_ele]};
    }
    num_map[nums[i]] = i;
  }
  return vector<int>{};
}

// 8ms 14.14Mb
vector<int> two_sum_v3(vector<int> nums, int target) {
  unordered_map<int, int> num_map = {};
  for (int i = 0; i < nums.size(); i++) {
    int search_ele = target - nums[i];
    if (num_map.find(search_ele) != num_map.end()) {
      return vector<int>{i, num_map[search_ele]};
    }
    num_map[nums[i]] = i;
  }
  return vector<int>{};
}

// 8ms 14.14MB
vector<int> two_sum_v4(vector<int> arr, int target) {
  unordered_map<int, int> m;
  int a, b;
  int n = arr.size();
  for (int i = 0; i < n; i++) {
    if (m.find(target - arr[i]) != m.end()) {
      a = (m[target - arr[i]]);
      b = i;
      break;
    }
    m.insert({arr[i], i});
  }
  arr.clear();
  arr.push_back(a);
  arr.push_back(b);
  return arr;
}

void test(vector<int> arr, int target) {
  // vector<int> indices = two_sum(arr, target);
  // vector<int> indices = two_sum_v1(arr, target);
  // vector<int> indices = two_sum_v2(arr, target);
  // vector<int> indices = two_sum_v3(arr, target);
  vector<int> indices = two_sum_v4(arr, target);

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
