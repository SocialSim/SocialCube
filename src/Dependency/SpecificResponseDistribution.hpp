#ifndef __SPECIFIC_RESPONSE_DISTRIBUTION__
#define __SPECIFIC_RESPONSE_DISTRIBUTION__

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>

class SpecificResponseDistribution {

private:

    std::string m_userID;

    std::vector<std::pair<std::string, double>> m_response_dists;

public:

    SpecificResponseDistribution(std::string t_userID);

    ~SpecificResponseDistribution();

    void pushResponseDist(std::string t_response, double t_prob);

    std::vector<std::pair<std::string, double>> getResponseDist();

    void show();
};

#endif
