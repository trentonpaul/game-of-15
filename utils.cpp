
#include "utils.h"

using namespace std;
vector<int> split(string str, char delim)
{
    stringstream ss(str);
    vector<int> res;
    string token;
    while (getline(ss, token, delim)) {
        res.push_back(stoi(token));
    }
    return res;
}

void printSet(unordered_set<int> set)
{
  int index = 0;
  for (int i: set) {
    if (index == 0)
      cout << "{";
    if (index == set.size()-1)
      cout << i << "}";
    else
      cout << i << ", ";
    index++;
  }
}

void printVector(vector<int> vec)
{
  int index = 0;
  for (int i: vec) {
    if (index == 0)
      cout << "(";
    if (index == vec.size()-1)
      cout << i << ")";
    else
      cout << i << ", ";
    index++;
  }
}

string vecToStr(vector<int> vec)
{
  string res = "";
  int index = 0;
  for (int i: vec) {
    if (index == 0)
      res += "(";
    if (index == vec.size()-1)
    {
      res += to_string(i);
      res += ")";
    }
    else
    {
      res += to_string(i);
      res += ", ";
    }
    index++;
  }
  return res;
}