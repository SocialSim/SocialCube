#ifndef __COMMUNITY_DISTRIBUTION_PROXY__
#define __COMMUNITY_DISTRIBUTION_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class CommunityDistributionProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unordered_map<std::string, double>> m_userCommunityDistributions;

    std::ifstream m_communityDistributionStatisticFile;

public:
    CommunityDistributionProxy(const std::string& file) throw();

    virtual ~CommunityDistributionProxy();

    virtual void parse();

    virtual void show();

    std::unordered_map<std::string, double> get(const std::string& userID);

};

#endif
