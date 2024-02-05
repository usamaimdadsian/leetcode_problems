#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

/*Given two strings s and t, return true if t is an anagram of s, and false
otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different
word or phrase, typically using all the original letters exactly once.
*/

// WORST ALGORITHM
bool isAnagram_v1(string s, string t) {
  if (s.size() != t.size())
    return false;

  vector<char> ts, tt;
  int i = 0;
  while (i < s.size()) {
    if (s[i] != t[i]){
      ts.push_back(s[i]);
      tt.push_back(t[i]);
    }
    i++;
  }

  bool flag;
  while (ts.size()>0){
    flag = false;
    for (int j = 0; j < tt.size(); j++){
      if (ts[0] == tt[j]){
        flag = true;
        ts.erase(ts.begin()+0);
        tt.erase(tt.begin()+j);
        break;
      }
    }
    if (!flag)
      break;
  }
  return flag;
}


bool isAnagram_v2(string s, string t) {
    int count[26] = {0};
    
    // Count the frequency of characters in string s
    for (char x : s) {
        count[x - 'a']++;
    }
    
    // Decrement the frequency of characters in string t
    for (char x : t) {
        count[x - 'a']--;
    }
    
    // Check if any character has non-zero frequency
    for (int val : count) {
        if (val != 0) {
            return false;
        }
    }

    return true;
}

bool isAnagram_v3(string s, string t) {
  sort(s.begin(), s.end());
  sort(t.begin(), t.end());
  return s == t;
}

bool isAnagram_v4(string s, string t) {
  unordered_map<char, int> char_count_s;
  unordered_map<char, int> char_count_t;

  if (s.length() != t.length())
      return false;

  for (int i = 0; i < s.length(); i++)
  {
      char_count_s[s[i]]++;
      char_count_t[t[i]]++;
  }

  for (auto &pair : char_count_s)
  {
      if (pair.second != char_count_t[pair.first])
      {
          return false;
      }
  }

  return true;
}

void test(string s, string t, bool (*func)(string s, string t)) {
  cout << "S: " << s << " T: " << t << " => ";
  cout << func(s, t) << endl;
}

int main() {
  string s1 = "anagram";
  string t1 = "nagaram";
  test(s1, t1, isAnagram_v1);
  test(s1, t1, isAnagram_v2);
  test(s1, t1, isAnagram_v3);
  test(s1, t1, isAnagram_v4);

  string s2 = "rat";
  string t2 = "car";
  test(s2, t2, isAnagram_v1);
  test(s2, t2, isAnagram_v2);
  test(s2, t2, isAnagram_v3);
  test(s2, t2, isAnagram_v4);

  return 0;
}
