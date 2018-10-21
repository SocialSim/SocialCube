#ifndef __POST_LIFESPAN_DISTRIBUTION_PROXY__
#define __POST_LIFESPAN_DISTRIBUTION_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/PostLifespanDistribution.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class PostLifespanDistributionProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<PostLifespanDistribution>> m_postLifespanDistribution;

    std::ifstream m_postLifespanDistributionFile;

public:
    PostLifespanDistributionProxy(const std::string& file) throw();

    virtual ~PostLifespanDistributionProxy();

    virtual void parse();

    virtual void show();

    PostLifespanDistribution& get(const std::string& userID);

};

#endif
