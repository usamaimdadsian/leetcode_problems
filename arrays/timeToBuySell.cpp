#include <iostream>
#include <vector>
using namespace std;

/*You are given an array prices where prices[i] is the price of a given stock on
the ith day.

You want to maximize your profit by choosing a single day to buy one stock and
choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot
achieve any profit, return 0.*/

// FAILS AT LARGE INPUT
int maxProfit_v1(vector<int> &prices) {
  vector<int> check_vec;
  int profit = 0;
  for (int p : prices) {
    for (int past_el : check_vec) {
      if ((p - past_el) > profit)
        profit = p - past_el;
    }
    check_vec.push_back(p);
  }
  return profit;
}

int maxProfit_v2(vector<int> &prices) {
  int profit = 0;
  int min = 99999999;
  for (int p : prices) {
    if (p < min)
      min = p;
    if ((p - min) > profit)
      profit = p - min;
  }
  return profit;
}

int maxProfit_v3(vector<int> &prices) {
  int left = 0;
  int right = 1;
  int max_profit = 0;
  int currentProfit;

  while (right < prices.size()) {
    currentProfit = prices[right] - prices[left];
    if (prices[left] < prices[right])
      max_profit = max(currentProfit, max_profit);
    else
      left = right;
    right += 1;
  }
  return max_profit;
}

void test(vector<int> &prices, int (*func)(vector<int> &p)) {
  cout << "Prices:";
  for (int p : prices) {
    cout << " " << p;
  }
  cout << " => Result: ";
  cout << func(prices) << endl;
}

int main() {
  vector<int> p1 = {7, 1, 5, 3, 6, 4};
  test(p1, maxProfit_v1);
  test(p1, maxProfit_v2);
  test(p1, maxProfit_v3);

  vector<int> p2 = {7, 6, 4, 3, 1};
  test(p2, maxProfit_v1);
  test(p2, maxProfit_v2);
  test(p2, maxProfit_v3);

  return 0;
}
