#include "PartA.h"

std::unordered_map<std::string, int> load_cows(std::string filename)
{
  std::unordered_map<std::string, int> d;
  std::fstream input;
  // open the file for read
  input.open(filename, std::ios::in);
  // check if open
  if (input.is_open())
  {
    // iterate over lines
    std::string tp;
    while(getline(input, tp))
    {
      std::stringstream str_strm(tp);
      std::string s;
      std::string name;
      int weight = 0;
      // iterate in the line over the comma separated values
      // and store them first in name and after that in weight
      while (getline(str_strm, s, ','))
      {
        if (name.empty())
        {
          name = s;
        }
        else
        {
          weight = std::stoi(s);
        }
      }
      d.insert({name, weight});
    }
  }
  return d;
}



std::vector<std::vector<std::string>> greedy_cow_transport(
  const std::unordered_map<std::string, int> &cows,const int limit)
{
  std::unordered_map<std::string, int> c = cows;
  std::vector<std::vector<std::string>> spaceships;
  // repeate until all cows are assigned to a spaceship
  while (!c.empty())
  {
    // find largest in remaining cow as key value
    // set start top as the first
    std::string top_key = c.begin()->first;
    for (auto iter = c.begin(); iter != c.end(); ++iter)
    {
      if (iter->second > c.at(top_key))
      {
        top_key = iter->first;
      }
    }
    // search in the existing spaceships if there is space for the cow
    bool continueMe = false;
    for (std::vector<std::string> &iter: spaceships)
    {
      // calc the total weight of the spaceship
      int s = 0;
      for (auto sc: iter)
      {
        s += cows.at(sc);
      }
      // check if the cow would fit into this spaceship
      // if to add it to the spaceship (push on the vector)
      //    delete from the map of cows that are still not assigned
      //    set continueMe to true so we skip the part later where we add a spaceship
      if (s + c.at(top_key) <= limit)
      {
        /*
        std::cout << "insert "  << top_key << " into :"<< '\n';
        std::for_each(iter.rbegin(),
                      iter.rend(),
                      [](const auto & element){
                        std::cout << element << '\n';
                      });
        */
        iter.push_back(top_key);
        c.erase(top_key);
        continueMe = true;
        break;
      }
    }
    // if we assigned it already continue with next cow
    if (continueMe)
      continue;
    // add a new spaceship with the current cow as its first passenger
    // erase the cow from the map
    std::vector<std::string> ns;
    ns.push_back(top_key);
    c.erase(top_key);
    spaceships.push_back(ns);

  }
  return spaceships;
}


std::vector<std::vector<std::string>>
brute_force_cow_transport(const std::unordered_map<std::string, int> &cows, int limit)
{
    // transform map of cows to vector
    std::vector<std::tuple<std::string, int>> c;
    for (auto it: cows)
    {
        c.emplace_back(it);
    }
    // the number of spaceships for the solution , start with 1 and increment until found
    int spaceship_counter = 0;
    do {
        // create the initial spaceship_config which is empty and push it on the queue
        SpaceShipConfig init = {std::vector<std::tuple<std::vector<std::string>, int>>(++spaceship_counter),
                                c,
                                0};
        std::queue<SpaceShipConfig> open_spaceships;
        open_spaceships.push(init);
        // breath-first-search expand
        while (!open_spaceships.empty())
        {
            // pop next spaceship config to expand
            auto ssc = open_spaceships.front();
            open_spaceships.pop();
            // pop the cow to assign
            if (ssc.open_cows.empty())
            {
                std::vector<std::vector<std::string>> r;
                for (auto s: ssc.spaceships)
                {
                    r.push_back(std::get<0>(s));
                }
                return r;
            }
            auto next_cow = ssc.open_cows[0];
            ssc.open_cows.erase(ssc.open_cows.begin());
            // try to add the new cow to each spaceship and if so create a new spaceship config
            // and push it to the open queue
            // else aka its to heavy... skip the add, effectively excluding from future expansion
            for (int i = 0; i < spaceship_counter; i++)
            {
                if ((std::get<1>(ssc.spaceships[i]) + std::get<1>(next_cow)) <= limit)
                {
                    auto ssa = ssc;
                    std::get<0>(ssa.spaceships[i]).push_back(std::get<0>(next_cow));
                    std::get<1>(ssa.spaceships[i]) += std::get<1>(next_cow);
                    open_spaceships.push(ssa);
                }
            }
        }
    } while (true);

    return {};
}

bool test_cow_transport(int limit) {
    using namespace std::chrono;

    auto cows = load_cows("../data/ps1_cow_data.txt");
    //for (auto& p: cows) std::cout << p.first << " => " << p.second << '\n';
    time_point<steady_clock> last = steady_clock::now();
    auto g = greedy_cow_transport(cows, 10);
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
    auto ss = brute_force_cow_transport(cows, 10);
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

    return true;
}
