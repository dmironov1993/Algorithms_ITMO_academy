// https://codeforces.com/edu/course/2/lesson/2/3/practice/contest/269118/problem/A
// Implement the algorithm that was discussed in the lecture
// Given a string t and n queries, each query is a string s_t. For each request you need to determine 
// whether the string s_i occurs as a substring in t.

// Input:
//  The first line of input contains the string t (1 <= |t| <= 300 000)
//  The second line contains as integer n, the number of queries (1 <= n <= 300 000). 
//  The following n lines contain one non-empty line s_i each. 
//  The sum of the lengths of all strings s_t does not exceed 300 000
//  All strings consist of lowercase English letters

// Output
// For each request print "Yes". If the string s_i occurs in t, and "No" otherwise

// Example:
//  Input:
//   ababba
//   3
//   ba
//   baba
//   abba

//  Output:
//  Yes
//  No
//  Yes



#include <iostream>
#include <algorithm>
#include <string>
#include <vector>


int binSearch(const std::string &s, const std::vector<int> &suffix, const std::string &target)
{
  int left = 0;
  int right = suffix.size() - 1;
  int target_length = target.size();
  while (right >= left)
  {
    int middle = left + (right - left) / 2;
    std::string substring = s.substr(suffix[middle], target_length);
    if (substring == target)
      return true;
    else if (substring < target)
      left = middle + 1; 
    else
      right = middle - 1;
  }
  return false;
}


int main()
{
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string t;
  std::cin >> t;
  t += "$";
  int n = t.size();
  std::vector<int> p(n), c(n);
  {
    std::vector<std::pair<char, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {t[i], i};
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
    {
      if (a[i].first == a[i-1].first)
        c[p[i]] = c[p[i-1]];
      else
        c[p[i]] = c[p[i-1]] + 1;
    }
  }
  int k = 0;
  while ((1 << k) < n)
  {
    std::vector<std::pair<std::pair<int, int>, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
    {
      if (a[i].first == a[i-1].first)
        c[p[i]] = c[p[i-1]];
      else
        c[p[i]] = c[p[i-1]] + 1;
    }
    k++;
  }

  int j;
  std::cin >> j;
  for (int i = 0; i < j; i++)
  {
    std::string s;
    std::cin >> s;
    int ans = binSearch(t, p, s);
    if (ans)
      std::cout << "Yes" << '\n';
    else
      std::cout << "No" << '\n';
  }
  return 0;
}
