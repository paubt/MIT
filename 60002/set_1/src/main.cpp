#include "PartA/PartA.h"
#include <iostream>


int main(int argc, char const *argv[])
{
    auto cows = load_cows("data/ps1_cow_data.txt");
    //for (auto& p: cows) std::cout << p.first << " => " << p.second << '\n';
    auto g = greedy_cow_transport(cows, 20 );
    return 0;
}
