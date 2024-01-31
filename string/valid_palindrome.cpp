#include <cctype>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

/*A phrase is a palindrome if, after converting all uppercase letters into
lowercase letters and removing all non-alphanumeric characters, it reads the
same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.*/

bool isPalindrome_v1(string s) {
  string ns = "";
  for (char t : s) {
    if (isalnum(t) && t != ':' && t != ' ')
      ns += tolower(t);
  }

  if (ns.size() < 2)
    return true;

  bool flag = false;
  int right = ns.size() - 1;
  int left = 0;

  while (right > left) {
    if (ns[left] != ns[right])
      return false;

    left++;
    right--;
  }

  return true;
}

// FASTEST AND MEOMORY EFFICIENT
bool isPalindrome_v2(string s) {
  if (s.size() < 2)
    return true;

  bool flag = false;
  int right = s.size() - 1;
  int left = 0;

  while (right > left) {
    if (!isalnum(s[left])) {
      left++;
      continue;
    }
    if (!isalnum(s[right])) {
      right--;
      continue;
    }

    if (tolower(s[left]) != tolower(s[right]))
      return false;

    left++;
    right--;
  }

  return true;
}

// SOWEST ALGO
bool isPalindrome_v3(string s) {
  regex pattern("[^a-zA-Z0-9]");

  s = regex_replace(s, pattern, "");
  transform(s.begin(), s.end(), s.begin(), ::tolower);

  int len = s.length();
  int left = 0;
  int right = len - 1;

  while (left < right) {
    if (s[left] != s[right]) {
      return false;
    }
    ++left;
    --right;
  }

  return true;
}
void test(string s, bool (*func)(string s)) {
  cout << "INPUT: " << s << " => Result: ";
  cout << func(s) << endl;
}

int main() {
  string s1 = "A man, a plan, a canal: Panama";
  test(s1, isPalindrome_v1);
  test(s1, isPalindrome_v2);
  test(s1, isPalindrome_v3);

  string s2 = "race a car";
  test(s2, isPalindrome_v1);
  test(s2, isPalindrome_v2);
  test(s2, isPalindrome_v3);

  string s3 = " ";
  test(s3, isPalindrome_v1);
  test(s3, isPalindrome_v2);
  test(s3, isPalindrome_v3);

  string s4 = ".,";
  test(s4, isPalindrome_v1);
  test(s4, isPalindrome_v2);
  test(s4, isPalindrome_v3);

  return 0;
}
