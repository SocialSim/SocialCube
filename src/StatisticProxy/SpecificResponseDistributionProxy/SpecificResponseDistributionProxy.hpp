#ifndef __SPECIFIC_RESPONSE_DISTRIBUTION_PROXY__
#define __SPECIFIC_RESPONSE_DISTRIBUTION_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/SpecificResponseDistribution.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class SpecificResponseDistributionProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<SpecificResponseDistribution>> m_specificResponseDistribution;

    std::ifstream m_specificResponseDistributionFile;

public:
    SpecificResponseDistributionProxy(const std::string& file) throw();

    virtual ~SpecificResponseDistributionProxy();

    virtual void parse();

    virtual void show();

    SpecificResponseDistribution& get(const std::string& userID);

};

#endif
