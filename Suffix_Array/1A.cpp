// Now try to implement the algorithm that was dicussed in the lecture: 
// https://codeforces.com/edu/course/2/lesson/2

// Write a program that reads the string s and prints the suffix array p for it

// Input:
//  Input contains a single string s of length n (1 <= n <= 100 000). String consists of small english letters.

// Output:
//  Print n + 1 distinct integers, indices of first characters of suffixes of s, ordered in lexicographical order.

// Examples:
//  ababba     ->  6 5 0 2 4 1 3 
//  aaaa       ->  4 3 2 1 0
//  ppppplppp  ->  9 5 8 4 7 3 6 2 1 0
//  nn         ->  2 1 0

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
  std::string s;
  std::cin >> s;
  s += "$";
  int n = s.size();
  std::vector<int> p(n), c(n);
  {
    std::vector<std::pair<char,int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
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
  for (int i = 0; i < n; i++)
    std::cout << p[i] << " ";
  return 0;
}
