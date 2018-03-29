#ifndef __TYPE_DISTRIBUTION_PROXY__
#define __TYPE_DISTRIBUTION_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/TypeDistribution.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"

class TypeDistributionProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<TypeDistribution>> m_typeDistribution;

    std::ifstream m_typeDistributionFile;

public:
    TypeDistributionProxy() throw();

    virtual ~TypeDistributionProxy();

    virtual void parse();

    virtual void show();

    TypeDistribution& get(const std::string& userID);

};

#endif
