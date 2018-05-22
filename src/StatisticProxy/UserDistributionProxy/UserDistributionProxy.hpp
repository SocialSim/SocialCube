#ifndef __USER_DISTRIBUTION_PROXY__
#define __USER_DISTRIBUTION_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include "Dependency/UserDistribution.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class UserDistributionProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<UserDistribution>> m_repoUserDistribution;

    std::ifstream m_userDistributionFile;

public:
    UserDistributionProxy(const std::string& file) throw();

    virtual ~UserDistributionProxy();

    virtual void parse();

    UserDistribution& get(const std::string& repoID);

    virtual void show();

};

#endif
