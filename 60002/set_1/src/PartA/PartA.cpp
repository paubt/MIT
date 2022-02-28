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
  std::cout <<"with this size limit " << spaceships.size() << " are needed"
            << "\nlist of the spaceships with its passengers:\n";
  int spaceship_counter = 1;
  for (auto s: spaceships)
  {
    std::cout << "spaceship nr " << spaceship_counter++ << "  =  ";
    for (auto p: s)
      std::cout << "[" << p << "] ";
    std::cout << '\n';
  }

  return spaceships;
}
