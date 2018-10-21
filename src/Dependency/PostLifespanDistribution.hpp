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

    std::vector<std::pair<int, double>> m_lifespans_dists;

public:

    PostLifespanDistribution(std::string t_userID);

    ~PostLifespanDistribution();

    void pushLifespanDist(int t_lifespan, double t_prob);

    std::vector<std::pair<int, double>> getLifespanDist();

    void show();
};

#endif
