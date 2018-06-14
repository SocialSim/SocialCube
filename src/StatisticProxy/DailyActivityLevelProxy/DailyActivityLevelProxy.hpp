#ifndef __HOURLY_ACTION_RATE_PROXY__
#define __HOURLY_ACTION_RATE_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/DailyActivityLevel.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class DailyActivityLevelProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<DailyActivityLevel>> m_dailyActivityLevels;

    std::ifstream m_dailyActivityLevelStatisticFile;

public:
    DailyActivityLevelProxy(const std::string& file) throw();

    virtual ~DailyActivityLevelProxy();

    virtual void parse();

    virtual void show();

    DailyActivityLevel& get(const std::string& userID);

};

#endif
