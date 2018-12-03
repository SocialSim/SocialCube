#ifndef __POST_BREADTH_DISTRIBUTION_PROXY__
#define __POST_BREADTH_DISTRIBUTION_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/PostBreadthDistribution.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class PostBreadthDistributionProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<PostBreadthDistribution>> m_postBreadthDistribution;

    std::ifstream m_postBreadthDistributionFile;

public:
    PostBreadthDistributionProxy(const std::string& file) throw();

    virtual ~PostBreadthDistributionProxy();

    virtual void parse();

    virtual void show();

    PostBreadthDistribution& get(const std::string& userID);

};

#endif
