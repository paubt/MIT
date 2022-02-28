
#ifndef PARTA_H
#define PARTA_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


std::unordered_map<std::string, int> load_cows(std::string filename);

std::vector<std::vector<std::string>> greedy_cow_transport(
  const std::unordered_map<std::string, int> &cows, int limit);


#endif // PARTA_H
