#ifndef __POST_BREADTH_DISTRIBUTION__
#define __POST_BREADTH_DISTRIBUTION__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>

class PostBreadthDistribution {

private:

    std::string m_userID;

    std::vector<std::pair<int, double>> m_breadth_dists;

public:

    PostBreadthDistribution(std::string t_userID);

    ~PostBreadthDistribution();

    void pushBreadthDist(int t_breadth, double t_prob);

    std::vector<std::pair<int, double>> getBreadthDist();

    void show();
};

#endif
