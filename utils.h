
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_set>

std::vector<int> split(std::string str, char delim);

void printSet(std::unordered_set<int> set);

void printVector(std::vector<int> vec);

std::string vecToStr(std::vector<int> vec);

#endif