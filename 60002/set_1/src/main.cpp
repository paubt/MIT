#include "PartA/PartA.h"
#include <iostream>
#include <chrono>

using namespace std::chrono;

int main(int argc, char const *argv[])
{
    auto cows = load_cows("../data/ps1_cow_data.txt");
    //for (auto& p: cows) std::cout << p.first << " => " << p.second << '\n';
    time_point<steady_clock> last = steady_clock::now();
    auto g = greedy_cow_transport(cows, 12 );
    auto t = duration_cast<milliseconds>( steady_clock::now() - last ).count();
    std::cout << "greedy needs " << g.size() << " spaceships" << std::endl;
    std::cout << "time needed: " << t << std::endl;
    int spaceship_counter = 1;
    for (auto s: g)
    {
        std::cout << "spaceship nr " << spaceship_counter++ << "  =  ";
        for (auto p: s)
            std::cout << "[" << p << "] ";
        std::cout << '\n';
    }
    last = steady_clock::now();
    auto ss = brute_force_cow_transport(cows, 12);
    t = duration_cast<milliseconds>( steady_clock::now() - last ).count();
    std::cout << "\nbrute force needs " << ss.size() << " spaceships" << std::endl;
    std::cout << "time needed: " << t << std::endl;
    spaceship_counter = 1;
    for (auto s: ss)
    {
        std::cout << "spaceship nr " << spaceship_counter++ << "  =  ";
        for (auto p: s)
            std::cout << "[" << p << "] ";
        std::cout << '\n';
    }

        return 0;
}
