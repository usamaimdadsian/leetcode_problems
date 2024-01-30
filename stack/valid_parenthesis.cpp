#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.
    Every close bracket has a corresponding open bracket of the same type.
*/

bool is_valid_v1(string s) {
  vector<char> stack;
  unordered_map<char, char> m = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
  for (char ts : s) {
    char last_char;
    if (stack.size() > 0) {
      last_char = stack[stack.size() - 1];
      // cout << "\n last stack char: " << last_char << " current char: " << ts
      // << endl;
      // cout << m.find(ts)->first << "HELLO" << m.find(ts)->second << endl;
      if (m[last_char] == ts)
        stack.pop_back();
      else if (m.find(ts) == m.end())
        return false;
      else
        stack.push_back(ts);
    } else
      stack.push_back(ts);
  }

  return (stack.size() > 0 ? false : true);
}

bool is_valid_v2(string s) {
  stack<char> st;
  unordered_map<char, char> map = {{'(', ')'}, {'{', '}'}, {'[', ']'}};
  for (char c : s) {
    if (c == '(' || c == '{' || c == '[') {
      st.push(c);
    } else {
      if (st.empty() || (c != map[st.top()])) {
        return false;
      }
      st.pop();
    }
  }
  return st.empty();
}

void test(string s) {
  cout << "is_valid_v1" << s << ": " << is_valid_v1(s) << endl;
  cout << "is_valid_v2" << s << ": " << is_valid_v2(s) << endl;
}

int main() {
  string s1 = "()[]{}";
  test(s1);

  string s2 = "()";
  test(s2);

  string s3 = "}()";
  test(s3);

  string s4 = "({})";
  test(s4);
}
