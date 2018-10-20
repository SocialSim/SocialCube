#ifndef __POST_LIFESPAN_DISTRIBUTION__
#define __POST_LIFESPAN_DISTRIBUTION__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>

class PostLifespanDistribution {

private:

    std::string m_userID;

    std::unordered_map<int, double> m_lifespans_dists;

public:

    PostLifespanDistribution(std::string t_userID);

    ~PostLifespanDistribution();

    void insertLifespanDist(int lifespan, double prob);

    std::unordered_map<int, double> getLifespanDists();

    void show();
};

#endif
