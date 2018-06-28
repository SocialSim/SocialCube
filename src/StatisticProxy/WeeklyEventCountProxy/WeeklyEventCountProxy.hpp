#ifndef __WEEKLY_EVENT_COUNT_PROXY__
#define __WEEKLY_EVENT_COUNT_PROXY__

#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "Dependency/WeeklyEventCount.hpp"
#include "StatisticProxy/ProxyModule.hpp"
#include "common/Exception.hpp"
#include "Log/Log.hpp"

class WeeklyEventCountProxy : public ProxyModule {
private:

    std::unordered_map<std::string, std::unique_ptr<WeeklyEventCount>> m_weeklyEventCounts;

    std::ifstream m_weeklyEventCountStatisticFile;

public:
    WeeklyEventCountProxy(const std::string& file) throw();

    virtual ~WeeklyEventCountProxy();

    virtual void parse();

    virtual void show();

    WeeklyEventCount& get(const std::string& userID);

};

#endif
