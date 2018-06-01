#ifndef __ACTIVITY_LEVEL_PROXY__
#define __ACTIVITY_LEVEL_PROXY__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class ActivityLevelProxy : public ProxyModule {
protected:
    std::vector<std::string> m_activityLevels;

    std::ifstream m_activityLevelStatisticsFile;
public:
    ActivityLevelProxy(const std::string& file) throw();

    virtual ~ActivityLevelProxy();

    virtual void parse();

    std::vector<std::string>& get();

    virtual uint64_t getCommunityTag(const std::string& t_userID);

    virtual void show();
};

#endif
