//
// Created by pau on 1/3/22.
//

#include "PartB.h"

bool test_golden_eggs()
{
    const vector<int> ew = {1,3, 7, 12, 51, 12, 10, 25, 5};
    const int tw = 2323;
    try
    {

        int r = dp_make_weight(ew, tw);
        cout << "for target weight of " << tw << "\nwith input: " << "[";
        for_each(ew.begin(), ew.end()-1, [](const int ele){
            cout << ele << ", " ;
        });
        cout << ew.back() << "]\nsolution is: " << r << endl;
        return true;
    }
    catch (invalid_argument const& em)
    {
        cout << "error: " << em.what() << endl;
        return false;
    }
}

int dp_make_weight(vector<int> egg_weights,int target_weight)
{
    // sort and print array
    std::sort(egg_weights.begin(), egg_weights.end());
    cout << endl;
    assert(!egg_weights.empty());
    // array for last iteration
    vector<tuple<int, int, bool>> last(target_weight);
    vector<tuple<int, int, bool>> next(target_weight);
    // fill last with one's
    // if one is in possible egg weights use it and set bool to true as all are viable
    // solutions
    // else make "artificial support" one start vector with bool <- false to signal
    // this solution is not viable
    {
        bool one_present = false;
        if (egg_weights[0] == 1)
        {
            egg_weights.erase(egg_weights.begin());
            one_present = true;
        }
        int i = 0;
        for (auto& [ele, c, v] : last)
        {
            ele = 1;
            c = ++i;
            v = one_present;
        }
    }
    // do the real loop
    for (auto egg: egg_weights)
    {
        //next.clear();
        int idx = 0;
        for (auto& [ele, c, v] : next)
        {
            // calc previous spot in the matrix (look up in last vector)
            int previous_pos = idx - egg;
            // if this pos is negative this egg doesn't fit in this position
            // thus just copying the entry from the last vector
            if (previous_pos < -1)
            {
                next[idx] = last[idx];
            }
            // if equal zero the plain singular combination is always better (smaller by egg count)
            // thus just add it
            else if (previous_pos == -1)
            {
                ele =  egg;
                c = 1;
                v = true;
            }
            // the normal common case
            else
            {
                // calc new possible solution by combining this element with combo
                // at previous position
                int possible_count = get<1>(next[previous_pos]) + 1;
                // solution is viable and better
                if ((get<2>(next[previous_pos])) && (possible_count < get<1>(last[idx])))
                {
                    ele = egg;
                    c = possible_count;
                    v = true;
                }
                // new solution is not viable -> just use the old one
                else
                {
                    next[idx] = last[idx];
                }
            }
            idx++;
        }
        last = next;
    }
    auto& [e, count, v] =next.back();
    if (v)
    {

        return count;
    }
    throw invalid_argument("there is no valid combination");
}
