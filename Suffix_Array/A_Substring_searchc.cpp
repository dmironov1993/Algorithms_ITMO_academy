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
