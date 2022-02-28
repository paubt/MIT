
#ifndef PARTA_H
#define PARTA_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

std::unordered_map<std::string, int> load_cows(std::string filename);

std::vector<std::vector<std::string>> greedy_cow_transport(
        const std::unordered_map<std::string, int> &cows, int limit);

// structure to store the spaceships in with the corresponding summed weight and the passenger list
struct SpaceShipConfig {
    std::vector<std::tuple<std::vector<std::string>, int>> spaceships;
    std::vector<std::tuple<std::string, int>> open_cows;
    int const ship_count;
};

std::vector<std::vector<std::string>> brute_force_cow_transport(
        const std::unordered_map<std::string, int> &cows, int limit);


#endif // PARTA_H
